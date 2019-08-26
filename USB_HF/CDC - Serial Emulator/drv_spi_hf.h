/* 
 * File:   drv_spi_hf.h
 * Author: zlatko
 *
 * Created on February 4, 2018, 7:04 PM
 */

#ifndef DRV_SPI_HF_H
#define	DRV_SPI_HF_H

#include "GenericTypeDefs.h"
#include "Compiler.h"

//CSD/CSC/IRQ
#define IRQ1_pin    INTCON3bits.INT3IF  // RB4

#define DATA_CS(x)  LATAbits.LATA5 = x;LATAbits.LATA5 = x;// RA5
#define REG_CS(x)   LATBbits.LATB5 = x;LATBbits.LATB5 = x;//RB5

void SPI_HF_Init(void);
void SPI_HF_Put(uint8 v);
uint8 SPI_HF_Get(void);
#endif	

