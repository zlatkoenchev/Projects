
#include "types.h"
#include "drv_io.h"
#include "svc_nvm.h"

#define ADC_RESOLUTION_01uV  5  //2mV resolution
#define TEMP_0_OFFSET   RAM_PARAM.C_TEMP_OFFS
#define TEMP_GAIN  RAM_PARAM.C_TEMP_GAIN
#define TEMP_SAMPLES 32

uint16 AdcRaw;
uint32 AdcTempFilt;
uint8 AdcTempCnt;
sint16 AdcTemp;
sint16 sTemp;

#define PIR_RDY 0x01
#define PIR_OLD 0x02
#define PIR_ACT 0x04
#define PIR_STABLE 62 //40sec
#define PIR_LEVEL RB5
#define SW1_LEVEL RB7
#define SW2_LEVEL RB6
#define SW_DEB_MASK 0x07
#define BUT_AUTOREP 20

typedef struct {
    uint8 bEdge:1;
    uint8 bOld:1;
    uint8 u8Ready;
}TPIR;

TPIR PIRFlags;

uint8 SW1buf,SW2buf,SWdeb1, SWdeb2, SWcnt1, SWcnt2;
static void IO_StartTimer2(uint8 Time);

void IO_DisablePIR(void){
    PIRFlags.u8Ready = 2;//wait 0.6-1.2s before detect new edges 
}

static void IO_CalcTemp(void){
    uint16 offs8 = TEMP_0_OFFSET;
    offs8 += 300;//500mV @ 0C
    sTemp = AdcTemp;
    sTemp = sTemp - offs8;
}
//0.1C resolution
sint16 IO_GetTempMeas(void){
    return sTemp;    
}

uint8 IO_GetPIRLevel(void){
    if (PIRFlags.bEdge){   
            PIRFlags.bEdge = 0;
            return TRUE;
    }
    return FALSE;
}

uint8 IO_GetPIRPin(void)
{
    return PIR_LEVEL;
}


uint8 IO_GetSW1Press(void) {
    uint8 b = SWdeb1 & 2;
    SWdeb1 &= ~2;
    
    return b;
}

uint8 IO_GetSW2Press(void) {
    uint8 b = SWdeb2 & 2;
    SWdeb2 &= ~2;
    
    return b;
}

void IO_TaskFast(void) {
    uint8 bUV = FALSE;
    
    if (PIR_LEVEL) {
       if (PIRFlags.bOld) {
             //already 1
        }
        else {
                PIRFlags.bOld = 1;
                if (0==PIRFlags.u8Ready){
                    PIRFlags.bEdge = 1;//rising edge
                }
                else {
                    PIRFlags.bEdge = 0;
                }
            }
    }
    else  {
        PIRFlags.bOld = 0;
    }
    
    if ((PORTB & 0xC0) == 0xC0)//both pressed?
    {
        bUV = TRUE;
    }
    //buttons
    SW1buf <<= 1;
        
    if ((0 == SW1_LEVEL) && (FALSE == bUV))    {
        SW1buf |= 1;
    }
    

    if (( SW1buf & SW_DEB_MASK) == SW_DEB_MASK) {
        if (!(SWdeb1 & 1)) {
            SWdeb1 |= 2; //pressed
            SWcnt1 = BUT_AUTOREP;
        }
        SWdeb1 |=1; 
        if (SWcnt1) {
            SWcnt1--;
            if (0 == SWcnt1) {
                SWcnt1 = BUT_AUTOREP;
                SWdeb1 |= 2; //pressed autorepeat
            }
        }
    } else if ((SW1buf & SW_DEB_MASK) == 0) {
       SWdeb1 &= ~1;
        SWcnt1 = 0;
    }
    
    SW2buf <<= 1;
    if ((0==SW2_LEVEL)&& (FALSE == bUV)) {
        SW2buf |= 1;
    }
    

    if ((SW2buf & SW_DEB_MASK) == SW_DEB_MASK) {
        if (!(SWdeb2 & 1)) {
            SWdeb2 |= 2; //pressed
            SWcnt2 = BUT_AUTOREP;
        }
        SWdeb2 |= 1;
        if (SWcnt2)
        {
            SWcnt2--;
            if (0 == SWcnt2)
            {
                SWcnt2 = BUT_AUTOREP;
                SWdeb2 |= 2; //pressed autorepeat
            }
        }
    } else if ((SW2buf & SW_DEB_MASK) == 0) {
        SWdeb2 &= ~1;
        SWcnt2 = 0;
    }
}

void IO_TaskSlow(void) {

#ifdef TMP36_PRESENT
    ADCON0bits.ADGO = 1; //start 1st conversion
    IO_StartTimer2(IO_Time10ms);
#endif
    if (PIRFlags.u8Ready) {
        PIRFlags.u8Ready--;
    } 
#ifdef TMP36_PRESENT
    //do some work before 10ms
    if (AdcTempCnt) {
        AdcTempCnt--;
    } else {
       
        AdcTempFilt = (AdcTempFilt * TEMP_GAIN);
        AdcTempFilt += 32768;//round
        AdcTemp = AdcTempFilt >> 16 ;

        AdcTempFilt = 0;
        AdcTempCnt = TEMP_SAMPLES-1;
        IO_CalcTemp();
    }
    

    while (ADCON0bits.ADGO);
    AdcRaw = (((uint16) ADRESH) << 8) | (ADRESL);
    AdcTempFilt += AdcRaw;
    
    while(!IO_IsTimer2Elapsed());
    
    ADCON0bits.ADGO = 1; //start 2nd conversion
    while (ADCON0bits.ADGO) ;
    AdcTempFilt += (((uint16) ADRESH) << 8) | (ADRESL);
#endif
}

void IO_Init(void) {

#ifdef TMP36_PRESENT    
   // FVRCON = 0b10000010;//enable , 2.048V reference

    ADCON0 = 0;
    ADCON1 = 0x80; //right justifyed, internal vrm
    ADCON0bits.ADON = 1;
#endif
    PIRFlags.u8Ready = PIR_STABLE;

#ifdef TMP36_PRESENT
    AdcTempCnt = TEMP_SAMPLES-1;
    //start measurement
    ADCON0bits.ADGO = 1;
#endif    
    //prepare io timers
    T4CON = (0x18 | 0x03); //fosc /4*64, poscaler 1:4 , 512us 
    TMR4IE = 0;
    
    T6CON = (0x18 | 0x03); //fosc /4*64, poscaler 1:4 , 512us 
    TMR6IE = 0;
    
    //clear buffers
    SWcnt1 = SWcnt2 = SW1buf = SW2buf = SWdeb1 = SWdeb2 = 0;
    AdcTempFilt = 0;
    
    sTemp = 200;  
    PIRFlags.bEdge = 0;
    PIRFlags.bOld = 0;
}

void IO_StartTimer1(uint8 Time) {
    T4CONbits.TMR4ON = 0;
    PR4 = Time;  
    TMR4IF = 0;
    T4CONbits.TMR4ON = 1;
}

static void IO_StartTimer2(uint8 Time) {
    T6CONbits.TMR6ON = 0;
    PR6 = Time;
    TMR6IF = 0;
    T6CONbits.TMR6ON = 1;
}