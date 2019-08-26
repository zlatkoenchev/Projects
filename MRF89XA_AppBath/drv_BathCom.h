
#ifndef _RTCLIB_H_
#define _RTCLIB_H_


#define RX_LEN 11
extern uint8 indata[RX_LEN];

#define SECONDS_PER_DAY 86400L

#define SECONDS_FROM_1970_TO_2000 946684800

uint8 BCom_GetErr(void);
void BCom_ReadIn(void);
#define BCom_GetIn(i) indata[i]
void BCom_SetOut(uint8 Data);



#endif // _RTCLIB_H_
