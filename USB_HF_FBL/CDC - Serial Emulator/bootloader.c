#include "types.h"
#include "bootloader.h"

#include "MRF89XA.h"

#define NWID_ADDR 0xF0

#define APP_VALID_FLAG_ADDR 0xFF
#define APPL_START_ADDR 0x500
#define APPL_END_ADDR 0x2000
#define FLASH_PAGE 32
#define PAGE_FLASH    0x01
#define PAGE_EEPROM   0x02


#define POS_RESP()   TxCMD = RxCMD();TxDataLen = 4

#define NEG_RESP(c)  TxCMD = CMD_NEG_RESP;TxData(0) = c; TxDataLen = 5; //l,da,sa,,res,cmd, data


#define Boot_AppValid() (AppValidFlag == APPL_VALID_VALUE)

#define FLASH_UNLOCK 0xA5
#define FLASH_ERASED 0xAC
#define FLASH_WRITTEN 0xAE

#define MY_NAD 0

static uint8 NWID[6];
static uint8 seed_stored;
static uint8 seed_received;
static uint8 FlashUnlocked;
static uint8 AppValidFlag;
static void Boot_EraseApp(void);



void Boot_Init(void)
{
   
 
    FlashUnlocked = 0;
   
}

void Boot_RxProcess(void)
{
   uint8 i;
   uint16 addr;
   volatile uint16 data;
   uint16 datar;
      
   {
        NEG_RESP(0x22);
        switch (RxCMD()) 
        {               
            case CMD_ERASE:
                    Boot_EraseApp();
                    FlashUnlocked = FLASH_ERASED;
                    POS_RESP();
                break;
            case CMD_WRITE:
                if (PAGE_FLASH == RxPage()) 
                {
                    if ((FLASH_ERASED == FlashUnlocked)   &&
                        (RxDataLen == 39)) //len,nad,nad,res,cmd,page,add2,data32
                    {
                        addr = RxAddr16();
                        //Write_FlashHalfRow(addr, &RxFlashData());
                        //FlashUnlocked = FLASH_WRITTEN;
                        TxCMD = RxCMD();
                        
                        data = 0;
                        for (i = 0; i < 16; i++) {
                            datar = RxPacket[C_FLASHDATA+1+i+i];
                            datar <<=8;
                            datar += RxPacket[C_FLASHDATA  + i + i]; 
                            data += datar ;
                        }
                        TxData(0) = (uint8) (data & 0xFF);
                        TxData(1) = (uint8) ((data >> 8)& 0xFF);
                        TxDataLen = 4 + 2; //l,da,sa,res,cmd, data
                    }
                } 
                else if (RxPage() == 0xF0)//reg set 
                {
                    MRF89XARegisterSet(RxPacket[C_PAGE + 1], RxPacket[C_PAGE + 2]);
                    POS_RESP();
                }
                break;
            case CMD_VALIDATE:
                //if (FLASH_WRITTEN == FlashUnlocked) 
                {
                   // Write_Eep(APP_VALID_FLAG_ADDR, (APPL_VALID_VALUE));
                   // if (APPL_VALID_VALUE == Read_Eep(APP_VALID_FLAG_ADDR))
                    {
                        FlashUnlocked = 0;
                        POS_RESP();
                    }
                }
                break;
                
            case CMD_ECURESET:
                POS_RESP();
                break;            
          
            case CMD_READ:
                if (RxPage() == 1 )//read DID 1
                {
                    TxCMD = RxCMD();
                    TxData(0) = 2;//boot
                    TxData(1) = MRF89XA_RSSI;
                    TxData(2) = 0;//dev caps
                    TxData(3) = 0;
                    TxDataLen = 4 + 4; //l,da,sa,res,cmd, data
                }
                break;
          
            default:
                break;
        }

        data = 2000;
        while (data){//wait some time before answer to setup Rx mode in receiver!!!
            TxDEST_NAD = RxSRC_NAD();
            TxSRC_NAD = MY_NAD;
            data--;
        }
        MRF89XASendFrame();
   }
}

static void Boot_EraseApp(void)
{
    
    
}
