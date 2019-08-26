/* 
 * File:   app_ProgTemp.h
 * Author: zlatko
 *
 * Created on March 4, 2018, 5:48 PM
 */

#ifndef APP_PROGTEMP_H
#define	APP_PROGTEMP_H

void PRG_Init(void);
void PRG_OnPIRFrame(void);
void PRG_TaskSlow(void);
extern sint16 ProgSetTemp;
#define PRG_GetSetTemp() (ProgSetTemp)
void PRG_SetNewTemp(uint8 bIncrease);

#endif	

