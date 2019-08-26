#include "types.h"
#include "svc_comm.h"
#include "svc_nm.h"

typedef enum {
    RTG_INIT,
    RTG_CHECKRSSI,
    RTG_WAITANS,
    RTG_FIN
}TRTGState;

#define NM_MAX_PERIOD (NM_MSG_PERIOD*(NM_MAX_NODES-1))

uint8 rtstate;
uint8 nmcount;
uint16 NMTimer;
TNMData NMData;

uint8 NM_GetDestNAD(uint8 nad) {
    if ( nad < NM_MAX_NODES ) {
        return NMData.RNAD[nad];
    }
    return 0;
}

void NM_StartNMTimer(uint8 rnad) {
    uint8 i;
    if (nmcount ) {//still message to send
        if (rnad <= Comm_GetMyNAD())    {
            i = (Comm_GetMyNAD() - rnad);
        } else {
            i = ((NM_MAX_NODES-1) + Comm_GetMyNAD()) - rnad;
        }
        NMTimer = NM_MSG_PERIOD * ((uint16)i);
    }
}

void NM_Init(void) {
    //todo if NM block is damaged set to 0
    nmcount = NM_MAX_PATH;
    if (Comm_GetMyNAD() < NM_MAX_NODES) {
        NM_StartNMTimer(0);
    } else {
        NMTimer = 0;
    }
}

void NM_OnNmMessage(void) {
    uint8 i,r;
    
    NM_StartNMTimer(RxSRC_NAD());
    //direct link to neighbour node
    if (RxSRC_NAD() < NM_MAX_NODES) { 
        NMData.RSSI[RxSRC_NAD()] = ((MRF89XA_RSSI >> 4) & 0x0F)|0xF0;
    }
    for (i = 1; i < NM_MAX_NODES; i++) {
        if (i != Comm_GetMyNAD()) {
            r = RxData(C_MSG_ID+i);
            //remote node has stronger RSSI than local to node i?
            if ( r > NMData.RSSI[i] ) {
                NMData.RSSI[i] = ((r >> 1) & 0x70) | (r & 0x0F);
                NMData.RNAD[i] = RxSRC_NAD(); //use RxSRC_NAD()as GW to node i
            }
        }
    }
}

void NM_Task(void) {
    uint8 i;
    if (NMTimer) {
        NMTimer--;
        if (0 == NMTimer) {
            //tx frame
            if (Comm_CanTransmit()) {
                Comm_MsgHeader(32, 0, CMD_APPL_NM);
                for (i = 1; i < NM_MAX_NODES; i++) {
                    TxData(i - 1) = NMData.RSSI[i];
                }
                Comm_Transmit();
                if (nmcount) {
                    nmcount--;
                    NMTimer = NM_MAX_PERIOD;
                }
            } else {
                NMTimer = 1;//try again after 20ms
            }
        }
    }
}
