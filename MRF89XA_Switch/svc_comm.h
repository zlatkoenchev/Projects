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


#define COM_TX_SEND_PERIOD  60
#define GW_BUFF_SIZE 4
#define GW_FRAME_TIMEKEEP 70 //1 sec

typedef struct {
  
    uint8 MY_NAD;

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

void Comm_Sleep(void);

void Comm_Task(void);

void Comm_OnIdle(void);

void Comm_Task(void);

void Comm_Transmit(uint8 val);


#endif	

