#include "types.h"
#include "hal.h"
#include "main.h"
#include "appl.h"
#include "htc.h"
#include "ram.h"
//#include <xc.h>
//#pragma config WDTE=ON, FOSC=HS, CPD=OFF, CP = OFF, PWRTE = ON, LVP = OFF, BOREN = OFF, DEBUG = OFF
__CONFIG(WDTEN & HS & PWRTEN & BOREN & LVPDIS & WRTEN);


#define T2_POSTSCALER(x) ((x-1)<<3)
#define T2_PRESCALER_4    0x01
#define T2_PRESCALER_1    0x00




void HALCtrlCpuInit(void)
{
	di();
	di();
	
	
	HALFlags.b1msSlot = 0;
	HALFlags.u8Cntr = 0;

	TRISA = 0x07;
	TRISB = 0xC7;
	TRISC = 0x1F;
	TRISD = 0x00;
	TRISE = 0x00;

	PORTA = 0x00;
	PORTB = 0x00;
	PORTC = 0x00;
	PORTD = 0x00;
	PORTE = 0x00;

	OPTION = 0x7D; //enable port B pullups, PSA assigned to WDG, PRSC = 1:32, typ 630ms
		
	INTCON = 0;
	
	//ADC
	ADCON1 = 0x82; //left justifyed result, 
	ADCON0 = ADC_FOSC; //fosc/32
	ADON = 1;//start ADC
	
	//Set TMR2 for OS 1 ms slot, Fosc=20MHz, interrupt
	//20 000 000 / (4*1*10*(PR2+1)) = 2000Hz
	T2CON = T2_POSTSCALER(10)+ T2_PRESCALER_1;
	PR2 = 249;
	TMR2IE = 1;
	TMR2ON  = 1;
	TMR2IF = 0;
	PEIE   = 1;//T2 int is enabled here	
	CLRWDT();
}

	

void interrupt IQR(void)
{
	if ( TMR2IF)
	{
		
	}
}










