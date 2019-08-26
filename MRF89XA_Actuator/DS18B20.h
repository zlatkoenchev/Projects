/* 
 * File:   DS18B20.h
 * Author: zlatko
 *
 * Created on November 18, 2018, 10:03 AM
 */

#ifndef DS18B20_H
#define	DS18B20_H

void DS18B20_Init(void);
void DS18B20_Task(void);

extern uint16 DS18B20_temp;
#define DS18B20_GetTemp() DS18B20_temp

#endif	

