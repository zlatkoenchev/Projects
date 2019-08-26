// Code by JeeLabs http://news.jeelabs.org/code/
// Released to the public domain! Enjoy!

#include "types.h"
#include "drv_BathCom.h"
#include "drv_I2c.h"

#define BATH_ADDRESS  (0x30)



uint8 Err;
uint8 indata[RX_LEN];
uint8 indata2[RX_LEN];

uint8 BCom_GetErr(void) {
    return Err;
}

void BCom_SetOut(uint8 Data) {
    
  Err = I2C_Start(BATH_ADDRESS);
  I2C_Write(Data); 
  I2C_Write(~Data);
  Err |= I2C_GetErr();
  I2C_Stop();
}


void BCom_ReadIn(void) {
  uint8 i;
  Err = I2C_Start(BATH_ADDRESS | 1);
  
  for (i = 0; i< (RX_LEN-1);i++)
  {
      indata2[i] = I2C_Read(0);
  }
  indata2[i] = I2C_Read(1);
  Err |= I2C_GetErr();
  I2C_Stop();
  if (0 == Err)
  {
      for (i = 0; i < (RX_LEN - 1); i++) {
          indata[i] = indata2[i];
      }
  }
}
