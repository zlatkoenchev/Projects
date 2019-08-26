#include "types.h"
#include "svc_comm.h"
#include "drv_eep.h"
#include "MRF89XA.h"
#include "main.h"
#include "svc_nvm.h"


////////////////////////////////////////////////////////////////

#define APP_VALID_FLAG_ADDR 0xFF
#define APPL_START_ADDR 0x500
#define APPL_END_ADDR 0x2000
#define FLASH_PAGE 32

#define NO_RESP()    TxCMD = CMD_NONE;TxDataLen=0;
#define MIN_RSSI        130 //-65dB
#define TX_RETRY        2
#define CSMA_RETRY      5


TComData ComData;
//3612
 

/////////////////////////////////////////////////////////
void Comm_Init(void){
         
    if (FALSE == MRF89XAInit()) {
        asm("RESET");
    }
    //data valid?
    MRF89XARegisterSet(REG_SYNCBYTE0, ROM_NWID[0]);
    MRF89XARegisterSet(REG_SYNCBYTE1, ROM_NWID[1]);
    MRF89XARegisterSet(REG_SYNCBYTE2, ROM_NWID[2]);
    MRF89XARegisterSet(REG_SYNCBYTE3, ROM_NWID[3]);
    ComData.MY_NAD = ROM_NWID[4];
    MRF89XARegisterSet(REG_NODEADDRESS, ComData.MY_NAD);
    MRF89XASetRFMode(CHIPMODE_SLEEPMODE);
    TRISC5 = 0; //out to avoid float IRQ
  
}

 void Comm_Transmit(uint8 val) {
    uint8 input;
    //wakeup from sleep
    TRISC5 = 1; //input
    MRF89XASetRFMode(RF_STANDBY);
    TxDEST_NAD = 0;
    TxSRC_NAD = ComData.MY_NAD;
    TxCMD = CMD_STATUS_INFO;
    TxData(0) = SIG_SWITCH;
    TxData(1) = val;
    TxData(2) = SIG_BATTERY;
    TxData(3) = CalcUbat();
    TxDataLen = 8;
    TxRSV = 0;
    GotoSleep(SLP_4MS);
    /* clear PLL_LOCK flag so we can see it restore on the new frequency */\
    input = MRF89XARegisterRead(REG_IRQPARAM1);
    MRF89XARegisterSet(REG_IRQPARAM1, (uint8) (input | 0x02));
    MRF89XASetRFMode(RF_SYNTHESIZER);
    GotoSleep(SLP_2MS);
    input = MRF89XARegisterRead(REG_IRQPARAM1);
    if (input & 0x02) {
        MRF89XASendFrame();
        while (MRF89XAIsBusy()) {
        }
    }    
    else {
        asm("RESET");
    }
    
    //wait 1 bit
    input = 10;
    while (input--);
    //set MRF to sleep mode
    MRF89XASetRFMode(CHIPMODE_SLEEPMODE);
    TRISC5 = 0; //out to avoid float IRQ
}
 
