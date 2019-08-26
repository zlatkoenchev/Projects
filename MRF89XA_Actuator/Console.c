/*********************************************************************
 *
 *                  Console specific Functions
 *
 *********************************************************************
 * FileName:        Console.c
 * Dependencies:    None
 * Processor:       PIC18/PIC24
 * Complier:        MCC18 v1.00.50 or higher, C30 3.10 or higher
 *                  HITECH PICC-18 V8.10PL1 or higher
 * Company:         Microchip Technology, Inc.
 *
 * Software License Agreement
 *
 * The software supplied herewith by Microchip Technology Incorporated
 * (the “Company”) for its PICmicro® Microcontroller is intended and
 * supplied to you, the Company’s customer, for use solely and
 * exclusively on Microchip PICmicro Microcontroller products. The
 * software is owned by the Company and/or its supplier, and is
 * protected under applicable copyright laws. All rights are reserved.
 * Any use in violation of the foregoing restrictions may subject the
 * user to criminal sanctions under applicable laws, as well as to
 * civil liability for the breach of the terms and conditions of this
 * license.
 *
 * THIS SOFTWARE IS PROVIDED IN AN “AS IS” CONDITION. NO WARRANTIES,
 * WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED
 * TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 * PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. THE COMPANY SHALL NOT,
 * IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL OR
 * CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 ********************************************************************/
#include "Console.h"
#include "GenericTypeDefs.h"
#include "RadioDriverDefs.h"
#include "compiler.h"

/************************ VARIABLES ********************************/
    ROM unsigned char CharacterArray[]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
#if defined(__18F87J11)    
//case for PIC18 processors.............

    #define USART_USE_BRGH_HIGH
    #if defined(USART_USE_BRGH_LOW)
        #define SPBRG_VAL   ( ((CLOCK_FREQ/BAUD_RATE)/64) - 1)
    #else
        #define SPBRG_VAL   ( ((CLOCK_FREQ/BAUD_RATE)/16) - 1)
    #endif
        
    void ConsoleInit(void)
    {
		TRISC7 = 1;
		TRISC6 = 0;
    #if defined(USART_USE_BRGH_HIGH)
        TXSTA = 0x24;
    #else
        TXSTA = 0x20;
    #endif
        RCSTA = 0x90; // 0b10010000;
        BRGL = SPBRG_VAL;
	#if defined (__18F87J11)
		BRG16 = 0;
	#endif
    }
    
    void ConsolePutROMString(ROM char* str)
    {
        BYTE c;
    
        while( c = *str++ )
            ConsolePut(c);
        
    }
    
   
    void ConsolePut(BYTE c)
    {
    if(c == 19)
		ConsolePutROMString((ROM char *)"(Ctrl + S)");
		//System Status
	else if(c == 18)
		ConsolePutROMString((ROM char *)"(Ctrl + R)");
		//Receive Mode - Default Receive Mode (Verbose)
	else if(c == 20)
		ConsolePutROMString((ROM char *)"(Ctrl + T)");
		//Transmit Precoded Packet continuously
	else if(c == 24)
		ConsolePutROMString((ROM char *)"(Ctrl + X)");
		//Reset MRF49XA
	else if(c == 26)
		ConsolePutROMString((ROM char *)"(Ctrl + Z)");
		//Exit + MainMenu
	else
		{
        while( !ConsoleIsPutReady() );
        TXREG = c;
		}
    }
    
    BYTE ConsoleGet(void)
    {
        // Clear overrun error if it has occured
        // New bytes cannot be received if the error occurs and isn't cleared
        if(OERR)
        {
            CREN = 0;   // Disable UART receiver
            CREN = 1;   // Enable UART receiver
        }
    
        return RCREG;
    }
	
    void PrintChar(BYTE toPrint)
    {
        BYTE PRINT_VAR;
        PRINT_VAR = toPrint;
        toPrint = (toPrint>>4)&0x0F;
        ConsolePut(CharacterArray[toPrint]);
        toPrint = (PRINT_VAR)&0x0F;
        ConsolePut(CharacterArray[toPrint]);
        return;
    }

