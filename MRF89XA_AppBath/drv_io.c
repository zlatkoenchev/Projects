
#include "types.h"
#include "drv_io.h"
#include "svc_nvm.h"
#include "drv_BathCom.h"

#define ADC_RESOLUTION_01uV  20  //2mV resolution
#define TEMP_0_OFFSET   RAM_PARAM.C_TEMP_OFFS
#define TEMP_GAIN_01uV  RAM_PARAM.C_TEMP_GAIN

#define BUT_DEB_MASK          0x0F

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



static uint8 DiRaw[Di_NUM];
uint8 DiDeb[Di_NUM];

uint8 PIRFlags;
uint8 PIRCnt;
uint8 outs;
static void IO_StartTimer2(uint8 Time);

uint16 IOGetADCFilt(tAI i) {
    i=i<<1;
    uint16 r = BCom_GetIn(i);
    r <<=8;
    r |= BCom_GetIn(i +1);
    return (r >> 2);
}

uint8 IOGetDio(tDI i) {
    return DiDeb[i];
}	


static void IO_DebounceDi(void) {
    uint8 i;
    DiRaw[Di_FanPanelBu] <<= 1;
    if (IOGetADCFilt(Ai_FanCtl) > 220) {
        DiRaw[Di_FanPanelBu] |= 1;
    }
    DiRaw[Di_FanLightSw] <<= 1;
    if (IOGetADCFilt(Ai_SWFan) > 220) {
        DiRaw[Di_FanLightSw] |= 1;
    }

    for (i = 0; i < Di_NUM; i++) {
        if (0 == (DiRaw[i] & BUT_DEB_MASK)) {
            DiDeb[i] = 0; //Di is stable 0
        } else if (BUT_DEB_MASK == (DiRaw[i] & BUT_DEB_MASK)) {
            DiDeb[i] = 1; //Di is stable 1
        }
        else {
            //keep old state
        }
    }
}		

void IO_TaskFast(void) {
  
   BCom_ReadIn();
   IO_DebounceDi();
   BCom_SetOut(outs);
}

void IO_SetOut(tOut i, uint8 val) {    
        if (0 == val)
        {
           outs &= (~i);
        }
        else
        {
            outs |= i;
        }
    	 
}

void IO_TaskSlow(void){
     
}

void IO_Init(void){
    
   // FVRCON = 0b10000010;//enable , 2.048V reference
  //  ADCON0 = 0;
   // ADCON1 = 0x83; //right justifyed, internal vrm
  //  ADCON0bits.ADON = 1;
  //  PIRCnt = PIR_STABLE; 
  //  AdcTempCnt = 16-1;
    //start measurement
  //  ADCON0bits.ADGO = 1;
    
    //prepare io timers
    T4CON = (0x18 | 0x03); //fosc /4*64, poscaler 1:4 , 512us 
    TMR4IE = 0;
    
    T6CON = (0x18 | 0x03); //fosc /4*64, poscaler 1:4 , 512us 
    TMR6IE = 0;
    
    //clear buffers
    outs = 0;
  
    
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