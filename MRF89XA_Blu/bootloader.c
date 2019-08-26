#include "types.h"
#include "bootloader.h"
#include "drv_eep.h"


#define NWID_ADDR 0xF0

#define APP_VALID_FLAG_ADDR 0xFF
#define FBL_START_ADDR 0x0
#define FBL_END_ADDR 0x380

#define FBL_NEW_START_ADDR 0x1000
#define FBL_NEW_END_ADDR   0x1380


#define FLASH_PAGE 32
#define PAGE_FLASH    0x01
#define PAGE_EEPROM   0x02



uint16 buf[32];




void Boot_EraseFbl(void){

   uint16 addr;

   addr = FBL_START_ADDR;

   while (addr < FBL_END_ADDR) {
        Erase_FlashRow(addr);
        addr += FLASH_PAGE;
   }
}

void Boot_ProgrFbl(void) {
    
    uint8 i;
    uint16 addr = FBL_START_ADDR;
    uint16 bluaddr = FBL_NEW_START_ADDR;
    
    while (bluaddr < FBL_NEW_END_ADDR) {
        for (i = 0; i < 16; i++) {
            buf[i] = Read_Flash(bluaddr++);
        }
        Write_FlashHalfRow(addr, &buf[0]);
        addr += 16;
    }
      
 
    //invalidate Blu and reset
    Write_Eep(APP_VALID_FLAG_ADDR, 0);
    asm("RESET");
}

