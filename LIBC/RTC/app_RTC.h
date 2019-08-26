/* 
 * File:   app_RTC.h
 * Author: zlatko
 *
 * Created on February 24, 2018, 11:31 AM
 */

#ifndef APP_RTC_H
#define	APP_RTC_H

#include "app_RTC_cfg.h"

#ifdef USE_RTC_CHIP
#include "drv_DS3231.h"
#endif

#define RTC_TIME_2NUMBER(hr, min)  ((((uint16)hr)*4)+((min)/15))

typedef struct {
    uint8 Seconds;
    uint8 Minutes;
    uint8 Hours;
    uint8 DOW;
    uint8 Day;
    uint8 Month;
    uint8 Year;

} TDateTime;

extern TDateTime DateTime;

extern uint8 RTC_Status;
#define RTC_GetStat()  RTC_Status
#define RTC_IsRTCPresent() (RTC_Status & 1)
#define RTC_IsTimeOk()  (0 != RTC_Status)  
void RTC_Init(void);
void RTC_TaskSlow(void);
void RTC_OnRTCFrame(void);
uint8 RTC_BCD2DEC(uint8 x);
uint8 RTC_TimeToNumber(void);
#endif	

