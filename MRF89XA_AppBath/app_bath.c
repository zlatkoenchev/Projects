#include "types.h"
#include "app_bath.h"
#include "drv_io.h"
#include "drv_temp.h"
#include "drv_fan.h"
#include "main.h"
#include "app_Presence.h"
#include "svc_comm.h"
#include "nvm_block_cfg.h"

#define I_SWR_ON  10
#define I_SWR_OFF  7
#define T_FAN_ONT  DEG_01C(250)
#define T_DHM_ON   DEG_01C(230)
#define T_HTR_ON   DEG_01C(235)
#define T_HTR_OFF  DEG_01C(235)
#define T_SHWR_OFF DEG_01C(300)
#define T_SHWR_ON  DEG_01C(325)
#define T_MAX      DEG_01C(990)
#define HTR_MAX_TIME_MIN 40 /*40 min*/
#define T_TIME20s  OS_TIME_MS(20000)
#define T_TIME15m  OS_TIME_MS(900000)

#define FAN_CTL_ON  225 /*1.1V*/
#define FAN_CTL_OFF 205 /*1V*/

#define POWER_OFF_TIME 100 /*2 sec*/

#define FAN_FLUSH_TIME 180 /*3h*/


typedef enum{
	B_NO,
	B_WAIT_ON,
	B_YES_CONS,
    B_YES_TEMP,        
    B_WAIT_OFF,
	B_WAIT_T
}TBath;	 

typedef enum {
    LM_OFF,
    LM_WAIT20S,
    LM_ON,
    LM_OFF_WAIT,
    LM_OFF_POWER
} TLamp;

typedef struct{
	TBath eShower;
	uint16 bathTimer;
        uint8 bShower:1;
        uint8 bFanCtl:1;
        uint8 bFanSw:1;
        uint8 bFanCtl_Old:1;
        uint8 bFanSw_Old:1;
        uint8 bWTempRise:1;
        uint8 bWTempFall:1;
        
    
}TApp;	

 TApp sapp;
