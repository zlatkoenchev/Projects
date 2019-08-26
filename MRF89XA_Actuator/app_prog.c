#include "types.h"
#include "app_RTC.h"
#include "app_prog.h"
#include "svc_nvm.h"

static uint8 bTimeOn;

void PRG_Init(void){
    bTimeOn = FALSE;
}

void PRG_Task1s(void){
    uint8 bitn = RTC_TimeToNumber();
    uint8 temp;
    if (DateTime.DOW > 5){
        temp = RAM_TIMEPROGRAM2[bitn >> 3];
    }
    else
    {
        temp = RAM_TIMEPROGRAM[bitn >> 3];
    }
    
    if (bitn < 96)     {
        bTimeOn = (temp & (1 << (bitn & 7))) != 0;
    }
    else    {
        bTimeOn = 0;
    }
}

uint8 PRG_IsOnTime(void){
    return bTimeOn;
}
