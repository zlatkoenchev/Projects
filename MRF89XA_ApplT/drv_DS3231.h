
#ifndef _RTCLIB_H_
#define _RTCLIB_H_




#define SECONDS_PER_DAY 86400L

#define SECONDS_FROM_1970_TO_2000 946684800



uint8 DS3231_Init(void);

void DS3231_GetTime(void);

void DS3231_SetTime(void);



#endif // _RTCLIB_H_
