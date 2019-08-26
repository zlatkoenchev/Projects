/* 
 * File:   app_TempReg.h
 * Author: zlatko
 *
 * Created on March 4, 2018, 5:47 PM
 */

#ifndef APP_TEMPREG_H
#define	APP_TEMPREG_H

void CTRL_Init(void) ;
uint8 REG_GetLevel(void);
void CTRL_Task1s(void);
void CTRL_Task(void);
void CTRL_DiagCtrl(uint8 c);
void CTRL_OnACTSignal(void);
void CTRL_OnSWSignal(void);
void App_OnAirSensFrame(void);

//actuator features
#define ACT_MODE_Si7021 8    //has inteligent t/h sensor
#define ACT_MODE_DS18B20 16    //has inteligent t/h sensor
#define ACT_BODE_BY_CMD 4    //control by command
#define ACT_MODE_BY_PIR 2    //control by PIR
#define ACT_MODE_BY_PRG 1    //control by program

//actuator type
#define ACT_TYPE_BSRELAY 1
#define ACT_TYPE_RELAY 2
#define ACT_TYPE_PWM 3
#define ACT_TYPE_PHOTOMOS 4

#endif	

