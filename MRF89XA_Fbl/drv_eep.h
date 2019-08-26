

#define EEP_IsBusy() (EECON1bits.WR)

void Busy_Eep(void);

uint8 Read_Eep(uint8 badd);

void Write_Eep(uint8 badd, uint8 bdata);

void Write_FlashHalfRow(uint16 badd, uint8 *pdata);

void Erase_FlashRow(uint16 badd);

uint16 Read_Flash(uint16 badd) ;


