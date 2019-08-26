/* 
 * File:   main.h
 * Author: zlatko
 *
 * Created on February 23, 2018, 8:41 PM
 */

#ifndef MAIN_H
#define	MAIN_H

extern uint16 u16Tics;

#define OS_GetTickCount()  u16Tics

void RequestReset(void);

#endif	

