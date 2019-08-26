#include <eep.h>

#define EEP_Read(add) Read_b_eep(add)

#define EEP_Write(add, d) Write_b_eep(add,d)

#define EEP_IsBusy() (EECON1bits.WR)

#define EEP_WaitBusy() Busy_eep() 


