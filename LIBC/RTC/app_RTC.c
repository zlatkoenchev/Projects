#include "types.h"
#include "app_RTC.h"
#include "MRF89XA.h"
#include "svc_comm.h"
#include "main.h"

uint8 RTC_Status; // b0 - RTC present, b1 - RTC adjusted
TDateTime DateTime;

void RTC_Init(void){
    
    RTC_Status = 0;
#ifdef USE_RTC_CHIP
    if (DS3231_Init())
    {
        //RTC present
        RTC_Status = 1;
    }
#endif
    
     DateTime.Seconds = DateTime.Minutes = DateTime.Hours = DateTime.DOW= DateTime.Day = DateTime.Month = DateTime.Year= 0;
}

void RTC_TaskSlow(void) {
    
#ifdef USE_RTC_CHIP 
    if (RTC_Status & 1)
    {
        DS3231_GetTime();//read actual time
        ComSendSignal(TxTime, DateTime);
    }
#endif
    DateTime.Seconds++;
    if (0 == DateTime.Seconds)
    {
        RTC_Status = 0;//invalidate time since no RF frame received for 3..4 minutes
    }
    //restart every day 
    if (RTC_Status)
    {
        if ((DateTime.Hours == RESET_HOUR) && 
            (DateTime.Minutes == RESET_MIN) &&
            (DateTime.Seconds == RESET_SEC )) 
        {
            RequestReset();
        }
    }
}

void RTC_OnRTCFrame(void) {
    
#ifdef USE_RTC_CHIP  
    if  ((0==(RTC_Status & 1)) || (255 == RxSRC_NAD())){
        RTC_Status |= 2;
        //l,da,sa,res,cmd, data
        
        DateTime = ComRecvSignal(TDateTime);
       
        if (RTC_Status & 1)   {
            DS3231_SetTime();//adjust RTC time too
        }
    }
#else
    RTC_Status |= 2;
    //l,da,sa,res,cmd, data
    DateTime = ComRecvSignal(TDateTime);
#endif
}

uint8 RTC_BCD2DEC(uint8 x) {
    uint8 y = x & 0x0F;
    y += (x >> 4)*10;
    return y;
}

//15 min resolution
uint8 RTC_TimeToNumber(void){
    uint8 r = RTC_BCD2DEC(DateTime.Hours);
    r *= 4;
    r = r + (RTC_BCD2DEC(DateTime.Minutes) / 15);
    return r;
}
