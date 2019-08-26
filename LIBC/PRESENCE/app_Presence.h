/* 
 * File:   app_Presence.h
 * Author: zlatko
 *
 * Created on March 17, 2018, 4:35 PM
 */

#ifndef APP_PRESENCE_H
#define	APP_PRESENCE_H

typedef struct {
    uint8 PIR_CTRL; //b0 - used,b1 - send RF frame 
    uint8 NAD1;
    uint8 NAD2;
    uint8 NAD3;
    uint8 NAD4;
    uint16 PIR_TIME; //1 sec resolution
    uint16 PIR_TIME_NIGHT; //1 sec resolution
    
} tNVMPIR;


void PRS_Init(void);
uint8 PRS_RoomPresence(void);
void PRS_Task1s(void);
void PRS_Task(void);
void PRS_OnPIRFrame(void);

extern uint16 PresenceTime;
#define PRS_GetPresenceTime() PresenceTime

#endif	

