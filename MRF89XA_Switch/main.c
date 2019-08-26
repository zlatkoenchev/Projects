/*
 * File:   main.c
 * Author: zlatko
 *
 * Created on January 28, 2018, 11:11 AM
 */

#include "types.h"
#include "svc_comm.h"
#include "MRF89XA.h"
#include "main.h"
#include "svc_nvm.h"
#include "svc_uds.h"


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
#pragma config MCLRE = ON       // Master Clear Enable bit (MCLR/VPP pin function is MCLR; Weak pull-up enabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config WDTE = SWDTEN      // Watchdog Timer Enable bits (WDT enabled, SWDTEN is ignored)
#pragma config LPBOREN = ON    // Low-power BOR enable bit (ULPBOR ENABLED)
#pragma config BOREN = OFF      // Brown-out Reset Enable bits (Brown-out Reset disabled)
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

#define BUT1  RA5
#define BUT1PU(x) WPUA5 = x;WPUA4 = x

#define RESET_FLAG 0xA55A
#define ONESEC_CTR 49 
#define ONEMIN_CTR 59 

static volatile uint8 temp;
uint8 Voltage;//20mv resolution
uint8 SWSstate;
uint16 WSOpenTime;
uint8 WSDeb;
uint8 ButLevel;


static void Clock_Init(void) {
    INTCON = 1; //INT rising edge
    
    PIE0 = 0;
    PIE1 = 0;
    PIE2 = 0;
    PIE3 = 0;
    PIE4 = 0;
    
    IDLEN = 0;
    
    OSCFRQ = 0;//1MHz HSOCS select
    OSCCON3 = 0; //switch clock acsap
    
    IOCIE = 0;
    
    //wait 4s on low power oscillator to stabilze the power
    GotoSleep(SLP_4S);
}

#define Select1Mhz() OSCCON1 = 0x60 //selct HSOC 1MHz, div 1

#define Select31khz() OSCCON1 = 0x40 //selct LFOSC 31kHz, div 1 

static void Ports_Init(void){ 
    
    INTPPS = 0x15;//RC5 -> INT
    
    SSP1CLKPPS = 0x10;//RC0 -> SCK
    RC0PPS = 0x18; //RC0 -> SCK
    RC2PPS = 0x19; //RC2 - SDO
    SSP1DATPPS = 0x11; //RC1 - SDI
       
    //PORTA A 
    // RA0 - PGD out 0
    // RA1 - PGC out 0
    // RA2 - (HCSC) out 1
    // RA3 - MCLR in
    // RA4 - In sw 1
    // RA5 - In sw 1
    
    //PORTA C 
    // RC0 -(SCK) out 0
    // RC1 - (MISO) in 
    // RC2 - (MOSI) out 0
    // RC3 - (HCSD) out 1
    // RC4 - In Sw 2 out
    // RC5 - (IRQ1) in
  
    LATA = 0b10000100;
    LATC = 0b00011010; 
    
    TRISC = 0b00100010;
    TRISA = 0b00111000;
    
    ANSELA = 0; //digital inp
    WPUA = 0b00001000;//sw 1 pullup on
   
    ANSELC = 0;
    WPUC = 0b00010000;
        
    PMD0 |= 0b00000110; //disable clock reference,NVM
    PMD1 |= 0b10000111; //timers off 
    PMD2 |= 0b01000110;
    PMD3 |= 0b01110011;
    PMD4 |= 0b00100000;
    PMD5 |= 0b00000111;
}

//disable not used pheripherals
#define IO_Sleep(){  \
    SPI_HF_Deinit(); \
    MSSP1MD=1;       \
    ADCMD = 1;       \
    SYSCMD = 1;      \
    FVRMD = 1;       \
}\

//enable pheripherals
#define IO_Wakeup() {\
    MSSP1MD = 0;\
    SYSCMD = 0;\
    ADCMD = 0;\
    FVRMD = 0;\
    SPI_HF_Init();\
}\

    
//negative edge on but 1
//enable interrupt on change
//clear single flags
#define EnableBut1Wakeup() {\
    IOCAN5 = 1; \
    IOCIE = 1;  \
    IOCAF = 0;  \
}\


   
uint8  CalcUbat(void){
    return (uint8)( 13107 / Voltage);//20mV resolution
}

