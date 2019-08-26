/* 
 * File:   svc_rotimg.h
 * Author: zlatko
 *
 * Created on September 29, 2018, 6:24 PM
 */

#ifndef SVC_ROTIMG_H
#define	SVC_ROTIMG_H

#define NM_MAX_NODES 33
#define NM_MSG_PERIOD 10 //*20ms
#define NM_MAX_PATH   3

typedef struct {
    uint8 RSSI[NM_MAX_NODES];
    uint8 RNAD[NM_MAX_NODES];
} TNMData;
extern TNMData NMData;

void NM_Init(void) ;
void NM_Task(void);
uint8 NM_GetDestNAD(uint8 nad);
void NM_OnNmMessage(void);

#endif	

