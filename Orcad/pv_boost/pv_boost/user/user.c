/*********************************************************************
 * FileName:        user.c
 * Dependencies:    See INCLUDES section below
 * Processor:       PIC18
 * Compiler:        C18 2.30.01+
 * Company:         sprut
 * Copyright:       2007-2010 Joerg Bredendiek (sprut)
 *
 *
 ********************************************************************/

/*
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */



//#define	NO_CDC	//MCD
#define	CDC_HEX	// nonsens
//#define	CDC_ASCII


/** I N C L U D E S **********************************************************/
#include <p18cxxx.h>
#include <usart.h>
#include "system\typedefs.h"
#include "system\usb\usb.h"
#include "io_cfg.h"             // I/O pin mapping

#include "delays.h"
//#include "system\interrupt\interrupt.h"
#include "user\user.h"
#include "timers.h"

#include "pwm.h"


#define RX_BUFFER 64
#define MIN_CMD_LEN 3
#define MAX_ANOUT  2850
#define MAX_DC     1023
#define MIN_HI_RANGE_CURRENT 4
#define MAX_LO_RANGE_CURRENT 1000
#define MIN_RANGE_TIME 10
#define CALIB_NUM 12
#define CURRENT_OFFSET_LO  Calib[0]
#define CURRENT_OFFSET_HI  Calib[1]
#define MAX_CURRENT_VAL 2000000
#define SCALE_LO_RANGE  Calib[2]
#define SCALE_HI_RANGE  Calib[3]
#define SCALE_AI(x)     Calib[5+x]
#define UBAT_SCALE      Calib[10]
#define AO_SCALE        Calib[11]

#define FIN_MIN_PER 23
#define FIN_CLC_FREQ 1500000

#define FO_MIN_FRQ  25
#define FO_MAX_FRQ  10000
#define FO_MIN_ON_TIME  30

#define COM_TIMEOUT   500



typedef struct{
	byte bLowRange:1;
	byte bLowRangeAvl:1;
	byte bHiRangeAvl:1;
	byte bFilter:1;
	byte DelayToNext;
	byte DelayToSwitch;
}tCurrentMeas;


typedef struct
{
	byte State;
	byte ON_L;
	byte ON_H;
	byte Per_L;
	byte Per_H;
	byte DC;
	byte Div;
	byte Timeout;
	word Freq;
}tFIN;

typedef struct
{
	byte State;
	byte ON_L;
	byte ON_H;
	byte Per_L;
	byte Per_H;
	byte old_fh;
	byte old_fl;
	byte old_dc;
}tFOUT;

typedef struct
{
	byte bDivider:1;
	byte bNewData:1;
	word PWM1;
	word PWM2;
}tAOUT;	

typedef struct
{
	byte RelN;
	dword ON_Counter;
}tSSR;
/** V A R I A B L E S ********************************************************/
#pragma udata


byte TxLen;
byte RxLen;
byte RxBuff[RX_BUFFER];
byte TxBuff[RX_BUFFER];
word ADCBuff[8];
word ADCScale[7];
word Calib[CALIB_NUM];
dword Current;
static tCurrentMeas sCM;
static tFIN sFIN;
static tFOUT sFO;
static tSSR sSSR;
static tAOUT sAOUT;

#pragma code

/** D E C L A R A T I O N S **************************************************/
//init pheripherals



