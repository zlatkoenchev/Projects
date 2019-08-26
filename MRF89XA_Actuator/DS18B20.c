
#include "types.h"

#define PIN_IN    TRISB7 = 1
#define PIN_LEVEL RB7
#define PIN_OUT   TRISB7 = 0
#define PIN_LOW   LATB7 = 0

static uint8 status;
static uint8 state;
static uint8 delay;
uint16 DS18B20_temp;

#define DS_WAIT(t,ac) {i = t; do { ac; i--;} while (i);}

//calibrated for 2Mhz
uint8  DS_Reset(void){
	uint8 i;
    uint8 r;
    
	PIN_IN;
    PIN_LOW;
    PIN_IN;
    DS_WAIT(63, PIN_IN); //500us high
   	
	PIN_OUT;
    DS_WAIT(63, PIN_OUT); //500us low
       
    PIN_IN;
    DS_WAIT(7, PIN_IN); //65us high
    
	r = PIN_LEVEL;
    PIN_IN;
    DS_WAIT(63, PIN_IN); //500us high
    
	return r;
}

//
// Write a bit. Port and bit is used to cut lookup time and provide
// more certain timing.
//
void DS_Write_bit(uint8 v) {
	uint8 i;
	PIN_LOW;
	PIN_OUT;
	PIN_OUT;
	PIN_OUT;//6us low
	if (v & 1) {
        PIN_IN;
        DS_WAIT(6, PIN_IN); //60us high
	}
	else {
        PIN_OUT;
        DS_WAIT(6, PIN_OUT); //60us low
	}
	PIN_IN;
	PIN_IN;
	PIN_IN;
	PIN_IN;
	PIN_IN;
}

//
// Read a bit. Port and bit is used to cut lookup time and provide
// more certain timing.
//
uint8 DS_Read_bit(void) {
    uint8 r;
	uint8 i;
	
    PIN_LOW;
	PIN_OUT;
	PIN_OUT;
	PIN_OUT;//6us
	PIN_IN;
	PIN_IN;
	PIN_IN;
	PIN_IN;//8us
	r = PIN_LEVEL;
	PIN_IN;
    DS_WAIT(6, PIN_IN); //50us high
    return r;
}

//
// Write a byte. The writing code uses the active drivers to raise the
// pin high, if you need power after the write (e.g. DS18S20 in
// parasite power mode) then set 'power' to 1, otherwise the pin will
// go tri-state at the end of the write to avoid heating in a short or
// other mishap.
//
void DS_Write(uint8 v) {
    uint8 i =8;
	while (i--) {
		DS_Write_bit(v & 1);
		v = v >> 1;
    }
}

//
// Read a byte
//
uint8 DS_Read(void) {
    uint8 bitMask;
    uint8 r = 0;
    
    for (bitMask = 0x01; bitMask; bitMask <<= 1) {	
		if ( DS_Read_bit()) {
			r |= bitMask;
		}
    }
	return r;
}




void DS18B20_Init(void){
	delay = status =  state = 0;
}


void DS18B20_Task(void) {
	if (status) {
        DS18B20_Init();
    }
	
    if (delay ) {
        delay--;
        return;
    }
    
	switch (state)
	{
		case 0:
            status = DS_Reset();
            state++;
            break;
        case 1:
			DS_Write(0xCC);         // Skip ROM
			state++;
            break;
		case 2:
			DS_Write(0x44);         // Convert
			state++;
            delay = 50;
            break;
		case 3:
			status = DS_Reset();
			state++;
            break;
		case 4:
			DS_Write(0xCC);         // Skip ROM
			state++;
            break;
		case 5:
			DS_Write(0xBE);         // Read RAM
			state++;
            break;
		case 6:
			DS18B20_temp = DS_Read();         // Read RAM
			DS18B20_temp |= ((uint16)(DS_Read() << 8)); 
			state++;
            delay = 250;
            break;
		case 7:
			state = 0;
            delay = 250;
            break;
        default:
            state = 0;
            break;
	}
}




