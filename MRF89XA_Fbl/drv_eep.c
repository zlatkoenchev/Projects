#include "types.h"
#include "drv_eep.h"


uint8 Read_Eep(uint8 badd) {

    EEADR = badd ;
    EECON1bits.CFGS = 0;
    EECON1bits.EEPGD = 0;
    EECON1bits.RD = 1;
    NOP(); 
    return ( EEDATL); // return with read byte

}

void Write_Eep(uint8 badd, uint8 bdata) {

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

uint16 Read_Flash(uint16 badd) {
    SUSPEND_IT();
    uint16 result;

    EEADR = badd;
    EECON1bits.CFGS = 0;
    EECON1bits.EEPGD = 1;
    EECON1bits.RD = 1;
    NOP();
    NOP();
    RESUME_IT();
    result = (((uint16)EEDATH)<<8) | EEDATL;
    //result <<=8;
    //result |= EEDATL;

    return ( result); // return with read byte
}

void Erase_FlashRow(uint16 badd) {
  
    SUSPEND_IT();
    EEADR = badd & 0xFFE0; //row is 32 word aligned
    EECON1bits.CFGS = 0;
    EECON1bits.EEPGD = 1;
    EECON1bits.FREE = 1;
    EECON1bits.WREN = 1;
    EECON2 = 0x55;
    EECON2 = 0xAA;
    EECON1bits.WR = 1;
    NOP();
    NOP();
    EECON1bits.WREN = 0;
    RESUME_IT();

}

//data low/high
void Write_FlashHalfRow(uint16 badd, uint8 *pdata) 
{
    uint8 i;
    SUSPEND_IT();
    EEADR = badd & 0xFFF0; //half row is 16 word aligned
    EECON1bits.EEPGD = 1;
    EECON1bits.CFGS = 0;
    EECON1bits.WREN = 1;
    EECON1bits.LWLO = 1;
    for (i =0; i<15; i++) //load 15 words
    {
        EEDATL = *pdata;
        pdata++;
        EEDATH = *pdata;
        pdata++;
        EECON2 = 0x55;
        EECON2 = 0xAA;
        EECON1bits.WR = 1;
        NOP();
        NOP();
        EEADRL++;
    }
    EEDATL = *pdata; //load 16th word
    pdata++;
    EEDATH = *pdata;
    EECON1bits.LWLO = 0;
    EECON2 = 0x55;
    EECON2 = 0xAA;
    EECON1bits.WR = 1;
    NOP();
    NOP();
    EECON1bits.WREN = 0;
    RESUME_IT();

}