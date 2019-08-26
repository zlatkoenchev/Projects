
#include "MRF89XA.h"


#if 0
//70 hopping Channels {R, P, S, BAND}
const freq_t l_ch_0 = {90, 71, 54, 2}; //863.05
const freq_t l_ch_1 = {168, 134, 5, 2}; //863.14
const freq_t l_ch_2 = {95, 75, 55, 2}; //863.25
const freq_t l_ch_3 = {154, 122, 68, 2}; //863.34
const freq_t l_ch_4 = {156, 124, 39, 2}; //863.44
const freq_t l_ch_5 = {127, 101, 26, 2}; //863.55
const freq_t l_ch_6 = {164, 130, 71, 2}; //863.65
const freq_t l_ch_7 = {114, 90, 73, 2}; //863.74
const freq_t l_ch_8 = {95, 75, 59, 2}; //863.85
const freq_t l_ch_9 = {169, 134, 74, 2}; //863.91
const freq_t l_ch_10 = {169, 135, 1, 2}; //864.08
const freq_t l_ch_11 = {95, 75, 61, 2}; //864.15
const freq_t l_ch_12 = {114, 91, 2, 2}; //864.25
const freq_t l_ch_13 = {164, 131, 4, 2}; //864.34
const freq_t l_ch_14 = {127, 101, 34, 2}; //864.45
const freq_t l_ch_15 = {156, 124, 51, 2}; //864.55
const freq_t l_ch_16 = {154, 123, 7, 2}; //864.65
const freq_t l_ch_17 = {95, 75, 65, 2}; //864.75
const freq_t l_ch_18 = {168, 134, 25, 2}; //864.85
const freq_t l_ch_19 = {90, 71, 66, 2}; //864.94
const freq_t l_ch_20 = {95, 75, 67, 2}; //865.05
const freq_t l_ch_21 = {162, 129, 43, 2}; //865.14
const freq_t l_ch_22 = {149, 119, 13, 2}; //865.24
const freq_t l_ch_23 = {127, 101, 42, 2}; //865.35
const freq_t l_ch_24 = {148, 118, 30, 2}; //865.44
const freq_t l_ch_25 = {157, 125, 47, 2}; //865.54
const freq_t l_ch_26 = {95, 75, 71, 2}; //865.65
const freq_t l_ch_27 = {106, 84, 58, 2}; //865.74
const freq_t l_ch_28 = {108, 86, 29, 2}; //865.84
const freq_t l_ch_29 = {95, 75, 73, 2}; //865.95
const freq_t l_ch_30 = {168, 134, 39, 2}; //866.04
const freq_t l_ch_31 = {153, 122, 38, 2}; //866.15
const freq_t l_ch_32 = {127, 101, 50, 2}; //866.25
const freq_t l_ch_33 = {97, 77, 46, 2}; //866.35
const freq_t l_ch_34 = {146, 116, 70, 2}; //866.44
const freq_t l_ch_35 = {95, 76, 2, 2}; //866.55
const freq_t l_ch_36 = {162, 129, 60, 2}; //866.65
const freq_t l_ch_37 = {88, 70, 32, 2}; //866.75
const freq_t l_ch_38 = {95, 76, 4, 2}; //866.85
const freq_t l_ch_39 = {82, 65, 47, 2}; //866.95
const freq_t l_ch_40 = {84, 67, 18, 2}; //867.05
const freq_t l_ch_41 = {127, 101, 58, 2}; //867.15
const freq_t l_ch_42 = {163, 130, 52, 2}; //867.25
const freq_t l_ch_43 = {158, 126, 52, 2}; //867.35
const freq_t l_ch_44 = {95, 76, 8, 2}; //867.45
const freq_t l_ch_45 = {145, 116, 21, 2}; //867.55
const freq_t l_ch_46 = {145, 116, 22, 2}; //867.65
const freq_t l_ch_47 = {95, 76, 10, 2}; //867.75
const freq_t l_ch_48 = {100, 80, 12, 2}; //867.85
const freq_t l_ch_49 = {112, 89, 61, 2}; //867.95
const freq_t l_ch_50 = {127, 101, 66, 2}; //868.05
const freq_t l_ch_51 = {169, 135, 49, 2}; //868.15
const freq_t l_ch_52 = {165, 132, 34, 2}; //868.25
const freq_t l_ch_53 = {95, 76, 14, 2}; //868.35
const freq_t l_ch_54 = {109, 87, 34, 2}; //868.45
const freq_t l_ch_55 = {154, 123, 49, 2}; //868.55
const freq_t l_ch_56 = {95, 76, 16, 2}; //868.65
const freq_t l_ch_57 = {96, 77, 2, 2}; //868.75
const freq_t l_ch_58 = {94, 75, 32, 2}; //868.85
const freq_t l_ch_59 = {127, 101, 74, 2}; //868.95
const freq_t l_ch_60 = {153, 122, 69, 2}; //869.05
const freq_t l_ch_61 = {150, 120, 39, 2}; //869.15
const freq_t l_ch_62 = {95, 76, 20, 2}; //869.25
const freq_t l_ch_63 = {147, 118, 10, 2}; //869.35
const freq_t l_ch_64 = {110, 88, 27, 2}; //869.45
const freq_t l_ch_65 = {95, 76, 22, 2}; //869.55
const freq_t l_ch_66 = {157, 126, 17, 2}; //869.65
const freq_t l_ch_67 = {167, 134, 22, 2}; //869.75
const freq_t l_ch_68 = {127, 102, 7, 2}; //869.85
const freq_t l_ch_69 = {166, 133, 39, 2}; //869.95
#endif


