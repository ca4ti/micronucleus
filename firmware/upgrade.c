// Upgrade will firstly rewrite the interrupt vector table to disable the bootloader,
// rewriting it to just run the upgrade app. Next it erases and writes each page of the
// bootloader in sequence, erasing over any remaining pages leaving them set to 0xFFFF
// Finally upgrader erases it's interrupt table again and fills it with RJMPs to
// bootloaderAddress, effectively bridging the interrupts in to the new bootloader's
// interrupts table.
//
// While upgrade has been written with attiny85 and micronucleus in mind, it should
// work with other bootloaders and other chips with flash self program but no hardware
// bootloader protection, where the bootloader exists at the end of flash
//
// Be very careful to not power down the AVR while upgrader is running.
//
// If you define BEEP_BIT and BEEP_IOPORTNAME in your bootloaderconfig.h
// and connect a piezo between gnd and defined pin you'll hear a bleep 
// when the update is complete.
//
// If you have defined LED_MODE other than "NONE" then your LED will blink

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <avr/wdt.h>
#include <avr/boot.h>
#include <util/delay_basic.h>
#include "bootloaderconfig.h"
#include "avrnrww.h"

#define USB_CONCAT(a, b)            a ## b
#define USB_CONCAT_EXPANDED(a, b)   USB_CONCAT(a, b)

#define USB_OUTPORT(name)           USB_CONCAT(PORT, name)
#define USB_INPORT(name)            USB_CONCAT(PIN, name)
#define USB_DDRPORT(name)           USB_CONCAT(DDR, name)
#define USBOUT          USB_OUTPORT(USB_CFG_IOPORTNAME)
#define USBDDR          USB_DDRPORT(USB_CFG_IOPORTNAME)
#define USBMASK     ((1<<USB_CFG_DPLUS_BIT) | (1<<USB_CFG_DMINUS_BIT))

#if !defined(RWWSRE) && !defined(ASRE)
  #undef boot_rww_enable
  #if defined(CTPB) 
    #define boot_rww_enable()	\
            __SPM_REG=(_BV(CTPB)|_BV(__SPM_ENABLE));asm volatile("spm")
  #else
    #define boot_rww_enable()
  #endif
#endif

extern const PROGMEM char loader[];
extern const PROGMEM char loader_end[];
extern void (*__init)();
uint16_t table[SPM_PAGESIZE / 2];

static void secure_interrupt_vector_table(void);
static void write_new_bootloader(void);
static void forward_interrupt_vector_table(void);
static inline void beep(void);
static inline void reboot(void);
static inline void msdelay(unsigned char ms);

static void load_table(uint16_t address);
static void erwr_page(uint16_t address) 
#if NRWW_START_ADDRESS > 0
  __attribute__((section("nrww")))
#endif
;

int main(void) {
  USBDDR|=USBMASK;    // USB D+ and D- links outputs
  USBOUT&=~(USBMASK); // all to ground - force usb disconnect
  LED_INIT()
  LED_MACRO(1)
  msdelay(250);
  cli();
  
  eeprom_busy_wait();
  boot_spm_busy_wait();
  secure_interrupt_vector_table(); // reset our vector table to it's original state
  write_new_bootloader();
  forward_interrupt_vector_table();
  
  beep();

  LED_EXIT()
  reboot();
  
  return 0;
}

// erase first page, removing any interrupt table hooks the bootloader added when
// upgrade was uploaded
static void secure_interrupt_vector_table(void) {
  uint16_t jmpinit=0xC000 + (uint16_t)(&__init) / 2 - 1;
  
  load_table(0);
  if (table[0] != jmpinit) { // wipe out interrupt hook the bootloader rewrote
    table[0] = jmpinit;
    erwr_page(0);
  }
}

// erase bootloader's section and write over it with new bootloader code
static void write_new_bootloader(void) {
  int iter = 0;
  while (iter < (loader_end - loader)) {
    // read in one page's worth of data from progmem
    int word_addr = 0;
    while (word_addr < SPM_PAGESIZE) {
      int subaddress = ((int) loader) + iter + word_addr;
      if (subaddress >= ((int) loader) + (loader_end - loader)) {
        table[word_addr / 2] = 0xFFFF;
      } else {
        table[word_addr / 2] = pgm_read_word(subaddress);
      }
      
      word_addr += 2;
    }
    
    // erase page in destination and write updated page
    erwr_page(BOOTLOADER_ADDRESS + iter);
    iter += SPM_PAGESIZE; // 64
  }
}

