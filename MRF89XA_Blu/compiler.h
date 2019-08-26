
#ifndef COMPILER_H
#define COMPILER_H
#include "GenericTypeDefs.h"
#define PIC16F1847_PIM
#include <pic16f1847.h>
//#include <pic18f26j50.h>
//#define PIC18F25J50_PIM

#define SUSPEND_IT()  /*uint8 SAVEICON = INTCON;INTCONbits.GIE=0*/
#define RESUME_IT()  /*if (SAVEICON & 0x80) {INTCONbits.GIE = 1;}*/
#define DISABLE_IT() INTCONbits.GIE=0

#endif

	



