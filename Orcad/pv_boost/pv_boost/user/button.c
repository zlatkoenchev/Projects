#include "types.h"
#include "button.h"
#include "io_drv.h"

static BYTE ButNew[BUT_NUM];
static BYTE ButOld[BUT_NUM];
static BYTE ButPress[BUT_NUM];
static BYTE Timers[BUT_NUM];
static BYTE AR_time[BUT_NUM];
static BYTE LongPress[BUT_NUM];

static byte i;



void But_Init(void)
{
	for (i = 0; i < BUT_NUM; i++)
	{
		Timers[i] = 0;
		AR_time[i] = AUTO_REPEAT_TIME;
		ButNew[i] = 0;
		ButOld[i] = 0;	
		ButPress[i] = 0;	
	}
}

//evaluates button press and generates autorepeat and long press
void But_Task(void)
{
	//reat state
	ButNew[0] = IOGetBut1();	
	ButNew[1] = IOGetBut2();	
	
	for (i = 0; i < BUT_NUM; i++)
	{	
		if (ButNew[i])
		{
			if (0 == ButOld[i] )
			{
				ButPress[i] = 1;//inital press
				LongPress[i] = LONG_PR_TIME;
			}	
			else
			{
				//hold
				if (Timers[i] < AR_time[i])
				{
					Timers[i]++;
				}	
				else
				{
					Timers[i] = 0;
					ButPress[i] |= 1;//simulate new button press
					if (AR_time[i] > MIN_REP_TIME)
					{
						AR_time[i] -= MIN_REP_TIME;
					}	
				}
				if (LongPress[i])
				{
					LongPress[i]--;
				}	
				else
				{
					ButPress[i] |= 2;//long press detected
				}	
			}	
		}
		else
		{
			//not pressed
			if (0 != ButOld[i] )
			{
				ButPress[i] = 4; //released
			}
			else
			{
				ButPress[i] = 0;
			}		
			Timers[i] = 0;
			AR_time[i] = AUTO_REPEAT_TIME;
		}		
		ButOld[i] = ButNew[i];
	}	
}		


byte But_GetBi(byte button)
{
	byte val = ButPress[button];
	ButPress[button] = 0x00;//consume press
	return val;	 
}	


