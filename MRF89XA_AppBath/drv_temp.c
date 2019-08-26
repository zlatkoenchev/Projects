#include "types.h"
#include "drv_temp.h"
#include "drv_io.h"

 uint8 TWater;
 uint8 TAir;





static uint8 TempDrv_Calc(uint8 ch)
{
	uint16 temp;
	temp = IOGetADCFilt(ch);
	
	//limit low range
	if (temp < T_0C_ADC)
	{
		temp = T_0C_ADC;
	}	
	
	//use safe value if sensor is missing
	if (temp > T_100C_ADC)
	{
		temp = T_100C_ADC;
	}	
	//remove offset
	temp -= T_0C_ADC;
	//value is lower than 450
	temp *=100;
	//temperature in 0.5C 
	temp /=102;
	return (uint8)temp;
}	

void TempDrv_Init(void)
{
	TWater = DEF_TEMP;
    TAir = DEF_TEMP;
}



void TempDrv_Main(void)
{
	TWater = TempDrv_Calc(Ai_Temp1);
	TAir = TempDrv_Calc(Ai_Temp2);
}		