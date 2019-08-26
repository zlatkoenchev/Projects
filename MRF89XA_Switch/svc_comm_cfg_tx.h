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

#ifdef Si7021_PRESENT
COM_SIG_TX( TxTemp1, SIG_TEMP1, uint16)
COM_SIG_TX( TxHumidity, SIG_HUMIDITY, uint8) 
#endif
COM_SIG_TX( TxPresence, SIG_PRESENCE, uint8)
COM_SIG_TX( Energy1, SIG_ENERGY1, uint32)
COM_SIG_TX( Energy2, SIG_ENERGY2, uint32)
COM_SIG_TX( TxAct,  SIG_ACTUATOR, uint8)
        
        