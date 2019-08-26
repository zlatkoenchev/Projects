#include "types.h"
#include "svc_comm.h"
#include "drv_eep.h"
#include "MRF89XA.h"
#include "main.h"
#include "drv_io.h"

#include "app_Presence.h"
#include "svc_uds.h"
#include "svc_nvm.h"
#include "app_control.h"

#ifdef RUNTIME_PRESENT 
#include "runtime.h"
#endif
#ifdef REMOTE_AIR_SENS_PRESENT
#include "drv_air_sens.h"
#endif
#ifdef WINDOW_SENSOER_PRESENT
#include "app_win_sens.h"
#endif

////////////////////////////////////////////////////////////////
TComTxData ComTxData;

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
 
static void TransmitFrame(void);
static uint8 Comm_IsAlreadyReceived(void);
/////////////////////////////////////////////////////////

static void Comm_PrepareTransmit(void) {
    ComData.CSRetries = CSMA_RETRY;
    ComData.bTxState = 1;
    IO_StartTimer1(IO_Time1ms); //send asap
}

 void NEG_RESP(uint8 c){
     if (RxDEST_NAD() != 0) {
        TxCMD = CMD_NEG_RESP;
        TxData(0) = c;
        TxDataLen = 5; //l,da,sa,res,cmd, data
     }
}

 void POS_RESP(uint8 len){
     if (RxDEST_NAD() != 0) {
        TxCMD = RxCMD();
        TxDataLen = (uint8)(len+4); //l,da,sa,res,cmd, data
     }
}

static void ACK_RESP(void){
    if (Comm_GetMyNAD() != 254)
    {
        POS_RESP(0);
    }
}

static void Comm_InitMRF(void) {
    if (FALSE == MRF89XAInit()) {
        asm("RESET");
    }
    //data valid?
    MRF89XARegisterSet(REG_SYNCBYTE0, RAM_NWID[0]);
    MRF89XARegisterSet(REG_SYNCBYTE1, RAM_NWID[1]);
    MRF89XARegisterSet(REG_SYNCBYTE2, RAM_NWID[2]);
    MRF89XARegisterSet(REG_SYNCBYTE3, RAM_NWID[3]);
    ComData.MY_NAD = RAM_NWID[4];
    MRF89XARegisterSet(REG_NODEADDRESS, ComData.MY_NAD);
    
}

void Comm_Init(void){
          
    Comm_InitMRF();
 
    //send ecu reset response
    TxCMD = CMD_ECURESET;
    TxDataLen = 5;
    TxDEST_NAD = 255;
    TransmitFrame();
    MRF89XAStartReception(); 
    
    ComData.bUnLocked = 0;
    ComData.bTxON = 1;
    ComData.bTxState = FALSE;
    ComData.TxPeriod = 0;

    ComData.RxIx = 0;
    while (ComData.RxIx < GW_BUFF_SIZE) {
        ComData.RxNADs[ComData.RxIx] = 0;
        ComData.RxTMRs[ComData.RxIx] = 0;
        ComData.RxIx++;
    }
  
    //fill signal IDs
#define TX_SIG_PROC
#include "svc_comm_cfg_tx.h"
}

static void TransmitFrame(void) {
    TxSRC_NAD = ComData.MY_NAD;
    //TxRSV = (TxRSV+1) & 0x0F; //increment frame counter
    TxRSV = 0;
    IO_DisablePIR();
    MRF89XASendFrame();
    IO_StartTimer1(IO_TimeMS(26)); //TX frame time should be below 16ms
    while ((MRF89XAIsBusy()) && (!IO_IsTimer1Elapsed())){
    
    }
    //problem in transmission?
    if (IO_IsTimer1Elapsed()) {
        Comm_InitMRF();
    } else {
        MRF89XASetRFMode(RF_STANDBY);
    }
}

