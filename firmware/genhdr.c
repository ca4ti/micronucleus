#include <avr/pgmspace.h>
#include "avrnrww.h"

#if (defined __AVR_ATtiny841__)||(defined __AVR_ATtiny441__)
  #define PGSZMUL	* 4
#else
  #define PGSZMUL	
#endif
#define LDRX	(1L + FLASHEND - LOADER_SIZE)
#define LDRADR	(LDRX - (LDRX % (SPM_PAGESIZE PGSZMUL)))
//#define LDRADR	FLASHEND
__attribute__ ((section (".genhead")))
const static char 
 hlA[]={
 'B','O','O','T','L','O','A','D','E','R','_','A','D','D','R',' ','=',' '
 ,LDRADR > 65535 ? ((LDRADR/65536) % 16 + ((LDRADR/65536) % 16 >=10 ? 0x37 : 0x30)) : ' '
 ,(LDRADR/4096) % 16 + ((LDRADR/4096) % 16 >=10 ? 0x37 : 0x30)
 ,(LDRADR/256) % 16 + ((LDRADR/256) % 16 >=10 ? 0x37 : 0x30)
 ,(LDRADR/16) % 16 + ((LDRADR/16) % 16 >=10 ? 0x37 : 0x30)
 ,LDRADR % 16 + (LDRADR % 16 >= 10 ? 0x37 : 0x30)
 ,0x0A
 ,'O','B','J','A','R','C','H',' ','=',' '
#ifdef __AVR_ARCH__
 ,'-','B',' ','a','v','r',':'
#if __AVR_ARCH__ >= 100
 ,(__AVR_ARCH__ / 100) % 10 + 0x30
#endif
#if __AVR_ARCH__ >= 10
 ,(__AVR_ARCH__ / 10) % 10 + 0x30
#endif
 ,__AVR_ARCH__ % 10 + 0x30
#endif
 ,0x0A
 ,'N','R','W','W','_','O','R','G',' ','=',' '
#if NRWW_START_ADDRESS > 0
 ,'-','W','l',',','-','-','s','e','c','t','i','o','n','-','s','t','a','r','t','=','n','r','w','w','=','0','x'
 ,NRWW_START_ADDRESS > 65535 ? ((NRWW_START_ADDRESS/65536) % 16 + ((NRWW_START_ADDRESS/65536) % 16 >=10 ? 0x37 : 0x30)) : '0'
 ,(NRWW_START_ADDRESS/4096) % 16 + ((NRWW_START_ADDRESS/4096) % 16 >=10 ? 0x37 : 0x30)
 ,(NRWW_START_ADDRESS/256) % 16 + ((NRWW_START_ADDRESS/256) % 16 >=10 ? 0x37 : 0x30)
 // NRWW have always 00 at the end
 ,'0','0'
#endif
 ,0x0A
};
