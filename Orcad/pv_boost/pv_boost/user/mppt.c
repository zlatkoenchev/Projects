#include "types.h"
#include "io_drv.h"
#include "mppt.h"
#include "em.h"
#include "hal.h"
#include "temperature.h"
#include "dtc.h"

#define TASK_PERIOD_MS   80
#define MS_2_TICK(x)    (x/TASK_PERIOD_MS)
#define R_START 100
#define WAIT_TIME MS_2_TICK(5000) //5 sec before start load again 

#define MAX_IN_VOLTAGE 4000 //40V
#define MAX_IN_CURRENT 1000 //10A
#define MIN_ROUT 17
#define ENERGY_1Wh (3600UL * 1000UL * 10)/TASK_PERIOD_MS //80ms X 10 X 3600
#define LED_ON   2
#define FILT_TIME  MS_2_TICK(640)

typedef enum
{
	MP_OFF,
	MP_ON,
	MP_STOP
}tMPPTState;

typedef struct
{
	word u16OutPower;
	word u16OutPowerF;
	word u16OutCurrent;
	word u16OutCurrentF;
	dword u32OutVoltage;
	word u16OutVoltageF;
	word u16OutR;
	byte u8OutRF;
	
	word u16Current[2];
	word u16CurrentF[2];
	word u16Voltage[2];
	word u16VoltageF[2];
	word u16Power[2];
	word u16PowerF[2];
	
	byte u8Counter;
}tFilt;

typedef struct
{

	word u16Current;
	word u16Voltage;
	word u16Power;
	word u16Energy;
	dword u32EnergyBuf;
	word u16PowerOld;
	word u16VoltageOld;
	byte u8PWM;
	byte u8Timer;
	byte bIncPwm;	
	tMPPTState eState;
	byte LEDOff;	
}tMPPT;	

	
typedef struct
{
	word u16OutCurrent;
	word u16OutVoltage;
	word u16OutPower;
	word u16OutEnergy;
	dword u32OutEnergyBuf;
	byte u8Rout;
	byte u8PWMStart;
	byte u8PWMStep;
	byte u8PWMMax;
	byte u8ImmStop;
}tGMPPT;		

static tMPPT sMPPT[2];
static tGMPPT sGMPPT;
static tFilt Filter;
static dword dw;
static word w1;
static word w2;
static byte i;
static void MPPT_InitFilter(void);

WORD MPPT_GetVi(BYTE ch)
{
	return Filter.u16VoltageF[ch];
}	
WORD MPPT_GetCi(BYTE ch)
{
	return Filter.u16CurrentF[ch];
}	
WORD MPPT_GetPi(BYTE ch)
{
	return Filter.u16PowerF[ch];
}

WORD MPPT_GetEi(BYTE ch)
{
	return (sMPPT[ch].u16Energy);
}
WORD MPPT_GetVo(void)
{
	return Filter.u16OutVoltageF;
}	

