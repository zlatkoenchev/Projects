#include <p18cxxx.h>
#include "io_cfg.h"                                 // Required
#include "timers.h"
#include "pwm.h"	
#define CPU_CLOCK 48UL

#define EI() INTCONbits.GIEH = 1
#define DI() INTCONbits.GIEH = 0


	
	