#else

    /************************ FUNCTIONS ********************************/
    
    /*********************************************************************
    * Function:         void ConsoleInit(void)
    *
    * PreCondition:     none
    *
    * Input:		    none
    *
    * Output:		    none
    *
    * Side Effects:	    UART2 is configured
    *
    * Overview:		    This function will configure the UART for use at 
    *                   in 8 bits, 1 stop, no flowcontrol mode
    *
    * Note:			    None
    ********************************************************************/
    void ConsoleInit(void)
    {

            U2BRG   = (CLOCK_FREQ/2/16)/BAUD_RATE-1;
				//program the baud rate
            IFS1bits.U2RXIF = 0;
				//reset the UART 2 Receive interrupt
		//	Temp = U2RXREG;
            U2STA  = 0;
				//Reset the UART 2 status bits
            U2MODE = 0b0000000010000000;
				//Set the bit UEN1 and UEN0 to value '01'
            U2MODEbits.UARTEN = 1;
				//set UARTEN to 1
            U2STAbits.UTXEN = 1;
				//set UTXEN bit in UART Status register
    }
    
    /*********************************************************************
    * Function:         void ConsolePutROMString(ROM char* str)
    *
    * PreCondition:     none
    *
    * Input:		    str - ROM string that needs to be printed
    *
    * Output:		    none
    *
    * Side Effects:	    str is printed to the console
    *
    * Overview:		    This function will print the inputed ROM string
    *
    * Note:			    Do not power down the microcontroller until 
    *                   the transmission is complete or the last 
    *                   transmission of the string can be corrupted.  
    ********************************************************************/
    void ConsolePutROMString(ROM char* str)
    {
        BYTE c;
    
        while( (c = *str++) )
        {
            ConsolePut(c); 
			//put character by character on screen (transmit using usart)
        }
    }
    
    /*********************************************************************
    * Function:         void ConsolePut(BYTE c)
    *
    * PreCondition:     none
    *
    * Input:		    c - character to be printed
    *
    * Output:		    none
    *
    * Side Effects:	    c is printed to the console
    *
    * Overview:		    This function will print the inputed character
    *
    * Note:			    Do not power down the microcontroller until 
    *                   the transmission is complete or the last 
    *                   transmission of the string can be corrupted.  
    ********************************************************************/
    void ConsolePut(BYTE c)
    {
			//Read from the console the byte/string that is entered
    if(c == 19)
		ConsolePutROMString((ROM char *)"(Ctrl + S)");
		//System Status
	else if(c == 18)
		ConsolePutROMString((ROM char *)"(Ctrl + R)");
		//Receive Mode - Default Receive Mode (Verbose)
	else if(c == 20)
		ConsolePutROMString((ROM char *)"(Ctrl + T)");
		//Transmit Precoded Packet continuously
	else if(c == 24)
		ConsolePutROMString((ROM char *)"(Ctrl + X)");
		//Reset MRF24J40
	else if(c == 26)
		ConsolePutROMString((ROM char *)"(Ctrl + Z)");
		//Exit + MainMenu
	else
		{
        while(U2STAbits.TRMT == 0);
			//wait until previous transmission is complete or done
        U2TXREG = c;
			//write the data byte to lower byte of TXREG
		}
    }
    
    /*********************************************************************
    * Function:         void PrintChar(BYTE toPrint)
    *
    * PreCondition:     none
    *
    * Input:		    toPrint - character to be printed
    *
    * Output:		    none
    *
    * Side Effects:	    toPrint is printed to the console
    *
    * Overview:		    This function will print the inputed BYTE to 
    *                   the console in hexidecimal form
    *
    * Note:			    Do not power down the microcontroller until 
    *                   the transmission is complete or the last 
    *                   transmission of the string can be corrupted.  
    ********************************************************************/
    void PrintChar(BYTE toPrint)
    {
        BYTE PRINT_VAR;
        PRINT_VAR = toPrint;
        toPrint = (toPrint>>4)&0x0F;
        ConsolePut(CharacterArray[toPrint]);
        toPrint = (PRINT_VAR)&0x0F;
        ConsolePut(CharacterArray[toPrint]);
        return;
    }

    BYTE ConsoleGet(void)
	{
    	char Temp;

	    while(IFS1bits.U2RXIF == 0);
    	Temp = U2RXREG;
		//read the input value in to temp
		IFS1bits.U2RXIF = 0;
		if(U2STAbits.URXDA)
			{
			Temp = U2RXREG;
			return Temp;
			}
		else
    		return Temp;
		//return the value to the calling function
	}

#endif

BYTE ConsoleInput(void)
{
    BYTE in;
    
    while(!ConsoleIsGetReady());
    
    in = ConsoleGet();
    ConsolePut(in);
    return in;
}


void PrintDigit(BYTE toPrint)
{
    BYTE tmp1, tmp2, tmp3;
    
    tmp1 = toPrint / 100 ;
    if( tmp1 == 0 )
    {
//        ConsolePut(' ');
    }
    else
    {
        ConsolePut('0' + tmp1 );
    }
    
    tmp3 = toPrint % 100;
    tmp2 = tmp3 / 10;
    if( tmp2 == 0 && tmp1 == 0 )
    {
//        ConsolePut(' ');
    }
    else
    {
        ConsolePut('0' + tmp2 );
    }
    
    tmp1 = tmp3 % 10;
    ConsolePut('0' + tmp1);
}


void PrintDigitW(WORD toPrint)
{
    BYTE tmp1, tmp2, tmp3, tmp4, tmp5;
    
    tmp1 = toPrint / 10000 ;
    if( tmp1 == 0 )
    {
//        ConsolePut(' ');
    }
    else
    {
        ConsolePut('0' + tmp1 );
    }
    
    toPrint = toPrint % 10000;
    tmp2 = toPrint / 1000;
    if( tmp2 == 0 && tmp1 == 0 )
    {
 //       ConsolePut(' ');
    }
    else
    {
        ConsolePut('0' + tmp2 );
    }
    toPrint = toPrint % 1000;
    tmp3 = toPrint / 100;
    if( tmp3 == 0 && tmp2 == 0 && tmp1 == 0 )
    {
  //      ConsolePut(' ');
    }
    else
    {
        ConsolePut('0' + tmp3 );
    }
    toPrint = toPrint % 100;
    tmp4 = toPrint / 10;
    if( tmp4 == 0 && tmp3 == 0 && tmp2 == 0 && tmp1 == 0 )
    {
  //      ConsolePut(' ');
    }
    else
    {
        ConsolePut('0' + tmp4 );
    }

    tmp5 = toPrint % 10;
    ConsolePut('0' + tmp5);
}


