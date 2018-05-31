/* Functions for replace usbdrvasm.o with micronucleus bootloader as library
 * include in main program after include "usbconfig.h" */

#if USBRESERVERDDATA
char usbBootReserved[USBRESERVERDDATA] __attribute__((used,section("usbbv.data")));

extern void micronucleusInt();

#ifdef USB_INTR_VECTOR
ISR(USB_INTR_VECTOR, ISR_NAKED)
#else
ISR(INT0_vect, ISR_NAKED)
#endif
{
  asm volatile(
  "	rcall	micronucleusInt\n"
  "     reti\n"
  : /* no output */
  );
}

extern char usbBootVarEnd;
void clrlibvars() __attribute__((used,section(".init5"),naked));
void clrlibvars() {
  asm volatile (
    "     ldi   r26,lo8(%[bres])\n"
    "     ldi   r27,hi8(%[bres])\n"
    "l1:  st    X+,__zero_reg__\n"
    "     cpi   r26,lo8(%[bend])\n"
    "     brne  l1\n"
    : /* no out */
    : [bres] "p" (usbBootReserved),
      [bend] "p" (&usbBootVarEnd)
  );
}
#endif
