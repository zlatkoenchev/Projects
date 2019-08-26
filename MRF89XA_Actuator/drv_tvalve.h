/* 
 * File:   drv_tvalve.h
 * Author: zlatko
 *
 * Created on June 17, 2018, 7:57 PM
 */

#ifndef DRV_TVALVE_H
#define	DRV_TVALVE_H


void RelTV_Init(void);

void RelTV_Task(void);

void RelTV_Task1s(void);

void RelTV_Request(uint8 breq);

uint8 RelTV_IsOn(void);

uint8 RelTV_IsIdle(void);

#endif	

