/* 
 * File:   bootloader.h
 * Author: zlatko
 *
 * Created on January 28, 2018, 12:04 PM
 */

#ifndef SVC_COMM_H
#define	SVC_COMM_H
#include "Protocol.h"
#include "MRF89XA.h"

#include "app_RTC.h"

#define COM_TX_SEND_PERIOD  60
#define GW_BUFF_SIZE 4
#define GW_FRAME_TIMEKEEP 70 //1 sec

typedef struct {
    uint8 bTxReq:1;
    uint8 bTxState : 1;
    uint8 bTxON:1;
    uint8 bUnLocked:1;
    uint8 TxPeriod;
    uint8 RxIx;
    uint8 CSRetries;
    uint8 MY_NAD;
    uint8 sigID;
    uint8 Min;
    uint8 RxNADs[GW_BUFF_SIZE];
    uint8 RxCTRs[GW_BUFF_SIZE];
    uint8 RxTMRs[GW_BUFF_SIZE];
} TComData;



typedef struct{
#define TX_SIG_BUF_DEC
#include "svc_comm_cfg_tx.h"
}TComTxData;

extern TComTxData ComTxData;
extern TComData ComData;

#define Comm_GetMyNAD() ComData.MY_NAD


void NEG_RESP(uint8 c);

void POS_RESP(uint8 len);

void Comm_TaskSlow(void);

void Comm_Init(void);

void Comm_Task(void);

void Comm_OnIdle(void);

void Comm_Task(void);



#define ComSendSignal( sig,val)   ComTxData.sig##TxBuf = val
#define ComSendSignalImmediate( sig,val)   if( ComTxData.sig##TxBuf != (val)) {ComTxData.sig##TxBuf= val; ComData.bTxReq=1;}

#define ComRecvSignal(typ)   (*((typ *)&RxData(ComData.RxIx+1)))

#endif	

