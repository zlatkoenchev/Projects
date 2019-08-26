
#ifndef _SPI_H
#define _SPI_H

#include "types.h"

//CSD/CSC/IRQ
#define IRQ1_pin  INTCONbits.INTF  
#define DATA_CS(x)  LATA4 = x
#define REG_CS(x)   LATB3 = x
#define  SPI_SDO LATA6
#define  SPI_SDI RB1
#define  SPI_SCK LATB4

void SPI_HF_Init(void);
void SPI_HF_Put(BYTE v);
uint8 SPI_HF_Get(void);
#endif
