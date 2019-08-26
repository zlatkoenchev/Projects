/* 
 * File:   nvm_block_cfg.h
 * Author: zlatko
 *
 * Created on March 18, 2018, 6:57 PM
 */


#ifdef NVM_BLOCK
//        ID          len     RAM                    ROM        EEP addr   
NVM_BLOCK(NVM_NWDATA, NWDATA_LEN, &RAM_NWID[0], &ROM_NWID[0]  ,  NWDATA_ADDR,0)

#else

#define NWDATA_LEN 5
#define NWDATA_ADDR 0xF0
extern uint8 RAM_NWID[NWDATA_LEN];
extern const uint8 ROM_NWID[NWDATA_LEN];


#endif


