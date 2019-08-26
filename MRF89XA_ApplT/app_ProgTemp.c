#include "types.h"
#include "app_ProgTemp.h"
#include "app_RTC.h"
#include "svc_nvm.h"
#include "drv_io.h"
#include "app_Presence.h"
#include "app_RTC.h"

#define DEFAULT_TEMP_PRESENCE RAM_PARAM.C_DEF_TEMP_PR
#define DEFAULT_TEMP_NOPRESENCE RAM_PARAM.C_DEF_TEMP_NOPR
#define C_DELAY_NVM 10
#define TEMP_POINTS 7

typedef enum{
    PRG_NOPRESENCE,
    PRG_DEF_PRESENCE,
    PRG_PRESENCE
}TPRGMode;

static uint8 nvblock;
static uint8 nvpos;
sint16 ProgSetTemp;
static TPRGMode c_mode;
static uint8 bWriteNvm;

static void DetermineProg(void) {
    
    uint8 ix;
    uint8 ctime;

    if (DateTime.DOW > 5) { 
        nvblock = NVM_TEMPPROG2;
    }
    else {
        nvblock = NVM_TEMPPROG;
    }
    
    ctime = RTC_TimeToNumber();
    ix = 7;
    while (ix) { 
          ix--;
          if (ctime >= NVM_ReadBlockData(nvblock,ix)) {
              nvpos = TEMP_POINTS + ix;
              ProgSetTemp = NVM_ReadBlockData( nvblock, nvpos);
              return;
          }
    } 
}

void PRG_Init(void) {
    ProgSetTemp = DEFAULT_TEMP_NOPRESENCE;
    c_mode = PRG_NOPRESENCE;
    bWriteNvm = nvpos = 0;
}

static void DetermineMode(void){
    
    if (PRS_RoomPresence()) {
        if (RTC_IsTimeOk()) {
           c_mode = PRG_PRESENCE;
           DetermineProg();
        } else {
            ProgSetTemp = DEFAULT_TEMP_PRESENCE;
            c_mode = PRG_DEF_PRESENCE;
            nvblock = NVM_PARAM;
        }
    } else {
        ProgSetTemp = DEFAULT_TEMP_NOPRESENCE;
        c_mode = PRG_NOPRESENCE;
        nvblock = NVM_PARAM;
    }
}

void PRG_TaskSlow(void){
    DetermineMode();
    if (bWriteNvm)     {
        bWriteNvm--;
        if (0 == bWriteNvm) {
            NVM_WriteBlock(nvblock);
        }
    }
}

void PRG_SetNewTemp(sint8 sIncrease) {
    
    ProgSetTemp += sIncrease;
    
    switch (c_mode) {
        case PRG_PRESENCE:
            NVM_WriteBlockData(nvblock, nvpos, ((uint8) ProgSetTemp));              
            break;

        case PRG_DEF_PRESENCE:
            DEFAULT_TEMP_PRESENCE = (uint8)ProgSetTemp;
            break;

        default:
            DEFAULT_TEMP_NOPRESENCE=(uint8)ProgSetTemp;
            break;
    }
    bWriteNvm = C_DELAY_NVM;
}

        