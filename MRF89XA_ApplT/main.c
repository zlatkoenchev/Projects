/*
 * File:   main.c
 * Author: zlatko
 *
 * Created on January 28, 2018, 11:11 AM
 */

#include "types.h"
#include "svc_comm.h"
#include "MRF89XA.h"
#include "drv_lcd.h"
#include "drv_I2c.h"
#include "drv_DS3231.h"
#include "drv_io.h"
#include "app_RTC.h"
#include "app_ProgTemp.h"
#include "svc_nvm.h"
#include "app_TempReg.h"
#include "app_Menu.h"
#include "app_Presence.h"
#include "drv_spi_hf.h"
#include "drv_air_sens.h"
#include "drv_Si7021.h"
#include "app_win_sens.h"

/*
 int oscillator on 2MHz
 */
#ifdef DEBUG

// CONFIG1
#pragma config FOSC = INTOSC    // Oscillator Selection (INTOSC oscillator: I/O function on CLKIN pin)
#pragma config WDTE = OFF       // Watchdog Timer Enable (WDT disabled)
#pragma config PWRTE = OFF       // Power-up Timer Enable (PWRT enabled)
#pragma config MCLRE = ON       // MCLR Pin Function Select (MCLR/VPP pin function is MCLR)
#pragma config CP = OFF         // Flash Program Memory Code Protection (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Memory Code Protection (Data memory code protection is disabled)
#pragma config BOREN = ON       // Brown-out Reset Enable (Brown-out Reset enabled)
#pragma config CLKOUTEN = OFF   // Clock Out Enable (CLKOUT function is disabled. I/O or oscillator function on the CLKOUT pin)
#pragma config IESO = OFF       // Internal/External Switchover (Internal/External Switchover mode is disabled)
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enable (Fail-Safe Clock Monitor is enabled)

// CONFIG2
#pragma config WRT = OFF        // Flash Memory Self-Write Protection (Write protection off)
#pragma config PLLEN = OFF      // PLL Enable (4x PLL enabled)
#pragma config STVREN = ON      // Stack Overflow/Underflow Reset Enable (Stack Overflow or Underflow will cause a Reset)
#pragma config BORV = HI        // Brown-out Reset Voltage Selection (Brown-out Reset Voltage (Vbor), high trip point selected.)
#pragma config LVP = ON         // Low-Voltage Programming Enable (Low-voltage programming enabled)
#endif 

uint16 u16Tics;
uint16 u16Reset;
#define RESET_FLAG 0xA55A
#define ONE_SECCNT 49
#define ONE_MINCNT 59

static void Clock_Init(void) {
    u16Tics =20000;
    
    //start on 500khz and wait 2 sec for power stable
    //OSCCONbits.IRCF =0;
    
    while (u16Tics--);
    
    OSCCONbits.IRCF = 12; //2MHz internal clock /500k instr
    u16Tics = 100;
    while (u16Tics--);
    T2CON = 3; //fosc /4*64
    PR2 = 156; //20ms 
    TMR2IF = 0;
    TMR2IE = 0;
    T2CONbits.TMR2ON = 1; 
}

static void Ports_Init(void){   
    APFCON0 = 0x40; // MOSI on RA6
    //PORTA A 
    // RA0 -(TSN) analog IN
    // RA1 - (LRST) out 1
    // RA2 - (SCL) int/out 0
    // RA3 - (SDA) int/out 0
    // RA4 - (HCSD) out 1
    // RA5 - MCLR in
    // RA6 - (MOSI) out 0
    // RA7 - (LCS) out 1
    
    //PORTA B 
    // RB0 -(IRQ1) in
    // RB1 - (MISO) in 
    // RB2 - (C/D) out 0
    // RB3 - (HCSC) out 1
    // RB4 - (SCK) out 0
    // RB5 - (PIR) in
    // RB6 - (PGC) in
    // RB7 - (PGD) in
    
    ANSELA = 0x01; //RA0 only analog
    ANSELB = 0x00; //no analog on this port
    
    TRISB = 0b11100011;
    TRISA = 0b00101101;
    
    
    OPTION_REG = 0x48; //pull enable, INT rising edge, TMR0 - fosc
    
    LATA  = 0b10010010;
    LATB  = 0b00001000; 
        
    WPUB = 0xC0;//RB6 & RB7 switches pullups
}

void RequestReset(void){
   u16Reset = RESET_FLAG; 
}

int main(void) {
    uint8 taskslot;
    uint8 task1sec;
    
    //HAL init
    Ports_Init();
    Clock_Init();
    I2C_Init();
    SPI_HF_Init();
    IO_Init();
    
    //drv Init
    LCD_Init();
    //svc init
    NVM_Init();
    Comm_Init();
        
    //appl init
    AirS_Init();
    RTC_Init();
    PRG_Init();
    REG_Init();
    PRS_Init();
    MNU_Init();
    WIN_Init();
    
    u16Reset = 0;
    task1sec = ONE_SECCNT;
   
    while (TRUE)
    {
        Comm_OnIdle();
        
        //20ms app scheduler
        if (TMR2IF)
        {
           TMR2IF = 0;
           u16Tics++;
           IO_TaskFast();
           MNU_TaskButton();
           PRS_Task();
           AirS_Task();
           Comm_Task();
           taskslot = ((uint8) u16Tics) & 0x1F;
           
           if (task1sec)   {
               task1sec--; 
           }
           else           {
               task1sec = ONE_SECCNT; 
               PRS_Task1s();
               AirS_Task_Slow();
               Comm_TaskSlow();
               WIN_TaskSlow();
           }
           //every 640ms
           switch (taskslot)
           {
               case 0:
                   RTC_TaskSlow();
                   break;
               case 1:
                   IO_TaskSlow();
                   break;
               case 2:
                    PRG_TaskSlow();
                    break;
               case 3:
                    REG_TaskSlow();
                    break;
               case 4:      
                    NVM_Task();
                    //if after task NVM is idle - no pending requests
                    if ((RESET_FLAG == u16Reset ) && (NVM_IsIdle()))   {
                        asm("RESET"); 
                    }
                    break;
               default:
                   MNU_Task();
                   break;
           }         
        }
    }
}

void interrupt ISR(void) {
    //asm("GOTO 0x484");
}