

/************************ HEADERS **********************************/
#include "types.h"
#include "GenericTypeDefs.h"
#include "Compiler.h"
#include "drv_spi_hf.h"

/************************ FUNCTIONS ********************************/

#define SPI_SDI             PORTBbits.RB2
#define SDI_TRIS            TRISBbits.TRISB2
#define SPI_SDO             LATBbits.LATB3
#define SDO_TRIS            TRISBbits.TRISB3
#define SPI_SCK             LATBbits.LATB1
#define SCK_TRIS            TRISBbits.TRISB1

volatile uint8 dl;
static void Delay1us(void)
{
    dl = 6;
    while (dl--);
}

void SPI_HF_Init(void)
{
    SDI_TRIS = 1;//input
    SDO_TRIS = 0;
    SCK_TRIS = 0;
    TRISAbits.TRISA5 = 0;
    TRISBbits.TRISB5 = 0;
    
    INTCON2bits.RBPU = 0;
    
    TRISBbits.TRISB4 = 1;
    INTCON2bits.INTEDG3 = 1; //rising edge
    EECON2 = 0x55;
    EECON2 = 0xAA;
    PPSCONbits.IOLOCK = 0;
    RPINR3 = 7; // IRQ1 is connected to INT3
    EECON2 = 0x55;
    EECON2 = 0xAA;
    PPSCONbits.IOLOCK = 1;
    
    DATA_CS(1);
    REG_CS(1);
    IRQ1_pin = 0;
}

void SPI_HF_Put(uint8 v)
{
    uint8 i;
        SPI_SDO = 0;
        SPI_SCK = 0;
        Delay1us();
        
        for(i = 0; i < 8; i++)
        {
            SPI_SDO = (v >> (7-i));      
            SPI_SCK = 1;
            Delay1us();
        
            SPI_SCK = 0;
            Delay1us();
        }  
        SPI_SDO = 0; 
        Delay1us();
}

uint8 SPI_HF_Get(void)
{    
        uint8 i;
        uint8 spidata = 0;

        SPI_SDO = 0;
        SPI_SCK = 0;
        Delay1us();
        
        for(i = 0; i < 8; i++)
        {
            spidata = (spidata << 1) | SPI_SDI;  
            SPI_SCK = 1;
            Delay1us();
            SPI_SCK = 0;
            Delay1us();
        } 
        Delay1us();
        return spidata;
}

    






