
#define CMD_GLOB_TIME   0x01  //date and time
#define CMD_SENS_HUM    0x02  //air temp/hum/pressure
#define CMD_SENS_PRESS  0x03  //air temp/hum/pressure
#define CMD_SENS_TEMP   0x04  //temp sensor
#define CMD_SENS_SWITCH 0x05  //on/off
#define CMD_SENS_ENERGY 0x06


#define CMD_ACT_PWM     0x07  //0..100%
#define CMD_ACT_SW      0x08  //0..1

#define CMD_SENS_PIR    0x09

#define CMD_APPL_STOP   0xEF  
//--------------------FBL only
#define CMD_GETSEED   0xF0
#define CMD_SENDKEY   0xF1
#define CMD_ERASE     0xF2
#define CMD_WRITE     0xF3
#define CMD_VALIDATE  0xF4
#define CMD_ECURESET  0xF5
#define CMD_READ      0xF6
#define CMD_SET_MODE  0xF8

#define CMD_GETDEVCAP 0xFE    //device type
#define CMD_NEG_RESP  0xFF

//--------------------device type 

