#include "types.h"
#include "svc_nvm.h"
#include "svc_comm.h"
#include "runtime_cfg.h"


TRuntime RAM_RUNTIME;
const TRuntime ROM_RUNTIME = {0, 0};

void Rnt_Init(void) {
   
}

void Rnt_Task1Sec(void){
    RAM_RUNTIME.LoadEnergy1 += Rtn_GetLoad1Power();//1w/s resolution
    RAM_RUNTIME.LoadEnergy2 += Rtn_GetLoad2Power(); //1w/s resolutio
  
    ComSendSignal(Energy1, RAM_RUNTIME.LoadEnergy1);
    ComSendSignal(Energy2, RAM_RUNTIME.LoadEnergy2);
}


void Rut_OnClearPower(void){
    RAM_RUNTIME.LoadEnergy1 = 0;
    RAM_RUNTIME.LoadEnergy2 = 0;
}
