#include "drv_spi_hf.h"


#define SPI_BY_HW

void SPI_HF_Init(void) {
    DATA_CS(1);
    REG_CS(1);
#ifdef SPI_BY_HW
    //ckp = 0
    //cke = 1
    //smp =0
    //clc = fosc/4
    SSP1CON1 = 0;
    SSP1CON2 = 0;
    SSP1CON3 = 0;
    SSP1STAT = 0x40;
    SSP1IE = 0;
    SSP1CON1bits.SSPEN = 1;
    
#else
    SPI_SCK = 0;
#endif    
    
}

void SPI_HF_Put(uint8 v) {
    volatile uint8 i;

#ifdef SPI_BY_HW    
    
    i = SSP1BUF;
    SSP1IF = 0;
    SSP1BUF = v;
    while (SSP1IF == 0); //wait until interrupt is set
#else

    SPI_SCK = 0;

    for (i = 0; i < 8; i++) {
        if (v & 0x80) {
            SPI_SDO = 1;
        } else {
            SPI_SDO = 0;
        }
        v <<= 1; //SPI_SDO = (v >> (7 - i));
        SPI_SCK = 1;
        SPI_SCK = 0;
    }
    SPI_SDO = 0;
#endif    

}

uint8 SPI_HF_Get(void) {
    volatile uint8 spidata;

#ifdef SPI_BY_HW   

    spidata = SSP1BUF;
    SSP1IF = 0;
    SSP1BUF = 0;
    while (SSP1IF == 0); //wait until interrupt is set;
    return SSP1BUF;
#else
    uint8 i;

    SPI_SDO = 0;
    SPI_SCK = 0;
    spidata = 0;

    for (i = 0; i < 8; i++) {
        if (SPI_SDI) {
            spidata |= 1;
        }
        spidata <<= 1; //(spidata << 1) | SPI_SDI;
        SPI_SCK = 1;
        SPI_SCK = 0;
    }
    return spidata;
#endif
}

