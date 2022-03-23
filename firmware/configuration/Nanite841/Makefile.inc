# Name: Makefile
# Project: Micronucleus
# License: GNU GPL v2 (see License.txt)
#
# Controller type: ATtiny 841 
# Configuration:   Default configuration - 12 Mhz RC oscillator
# Last Change:     Mar 16,2014
 

F_CPU = 12000000
DEVICE = attiny841

FUSEOPT = -U lfuse:w:0xe2:m -U hfuse:w:0xdd:m -U efuse:w:0xf4:m
FUSEOPT_DISABLERESET =  # Not supported
