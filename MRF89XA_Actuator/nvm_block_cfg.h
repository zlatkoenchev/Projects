/* 
 * File:   nvm_block_cfg.h
 * Author: zlatko
 *
 * Created on March 18, 2018, 6:57 PM
 */


#ifdef NVM_BLOCK
//        ID          len     RAM                    ROM        EEP addr   
NVM_BLOCK(NVM_NWDATA, NWDATA_LEN, &RAM_NWID[0], &ROM_NWID[0]  ,  NWDATA_ADDR,0)
NVM_BLOCK(NVM_TIMEPROG, TIMEPROG_LEN, &RAM_TIMEPROGRAM[0], &ROM_TIMEPROGRAM[0] , TIMEPROG_ADDR,0)
NVM_BLOCK(NVM_ACTMODE, ACTMODE_LEN, (__ram uint8 *)&RAM_ACTMODE, (__rom uint8 *)&ROM_ACTMODE, ACTMODE_ADDR,0)
NVM_BLOCK(NVM_PIRDATA, PIRDATA_LEN, (__ram uint8 *) &RAM_PIRDATA, (__rom uint8 *) & ROM_PIRDATA, PIRDATA_ADDR,0)
NVM_BLOCK(NVM_THERMO, THERMO_LEN, (__ram uint8 *) & RAM_THERMO, (__rom uint8 *) & ROM_THERMO, THERMO_ADDR,0)
NVM_BLOCK(NVM_RUNTIME, RUNTIME_LEN, (__ram uint8 *) & RAM_RUNTIME, (__rom uint8 *) & ROM_RUNTIME, RUNTIME_ADDR,0)
NVM_BLOCK(NVM_LOADPOWER, LOADPOWER_LEN, (__ram uint8 *) & RAM_LOADPOWER, (__rom uint8 *) & ROM_LOADPOWER, LOADPOWER_ADDR,0)
NVM_BLOCK(NVM_SWITCH, SWITCHDATA_LEN, (__ram uint8 *) & RAM_SWITCHDATA, (__rom uint8 *) & ROM_SWITCHDATA, SWITCHDATA_ADDR, 0)
NVM_BLOCK(NVM_TIMEPROG2, TIMEPROG_LEN, &RAM_TIMEPROGRAM2[0], &ROM_TIMEPROGRAM[0], TIMEPROG_ADDR2, 0)


#else

#define NWDATA_LEN 5
#define NWDATA_ADDR 0xF0
extern uint8 RAM_NWID[NWDATA_LEN];
extern const uint8 ROM_NWID[NWDATA_LEN];

#define TIMEPROG_LEN 12   //1 bit per 15min
#define TIMEPROG_ADDR 0
extern uint8 RAM_TIMEPROGRAM[TIMEPROG_LEN];
extern uint8 RAM_TIMEPROGRAM2[TIMEPROG_LEN];

extern const  uint8 ROM_TIMEPROGRAM[TIMEPROG_LEN];

typedef struct{
    uint8 byPROGPIRCMD;//
    uint8 ActType;
    uint8 PulseNum;
    uint8 PulseDelay;
    uint16 CMDTime;
    uint8 CtrlNAD;
}TActModeData;



#define ACTMODE_ADDR 20
#define ACTMODE_LEN 7

extern TActModeData RAM_ACTMODE;
extern const TActModeData ROM_ACTMODE;




#include "app_Presence.h"
#define PIRDATA_ADDR 30
#define PIRDATA_LEN  9
extern tNVMPIR RAM_PIRDATA;
extern const tNVMPIR ROM_PIRDATA;

typedef struct {
    uint8 DELAY;
    uint8 HOLD;
    uint8 RAMP;
    uint8 DOWN;
    uint8 PWM_OFF;
    uint8 PWM_ON;
    uint8 PWM_REG;
    uint8 PWM_PERIOD;
} TThermoData;

#define THERMO_ADDR 50
#define THERMO_LEN 8

extern TThermoData RAM_THERMO;
extern const TThermoData ROM_THERMO;

typedef struct {
    uint32 LoadEnergy1;
    uint32 LoadEnergy2;
} TRuntime;
#define RUNTIME_ADDR 60
#define RUNTIME_LEN 8
extern TRuntime RAM_RUNTIME;
extern const TRuntime ROM_RUNTIME;



typedef struct {
    uint16 LoadPower1;
    uint16 LoadPower2;
} TLoadPower;

extern TLoadPower RAM_LOADPOWER;
extern const TLoadPower ROM_LOADPOWER;

#define LOADPOWER_ADDR 70
#define LOADPOWER_LEN 4



typedef struct {
    uint8 Mode; //b0 - enabled
    uint8 CtrlNAD1;
    uint8 CtrlNAD2;
    uint8 CtrlNAD3;
    uint16 CMDTime;
} TSWData;
extern TSWData RAM_SWITCHDATA;
extern const TSWData ROM_SWITCHDATA;

#define SWITCHDATA_ADDR 80
#define SWITCHDATA_LEN 6


#define TIMEPROG_ADDR2 100

#endif


