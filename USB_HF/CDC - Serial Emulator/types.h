
typedef unsigned char uint8; // 8-bit
typedef unsigned short int uint16; // 16-bit
typedef unsigned long uint32; // 32-bit


#define SUSPEND_IT()  /*uint8 SAVEICON = INTCON;INTCONbits.GIE=0*/
#define RESUME_IT()  /*if (SAVEICON & 0x80) {INTCONbits.GIE = 1;}*/
#define DISABLE_IT() INTCONbits.GIE=0