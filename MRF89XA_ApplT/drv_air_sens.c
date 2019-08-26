#include "types.h"
#include "drv_io.h"
#include "svc_comm.h"
#include "svc_nvm.h"
#include "app_RTC.h"
#include "drv_si7021.h"


sint16 currtemp;
uint8 currhum;
static uint8 ftimer; 
static uint8 oldhrs;
uint8 TEMP_HISTORY[24];

void AirS_Init(void) {
    uint8 i;
    currtemp = 200;
    currhum = 255;
    ftimer = 0;
    oldhrs = 255;
    
    for ( i=0; i<24;i++)  {
        TEMP_HISTORY[i]=255;//invalid
    }
#ifdef Si7021_PRESENT
    Si7021_Init();
#endif

}

void AirS_Task(void) {
#ifdef Si7021_PRESENT
    Si7021_Task();
#endif
}

void AirS_Task_Slow(void) {
    if (ftimer) {
        ftimer--;
    } else {
#ifdef Si7021_PRESENT
        currtemp = Si7021_GetTemp();
        currhum = Si7021_GetHum(); 
#endif
#ifdef TMP36_PRESENT
        currtemp = IO_GetTempMeas();
        currhum = 255;//invalidate
#endif
    }
    
    ComSendSignal(TxTemp1, currtemp );
    ComSendSignal(TxHumidity, currhum);  
    
    if (RTC_IsTimeOk()){
        if (oldhrs != DateTime.Hours){
            oldhrs = DateTime.Hours;
            TEMP_HISTORY[RTC_BCD2DEC(oldhrs)] = (uint8) (currtemp >>1); //0.2C
        }
    }
}

#ifdef REMOTE_AIR_SENS_PRESENT
void App_OnAirTempSig(void) {
    if (RxSRC_NAD() == RAM_TEMP_REGDATA[2]) {
        
        currtemp = ComRecvSignal(uint16);
        
        if (currtemp == 65535) {
            ftimer = 0;//force local reading
        } else {
            ftimer = 255;
        }
    }
}

void App_OnAirHumSig(void) {
    if (RxSRC_NAD() == RAM_TEMP_REGDATA[2]) {
        currhum = ComRecvSignal(uint8);
    }
}
#endif