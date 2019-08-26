#include "types.h"
#include "svc_nvm.h"
#include "drv_relay.h"
#include "drv_relayBS.h"
#include "drv_io.h"
#include "drv_tvalve.h"
#include "drv_photomos.h"
#include "app_control.h"

uint8 u8PWM;

void Rel_Init(void) {
    u8PWM = 0;
    
    switch (RAM_ACTMODE.ActType) {
        case ACT_TYPE_BSRELAY://BISTABLE relay
            RelBS_Init(); 
            break;

        case ACT_TYPE_RELAY://MOSFET / MONOSTABLE relay
            IO_SetREL_ON(0);
            break;

        case ACT_TYPE_PWM://PWM actor
            RelTV_Init();
            IO_SetREL_ON(0);
            IO_SetRelSync(0);
            break;
            
        case ACT_TYPE_PHOTOMOS:
            RelPM_Init();
            break;
    } 
}

void Rel_Task1s(void) {
    if (RAM_ACTMODE.ActType == ACT_TYPE_PWM){
        RelTV_Task1s();
    }
}

void Rel_Task(void) {
    
    switch (RAM_ACTMODE.ActType) {
        case ACT_TYPE_BSRELAY://BISTABLE relay
            RelBS_Task(); 
            break;

        case ACT_TYPE_RELAY://MOSFET / MONOSTABLE relay
            break;

        case ACT_TYPE_PWM://PWM actor
            RelTV_Task();
            break;

        case ACT_TYPE_PHOTOMOS:
            RelPM_Task();
            break;
    }
}

void Rel_Request(uint8 PWM) {
    u8PWM = PWM;
    switch (RAM_ACTMODE.ActType) {
        case ACT_TYPE_BSRELAY://BISTABLE relay
            if (PWM > RAM_THERMO.PWM_ON) {
                if (FALSE == RelBS_IsOn()) {
                    RelBS_Request(TRUE);
                }
            } else {
                if (TRUE == RelBS_IsOn()) {
                   RelBS_Request(FALSE);
                }
            }
            break;

        case ACT_TYPE_RELAY://MOSFET relay
            if (PWM) {
                IO_SetREL_ON(1);
            }
            else {
                IO_SetREL_ON(0);
            }
            break;

        case ACT_TYPE_PWM://PWM actor
            RelTV_Request(PWM);
            break;

        case ACT_TYPE_PHOTOMOS:
            RelPM_Request(PWM);
            break;
    }
}

uint8 Rel_IsOn(void) {
    uint8 res = FALSE;
    switch (RAM_ACTMODE.ActType) {
        case ACT_TYPE_BSRELAY://BISTABLE relay
            res = RelBS_IsOn();
            break;

        case ACT_TYPE_RELAY://MOSFET relay
            res = (u8PWM != 0);
            break;

        case ACT_TYPE_PWM://PWM actor
            res = RelTV_IsOn();
            break;
        case ACT_TYPE_PHOTOMOS:
            res = (u8PWM != 0);
            break;
    }
    return res;
}

uint8 Rel_IsIdle(void) {
    uint8 res = TRUE;
    switch (RAM_ACTMODE.ActType) {
        case ACT_TYPE_BSRELAY://BISTABLE relay
            res = RelBS_IsIdle();
            break;

        case ACT_TYPE_RELAY://MOSFET relay

            break;

        case ACT_TYPE_PWM://PWM actor
            break;

        case ACT_TYPE_PHOTOMOS:
            break;
    }
    return res;
}

uint8 Rel_GetPWM(void) {
    return u8PWM;
}

