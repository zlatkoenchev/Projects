/* 
 * File:   main.h
 * Author: zlatko
 *
 * Created on February 23, 2018, 8:41 PM
 */

#ifndef MAIN_H
#define	MAIN_H

extern uint16 u16Tics;
extern uint16 u16IdleTicks;

extern uint16 Power;

#define OS_GetTickCount()  u16Tics
#define OS_GetIdleTickCount() u16IdleTicks

void RequestReset(void);

#define SLP_FVR    0x0
#define SLP_1MS    0x1
#define SLP_2MS    0x3
#define SLP_4MS    0x5
#define SLP_8MS    0x7
#define SLP_16MS   0x9
#define SLP_64MS   0xD
#define SLP_128MS  0x0F
#define SLP_256MS  0x11
#define SLP_4S     0x19
#define SLP_256S   0x25

//clear single flags
//stop WDG
//disable wakeup by button
#define GotoSleep( delay){  \
    IOCAF = 0;              \
    WDTCON = delay;         \
    IOCIF = 0;              \
    asm("NOP");             \
    asm("SLEEP");           \
    asm("NOP");             \
    asm("NOP");             \
    SWDTEN = 0;             \
    IOCIE = 0;              \
}\


uint8 CalcUbat(void);

#endif	