WORD MPPT_GetCo(void)
{
	return Filter.u16OutCurrentF;
}	
WORD MPPT_GetPo(void)
{
	return Filter.u16OutPowerF;
}
WORD MPPT_GetEo(void)
{
	return (sGMPPT.u16OutEnergy);
}
byte MPPT_GetRout(void)
{
	 return Filter.u8OutRF;
}
byte MPPT_GetMPPT(BYTE ch)
{
	 return sMPPT[ch].eState;
}
byte MPPT_GetPWM(BYTE ch)
{
	 return sMPPT[ch].u8PWM;
}
byte MPPT_GetInc(BYTE ch)
{
	 return sMPPT[ch].bIncPwm;
}
//////////////////////////////////////////////
static void MPPT_DoFiltering(void)
{
	Filter.u16OutPower     +=sGMPPT.u16OutPower;
	Filter.u16OutCurrent   +=sGMPPT.u16OutCurrent;
	Filter.u32OutVoltage   +=sGMPPT.u16OutVoltage;
	Filter.u16Current[0]   +=sMPPT[0].u16Current; 
	Filter.u16Current[1]   +=sMPPT[1].u16Current;
	Filter.u16Voltage[0]   +=sMPPT[0].u16Voltage;
	Filter.u16Voltage[1]   +=sMPPT[1].u16Voltage;
	Filter.u16Power[0]     +=sMPPT[0].u16Power;
	Filter.u16Power[1]     +=sMPPT[1].u16Power;
	Filter.u16OutR         += sGMPPT.u8Rout;
	
	Filter.u8Counter--;
	if (0 == Filter.u8Counter)
	{
		//1W resolution
		Filter.u16OutPowerF    = (Filter.u16OutPower / (FILT_TIME*10));
		Filter.u16OutCurrentF  = (Filter.u16OutCurrent / (FILT_TIME));
		Filter.u16OutVoltageF = (Filter.u32OutVoltage / (FILT_TIME*10));
		Filter.u16CurrentF[0]  = (Filter.u16Current[0]  / (FILT_TIME));
		Filter.u16CurrentF[1]  = (Filter.u16Current[1]  / (FILT_TIME));
		Filter.u16VoltageF[0] = (Filter.u16Voltage[0]  / (FILT_TIME*10));
		Filter.u16VoltageF[1] = (Filter.u16Voltage[1]  / (FILT_TIME*10));
		Filter.u16PowerF[0]    = (	Filter.u16Power[0] /( FILT_TIME*10));
		Filter.u16PowerF[1]    = (	Filter.u16Power[1] /( FILT_TIME*10));
		Filter.u8OutRF        = (byte)(Filter.u16OutR/(FILT_TIME));
		
		MPPT_InitFilter();
	}	
}	
	
//////////////////////////////////////////////	
static void MPPT_SetPWM(void)
{
	if (sGMPPT.u8ImmStop)
	{
		sMPPT[0].u8PWM = 0;
		sMPPT[1].u8PWM = 0;
	}	
	
	SetDCPWM2( ((word)sMPPT[0].u8PWM) <<2 ); 
	SetDCPWM1( ((word)sMPPT[1].u8PWM) <<2 ); 
}
//////////////////////////////////////////////
void MMPT_ImmediateStop(void)
{
	sGMPPT.u8ImmStop = 1;	
	MPPT_SetPWM();
}	

//////////////////////////////////////////////
static void MPPT_CalcPower(void)
{
	//calc power in 0.1W resolution
	dw = sMPPT[0].u16Voltage;
	dw *= sMPPT[0].u16Current;
	dw /=1000;
	sMPPT[0].u16Power = (word)dw;
	
	dw = sMPPT[1].u16Voltage;
	dw *= sMPPT[1].u16Current;
	dw /=1000;
	sMPPT[1].u16Power = (word)dw;
	
	dw = sGMPPT.u16OutVoltage;
	dw *= sGMPPT.u16OutCurrent;
	dw /=1000;
	sGMPPT.u16OutPower = (word)dw;
	
	//Rout
	if (sGMPPT.u16OutCurrent)
	{
		w1 = (sGMPPT.u16OutVoltage / sGMPPT.u16OutCurrent);
		if (w1 > 255)
		{
			w1 = 255;
		}	
	}
	else
	{
		w1 = 255;
	}	
	sGMPPT.u8Rout = (byte)w1;
}

