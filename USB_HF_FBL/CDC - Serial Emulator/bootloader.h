/* 
 * File:   bootloader.h
 * Author: zlatko
 *
 * Created on January 28, 2018, 12:04 PM
 */

#ifndef BOOTLOADER_H
#define	BOOTLOADER_H
#include "Protocol.h"


#define APPL_VALID_VALUE 0xCA

void Boot_Init(void);

void Boot_RxProcess(void);
void Boot_Task(void);

#endif	

