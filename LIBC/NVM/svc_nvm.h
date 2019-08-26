#ifndef SVC_NVM_H
#define SVC_NVM_H

//defines inclusion
#undef NVM_BLOCK
#include "nvm_block_cfg.h"

//block IDs generation
#undef NVM_BLOCK
#define NVM_BLOCK(a,b,c,d,e,f) a,
typedef enum {
 #include "nvm_block_cfg.h"
    NVM_NUM_BLOCKS
}tNVM_BlockID;

//enable difference check before write
#define DIFF_CHECK

//#define NVM_DATASET


extern uint8 NVM_BlockStatus[NVM_NUM_BLOCKS];

void NVM_Init(void);

void NVM_Task(void);

#define NVM_IsBlockRead(x) (NVM_BlockStatus[x] & 0x01)
#define NVM_IsBlockCSErr(x) (NVM_BlockStatus[x] & 0x02)
#define NVM_IsBlockWrite(x) (NVM_BlockStatus[x] & 0x04)

uint8 NVM_IsIdle(void);

void NVM_ReadBlock(uint8 BlockIndex);

void NVM_WriteBlock(uint8 BlockIndex);

#ifdef NVM_DATASET
uint8 NVM_SetDataIndex(uint8 Block, uint8 Ds);
uint8 NVM_GetDataIndex(uint8 Block);
#endif

uint8 NVM_ReadBlockData(uint8 Block, uint8 offset);

uint8 NVM_WriteBlockData(uint8 Block, uint8 offset, uint8 data);

uint8 NVM_GetBlockLenght(uint8 Block);

#endif