/** D E C L A R A T I O N S **************************************************/
//set output relays
void SetRelays(byte outs )
{
	if (0==(1 && sSSR.RelN)){
		if (outs & 1) { Rel1 = 1; } else {Rel1 = 0;}
	}
	if (0==(2 && sSSR.RelN)) {
		if (outs & 2) { Rel2 = 1; } else {Rel2 = 0;}
	}
	if (0==(4 && sSSR.RelN)) {
		if (outs & 4) { Rel3 = 1; } else {Rel3 = 0;}
	}
	if (0==(8 && sSSR.RelN)) {
		if (outs & 8) { Rel4 = 1; } else {Rel4 = 0;}
	}
	if (0==(16 && sSSR.RelN)) {
		if (outs & 16) { Rel5 = 1; } else {Rel5 = 0;}
	}
	if (0==(32 && sSSR.RelN)) {
		if (outs & 32) { Rel6 = 1; } else {Rel6 = 0;}
	}
	if (0==(64 && sSSR.RelN)) {
		if (outs & 64) { SSR = 1; } else {SSR = 0;}
	}
}
/** D E C L A R A T I O N S **************************************************/
//set Pulse mode of relays 
void SetPulseMode(void )
{
	
	sSSR.ON_Counter = RxBuff[2];
	sSSR.ON_Counter <<=7;
	sSSR.ON_Counter |= RxBuff[3];
		
	sSSR.ON_Counter *= 3298; //timer2 tick is 329.8us
	sSSR.ON_Counter /= 1000;
	
	sSSR.RelN = 1 << (RxBuff[1] & 0x07);
	
	if (1 & sSSR.RelN)	 {Rel1 = 1;}
	if (2 & sSSR.RelN)	 {Rel2 = 1;}
	if (4 & sSSR.RelN)	 {Rel3 = 1;}
	if (8 & sSSR.RelN)	 {Rel4 = 1;}
	if (16 & sSSR.RelN)	 {Rel5 = 1;}
	if (32 & sSSR.RelN)	 {Rel6 = 1;}
	if (64 & sSSR.RelN)	 {SSR = 1;}		
}
/** D E C L A R A T I O N S **************************************************/
//0.3ms pulse gen task

void SSRFastTask(void)
{
	if (sSSR.ON_Counter)
	{
		sSSR.ON_Counter--;
		if (0 == sSSR.ON_Counter)
		{
			if (1 & sSSR.RelN)	 {Rel1 = 0;}
			if (2 & sSSR.RelN)	 {Rel2 = 0;}
			if (4 & sSSR.RelN)	 {Rel3 = 0;}
			if (8 & sSSR.RelN)	 {Rel4 = 0;}
			if (16 & sSSR.RelN)	 {Rel5 = 0;}
			if (32 & sSSR.RelN)	 {Rel6 = 0;}
			if (64 & sSSR.RelN)	 {SSR = 0;}
			sSSR.RelN  = 0;
		}	
	}	
}
/** D E C L A R A T I O N S **************************************************/
//set current ranges
void SetCurrentRanges(void )
{
	//set current measurement ranges
	if (RxBuff[6] & 0x10)
	{
		sCM.bLowRangeAvl = 1;
	}
	else
	{
		sCM.bLowRangeAvl = 0;
	}	
		
	if (RxBuff[6] & 0x20)
	{
		sCM.bHiRangeAvl = 1;
	}
	else
	{
		sCM.bHiRangeAvl = 0;
		//if case of both ranges disabled - enable hi range!
		if (0 == sCM.bLowRangeAvl)
		{
			sCM.bHiRangeAvl = 1;
		}
	}
	
	if (RxBuff[6] & 0x40)
	{
		sCM.bFilter = 1;
	}
	else
	{
		sCM.bFilter = 0;
	}			
}

/** D E C L A R A T I O N S **************************************************/
//task pwm values
void PWM_Task(void)
{
	dword dwValue;
	if (sAOUT.bNewData)
	{
		sAOUT.bNewData = 0;
	
			if (sAOUT.PWM1 >=MAX_ANOUT)
			{
				sAOUT.PWM1 = MAX_DC;
			}
			else
			{
				dwValue = ((dword)sAOUT.PWM1)*MAX_DC;
				sAOUT.PWM1 = (word)(dwValue/UBAT_SCALE);
			}		
						
			SetDCPWM1(sAOUT.PWM1); 
		
			if (sAOUT.PWM2 >=MAX_ANOUT)
			{
				sAOUT.PWM2 = MAX_DC;
			}
			else
			{
				dwValue = ((dword)sAOUT.PWM2)*MAX_DC;
				sAOUT.PWM2 = (word)(dwValue/AO_SCALE);
			}
			SetDCPWM2(sAOUT.PWM2); 
	}
}	

