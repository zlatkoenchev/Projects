
#ifndef _SPI_H
#define _SPI_H

#include "types.h"

#define IRQ1_pin    INTCONbits.INTF  // RB0
#define IRQSETDIR   TRISBbits.TRISB0 = 1
#define DATA_CS(x)  LATAbits.LATA4 = x;// RA4
#define REG_CS(x)   LATBbits.LATB3 = x; //RB3
#define SETCSPINS   TRISBbits.TRISB3 = 0;LATAbits.LATA4 = 0;
#define SPI_SDI             PORTBbits.RB1
#define SDI_TRIS            TRISBbits.TRISB1
#define SPI_SDO             LATAbits.LATA6
#define SDO_TRIS            TRISAbits.TRISA6
#define SPI_SCK             LATBbits.LATB4
#define SCK_TRIS            TRISBbits.TRISB4

void SPI_HF_Init(void);
void SPI_HF_Put(BYTE v);
uint8 SPI_HF_Get(void);
#endif
