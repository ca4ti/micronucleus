/*
 * AVR NRWW Flash section - generated from online fuse calculators
 * maximum "bootloader" section which can be set by fuses
 * special values:
 *   0x0000     - no bootloader area - whole flash is NRWW (tiny chips)
 *   FLASHEND+1 - unknown chip or chip without self programmable flash
 */

#if defined(__AVR_ATmega103__)
  #define NRWW_START_ADDRESS	0x1E000
#elif defined(__AVR_ATmega128A__)
  #define NRWW_START_ADDRESS	0x1E000
#elif defined(__AVR_ATmega128RFA1__)
  #define NRWW_START_ADDRESS	0x1E000
#elif defined(__AVR_ATmega128__)
  #define NRWW_START_ADDRESS	0x1E000
#elif defined(__AVR_ATmega1280__)
  #define NRWW_START_ADDRESS	0x1E000
#elif defined(__AVR_ATmega1281__)
  #define NRWW_START_ADDRESS	0x1E000
#elif defined(__AVR_ATmega1284P__)
  #define NRWW_START_ADDRESS	0x1E000
#elif defined(__AVR_ATmega16A__)
  #define NRWW_START_ADDRESS	0x3800
#elif defined(__AVR_ATmega16HVA__)
  #define NRWW_START_ADDRESS	0x0000
#elif defined(__AVR_ATmega16HVB__)
  #define NRWW_START_ADDRESS	0x3000
#elif defined(__AVR_ATmega16M1__)
  #define NRWW_START_ADDRESS	0x3000
#elif defined(__AVR_ATmega16U2__)
  #define NRWW_START_ADDRESS	0x3000
#elif defined(__AVR_ATmega16U4__)
  #define NRWW_START_ADDRESS	0x3000
#elif defined(__AVR_ATmega16__)
  #define NRWW_START_ADDRESS	0x3800
#elif defined(__AVR_ATmega161__)
  #define NRWW_START_ADDRESS	0x3800
#elif defined(__AVR_ATmega162__)
  #define NRWW_START_ADDRESS	0x3800
#elif defined(__AVR_ATmega163__)
  #define NRWW_START_ADDRESS	0x0000
#elif defined(__AVR_ATmega164PA__)
  #define NRWW_START_ADDRESS	0x3800
#elif defined(__AVR_ATmega164P__)
  #define NRWW_START_ADDRESS	0x3800
#elif defined(__AVR_ATmega165PA__)
  #define NRWW_START_ADDRESS	0x3800
#elif defined(__AVR_ATmega165P__)
  #define NRWW_START_ADDRESS	0x3800
#elif defined(__AVR_ATmega165__)
  #define NRWW_START_ADDRESS	0x3800
#elif defined(__AVR_ATmega168PA__)
  #define NRWW_START_ADDRESS	0x3800
#elif defined(__AVR_ATmega168P__)
  #define NRWW_START_ADDRESS	0x3800
#elif defined(__AVR_ATmega168__)
  #define NRWW_START_ADDRESS	0x3800
#elif defined(__AVR_ATmega169PA__)
  #define NRWW_START_ADDRESS	0x3800
#elif defined(__AVR_ATmega169P__)
  #define NRWW_START_ADDRESS	0x3800
#elif defined(__AVR_ATmega169__)
  #define NRWW_START_ADDRESS	0x3800
#elif defined(__AVR_ATmega2560__)
  #define NRWW_START_ADDRESS	0x3E000
#elif defined(__AVR_ATmega2561__)
  #define NRWW_START_ADDRESS	0x3E000
#elif defined(__AVR_ATmega32A__)
  #define NRWW_START_ADDRESS	0x7000
#elif defined(__AVR_ATmega32C1__)
  #define NRWW_START_ADDRESS	0x7000
#elif defined(__AVR_ATmega32HVB__)
  #define NRWW_START_ADDRESS	0x7000
#elif defined(__AVR_ATmega32M1__)
  #define NRWW_START_ADDRESS	0x7000
#elif defined(__AVR_ATmega32U2__)
  #define NRWW_START_ADDRESS	0x7000
#elif defined(__AVR_ATmega32U4__)
  #define NRWW_START_ADDRESS	0x7000
#elif defined(__AVR_ATmega32U6__)
  #define NRWW_START_ADDRESS	0x7000
#elif defined(__AVR_ATmega32__)
  #define NRWW_START_ADDRESS	0x7000
#elif defined(__AVR_ATmega323__)
  #define NRWW_START_ADDRESS	0x0000
#elif defined(__AVR_ATmega324PA__)
  #define NRWW_START_ADDRESS	0x7000
#elif defined(__AVR_ATmega324P__)
  #define NRWW_START_ADDRESS	0x7000
#elif defined(__AVR_ATmega325P__)
  #define NRWW_START_ADDRESS	0x7000
