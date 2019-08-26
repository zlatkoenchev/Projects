#include "types.h"
#include "bootloader.h"
#include "drv_eep.h"
#include "MRF89XA.h"

#define NWID_ADDR 0xF0

#define APP_VALID_FLAG_ADDR 0xFF
#define APPL_START_ADDR 0x380
#define APPL_END_ADDR 0x2000
#define FLASH_PAGE 32
#define PAGE_FLASH    0x01
#define PAGE_EEPROM   0x02

#define NO_RESP()    TxDataLen = 0
#define Boot_AppValid() (AppValidFlag == APPL_VALID_VALUE)


#define FLASH_ERASED 1
#define FLASH_WRITTEN 2

#define MY_NAD NWID[4]

static uint8 NWID[6];
static uint8 FlashState;
static uint8 AppValidFlag;
static void Boot_EraseApp(void);
static uint16 oldaddress;

#define NEG_RESP( c) TxCMD = CMD_NEG_RESP;TxData(0) = c; TxDataLen = 5; //l,da,sa,res,cmd, data


void POS_RESP(uint8 len){
    TxCMD = RxCMD();
    TxDataLen = (uint8)(4+len);
}

void Boot_CheckValidApp(void) {
    AppValidFlag = Read_Eep(APP_VALID_FLAG_ADDR);

    if (Boot_AppValid()) {
        asm("GOTO 0x380");
    }
}

void Boot_Init(void){
    uint8 i;
    uint8 ad = NWID_ADDR ;
    uint8 cs = 0;
        
    //bootmode requested, try to init RF
    if (FALSE == MRF89XAInit())
    {
        asm("RESET");
    }
    //read eeprom NWID if stored
    for (i=0; i<5; i++)
    {
        NWID[i] = Read_Eep(ad++);
        cs += NWID[i];
    }
    
    if (cs != Read_Eep(NWID_ADDR + 5))
    {
        NWID[0] = 122;//set defaults
        NWID[1] = 122;
        NWID[2] = 108;
        NWID[3] = 49;
        NWID[4] = 254;
    }
    
    MRF89XARegisterSet(REG_SYNCBYTE0, NWID[0]);
    MRF89XARegisterSet(REG_SYNCBYTE1, NWID[1]);
    MRF89XARegisterSet(REG_SYNCBYTE2, NWID[2]);
    MRF89XARegisterSet(REG_SYNCBYTE3, NWID[3]);
    MRF89XARegisterSet(REG_NODEADDRESS, NWID[4]);
    
    FlashState = 0;
    oldaddress = 0;
    TxRSV = 0;
    //send pos response to fbl jump
    TxCMD = CMD_ECURESET;
    TxDataLen = 4 ; //l,da,sa,res,cmd
    TxDEST_NAD = 255;//FF flash tool, 254 unassigned
    TxSRC_NAD = MY_NAD;
    MRF89XASendFrame();
    while (MRF89XAIsBusy());
    MRF89XASetRFMode(RF_STANDBY);
}

void Boot_RxProcess(void){
   uint8 i;
   volatile uint16 delay = 1000;
   uint16 addr;
   uint16 data;
   
   
   if (MY_NAD == RxDEST_NAD()) {
       NEG_RESP(0x22);
        switch (RxCMD()) 
        {               
            case CMD_ERASE:
                    addr = APPL_START_ADDR;

                    while (addr < APPL_END_ADDR) {
                        Erase_FlashRow(addr);
                        addr += FLASH_PAGE;
                    }
                    FlashState |= FLASH_ERASED;
                   
                    
                    POS_RESP(0);
                break;
            case CMD_WRITE:
                
                if (PAGE_FLASH == RxPage()) 
                {
                    if ((FLASH_ERASED & FlashState) &&
                        (RxDataLen == 39)) //len,nad,nad,res,cmd,page,add2,data32
                    {
                        addr = RxAddr16();
                        if (addr>=APPL_START_ADDR)
                        {
                            if (addr != oldaddress)//check if same address is send at comm retry
                            {
                                Write_FlashHalfRow(addr, &RxFlashData());
                                FlashState |= FLASH_WRITTEN;
                                oldaddress = addr;
                                
                            }
                            data = 0;
                            for ( i=0; i<16; i++ )
                            {
                                data += Read_Flash(addr++);
                            }
                            TxData(0) = (uint8) (data);
                            TxData(1) = (uint8) ((data >> 8));
                            POS_RESP(2); //l,da,sa,res,cmd, data
                        }
                          
                    }
                } 
                break;
            case CMD_VALIDATE:
                if (FLASH_WRITTEN & FlashState) 
                {
                    Write_Eep(APP_VALID_FLAG_ADDR, (APPL_VALID_VALUE));
                    POS_RESP(0);
                }
                
                break;
                
            case CMD_ECURESET:
                asm("RESET");
                break;            
          
            case CMD_READ:
                if (RxPage() == 1){
                   TxData(0) = 2;//boot
                   TxData(1) = MRF89XA_RSSI;
                   TxData(2) = TxData(3) = 0;
                   POS_RESP(4); //l,da,sa,cmd, data, rssi
                }
                
                break;
                
            default:
               
                break;
        }

        TxDEST_NAD = RxSRC_NAD();
        TxSRC_NAD = MY_NAD;
        TxRSV = RxRSV() & 0x7F;
        
        while (delay--);

        MRF89XASendFrame();
        while (MRF89XAIsBusy());
        MRF89XASetRFMode(RF_STANDBY);
   } 
}

