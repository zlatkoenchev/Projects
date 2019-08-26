/***************************************************************************
  This is a library for the BME280 humidity, temperature & pressure sensor

  Designed specifically to work with the Adafruit BME280 Breakout
  ----> http://www.adafruit.com/products/2650

  These sensors use I2C or SPI to communicate, 2 or 4 pins are required
  to interface.

  Adafruit invests time and resources providing this open source code,
  please support Adafruit andopen-source hardware by purchasing products
  from Adafruit!

  Written by Limor Fried & Kevin Townsend for Adafruit Industries.
  BSD license, all text above must be included in any redistribution
 ***************************************************************************/
#ifndef __BME280_H__
#define __BME280_H__


/*=========================================================================
    I2C ADDRESS/BITS
    -----------------------------------------------------------------------*/
    #define BME280_ADDRESS                (0xEC)//76
/*=========================================================================*/

/*=========================================================================
    REGISTERS
    -----------------------------------------------------------------------*/
    enum
    {
        BME280_REGISTER_DIG_T1              = 0x88,
        BME280_REGISTER_DIG_T2              = 0x8A,
        BME280_REGISTER_DIG_T3              = 0x8C,

        BME280_REGISTER_DIG_P1              = 0x8E,
        BME280_REGISTER_DIG_P2              = 0x90,
        BME280_REGISTER_DIG_P3              = 0x92,
        BME280_REGISTER_DIG_P4              = 0x94,
        BME280_REGISTER_DIG_P5              = 0x96,
        BME280_REGISTER_DIG_P6              = 0x98,
        BME280_REGISTER_DIG_P7              = 0x9A,
        BME280_REGISTER_DIG_P8              = 0x9C,
        BME280_REGISTER_DIG_P9              = 0x9E,

        BME280_REGISTER_DIG_H1              = 0xA1,
        BME280_REGISTER_DIG_H2              = 0xE1,
        BME280_REGISTER_DIG_H3              = 0xE3,
        BME280_REGISTER_DIG_H4              = 0xE4,
        BME280_REGISTER_DIG_H5              = 0xE5,
        BME280_REGISTER_DIG_H6              = 0xE7,

        BME280_REGISTER_CHIPID             = 0xD0,
        BME280_REGISTER_VERSION            = 0xD1,
        BME280_REGISTER_SOFTRESET          = 0xE0,

        BME280_REGISTER_CAL26              = 0xE1,  // R calibration stored in 0xE1-0xF0

        BME280_REGISTER_CONTROLHUMID       = 0xF2,
        BME280_REGISTER_STATUS             = 0XF3,
        BME280_REGISTER_CONTROL            = 0xF4,
        BME280_REGISTER_CONFIG             = 0xF5,
        BME280_REGISTER_PRESSUREDATA       = 0xF7,
        BME280_REGISTER_TEMPDATA           = 0xFA,
        BME280_REGISTER_HUMIDDATA          = 0xFD
    };

/*=========================================================================*/

/*=========================================================================
    CALIBRATION DATA
    -----------------------------------------------------------------------*/
    typedef struct
    {
        uint16 dig_T1;
        sint16  dig_T2;
        sint16  dig_T3;

        uint16 dig_P1;
        sint16  dig_P2;
        sint16  dig_P3;
        sint16  dig_P4;
        sint16  dig_P5;
        sint16  dig_P6;
        sint16  dig_P7;
        sint16  dig_P8;
        sint16  dig_P9;

        uint8  dig_H1;
        sint16  dig_H2;
        uint8  dig_H3;
        sint16  dig_H4;
        sint16  dig_H5;
        sint8   dig_H6;
    } bme280_calib_data;
/*=========================================================================*/

/*
class Adafruit_BME280_Unified : public Adafruit_Sensor
{
  public:
    Adafruit_BME280_Unified(int32_t sensorID = -1);

    bool  begin(uint8_t addr = BME280_ADDRESS);
    void  getTemperature(float *temp);
    void  getPressure(float *pressure);
    float pressureToAltitude(float seaLevel, float atmospheric, float temp);
    float seaLevelForAltitude(float altitude, float atmospheric, float temp);
    void  getEvent(sensors_event_t*);
    void  getSensor(sensor_t*);

  private:
    uint8_t   _i2c_addr;
    int32_t   _sensorID;
};

*/

enum sensor_sampling {
            SAMPLING_NONE = 0b000,
            SAMPLING_X1   = 0b001,
            SAMPLING_X2   = 0b010,
            SAMPLING_X4   = 0b011,
            SAMPLING_X8   = 0b100,
            SAMPLING_X16  = 0b101
        };

enum sensor_mode {
            MODE_SLEEP  = 0b00,
            MODE_FORCED = 0b01,
            MODE_NORMAL = 0b11
        };

enum sensor_filter {
            FILTER_OFF = 0b000,
            FILTER_X2  = 0b001,
            FILTER_X4  = 0b010,
            FILTER_X8  = 0b011,
            FILTER_X16 = 0b100
        };

// standby durations in ms 
enum standby_duration {
            STANDBY_MS_0_5  = 0b000,
            STANDBY_MS_10   = 0b110,
            STANDBY_MS_20   = 0b111,
            STANDBY_MS_62_5 = 0b001,
            STANDBY_MS_125  = 0b010,
            STANDBY_MS_250  = 0b011,
            STANDBY_MS_500  = 0b100,
            STANDBY_MS_1000 = 0b101
        };
    
		
extern uint8 BME280_Init(void);
extern void BME280_Task(void);

#endif
