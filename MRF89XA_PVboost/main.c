/*
 * File:   main.c
 * Author: zlatko
 *
 * Created on January 28, 2018, 11:11 AM
 */

#include "types.h"
#include "main.h"
#include "drv_io.h"

/*
 int oscillator on 2MHz
 */

// PIC16F18323 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1
#pragma config FEXTOSC = OFF    // FEXTOSC External Oscillator mode Selection bits (Oscillator not enabled)
#pragma config RSTOSC = LFINT  // Power-up default value for COSC bits (LFINT (32k))
#pragma config CLKOUTEN = OFF   // Clock Out Enable bit (CLKOUT function is disabled; I/O or oscillator function on OSC2)
#pragma config CSWEN = ON       // Clock Switch Enable bit (Writing to NOSC and NDIV is allowed)
#pragma config FCMEN = OFF       // Fail-Safe Clock Monitor Enable (Fail-Safe Clock Monitor is disabled)

// CONFIG2
#pragma config MCLRE = OFF      // Master Clear Enable bit (MCLR/VPP pin function is MCLR; Weak pull-up enabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config WDTE = OFF      // Watchdog Timer Enable bits (WDT enabled, SWDTEN is ignored)
#pragma config LPBOREN = OFF    // Low-power BOR enable bit (ULPBOR ENABLED)
#pragma config BOREN = ON      // Brown-out Reset Enable bits (Brown-out Reset disabled)
#pragma config BORV = LOW       // Brown-out Reset Voltage selection bit (Brown-out voltage (Vbor) set to 2.45V)
#pragma config PPS1WAY = OFF    // PPSLOCK bit One-Way Set Enable bit (The PPSLOCK bit can be set and cleared repeatedly (subject to the unlock sequence))
#pragma config STVREN = ON      // Stack Overflow/Underflow Reset Enable bit (Stack Overflow or Underflow will cause a Reset)
//#pragma config DEBUG = ON       // Debugger enable bit (Background debugger enabled)

// CONFIG3
#pragma config WRT = OFF        // User NVM self-write protection bits (Write protection off)
#pragma config LVP = ON         // Low Voltage Programming Enable bit (Low Voltage programming enabled. MCLR/VPP pin function is MCLR. MCLRE configuration bit is ignored.)

// CONFIG4
#pragma config CP = OFF         // User NVM Program Memory Code Protection bit (User NVM code protection disabled)
#pragma config CPD = OFF        // Data NVM Memory Code Protection bit (Data NVM code protection disabled)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#define CLWD()  asm("CLRWDT")




#define MAX_POWER  5000
#define PWM_MIN 10
#define MAX_VOUT  1250



#define BUT1  RA5
#define BUT1PU(x) WPUA5 = x;WPUA4 = x

#define RESET_FLAG 0xA55A 
#define ONEMIN_CTR 59 

#define LED LATA2

uint8 bDir;
uint8 u8PWM;
uint16 Power; //0.1W resolution
uint16 OldPower;
uint16 MaxPower;

//0.1W
void CalcPower(void) {
    
    //d = pwm/320
    
    u32t = Vin;
    u32t *= CSense;
    u32t = ((u32t * 32) / 10);
    
    Power =(uint16)( u32t / ((uint16)320 - u8PWM));
    
    MaxPower = MAX_POWER;
    
    if (Temperature > 60){
        MaxPower = 1000;//100W
    }
    else if (Temperature > 50)    {
        MaxPower = 3000;//300W
    } 
    else if (Temperature > 45)
    {
        MaxPower = 4000;//400W
    } 
    else if (Temperature > 40) {
        MaxPower = 4500;//450W
    }
}

void MPPT(void){
    //change direction 
    
    if (u8PWM ==0)     {
        bDir = 1;
    }
    
    if (Power < OldPower)  {
        bDir = !bDir;
    }

    //limit power and voltage
    if ((Power > MaxPower) ||
        (Vout > MAX_VOUT)) {
        bDir = 0;
    }
    
    if (bDir){
        if (u8PWM < 240)  
        {
            if (u8PWM < PWM_MIN)   {
                u8PWM = PWM_MIN;
            } else {
                u8PWM += 2;
            }
        }
    }
    else {
        if (u8PWM > PWM_MIN) 
        {
            u8PWM = u8PWM - 2;
        }
        else {
            u8PWM = 0;
        }
    }

    OldPower = Power;
    
    //below 10V stop PWM too
    if (Vin < 100) {
        u8PWM = 0;
    }
}

uint8 zzl;
int main(void) {   
    DISABLE_IT();
    //HAL init
    IO_Init(1);
    bDir = 1;
    u8PWM = 0;
   
    ENABLE_IT();
    
    while (1) {
        IO_safetyCheckIdle();
        if (IO_OSTMRElapsed()){
            LED = 1;
            IO_ReadADC();
            UART_Send();
            IO_safetyCheck10ms();
            if (0 == bEmStop) {
                zzl++;
                if ((zzl & 0x07) == 0){
                    CalcPower();
                    MPPT();
                }
                IO_SetPWM(u8PWM);
            } else {
                bEmStop--;
                if (0 == bEmStop) {
                    IO_Init(0);//reinit PWM
                    bDir = 1;
                }
            }
            LED = 0;
        }
    }
}


