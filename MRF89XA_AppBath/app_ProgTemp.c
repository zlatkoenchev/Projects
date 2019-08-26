#include "types.h"
#include "app_ProgTemp.h"
#include "app_RTC.h"
#include "svc_nvm.h"
#include "drv_io.h"
#include "app_Presence.h"

#define DEFAULT_TEMP_PRESENCE RAM_PARAM.C_DEF_TEMP_PR
#define DEFAULT_TEMP_NOPRESENCE RAM_PARAM.C_DEF_TEMP_NOPR
#define C_DELAY_NVM 10
#define TEMP_POINTS 7

typedef enum{
    PRG_NOPRESENCE,
    PRG_DEF_PRESENCE,
    PRG_PRESENCE
}TPRGMode;

sint16 ProgSetTemp;
static uint8 c_range;
static TPRGMode c_mode;
static uint8 bWriteNvm;





static void DetermineProg(void) {
    
}

//0.2C resolution
static uint8 GetProgTemp(void){
    
    return DEFAULT_TEMP_PRESENCE;
}

void PRG_Init(void) {
  
}

static void DetermineMode(void){
    
    
}

void PRG_TaskSlow(void){
    
   
   
}

void PRG_SetNewTemp(uint8 bIncrease) {
   
    
}

        