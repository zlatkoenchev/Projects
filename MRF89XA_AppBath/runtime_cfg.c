#include "types.h"
#include "svc_nvm.h"
#include "app_bath.h"
#include "runtime_cfg.h"
#include "drv_fan.h"


//fan power
uint16 Rtn_GetLoad1Power(void){
    if (FAN_HI == FanDrv_GetState()) {
        return 18;
    } else if (FAN_LOW == FanDrv_GetState()) 
    {
        return 9;
    }
    return 0;
}

//heater state
uint16 Rtn_GetLoad2Power(void){
    
    if ( HTR_100P == App_GetHtrState()){
        return 1200;
    } else if ((HTR_REG1 == App_GetHtrState()) || (HTR_REG2 == App_GetHtrState())){
        return 600;
    }
    return 0;
}


