/* 
 * File:   nvm_block_cfg.h
 * Author: zlatko
 *
 * Created on March 18, 2018, 6:57 PM
 */


#ifdef NVM_BLOCK
//        ID          len RAM     ROM  EEP addr   
NVM_BLOCK(NVM_NWDATA, NWDATA_LEN, &RAM_NWID[0], ROM_NWID  ,  NWDATA_ADDR,0)
NVM_BLOCK(NVM_PARAM, PARAM_LEN, (__ram uint8 *)&RAM_PARAM, (__rom uint8 *)&ROM_PARAM  ,  PARAM_ADDR,0)
NVM_BLOCK(NVM_PIRDATA, PIRDATA_LEN, (__ram uint8 *)&RAM_PIRDATA, (__rom uint8 *) &ROM_PIRDATA, PIRDATA_ADDR,0)
NVM_BLOCK(NVM_RUNTIME, RUNTIME_LEN, (__ram uint8 *)&RAM_RUNTIME, (__rom uint8 *)&ROM_RUNTIME, RUNTIME_ADDR,0)


#else

#define NWDATA_LEN 5
#define NWDATA_ADDR 0xF0
extern uint8 RAM_NWID[NWDATA_LEN];
extern const uint8 ROM_NWID[NWDATA_LEN];

typedef struct {
    uint8 C_TEMP_OFFS;
    uint8 C_TEMP_GAIN;
    uint8 C_DEF_TEMP_PR; 
    uint8 C_DEF_TEMP_NOPR;
    
} tNVMParam;

#define PARAM_LEN 4
#define PARAM_ADDR 0
extern tNVMParam RAM_PARAM;
extern const tNVMParam ROM_PARAM;


#include "app_Presence.h"
#define PIRDATA_ADDR 10
#define PIRDATA_LEN 9
extern tNVMPIR RAM_PIRDATA;
extern const tNVMPIR ROM_PIRDATA;


#define TEMPPROG_ADDR 20
#define TEMPPROG_LEN  14
extern uint8 RAM_TEMPPROG[TEMPPROG_LEN];
extern const uint8 ROM_TEMPPROG[TEMPPROG_LEN];

#define ACTNAD_ADDR 30
#define ACTNAD_LEN 2
extern uint8 RAM_ACTNAD[ACTNAD_LEN];
extern const uint8 ROM_ACTNAD[ACTNAD_LEN];


typedef struct {
    uint32 LoadEnergy1;
    uint32 LoadEnergy2;
} TRuntime;
#define RUNTIME_ADDR 40
#define RUNTIME_LEN 8
extern TRuntime RAM_RUNTIME;
extern const TRuntime ROM_RUNTIME;

#endif


