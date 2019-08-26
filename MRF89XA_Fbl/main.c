/*
 * File:   main.c
 * Author: zlatko
 *
 * Created on January 28, 2018, 11:11 AM
 */

#include "types.h"
#include "bootloader.h"
#include "MRF89XA.h"
#include "drv_spi_hf.h"

/*
 int oscillator on 2MHz
 */

// CONFIG1
#if defined(PIC16F1847_PIM)
#pragma config FOSC = INTOSC    // Oscillator Selection (INTOSC oscillator: I/O function on CLKIN pin)
#pragma config WDTE = OFF       // Watchdog Timer Enable (WDT disabled)
#pragma config PWRTE = OFF //zzl todo      // Power-up Timer Enable (PWRT disabled)
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

#if defined(PIC18F25J50_PIM)
#pragma config WDTEN = OFF          //WDT disabled (enabled by SWDTEN bit)
#pragma config PLLDIV = 2           //Divide by 2 (8 MHz oscillator input)
#pragma config STVREN = ON            //stack overflow/underflow reset enabled
#pragma config XINST = OFF          //Extended instruction set disabled
#pragma config CPUDIV = OSC1        //No CPU system clock divide
#pragma config CP0 = OFF            //Program memory is not code-protected
#pragma config OSC = INTOSCPLL      //internal RC oscillator, PLL enabled, HSPLL used by USB
#pragma config T1DIG = ON           //Sec Osc clock source may be selected
#pragma config LPT1OSC = OFF        //high power Timer1 mode
#pragma config FCMEN = OFF          //Fail-Safe Clock Monitor disabled
#pragma config IESO = OFF           //Two-Speed Start-up disabled
#pragma config WDTPS = 32768        //1:32768
#pragma config DSWDTOSC = INTOSCREF //DSWDT uses INTOSC/INTRC as clock
#pragma config RTCOSC = T1OSCREF    //RTCC uses T1OSC/T1CKI as clock
#pragma config DSBOREN = OFF        //Zero-Power BOR disabled in Deep Sleep
#pragma config DSWDTEN = OFF        //Disabled
#pragma config DSWDTPS = 8192       //1:8,192 (8.5 seconds)
#pragma config IOL1WAY = OFF        //IOLOCK bit can be set and cleared
#pragma config MSSP7B_EN = MSK7     //7 Bit address masking
#pragma config WPFP = PAGE_1        //Write Protect Program Flash Page 0
#pragma config WPEND = PAGE_0       //Start protection at page 0
#pragma config WPCFG = OFF          //Write/Erase last page protect Disabled
#pragma config WPDIS = OFF          //WPFP[5:0], WPEND, and WPCFG bits ignored 


#endif


static void Clock_Init(void)
{
    volatile uint16 delay =15625;
    
    //start on 500kHz by default 
    //wait 1 sec for power stable
    while (delay--);
    
    OSCCONbits.IRCF = 12; //2MHz internal clock /500k instr   
}
static void Ports_Init(void) {
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

    LATA = 0b10010010;
    LATB = 0b00001000;
}

int main(void) {
    DISABLE_IT();
    
    Boot_CheckValidApp();//check/jump to appl 
    
    Ports_Init();
    Clock_Init();
    SPI_HF_Init();
    
    Boot_Init();
    MRF89XAStartReception();
    
    while (TRUE)
    {
        MRF89XATask();
        if (RxDataLen) {
            Boot_RxProcess();
            MRF89XAStartReception();
        }
    }
}

void interrupt ISR(void)
{
    asm("GOTO 0x384");
}