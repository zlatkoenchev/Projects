#ifndef PROTCOL_H
#define PROTCOL_H


#define CMD_GLOB_TIME      0x01  //date and time
#define CMD_SENS_AIR    0x02  //air temp/hum/pressure
#define CMD_SENS_SWITCH 0x03  //on/off
#define CMD_ACTUTAOR    0x04  //0..100%
#define CMD_SENS_PIR    0x05
#define CMD_STATUS_INFO 0x06
#define CMD_ENERGY_INFO 0x07
#define CMD_ENERGY_CLR  0x08


#define SIG_RTIME       0x07
#define SIG_PRESENCE    0x11 //17
#define SIG_TEMP1       0x22  //34
#define SIG_TEMP2       0x32  //50
#define SIG_ENERGY1     0x44  //68
#define SIG_ENERGY2     0x54  //84
#define SIG_HUMIDITY    0x61  //97
#define SIG_ACTUATOR    0x71  //113
#define SIG_FAN         0x81  //129
#define SIG_HTR         0x91  //145
#define SIG_BATH        0xA1  //161
#define SIG_SWITCH      0xB1  //177
#define SIG_BATTERY     0xC1  //193


#define CMD_APPL_NM     0xEF  
//--------------------FBL only
#define CMD_GETSEED   0xF0
#define CMD_SENDKEY   0xF1
#define CMD_ERASE     0xF2
#define CMD_WRITE     0xF3
#define CMD_VALIDATE  0xF4
#define CMD_ECURESET  0xF5
#define CMD_READ      0xF6
#define CMD_MODE      0xF7
#define CMD_INVALIDATE  0xF8
#define CMD_COM_CTL   0xF9

#define CMD_NEG_RESP  0xFF
#define CMD_NONE      0x00
//--------------------device type 

#define DVC_RTC          0x0001
#define DVC_TERM_REG     0x0002
#define DVC_PIR          0x0004
#define DVC_RELAY        0x0008
#define DVC_PWM          0x0010
#define DVC_SW1          0x0020
#define DVC_SW2          0x0040

#endif

