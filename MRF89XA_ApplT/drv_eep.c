#include "types.h"
#include "drv_eep.h"


uint8 Read_Eep(uint8 badd) 
{
    EEADR = badd ;
    EECON1bits.CFGS = 0;
    EECON1bits.EEPGD = 0;
    EECON1bits.RD = 1;
    NOP(); 
    return ( EEDATL); // return with read byte
}

void Write_Eep(uint8 badd, uint8 bdata) 
{
    SUSPEND_IT();
    EEADR = badd ;
    EEDATL = bdata;
    EECON1bits.EEPGD = 0;
    EECON1bits.CFGS = 0;
    EECON1bits.WREN = 1;
    EECON2 = 0x55;
    EECON2 = 0xAA;
    EECON1bits.WR = 1;
    while (EECON1bits.WR); //Wait till the write completion
    RESUME_IT();
    EECON1bits.WREN = 0;
}

