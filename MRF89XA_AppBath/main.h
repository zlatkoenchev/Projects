/* 
 * File:   main.h
 * Author: zlatko
 *
 * Created on February 23, 2018, 8:41 PM
 */

#ifndef MAIN_H
#define	MAIN_H

#define OS_TICK_MS 20
#define OS_TIME_MS(x) ((x)/OS_TICK_MS)
extern uint16 u16Tics;

#define OS_GetTickCount()  u16Tics

void RequestReset(void);

#endif	

