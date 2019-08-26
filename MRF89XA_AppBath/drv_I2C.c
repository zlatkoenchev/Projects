#include "types.h"
#include "drv_I2c.h"

#define  SDA_LOW TRISA3 = 0
#define  SCK_LOW TRISA2 = 0
#define  SDA_HI TRISA3 = 1
#define  SCK_HI TRISA2 = 1
#define  SDA_LEV RA3
#define  SCK_LEV RA2

uint8 Err;

uint8 I2C_GetErr(void)
{
    return Err;
}

void I2C_Init(void){
    SDA_HI;
    SCK_HI;
    Err = 0;
}

uint8 I2C_Start(uint8 AddrCMD){
    SDA_HI;
    SCK_HI;
    SDA_LOW;
    Err = 0;
    return I2C_Write(AddrCMD);
}

void I2C_Stop(void){
    SDA_LOW;
    SCK_LOW;
    SCK_HI;
    SCK_HI;
    SDA_HI;
}

uint8 I2C_Write(uint8 data){
    uint8 i;
    uint8 j = 255;
    for (i=0; i<8; i++)
    {    
        SCK_LOW;
        if (data & 0x80)
        {
            SDA_HI;
        }
        else
        {
            SDA_LOW;
        }
        data <<=1;
        SCK_HI;
        SCK_HI;
        while ((0 == SCK_LEV) && (j !=0 ))
        {
            j--;
        }
        if (j==0)
        {
            Err |=1;//clock held to low
        }
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
    uint8 j = 255;
    
    SDA_HI;
    for (i = 0; i < 8; i++) {
        SCK_LOW;
        v <<= 1;
        SCK_HI;
        SCK_HI;
        while ((0 == SCK_LEV) && (j != 0)) {
            j--;
        }
        if (j == 0) {
            Err |= 1; //clock held to low
        }
        if (SDA_LEV ) {
            v |= 1;
        }
       
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
    SCK_HI;
    SCK_LOW;
    SDA_HI;//release SDA
    return v;
}

