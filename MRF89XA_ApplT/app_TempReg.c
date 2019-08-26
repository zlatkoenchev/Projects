#include "types.h"
#include "app_ProgTemp.h"
#include "app_TempReg.h"
#include "drv_io.h"
#include "svc_comm.h"
#include "svc_nvm.h"
#include "app_RTC.h"
#include "drv_air_sens.h"
#include "app_win_sens.h"

uint8 newPWM;

typedef struct{
    uint8 bForceOff:1; 
    uint8 bHeatDetStarted:1;
    uint8 bTxFrame:1;
    uint8 bAdapt : 1;
}TRegFlags;
static TRegFlags sFlags; 
static uint8 evalCntr;
uint8 RegRow, RegCol;
static uint16 startTime; 
static sint16 startTemp;
static sint16 oldSetTemp;
sint16 Delta;
sint8 OldDelta;

TRegParams REG_PARAMS_RAM;
const TRegParams REG_PARAMS_ROM = {50,100,0,0 };

#define REG_EVAL_PERIOD_OFF        REG_PARAMS_RAM.EvalTime //60sec
#define REG_HEAT_OFF_TIME 5600     //30  min
#define MAX_TEMP_REG 230 //22C


#define FORCE_OFF_DT 3

Trow RAM_CTRL[7];

const Trow ROM_CRTRL[7] ={
    //      Derror
    //    -   0  +
    {15, {4, 10, 15}}, //>1.5C
    {5,  {1, 5,  7 }}, //0.5 -1.5 C
    {0,  {-1, 2,  3 }}, //0.1 - 0.4 C
    {-1, {-1, 0,  1}}, //0
    {-5, {-1,-2, -3}}, //0.1 - 0.4 C
    {-16,{-2,-5, -7}}, //0.5 -1.5 C
    {-30,{-5,-10,-15}} //>1.5C
};

void REG_Init(void){
    
    evalCntr = 10;
    startTime = oldSetTemp = 0;
    sFlags.bForceOff = 0;
    //sFlags.bTxFrame = 0;
    sFlags.bHeatDetStarted = 0;
    sFlags.bAdapt = 0;
    newPWM = 0;
}

#if 0
static void REG_P_Reg(void) {
    
    if (AirS_GetTemp() > MAX_TEMP_REG) {
        Delta = 0;
    } else {
        if ((RTC_IsTimeOk()) &&
                (DateTime.Month > 4) &&
                (DateTime.Month < 10)) {
            Delta = 0; //from may to sept - disable heating
        } else {
            Delta = PRG_GetSetTemp() - AirS_GetTemp();
        }
    }
    //limit error
    if (Delta > 20) {
       newPWM  = 100;
    } else if (Delta>10){
        newPWM = 70;
    } else if (Delta > 5) {
        newPWM = 50;
    } else if (Delta > 1) {
        newPWM = 35;
    } else if (Delta > 0) {
        newPWM = 10;
    } else {
        newPWM = 0;
    }
            
   if (Delta > 5) {
   }
   else if (Delta > 0) {
        startTime = 0;
        sFlags.bForceOff = 0;
    } else {
        sFlags.bHeatDetStarted = FALSE;
        startTime = 0;
        bForceOff = 0;
    }
}
#endif 
static void REG_FZLogic(void) {
    sint8 NewDelta;
    uint8 oldPwm = newPWM;

    if ((RTC_IsTimeOk()) &&
            (DateTime.Month > 5) &&
            (DateTime.Month < 10)) {
        Delta = 0; //from may to sept - disable heating
    } else {
        Delta = PRG_GetSetTemp() - AirS_GetTemp();
    }
#ifdef REG_ON_OFF
    if (Delta > 0) {
        newPWM = 100; 
    } else if (Delta < 0 ){
        newPWM = 0;
    }
#else
    //limit error to 8 bit
    if (Delta > 20) { Delta = 20 ; }
    else if (Delta < -20) { Delta = -20;  }
    NewDelta = (sint8) Delta;

    //find control row table
    RegRow = 0;
    while (NewDelta <= RAM_CTRL[RegRow].lim) {
        RegRow++;
    }
    
    //find error trend
    if (NewDelta < 0) {NewDelta = -NewDelta; }//ABS()
    if (NewDelta > OldDelta) { RegCol = 2;}
    else if (NewDelta < OldDelta) {  RegCol = 0; }
    else { RegCol = 1;}

    OldDelta = NewDelta;

    //load control change
    Delta = newPWM;
    Delta += RAM_CTRL[RegRow].de[RegCol];
    //limit pwm
    if (Delta > 100) { newPWM = 100; } 
    else if (Delta <= 0) { newPWM = 0; } 
    else if (0 == oldPwm) { newPWM = REG_PARAMS_RAM.StartPwm;}//start with min 50%
    else { newPWM = (uint8)Delta;}
    //in case of big overshoot decrease start pwm
    if ((RegRow > 4) && (REG_PARAMS_RAM.StartPwm > 20) && (0 == sFlags.bAdapt)) { 
        sFlags.bAdapt = 1;
        REG_PARAMS_RAM.StartPwm -= 5;  
    }
    if (RegRow < 4) { sFlags.bAdapt = 0;}
#endif
}

void REG_TaskSlow(void){
    if (startTime) {
        startTime--;
        Delta = AirS_GetTemp() - startTemp;
        if (Delta < 0) {
            Delta = -Delta;
        }
        if (Delta >= FORCE_OFF_DT){
            startTime = 0;//stop monitoring temp is changing!
        }
        else if (0 == startTime) {
           if (Delta < FORCE_OFF_DT) {
#ifndef REG_ON_OFF                
               //force off since no big rise of temp from 30 min
                //sFlags.bForceOff = TRUE;
                
#endif
            }
        }
    }
    
   //determine set temp change
    if ((oldSetTemp != PRG_GetSetTemp()) && (evalCntr > 1)){
        evalCntr = 1;
        if (AirS_GetTemp() > PRG_GetSetTemp()) {
            newPWM = 0;
        }
    }
    oldSetTemp = PRG_GetSetTemp();
    
   if (0 == evalCntr)   {
        evalCntr = REG_PARAMS_RAM.EvalTime;
        REG_FZLogic();
        if (sFlags.bForceOff) {
            newPWM = 0; //stop valve since no heating 
        }
#ifdef WINDOW_SENSOER_PRESENT
        if (WIN_IsOpen()){
            newPWM = 0;//force off due to open window
        }
#endif
        //heat off detection
        if ((newPWM > 5) && (0 == sFlags.bHeatDetStarted)) {
                sFlags.bHeatDetStarted = TRUE;
                startTemp = AirS_GetTemp();
                startTime = REG_HEAT_OFF_TIME;
        }
   }
   else {
       evalCntr--;
   }
    
    ComSendSignalImmediate(TxAct, newPWM);
   
}

uint8 REG_GetLevel(void){
    if (sFlags.bForceOff){
        return 255;
    }
    return newPWM;
}


