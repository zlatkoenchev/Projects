/* 
 * File:   svc_comm_cfg.h
 * Author: zlatko
 *
 * Created on June 9, 2018, 9:28 AM
 */

#undef COM_SIG_RX


#ifdef RX_SIG_PROC
#undef RX_SIG_PROC
#define COM_SIG_RX( sig, ID , typ, cbk) if (ComData.sigID == ID) { cbk;} else 
#endif


COM_SIG_RX( RxPresence, SIG_PRESENCE, uint8, PRS_OnPIRFrame())
COM_SIG_RX( RxTime, SIG_RTIME, TDateTime, RTC_OnRTCFrame())
//COM_SIG_RX( RxActuator, SIG_ACTUATOR, uint8, CTRL_OnACTFrame())