static uint8 ReadFIFO(void);
static void WriteFIFO(uint8);


//First time configuration settings for MRF89XA
const uint8 InitConfigRegs[] = {
    /* 0ok */ CHIPMODE_STBYMODE | FREQBAND_950 | VCO_TRIM_11,
    /* 1ok */ MODSEL_FSK | DATAMODE_PACKET | IFGAIN_0,
    /* 2ok */ FREGDEV_80,
    /* 3ok */ BITRATE_40,
    /* 4ok */ OOKFLOORTHRESH_VALUE,
    /* 5ok */ FIFOSIZE_64 | FIFO_THRSHOLD_1,
    /* 6ok 0x77*/ 125,
    /* 7ok 0x5f*/ 100,
    /* 8ok 0x13*/ 20,
    /* 9ok */ 0x77,
    /* 10ok */ 0x5f,
    /* 11ok */ 0x13,
    /* 12ok */ DEF_PARAMP | PA_RAMP_23,
    /* 13ok */ IRQ0_RX_STDBY_PAYLOADREADY | IRQ1_RX_STDBY_CRCOK | IRQ1_TX_TXDONE,
    /* 14ok */ IRQ0_TX_START_FIFOTHRESH | IRQ1_PLL_LOCK_PIN_ON,
    /* 15ok */ RSSIIRQTHRESH_VALUE,
    /* 16ok */ PASSIVEFILT_378 | RXFC_FOPLUS100,
    /* 17ok */ DEF_RXPARAM1 | FO_100,
    /* 18ok */ POLYPFILT_OFF | SYNC_SIZE_32 | SYNC_ON | SYNC_ERRORS_0,
    /* 19ok */ DEF_RXPARAM3,
    /* 20ok */ 0,
    /* 21ok */ OOK_THRESH_DECSTEP_000 | OOK_THRESH_DECPERIOD_000 | OOK_THRESH_AVERAGING_00,
    /* 22ok */ 'z', // 1st byte of Sync word,
    /* 23ok */ 'z', // 2nd byte of Sync word,
    /* 24ok */ 'l', // 3rd byte of Sync word,
    /* 25ok */ '1', // 4th byte of Sync word,
    /* 26ok */ FC_300 | TX_POWER_LEVEL,// configred power
    /* 27ok */ CLKOUT_OFF | CLKOUT_12800,
    /* 28ok */ MANCHESTER_OFF | 64,
    /* 29ok */ NODEADRS_VALUE,
    /* 30ok */ PKT_FORMAT_VARIABLE | PREAMBLE_SIZE_4 | WHITENING_ON | CRC_ON | ADRSFILT_ME_AND_00, 
    /* 31ok */ FIFO_AUTOCLR_ON | FIFO_STBY_ACCESS_WRITE
};
//declare external variables
 static uint8 RF_Mode;
 uint8 TxPacket[PACKET_LEN];
 uint8 RxPacket[PACKET_LEN];
 uint8 MRF89XA_RSSI;
#ifdef ERROR_ENABLED 
 uint8 MRF89XA_Error;
#endif
 
 
uint8 MRF89XAInit(void){
    uint8 input, i, res;
    
    for (i = 0; i <= 31; i++) {
        MRF89XARegisterSet(i, InitConfigRegs[i]);	 
    }
    
    /* clear PLL_LOCK flag so we can see it restore on the new frequency */\
	input = MRF89XARegisterRead(REG_IRQPARAM1);
    MRF89XARegisterSet(REG_IRQPARAM1, (uint8)(input | 0x02));
    
    MRF89XASetRFMode(RF_SYNTHESIZER);
    i = 255;
    res = FALSE;
    while (i--)
    {
        input = MRF89XARegisterRead(REG_IRQPARAM1);
        if (input & 0x02)
        {
            i = 0;
            res = TRUE;
        }
    }
        
    MRF89XASetRFMode(RF_STANDBY);
    
    input = MRF89XARegisterRead(REG_IRQPARAM1);
    MRF89XARegisterSet(REG_IRQPARAM1, (uint8)(input | 0x02));//clear pll
#ifdef ERROR_ENABLED    
    MRF89XA_Error =
#endif
    RxDataLen = MRF89XA_RSSI = 0;
    return res;
}

