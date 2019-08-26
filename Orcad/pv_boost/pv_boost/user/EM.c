#include "types.h"
#include "em.h"
#include "eep_drv.h"

#define CS_ID (P_CHK)


#undef EM_PAR
#define EM_PAR(x,y,z) z,
const byte u8Def[EM_MAX_BYTES] =
{
	#include "em_cfg.h"	
};
	
#undef EM_PAR
#define EM_PAR(x,y,z) y,
const byte u8Sec[EM_MAX_BYTES] =
{
	#include "em_cfg.h"	
};	
	
static byte u8WriteCS;	
static byte cb;
static byte Storage;
byte u8Mirror[EM_MAX_BYTES];

//read all bytes in mirror
void EM_Init(void)
{
	//read all
	u8Mirror[CS_ID] = 0;
	for (cb = 0; cb < EM_MAX_BYTES; cb++)
	{
		if (cb != CS_ID)
		{
			u8Mirror[cb] = EEP_Read(cb);
			if (cb < CS_ID)
			{
				u8Mirror[CS_ID] += u8Mirror[cb];//cs 
			}	
		}	
	}
	
	if (u8Mirror[CS_ID] != EEP_Read(CS_ID))
	{
		//cs fail, use defaults of all bytes
		for (cb = 0; cb < EM_MAX_BYTES; cb++)
		{
			u8Mirror[cb] = u8Def[cb];
		}
	}
	u8WriteCS = 0;
	cb = 0;	
	Storage = 0;	
}	

//task for data write back
void EM_Task(void)
{
	if (EEP_IsBusy())
	{
		return;//wait until eeprom is idle
	}
	
	if (cb >= EM_MAX_BYTES)
	{
		cb = 0;//restart from first byte
	}		
	
	if ((Storage & u8Sec[cb]) !=0) //store enabled?
	{
		if (cb != CS_ID)
		{
			if (u8Mirror[cb] != EEP_Read(cb))//changed byte??
			{
				EEP_Write(cb,u8Mirror[cb]);
				if ( cb < CS_ID )
				{
					u8WriteCS = 1;//CS must be updated!
				}	
			}
		}	 
		else 
		{
			//here we have write all bytes and CS must be updated
			if (u8WriteCS)
			{
				u8WriteCS = 0;
				u8Mirror[CS_ID] = 0;
				for (cb = 0; cb < CS_ID; cb++)
				{
					u8Mirror[CS_ID] += u8Mirror[cb];//cs 
				}
				EEP_Write(CS_ID,u8Mirror[CS_ID]);
			}
			cb = CS_ID;
		}
	}
	cb++;	
}	

//enable storage of section
void EM_StorageEn(byte section)
{
	Storage |= section;
}	

//disable storage of section
void EM_StorageDis(byte section)
{
	Storage &= (~section);
}	