/** D E C L A R A T I O N S **************************************************/
//set pwm values
void SetPWMs(void )
{	
	sAOUT.PWM1 = RxBuff[2];
	sAOUT.PWM1 <<=7;
	sAOUT.PWM1 |= RxBuff[3];	
				
	sAOUT.PWM2  = RxBuff[4];
	sAOUT.PWM2  <<=7;
	sAOUT.PWM2  |= RxBuff[5];
	
	sAOUT.bNewData = 1;
}
/** D E C L A R A T I O N S **************************************************/
//converts gven channel
word DoADC(byte ChID)
{
	word res;
	ADCON0 = ChID | 0x01;              // Set channel for AD conversion
							//ACQ time is auto done
	ADCON0 |= 0x02 ; //start AD
   	while( ADCON0 & 0x02 );     // Wait for conversion
   	res = (word)ADRESH<<8;
   	res |= ADRESL;
   	return res;
}







/** D E C L A R A T I O N S **************************************************/
//starts measurement of input DC and period
void FINStartMeasure(void)
{
	if (0 == sFIN.State)
	{
		INTCON2bits.INTEDG0 = 1; //rising
		
		sFIN.State = 1; 
		sFIN.Timeout = 2; 
		T0CON = 0x02; //OFF, 16 bit, Presc 1:8, 0.666us resolution-> 22Hz min  
		TMR0H = 0;
		TMR0L = 0;      
		INTCONbits.TMR0IE = 0;  //no TMR0 int
		INTCONbits.TMR0IF = 0;
		INTCONbits.INT0IF = 0;  //clear flag
		INTCONbits.INT0IE = 1; //INT0 IE
		INTCONbits.GIEH = 1;   //gloabl IE
	}
	else
	{
		//after 300ms set Freq to 0 if there is no measurement
		if (sFIN.Timeout)
		{
			sFIN.Timeout--;
			if (0 == sFIN.Timeout)
			{
				sFIN.Freq = 0;
				sFIN.DC = 0;
			}	
		}	
	}	
}	

/** D E C L A R A T I O N S **************************************************/
//set FO mode
void SetFOState(void)
{
	byte nst;
	word wTemp;
	word wTemp2;
	dword dwTemp;
	
	nst = RxBuff[6] & 0x03;
	if (nst == 0)
	{
		PIE1bits.TMR1IE = 0;
		PIE2bits.TMR3IE = 0;
		sFO.old_dc = 0;
		sFO.old_fh = 0;
		sFO.old_fl = 0;
		DOUT = 0;
	}
	else if (nst == 1)
	{
		PIE1bits.TMR1IE = 0;
		PIE2bits.TMR3IE = 0;
		sFO.old_dc = 0;
		sFO.old_fh = 0;
		sFO.old_fl = 0;
		DOUT = 1;
	}
	else {
		if ((sFO.old_fh == RxBuff[7]) && 
		    (sFO.old_fl == RxBuff[8]) && 
		    (sFO.old_dc == RxBuff[9]))
		{
			//do nothing same freq/DC
		}
		else
		{
			sFO.old_fh = RxBuff[7];
			sFO.old_fl = RxBuff[8];	
			sFO.old_dc = RxBuff[9];
			
			wTemp = RxBuff[7];
			wTemp <<=7;
			wTemp |= RxBuff[8];//frequency
			if (wTemp > FO_MAX_FRQ)
			{
				wTemp = FO_MAX_FRQ;
			}	
			else if (wTemp < FO_MIN_FRQ)
			{
				wTemp = FO_MIN_FRQ;
			}
			dwTemp = FIN_CLC_FREQ;
			dwTemp /=wTemp;
			wTemp = (word)dwTemp;
			wTemp -=3;//small correction of period error
			wTemp = ~wTemp;//here is period
			
			if (RxBuff[9]>100)
			{
				RxBuff[9] = 100;//limit DC	
			}	
			
			dwTemp *= RxBuff[9];
			dwTemp /=100;
			wTemp2 = (word)dwTemp;
			if (wTemp2 < FO_MIN_ON_TIME)
			{
				wTemp2 = FO_MIN_ON_TIME;
			}	
			wTemp2 = ~wTemp2;//here is ON time
			
			INTCONbits.GIEH = 0; //DI interrupts during period update in case of freqeuncy running
			INTCONbits.GIEH = 0;
			sFO.Per_L = (byte)wTemp;
			sFO.Per_H = wTemp>>8;
			TMR3H = sFO.Per_H;
			sFO.ON_L = (byte)wTemp2;
			sFO.ON_H = wTemp2>>8;
			TMR1H = sFO.ON_H;
			INTCONbits.GIEH = 1;
			
			if (2 != sFO.State)
			{
				//start frequency only once if not started before for glitch free signal
				IPR1bits.TMR1IP = 0;//low prio
				IPR2bits.TMR3IP = 0;//low prio
				
				T1CON = 0xB0;
				T3CON = 0xB0;
				TMR1H = sFO.ON_H;
				TMR1L = sFO.ON_L;
				TMR3H = sFO.Per_H;
				TMR3L = sFO.Per_L;
				PIR1bits.TMR1IF = 0;
				PIR2bits.TMR3IF = 0;
				PIE1bits.TMR1IE = 1;
				PIE2bits.TMR3IE = 1;
				DOUT = 1;
				T1CONbits.TMR1ON = 1;
				T3CONbits.TMR3ON = 1;
				
				INTCONbits.GIEL = 1;
				INTCONbits.GIEH = 1;
			}
		}	
	}
	sFO.State = nst;		
}	

