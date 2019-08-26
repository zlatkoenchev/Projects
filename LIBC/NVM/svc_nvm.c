#include "types.h"
#include "svc_nvm.h"
#include "drv_eep.h"


#undef NVM_BLOCK
#define NVM_BLOCK(a,b,c,d,e,f) b,
const uint8 NVM_BlockSize[NVM_NUM_BLOCKS]=
{
#include "nvm_block_cfg.h"
};

#undef NVM_BLOCK
#define NVM_BLOCK(a,b,c,d, e,f) e,
const uint8 NVM_BlockAddr[NVM_NUM_BLOCKS] ={
#include "nvm_block_cfg.h"
};

#undef NVM_BLOCK
#define NVM_BLOCK(a,b,c,d ,e,f) c,
__ram uint8  * const NVM_BlockRAM[NVM_NUM_BLOCKS] = {
#include "nvm_block_cfg.h"
};

#undef NVM_BLOCK
#define NVM_BLOCK(a,b,c,d ,e,f) d,
const __rom uint8   * const NVM_BlockROM[NVM_NUM_BLOCKS] = {
#include "nvm_block_cfg.h"
};

#ifdef NVM_DATASET
#undef NVM_BLOCK
#define NVM_BLOCK(a,b,c,d ,e,f) f,
const uint8 NVM_BlockCopies[NVM_NUM_BLOCKS] = {
#include "nvm_block_cfg.h"
};
uint8 NVM_BlockDataSet[NVM_NUM_BLOCKS];	
#endif	

uint8 NVM_BlockStatus[NVM_NUM_BLOCKS];


typedef enum{
    NVM_DIFF,
    NVM_WRITE_BYTE,
    NVM_WRITE_CS        
}TNVMState;

static uint8 CSm;	
static uint8 CurrentBlock;
static uint8 ByteCount;
static uint8 *pRam;
static const uint8 __rom *pRom;
static uint8 addr;
static TNVMState NVMState;
static uint8 WorkBuff[30];


static void PrepBlockData(void) {
    addr = NVM_BlockAddr[CurrentBlock];
    pRam = NVM_BlockRAM[CurrentBlock];
    pRom = NVM_BlockROM[CurrentBlock];
    ByteCount = NVM_BlockSize[CurrentBlock];
#ifdef NVM_DATASET
    //dataset offset calculation
    addr += (ByteCount+1) * NVM_BlockDataSet[ CurrentBlock];
#endif	
    CSm = 0;
}

void NVM_ReadBlock(uint8 BlockIndex){
    NVM_BlockStatus[BlockIndex] = 0;
}

void NVM_WriteBlock(uint8 BlockIndex) {
    NVM_BlockStatus[BlockIndex] |= 4;
}

static void ReadBlock(void) {
    PrepBlockData();
    while (ByteCount--) {
        *pRam = Read_Eep(addr);
        CSm += *pRam;
        addr++;
        pRam++;
    }
    if (CSm == Read_Eep(addr)) {
        NVM_BlockStatus[CurrentBlock] = 1; //data valid
    } else {
        //set defaults!
        NVM_BlockStatus[CurrentBlock] = 2;
        PrepBlockData();
        if (0 != pRom) {
            while (ByteCount--) {
                *pRam = *pRom;
                pRam++;
                pRom++;
            }
            NVM_BlockStatus[CurrentBlock] = 3; //data valid CS error
        }
    }
}

void NVM_Init(void){
    
	//read all
    for ( CurrentBlock = 0; CurrentBlock < NVM_NUM_BLOCKS; CurrentBlock++ )
    {
#ifdef NVM_DATASET
        NVM_BlockDataSet[CurrentBlock] = 0;
#endif
        ReadBlock();
    }
    
    CurrentBlock = 0;
    PrepBlockData();
    NVMState = NVM_DIFF;
}

uint8 NVM_IsIdle(void) {
    uint8 i;
    for (i = 0; i < NVM_NUM_BLOCKS; i++) {
        if (NVM_BlockStatus[i] & 4) {
            return FALSE;
        }
    }      
    return (NVMState == NVM_DIFF);
}

void NVM_Task(void){
	uint8 i;
       
    switch (NVMState)  {
        case NVM_DIFF:
            for (CurrentBlock = 0; CurrentBlock < NVM_NUM_BLOCKS; CurrentBlock++) {
                if (NVM_BlockStatus[CurrentBlock] == 0) {
                    ReadBlock();
                    return;
                }
                else if (NVM_BlockStatus[CurrentBlock] & 4) {
                    NVM_BlockStatus[CurrentBlock] &= 0xFB;
                    PrepBlockData();
                    for (i = 0; i < ByteCount; i++) {
                        WorkBuff[i] = *pRam;
                        pRam++;
                    }
                    pRam = WorkBuff;
                    NVMState = NVM_WRITE_BYTE;
                    return;
                }
            }
            break;
            
        case NVM_WRITE_BYTE:
#ifdef DIFF_CHECK
            if ( Read_Eep(addr) != *pRam )
#endif
            {
                Write_Eep(addr, *pRam);
            }
            CSm += *pRam;
            addr++;
            pRam++;
            ByteCount--;
            if (0 == ByteCount) {
                NVMState = NVM_WRITE_CS;
            }
            break;
            
        case NVM_WRITE_CS:
#ifdef DIFF_CHECK
            if (Read_Eep(addr) != CSm)
#endif
            {
                Write_Eep(addr, CSm);
            }
            NVMState = NVM_DIFF;
            break;
            
        default:
            NVMState = NVM_DIFF;
            break;
    }
}

#ifdef NVM_DATASET
uint8 NVM_SetDataIndex(uint8 Block, uint8 Ds){
    if (NVM_BlockCopies[Block] > Ds) {
        NVM_BlockDataSet[Block] = Ds;
        return 0;
    }
    return 1;
}

uint8 NVM_GetDataIndex(uint8 Block) {
    return NVM_BlockDataSet[Block];
}
#endif

uint8 NVM_GetBlockLenght(uint8 Block) {
    if (Block < NVM_NUM_BLOCKS) {
        return NVM_BlockSize[Block];
    } else {
        return 0;
    }
}

uint8 NVM_WriteBlockData(uint8 Block, uint8 offset, uint8 data) {
    uint8 *pr;
    if ((Block < NVM_NUM_BLOCKS) && (offset < NVM_BlockSize[Block])) {
        pr = NVM_BlockRAM[Block];
        pr[offset] = data;
        return 0;
    } else {
        return 1;
    }
}

uint8 NVM_ReadBlockData(uint8 Block, uint8 offset) {
    uint8 *pr;
    pr = NVM_BlockRAM[Block];
    return pr[offset];
}