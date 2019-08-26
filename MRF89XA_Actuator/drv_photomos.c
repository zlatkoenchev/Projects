#include "types.h"
#include "drv_photomos.h"
#include "drv_io.h"

void RelPM_Init(void){
    IO_PHOTOMOS_OFF;
}

void RelPM_Task(void){
}

void RelPM_Request(uint8 breq){
    IO_SetPhotomosSync(breq);
} 
    
