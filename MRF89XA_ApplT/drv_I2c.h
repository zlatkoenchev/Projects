/* 
 * File:   drv_I2c.h
 * Author: zlatko
 *
 * Created on February 18, 2018, 1:55 PM
 */

#ifndef DRV_I2C_H
#define	DRV_I2C_H

void I2C_Init(void);
uint8 I2C_Start(uint8 AddrCMD);
void I2C_Stop(void);
uint8 I2C_Write(uint8 data);
uint8 I2C_Read(uint8 ACK);

#endif	