/** D E C L A R A T I O N S **************************************************/
//check for end of measure
void FINCheckMeasureOnIdle(void)
{
	dword dwTemp;
	word wTemp;
	if ( 0 == sFIN.State ) {return;}	
	if ((sFIN.State > 4 ) || (INTCONbits.TMR0IF))//measurement finished
	{
		INTCONbits.INT0IE = 0; //disable INT0
		if ( sFIN.State > 4 )
		{
			if ((sFIN.Per_L) || (sFIN.Per_H)) //valid period
			{
				wTemp = sFIN.Per_H;
				wTemp <<=8;
				wTemp |= sFIN.Per_L;
				//calc frequency and DC
				if (wTemp > FIN_MIN_PER )
				{
					dwTemp = FIN_CLC_FREQ;
					dwTemp /= wTemp;
					sFIN.Freq = (word)dwTemp;
					
					dwTemp = ((word)sFIN.ON_H)<<8;
					dwTemp |= sFIN.ON_L;
					dwTemp *=100;
					dwTemp /= wTemp;
					sFIN.DC = (byte)dwTemp;
				}
				else
				{
					sFIN.Freq = 0xFFFF;
					sFIN.DC = 0;
				}		
			}
			else
			{
				sFIN.Freq = 0;
				sFIN.DC = 0;
			}		
		}	
		else
		{
			sFIN.Freq = 0; //too long period
			sFIN.DC = 0;
		}
		sFIN.State = 0;	
	}		
}

/** D E C L A R A T I O N S **************************************************/
//Read Calibration
void ReadCalibration(void)
 {
	byte i;
	//read calibration consts
	//Calib[0] = 21;
	//Calib[1] = 21;
	//Calib[2] = 1154;
	//Calib[3] = 2338;
	
	EEADR = 0;
	for (i = 0; i < CALIB_NUM; i++)
	{
		EECON1bits.EEPGD = 0;				/* READ step #1 */
		EECON1bits.CFGS  = 0;
		EECON1bits.RD = 1;					/* READ step #3 */
		ADCBuff[0] = EEDATA;
		ADCBuff[0] <<=8;
		EEADR++;	
		EECON1bits.RD = 1;					/* READ step #3 */
		ADCBuff[0] |= EEDATA;
		EEADR++;
		Calib[i] = ADCBuff[0];
	}
	ADCBuff[0] = 0;
 }

/** D E C L A R A T I O N S **************************************************/
//init 
void UserInit(void)
{
	InitIO();
	RxLen = 0;
	Current = 0;
	sCM.bLowRange = 0;
	sCM.DelayToNext = 0;
	sCM.bLowRangeAvl = 0;
	sCM.bHiRangeAvl = 1;
	Rel7 = 0;
	
	sFIN.State = 0;
	sFIN.Freq = 0;
	sFIN.DC = 0;
	sFIN.Div = 10;
	
	sFO.State = 0;
	sFO.old_dc = 0;
	sFO.old_fh = 0;
	sFO.old_fl = 0;
	
	sSSR.RelN = 0;
	SSR = 0;
	
	
	sAOUT.bDivider=0;
	sAOUT.PWM1 = 0;
	sAOUT.PWM2 = 0;
	sAOUT.bNewData = 0;
	
	ReadCalibration();
	
}	



