#include "types.h"
#include "svc_nvm.h"

uint8 RAM_NWID[5];
const uint8 ROM_NWID[NWDATA_LEN] = {122, 122, 108, 49, 254};

tNVMParam RAM_PARAM;
const tNVMParam ROM_PARAM = {200,3300,200,100};


tNVMPIR RAM_PIRDATA;
const tNVMPIR ROM_PIRDATA = {3,255, 255, 255, 255,3600,3600};


uint8 RAM_TEMPPROG[TEMPPROG_LEN];
uint8 RAM_TEMPPROG2[TEMPPROG_LEN];
const uint8 ROM_TEMPPROG[TEMPPROG_LEN] = {0,50,90,120,140,180,200,200,200,200,200,200,200,200};


uint8 RAM_TEMP_REGDATA[TEMP_REGDATA_LEN];
const uint8 ROM_TEMP_REGDATA[TEMP_REGDATA_LEN]= {255,255,255,255};