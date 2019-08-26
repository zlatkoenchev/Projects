#include "types.h"
#include "lcd_drv.h"


BYTE uLine[16];
const BYTE CGRAM[64]=
{
	0,0,0,0,0,0,0,0x1F,
	0,0,0,0,0,0,0x1F,0x1F,
	0,0,0,0,0,0x1F,0x1F,0x1F,
	0,0,0,0,0x1F,0x1F,0x1F,0x1F,
	0,0,0,0x1F,0x1F,0x1F,0x1F,0x1F,
	0,0,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,
	0,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,
	0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F
};
	
void LCD_SetCGRAM(void);

/*HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH*/


//wait 12 clocks
void LCD_WaitUs(BYTE uWait)
{
	while(uWait)
	{
	//	uWait++;
		uWait++;
		uWait++;
	//	uWait--;
		uWait--;
		uWait--;
		uWait--;
	}
}

void LCD_WaitMs(word uWait)
{
	while(uWait)
	{
		uWait++;
		uWait++;
		uWait++;
		uWait++;
		uWait++;
		uWait--;
		uWait--;
		uWait--;
		uWait--;
		uWait--;
		uWait--;
	}
}



//Initilaizes 2 line LCD 
void LCD_Init(void)
{
	//power up
	HALCtrlLCDON();
	
	//wait 50ms
	LCD_WaitMs(c50ms);
	//LCD
	HALCtrlLCDFSet8();
	//wait 10ms
	LCD_WaitMs(c10ms);
	
	HALCtrlLCDFSet8();
	//wait 10ms
	LCD_WaitMs(c10ms);
	
	//wait 10ms
	HALCtrlLCDFSet8();
		
	//wait 10ms
	LCD_WaitMs(c10ms);
	
	HALCtrlLCDFSet4()
		
	LCD_WaitMs(c2ms);
	
	HALCtrlLCDFSet42()
		
	LCD_WaitMs(c2ms);
		
	HALCtrlLCDStop()
	
	LCD_WaitMs(c2ms);
		
	HALCtrlLCDStart();
	
	LCD_WaitMs(c2ms);
	
	HALCtrlLCDEMS()
	
	LCD_WaitMs(c2ms);
	
	HALCtrlLCDEMS()
	
	LCD_WaitMs(c2ms);

	//HALCtrlLCDL1();
	
	LCD_SetCGRAM();
	
	LCD_ClearLine();
	
	LCD_SendLineToLCD(1);
	LCD_SendLineToLCD(2);
}




/*HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH*/
void LCD_SendLineToLCD(BYTE uLineNb)
{
	if (uLineNb & 1)
	{
		HALCtrlLCDL2();
	}
	else
	{
		HALCtrlLCDL1();
	}

	LCD_WaitUs(c50uS);

	for (uLineNb=0; uLineNb<16; uLineNb++)
	{
		HALWriteLCD(uLine[uLineNb]);
		LCD_WaitUs(c50uS);
	} 
}



/*HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH*/
void LCD_ClearLine(void)
{
	BYTE uIndex;
	for (uIndex = 0; uIndex<16; uIndex++)
	{
		uLine[uIndex] = ' ';
	}
}

/*HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH*/
void LCD_SetCGRAM(void)
{
	BYTE uIndex;
	
	LCD_WaitUs(c50uS);
	HALCtrlLCDCGRAM();
	LCD_WaitUs(c50uS);
	
	for ( uIndex = 0; uIndex < 64; uIndex++ )
	{
		LCD_WaitUs(c50uS);
		HALWriteLCD(CGRAM[uIndex]);
		LCD_WaitUs(c50uS);
	}	
}	