#elif defined(__AVR_ATmega325__)
  #define NRWW_START_ADDRESS	0x7000
#elif defined(__AVR_ATmega3250P__)
  #define NRWW_START_ADDRESS	0x7000
#elif defined(__AVR_ATmega3250__)
  #define NRWW_START_ADDRESS	0x7000
#elif defined(__AVR_ATmega328P__) || defined(__AVR_ATmega328__)
  #define NRWW_START_ADDRESS	0x7000
#elif defined(__AVR_ATmega329P__)
  #define NRWW_START_ADDRESS	0x7000
#elif defined(__AVR_ATmega329__)
  #define NRWW_START_ADDRESS	0x7000
#elif defined(__AVR_ATmega3290P__)
  #define NRWW_START_ADDRESS	0x7000
#elif defined(__AVR_ATmega3290__)
  #define NRWW_START_ADDRESS	0x7000
#elif defined(__AVR_ATmega406__)
  #define NRWW_START_ADDRESS	0x9000
#elif defined(__AVR_ATmega48PA__)
  #define NRWW_START_ADDRESS	0x0000
#elif defined(__AVR_ATmega48P__)
  #define NRWW_START_ADDRESS	0x0000
#elif defined(__AVR_ATmega48__)
  #define NRWW_START_ADDRESS	0x0000
#elif defined(__AVR_ATmega64A__)
  #define NRWW_START_ADDRESS	0xE000
#elif defined(__AVR_ATmega64C1__)
  #define NRWW_START_ADDRESS	0xE000
#elif defined(__AVR_ATmega64HVE__)
  #define NRWW_START_ADDRESS	0xE000
#elif defined(__AVR_ATmega64M1__)
  #define NRWW_START_ADDRESS	0xE000
#elif defined(__AVR_ATmega64__)
  #define NRWW_START_ADDRESS	0xE000
#elif defined(__AVR_ATmega640__)
  #define NRWW_START_ADDRESS	0xE000
#elif defined(__AVR_ATmega644PA__)
  #define NRWW_START_ADDRESS	0xE000
#elif defined(__AVR_ATmega644P__)
  #define NRWW_START_ADDRESS	0xE000
#elif defined(__AVR_ATmega644__)
  #define NRWW_START_ADDRESS	0xE000
#elif defined(__AVR_ATmega645__)
  #define NRWW_START_ADDRESS	0xE000
#elif defined(__AVR_ATmega6450__)
  #define NRWW_START_ADDRESS	0xE000
#elif defined(__AVR_ATmega649P__)
  #define NRWW_START_ADDRESS	0xE000
#elif defined(__AVR_ATmega649__)
  #define NRWW_START_ADDRESS	0xE000
#elif defined(__AVR_ATmega6490__)
  #define NRWW_START_ADDRESS	0xE000
#elif defined(__AVR_ATmega8A__)
  #define NRWW_START_ADDRESS	0x1800
#elif defined(__AVR_ATmega8HVA__)
  #define NRWW_START_ADDRESS	0x0000
#elif defined(__AVR_ATmega8U2__)
  #define NRWW_START_ADDRESS	0x3000
#elif defined(__AVR_ATmega8__)
  #define NRWW_START_ADDRESS	0x1800
#elif defined(__AVR_ATmega8515__)
  #define NRWW_START_ADDRESS	0x1800
#elif defined(__AVR_ATmega8535__)
  #define NRWW_START_ADDRESS	0x1800
#elif defined(__AVR_ATmega88PA__)
  #define NRWW_START_ADDRESS	0x1800
#elif defined(__AVR_ATmega88P__)
  #define NRWW_START_ADDRESS	0x1800
#elif defined(__AVR_ATmega88__)
  #define NRWW_START_ADDRESS	0x1800
#elif defined(__AVR_ATtiny10__)
  #define NRWW_START_ADDRESS	0x0000
#elif defined(__AVR_ATtiny11__)
  #define NRWW_START_ADDRESS	0x0000
#elif defined(__AVR_ATtiny12__)
  #define NRWW_START_ADDRESS	0x0000
#elif defined(__AVR_ATtiny13A__)
  #define NRWW_START_ADDRESS	0x0000
#elif defined(__AVR_ATtiny13__)
  #define NRWW_START_ADDRESS	0x0000
#elif defined(__AVR_ATtiny15__)
  #define NRWW_START_ADDRESS	0x0000
#elif defined(__AVR_ATtiny167__)
  #define NRWW_START_ADDRESS	0x0000
#elif defined(__AVR_ATtiny20__)
  #define NRWW_START_ADDRESS	0x0000
#elif defined(__AVR_ATtiny22__)
  #define NRWW_START_ADDRESS	0x0000
#elif defined(__AVR_ATtiny2313A__)
  #define NRWW_START_ADDRESS	0x0000
#elif defined(__AVR_ATtiny2313__)
  #define NRWW_START_ADDRESS	0x0000