//////////////////////////////////////////////
static void MPPT_CalcEnergy(void)
{
	sMPPT[0].u32EnergyBuf += sMPPT[0].u16Power;
	if (sMPPT[0].u32EnergyBuf >= ENERGY_1Wh)
	{
		sMPPT[0].u32EnergyBuf -=ENERGY_1Wh;
		sMPPT[0].u16Energy++;
		EM_GetU32(D_E1) +=1; 
	}
	sMPPT[1].u32EnergyBuf += sMPPT[1].u16Power;
	if (sMPPT[1].u32EnergyBuf >= ENERGY_1Wh)
	{
		sMPPT[1].u32EnergyBuf -=ENERGY_1Wh;
		sMPPT[1].u16Energy++;
		EM_GetU32(D_E2) +=1; 
	}	
	
	sGMPPT.u32OutEnergyBuf +=sGMPPT.u16OutPower;
	if (sGMPPT.u32OutEnergyBuf >= ENERGY_1Wh) 
	{
		sGMPPT.u32OutEnergyBuf -= ENERGY_1Wh;
		sGMPPT.u16OutEnergy++;
		EM_GetU32(D_Eo) +=1; 
	}	
}	
//////////////////////////////////////////////
static void MPPT_CheckErrors(void)
{
	if (sMPPT[0].u16Voltage > MAX_IN_VOLTAGE)
	{
		EM_GetU8(D_DTC) |= DTC_OVERVOLT1;
	}
	if (sMPPT[1].u16Voltage > MAX_IN_VOLTAGE)
	{
		EM_GetU8(D_DTC) |= DTC_OVERVOLT2;
	}
	if (sMPPT[0].u16Current > MAX_IN_CURRENT)
	{
		EM_GetU8(D_DTC) |= DTC_OVERCURRENT1;
	}
	if (sMPPT[1].u16Current > MAX_IN_CURRENT)
	{
		EM_GetU8(D_DTC) |= DTC_OVERCURRENT2;
	}	
	if (sGMPPT.u8Rout < MIN_ROUT)
	{
		EM_GetU8(D_DTC) |= DTC_ROUT_LOW;
	}
}	
//////////////////////////////////////////////
static void MPPT_Algo(void)
{
	switch(EM_GetU8(P_MPPT_TYP))
	{
		case 0:
			if (sMPPT[i].u16Power < sMPPT[i].u16PowerOld)
			{
				sMPPT[i].bIncPwm =  ! sMPPT[i].bIncPwm;
			}
		break;
		case 1:
			if (sMPPT[i].u16Power < sMPPT[i].u16PowerOld)
			{
				if (sMPPT[i].u16Voltage >= sMPPT[i].u16VoltageOld) //voltage rise, and P not
				{
					sMPPT[i].bIncPwm = 1;
				}
				else
				{
					sMPPT[i].bIncPwm = 0;
				}		
			}
			else
			{
				sMPPT[i].bIncPwm = 1;
			}	
		break;
		default:
			if (sMPPT[i].u16Power < sMPPT[i].u16PowerOld)//CV todo
			{
				sMPPT[i].bIncPwm =  ! sMPPT[i].bIncPwm;
			}
		break;
	}	
}

