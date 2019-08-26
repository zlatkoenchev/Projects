/* 
 * File:   app_relay.h
 * Author: zlatko
 *
 * Created on May 7, 2018, 8:15 AM
 */

#ifndef APP_RELAY_H
#define	APP_RELAY_H

void RelBS_Init(void); 

void RelBS_Task(void);

void RelBS_Request(uint8 breq);

uint8 RelBS_IsOn(void);

uint8 RelBS_IsIdle(void);

uint8 RelBS_GetState(void);

#endif	

