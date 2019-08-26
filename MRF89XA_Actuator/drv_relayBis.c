
#include "types.h"
#include "drv_io.h"
#include "drv_relayBS.h"
#include "main.h"
#include "svc_nvm.h"

typedef enum{
    REL_IDLE,
    REL_WAIT
} TRelState;

#define DELAY_RECHARGE 100

TRelState RelState;
uint8 RelStatus;
uint8 request;
uint8 delay;


void RelBS_Init(void) {
       
    RelStatus = 0;
    request = 1; // at start also switch off relay
    delay = 255;
    RelState = REL_WAIT;//wait for power stable
}

void RelBS_Task(void) {
       
    switch (RelState)
    {
        case REL_IDLE:
            //fail of power - switch off relay
            DISABLE_IT();
            if (0 == IO_GetZCNumber())
            {
                if (2 == RelStatus)//ON state?
                {
                     request = 1;
                }
            }
            else
            {
                IO_GetZCNumber() = 0;
            }
            ENABLE_IT();
            
            if (0 != request)     {
                RelStatus = request;
                if (1 == request) {
                    IO_SetREL_ON(0);
                    IO_SetREL_OFF(1);           
                    
                } else if (2 == request) {
                    IO_SetREL_OFF(0);
                    IO_SetREL_ON(1);
                    
                } else {
                    IO_SetREL_ON(0);
                    IO_SetREL_OFF(0);
                }
                IO_StartTimer2(IO_Time20ms);
                while (!IO_IsTimer2Elapsed()) {

                }
                IO_SetREL_ON(0);
                IO_SetREL_OFF(0);
                
                request = 0;
                RelState = REL_WAIT;
                delay = DELAY_RECHARGE;               
            }
            else  {
                IO_SetREL_ON(0);
                IO_SetREL_OFF(0);
            }
            break;
        case REL_WAIT:
            IO_SetREL_ON(0);
            IO_SetREL_OFF(0);
            if (delay)   {
                delay--;
            }
            else            {
                RelState = REL_IDLE;
            }
            break;
        default:
            RelState = REL_IDLE;
        break;
    }
}

uint8 RelBS_IsOn(void){
    if (2 == RelStatus)    {
        return TRUE;
    }
    else    {
        return FALSE;
    }
}

void RelBS_Request(uint8 breq) {
    if (breq)    {
        request = 2;//on
    }
    else {
        request = 1; //off
    }
}

uint8 RelBS_IsIdle(void) {
    uint8 bRet = TRUE;
    if ((REL_IDLE != RelState) || (0 != request))    {
        bRet = FALSE;
    }
    return bRet;
}

uint8 RelBS_GetState(void){
    return RelState;
}