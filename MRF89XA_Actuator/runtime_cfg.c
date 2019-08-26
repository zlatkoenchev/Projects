#include "types.h"
#include "svc_nvm.h"
#include "drv_relay.h"
#include "runtime_cfg.h"


TLoadPower RAM_LOADPOWER;
const TLoadPower ROM_LOADPOWER = {0, 0};


uint16 Rtn_GetLoad1Power(void){
    if (Rel_IsOn()) {
        return RAM_LOADPOWER.LoadPower1;
    }
    return 0;
}

uint16 Rtn_GetLoad2Power(void){
    return 0;
}


