
#ifndef _SI7021_H_
#define _SI7021_H_



void Si7021_Init(void);
void Si7021_Task(void);

extern uint8 Si7021_Hum;
extern sint16 Si7021_Temp;

#define Si7021_GetTemp() Si7021_Temp
#define Si7021_GetHum()  Si7021_Hum


#endif // _RTCLIB_H_
