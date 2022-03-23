# Name: Makefile
# Project: Micronucleus
# License: GNU GPL v2 (see License.txt)

# Controller type: AtTiny 2313
# Configuration:   Gabo
# Last Change:     Sun, 04 Nov 2018
 
CFLAGS += -DENABLE_RESET_VECT_CLIENT
 
USBLIBRARY = 0
F_CPU = 16000000
DEVICE = attiny2313

FUSEOPT = -U lfuse:w:0xff:m -U hfuse:w:0x99:m -U efuse:w:0xfe:m
FUSEOPT_DISABLERESET = -U lfuse:w:0xff:m -U hfuse:w:0x98:m -U efuse:w:0xfe:m

