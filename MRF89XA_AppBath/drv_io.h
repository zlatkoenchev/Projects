/* 
 * File:   drv_io.h
 * Author: zlatko
 *
 * Created on February 23, 2018, 8:38 PM
 */

#ifndef DRV_IO_H
#define	DRV_IO_H


#define IO_DisablePIR()
void IO_TaskSlow(void);
void IO_Init(void);
void IO_TaskFast(void);
uint8 IO_GetPIREdge(void);
uint8 IO_GetSW1Press(void);
uint8 IO_GetSW2Press(void);
uint16 IO_GetADCTemp(void);
#define IO_GetPIRLevel() 0
#define IO_TimeMS(x)  ((x)*2)
#define IO_Time512us  1
#define IO_Time1ms    2
#define IO_Time2ms   4
#define IO_Time10ms   19

void IO_StartTimer1(uint8 Time);
#define IO_IsTimer1Elapsed() TMR4IF
#define IO_IsTimer2Elapsed() TMR6IF
#define IO_GetPIREdge() FALSE

typedef enum {
    Di_FanPanelBu,
    Di_FanLightSw,
    Di_NUM
} tDI;

typedef enum {
    Ai_Temp1,
    Ai_Temp2,
    Ai_FanCtl,
    Ai_SWFan,
    Ai_Consmp,
    Ai_NUM
} tAI;

typedef enum {
    Do_HTR1 =1,
    Do_HTR2 =2,
    Do_Fan_Low =4,
    Do_Fan_Hi =8,
    Do_DHM =16,
    Do_LED =32,
    Do_POWER =64
    
} tOut;

uint16 IOGetADCFilt(tAI i);
uint8 IOGetDio(tDI i);
void IO_SetOut(tOut i, uint8 val);
#endif	