static void Comm_RxProcess(void){
    if (Comm_IsAlreadyReceived()){
        return;
    }
    NO_RESP(); //assume no response
    switch (RxCMD()) {
      case CMD_STATUS_INFO:
          ComData.RxIx = C_PAGE;
          //parse signals
          while (ComData.RxIx < RxDataLen){
              ComData.sigID = RxData(ComData.RxIx);
#define RX_SIG_PROC
#include "svc_comm_cfg_rx.h"
              {
                 //unknown signal
              }
              ComData.RxIx = ComData.RxIx + (ComData.sigID & 0x0F) + 1;
          }
          break;

      case CMD_GETSEED:
          if (RxDEST_NAD() != 0){
                UDS_GetSeed();
          }
         break;

       case CMD_SENDKEY:
           if (RxDEST_NAD() != 0) {
                if (UDS_CompareKey()) {
                       ComData.bUnLocked = 1; 
                }
           }
         break;

        case CMD_INVALIDATE:
            if (RxDEST_NAD() != 0) {
                if ( ComData.bUnLocked ) {
                    Write_Eep(APP_VALID_FLAG_ADDR, 255);
                    POS_RESP(0);
                }
            }
         break;
           
        case CMD_WRITE:
            NEG_RESP(0x22);
            if (RxDEST_NAD() != 0) {
                if (ComData.bUnLocked) {
                    UDS_WDBID();
                }
            }
            break;
            
         case CMD_READ:
            NEG_RESP(0x22);
            if (RxDEST_NAD() != 0) {
                UDS_RDBID();
            }
            break;
                
          case CMD_ECURESET:
            if (RxDEST_NAD() != 0) {
                if (ComData.bUnLocked) {
                    RequestReset();
                }
            }
          break;

          case CMD_COM_CTL:
             if (0xA4 == RxData(C_PAGE)) {
                ComData.bTxON =0;  
             } else if (0x4A == RxData(C_PAGE)) {
                 ComData.bTxON = 1;
                 ComData.bUnLocked = 0;
             }
          break;
         
#ifdef RUNTIME_PRESENT
        case CMD_ENERGY_CLR:
            Rut_OnClearPower();
            break;
#endif
              
          default:
              
          break;
    }
      
   if (TxCMD != CMD_NONE)
   {     
        TxDEST_NAD = RxSRC_NAD();
        Comm_PrepareTransmit();
   }
}

void Comm_TaskSlow(void) {
    if (ComData.TxPeriod < COM_TX_SEND_PERIOD) {
        ComData.TxPeriod++;
    }
    else {
        ComData.bTxReq = 1;
    }
}

void Comm_Task(void){
    if ((ComData.bTxReq) && 
        (0==ComData.bTxState) && 
        (ComData.bTxON) && 
        (ComData.TxPeriod)) 
    {
        ComData.bTxReq = 0;
        ComData.TxPeriod = 0;
        TxDEST_NAD = 0;
        TxCMD = CMD_STATUS_INFO;
        TxDataLen = 4 + sizeof (TComTxData);
        //copy signal frame to Tx buffer
        *((TComTxData *)(&TxData(0))) = ComTxData;
        Comm_PrepareTransmit();
    }
    
    //after timeout , clear buffered NADs
    ComData.RxIx = 0;
    while (ComData.RxIx < GW_BUFF_SIZE) {
        if (ComData.RxTMRs[ComData.RxIx]){
            ComData.RxTMRs[ComData.RxIx]--;
        }
        else {
            ComData.RxNADs[ComData.RxIx] = 0;
        }
        ComData.RxIx++;
    }

}

void Comm_OnIdle(void){ 
    if (ComData.bTxState)
    {
            if (!IO_IsTimer1Elapsed()) {return;}
            MRF89XACheckRSSI();
            if (MRF89XA_RSSI > MIN_RSSI)
            {
                //channel busy
                IO_StartTimer1(IO_TimeMS(20));//wait 20ms and try again
                if (ComData.CSRetries) {
                    ComData.CSRetries--;
                }
                else 
                {
                    ComData.bTxState = 0; //abort transmission
                    MRF89XAStartReception();
                }
            }
            else {
                TransmitFrame();
                ComData.bTxState = 0;
                MRF89XAStartReception();
            }
    }
    else {
          MRF89XATask();
          if (RxDataLen) {
              Comm_RxProcess();
              MRF89XAStartReception();
          } else if (MRF89XA_Error) {
                Comm_InitMRF();
                MRF89XAStartReception();
          }
    }
}

static uint8 Comm_IsAlreadyReceived(void) {
    if (RxDEST_NAD() != 0) {
        return FALSE;//frame for me
    }
    //check if this NAD:CTR was already received before
    ComData.RxIx = ComData.sigID = 0;
    ComData.Min = 255;
    while (ComData.RxIx < GW_BUFF_SIZE) {
        if ((ComData.RxNADs[ComData.RxIx] == RxSRC_NAD()) &&
            (ComData.RxCTRs[ComData.RxIx] == (RxRSV() & 0x0F))) {
                //this NAD:CTR was already received! Ignore it
                return TRUE;
        }
        
        if (ComData.RxTMRs[ComData.RxIx] < ComData.Min ){
            ComData.Min = ComData.RxTMRs[ComData.RxIx];
            ComData.sigID = ComData.RxIx;
        }
        ComData.RxIx++;
    }
    //find oldest frame counter and overwrite it with just received
    ComData.RxNADs[ComData.sigID]  = RxSRC_NAD();
    ComData.RxCTRs[ComData.sigID]  = RxRSV() & 0x0F;
    ComData.RxTMRs[ComData.sigID] = GW_FRAME_TIMEKEEP;
    return FALSE;
}