/** D E C L A R A T I O N S **************************************************/
//verify command lenght and checskum
byte CmdVfy(byte ExpLen)
{
	byte i;
	byte CS = 0;
	
	if (ExpLen <= RxLen)
	{
		for ( i=0; i < ExpLen; i++)
		{
			CS ^= RxBuff[i];	
		}
		
		if (0x80 ==CS)
		{
			return 1;
		}
		else
		{
			//bad CS, buffer needs to be flushed
			return 2; 
		}		
	}	
	return 0;//wait for more bytes
}

//todo add current averaging due to peak consumption
//fileter to be on/off

	
/** D E C L A R A T I O N S **************************************************/
//process received commands
void ServiceRequests(void)
{
    byte index;
    byte CS;
    byte MaxBytes;
	word wValue;
	dword dwValue;
	
    // read some bytes
    MaxBytes = RX_BUFFER - RxLen;
    index = getsUSBUSART((char*)&RxBuff[RxLen],MaxBytes);
    if (0 == index)
    {
		//no data
		return;    
	}
	
	RxLen += index; 
	//search for command start in buffer
	MaxBytes = RX_BUFFER;
	for (index = 0; index < RxLen; index++)
	{
		if (RxBuff[index] & 0x80 )
		{
			//command start found
			MaxBytes = index;
			break;
		}
	}
		
	//no command found, flush buffer	
	if (MaxBytes == RX_BUFFER)
	{
		RxLen = 0;
		return;
	}
	
	//command found! copy data to the first byte of the buffer if not aligned already
	if (0 != MaxBytes)
	{
		RxLen -= MaxBytes;
		for (index = 0; index < RxLen ; index++)
		{
			RxBuff[index] = RxBuff[index + MaxBytes];
		}
	}
	TxLen = 0;

	//process command aligned to the first byte
	switch(RxBuff[0]) 	
    {
		case 0x8A://control outputs
			MaxBytes = 11;// cmd len including checksum
			index = CmdVfy(MaxBytes);
			if (1 == index) //valid command
			{
				//refresh IO
				SetRelays(RxBuff[1]);
				SetPWMs();
				SetCurrentRanges();	
				SetFOState();

				//return response	
				TxBuff[0] = 0x8B;
			
				TxBuff[1] = (ADCScale[0] >>7) & 0x7F;
				TxBuff[2] = (byte)ADCScale[0] & 0x7F ;
				
				
				TxBuff[3] = (ADCScale[1] >>7) & 0x7F;
				TxBuff[4] = (byte)ADCScale[1] & 0x7F ;
				
			
				TxBuff[5] = (ADCScale[2] >>7) & 0x7F;
				TxBuff[6] = (byte)ADCScale[2] & 0x7F;
				

				TxBuff[7] = (ADCScale[3] >>7) & 0x7F;
				TxBuff[8] = (byte)ADCScale[3] & 0x7F;
				

				TxBuff[9] = (ADCScale[4] >>7) & 0x7F;
				TxBuff[10] = (byte)ADCScale[4] & 0x7F;
				

				TxBuff[11] = (ADCScale[5] >>7)& 0x7F ;
				TxBuff[12] = (byte)ADCScale[5] & 0x7F;
				
				TxBuff[13] = ((byte)(sFIN.Freq>>14))& 0x7F;
				TxBuff[14] = ((byte)(sFIN.Freq>>7)) & 0x7F ;//Fin
				TxBuff[15] = sFIN.Freq & 0x7F;
				TxBuff[16] = sFIN.DC & 0x7F;
				TxBuff[17] = ((byte)(Current>>14)) & 0x7F;
				TxBuff[18] = ((byte)(Current>>7))& 0x7F ;
				TxBuff[19] = ((byte)Current )& 0x7F;
				TxLen = 20;
			}		
	   		break;
		
		case 0x8C://Write EEDATA
			MaxBytes = 5;// cmd len
			index = CmdVfy(MaxBytes);
			
			if (1 ==  index) //valid command
			{
				wValue = RxBuff[2];
				wValue <<=7;
				wValue |= RxBuff[3];
			
				PIR2bits.EEIF = 0;
				EECON1bits.EEPGD = 0;				/* WRITE step #1 */
				EECON1bits.CFGS  = 0;
				EECON1bits.WREN = 1;				/* WRITE step #2 */
				EEADR = RxBuff[1] & 0xFE;		/* WRITE step #3 */
				INTCONbits.GIEH = 0; 
				EEDATA = wValue>>8;		/* WRITE step #4 */
				EECON2 = 0x55;						/* WRITE step #5 */
				EECON2 = 0xaa;						/* WRITE step #6 */
				EECON1bits.WR = 1;					/* WRITE step #7 */
				INTCONbits.GIEH = 1; 
				while (!PIR2bits.EEIF);				/* WRITE step #8 */
				PIR2bits.EEIF = 0;					/* WRITE step #9 */
				
				EEADR++;		/* WRITE step #3 */
				EEDATA = (byte)wValue;		/* WRITE step #4 */
				INTCONbits.GIEH = 0; 
				EECON2 = 0x55;						/* WRITE step #5 */
				EECON2 = 0xaa;						/* WRITE step #6 */
				EECON1bits.WR = 1;					/* WRITE step #7 */
				INTCONbits.GIEH = 1;
				while (!PIR2bits.EEIF);				/* WRITE step #8 */
				PIR2bits.EEIF = 0;	
				ReadCalibration();
			}	
		break;
			
		case 0x8E://Read EEDATA
			MaxBytes = 3;// cmd len
			index = CmdVfy(MaxBytes);
			
			if (1 == index) //valid command
			{
				EEADR = RxBuff[1] & 0xFE;
				EECON1bits.EEPGD = 0;				/* READ step #1 */
				EECON1bits.CFGS  = 0;
				EECON1bits.RD = 1;					/* READ step #3 */
				wValue = EEDATA;
				wValue <<=8;
				EEADR++;	
				EECON1bits.RD = 1;					/* READ step #3 */
				wValue |= EEDATA;
				TxBuff[0] = 0x8F;
				TxBuff[1] = RxBuff[1]& 0x7F;
				TxBuff[2] = (wValue >>7)& 0x7F ;
				TxBuff[3] = (wValue)& 0x7F ;
				TxLen = 4;
			}
		break;		
                 
        case 0x90:
        	MaxBytes = 5;// cmd len
			index = CmdVfy(MaxBytes);
			if (1 == index) //valid command
			{
				SetPulseMode();
			}	
        break;
        
        case 0x92:
        	MaxBytes = 2;// cmd len
			index = CmdVfy(MaxBytes);
			if (1 == index) //valid command
			{
				TxBuff[0] = 0x93;
				TxBuff[1] = (ADCBuff[0]>>7) & 0x7F;
				TxBuff[2] = (ADCBuff[0] )& 0x7F;
				TxBuff[3] = (ADCBuff[1]>>7)& 0x7F;
				TxBuff[4] = (ADCBuff[1] )& 0x7F;
				TxBuff[5] = (ADCBuff[2]>>7)& 0x7F;
				TxBuff[6] = (ADCBuff[2] )& 0x7F;
				TxBuff[7] = (ADCBuff[3]>>7)& 0x7F;
				TxBuff[8] = (ADCBuff[3] )& 0x7F;
				TxBuff[9] = (ADCBuff[4]>>7)& 0x7F;
				TxBuff[10] = (ADCBuff[4] )& 0x7F;
				TxBuff[11] = (ADCBuff[5]>>7)& 0x7F;
				TxBuff[12] = (ADCBuff[5] )& 0x7F;
				TxBuff[13] = (ADCBuff[6]>>7)& 0x7F;
				TxBuff[14] = (ADCBuff[6] )& 0x7F;
				TxLen = 15;
			}	
        break;
                 
        case 0xFF://reset
                //When resetting, make sure to drop the device off the bus
                //for a period of time. Helps when the device is suspended.
                UCONbits.USBEN = 0;
                wValue = 0;		//word = 16 Bit
                while(--wValue);
                while(--wValue);
                while(--wValue);
                Reset();
         	break;
                
         default:
				index = 2;
				MaxBytes = MIN_CMD_LEN;
         	break;
     }
		
	//check command status and if there is a need to flush the buffer
	if (index != 0 )
	{
		RxLen -= MaxBytes;
		for (index = 0; index < RxLen ; index++)
		{
			RxBuff[index] = RxBuff[index+MaxBytes];
		}
	}	
		
	//response to transmit?
	if(TxLen != 0)
	{
		CS = TxBuff[0];//checksum
		for (index = 1; index < TxLen ; index++)
		{
			
			CS ^=TxBuff[index];
		}
		
		TxBuff[TxLen]= CS & 0x7F;
		TxLen++;	
		mUSBUSARTTxRam((byte*)&TxBuff,TxLen);	
	}
}

	
/** D E C L A R A T I O N S **************************************************/
//on IDLE measure inputs	
void InputADCTaskIdle(void)
{
	word wTemp;
	ADCBuff[0] = DoADC(ADC_1);
	ADCBuff[1] = DoADC(ADC_2);
	ADCBuff[2] = DoADC(ADC_3);
	ADCBuff[3] = DoADC(ADC_4);
	ADCBuff[4] = DoADC(ADC_5);
	ADCBuff[5] = DoADC(ADC_6);
	 
	if (sCM.bFilter)
	{
		ADCBuff[7] = DoADC(ADC_7);
		if (ADCBuff[7] > ADCBuff[6])
		{
			
			ADCBuff[6]++;	
		}
		else if (ADCBuff[7]< ADCBuff[6])
		{
			
			ADCBuff[6]--;
		}		
	}
	else	
	{ 
	 	ADCBuff[6] = DoADC(ADC_7);
	} 
}	


