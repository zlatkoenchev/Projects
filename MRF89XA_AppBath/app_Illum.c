#include "types.h"
#include "main.h"
#include "app_illum.h"
#include "drv_io.h"
#include "drv_temp.h"
#include "app_bath.h"

#define SEC_CNTR (1000/OS_TICK_MS)
static uint8 icnt;
static uint8 t1deb;
static uint8 t2deb;
static uint8 ledDC;
 
void Ill_Init(void){
	icnt =SEC_CNTR;
	t1deb = 0;
	t2deb = 0;
	ledDC = SEC_CNTR -1;
}

void Ill_Main(void){
	uint8 temp;
	
	if (icnt >= ledDC)
    {
		IO_SetOut(Do_LED, 1);
	}
	else
	{
		IO_SetOut(Do_LED, 0);
    }	
	
	temp = TempDrv_GetAir();
	
	if ((temp == 0)|| (temp > DEG_01C(990)))
	{
		if (t1deb<255)
		{
			t1deb++;
		}	
	}	 
	else
	{
		if (t1deb)
		{
			t1deb--;
		}	
	}	
		temp = TempDrv_GetWater();
	
	if ((temp == 0)|| (temp > DEG_01C(990)))
	{
		if (t2deb<255)
		{
			t2deb++;
		}	
	}	 
	else
	{
		if (t2deb)
		{
			t2deb--;
		}	
	}	
		
	if ((t1deb == 255) || (t2deb == 255))
	{
		ledDC = 2;//almost on
	}
	else if (App_GetShower())
	{
		ledDC = SEC_CNTR / 2;
	}			
	else
	{
		ledDC = SEC_CNTR - 1;
	}	
		
	if (icnt)
	{
		icnt--;
		if (0 == icnt)
		{
			icnt = SEC_CNTR;
		}	
	}	
}
	