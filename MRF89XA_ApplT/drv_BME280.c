/***************************************************************************
  This is a library for the BME280 humidity, temperature & pressure sensor

  Designed specifically to work with the Adafruit BME280 Breakout
  ----> http://www.adafruit.com/products/2650

  These sensors use I2C or SPI to communicate, 2 or 4 pins are required
  to interface.

 ***************************************************************************/
#include "types.h"
#include "drv_BME280.h"
#include "drv_I2c.h"


sint32 t_fine;
sint16 t_coarse;//0.1C resolution
uint16 p_coarse;//1hPa resolution
bme280_calib_data Calib;
uint8 h_coarse;

static uint8 SensorData[8];

static void BME280_ReadSensorData(void);
static void BME280_SetSampling(void);
static uint8 BME280_IsReadingCalibration(void);
static void BME280_ReadCoefficients(void);
static void BME280_StartMeasurement(void);
static void BME280_CalcHumidity(void);
static void BME280_CalcPressure(void);
static void BME280_CalcTemperature(void);
static void write8(uint8 reg, uint8 value);
static uint8 read8(uint8 reg);
static uint16 read16(uint8 reg);
static uint16 read16_LE(uint8 reg);
static sint16 readS16(uint8 reg);
sint16 readS16_LE(uint8 reg);


/**************************************************************************/
/*!
    @brief  Initialise sensor with given parameters / settings
*/
/**************************************************************************/

uint8 BME280_Init(void){   
    // check if sensor, i.e. the chip ID is correct
    if (read8(BME280_REGISTER_CHIPID) != 0x60){
        return 0;
    }
    // reset the device using soft-reset
    // this makes sure the IIR is off, etc.
    write8(BME280_REGISTER_SOFTRESET, 0xB6);

    // wait for chip to wake up.//zzl todo
    //delay(300);

    // if chip is still reading calibration, delay
    while (BME280_IsReadingCalibration());

    BME280_ReadCoefficients(); // read trimming parameters, see DS 4.2.2

    // you must make sure to also set REGISTER_CONTROL after setting the
    // CONTROLHUMID register, otherwise the values won't be applied (see DS 5.4.3)
    write8(BME280_REGISTER_CONTROLHUMID, SAMPLING_X16);
    write8(BME280_REGISTER_CONFIG, MODE_NORMAL | (SAMPLING_X16 << 2) | (SAMPLING_X16 << 5));
    write8(BME280_REGISTER_CONTROL, (STANDBY_MS_125 << 5) | (FILTER_X4 << 2));
    
    return 1;
}

void BME280_Task(void){
    BME280_ReadSensorData();
    BME280_CalcTemperature();
   // BME280_CalcHumidity();
    //BME280_CalcPressure();
}

static void BME280_ReadSensorData(void){
        uint8 i;
        I2C_Start(BME280_ADDRESS);
        I2C_Write(0xF7);
        I2C_Stop();
        I2C_Start(BME280_ADDRESS | 1);
        for (i = 0; i < 7; i++)
        {
            SensorData[i] = I2C_Read(0);
        }
        SensorData[i] = I2C_Read(1);
        I2C_Stop();
}

static void write8(uint8 reg, uint8 value) {
    I2C_Start(BME280_ADDRESS);
    I2C_Write(reg);
    I2C_Write(value);
    I2C_Stop();
}

static uint8 read8(uint8 reg) {
    uint8 value;

    I2C_Start(BME280_ADDRESS);
    I2C_Write(reg);
    I2C_Stop();
    I2C_Start(BME280_ADDRESS | 1);
    value = I2C_Read(1);
    I2C_Stop();
    return value;
}

static uint16 read16(uint8 reg){
    uint16 value;

    I2C_Start(BME280_ADDRESS);
    I2C_Write(reg);
    I2C_Stop();
    I2C_Start(BME280_ADDRESS | 1);
    value = ((uint16)I2C_Read(0))<<8;
    value |=  I2C_Read(1);
    I2C_Stop();
   
    return value;
}

static uint16 read16_LE(uint8 reg) {
    uint16 temp = read16(reg);
    return (temp >> 8) | (temp << 8);
}

static void BME280_ReadCoefficients(void){
    Calib.dig_T1 = read16_LE(BME280_REGISTER_DIG_T1);
    Calib.dig_T2 = (sint16)read16_LE(BME280_REGISTER_DIG_T2);
    Calib.dig_T3 = (sint16) read16_LE(BME280_REGISTER_DIG_T3);

    Calib.dig_P1 = read16_LE(BME280_REGISTER_DIG_P1);
    Calib.dig_P2 = (sint16) read16_LE(BME280_REGISTER_DIG_P2);
    Calib.dig_P3 = (sint16) read16_LE(BME280_REGISTER_DIG_P3);
    Calib.dig_P4 = (sint16) read16_LE(BME280_REGISTER_DIG_P4);
    Calib.dig_P5 = (sint16) read16_LE(BME280_REGISTER_DIG_P5);
    Calib.dig_P6 = (sint16) read16_LE(BME280_REGISTER_DIG_P6);
    Calib.dig_P7 = (sint16) read16_LE(BME280_REGISTER_DIG_P7);
    Calib.dig_P8 = (sint16) read16_LE(BME280_REGISTER_DIG_P8);
    Calib.dig_P9 = (sint16) read16_LE(BME280_REGISTER_DIG_P9);

    Calib.dig_H1 = read8(BME280_REGISTER_DIG_H1);
    Calib.dig_H2 = (sint16) read16_LE(BME280_REGISTER_DIG_H2);
    Calib.dig_H3 = read8(BME280_REGISTER_DIG_H3);
    Calib.dig_H4 = (((uint16)read8(BME280_REGISTER_DIG_H4)) << 4) | (read8(BME280_REGISTER_DIG_H4+1) & 0xF);
    Calib.dig_H5 = (((uint16)read8(BME280_REGISTER_DIG_H5+1)) << 4) | (read8(BME280_REGISTER_DIG_H5) >> 4);
    Calib.dig_H6 = (sint8)read8(BME280_REGISTER_DIG_H6);
}

