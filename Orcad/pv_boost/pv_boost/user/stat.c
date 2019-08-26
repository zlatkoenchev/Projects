#include "types.h"
#include "stat.h"

#define HRS_TO_40MS (90000-1)
static word divider;

void Stat_Init(void)
{
	divider = HRS_TO_40MS;
}	

void Stat_Task(void)
{
	if (divider)
	{
		divider--;
	}	
	else
	{
		divider = HRS_TO_40MS;
	}	
}	