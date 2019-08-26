/* 
 * File:   config.h
 * Author: zlatko
 *
 * Created on January 7, 2019, 10:07 PM
 */

#ifndef CONFIG_H
#define	CONFIG_H

#define TX_POWER_LEVEL TXPOWER_13

//#define HOL
#define DETSKA
//#define KUHNJA
//#define VYRSHEC




#ifdef HOL

#define USE_RTC_CHIP
#define Si7021_PRESENT
#define WINDOW_SENSOER_PRESENT

#elif defined DETSKA

//#define Si7021_PRESENT
#define TMP36_PRESENT
#define REG_ON_OFF
#define REMOTE_AIR_SENS_PRESENT
#define WINDOW_SENSOER_PRESENT

#elif defined KUHNJA

#define Si7021_PRESENT

#elif defined VYRSHEC

#define TMP36_PRESENT
#define USE_RTC_CHIP

#else

#error "not defined"
#endif



#endif	

