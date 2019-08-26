#include "types.h"
#include "svc_nvm.h"

uint8 RAM_NWID[NWDATA_LEN];
const uint8 ROM_NWID[NWDATA_LEN] = {122, 122, 108, 49, 254};

uint8 RAM_TIMEPROGRAM[TIMEPROG_LEN];
uint8 RAM_TIMEPROGRAM2[TIMEPROG_LEN];
const uint8 ROM_TIMEPROGRAM[TIMEPROG_LEN] = {0,0,0,0, 0,0,0,0, 0, 0, 0, 0};

TActModeData RAM_ACTMODE;
const TActModeData ROM_ACTMODE = {4,0,3,62,0,255};

tNVMPIR RAM_PIRDATA;
const tNVMPIR ROM_PIRDATA = {0, 255, 255, 255, 255, 60,60};


TThermoData RAM_THERMO;
const TThermoData ROM_THERMO = {
    100, //DELAY
    80, //HOLD not used
    60, //RAMP not used
    4, //DOWN 
    5, //PWM OFF
    10, //PWM ON
    80, //PWM REGULATE not used
    25}; //PWM_PERIOD not used


TSWData RAM_SWITCHDATA;
const TSWData ROM_SWITCHDATA = {0,255,255,255,180};