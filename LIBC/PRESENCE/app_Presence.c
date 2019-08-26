#include "types.h"
#include "drv_io.h"
#include "svc_nvm.h"
#include "svc_comm.h"
#include "app_Presence.h"
#include "app_RTC.h"

typedef enum{
    PRS_INIT,
    PRS_WAIT,
    PRS_ACTIVE, 
    PRS_ELAPSE, //300ms
    PRW_WAIT3S
}TPresState;

typedef struct {
    uint8 bRemotePresence:1;
    uint8 bTxFrame : 1;
}TPrsFlags;

static TPrsFlags pflags;

static TPresState ePrs; 
static uint8 PresenceOff;
uint16 PresenceTime;

void PRS_Init(void){
    PresenceTime = 20; 
    pflags.bRemotePresence = 0; 
    ePrs = PRS_INIT;
    ComSendSignal(TxPresence, 0);
}

uint8 PRS_RoomPresence(void){
    return (ePrs == PRS_ACTIVE);
}

static void ReloadTime(uint8 bLocal) {
    
    if (DateTime.Hours < 0x20 ) {
        PresenceTime = RAM_PIRDATA.PIR_TIME;
    }else {
        PresenceTime = RAM_PIRDATA.PIR_TIME_NIGHT;
    }
   //send frame  if enabled
   if ((bLocal & 1) && (RAM_PIRDATA.PIR_CTRL & 2) ) {
        ComSendSignalImmediate(TxPresence,1);
   }
}

static uint8 GetRIRLevel(void){
    if ((RAM_PIRDATA.PIR_CTRL & 2) && (IO_GetPIRLevel()))
    {
        return 1;
    }
    return 0;
}

void PRS_Task(void) {
    if (RAM_PIRDATA.PIR_CTRL & 1) {
        switch(ePrs)
        {
            case PRS_INIT:
                if (0 == PresenceTime) {
                    ePrs = PRS_WAIT;
                }
                break;
            case PRS_WAIT:
                if (GetRIRLevel()) {
                    ReloadTime(TRUE);
                    ePrs = PRS_ACTIVE;
                } else if (pflags.bRemotePresence ) {
                    pflags.bRemotePresence = FALSE;
                    ReloadTime(FALSE);
                    ePrs = PRS_ACTIVE;
                }
                break;
            case PRS_ACTIVE:
                if (GetRIRLevel()) {
                    ReloadTime(TRUE);
                }else if (pflags.bRemotePresence ) {
                    pflags.bRemotePresence = FALSE;
                    ReloadTime(FALSE);
                }
                if (0 == PresenceTime) {
                    PresenceOff = 15;//300ms dead window
                    ePrs = PRS_ELAPSE;
                }
                break;
            case PRS_ELAPSE:
                if (PresenceOff) {
                    PresenceOff--;
                } else {
                    if (GetRIRLevel()){
                        //active - could be noise from switch off relay
                        PresenceOff = 155;
                        ePrs = PRW_WAIT3S;
                    } else {
                        ePrs = PRS_WAIT;
                    }
                }
                break;
            case PRW_WAIT3S:
                if (PresenceOff) {
                    PresenceOff--;
                } else {
                    ePrs = PRS_WAIT;
                }
                break;
            default:
                ePrs = PRS_WAIT;    
                break;
          }
    }
    else {
        ePrs = PRS_ACTIVE; //if disable always presence
    }
}

void PRS_Task1s(void){
    if (RAM_PIRDATA.PIR_CTRL & 1) {
        if (PresenceTime) {
            PresenceTime--;
        }
        else {
            ComSendSignal(TxPresence, 0);
        }
    }
}

void PRS_OnPIRFrame(void) {
        
    //known NAD?
    if ((RxSRC_NAD() == RAM_PIRDATA.NAD1) ||
        (RxSRC_NAD() == RAM_PIRDATA.NAD2) ||
        (RxSRC_NAD() == RAM_PIRDATA.NAD3) ||
        (RxSRC_NAD() == RAM_PIRDATA.NAD4))    
    {
        if (0 != ComRecvSignal(uint8)){
            pflags.bRemotePresence = 1;
        }
    }
}
