/* 
 * File:   drv_air_sens.h
 * Author: zlatko
 *
 * Created on October 7, 2018, 12:06 PM
 */

#ifndef DRV_AIR_SENS_H
#define	DRV_AIR_SENS_H
extern sint16 currtemp;
extern uint8 currhum;

void AirS_Init(void);
void AirS_Task(void);
void AirS_Task_Slow(void);
void AirS_Task1min(void);
#define AirS_GetTemp() currtemp
#define AirS_GetHum()  currhum

void App_OnAirTempSig(void);
void App_OnAirHumSig(void);

#endif	

