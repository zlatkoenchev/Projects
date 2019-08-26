
#include "types.h"
#include "drv_io.h"
#include "main.h"

//10ms cycle
#define OS_CYLE  78   //156   //20 ms


#define ADC_SAMPLES 4
uint8 AdcIndex;
uint16 AdcVin[ADC_SAMPLES];
uint16 AdcVout[ADC_SAMPLES];
uint16 AdcCS[ADC_SAMPLES];
uint16 AdcTemp[ADC_SAMPLES];
uint16 zzz;
uint16 Vin,VinRaw;
uint16 Vout, VoutRaw;
uint16 CSense,CSenseRaw;
uint8 Temperature;
uint8 bEmStop;
uint32 u32t;

#define SW_DEB_MASK 0x07

 void Clock_Init(void) {
    INTCON = 1; //INT rising edge

    PIE0 = 0;
    PIE1 = 0;
    PIE2 = 0;
    PIE3 = 0;
    PIE4 = 0;

    IDLEN = 0;

    OSCFRQ = 7; //32MHz HSOCS select
    OSCCON3 = 0; //switch clock acsap

    IOCIE = 0;
    OSCCON1 = 0x60; //selct HSOC 32MHz, div 1

}

 void FVR_Init(void) {
    //FVR enable 2.048V
    FVRCON = 0b00001000;
    FVREN = 1;
}

 void CMP_Init(void) {
    C1IE = 0;
    CM1CON0 = 0b00010110; //hyst,inverted
    CM1CON1 = 0b10110011; //RC3 is C1IN3, other in is FVR
    C1ON = 1;

    PEIE = 1;
    C1IF = 0;
    C1IE = 1; //enable interrupts
}

 void Ports_Init(void) {
    RC4PPS = 0x18; //scl
   // RC5PPS = 0x19; //sda

    //PORTA A 
    // RA0 - PGD in 
    // RA1 - PGC in 
    // RA2 - DATA/LED out 0
    // RA3 - MCLR in
    // RA4 - AN Current in
    // RA5 - AN Vin in

    //PORTA C 
    // RC0 - PWM out 0
    // RC1 - AN Vout in 
    // RC2 - AN Temp in
    // RC3 - AN comp in
    // RC4 - SCL in
    // RC5 - SDA in

    LATA = 0b00000000;
    LATC = 0b00000000;

    TRISC = 0b00111110;
    TRISA = 0b00111011;

    ANSELA = 0b00110000; //
    WPUA = 0b00000000; //

    ANSELC = 0b00001110;
    WPUC = 0b00000000;
}

 void PWM_Init(void) {
    PWM5DCH = 0;
    PWM5DCL = 0;
    T2CON = 0x04; //T2 ON, prescaler =1
    PR2 = 79;
    PWM5CON = 0x80;
    RC0PPS = 0x02; //pwm5

}

 void TMR0_Init(void) {
     T0CON0 = 0;//8 bit
     T0CON1 = 0b01001010; //F0sc/4, 1:1024  50hz 100khz 24.4%
     TMR0H = OS_CYLE;
     TMR0IE = 0;
     TMR0IF = 0;
     T0EN = 1;
 }
 
 void ADC_Init(void) {
    ADCON1 = 0b11110000; //frc, GND-VDD
    ADCON0 = 0b00010101; //ADC on, 
    ADACT = 0;
    AdcIndex = 0; 
}
 
 void UART_Init(void) {
    RC5PPS = 0x14; //UART
    SP1BRGL  = 12; //38400 bps
    TXEN = 1;//rc5
    SYNC = 0;
    SPEN = 1;
 }
 
 void UART_Send(void){
     uint16 t = Power/10;
     TX1REG = (uint8)(t>>8);
     NOP();
     NOP();
     NOP();
    
     while (TXIF == 0) {};
     TX1REG = (uint8) (t );
 }
 
