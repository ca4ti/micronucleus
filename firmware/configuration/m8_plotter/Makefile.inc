# Name: Makefile
# Project: Micronucleus
# License: GNU GPL v2 (see License.txt)

# Controller type: AtMega 8 - 16 MHz
# Configuration:   Gabo
# Last Change:     Mar 16,2014
 
CFLAGS += -DENABLE_RESET_VECT_CLIENT
 
#USBLIBRARY = 1
F_CPU = 16000000
DEVICE = atmega8

# hexadecimal address for bootloader section to begin. To calculate the best value:
# - make clean; make main.hex; ### output will list data: 2124 (or something like that)
# - for the size of your device (8kb = 1024 * 8 = 8192) subtract above value 2124... = 6068
# - How many pages in is that? 6068 / 64 (tiny85 page size in bytes) = 94.8125
# - round that down to 94 - our new bootloader address is 94 * 64 = 6016, in hex = 1780
#BOOTLOADER_ADDRESS = 1A40

FUSEOPT = -U lfuse:w:0xee:m -U hfuse:w:0xd1:m 
FUSEOPT_DISABLERESET = -U lfuse:w:0xee:m -U hfuse:w:0x51:m

