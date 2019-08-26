/* 
 * File:   drv_rel.h
 * Author: zlatko
 *
 * Created on June 9, 2018, 3:24 PM
 */

#ifndef DRV_REL_H
#define	DRV_REL_H

void Rel_Init(void);

void Rel_Task(void);

void Rel_Task1s(void);

void Rel_Request(uint8 breq);

uint8 Rel_IsOn(void);

uint8 Rel_IsIdle(void);

uint8 Rel_GetPWM(void);

#endif	

