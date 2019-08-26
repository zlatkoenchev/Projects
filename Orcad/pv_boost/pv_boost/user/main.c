/*********************************************************************
 *
 *                Microchip USB C18 Firmware Version 1.2
 *
 *********************************************************************
 * FileName:        main.c
 * Dependencies:    See INCLUDES section below
 * Processor:       PIC18
 * Compiler:        C18 3.11+
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
 *
 * Author               Date        Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Rawin Rojvanit       11/19/04    Original.
 * Rawin Rojvanit       08/14/07    A few updates; added #if defined
 *									sections to support PIC18F87J50
 *									family devices.
 ********************************************************************/

/*********************************************************************
IMPORTANT NOTE: This code is written to work directly on both the
PICDEM FS USB Demo Board, as well as the PIC18F87J50 FS USB Plug-In
Module board.  The code may also be used with your own hardware
platform, but some modifications will be needed.

By default, the code is configured to work with the PICDEM
FS USB Demo board.  When using this board, nothing needs to be
changed.  If using the PIC18F87J50 FS USB Plug-In Module, make the
following changes:

1.  In MPLAB IDE, click "Configure --> Select Device" and then
	select the PIC18F87J50
2.  From the project window, change the linker script to the 
	18f87j50.lkr file
3.  Open usbcfg.h and uncomment the line that reads,
	"//#define PIC18F87J50_FS_USB_PIM" and then comment the other
	choices.

If using this code for other hardware platforms, follow the above
steps (while selecting the appropriate values), but in step #3,
select the "//#define YOUR_BOARD" section instead.  Then attempt to
build the project.  A number of build errors will deliberately occur,
due to the use of the "#error" compiler directive.  Double click on the
error messages and fill in the missing sections with values appropriate
for your hardware platform.

After programming a device with this code, and allowing it to
enumerate for the first time, Windows will ask for a driver. Upon
receiving this prompt, point Windows to the mchpcdc.inf file in the
\MCHPFSUSB\fw\Cdc\inf\win2k_winxp_winvista32 directory.
**********************************************************************/


/** I N C L U D E S **********************************************************/
#include "hal.h"
#include "types.h"
#include "io_drv.h"
#include "lcd_drv.h"
#include "eep_drv.h"
#include "pwm.h"
#include "mppt.h"
#include "EM.h"
#include "temperature.h" 
#include "menu.h" 
#include "button.h"
#include "stat.h"

/** Configuration ********************************************************/
#pragma config PLLDIV = 2, CPUDIV = OSC1_PLL2, USBDIV = 2, FOSC = HSPLL_HS


 //CPU=48 MHz  Quarz= 8 MHz
#pragma config PWRT   = ON
#pragma config BOR    = ON
#pragma config BORV   = 0         //4.6V
#pragma config VREGEN = OFF    //USB Voltage Regulator Enable:
#pragma config WDT    = OFF   //Watchdog Timer:
#pragma config MCLRE  = ON    //MCLR Enable:
#pragma config PBADEN = OFF   //PORTB<4:0> pins are configured as digital I/O on Reset
#pragma config LVP    = OFF   //Low Voltage ICSP:
#pragma config CCP2MX = ON    // CCP2 input/output is multiplexed with RC1



/** V A R I A B L E S ********************************************************/
#pragma udata


/** P R I V A T E  P R O T O T Y P E S ***************************************/

/** V E C T O R  R E M A P P I N G *******************************************/
extern void _startup (void);        // See c018i.c in your C18 compiler dir
#pragma code _RESET_INTERRUPT_VECTOR = 0x000800
void _reset (void)
{
    _asm goto _startup _endasm
}

static byte divider;

/** D E C L A R A T I O N S **************************************************/
#pragma code
/*****************************************************************************/


void main(void)
{
    byte bEepEn;
     
    IO_Init1();
    LCD_Init();
    But_Init();
    Menu_Init();
    EM_Init();
    IO_Init2();
    MPPT_Init();
    Temp_Init();
    Stat_Init();
    
    bEepEn = 0;
    EM_StorageEn(0x01);//CS section always enabled
    while (1)
	{
		//20ms task cycle
		if (IOGetOSFlag())
		{
			TST1 = 1;
			divider++;
		
			if ((divider & 0x03) == 0)
			{
				MPPT_Task();
			}
			else
			{
				Temp_Task();
			}	
			//every 40ms
			if (divider & 0x01)
			{
				But_Task();	
				Temp_Fan_Task();
				Stat_Task();
			}
			else
			{	
				Menu_Task();
			}
			TST1 = 0;	
		}
		else
		{
			EM_Task();//on idle
		}		
	} 
}
