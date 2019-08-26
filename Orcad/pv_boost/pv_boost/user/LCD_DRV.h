
#include "hal.h"

void LCD_Init(void);

void LCD_SendLineToLCD(BYTE uLineNb);

void LCD_ClearLine(void);

extern BYTE uLine[];
#define LCDLine(x) (&uLine[x])	

//LCD
#define LCDRS LATDbits.LATD0

#define LCDEN LATDbits.LATD2

#define LCDD4 LATDbits.LATD4
#define LCDD5 LATDbits.LATD5
#define LCDD6 LATDbits.LATD6
#define LCDD7 LATDbits.LATD7
#define cCMD 0
#define cDATA 1 
#define cPOWER 0x02 
#define cLIGHT 0x08


#define uS(x)        (((x)*CPU_CLOCK)/48)
#define mS(x)        (((x)*CPU_CLOCK)*2)
#define c3uS         uS(3)
#define c100uS       uS(100)
#define c160uS       uS(160)

#define c50uS        uS(50)
#define c25uS        uS(25)
#define c16uS        uS(16)
#define c20uS        uS(20)

#define c50ms        mS(50) 
#define c10ms        mS(10) 
#define c2ms         mS(2)
	
#define  HALLCDSend4bit( uByte, type ) \
{\
		LCDRS = type;\
		if (uByte & 0x80) {LCDD7=1;} else {LCDD7=0;};\
		if (uByte & 0x40) {LCDD6=1;} else {LCDD6=0;};\
		if (uByte & 0x20) {LCDD5=1;} else {LCDD5=0;};\
		if (uByte & 0x10) {LCDD4=1;} else {LCDD4=0;};\
		LCD_WaitUs(c3uS);LCDEN=1;LCD_WaitUs(c3uS);LCDEN=0;LCD_WaitUs(c3uS);\
}

    #define HALWriteLCD(uByte) HALLCDSend4bit(uByte, cDATA);HALLCDSend4bit((uByte<<4), cDATA)
	#define HALCtrlLCDStart()  HALLCDSend4bit(0x00, cCMD);HALLCDSend4bit(0xC0, cCMD)
	#define HALCtrlLCDStop()   HALLCDSend4bit(0x00, cCMD);HALLCDSend4bit(0x80, cCMD)
    #define HALCtrlLCDOFF()    LCDEN=0
    #define HALCtrlLCDON() 	   LCDEN=0
    #define HALCtrlLCDFSet8()  HALLCDSend4bit(0x30, cCMD)
	#define HALCtrlLCDFSet4()  HALLCDSend4bit(0x20, cCMD)
	#define HALCtrlLCDFSet42() HALLCDSend4bit(0x20, cCMD);HALLCDSend4bit(0x80, cCMD)
    #define HALCtrlLCDCLR()    HALLCDSend4bit(0x00, cCMD);HALLCDSend4bit(0x10, cCMD)
    #define HALCtrlLCDL1()     HALLCDSend4bit(0x80, cCMD);HALLCDSend4bit(0x00, cCMD)
    #define HALCtrlLCDL2()     HALLCDSend4bit(0xC0, cCMD);HALLCDSend4bit(0x00, cCMD)
    #define HALCtrlLCDEMS()    HALLCDSend4bit(0x00, cCMD);HALLCDSend4bit(0x60, cCMD)
    #define HALCtrlLCDCGRAM()  HALLCDSend4bit(0x40, cCMD);HALLCDSend4bit(0x00, cCMD)
 


	

