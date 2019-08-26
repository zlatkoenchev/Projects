#include "types.h"
#include "temperature.h" 
#include "em.h"
#include "hal.h"
#include "io_drv.h"
#include "dtc.h"

static byte u8InitState;	
static byte u8FanState;	
static byte u8FanLvl;
static byte u8FanTmr;	
static word uwTemperature[2];
static byte u8Temp[2];

#define FAN_START_TIME 24 //1s
#define TEMP_FAN_STOP EM_GetU8(P_F_OFF) //40C
#define TEMP_FAN_START EM_GetU8(P_F_LEV1) //45C
#define TEMP_FAN_LEV2 EM_GetU8(P_F_LEV2) //55C


#define CALC_T(i, IN, OFFS, SCALE)  \
	uTemp = IN;                     \
	uTemp <<= 6;                    \
	if (uwTemperature[i] > uTemp)   \
	{                               \
		uwTemperature[i]--;         \
	}	                            \
	else if (uTemp > uwTemperature[i]) \
	{                                  \
		uwTemperature[i]++;            \
	}                                  \
	uTemp = OFFS;	                   \
	uTemp <<= 6;	                   \
	if (uwTemperature[i] <= uTemp)     \
	{                                  \
		uTemp -= uwTemperature[i];     \
		uTemp /= SCALE;                \
		u8Temp[i] = (byte)uTemp;       \
		u8Temp[i] += EM_GetU8(P_T_T0); \
	}                                  \
	else                               \
	{                                    \
		uTemp = uwTemperature[i] - uTemp;   \
		uTemp /= SCALE;                   \
		u8Temp[i] = (byte)uTemp;           \
		if (u8Temp[i] >= EM_GetU8(P_T_T0))  \
		{                                   \
			/*negative T, use 0*/           \
			u8Temp[i] = 0;                  \
		}                                   \
		else                                \
		{                                    \
			u8Temp[i] = EM_GetU8(P_T_T0) - u8Temp[i]; \
		}		                                       \
	}  \


/////////////////////////////////////////////	
 void Temp_Fan_Task(void)
{
	
	switch (u8FanState)
	{
		case 0:
		{
			if ((u8Temp[0]> TEMP_FAN_START)||(u8Temp[1]> TEMP_FAN_START))
			{
				u8FanState = 1;
				u8FanTmr = FAN_START_TIME;
				FAN = 1;
			}
			else
			{
				FAN = 0;
				u8FanLvl = 0;
			}	
			break;	
		}
		case 1://turn on fan on 100% 
		{
			if (u8FanTmr)
			{
				u8FanTmr --;
				FAN = 1;
			}
			else
			{
				u8FanState = 2;
				u8FanTmr = 0;
				FAN = 0;
			}	
			break;	
		}
		case 2://regulate fan
		{
			if (u8FanTmr)
			{
				u8FanTmr--;
				if (0 == u8FanTmr)
				{
					FAN = 0;
				}	
			}
			else
			{
				if ((u8Temp[0]> TEMP_FAN_LEV2)||(u8Temp[1]> TEMP_FAN_LEV2))
				{
					u8FanTmr = 0;//level 2, 100%
					u8FanLvl = 2;
					FAN = 1;
				}
				else if((u8Temp[0]< TEMP_FAN_STOP)&&(u8Temp[1] < TEMP_FAN_STOP))
				{
					u8FanState = 0;//off state
					FAN = 0;
				}
				else
				{
					u8FanTmr = 1;//level 1,66% 
					u8FanLvl = 1;
					FAN = 1;
				}			
			}	
			break;	
		}
	}		
}	

/////////////////////////////////////////////
void Temp_Init(void)
{
	u8InitState = 0;
	u8FanState = 0;
	//start from 20C;
	u8Temp[0] = 20;
	u8Temp[1] = 20;
}	
/////////////////////////////////////////////
void Temp_Task(void)
{
	word uTemp ;
	
	if (u8InitState < 2)
	{
		u8InitState++;
		uwTemperature[0] = IOGetADCF(Ai_Temp1); 
		uwTemperature[0] <<= 6;
		uwTemperature[1] = IOGetADCF(Ai_Temp2); 
		uwTemperature[1] <<= 6;
		return;
	}	
	
	CALC_T(0,IOGetADCF(Ai_Temp1), EM_GetU8(P_T_U0_1), EM_GetU8(P_T_SCALE_1)); 
	CALC_T(1,IOGetADCF(Ai_Temp2), EM_GetU8(P_T_U0_2), EM_GetU8(P_T_SCALE_2)); 
	

	//set DTCs
	if (u8Temp[0] > EM_GetU8(P_T_LIM))
	{
		 EM_GetU8(D_DTC) |= DTC_OVERTEMP1;
	}
	if (u8Temp[1] > EM_GetU8(P_T_LIM))
	{
		 EM_GetU8(D_DTC) |= DTC_OVERTEMP2;
	}	 		
}
/////////////////////////////////////////////	
byte Temp_Get(byte ch)
{
	return u8Temp[ch];//in degree
}

/////////////////////////////////////////////	
byte Temp_GetFan(void)
{
	return u8FanLvl;//in degree
}