#elif defined(__AVR_ATtiny24A__)
  #define NRWW_START_ADDRESS	0x0000
#elif defined(__AVR_ATtiny24__)
  #define NRWW_START_ADDRESS	0x0000
#elif defined(__AVR_ATtiny25__)
  #define NRWW_START_ADDRESS	0x0000
#elif defined(__AVR_ATtiny26__)
  #define NRWW_START_ADDRESS	0x0000
#elif defined(__AVR_ATtiny261A__)
  #define NRWW_START_ADDRESS	0x0000
#elif defined(__AVR_ATtiny261__)
  #define NRWW_START_ADDRESS	0x0000
#elif defined(__AVR_ATtiny28__)
  #define NRWW_START_ADDRESS	0x0000
#elif defined(__AVR_ATtiny4__)
  #define NRWW_START_ADDRESS	0x0000
#elif defined(__AVR_ATtiny40__)
  #define NRWW_START_ADDRESS	0x0000
#elif defined(__AVR_ATtiny43U__)
  #define NRWW_START_ADDRESS	0x0000
#elif defined(__AVR_ATtiny4313__)
  #define NRWW_START_ADDRESS	0x0000
#elif defined(__AVR_ATtiny44A__)
  #define NRWW_START_ADDRESS	0x0000
#elif defined(__AVR_ATtiny44__)
  #define NRWW_START_ADDRESS	0x0000
#elif defined(__AVR_ATtiny45__)
  #define NRWW_START_ADDRESS	0x0000
#elif defined(__AVR_ATtiny461A__)
  #define NRWW_START_ADDRESS	0x0000
#elif defined(__AVR_ATtiny461__)
  #define NRWW_START_ADDRESS	0x0000
#elif defined(__AVR_ATtiny48__)
  #define NRWW_START_ADDRESS	0x0000
#elif defined(__AVR_ATtiny5__)
  #define NRWW_START_ADDRESS	0x0000
#elif defined(__AVR_ATtiny84__)
  #define NRWW_START_ADDRESS	0x0000
#elif defined(__AVR_ATtiny841__)
  #define NRWW_START_ADDRESS    0x0000
#elif defined(__AVR_ATtiny85__)
  #define NRWW_START_ADDRESS	0x0000
#elif defined(__AVR_ATtiny861A__)
  #define NRWW_START_ADDRESS	0x0000
#elif defined(__AVR_ATtiny861__)
  #define NRWW_START_ADDRESS	0x0000
#elif defined(__AVR_ATtiny9__)
  #define NRWW_START_ADDRESS	0x0000
#elif defined(__AVR_AT90CAN128__)
  #define NRWW_START_ADDRESS	0x1E000
#elif defined(__AVR_AT90CAN32__)
  #define NRWW_START_ADDRESS	0x6000
#elif defined(__AVR_AT90CAN64__)
  #define NRWW_START_ADDRESS	0xE000
#elif defined(__AVR_AT90PWM2B__)
  #define NRWW_START_ADDRESS	0x1800
#elif defined(__AVR_AT90PWM2__)
  #define NRWW_START_ADDRESS	0x1800
#elif defined(__AVR_AT90PWM216__)
  #define NRWW_START_ADDRESS	0x3000
#elif defined(__AVR_AT90PWM3B__)
  #define NRWW_START_ADDRESS	0x1800
#elif defined(__AVR_AT90PWM3__)
  #define NRWW_START_ADDRESS	0x1800
#elif defined(__AVR_AT90PWM316__)
  #define NRWW_START_ADDRESS	0x3000
#elif defined(__AVR_AT90PWM81__)
  #define NRWW_START_ADDRESS	0x1800
#elif defined(__AVR_AT90SCR100__)
  #define NRWW_START_ADDRESS	0xE000
#elif defined(__AVR_AT90S1200__)
  #define NRWW_START_ADDRESS	0x0000
#elif defined(__AVR_AT90S2313__)
  #define NRWW_START_ADDRESS	0x0000
#elif defined(__AVR_AT90S2323__)
  #define NRWW_START_ADDRESS	0x0000
#elif defined(__AVR_AT90S2343__)
  #define NRWW_START_ADDRESS	0x0000
#elif defined(__AVR_AT90S4414__)
  #define NRWW_START_ADDRESS	0x0000
#elif defined(__AVR_AT90S4433__)
  #define NRWW_START_ADDRESS	0x0000
#elif defined(__AVR_AT90S4434__)
  #define NRWW_START_ADDRESS	0x0000
#elif defined(__AVR_AT90S8515__)
  #define NRWW_START_ADDRESS	0x1800
#elif defined(__AVR_AT90S8535__)
  #define NRWW_START_ADDRESS	0x1800
#else
  #warning Undefined NRWW_START_ADDRESS for __AVR_ARCH__
  #define NRWW_START_ADDRESS	(FLASHEND+1)
#endif
