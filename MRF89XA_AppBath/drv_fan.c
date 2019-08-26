#include "types.h"
#include "main.h"
#include "drv_fan.h"
#include "drv_io.h"
#include "app_RTC_cfg.h"
#include "app_RTC.h"
#include "app_bath.h"



#define FAN_START_TIME  (2000/OS_TICK_MS) /*wait flap to open*/
	
	
//variables
TFanState eFS;
static uint8 u8LowMinutes;
static uint8 u8HiMinutes;
static uint8 bStartCnt;

///////////////////////////////////////////////////////////
static uint8 FanDrv_GetLowSpeed(void){
    uint16 TimeNow = RTC_TimeToNumber();
   
    if ((RTC_IsTimeOk()) && 
            ((TimeNow > RTC_TIME_2NUMBER(21,00)) || (TimeNow < RTC_TIME_2NUMBER(7, 0))))
    {
        return TRUE;
    }
        
    return FALSE;
}
///////////////////////////////////////////////////////////
void FanDrv_Init(void){

	u8LowMinutes = 0;
	u8HiMinutes = 0;
	eFS = FAN_OFF;
}	
///////////////////////////////////////////////////////////
void FanDrv_Task(void){
	switch (eFS)
	{
		case FAN_OFF:
			if ((0!=u8LowMinutes) || (0!=u8HiMinutes))
			{
				eFS = FAN_START;
				bStartCnt = FAN_START_TIME;
			}
			IO_SetOut(Do_Fan_Low,0);
			IO_SetOut(Do_Fan_Hi,0);
		break;
		
		case FAN_START:
			if (0!=bStartCnt)
			{
				bStartCnt--;
			}	
			else
			{
				if (0!=u8HiMinutes)
				{
					eFS = FAN_HI;
				}
				else if	(0!=u8LowMinutes)
				{
					eFS = FAN_LOW;
				}
				else
				{
					eFS = FAN_OFF;
				}		
			}
			IO_SetOut(Do_Fan_Low,0);
			IO_SetOut(Do_Fan_Hi,1);	
		break;
		case FAN_HI:
			if (0 != u8LowMinutes) //force low
			{
				eFS = FAN_LOW;
				u8HiMinutes = 0;
			}
            //decrease fan speed at night hours and shower is finished
            else if (TRUE == FanDrv_GetLowSpeed())
            {
                if (u8HiMinutes)
                {
                    u8LowMinutes = u8HiMinutes;
                    u8HiMinutes =0;
                    eFS = FAN_LOW;
                }
            }
			else if (0 == u8HiMinutes)
			{
				eFS = FAN_OFF;
			}
			IO_SetOut(Do_Fan_Low,0);
			IO_SetOut(Do_Fan_Hi,1);	
		break;
		case FAN_LOW:
			if (0 != u8HiMinutes)
			{
				eFS = FAN_HI;
				u8LowMinutes = 0;
			}	
			else if (0 == u8LowMinutes)
			{
				eFS = FAN_OFF;
			}	
			IO_SetOut(Do_Fan_Low,1);
			IO_SetOut(Do_Fan_Hi,0);
		break;
		default:
			eFS = FAN_OFF;
		break;
	}	 	
}

///////////////////////////////////////////////////////////
void FanDrv_Task1Min(void){
	if (u8LowMinutes)
	{
		u8LowMinutes--;
	}
	if (u8HiMinutes)
	{
		u8HiMinutes--;
	}
}

///////////////////////////////////////////////////////////
uint8 FanDrv_GetLoTime(void){
    return u8LowMinutes;
}
///////////////////////////////////////////////////////////
uint8 FanDrv_GetHiTime(void) {
    return u8HiMinutes;
}
///////////////////////////////////////////////////////////
void FanDrv_ReqLow(uint8 time){
	if (0 == u8HiMinutes )
	{
		u8LowMinutes = time;
	}	
}

///////////////////////////////////////////////////////////
void FanDrv_ForceLow(uint8 time){
	u8LowMinutes = time;	
}

///////////////////////////////////////////////////////////
void FanDrv_ReqHi(uint8 time){
	u8HiMinutes = time; 
}	
	
///////////////////////////////////////////////////////////
void FanDrv_ForceOff(void){
	u8LowMinutes = 0;
	u8HiMinutes = 0;
}	