static uint8 BME280_IsReadingCalibration(void){
  uint8 rStatus = read8(BME280_REGISTER_STATUS);
  return ((rStatus & 1) != 0);
}

static void BME280_CalcTemperature(void){
    sint32 var1, var2;
    //read only 16 bit and ignore rest bits
    uint16 adc_T = (((uint16)SensorData[3])<<8) | SensorData[4];
    
    if (adc_T == 0x8000){ // value in case temp measurement was disabled
        return;
    }

    //T = (ADC-T1)*T2/1024  + T3*(ADC-T1)^2 /(16384*4096)
    
    
    //((adc/8-T1*2)*T2)/2048
    //var1 = ((((adc_T>>3) - ((int32_t)_bme280_calib.dig_T1 <<1))) *
    //        ((int32_t)_bme280_calib.dig_T2)) >> 11;
    var2 = (adc_T - Calib.dig_T1);//remove offset
    var1 = (var2 * ((sint32) Calib.dig_T2)) >> 10;//raw temp
         
    //((((adc/16-T1)^2)/4096)*T3)/16384 
    //var2 = (((((adc_T>>4) - ((int32_t)_bme280_calib.dig_T1)) *
    //          ((adc_T>>4) - ((int32_t)_bme280_calib.dig_T1))) >> 12) *
    //        ((int32_t)_bme280_calib.dig_T3)) >> 14;

    var2 = (((var2 * var2) >> 12) * ((sint32) Calib.dig_T3)) >> 14;
            
    t_fine = var1 + var2;//0.00019C
    t_coarse = t_fine >> 9; //0.1C 
}

static void BME280_CalcPressure(void) {
    sint32 var1, var1_4, var2, var4, p;

    uint32 adc_P = (((uint32) SensorData[0]) << 16) | 
                    (((uint32)SensorData[1]) << 8) |
                     SensorData[2];
    
    if (adc_P == 0x800000) {// value in case pressure measurement was disabled
        return;
    }
    
    adc_P >>= 4;

    var1 = ((t_fine>>1) - 64000);//center to 25C
    var1_4 = var1>>2; //4
    //var2=  ((((t-25)/4)^2)/2048 * P6) + (t-25)*P5*2 + P4*65536   
    var2 = ((var1_4 * var1_4) >> 11) * (sint32)Calib.dig_P6;
    var2 = var2 + ((var1*(sint32)Calib.dig_P5)*2);
    var2 = (var2>>2) + (((sint32)Calib.dig_P4)<<16);
    
    var1 = ((((var1_4 * var1_4)>>13) * (sint32)Calib.dig_P3))>>3;
    var4 = (var1 * (sint32)Calib.dig_P2)>>1;
    var1 = (var1 + var4)>>18;
    var1 = (32768+var1)*((sint32)Calib.dig_P1)>>15;

    if (var1 == 0) {
        p_coarse = 300;
        return; // avoid exception caused by division by zero
    }
    
    p = 1048576 - adc_P;
    p = (p - (var2 >> 12))*3125;
    p = (p / var1) << 1;
    
    var4 = p>>3;
    var1 = (((sint32)Calib.dig_P9) * (var4 * var4)>>13)>>12 ;
    var2 = ((p>>2)*((sint32)Calib.dig_P8))>> 13;

    p = p + (var1 + var2 +(sint32)Calib.dig_P7)>>4;
    p_coarse = (uint16)(p/100);
}

static void BME280_CalcHumidity(void){   
    sint32 var1;
    sint32 var2;
    sint32 var3;
    sint32 var4;
    sint32 var5;
  
    uint16 adc_H = (((uint16) SensorData[6]) << 8) | SensorData[7];
    
    if (adc_H == 0x8000) // value in case humidity measurement was disabled
        return;
        
    var1 = t_fine - ((sint32) 76800);
    var2 = (sint32) (adc_H << 14);
    var3 = ((sint32) Calib.dig_H4) << 20;
    var4 = ((sint32) Calib.dig_H5) * var1;
    var5 = (((var2 - var3) - var4) + (sint32) 16384) >> 15;
    var2 = (var1 * ((sint32) Calib.dig_H6)) >> 10;
    var3 = (var1 * ((sint32) Calib.dig_H3)) >> 11;
    var4 = ((var2 * (var3 + 32768)) >>10) + (sint32) 2097152;
    var2 = ((var4 * ((sint32) Calib.dig_H2)) + 8192) >>14;
    var3 = var5 * var2;
    var1 = (var3 >>15);
    var4 = (var1  * var1)>>7;
    var5 = var3 - ((var4 * ((sint32) Calib.dig_H1)) >> 4);
    if (var5 < 0)
    {
        h_coarse = 0;
    }
    else 
    {
        h_coarse = (uint8) (var5 / 4194304);
        if (h_coarse>100)
        {
            h_coarse = 100;
        }
    }
}

