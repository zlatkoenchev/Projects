

#define EEP_IsBusy() (EECON1bits.WR)

void Busy_Eep(void);

uint8 Read_Eep(uint8 badd);

void Write_Eep(uint8 badd, uint8 bdata);

void Write_FlashHalfRow(sint16 badd, uint8 *pdata);

void Erase_FlashRow(sint16 badd);

sint16 Read_Flash(sint16 badd) ;