//////////////////////////////////////////////
static void MPPT_ManageState(void)
{
	w2  =  EM_GetU8(P_MAX_U_OUT);
	w2 *= 100; 
	
	//check for max out voltage
	if ((sGMPPT.u16OutVoltage > w2)||
		(sGMPPT.u8Rout > R_START))
	{
		MMPT_ImmediateStop();
	}
	//stop in task context
	if (sGMPPT.u8ImmStop)
	{
		sGMPPT.u8ImmStop = 0;
		sMPPT[0].u8Timer = WAIT_TIME;
		sMPPT[1].u8Timer = WAIT_TIME;
		sMPPT[0].eState = MP_STOP;
		sMPPT[1].eState = MP_STOP;
	}	
	//determine max channel power
	w2 = EM_GetU8(P_MAX);
	i = Temp_Get(0);
	if (Temp_Get(1) > i)//get max temp
	{
		i = Temp_Get(1);
	}	
	if (i >= (EM_GetU8(P_T_LIM)+ 5))
	{
		w2 >>=1;//limit to 50% power, getting too hot
	}
	else if (i >= EM_GetU8(P_T_LIM))
	{
		w2 *=3;//limit to 75% power
		w2 /=4;
	}//no limit	
	w2 *= 10;//scale to 0.1W
			
	for (i = 0; i < 2; i++)
	{
		switch (sMPPT[i].eState)
		{
			case MP_OFF:
				w1 = EM_GetU8(P_U_START); //convert to 0.01V
				w1 *= 100;
				if ((sMPPT[i].u16Voltage > w1) &&
				    (sGMPPT.u8Rout < R_START) &&
				    ( EM_GetU8(P_CFG) & (1<<i)))
				   {
					   sMPPT[i].eState = MP_ON;
					   sMPPT[i].u8PWM = sGMPPT.u8PWMStart;
					   sMPPT[i].u16PowerOld = 0;//assume we start from 0 W
					   sMPPT[i].bIncPwm = 1;
				   }
				   else
				   {
				   		sMPPT[i].u8PWM = 0;
				   }  
			break;
			case MP_ON:
				w1 = EM_GetU8(P_U_STOP); //convert to 0.01V
				w1 *= 100;
				//stop if voltage low
				if (sMPPT[i].u16Voltage < w1)
				   {
					   sMPPT[i].eState = MP_STOP;
					   sMPPT[i].u8Timer = WAIT_TIME;
					   sMPPT[i].u8PWM = 0;
				   }
				   else
				   { 
						//if power is too high, decrease PWM
						if (sMPPT[i].u16Power > w2)
						{
							sMPPT[i].bIncPwm = 0;
						}	
						else
						{
							MPPT_Algo();
						}
						
						//try to increase power
						if (sMPPT[i].bIncPwm)
						{
							sMPPT[i].u8PWM += sGMPPT.u8PWMStep;
							if (sMPPT[i].u8PWM > sGMPPT.u8PWMMax )
							{
								//limit DC
								sMPPT[i].u8PWM = sGMPPT.u8PWMMax;
							}	
						}
						else
						{
							if ( sMPPT[i].u8PWM > sGMPPT.u8PWMStart)
							{
								sMPPT[i].u8PWM -= sGMPPT.u8PWMStep;
							}
							else
							{
								sMPPT[i].u8PWM = sGMPPT.u8PWMStart;
							}		
						}			
				   }
				   sMPPT[i].u16PowerOld = sMPPT[i].u16Power; 
			break;
			//wait some time before start again
			case MP_STOP:
				sMPPT[i].u8PWM = 0;
				if (sMPPT[i].u8Timer)
				{
					sMPPT[i].u8Timer--;
				}
				else
				{
					sMPPT[i].eState = MP_OFF;
				}		
			break;
			default:
				MMPT_ImmediateStop();
			break;
			
		}
		sMPPT[i].u16VoltageOld 	= sMPPT[i].u16Voltage;
	} 
	
	//if no MPPT active enable power storage in eeprom
	if ((sMPPT[0].eState != MP_ON) && (sMPPT[1].eState != MP_ON))
	{
		EM_StorageEn(0x02);
	}	
	else
	{
		EM_StorageDis(0x02); //disable energy storage in MMPT is active
	}	
}	

	
//////////////////////////////////////////////
static void MPPT_ReadInputs(void)
{
	dw = IOGetADCF(Ai_U1);
	dw *= EM_GetU16(P_VS1);
	dw /= 1023;
	sMPPT[0].u16Voltage = (word)dw;
	
	dw = IOGetADCF(Ai_U2);
	dw *= EM_GetU16(P_VS2); //55.00V
	dw /= 1023;
	sMPPT[1].u16Voltage = (word)dw;
	
	w1 = IOGetADCF(Ai_CS1);
	w2 = EM_GetU8(P_CS1_offs);
	if (w1 > w2)
	{
		w1 -= w2;
	}
	else 
	{
		w1 = 0;
	}
	dw = w1;		
	dw *= EM_GetU16(P_CS1); //10.00A
	dw /= 1023;
	sMPPT[0].u16Current = (word)dw;
	
	w1 = IOGetADCF(Ai_CS2);
	w2 = EM_GetU8(P_CS2_offs);
	if (w1 > w2)
	{
		w1 -= w2;
	}
	else 
	{
		w1 = 0;
	}
	dw = w1;		
	dw *= EM_GetU16(P_CS2); //10.00A
	dw /= 1023;
	sMPPT[1].u16Current = (word)dw;
	
	
	dw = IOGetADCF(Ai_Uo);
	dw *= EM_GetU16(P_VSo);//220.10V
	dw /= 1023;
	sGMPPT.u16OutVoltage = (word)dw;
	
	w1 = IOGetADCF(Ai_Io);
	w2 = EM_GetU8(P_CSo_offs);
	if (w1 > w2)
	{
		w1 -= w2;
	}
	else 
	{
		w1 = 0;
	}
	dw = w1;		
	dw *= EM_GetU16(P_CSo); //10.00A
	dw /= 1023;
	sGMPPT.u16OutCurrent = (word)dw;
}

