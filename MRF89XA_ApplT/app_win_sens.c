
#include "types.h"
#include "svc_comm.h"
#include "app_win_sens.h"
#include "svc_nvm.h"

#define NUM_WIN_SENS 2
#define WIN_RELOAD_TIME 255

static uint8 uSc[NUM_WIN_SENS];
static uint8 cntr;
void WIN_Init(void){
    uSc[0] = 0;
    uSc[1] = 0;
    cntr = 0;
}

void WIN_TaskSlow(void){
    //handle 15 min timeout
    cntr++;
    if (cntr>=4){
        cntr = 0;
        if (uSc[0]) {
            uSc[0]--;
        }
        if (uSc[1]) {
            uSc[1]--;
        }
    }
}

uint8 WIN_IsOpen(void) {
    return ((0 != uSc[0]) || (0!=uSc[1])); 
}

void App_OnWinSensor(void) {
    if (RxSRC_NAD() == RAM_TEMP_REGDATA[0]) {
        if ( ComRecvSignal(uint8)){
            uSc[0] = WIN_RELOAD_TIME;
        } else {
            uSc[0] = 0;}
    } else  if (RxSRC_NAD() == RAM_TEMP_REGDATA[1]) {
        if (ComRecvSignal(uint8)) {
            uSc[1] = WIN_RELOAD_TIME;
        } else {
            uSc[1] = 0;
        }
    }
}