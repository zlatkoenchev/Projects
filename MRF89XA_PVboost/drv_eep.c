#include "types.h"
#include "drv_eep.h"


uint8 Read_Eep(uint8 badd) {
    NVMADRH = (0x70);
    NVMADRL = (badd);
    NVMCON1bits.NVMREGS = 1;
    NVMCON1bits.RD = 1;
    NOP(); // NOPs may be required for latency at high frequencies
    NOP();
    return (NVMDATL);
}

void Write_Eep(uint8 badd, uint8 bdata) {
    SUSPEND_IT();
 
    NVMADRH = (0x70);
    NVMADRL = (badd);
    NVMDATL = bdata;
    NVMCON1bits.NVMREGS = 1;
    NVMCON1bits.WREN = 1;
    NVMCON2 = 0x55;
    NVMCON2 = 0xAA;
    NVMCON1bits.WR = 1;
    // Wait for write to complete
    while (NVMCON1bits.WR) {
    }

    NVMCON1bits.WREN = 0;
    
    RESUME_IT();
    
}