static TLamp eLamp;
THtr eHtr ;
static uint8 u8Htr_on;
static uint8 u8Htr_time;
static uint8 u8Fan_time;
static uint8 u8Startup; 
static uint8 u8DHM_time;
static uint8 u8OldTW;
static uint16 u16LampTmr;
static void App_OnShowerON(void);
static void App_OnShowerOFF(void);
//////////////////////////////////////////
static void App_Lamp(void) {
    uint8 bTempW = TempDrv_GetWater();
    switch (eLamp)
    {
        case LM_OFF:
            if (IOGetADCFilt(Ai_Consmp) > I_SWR_ON) {
               eLamp = LM_WAIT20S;
               u16LampTmr = T_TIME20s;
            }
            break;
            
        case LM_WAIT20S:
            if (IOGetADCFilt(Ai_Consmp) < I_SWR_OFF) {
               eLamp = LM_OFF; 
            } else if (u16LampTmr) {
                u16LampTmr--;
            } else {
                eLamp = LM_ON;
                u16LampTmr = T_TIME15m;
            }
            break;
            
        case LM_ON:   
            if (IOGetADCFilt(Ai_Consmp) < I_SWR_OFF) {
                eLamp = LM_OFF_WAIT;
                u16LampTmr = LM_WAIT20S; //consm drop
            }
            else if (u16LampTmr) {
                u16LampTmr--;
            } else if ((bTempW < T_SHWR_OFF) || (bTempW == T_MAX)) {
                eLamp = LM_OFF_POWER;
                IO_SetOut(Do_POWER, 1); //15 min elapsed , but temp is low or invalid, stop lamp
                u16LampTmr = 100; //2sec
            }
            break;
            
        case LM_OFF_WAIT:
            if (IOGetADCFilt(Ai_Consmp) > I_SWR_ON) {
                eLamp = LM_ON; //back to on, but not reload timer
            } else if (u16LampTmr) {
                u16LampTmr--;//20 sec debounce
            } else {
                eLamp = LM_OFF_POWER;
                IO_SetOut(Do_POWER, 1); //switch off power to prevent lamp forever on
                u16LampTmr = 100; //2sec
            }
            break;
            
        case LM_OFF_POWER:
            if (u16LampTmr) {
                u16LampTmr--;
            } else {
                eLamp = LM_OFF;
                IO_SetOut(Do_POWER, 0); //turn back power
            }
            break;
            
        default:
            eLamp = LM_OFF;
            break;
    }
}
//////////////////////////////////////////
static void App_FanCtrl(void) {
	uint8 bReq = 0;
	
	//light fan switch
	if ((sapp.bFanSw) && (0 == sapp.bFanSw_Old ))
	{
		bReq = 1;
        u8Fan_time = FAN_FLUSH_TIME;
	}	
	//shower fan ctrl
	if (sapp.bFanCtl != sapp.bFanCtl_Old )
	{
		bReq = 1;
        u8Fan_time = FAN_FLUSH_TIME;
	}
	
	if (bReq)
	{
		switch (FanDrv_GetState())
		{
			case FAN_OFF:
				FanDrv_ReqHi(20);
				break;
			case FAN_START:
			case FAN_HI:
				FanDrv_ForceLow(20);
				break;
			default:
				FanDrv_ForceOff();
				break;
		}
	}	
}	
//////////////////////////////////////////
static void App_Htr(void) {
	switch (eHtr)
	{
		case HTR_OFF:
			IO_SetOut(Do_HTR1,0);
			IO_SetOut(Do_HTR2,0);
			if ((sapp.bShower) && (TempDrv_GetAir() < T_HTR_ON))
			{
				eHtr = HTR_100P;
				u8Htr_time = 10;//10 min preheat
				u8Htr_on = 0;
				IO_SetOut(Do_HTR1,1);//activate heaters with distance 20ms
			}	
		break;
		case HTR_100P:
		    IO_SetOut(Do_HTR1,1);
			IO_SetOut(Do_HTR2,1);
			if (!sapp.bShower) 
			{
				eHtr = HTR_OFF;
			}
			else if (0 == u8Htr_time)
			{
				eHtr = HTR_REG1;
				u8Htr_time = 2;//10 min
			} 
			else if ((TempDrv_GetAir() > T_HTR_OFF)&& (u8Htr_time < 6))
			{
				eHtr = HTR_WAIT;
				u8Htr_on = 0;
				u8Htr_time = 60;//wait 1hrs before new heating
			}		
		break;
		case HTR_REG1:
			IO_SetOut(Do_HTR1,1);
			IO_SetOut(Do_HTR2,0);
			if ((0 == sapp.bShower) ||  
				(TempDrv_GetAir() > T_HTR_OFF) ||
				(u8Htr_on > HTR_MAX_TIME_MIN))
			{
				eHtr = HTR_WAIT;
				u8Htr_on = 0;
				u8Htr_time = 60;//wait 1hrs before new heating
			}
			if (0 == u8Htr_time)
			{
				eHtr = HTR_REG2;
				u8Htr_time = 2;//each 2 min turn on/off each heater
				IO_SetOut(Do_HTR1,0);
			}	
		break;
		case HTR_REG2:
			IO_SetOut(Do_HTR1,0);
			IO_SetOut(Do_HTR2,1);
			if ((0 == sapp.bShower) ||  
				(TempDrv_GetAir() > T_HTR_OFF) ||
                (u8Htr_on > HTR_MAX_TIME_MIN))
			{
				eHtr = HTR_WAIT;
				u8Htr_on = 0;
				u8Htr_time = 60;//wait 1hrs before new heating
			}
			else if (0 == u8Htr_time)
			{
				eHtr = HTR_REG1;
				u8Htr_time = 2;//2 min
				IO_SetOut(Do_HTR2,0);
			}
		break;
		case HTR_WAIT:
			IO_SetOut(Do_HTR1,0);
			IO_SetOut(Do_HTR2,0);
			if ((0 == u8Htr_time) && (0 == sapp.bShower))
			{
				eHtr = HTR_OFF;//permit new heating on next shower
			}
		break;
		default:
			eHtr = HTR_OFF;
		break;
	}	
}
//////////////////////////////////////////
static void App_ProcFanSw(void) {
	if ( IOGetDio(Di_FanPanelBu) )
	{
		sapp.bFanCtl = 1;
	}	
	else 
	{
		sapp.bFanCtl = 0;
	}	
	if ( IOGetDio(Di_FanLightSw) )
	{
		sapp.bFanSw = 1;
	}	
	else 
	{
		sapp.bFanSw = 0;
	}	
}
//////////////////////////////////////////
static void App_ProcBath(void) {
    uint8 bTempW = TempDrv_GetWater();
    uint8 bBathDetC = (uint8)(IOGetADCFilt(Ai_Consmp) > I_SWR_ON);
    uint8 bBathNotDetC = (uint8) (IOGetADCFilt(Ai_Consmp) < I_SWR_OFF);
    uint8 bBathDetT = 0;
    uint8 bBathNotDetT = 0;
    
    if (bTempW < T_MAX) {
        bBathDetT = (uint8) (bTempW > T_SHWR_ON);
        bBathNotDetT = (uint8) (bTempW < T_SHWR_OFF);
        
        if (bTempW > u8OldTW) {
            sapp.bWTempRise = 1;
            sapp.bWTempFall = 0;
        } else if (bTempW < u8OldTW) {
            sapp.bWTempFall = 1;
            sapp.bWTempRise = 0;
        }
    } 
    
    
    
	switch (sapp.eShower)
	{
		case B_NO:
			if (bBathDetC )	{
				sapp.bathTimer = T_TIME20s;
                sapp.eShower = B_WAIT_ON;
			} else if (bBathDetT){
                sapp.bShower = 1;
                App_OnShowerON();
                sapp.eShower = B_YES_TEMP;
            } else {
                sapp.bShower = 0;
            }
			break;
		
		case B_WAIT_ON:
			if (bBathNotDetC ) {
				sapp.eShower = B_NO;
        	}
			else if (sapp.bathTimer) {
                sapp.bathTimer--;
            } else {
                sapp.bShower = 1;
                App_OnShowerON();
                sapp.eShower = B_YES_CONS;
            }	
			break;
			
		case B_YES_CONS:
			if (bBathNotDetC) 	{
				sapp.bathTimer = T_TIME20s;
                sapp.eShower = B_WAIT_OFF;
			}	
		break;

        case B_YES_TEMP:
            if (bBathDetC) {
                sapp.eShower = B_YES_CONS;//by lamp
            } else if (bBathNotDetT) {
                sapp.bShower = 0;
                App_OnShowerOFF();
                sapp.eShower = B_WAIT_T;
            }
            break;
		case B_WAIT_OFF:
            if (bBathDetC) {
                sapp.eShower = B_YES_CONS;
            } else if (sapp.bathTimer) {
                sapp.bathTimer--;
            } else {
                sapp.bShower = 0;
                App_OnShowerOFF();
                sapp.eShower = B_WAIT_T;
            }
		break;
		//wait until temp get lower to prevent double bath detection
        case  B_WAIT_T:
            if ((bTempW == T_MAX) || (bBathNotDetT)) {
                sapp.eShower = B_NO;
            }
        break;    
		default:
			sapp.eShower = B_NO;
		break;
    }

   
   u8OldTW = bTempW;
}	
//////////////////////////////////////////
static void App_OnShowerOFF(void){
    
}
//////////////////////////////////////////
static void App_OnShowerON(void){
	uint8 ta = TempDrv_GetAir();
    if (T_FAN_ONT <= ta )
    {
        ta -= T_FAN_ONT;
        ta * = 5;
        if (ta > 50) {
            ta = 50;
        }
        ta = (uint8) (100-ta);
    }
    else {
       ta = 100; 
    }
    FanDrv_ReqLow(ta); //100min	
}	
//////////////////////////////////////////
static void App_DHM(void) {
	if (u8DHM_time)
	{
		IO_SetOut(Do_DHM,1);
	}	
	else
	{
		IO_SetOut(Do_DHM,0);
	}	
}	 
//////////////////////////////////////////
//activates FAN for 5 min every 2 hours
static void App_FanFlush(void) {
	if (0 != sapp.bShower)
	{
		u8Fan_time = FAN_FLUSH_TIME;//during shower restart flush timer
	}	
	
	if (0 == u8Fan_time)
	{
		u8Fan_time = FAN_FLUSH_TIME;
        if (PRS_RoomPresence())
        {
            FanDrv_ReqLow(5);
        }
	}
}	
//////////////////////////////////////////
void App_Init(void){
	eHtr = HTR_OFF;
	u8Htr_on = 0;
	u8Htr_time = 0;
    eLamp = LM_OFF;
    sapp.bShower =0;
    sapp.bFanCtl = 0;
    sapp.bFanSw = 0;
    sapp.bFanCtl_Old = 0;
    sapp.bFanSw_Old = 0;
    
    sapp.bWTempRise = 0;
    sapp.bWTempFall = 0;
     
	sapp.eShower = B_NO;
	u8Fan_time = FAN_FLUSH_TIME;
	u8Startup = 200; //tasks to set temperature
	u8DHM_time = 0;
    u8OldTW = 0;
}
//////////////////////////////////////////
void App_Task(void) {
	App_ProcFanSw();
	if (u8Startup)	{
		u8Startup--;
	}	
	else
	{
		App_ProcBath();
		App_FanFlush();
		App_FanCtrl();
        App_Lamp();
		App_Htr();
		App_DHM();
	}
	sapp.bFanCtl_Old = sapp.bFanCtl;
	sapp.bFanSw_Old	 = sapp.bFanSw;
    
}
//////////////////////////////////////////
uint8 App_HTPw(void){
    if (eHtr == HTR_100P) {
        return 2;
    } else if ((eHtr == HTR_REG1) || (eHtr == HTR_REG2)){
        return 1;
    } else {return 0;}
}
//////////////////////////////////////////
void App_Task1s(void){
    
    ComSendSignal(TxTemp1, (((uint16) TempDrv_GetAir())*5));
    ComSendSignal(TxTemp2, (((uint16) TempDrv_GetWater()) * 5));
    ComSendSignal(TxHTPower, App_HTPw());
    ComSendSignal(TxBath, sapp.eShower);
    ComSendSignal(TxFan, FanDrv_GetState());
   
}
//////////////////////////////////////////
void App_Task1Min(void) {
	//handle  timers
	if (eHtr != HTR_OFF){
		if (u8Htr_on < 255)
		{
			u8Htr_on++;
		}		
	}
	if (u8Htr_time)
	{
		u8Htr_time--;
	}
	if (u8Fan_time)
	{
		u8Fan_time--;
	}
	if (u8DHM_time)
	{
		u8DHM_time--;
	}
    
}
//////////////////////////////////////////
uint8 App_GetShower(void) {
	return sapp.bShower ;
}
//////////////////////////////////////////
uint8 App_GetBathState(void){
    return sapp.eShower;
}
//////////////////////////////////////////
uint8 App_GetLampState( void) { 
    return eLamp;
}
