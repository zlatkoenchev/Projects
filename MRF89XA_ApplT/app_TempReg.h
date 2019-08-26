/* 
 * File:   app_TempReg.h
 * Author: zlatko
 *
 * Created on March 4, 2018, 5:47 PM
 */

#ifndef APP_TEMPREG_H
#define	APP_TEMPREG_H

typedef struct {
    sint8 lim;
    sint8 de[3];
} Trow;
extern Trow RAM_CTRL[7];
extern const Trow ROM_CRTRL[7];

typedef struct {
    uint8 StartPwm;
    uint8 EvalTime;
    uint8 Rsv1;
    uint8 Rsv2;
} TRegParams;

extern TRegParams REG_PARAMS_RAM;
extern const TRegParams REG_PARAMS_ROM;

extern uint8 RegRow, RegCol, StartPwm, newPWM;
void REG_Init(void);
uint8 REG_GetLevel(void);
void REG_TaskSlow(void);

#endif	

