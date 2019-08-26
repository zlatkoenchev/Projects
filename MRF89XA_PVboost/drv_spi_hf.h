
#ifndef _SPI_H
#define _SPI_H

#include "types.h"

//CSD/CSC/IRQ
#define IRQ1_pin  PIR0bits.INTF  
#define DATA_CS(x)  LATC3 = x
#define REG_CS(x)   LATA2 = x
#define  SPI_SDO LATC2
#define  SPI_SDI RC1
#define  SPI_SCK LATC0

void SPI_HF_Init(void);
void SPI_HF_Put(BYTE v);
uint8 SPI_HF_Get(void);
void SPI_HF_Deinit(void);
#endif