// write in forwarding interrupt vector table
static void forward_interrupt_vector_table(void) {
  
  int iter = 0;
  while (iter < SPM_PAGESIZE / 2) {
    #if _VECTOR_SIZE == 2
    // rjmp to bootloader_address's interrupt table
    table[iter] = 0xC000 + ((BOOTLOADER_ADDRESS - iter) / 2) - 1;
    iter++;
    #else // _VECTOR_SIZE = 4
    // far jmp
    table[iter++] = 0x940c;
    table[iter++] = (BOOTLOADER_ADDRESS/2);
    #endif
  }
  erwr_page(0);
  // erase saved bootloader jump to application
  load_table(BOOTLOADER_ADDRESS - SPM_PAGESIZE);
  table[(SPM_PAGESIZE-4)/2]=0xFFFF; // saved vector clear
  table[(SPM_PAGESIZE-4)/2]=0xFFFF;
  erwr_page(BOOTLOADER_ADDRESS - SPM_PAGESIZE);
}

static void load_table(uint16_t address) {
  uint16_t subaddress = 0;
  address -= address % SPM_PAGESIZE; // round down to nearest page start
  
  while (subaddress < SPM_PAGESIZE) {
    table[subaddress / 2] = pgm_read_word(address + subaddress);
    subaddress += 2;
  }
}

// delay_loop_2 - 4 cycles per loop
// cycle length is 1000000/F_CPU usec => 1000/F_CPU msec
// for 1ms i need F_CPU/1000 cycles then F_CPU/4000 loops
#define MSDELAY	(uint16_t)((uint32_t)USB_CONCAT_EXPANDED(F_CPU,UL) / 4000UL)
static inline void msdelay(unsigned char ms) {
  do {
    _delay_loop_2(MSDELAY);     // delay and stay disconnected
  } while(--ms);
}
// beep for a quarter of a second
static inline void beep(void) {
#if LED_MODE != NONE
  unsigned char i = 0;
  while (i < 250) {
    LED_MACRO(i);
    _delay_loop_2(MSDELAY);
    i++;
  }
#endif
#if defined(BEEP_BIT) && defined(BEEP_IOPORTNAME)
  #define BEEPOUT          USB_OUTPORT(BEEP_IOPORTNAME)
  #define BEEPDDR          USB_DDRPORT(BEEP_IOPORTNAME)
  BEEPDDR |= _BV(BEEP_BIT);
  BEEPOUT &= ~(_BV(BEEP_BIT));
  
  unsigned char i = 0;
  while (i < 250) {
    _delay_loop_2(MSDELAY);
    BEEPOUT ^= _BV(BEEP_BIT);
    i++;
  }
#else
  msdelay(100);
#endif
}

static void reboot(void) {
  void (*ptrToFunction)(); // pointer to a function 
  ptrToFunction = 0x0000;
  (*ptrToFunction)(); // reset!
}

static void erwr_page(uint16_t address) 
{
  uint16_t addr = address - (address % SPM_PAGESIZE);
  boot_page_erase(addr);
  boot_spm_busy_wait();
  // fill buffer
  uint16_t iter = 0;
  while (iter < SPM_PAGESIZE / 2) {
    boot_page_fill(addr + (iter * 2), table[iter]);
    iter++;
  }
  boot_page_write(addr);
  boot_spm_busy_wait(); // Wait until the memory is written.
  boot_rww_enable();
}

// fill whole first page with nops - secure_interrupt_table rewrite it
#if __AVR_HAVE_JMP_CALL__
  __attribute__ ((section (".init0"))) const unsigned short nops[(SPM_PAGESIZE - 4) / 2];
#else
  __attribute__ ((section (".init0"))) const unsigned short nops[(SPM_PAGESIZE - 2) / 2];
#endif
