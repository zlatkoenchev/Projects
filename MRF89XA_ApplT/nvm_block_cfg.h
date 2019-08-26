/* 
 * File:   nvm_block_cfg.h
 * Author: zlatko
 *
 * Created on March 18, 2018, 6:57 PM
 */


#ifdef NVM_BLOCK
//        ID          len RAM     ROM  EEP addr   
NVM_BLOCK(NVM_NWDATA, NWDATA_LEN, &RAM_NWID[0], &ROM_NWID[0]  ,  NWDATA_ADDR,1)
NVM_BLOCK(NVM_PARAM, PARAM_LEN, (__ram uint8 *)&RAM_PARAM, (__rom uint8 *)&ROM_PARAM  ,  PARAM_ADDR,1)
NVM_BLOCK(NVM_PIRDATA, PIRDATA_LEN, (__ram uint8 *)&RAM_PIRDATA, (__rom uint8 *) &ROM_PIRDATA, PIRDATA_ADDR,1)
NVM_BLOCK(NVM_TEMPPROG, TEMPPROG_LEN, &RAM_TEMPPROG[0], &ROM_TEMPPROG[0], TEMPPROG_ADDR,7)
NVM_BLOCK(NVM_TEMPPROG2, TEMPPROG_LEN, &RAM_TEMPPROG2[0], &ROM_TEMPPROG[0], TEMPPROG_ADDR2, 7)
NVM_BLOCK(NVM_ACTNAD, TEMP_REGDATA_LEN, &RAM_TEMP_REGDATA[0], &ROM_TEMP_REGDATA[0], TEMP_REGDATA_ADDR,1)
NVM_BLOCK(NVM_TEMPHISTORY, TEMP_HIST_LEN, &TEMP_HISTORY[0], 0, TEMP_HISTORY_ADDR, 1)
NVM_BLOCK(NVM_TEMPCTRL, TEMP_CTRL_LEN, &RAM_CTRL[0], &ROM_CRTRL[0], TEMP_CTRL_ADDR, 1)
NVM_BLOCK(NVM_TEMPPAR, TEMP_PAR_LEN, &REG_PARAMS_RAM, &REG_PARAMS_ROM, TEMP_PAR_ADDR, 1)


#else

#define NWDATA_LEN 5
#define NWDATA_ADDR 0xF0
extern uint8 RAM_NWID[NWDATA_LEN];
extern const uint8 ROM_NWID[NWDATA_LEN];
typedef struct {
    uint8 C_TEMP_OFFS; //adc units
    uint16 C_TEMP_GAIN; //gain 
    uint8 C_DEF_TEMP_PR; 
    uint8 C_DEF_TEMP_NOPR;
    
} tNVMParam;

#define PARAM_LEN 5
#define PARAM_ADDR 0
extern tNVMParam RAM_PARAM;
extern const tNVMParam ROM_PARAM;



#include "app_Presence.h"
#define PIRDATA_ADDR 10
extern tNVMPIR RAM_PIRDATA;
extern const tNVMPIR ROM_PIRDATA;
#define PIRDATA_LEN 9

#define TEMPPROG_ADDR 20
#define TEMPPROG_LEN  14 //dtaset block
extern uint8 RAM_TEMPPROG[TEMPPROG_LEN];
extern const uint8 ROM_TEMPPROG[TEMPPROG_LEN];
#define TEMPPROG_ADDR2 40
extern uint8 RAM_TEMPPROG2[TEMPPROG_LEN];

extern uint8 TEMP_HISTORY[24];
#define TEMP_HISTORY_ADDR 60
#define TEMP_HIST_LEN 24

#define TEMP_REGDATA_ADDR 140
#define TEMP_REGDATA_LEN 4
extern uint8 RAM_TEMP_REGDATA[TEMP_REGDATA_LEN];
extern const uint8 ROM_TEMP_REGDATA[TEMP_REGDATA_LEN];//byte 0,1 actuator NADs, byte 2,3 Sensor nads

#include "app_TempReg.h"
#define TEMP_CTRL_ADDR 150
#define TEMP_CTRL_LEN 28

#define TEMP_PAR_ADDR 180
#define TEMP_PAR_LEN 4

#endif

