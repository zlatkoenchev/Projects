
#include "types.h"
#include "drv_io.h"
#include "svc_nvm.h"
#include "app_control.h"

#define ADC_RESOLUTION_01uV  20  //2mV resolution
#define TEMP_0_OFFSET   RAM_PARAM.C_TEMP_OFFS
#define TEMP_GAIN_01uV  RAM_PARAM.C_TEMP_GAIN



#define SW_DEB_MASK 0x07

uint8 u8ZCnumber;
uint8 u8ZCpwm;
uint8 uPMRequest;//photomos request for ON
uint8 u8RelSync;
uint8 u8RelPulses;
uint8 SW1buf,SW2buf,SWdeb1, SWdeb2;

void IO_SetPhotomosSync(uint8 cmd){
    uPMRequest = cmd;
    if (0 ==uPMRequest) { 
            IO_PHOTOMOS_OFF;
    }
}

//255 =100%, 0 = off
void IO_SetRelSync(uint8 cmd){
    u8RelSync = cmd;
}

uint8 IO_GetSW1Press(void) {
   // uint8 b = SWdeb1 & 2;
    //SWdeb1 &= ~1;
    return (SWdeb1 & 2);
}

uint8 IO_GetSW2Press(void) {
    uint8 b = SWdeb1 & 1;
    SWdeb1 &= ~1;
    return b;
}

void IO_TaskFast(void) {
   
    //enable zc interrupt only in case it is used
    if ((RAM_ACTMODE.ActType == ACT_TYPE_BSRELAY) ||
        (RAM_ACTMODE.ActType == ACT_TYPE_PHOTOMOS) ||
        (RAM_ACTMODE.ActType == ACT_TYPE_PWM)) {
        if (( 0 == C1IE ) || (0 == PEIE)) {
            C1IE = 1; // int Comp1
            PEIE = 1; // pie = 1
        }
    } else {
        C1IE = 0; // int Comp1
        PEIE = 0;
    }
   
    //buttons
    SW1buf <<= 1;
    if (1==SW1_LEVEL)   {
        SW1buf |= 1;
    }
    

    if (( SW1buf & SW_DEB_MASK) == SW_DEB_MASK) {
        SWdeb1 |=2;   
    } else if ((SW1buf & SW_DEB_MASK) == 0) {
       SWdeb1 &= ~2;   
    }
    if (SWdeb1 == 2) {
        SWdeb1 |= 1;//pressed
    }
    
    SW2buf <<= 1;
    if (0==SW2_LEVEL) {
        SW2buf |= 1;
    }
    

    if ((SW2buf & SW_DEB_MASK) == SW_DEB_MASK) {
        SWdeb2 |= 2;
    } else if ((SW2buf & SW_DEB_MASK) == 0) {
        SWdeb2 &= ~2;
    }
    if (SWdeb2 == 2) {
        SWdeb2 |= 1; //pressed
    }
    
    
}

void IO_TaskSlow(void){
   
}

void IO_TaskIdle(void){
   
}

void IO_Init(void){
    
    CM1CON1 = 0b11100001; //both edges, FVR, C12IN1
    CM1CON0 = 0b00000010; //hyst enable, low speed
    FVRCON = 0b10000100; //enable , 1V reference
    CM1CON0bits.C1ON = 1; //enable comparator
    C1IF = 0;
   
    
    //prepare io timers
    T4CON = (0x18 | 0x03); //fosc /4*64, poscaler 1:4 , 512us resolution
    TMR4IE = 0;
    
    T6CONbits.TMR6ON = 0;
    T6CON = (0x0 | 0x01); //fosc /4*4, poscaler 1:1 , 8us resolution
    TMR6IE = 0;
    TMR6IF = 0;
    
    uPMRequest =  u8ZCpwm = u8ZCnumber = u8RelSync = SW1buf = SW2buf = SWdeb1 = SWdeb2 = 0;

    if (RAM_PIRDATA.PIR_CTRL & 2)   {
        WPUB7 = 0; //RB7  PIR input, no pullup  
    }
}

void IO_StartTimer1(uint8 Time) {
    T4CONbits.TMR4ON = 0;
    PR4 = Time;  
    TMR4IF = 0;
    T4CONbits.TMR4ON = 1;
}

void IO_StartTimer2(uint8 Time) {
    TMR0IE = 0;
    TMR0 = ~Time;
    TMR0IF = 0;
}

void interrupt ISR(void) {
    if (C1IF) {
        C1IF = 0;
        if (0xff != u8ZCnumber) {
            u8ZCnumber++;
        }
        u8ZCpwm++;
        
        if (u8RelSync > u8ZCpwm) 
        {
            T6CONbits.TMR6ON = 0;
            PR6 = ROM_ACTMODE.PulseDelay;//512us
            TMR6IF = 0;
            TMR6IE = 1;
            T6CONbits.TMR6ON = 1;
            u8RelPulses = ROM_ACTMODE.PulseNum;
        }
        else   {
            T6CONbits.TMR6ON = 0;
         if (uPMRequest) {
                IO_PHOTOMOS_LO;
                IO_PHOTOMOS_ON;
            } else {
               // IO_PHOTOMOS_OFF;
            }
        }
    }
    if (TMR6IF) {
        IO_SetREL_ON(1);
        IO_SetREL_ON(1);
        IO_SetREL_ON(1);
        IO_SetREL_ON(1);
        IO_SetREL_ON(1);
        IO_SetREL_ON(1);
        IO_SetREL_ON(1);
        IO_SetREL_ON(1);
        IO_SetREL_ON(1);
        IO_SetREL_ON(1);
        IO_SetREL_ON(1);
        IO_SetREL_ON(1);
        if (u8RelPulses !=0)   {
            u8RelPulses--;
            if (0 == u8RelPulses)   {
                TMR6IE = 0;
                T6CONbits.TMR6ON = 0;
            }
        }
        TMR6IF = 0;
        IO_SetREL_ON(0);
    }
}