//////////////////////////////////////////////	
static void MPPT_InitFilter(void)
{
	Filter.u8Counter = FILT_TIME;
	Filter.u16OutPower = 0;
	Filter.u16OutCurrent = 0;
	Filter.u32OutVoltage = 0;
	Filter.u16Current[0] = 0;
	Filter.u16Current[1] = 0;
	Filter.u16Voltage[0] = 0;
	Filter.u16Voltage[1]  =0;
	Filter.u16Power[0] = 0;
	Filter.u16Power[1]  =0;
	Filter.u16OutR = 0;
	//refresh PWMs
	w1 =	EM_GetU8(P_PWM_START);
	w1 *= EM_GetU8(P_PWM_PERIOD);
	w1 *= 3;
	w1 /= 250;
	if (w1<1)
	{
		w1 = 1;
	}
	sGMPPT.u8PWMStart = (byte)w1;
	
	w1 =	EM_GetU8(P_PWM_STEP);
	w1 *= EM_GetU8(P_PWM_PERIOD);
	w1 *= 3;
	w1 /= 250;
	if (w1<1)
	{
		w1 = 1;
	}
	sGMPPT.u8PWMStep = (byte)w1;
	
	w1 =	EM_GetU8(P_PWM_MAX);
	w1 *= EM_GetU8(P_PWM_PERIOD);
	w1 *= 3;
	w1 /= 250;
	if (w1<1)
	{
		w1 = 1;
	}		
	sGMPPT.u8PWMMax = (byte)w1;
}	
//////////////////////////////////////////////	
void MPPT_Init(void)
{
	sMPPT[0].u8PWM = 0;
	sMPPT[1].u8PWM = 0;
	sMPPT[0].eState = MP_OFF;
	sMPPT[1].eState = MP_OFF;
	sMPPT[0].u16PowerOld = 0;
	sMPPT[1].u16PowerOld = 0;
	sMPPT[0].u16VoltageOld = 0;
	sMPPT[1].u16VoltageOld = 0;
	sMPPT[0].u16Energy = 0;
	sMPPT[1].u16Energy = 0;
	sMPPT[0].u32EnergyBuf = 0;
	sMPPT[1].u32EnergyBuf = 0;
	sMPPT[0].LEDOff = 0;
	sMPPT[1].LEDOff = 0;
	sMPPT[0].bIncPwm = 0;
	sMPPT[1].bIncPwm = 0;
	
	
	sGMPPT.u16OutEnergy = 0; //daily energy
	sGMPPT.u32OutEnergyBuf = 0;
	sGMPPT.u8Rout = 255;//infinite
	sGMPPT.u8ImmStop = 0;

	
	MPPT_InitFilter();
	
	
	Filter.u16OutPowerF    = 0;
	Filter.u16OutCurrentF  = 0;
	Filter.u16OutVoltageF = 0;
	Filter.u16CurrentF[0]  = 0;
	Filter.u16CurrentF[1]  = 0;
	Filter.u16VoltageF[0] = 0;
	Filter.u16VoltageF[1] = 0;
	Filter.u16PowerF[0]    = 0;
	Filter.u16PowerF[1]    = 0;
	Filter.u8OutRF        = 255;
}
//////////////////////////////////////////////	
void MPPT_DriveLEDs(void)
{
	byte i;
	for (i = 0; i < 2; i++)
	{
		//>10W
		if ((MP_ON == sMPPT[i].eState) && (sMPPT[i].u16Power > 100))
		{	
			if (sMPPT[i].LEDOff) {sMPPT[i].LEDOff--;}
	
			if (0 == sMPPT[i].LEDOff)
			{		
				w1 = (7500/sMPPT[i].u16Power);
				sMPPT[i].LEDOff = (byte)w1;
			}	
		}
		else
		{
			sMPPT[i].LEDOff = LED_ON;
		}	
	}	 
	
	
	if (LED_ON > sMPPT[1].LEDOff)
	{
		LED1 = 1;
	}		
	else
	{
		LED1 = 0;
	}
	if (LED_ON > sMPPT[0].LEDOff)
	{
		LED2 = 1;
	}		
	else
	{
		LED2 = 0;
	}	
}
//////////////////////////////////////////////
void MPPT_Task(void)
{
	MPPT_ReadInputs();
	MPPT_CalcPower();
	MPPT_ManageState();
	MPPT_SetPWM();
	MPPT_CalcEnergy();
	MPPT_CheckErrors();
	MPPT_DriveLEDs();
	MPPT_DoFiltering();
}			