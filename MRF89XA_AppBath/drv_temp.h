
#ifndef TEMDRVH
#define TEMDRVH

#define T_0C_ADC 562 //2.75Volts 0C
#define T_100C_ADC 818 //4V 100C
#define T_25C_ADC 613 //3V 25C

#define DEG_01C(x)   (x/5)
#define DEF_TEMP   DEG_01C(1000)

extern uint8 TWater;
extern uint8 TAir;

void TempDrv_Init(void);
//temperature in 0.5C 
#define TempDrv_GetAir() TAir
//temperature in 0.5C
#define TempDrv_GetWater() TWater
void TempDrv_Main(void);

#endif