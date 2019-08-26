#include "types.h"
#include "svc_uds.h"
#include "svc_comm.h"
#include "svc_nvm.h"
#include "drv_eep.h"
#include "main.h"
#include "drv_io.h"
#include "app_RTC.h"
#include "drv_io.h"
#include "app_Presence.h"
#include "app_TempReg.h"
#include "app_ProgTemp.h"
#include "drv_air_sens.h"

#define WDBID_FLASH     0x01
#define WDBID_NVMDATA   0x02 

#define WDBID_HFWRITE  0xF0

#define RDBID_DEVCAPS  0x01
#define RDBID_NVMDATA  0x02
#define RDBID_IN_DATA  0x05

static uint32 seed;

void UDS_Init(void){
    
}

static void ROL(uint8 num) {
    while (num--) {
        if (seed & 0x80000000) {
            seed <<= 1;
            seed |= 0x01;
        } else {
            seed <<= 1;
        }
    }
}

static void Calc_Key(void) {
    ROL(7);
    seed = seed ^ 0xCA236124;
    ROL(5);
    seed = seed ^ 0xAC321641;
    ROL(3);
    seed = seed ^ 0x01100112;
    ROL(1);
}

uint8 UDS_CompareKey(void) {
    uint32 s1;
    Calc_Key();
    s1 = (((uint32) RxData(C_PAGE + 3)) << 24) |
            (((uint32) RxData(C_PAGE + 2)) << 16) |
            (((uint32) RxData(C_PAGE + 1)) << 8) |
            (RxData(C_PAGE));

    if (seed != s1) {
        seed = 0;
        NEG_RESP(0x22);
        return FALSE;
    } else {
        POS_RESP(0);
        return TRUE;
    }
}

void UDS_GetSeed(void) {
    seed = (((uint32) OS_GetTickCount()) << 16) | (uint16) AirS_GetTemp();
    TxData(3) = (uint8) (seed >> 24);
    TxData(2) = (uint8) (seed >> 16);
    TxData(1) = (uint8) (seed >> 8);
    TxData(0) = (uint8) (seed);
    POS_RESP(4);
}

static void WriteNVMBlockSync(uint8 block) {
    NVM_WriteBlock(block);
    while ( NVM_IsBlockWrite(block)) {
        NVM_Task();
    } 
}

void UDS_WDBID(void){
    uint8 k,i,j;
    
    k = (uint8)(RxDataLen - 5); 
    switch ( RxPage())
    {
        case WDBID_NVMDATA://len,nad,nad,res,cmd,wdbid,block ID,data32
            i = 0;
            j = 0;
            k--;
            while (k)            {
                j += NVM_WriteBlockData(RxData(6) ,i, RxData(7+i));
                i++;
                k--;
            }
            if (j ==0 )             {
                WriteNVMBlockSync(RxData(6));
                POS_RESP(0);
            }
        break;
       
        case WDBID_HFWRITE:
            if (k == 2) {
                MRF89XARegisterSet(RxData(6), RxData(7));
                POS_RESP(0);
            }
            break;
    }
}
extern uint16 AdcRaw;
extern uint8 NVM_BlockStatus[NVM_NUM_BLOCKS];
void UDS_RDBID(void) {
    uint16 k,i;
   // uint8 a;
    //k = RxDataLen - 5; //len,nad,nad,res,cmd,wdbid,add4,data32
    switch (RxPage()) {
        case RDBID_DEVCAPS:

            TxData(0) = 1; //appl
            TxData(1) = MRF89XA_RSSI; 

            k = DVC_TERM_REG | DVC_PIR;
            if (RTC_IsRTCPresent()) {
                k |= DVC_RTC;
            }
            
            TxData(2) = (uint8)(k>>8);
            TxData(3) = (uint8) (k);
            POS_RESP(4);
            break;
          
        case RDBID_NVMDATA:
            k = NVM_GetBlockLenght(RxData(6));
            if ( k > 0 ) {
                    for (i = 0; i < k ;i++)   {
                       TxData(i) = NVM_ReadBlockData(RxData(6),i); 
                    }
                    POS_RESP(k);
            }
            break;
            
        case RDBID_IN_DATA:
            k = (uint16) AdcRaw;
            TxData(0) = (uint8) (k >> 8);
            TxData(1) = (uint8) (k);
            
            TxData(2) = (uint8)((PRS_GetPresenceTime())>>8);
            TxData(3) = (uint8) PRS_GetPresenceTime();
            TxData(4) = (uint8)PRG_GetSetTemp();
            TxData(5) = IO_GetPIRPin();
            TxData(6) = REG_GetLevel(); 
            TxData(7) = RegRow;
            TxData(8) = RegCol;
            TxData(9) = REG_PARAMS_RAM.StartPwm;
            //for (a=0;a < NVM_NUM_BLOCKS;a++){
                TxData(10) = NVM_IsIdle();
            //}
            POS_RESP(11);
            break;
    }
}