static void ConvBat(void){
    FVRCON = 0b10000001;//FVR on, Temp off, ADC gain 1;
    //35 us wait time before usage!
    temp = 5;
    while (temp--); //delay to stabilize FVR
    
    ADCON1 = 0b00000000; //fosc/2, GND-VDD
    ADCON0 = 0b11111101; //ADC on, FVR input;
    ADACT = 0;
    temp = 5;
    while (temp--); //delay to stabilize FVR
    
    ADCON0bits.ADGO = 1;
    while (ADCON0bits.ADGO){ //wait conversion
    }
    Voltage = ADRESH;
    FVRCON = 0;
    ADCON0 = 0;
    if ( 0 == Voltage) {
        Voltage++;
    }
}

#ifdef SWITCH_PUSH_BUTTON
void MainLoop(void) {
    Select31khz();
    WSDeb = 1;
    while(1)
    {
        if (0==BUT1) {
            //wait for release
            WSDeb = 1;
        }
        else if (WSDeb) { WSDeb--;}//2 times x 256ms button is released
        else  {
            //deep sleep enter - leave by button press only
            IO_Sleep();     
            EnableBut1Wakeup();
            GotoSleep(SLP_FVR); 
            Select1Mhz();
            IO_Wakeup();
            ConvBat();
            Comm_Transmit(2); //toggle value
            WSDeb = 1;
            Select31khz();
        }
        
        LATC4 = 0; //disable pullup
        GotoSleep(SLP_256MS);
        temp = 7;
        while (temp--){
            LATC4 = 1; //enable pullup
        } //wait 1ms for level stabilize
    }
}
#endif

#ifdef SWITCH_WINDOW
void MainLoop(void) {
    Select31khz();
    SWSstate = 1; //assume open
    WSDeb = 2;
    while (1) {
        if  ( 0==SWSstate )
        {
            //deep sleep enter - leave by button press only
            LATC4 = 1; //enable pullup
            IO_Sleep();
            EnableBut1Wakeup();
            GotoSleep(SLP_FVR);
            LATC4 = 0; //disable pullup
            Select1Mhz();
            IO_Wakeup();
            ConvBat();
            Comm_Transmit(1); //send open
            IO_Sleep();
            WSDeb = 2;
            SWSstate = 1;
            WSOpenTime = 1; //send second frame after 8s
            Select31khz();
        }
        else  
        {
            GotoSleep(SLP_4S);
            //enable pullup for short and read input
            for (temp = 0; temp < 4; temp++ ) {
                LATC4 = 1; //enable pullup    
            } //wait 1ms for level stabilize
            temp = BUT1;//read it
            LATC4 = 0; //disable pullup
                
            if (0 == temp) {
                //wait for close window - stay here
                if (WSOpenTime)  {
                    WSOpenTime--;
                } 
                else  {
                    Select1Mhz();
                    WSOpenTime = 150;//10 min
                    IO_Wakeup();
                    Comm_Transmit(1); //send open
                    IO_Sleep();
                    Select31khz();
               }
               WSDeb = 2;
            } else {
               if (WSDeb ) {
                   WSDeb--;
               } else {
                  //really closed send once closed
                  Select1Mhz();
                  IO_Wakeup();
                  Comm_Transmit(0); 
                  IO_Sleep();
                  SWSstate = 0;
                  Select31khz();
              }
          }
        }   
    }//while 1
}
#endif

#ifdef SWITCH_BISTABLE
void MainLoop(void) {
    SWSstate = 0;
    WSDeb = 2;
    Select31khz();
    while (1) {
        GotoSleep(SLP_64MS);
        if (0 == SWSstate) {
            if (0 == BUT1) {
                //presed
                Select1Mhz();
                IO_Wakeup();
                ConvBat();
                Comm_Transmit(1); //send on
                IO_Sleep();
                SWSstate = 1;
                WSOpenTime = 1;//10min send frame once more after 128ms
                WSDeb = 2;
                Select31khz();
            }
        } else {
            if (0 == BUT1) {
                //wait for release stay here
                if (WSOpenTime) {
                    WSOpenTime--;
                } else {
                    Select1Mhz();
                    WSOpenTime = 9300; //resend every 10min
                    IO_Wakeup();
                    ConvBat();
                    Comm_Transmit(1); //send on
                    IO_Sleep();
                    Select31khz();
                }
                WSDeb = 2;
            } else {
                if (WSDeb) {
                    WSDeb--;
                } else {
                    //really off
                    Select1Mhz();
                    IO_Wakeup();
                    Comm_Transmit(0); //send once open
                    IO_Sleep();
                    SWSstate = 0;
                    Select31khz();
                }
            }
        }
    }//while 1
}
#endif

int main(void) {   
    DISABLE_IT();
    //HAL init
    Ports_Init();
    Clock_Init();
    //svc init
    Select1Mhz();
  //  NVM_Init();
    SPI_HF_Init();
    Comm_Init();
    
    MainLoop();
}

