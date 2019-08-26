/* 
 * File:   drv_io.h
 * Author: zlatko
 *
 * Created on February 23, 2018, 8:38 PM
 */

#ifndef DRV_IO_H
#define	DRV_IO_H


sint16 IO_GetTempMeas(void);
void IO_TaskSlow(void);
void IO_Init(void);
void IO_TaskFast(void);
uint8  IO_GetPIRPin(void);
uint8 IO_GetSW1Press(void);
uint8 IO_GetSW2Press(void);
uint16 IO_GetADCTemp(void);
uint8 IO_GetPIRLevel(void);
void IO_DisablePIR(void);

#define IO_TimeMS(x)  ((x)*2)
#define IO_Time512us  1
#define IO_Time1ms    2
#define IO_Time2ms   4
#define IO_Time10ms   19

void IO_StartTimer1(uint8 Time);
#define IO_IsTimer1Elapsed() TMR4IF
#define IO_IsTimer2Elapsed() TMR6IF
#endif	

