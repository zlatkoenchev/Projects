#include "types.h"
#include "app_control.h"
#include "drv_io.h"
#include "svc_comm.h"
#include "svc_nvm.h"
#include "drv_relay.h"
#include "app_prog.h"
#include "drv_Si7021.h"

static uint8 cmd;
static uint16 cmdtimer;

#define HOUR_TICKS 3600
#define REG_EVAL_PERIOD 30 //30sec




void CTRL_Init(void){ 
  
    cmd = cmdtimer = 0;
}

static uint8 CTRL_CheckProgPIR(void){
    uint8 bres = FALSE;
    
    if (RAM_ACTMODE.byPROGPIRCMD & ACT_MODE_BY_PIR)     {
        bres = PRS_RoomPresence();
        
        if (RAM_ACTMODE.byPROGPIRCMD & ACT_MODE_BY_PRG) {
            bres &= PRG_IsOnTime();
        }
    }
    else if (RAM_ACTMODE.byPROGPIRCMD & ACT_MODE_BY_PRG) {
        bres = PRG_IsOnTime();
    }
            
    return bres;
}

void CTRL_Task(void) {
    
    if ((RAM_ACTMODE.byPROGPIRCMD & ACT_BODE_BY_CMD) || (cmdtimer != 0))     {
        //command active or diag mode
        if (RAM_ACTMODE.byPROGPIRCMD & ACT_MODE_BY_PRG) {
             if (0 == PRG_IsOnTime()){
                 cmd = 0;
             }
        }
    }
    else if (CTRL_CheckProgPIR())    {
        cmd = 100;// inlocal mode only max is possible
    }
    else {
        cmd = 0;
    }
    Rel_Request(cmd);
}

void CTRL_Task1s(void){
    if (cmdtimer)   {
        cmdtimer--;
        if (0 == cmdtimer){
            cmd = 0;
        }
    }
#ifdef Si7021_PRESENT
    if (RAM_ACTMODE.byPROGPIRCMD & ACT_MODE_Si7021) {
        ComSendSignal(TxTemp1, Si7021_GetTemp());
        ComSendSignal(TxHumidity, Si7021_GetHum());
    }
#endif
    ComSendSignalImmediate(TxAct,  Rel_IsOn());
}

void CTRL_DiagCtrl(uint8 c) {
   
    if (ACT_TYPE_PWM == RAM_ACTMODE.ActType)   {
        cmdtimer = 4000;//quite long time
    }
    else {
        cmdtimer = 10;
    }
    cmd = c;
}

void CTRL_OnACTSignal(void) {
    if (RAM_ACTMODE.CtrlNAD == RxSRC_NAD()) {
        cmd = ComRecvSignal(uint8);
        cmdtimer = RAM_ACTMODE.CMDTime;
    }
}

void CTRL_OnSWSignal(void){
    //uint8 sw;
    if (RAM_SWITCHDATA.Mode & 1) {
        if ((RAM_SWITCHDATA.CtrlNAD1 == RxSRC_NAD()) ||
            (RAM_SWITCHDATA.CtrlNAD2 == RxSRC_NAD()) ||
            (RAM_SWITCHDATA.CtrlNAD3 == RxSRC_NAD()))    
        {
            //sw = ;
            switch (ComRecvSignal(uint8))
            {
                case 0://off
                    cmd = cmdtimer = 0;
                    break;
                case 1://on
                    cmdtimer = RAM_SWITCHDATA.CMDTime;
                    cmd = 100;
                    break;
                case 2://toggle
                    if (cmd) { 
                        cmd = cmdtimer = 0;
                    } else {
                        cmdtimer = RAM_SWITCHDATA.CMDTime;
                        cmd = 100;
                    };
                    break;
                    
                default:
                    break;
            }
        }
    }
}