#define CUR_OFFS 65
#define TEMP_OFFS 155  //0.5V at 0C
 
 void IO_ReadADC(void) {

    ADCON0bits.CHS = 5; //Vin

    ADCON0bits.ADGO = 1;
    while (ADCON0bits.ADGO) { //wait conversion
    }
    
    ADCON0bits.CHS = 4; //CS
    u32t = (((uint16) ADRESH)<<8) | ADRESL;
    u32t = (u32t * 1020) / 1024; //102.3 *adc /4*1023
    ADCON0bits.ADGO = 1;
    
    //Vin
    VinRaw = AdcVin[AdcIndex] = (uint16) u32t;
    Vin  = ((AdcVin[0] + AdcVin[1] + AdcVin[2] + AdcVin[3]) / 4);
    
    while (ADCON0bits.ADGO) { //wait conversion
    }
    ADCON0bits.CHS = 0x11; //Vout
    u32t = zzz=(((uint16) ADRESH)<<8) | ADRESL;
    
    
    //CSense
    if (u32t >= CUR_OFFS) { //206mV out 0A 213mv reference
                            //551mV 0.87a 4.4mV  35
                            //1.54A - 173 903mV 7.7mv/833  102 
        u32t -= CUR_OFFS;
    } else {
        u32t = 0;
    } //remove offset 206mV
    u32t = (949
            * u32t) / 1024; //8,90A max

    ADCON0bits.ADGO = 1;
    CSenseRaw = AdcCS[AdcIndex] =  (uint16) u32t;
    CSense = ((AdcCS[0] + AdcCS[1] + AdcCS[2] + AdcCS[3]) / 4);
    
    while (ADCON0bits.ADGO) { //wait conversion
    }
    ADCON0bits.CHS = 0x12; //Temp
    u32t = (((uint16) ADRESH)<<8) | ADRESL;
    u32t *= 2385;
    
    ADCON0bits.ADGO = 1;
    
    VoutRaw = AdcVout[AdcIndex] = (uint16)(u32t / 1024);
    Vout = (AdcVout[0] + AdcVout[1] + AdcVout[2] + AdcVout[3])/4;
    
    while (ADCON0bits.ADGO) { //wait conversion
    }
    
    AdcTemp[AdcIndex]= (((uint16) ADRESH)<<8) | ADRESL;
    ADCON0bits.CHS = 5; //Vin
    
    u32t = (AdcTemp[0] + AdcTemp[1] + AdcTemp[2] + AdcTemp[3])/4;
    if (u32t >= TEMP_OFFS) {
        u32t -= TEMP_OFFS;
    } else {
        u32t = 0;
    }
    u32t = (u32t *330) / 1024;
    Temperature = (uint8)u32t;
    
    AdcIndex++;
    if (AdcIndex >= ADC_SAMPLES) {
        AdcIndex = 0;
    }
}

 void IO_SetPWM(uint8 pwm){
     PWM5DCL = pwm << 6;
     PWM5DCH = pwm >> 2;
 }
 
 void IO_Init(uint8 bFull) {
    if (bFull){
     
        bEmStop = 0;
        Ports_Init();
        Clock_Init();
        FVR_Init();
        ADC_Init();
        UART_Init();
    }
    
    PWM_Init();
    CMP_Init();
    
    if (bFull) {

        //init ADC buffer
        IO_ReadADC();
        IO_ReadADC();
        IO_ReadADC();
        IO_ReadADC();

        TMR0_Init();
    }
 }
 
 uint8 IO_OSTMRElapsed(void){
     if (TMR0IF) {
         TMR0IF = 0;
         return 1;
     }
     else return 0;
 }
 
 void interrupt intr(void) {
    C1IF = 0;
    LATC0 = 0;
    RC0PPS = 0; //pin if GPIO
    bEmStop = 100;//seconds off
}

 void IO_safetyCheckIdle(void) {
     if (( RC3 == 1 ) || 
         ( C1OUT == 1 ) 
          ) {
        LATC0 = 0;
        RC0PPS = 0; //pin is GPIO
        bEmStop = 100; //seconds off
     }
 }
 
 void IO_safetyCheck10ms(void) {
    if ((VoutRaw > MAX_V_OUT) ||
        (CSenseRaw < MIN_I_OUT)
         ) {
        LATC0 = 0;
        RC0PPS = 0; //pin is GPIO
        bEmStop = 100; //1 seconds off
    }
}