// Code by JeeLabs http://news.jeelabs.org/code/
// Released to the public domain! Enjoy!

#include "types.h"
#include "drv_DS3231.h"
#include "drv_I2c.h"
#include "app_RTC.h"

#define DS3231_ADDRESS  (0xD0)
#define DS3231_CONTROL  0x0E
#define DS3231_STATUSREG 0x0F



static uint8 read_i2c_register( uint8 reg) {
  uint8 val;
  I2C_Start(DS3231_ADDRESS);
  I2C_Write(reg);
  I2C_Start(DS3231_ADDRESS|1);
  val = I2C_Read(1);
  I2C_Stop();
  return val;
}

static uint8 write_i2c_register(uint8 reg, uint8 val) {
  uint8 i = I2C_Start(DS3231_ADDRESS);
  I2C_Write(reg);
  I2C_Write(val);
  I2C_Stop();
  return i;
}

uint8 DS3231_Init(void) {
    
    if (0 == write_i2c_register( DS3231_CONTROL, 0))
    {
        return 1;
    }
    return 0;
}

uint8 DS3231_lostPower(void) {
  return (uint8) (read_i2c_register( DS3231_STATUSREG) >> 7);
}

void DS3231_SetTime(void) {
  I2C_Start(DS3231_ADDRESS);
  I2C_Write(0); // start at location 0
  I2C_Write(DateTime.Seconds);
  I2C_Write(DateTime.Minutes);
  I2C_Write(DateTime.Hours);
  I2C_Write(DateTime.DOW);
  I2C_Write(DateTime.Day);
  I2C_Write(DateTime.Month);
  I2C_Write(DateTime.Year);
  I2C_Stop();

  uint8 statreg = read_i2c_register( DS3231_STATUSREG);
  statreg &= ~0x80; // flip OSF bit
  write_i2c_register( DS3231_STATUSREG, statreg);
}

void DS3231_GetTime(void) {
  I2C_Start(DS3231_ADDRESS);
  I2C_Write(0);	
  I2C_Start(DS3231_ADDRESS | 1);
  DateTime.Seconds  = I2C_Read(0);
  DateTime.Minutes = I2C_Read(0);
  DateTime.Hours = I2C_Read(0);
  DateTime.DOW = I2C_Read(0);
  DateTime.Day = I2C_Read(0);
  DateTime.Month = (uint8)(I2C_Read(0) & 0x1F); 
  DateTime.Year = I2C_Read(1);
  I2C_Stop();
}