/** D E C L A R A T I O N S **************************************************/
//current process task on 10ms
void InputTask(void)
{

	//every 100ms measure frequency
	if (0!= sFIN.Div)
	{
		sFIN.Div--;
	}
	else
	{	
		FINStartMeasure();
		sFIN.Div = 9;
	}
	//process current measure	
	if (0 != sCM.DelayToNext)
	{
		sCM.DelayToNext--;
	}
	else
	{
		//we are in low range
		if (sCM.bLowRange)
		{
			if (ADCBuff[6] > (CURRENT_OFFSET_LO+1))
			{
				ADCBuff[6] -= CURRENT_OFFSET_LO;
			}	
			else
			{
				ADCBuff[6] = 0;
			}	
			
			if (ADCBuff[6] > MAX_LO_RANGE_CURRENT)
			{
				if (sCM.DelayToSwitch)
				{
					sCM.DelayToSwitch--;
				}
				else
				{	
					if (sCM.bHiRangeAvl)
					{
						sCM.bLowRange = 0;
						Rel7 = 0;
						sCM.DelayToNext = 3;//wait time to switch relays
					}
				}
			}
			else
			{
				sCM.DelayToSwitch = MIN_RANGE_TIME;
				
				//valid current, do calculation
				Current = ADCBuff[6]; 
				Current *= SCALE_LO_RANGE;
				Current /= 100; 
			}
			//if this range is disabled
			if (0 == sCM.bLowRangeAvl)
			{
				sCM.bLowRange = 0;//hi should be enabled
				Rel7 = 0;
				sCM.DelayToNext = 3;//wait time to switch relays
			}					
		}
		else
		{
			if (ADCBuff[6] > (CURRENT_OFFSET_HI+1))
			{
				ADCBuff[6] -= CURRENT_OFFSET_HI;
			}	
			else
			{
				ADCBuff[6] = 0;
			}	
			
			if (ADCBuff[6] > MIN_HI_RANGE_CURRENT)
			{
				//high current , stay in this range for min time
				sCM.DelayToSwitch = MIN_RANGE_TIME;
			}
			else if( 0 == sCM.DelayToSwitch )
			{
				//if low range enabled - switch to it!
				if (sCM.bLowRangeAvl)
				{
					sCM.bLowRange = 1;
					Rel7 = 1;   //power relay
					sCM.DelayToNext = 3;//wait time to switch relays
				}	
			}
			else 
			{
				sCM.DelayToSwitch--;
			}
			Current = ADCBuff[6]; 
			Current *= SCALE_HI_RANGE;
			//Current /= 10; 
			//limit to 21 bit result
			if (Current > MAX_CURRENT_VAL)
			{
				Current = MAX_CURRENT_VAL; 
			}
			//if this range is disabled
			if (0 == sCM.bHiRangeAvl)
			{
				sCM.bLowRange = 1;//low should be enabled
				Rel7 = 1;
				sCM.DelayToNext = 3;//wait time to switch relays
			}				
		}		
	}		
}
	






