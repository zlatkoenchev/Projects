#include "types.h"
#include "svc_nvm.h"

uint8 RAM_NWID[5];
const uint8 ROM_NWID[NWDATA_LEN] = {122, 122, 108, 49, 254 };



tNVMParam RAM_PARAM;
const tNVMParam ROM_PARAM = {0xC9,198,200,100};


tNVMPIR RAM_PIRDATA;
const tNVMPIR ROM_PIRDATA = {1,255, 255, 255, 255,65000};


