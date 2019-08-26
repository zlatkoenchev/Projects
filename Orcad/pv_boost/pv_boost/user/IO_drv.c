#include "types.h"
#include "io_drv.h"
#include "mppt.h"
#include "hal.h"
#include "em.h"

#define mSetAndStartADC(ChID) ADCON0 = ChID; ADCON0 |= 0x02   
#define mSetADCCh(ChID) ADCON0 = ChID
#define mStartADC() ADCON0 |= 0x02    

static byte Button1;
static byte Button2;
static byte Buttons;
static byte CurADCCh;
static word OSCntr;
static word MaxOutADC;
static byte OSFlag;
static word ADCVal[Ai_NUM];

const byte Log2ADCCh[Ai_NUM] =
{	 
	 ADC_CS2 ,   
	 ADC_CS1 ,   
	 ADC_U2 ,    
	 ADC_U1 ,    
	 ADC_Temp1 , 
	 ADC_Temp2 , 
	 ADC_Io ,    
	 ADC_Uo 
};	

/** D E C L A R A T I O N S **************************************************/
#pragma code

 
 void IO_Init1(void)
{
	//IO ports
	TRISA = 0xEF; // all analog inputs
	
	PORTB = 0; //all in 0
	TRISB = 0x04; //RB2 input, other outputs
	
	PORTC = 0; //all in 0
	TRISC = 0x30; //RC4 and RC5 inputs, all other outputs
	UCON = 0; //USB disabled
	UCFG = 0x08; //enable RC4/5
	
	PORTD = 0; //all in 0
	TRISD = 0; //RD  outputs
	
	TRISE = 0x07;// all analog inputs
	//ADC
	ADCON1  = 0x06; //AN0..AN8 analog
	ADCON2 = 0x80 | (4<<3) | 6; //RJ, 8TAD acq, Fosc/64
	
	ADCON0 = 0x01;//ADC enabled

	
	for(OSCntr = 0; OSCntr < 200; OSCntr++)
	{
		CurADCCh = 0;
	}
	for(OSCntr = 0; OSCntr < Ai_NUM; OSCntr++)
	{
		ADCVal[OSCntr] = 0;
	}
	
	//delay ADC to stabilize and start conversion
	OSCntr = 0;

	Button1 = 0;
	Button2 = 0;
	Buttons = 0;
	
	//PWM
	PR2     = 0x8F;			// 143 -> 83.3kHz
	CCP1CON = 0x0C;			// PWM-Mode
	CCPR1L  = 0x00;			// 0
	CCP2CON = 0x0C;			// PWM-Mode
	CCPR2L  = 0x00;			// 0
    T2CON   = 0x48;         // Timer2 on PreScaler=1:1, PostScaler 1:10, 12MHz
    T2CONbits.TMR2ON  = 1;     
    PIR1bits.TMR2IF = 0;
    PIE1bits.TMR2IE = 0;
    
    mSetAndStartADC((Log2ADCCh[CurADCCh]));
    //OS timer
    T0CON = 0x42; //8bit, PSA = 1:8
    INTCONbits.TMR0IF = 0;
    INTCONbits.TMR0IE = 1;
    TMR0L = OS_TMR_RELOAD;
    

}	

//set PR2 depending on PWM Period, fc = 12MHz
void IO_Init2(void)
{
	word temp = EM_GetU8(P_PWM_PERIOD);
	dword temp2;
	
	T2CONbits.TMR2ON  = 0; 
	if (temp > 210)
	{
		temp = 210;
	}
	else if (temp < 30)
	{
		temp = 30;
	}		 
	temp *= 12;
	temp /= 10;
	PR2     = (byte)temp;	
	T2CONbits.TMR2ON  = 1;	
	
	temp2 = EM_GetU8(P_MAX_U_OUT);
	temp2 *= 102300UL;
	temp2 /= EM_GetU16(P_VSo);
	MaxOutADC = (word)temp2;
	
	//start timer here
	T0CONbits.TMR0ON = 1;
    RCON &= 0x7F; // no ISR priority
    INTCONbits.GIEL = 1;  
    INTCONbits.GIEH = 1;   //gloabl IE

}	
 
//protected read of ADC 
word IOGetADCF(byte i)
{
	 word res;
	 DI();
	 res = ADCVal[i];
	 EI();
	 return (res>>2); 
} 


byte IOGetBut1(void)
{
	if (Buttons & 0x01 ) 
	{
		return 1;
	}	
	return 0;
}	


byte IOGetBut2(void)
{
	if (Buttons & 0x02 ) 
	{
		return 1;
	}	
	return 0;
}

byte IOGetOSFlag(void)
{
	if (OSFlag)
	{
		OSFlag = 0;
		return 1;
	}
	return 0;	
}

#pragma code /* return to the default code section */
#pragma interrupt high_isr
void high_isr (void)
{
	word res;
	word tmp;
	//100us isr
	if (INTCONbits.TMR0IF)
	{
		//set out channel 
		mSetADCCh(ADC_Uo);
		//read last ADC
	   	res = (word)ADRESH<<8;
	   	res |= ADRESL;
	   	mStartADC();
	   	TMR0L = OS_TMR_RELOAD;
	   	
	   	INTCONbits.TMR0IF = 0;
	   	
	   	//filter value 1/3
	   	tmp = ADCVal[CurADCCh];
	   	ADCVal[CurADCCh] += res;
	   	if (tmp)
	   	{
		   	tmp >>=2;
		   	if (0 == tmp)
		   	{
			   	tmp = 1;
			}
			ADCVal[CurADCCh] -=tmp;	
		}	
	   	
	   	//move to next channel
	   	CurADCCh++;
	   	if (CurADCCh >= Ai_NUM)
	   	{
		   	CurADCCh = 0;
		}	
		
		//handle OS timer
		OSCntr++;
		if (OSCntr >= MAX_OS_CNTR)
		{
			OSCntr = 0;
			OSFlag = 1;
			//handle buttons
			if (0 == BUT1)
			{
				Button1 |= 0x01;
			}
			Button1 &= BUT_DEB_MASK;
			if (Button1 == BUT_DEB_MASK)
			{
				Buttons |= 0x01;
			}
			if (Button1 == 0x00)
			{
				Buttons &= 0xFE;
			}	
			Button1 <<= 1;
			
			if (0 == BUT2)
			{
				Button2 |= 0x01;
			}
			Button2 &= BUT_DEB_MASK;
			if (Button2 == BUT_DEB_MASK)
			{
				Buttons |= 0x02;
			}
			if (Button2 == 0x00)
			{
				Buttons &= 0xFD;
			}	
			Button2 <<= 1;
		}
		
	   	while( ADCON0 & 0x02 );     // Wait for conversion of Uout
	   	mSetADCCh(Log2ADCCh[CurADCCh]);
	   	res = (word)ADRESH<<8;
	   	res |= ADRESL;
	   		   	
	   	if ( res > MaxOutADC )
	   	{
		   	ADCVal[Ai_Uo] = (res<<2);
		   	MMPT_ImmediateStop();
		}
		 	
	   	//start next channel
	   	mStartADC();
	}	
}




/** D E C L A R A T I O N S **************************************************/
//ISR high jump
#pragma code high_vector=0x08
void interrupt_at_high_vector(void)
{
  _asm GOTO high_isr _endasm
}
#pragma code

#pragma interruptlow low_isr
void low_isr(void)
{


}



#pragma code low_vector=0x18
void interrupt_at_low_vector(void)
{
    _asm goto low_isr _endasm
}
#pragma code

	