/** D E C L A R A T I O N S **************************************************/
//Rx check 
void ProcessRx(void)
{   
    // User Application USB tasks
    if((usb_device_state < CONFIGURED_STATE)||(UCONbits.SUSPND==1)) return;
    //Check if no response TX in progress
    if(!mUSBUSARTIsTxTrfReady()) return;
    ServiceRequests();
}

/** D E C L A R A T I O N S **************************************************/
//ADCscale 
void TaskADCScale(void)
{
	dword dwValue;
	 
	dwValue = ((dword)ADCBuff[0])*SCALE_AI(0);
	ADCScale[0] = dwValue >> 10;
	
	dwValue = ((dword)ADCBuff[1])*SCALE_AI(1);
	ADCScale[1] = dwValue >> 10;
	
	dwValue = ((dword)ADCBuff[2])*SCALE_AI(2);
	ADCScale[2] = dwValue >> 10;
	
	dwValue = ((dword)ADCBuff[3])*SCALE_AI(3);
	ADCScale[3] = dwValue >> 10;
	
	dwValue = ((dword)ADCBuff[4])*SCALE_AI(4);
	ADCScale[4] = dwValue >> 10;
	
	dwValue = ((dword)ADCBuff[5])*SCALE_AI(5);
	ADCScale[5] = dwValue >> 10;
}	

