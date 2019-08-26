#include "types.h"
#include "drv_tvalve.h"
#include "svc_nvm.h"
#include "drv_io.h"
#include "main.h"

typedef enum {
    tvOFF,
    tvDelay,
    tvPWM,
    tvFall
}TTvStates;

TTvStates tvState;
uint8 pwm;
uint8 outpwm;
uint8 secctr;
uint8 delay;

void RelTV_Init(void){
    tvState  = tvOFF;
    secctr = pwm = outpwm = delay = 0;
   
}

void RelTV_Task(void){
    
  
}

void RelTV_Task1s(void) {
    
    switch (tvState) {
        case tvOFF:
            if (pwm > RAM_THERMO.PWM_ON) {
                tvState = tvDelay;
                outpwm = 255;
            } else {
                outpwm = delay = 0;
            }
            break;
        case tvDelay:
            if (RAM_THERMO.DELAY <= delay) {
                tvState = tvPWM;
            } else {
                delay++;
                outpwm = 255;
            }
            break;
        case tvPWM:
            if (pwm <= RAM_THERMO.PWM_OFF) {
                tvState = tvFall;
                secctr = outpwm = 0;
            } else {
                outpwm = (pwm + 3) / 4;
            }
            break;
        case tvFall:
            if (pwm > RAM_THERMO.PWM_ON) {
                tvState = tvDelay;
                outpwm = 255;
            } else if (0 == delay) {
                tvState = tvOFF;
            } else {
                secctr++;//wait more time to cooldown
                if (secctr > RAM_THERMO.DOWN) {
                    secctr = 0;
                    delay--;
                }
                outpwm = 0;
            }
            break;
        default:
            tvState = tvOFF;
            break;
    } 
   
 
    IO_SetRelSync(outpwm); 
}

void RelTV_Request(uint8 breq){
    pwm = breq;
}

uint8 RelTV_IsOn(void){
    return (uint8) (outpwm != 0);
}

uint8 RelTV_IsIdle(void){
    return (uint8)(tvState == tvOFF );
}