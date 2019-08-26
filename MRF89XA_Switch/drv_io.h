/* 
 * File:   drv_io.h
 * Author: zlatko
 *
 * Created on February 23, 2018, 8:38 PM
 */

#ifndef DRV_IO_H
#define	DRV_IO_H

#define IO_SetREL_ON(x)    LATA3 = x
#define IO_SetREL_OFF(x)   LATA2 = x
#define SW1_LEVEL RB7
#define SW2_LEVEL RB6

#define IO_PHOTOMOS_OFF     LATA3 = 0;LATA2 = 0 ;TRISA2 = 0;TRISA3 = 0
#define IO_PHOTOMOS_ON      TRISA3 = 0;LATA3 = 1
#define IO_PHOTOMOS_HI      LATA2 = 1;TRISA2 = 0 //outtut
#define IO_PHOTOMOS_LO      TRISA2 = 1 //input


extern uint8 u8ZCnumber;
extern uint8 SWdeb1;
extern uint8 SWdeb2;

void IO_SetPhotomosSync(uint8 cmd);
void IO_TaskSlow(void);
void IO_Init(void);
void IO_TaskFast(void);
void IO_SetRelSync(uint8 cmd);
uint8 IO_GetSW1Press(void);
uint8 IO_GetSW2Press(void);

#define IO_GetPIRLevel() RB7

#define IO_TimeMS(x)  ((x)*2)
#define IO_Time512us  1
#define IO_Time1ms    2
#define IO_Time20ms   39

void IO_StartTimer1(uint8 Time);
void IO_StartTimer2(uint8 Time);
#define IO_IsTimer1Elapsed() TMR4IF
#define IO_IsTimer2Elapsed() TMR0IF
#define IO_GetZCNumber() u8ZCnumber
#define IO_DisablePIR()
void IO_TaskIdle(void);

#endif	