/** D E C L A R A T I O N S **************************************************/
#pragma code /* return to the default code section */
#pragma interrupt high_isr
void high_isr (void)
{
  	if (sFIN.State & 1)
  	{
	  	T0CONbits.TMR0ON = 0x01;//start T0
	  	INTCON2bits.INTEDG0 = 0;//falling
	  	INTCONbits.TMR0IF = 0;//clear timer Overflow flag
	  	INTCONbits.INT0IF = 0;//clear IF
	}
	else if (sFIN.State & 2)
	{
		sFIN.ON_L = TMR0L;
		sFIN.ON_H = TMR0H;
		INTCON2bits.INTEDG0 = 1;//rising
		INTCONbits.INT0IF = 0;//clear IF
	}
	else
	{
		sFIN.Per_L = TMR0L;
		sFIN.Per_H = TMR0H;
		if (INTCONbits.TMR0IF) //timer overflow?
		{
			sFIN.Per_L = 0;
			sFIN.Per_H = 0;
		}	
		INTCONbits.INT0IE = 0;
		INTCONbits.INT0IF = 0;//clear IF   
	}			
	sFIN.State <<=1;
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
	if (PIR1bits.TMR1IF)
	{
		DOUT = 0;
		T1CONbits.TMR1ON = 0;//stop to avoid false IT	
		TMR1L = sFO.ON_L;//reloads also high
		PIR1bits.TMR1IF = 0;
	}
	if (PIR2bits.TMR3IF)
	{
		TMR3L = sFO.Per_L;//reloads also high
		DOUT = 1;
		//PIR1bits.TMR1IF = 0;
		T1CONbits.TMR1ON = 1;	
		PIR2bits.TMR3IF = 0;
	}		
}



#pragma code low_vector=0x18
void interrupt_at_low_vector(void)
{
    _asm goto low_isr _endasm
}
#pragma code


/** EOF user.c ***************************************************************/
