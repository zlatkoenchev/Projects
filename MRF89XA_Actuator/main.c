/*
 * File:   main.c
 * Author: zlatko
 *
 * Created on January 28, 2018, 11:11 AM
 */

#include "types.h"
#include "svc_comm.h"
#include "MRF89XA.h"
#include "drv_io.h"
#include "svc_nvm.h"
#include "app_control.h"
#include "drv_relay.h"
#include "drv_spi_hf.h"
#include "drv_I2c.h"
#include "app_Presence.h"
#include "app_prog.h"
#include "app_RTC.h"
#include "svc_uds.h"
#include "drv_tvalve.h"
#include "runtime.h"
#include "svc_nm.h"
#include "drv_Si7021.h"
#include "svc_nm.h"
#include "DS18B20.h"

/*
 int oscillator on 2MHz
 */
#ifdef DEBUG

// CONFIG1
#pragma config FOSC = INTOSC    // Oscillator Selection (INTOSC oscillator: I/O function on CLKIN pin)
#pragma config WDTE = OFF       //SWDTEN  Watchdog Timer Enable (WDT disabled)
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
uint16 u16IdleTicks;

#define RESET_FLAG 0xA55A
#define ONESEC_CTR 49 
#define ONEMIN_CTR 59 

static void Clock_Init(void) {
    
    INTCON = 0;
    PIE1 = 0;
    PIE2 = 0;
    u16Tics = 20000;
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
    // RA0 - out 0
    // RA1 - ZCROSS in
    // RA2 - Rel off
    // RA3 - Rel on
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
    // RB7 - (PGD) in PIR

    LATA = 0b10010000;
    LATB = 0b00001000; 
    
    ANSELA = 0x02; //RA1 only analog comparator input
    ANSELB = 0x00; //no analog on this port
    
    TRISB = 0b11100011;
    TRISA = 0b00100010;
   
    OPTION_REG = 0x47; //pull enable, INT rising edge, TMR0 - prescaller 256
    
   
    
    WPUB = 0xE1; //RB5 , RB6, RB7, IRQ1  switches pullups,  
}

void RequestReset(void){
   Rel_Request(0); //request off first
   u16Reset = RESET_FLAG; 
   NVM_WriteBlock(NVM_RUNTIME);
}

int main(void) {
    uint8 taskslot;
    uint8 task1sek;
   
    //HAL init
    Ports_Init();
    Clock_Init();
   
    SPI_HF_Init();
    I2C_Init();
    
    //svc init
    NVM_Init();
    
    Si7021_Init();
    
    DS18B20_Init();
    
    IO_Init(); 
    Comm_Init();
 
    UDS_Init();
        
    //appl init
    Rel_Init();
    CTRL_Init();
    PRS_Init();
    PRG_Init();
    RTC_Init();
    Rnt_Init();
        
    u16Reset = 0;
    u8ZCnumber = 0;
    task1sek = ONESEC_CTR;
    
    ENABLE_IT();
    
    while (TRUE)
    {
        u16IdleTicks++;
        Comm_OnIdle();
        IO_TaskIdle();
        
        if (TMR2IF) //20ms app scheduler
        {
           TMR2IF = 0;
           u16Tics++;
           IO_TaskFast();
           PRS_Task();
           CTRL_Task();
           Rel_Task();
           Comm_Task();
           
           NVM_Task();
           if (RAM_ACTMODE.byPROGPIRCMD & ACT_MODE_Si7021) {
                Si7021_Task();
            }
           if (RAM_ACTMODE.byPROGPIRCMD & ACT_MODE_DS18B20)
           {
                DS18B20_Task();
           }
                      
           if (task1sek)           {
               task1sek--;
           }
           else {
               task1sek = ONESEC_CTR;
               PRS_Task1s();
               CTRL_Task1s();
               PRG_Task1s();
               Rel_Task1s();
               Rnt_Task1Sec();
               Comm_TaskSlow();
           }
                      
           taskslot = ((uint8) u16Tics) & 0x1F;
           
           //every 640ms
           switch (taskslot)
           {
               case 0:
                   IO_TaskSlow();
                   break;
               case 1:
                   RTC_TaskSlow();
                   break;
                  
               case 2:
                    //if after task NVM is idle - no pending requests
                    if ((RESET_FLAG == u16Reset ) && 
                        (NVM_IsIdle()) &&
                        (Rel_IsIdle()) )
                    {
                        DISABLE_IT();
                        DISABLE_IT();
                        asm("RESET"); 
                    }
                    break;
               case 4:
                   
                   break;
               default:
                  
                   break;
           }         
        }
    }
}