void MRF89XARegisterSet(uint8 address, uint8 value){
    REG_CS(0);
    address = (uint8)(address << 1);
    SPI_HF_Put(address);
    SPI_HF_Put(value);
    REG_CS(1);
}

uint8 MRF89XARegisterRead(uint8 address){
    uint8 value;
    REG_CS(0);
      
    address = (uint8) ((address << 1) | 0x40);
    SPI_HF_Put(address);
    value = SPI_HF_Get();
    REG_CS(1);
    return value;
}

void MRF89XAStartReception(void){
    uint8 i;
    RxDataLen = 0;
    MRF89XASetRFMode(RF_STANDBY);
    //Reset FIFO
    i = MRF89XARegisterRead(REG_IRQPARAM0);
    MRF89XARegisterSet(REG_IRQPARAM0, (uint8) (i | IRQ1_FIFO_OVERRUN_CLEAR));
    
#ifndef RX_POLLING
    IRQ1_pin = 0;
#endif
    
    MRF89XASetRFMode(RF_RECEIVER);
}

//todo set power
void MRF89XASendFrame(void){
    uint8 i;
    
    MRF89XASetRFMode(RF_STANDBY);
    MRF89XARegisterSet(REG_PKTPARAM3, (uint8) ((InitConfigRegs[REG_PKTPARAM3] & 0xBF) | FIFO_STBY_ACCESS_WRITE));
    MRF89XARegisterSet(REG_IRQPARAM0, (uint8) (InitConfigRegs[REG_IRQPARAM0] | IRQ1_FIFO_OVERRUN_CLEAR));
    MRF89XARegisterSet(REG_IRQPARAM1, (uint8) ((InitConfigRegs[REG_IRQPARAM1]) | 0x02));//pll clear
    //copy data to FIFO

    for (i = 0; i <= TxDataLen; i++) {
        WriteFIFO(TxPacket[i]);
    }
    
    MRF89XASetRFMode(RF_TRANSMITTER);
#ifdef TX_POLLING   
    i = 1;
    while (i)
    {
       i = MRF89XARegisterRead(REG_IRQPARAM0) & 0x02;//poll FIFOEMPTY
    }
#else
    //while (0 == IRQ1_pin); //Wait until TX Done interrupt and restore the RF state to standby mode
#endif 
    
    //MRF89XASetRFMode(RF_STANDBY);
}

static void WriteFIFO(uint8 Data) 
{
    DATA_CS(0);
    SPI_HF_Put(Data);
    DATA_CS(1);
}

static uint8 ReadFIFO(void){
    uint8 value;
    DATA_CS(0);
    value = SPI_HF_Get();
    DATA_CS(1);
    return value;
}

void MRF89XASetRFMode(uint8 mode) {
    uint8 mcparam0_read;
#if defined( TX_POLLING) || defined(RX_POLLING)
#else
    IRQ1_pin = 0;
#endif
    
    mcparam0_read = InitConfigRegs[REG_MCPARAM0] &0x1F;
    mcparam0_read |= mode;
    MRF89XARegisterSet(REG_MCPARAM0, mcparam0_read );
    RF_Mode = mode;
}


#ifdef RSSI_ENABLED
void MRF89XACheckRSSI(void){
    MRF89XA_RSSI = MRF89XARegisterRead(REG_RSSIVALUE);
}
#endif

void MRF89XATask(void){
    
    if (RF_RECEIVER == RF_Mode)
    {
        uint8 i;
        uint8 k;
        
#ifdef RX_POLLING
        k = MRF89XARegisterRead(REG_PKTPARAM2) & 0x01; //poll STSCRCEN
        if (k)
#else
        if (IRQ1_pin)
#endif
        {
#ifdef RSSI_ENABLED            
            MRF89XACheckRSSI();
#endif  
            MRF89XASetRFMode(RF_STANDBY);
            MRF89XARegisterSet(REG_PKTPARAM3, (uint8)((InitConfigRegs[REG_PKTPARAM3] & 0xBF) | FIFO_STBY_ACCESS_READ));
      
            i = ReadFIFO(); //read lenght
            if (i <= PAYLOAD_LEN)   {
                RxPacket[0] = i;
                k = 0;
                while (i) {
                    RxPacket[++k] = ReadFIFO();
                    i--;
                }
            }
            
            //flush fifo
            while (MRF89XARegisterRead(REG_IRQPARAM0) & 0x02) {
                ReadFIFO();
            }
#ifdef ERROR_ENABLED          
            if (0 == RxDataLen) {
                MRF89XA_Error = TRUE;
            }
#endif
        } 
    }
}