#include "types.h"
#include "drv_I2c.h"

#define  SDA_LOW TRISB6 = 0
#define  SCK_LOW TRISB7 = 0
#define  SDA_HI TRISB6 = 1
#define  SCK_HI TRISB7 = 1
#define  SDA_LEV RB6

void I2C_Init(void){
    LATB6 = 0;
    LATB7 = 0;
    SDA_HI;
    SCK_HI;
}

uint8 I2C_Start(uint8 AddrCMD){
    SDA_HI;
    SCK_HI;
    SCK_HI;
    SDA_LOW;
    return I2C_Write(AddrCMD);
}

void I2C_Stop(void){
    SDA_LOW;
    SDA_LOW;
    SCK_LOW;
    SCK_LOW;
    SCK_HI;
    SCK_HI;
    SCK_HI;
    SDA_HI;
}

uint8 I2C_Write(uint8 data){
    uint8 i;
    for (i=0; i<8; i++)
    {    
        SCK_LOW;
        if (data & 0x80)        {
            SDA_HI;
        }
        else        {
            SDA_LOW;
        }
        SCK_HI;
        data <<=1;
        SCK_HI;
        SCK_HI;
        SCK_HI;
        SCK_LOW;
        
    }
    SDA_HI; // release SDA
    SCK_LOW;//ACK clock pulse
    SCK_HI;
    SCK_HI;
    SCK_HI;
    i = SDA_LEV;
    SCK_LOW;
    return i;
}

uint8 I2C_Read(uint8 ACK){
    uint8 i;
    uint8 v = 0;
    SDA_HI;
    for (i = 0; i < 8; i++) {
        SCK_LOW;
        v <<= 1;
        SCK_HI;
        if (SDA_LEV ) {
            v |= 1;
        }
        SCK_HI;
        SCK_HI;
        SCK_HI;
        SCK_LOW;
    }
    if (0 == ACK)
    {
        SDA_LOW;
    }
    else 
    {
        SDA_HI;
    }
 
    SCK_LOW; //ACK pulse
    SCK_HI;
    SCK_HI;
    SCK_HI;
    SCK_LOW;
    SDA_HI;//release SDA
    return v;
}

