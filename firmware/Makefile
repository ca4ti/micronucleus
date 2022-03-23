# Name: Makefile
# Project: Micronucleus
# Author: Jenna Fox; portions by Christian Starkjohann, Louis Beaudoin
# Creation Date: 2007-12-10
# Tabsize: 4
# Copyright: (c) 2007 by OBJECTIVE DEVELOPMENT Software GmbH
# License: GNU GPL v2 (see License.txt)

###############################################################################
# Configure the following variables according to your AVR.
# Program the device with
#     make fuse    			# to set the clock generator, boot section size etc.
#     make flash   			# to load the boot loader into flash
#     make disablereset		# use external reset line for IO (CAUTION: this is not easy to enable again, see README) 

# use gnu make version 4.2 or newer for windows can be downloaded from http://blog.zakkemble.co.uk/avr-gcc-builds/
#
all: main.hex

ALLCONFIGS = $(sort $(patsubst configuration/%/Makefile.inc,%,$(wildcard configuration/*/Makefile.inc)))

define MCFG
$(1): configuration/$(1)/Makefile.inc configuration/$(1)/bootloaderconfig.h
	@$(MAKE) --no-print-directory CONFIG=$(1) main.hex

endef

$(eval $(foreach c,$(ALLCONFIGS),$(call MCFG,$(c))))

CONFIG ?= undefined

PREVCFG = none
DEPLADR = 
-include Aconfig.inc
ifeq ($(CONFIG),undefined)
  ifeq ($(PREVCFG),none)
    CONFIG = t85_default
    #CONFIG ?= t85_aggressive
    #CONFIG ?= t841_default
    #CONFIG ?= t167_default
  else
    CONFIG = $(PREVCFG)
  endif
endif
ifneq ($(PREVCFG),$(CONFIG))
  DEPLADR = .FORCE
endif

CFLAGS =
CONFIGPATH = configuration/$(CONFIG)
include $(CONFIGPATH)/Makefile.inc

PROGRAMMER ?= -c USBasp
# PROGRAMMER contains AVRDUDE options to address your programmer

# Tools:
AVRDUDE = avrdude $(PROGRAMMER) -p $(DEVICE) 
CC = avr-gcc
ifeq "$(OS)" "Windows_NT"
RM = -DEL /Q /F
CP = -COPY /Y
DS = \\
else
RM = rm -f
CP = cp
DS = /
endif

# Options:
CFLAGS += -I. -g2 -Os # -Wall
CFLAGS += -I$(CONFIGPATH) -mmcu=$(DEVICE) -DF_CPU=$(F_CPU)
ifeq ($(USBLIBRARY),1)
CFLAGS += -DUSBLIBRARY=1
endif
CFLAGS += -nostartfiles -fdata-sections -fno-inline-small-functions -fpack-struct -fno-move-loop-invariants -fno-tree-scev-cprop
CFLAGSUP = $(CFLAGS)
CFLAGS += -ffunction-sections

LDFLAGS = -Wl,--relax,--gc-sections
LDSTART = -Wl,--section-start=.text=$(BOOTLOADER_ADDR)

OBJECTS =  crt1.o usbdrvasm.o oddebug.o
OBJECTS += osccalASM.o

LDRSIZDEP = $(CONFIGPATH)/Makefile.inc $(CONFIGPATH)/bootloaderconfig.h \
            genhdr.c main.c 

.SUFFIXES:
.SUFFIXES: .o .c .S

.c.o:
	@$(CC) $(CFLAGS) -c $< -o $@

.S.o:
	@$(CC) $(CFLAGS) -x assembler-with-cpp -c $< -o $@



usbdrvasm.o: usbdrv/usbdrvasm.S usbdrv/asmcommon.inc
	@$(CC) $(CFLAGS) -x assembler-with-cpp -c $< -o $@

oddebug.o: usbdrv/oddebug.c
	$(CC) $(CFLAGS) -c $< -o $@

main.o: main.c loadersize.inc
	$(eval include loadersize.inc)
	$(CC) $(CFLAGS) -DBOOTLOADER_ADDRESS=0x$(BOOTLOADER_ADDR) -c $< -o $@ -Wa,-ahls=$<.lst

upgrade.o: upgrade.c loadersize.inc
	$(eval include loadersize.inc)
	@$(CC) $(CFLAGSUP) -DBOOTLOADER_ADDRESS=0x$(BOOTLOADER_ADDR) -c $< -o $@ -Wa,-ahls=$<.lst

# "-x assembler-with-cpp" should not be necessary since this is the default
# file type for the .S (with capital S) extension. However, upper case
# characters are not always preserved on Windows. To ensure WinAVR
# compatibility define the file type manually.

.c.s:
	@$(CC) $(CFLAGS) -S $< -o $@

.FORCE:

mainsiz.o: $(OBJECTS)
	@$(CC) $(CFLAGS) -DBOOTLOADER_ADDRESS=0x0180 -c main.c -o mainso.o
	@$(CC) $(CFLAGS) -o mainsiz.elf $(OBJECTS) mainso.o $(LDFLAGS) \
	-Wl,--section-start=.text=180
	@avr-objcopy -O binary mainsiz.elf mainsiz.raw
	@avr-objcopy -I binary -O elf32-avr \
        --rename-section .data=.text \
        --redefine-sym _binary_main_raw_start=loader \
        --redefine-sym _binary_main_raw_end=loader_end \
	mainsiz.raw mainsiz.o
	@$(RM) mainsiz.elf mainsiz.raw mainso.o

ldrsize.w: mainsiz.o
	@$(CC) -nostartfiles -mmcu=$(DEVICE) \
	      -DLOADER_SIZE=0x$(firstword $(shell avr-nm mainsiz.o)) \
	      -c genhdr.c -o mainsiz.elf
	@avr-objcopy -O binary -j .genhead mainsiz.elf $@
	@$(RM) mainsiz.elf

loadersize.inc: $(LDRSIZDEP)
	$(info $(shell $(MAKE) --no-print-directory CONFIG=$(CONFIG) ldrsize.w))
	$(eval include ldrsize.w)
	$(file >$@,BOOTLOADER_ADDR = $(BOOTLOADER_ADDR))
	$(file >>$@,OBJARCH = $(OBJARCH))
	$(file >>$@,NRWW_ORG = $(NRWW_ORG))
	$(info Recalculated start address is 0x$(BOOTLOADER_ADDR))
	@$(RM) ldrsize.w
	
Aconfig.inc: $(DEPLADR)
ifneq ($(PREVCFG),$(CONFIG))
	$(file >$@,PREVCFG := $(CONFIG))
	$(file >>$@,PREVDEV := $(DEVICE))
	$(info Rebuild for $(CONFIG) prevoius was $(PREVCFG))
	-@$(MAKE) --no-print-directory clean
	$(eval PREVCFG = $(CONFIG))
else
	$(eval PREVCFG = $(CONFIG))
endif

flash:	all
	$(AVRDUDE) -U flash:w:main.hex:i -B 20

readflash:
	$(AVRDUDE) -U flash:r:read.hex:i -B 20

fuse:
	$(AVRDUDE) $(FUSEOPT) -B 20
	
disablereset:
	$(AVRDUDE) $(FUSEOPT_DISABLERESET) -B 20

read_fuses:
	$(UISP) --rd_fuses -B 20

clean:	.FORCE
	@$(RM) main.hex main.bin main.c.lst main.map main.raw *.o \
	main.s main.lss \
	upgrade.c.lst upgrade.map upgrade.elf upgrade.hex \
	bootloader_linkable.o loadersize.inc oddebug.c.lst \
	upgrade.lss micronusblib.inc micronusblib.ld

distclean: clean
	@$(RM) Aconfig.inc

# file targets:
main.bin: $(OBJECTS) main.o
	$(eval include loadersize.inc)
	@$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS) -Wl,-Map=main.map $(LDSTART)

main.hex:	main.bin
	$(info Building Micronucleus configuration: $(CONFIG))
	@$(RM) main.hex main.eep.hex
	@avr-objcopy -j .text -j .data -O ihex main.bin main.hex
	@avr-size main.bin

bootloader_linkable.o: main.bin loadersize.inc
	$(eval include loadersize.inc)
	@avr-objcopy -O binary main.bin main.raw
	@avr-objcopy -I binary -O elf32-avr $(OBJARCH) \
	--rename-section .data=.text \
	--redefine-sym _binary_main_raw_start=loader \
	--redefine-sym _binary_main_raw_end=loader_end \
	main.raw bootloader_linkable.o

upgrade.hex:	upgrade.o crt1.o bootloader_linkable.o 
	@$(CC) $(CFLAGSUP) -o upgrade.elf $^ $(LDFLAGS) -Wl,-Map=upgrade.map $(NRWW_ORG)
	@avr-objcopy -j .text -j .data -j nrww -O ihex upgrade.elf upgrade.hex

upgrade: upgrade.hex
	$(info Builded upgrade for $(CONFIG). Upload with)
	$(info micronucelus upgrade.hex)

EXPORTED_VARS = usbTxBuf usbDeviceAddr usbRxToken usbInputBufOffset usbTxLen \
	        usbMsgPtr usbRxLen usbNewDeviceAddr usbCurrentTok \
	        usbConfiguration usbRxBuf __bss_start __bss_end usbSofCount \
	        usbTxStatus1 usbTxStatus3
EXPORTED_FNS = calibrateOscillatorASM usbCrc16 usbCrc16Append __vector_2 __vector_1

define nmparse
  $(eval w3 := $(w2))
  $(eval w2 := $(w1))
  $(eval w1 := $(1))
  $(eval wo := $(strip $(if $(and $(findstring $(w2),$(3)), $(findstring $(1),$(2))), PROVIDE($(1) = 0x$(w3));)))
  $(if $(and $(wo),$(findstring $(1),__bss_start)),$(eval NMVDSSTART:=0x$(w3)))
  $(if $(and $(wo),$(findstring $(1),__bss_end)),$(eval NMVDSEND:=0x$(w3)))
  $(eval wo := $(subst __bss_end,usbBootVarEnd,$(wo)))
  $(eval wo := $(subst __bss_start,usbBootReserved,$(wo)))
  $(eval wo := $(subst __vector_2,micronucleusInt,$(wo)))
  $(eval wo := $(subst __vector_1,micronucleusInt,$(wo)))
  $(if $(wo), $(file >>$(4),	$$(file >>$$@,$(wo))))
endef

define grep-fns
  $(eval w3 := )
  $(eval w2 := )
  $(eval w1 := )
  $(eval wo := )
  $(foreach ww,$(1),$(call nmparse,$(ww),$(2),$(3),$(4)))
endef

define last3
  $(eval w3 := $(w2))
  $(eval w2 := $(w1))
  $(eval w1 := $(1))
  $(eval wo := $(strip $(w3) $(w2) $(w1)))
endef

define datetimenow
  $(eval w3 := )
  $(eval w2 := )
  $(eval w1 := )
  $(eval wo := )
  $(eval ti := $(lastword $(shell echo __TIME__ | $(CC) -E -c -)))
  $(foreach ww,$(shell echo __DATE__ | $(CC) -E -c - ),$(call last3,$(ww)))
  $(eval now := $(subst $\",,$(wo) $(ti)))
endef

micronusblib.inc: main.bin loadersize.inc
	$(eval include loadersize.inc)
	$(call datetimenow)
	$(file >$@,# Makefile include for use micronucleus bootloader as usb library )
	$(file >>$@,# generated for $(CONFIG) ($(DEVICE)) at $(now) )
	$(file >>$@,)
	$(file >>$@,micronusblib.ld:)
	$(file >>$@,	$$(file >$$@,/* auto generated by micronusblib.inc dont modify */))
	$(eval W = $(shell avr-nm -g $<))
	$(call grep-fns,$(W),$(EXPORTED_FNS),T,$@)
	$(file >>$@,	$$(file >>$$@,))
	$(call grep-fns,$(W),$(EXPORTED_VARS),B,$@) 
	$(file >>$@,	$$(file >>$$@,))
	$(file >>$@,	$$(file >>$$@,SECTIONS))
	$(file >>$@,	$$(file >>$$@,{))
	$(file >>$@,	$$(file >>$$@,  usbbv.data : AT ($(NMVDSSTART))))
	$(file >>$@,	$$(file >>$$@,  {))
	$(file >>$@,	$$(file >>$$@,    KEEP (*(usbbv.data))))
	$(file >>$@,	$$(file >>$$@,  }))
	$(file >>$@,	$$(file >>$$@,}))
	$(file >>$@,)
	$(file >>$@,CFLAGS += -DUSBRESERVERDDATA=$(NMVDSEND)-$(NMVDSSTART) -DHAVEUSBLIB=1)
	$(file >>$@,MCUARCH = $(subst -B avr:,avr,$(OBJARCH)))
	$(file >>$@,LDFLAGS += -T micronusblib.ld -T ldscripts/$$(MCUARCH).x)
	$(file >>$@,LDDEPENDS += micronusblib.ld)
	$(file >>$@,)

release: main.hex upgrade.hex $(if $(filter 1,$(USBLIBRARY)),micronusblib.inc)
	$(CP) main.hex releases$(DS)$(CONFIG).hex
	$(CP) upgrade.hex releases$(DS)$(CONFIG)_upgrade.hex
ifeq ($(USBLIBRARY),1)
	$(CP) micronusblib.inc releases$(DS)$(CONFIG)_bootlib.inc
endif

define MKREL
@$(MAKE) --no-print-directory CONFIG=$(1) release

endef

releases: .FORCE
	$(foreach cfg,$(ALLCONFIGS),$(call MKREL,$(cfg))	)

disasm:	main.bin upgrade.hex
	@avr-objdump -d -S main.bin >main.lss
	@avr-objdump -d -S upgrade.elf >upgrade.lss
