#include "types.h"
#include "drv_Si7021.h"
#include "drv_I2c.h"

#define Si7021_ADDRESS  0x80
#define Si7021_CONTROL  0xE7
#define Si7021_RESET    0xFE
#define Si7021_HUMNO    0xF5
#define Si7021_TEMP     0xE0

#define Si7021_READ_TIME 255 //low self teating

typedef enum {
    Si_RESET,
    Si_INIT,
    Si_HUM,
    Si_HUM_RD,
    Si_TEMP_RD
    
}TSiState;

static uint8 state;
static uint8 dly;
uint8 Si7021_Hum;
sint16 Si7021_Temp;


void Si7021_Init(void) {
    state = Si_RESET;
    Si7021_Hum = 255; Si7021_Temp =200; dly = 0;
}

void Si7021_Task(void) {
    uint8 i;
    uint16 val_raw;
    if (dly) {
        dly--;
        return;
    }
    switch(state)     {
        case Si_RESET:
            I2C_Start(Si7021_ADDRESS);
            I2C_Write(Si7021_RESET);
            I2C_Stop();
            dly = 5;
            state = Si_INIT;
            break;
        case Si_INIT:
            I2C_Start(Si7021_ADDRESS);
            I2C_Write(Si7021_CONTROL);
            I2C_Start(Si7021_ADDRESS | 1);
            i = I2C_Read(1);
            I2C_Stop();
            if (0x3A == i) {
                state = Si_HUM;
            }
            else {
                 state = Si_RESET;
            }
            break;
            
        case Si_HUM:
            I2C_Start(Si7021_ADDRESS);
            I2C_Write(Si7021_HUMNO);
            I2C_Stop();
            dly = 2;
            state = Si_HUM_RD;
            break;
            
        case Si_HUM_RD:
            i = I2C_Start(Si7021_ADDRESS|1);
            if (0==i) {
                val_raw = I2C_Read(0);
                val_raw <<=8;
                val_raw |= I2C_Read(1);
                //calc hum
                Si7021_Hum = (uint8) ((((uint32) val_raw)*125) >> 16);
                if (Si7021_Hum > 6) {
                    Si7021_Hum -= 6;
                } else {
                    Si7021_Hum = 0;
                }
                if (Si7021_Hum > 100) {
                    Si7021_Hum = 100;
                }    
                
                state = Si_TEMP_RD;
            } else {
                state = Si_RESET;
            }
            I2C_Stop();
            break;
            
        case Si_TEMP_RD:
            i = I2C_Start(Si7021_ADDRESS);
            if (0 == i) {
                I2C_Write(Si7021_TEMP);
                I2C_Start(Si7021_ADDRESS|1);
                val_raw = I2C_Read(0);
                val_raw <<= 8;
                val_raw |= I2C_Read(1);
                //calc temp
                Si7021_Temp = (uint16) ((((uint32) val_raw)*17572) >> 16);
                Si7021_Temp -= 4685;
                Si7021_Temp /= 10;
                
                dly = Si7021_READ_TIME;
                state = Si_HUM;
            } else {
                state = Si_RESET;
            }
            I2C_Stop();
            break;
        default:
            state = Si_RESET;
            break;
    }
}
