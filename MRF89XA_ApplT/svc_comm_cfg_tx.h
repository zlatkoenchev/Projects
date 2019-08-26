/* 
 * File:   svc_comm_cfg_tx.h
 * Author: zlatko
 *
 * Created on February 23, 2019, 6:20 PM
 */

#undef COM_SIG_TX


#ifdef TX_SIG_BUF_DEC
#undef TX_SIG_BUF_DEC
#define COM_SIG_TX( sig, ID, typ ) uint8 sig##ID; typ sig##TxBuf; 
#endif

#ifdef TX_SIG_PROC
#undef TX_SIG_PROC
#define COM_SIG_TX( sig, ID, typ ) ComTxData.sig##ID =ID;
#endif


COM_SIG_TX( TxTemp1, SIG_TEMP1, uint16)
COM_SIG_TX( TxHumidity, SIG_HUMIDITY, uint8)        
COM_SIG_TX( TxPresence, SIG_PRESENCE, uint8)
#ifdef USE_RTC_CHIP
COM_SIG_TX(TxTime, SIG_RTIME, TDateTime )
#endif
COM_SIG_TX(TxAct, SIG_ACTUATOR, uint8 )
        