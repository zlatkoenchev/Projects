#include "types.h"
#include "lcd_drv.h" 
#include "button.h" 
#include "string.h" 
#include "mppt.h"
#include "em.h"
#include "temperature.h"
#include "io_drv.h"

#define EDIT_TIME 180

typedef enum
{
	cMenuNet,
	cMenuEnergy,
	cMenuOut,
	cMenuMPPT,
	cMenuDiag,
	cMenuTotEnergy1,
	cMenuTotEnergy2,
	cMenuTotEnergyOut,
	cMenuCalVS1,
	cMenuCalVS2,
	cMenuCalVSo,
	cMenuCalCS1,
	cMenuCalCS1_offs,
	cMenuCalCS2,
	cMenuCalCS2_offs,
	cMenuCalCSo,
	cMenuCalCSo_offs,
	cMenuCalT_U0_1,
	cMenuCalT_U0_2,
	cMenuCalT_T0,
	cMenuCalT_SCALE_1,
	cMenuCalT_SCALE_2,
	cMenuCalT_LIM,
	cMenuCalT_FAN_OFF,
	cMenuCalT_FAN_L1,
	cMenuCalT_FAN_L2,  
	cMenuCalUstart,
	cMenuCalUstop,
	cMenuCalUMax,
	cMenuCalUCFG,
	cMenuCalP_MPPT_TYP,
	cMenuCalP_MAX,
	cMenuCalP_PWM_START,
	cMenuCalP_PWM_STEP,
	cMenuCalP_PWM_MAX,
	cMenuCalP_PWM_PER,
	cMenuOff
}tMenuVal;


typedef struct
{
	tMenuVal uMenu;
	BYTE uMenuTimer;
	BYTE uEditTimer;
	BYTE uIncr;
	BYTE uDecr;
	BYTE bEditMode:1;
	BYTE bAllowEdit:1;
	
}tMenu;

static tMenu sMENU;	
static void Menu_HandleButtons(void);
static void Menu_Draw(void);
static void Menu_Manage(void);

//  Implementation ====================================
void Menu_Init(void)
{
	sMENU.uMenuTimer =0;
	sMENU.uEditTimer = 0;
	sMENU.uMenu  = cMenuNet;
	sMENU.bEditMode = 0;
	sMENU.uIncr = 0;
	sMENU.uDecr = 0;
}



void Menu_Task(void)
{
	Menu_HandleButtons(); 
	Menu_Manage();
	Menu_Draw();	
}	


static void Menu_HandleButtons(void)
{	
	byte bt = But_GetBi(0);
	
	if (bt & 0x01 )
	{
		if (sMENU.bEditMode)
		{
			sMENU.uIncr = 1;
			sMENU.uEditTimer = EDIT_TIME;
		}	
		else
		{
			sMENU.uMenu++;
			if ((sMENU.uMenu == (cMenuDiag+1)) ||(sMENU.uMenu >= cMenuOff))
			{
				sMENU.uMenu = cMenuNet;
			}			
		}
	}
	
	bt = But_GetBi(1);
	if (sMENU.bEditMode)
	{
		if (bt & 4)
		{
			sMENU.bAllowEdit = 1;
		}	
		
		if (( bt & 1) && (1 == sMENU.bAllowEdit))
		{
			sMENU.uDecr = 1;
			sMENU.uEditTimer = EDIT_TIME;
		}	
	}
	else
	{
		//long press enters to edit mode
		if (( bt & 2) && (sMENU.uMenu > cMenuDiag))
		{
			sMENU.bEditMode = 1;
			sMENU.bAllowEdit = 0;
			sMENU.uEditTimer = EDIT_TIME;
		}
		else if (( bt & 1) && (sMENU.uMenu <= cMenuDiag))
		{
			sMENU.uMenu = cMenuDiag+1;
		}		
	}
	if (sMENU.uEditTimer )
	{
		sMENU.uEditTimer--;
		EM_StorageDis(0x01);
	}	
	else
	{
		sMENU.bEditMode = 0;
		EM_StorageEn(0x01);
	}			
}	

static void Menu_Draw(void)
{ 
	DWORD u32Temp;

	//clear buffer
	LCD_ClearLine();
	
	
	//in calibration mode show "edit"
	if (sMENU.bEditMode) 
	{
		sMENU.uMenuTimer++;
		if (sMENU.uMenuTimer & 0x08)
		{
			*(LCDLine(0)) = '<';
			*(LCDLine(1)) = '>';
		}
	}
	
	if (sMENU.uMenu > cMenuDiag)
	{
		*(LCDLine(6)) = 'S';
		*(LCDLine(7)) = 'E';
		*(LCDLine(8)) = 'T';
		LCD_SendLineToLCD(0);
		LCD_ClearLine();
	}		
	
	switch(sMENU.uMenu) 
	{
		case cMenuNet: 
			*(LCDLine(0)) = 'P';
			*(LCDLine(1)) = 'V';
			*(LCDLine(9)) = 'V';
			*(LCDLine(15)) = 'A';
			*(LCDLine(2)) = '1';
			*(LCDLine(3)) = ':'; 
			hex2dec(LCDLine(5),MPPT_GetVi(0),4,1);
			hex2dec(LCDLine(12),MPPT_GetCi(0)/10,3,1);
			LCD_SendLineToLCD(0);
			LCD_ClearLine();
			*(LCDLine(2)) = '2';
			*(LCDLine(0)) = 'P';
			*(LCDLine(1)) = 'V';
			*(LCDLine(9)) = 'V';
			*(LCDLine(15)) = 'A';
			*(LCDLine(3)) = ':'; 
			hex2dec(LCDLine(5),MPPT_GetVi(1),4,1);
			hex2dec(LCDLine(12),MPPT_GetCi(1)/10,3,1);
			break;
		case cMenuEnergy:
			*(LCDLine(0)) = 'P';
			*(LCDLine(1)) = 'V';
			*(LCDLine(8)) = 'W';
			*(LCDLine(14)) = 'W';
			*(LCDLine(15)) = 'h';
			*(LCDLine(2)) = '1';
			*(LCDLine(3)) = ':';
			hex2dec(LCDLine(5),MPPT_GetPi(0),3,0);
			hex2dec(LCDLine(10),MPPT_GetEi(0),4,0);
			LCD_SendLineToLCD(0);
			LCD_ClearLine();
			*(LCDLine(2)) = '2';
			*(LCDLine(0)) = 'P';
			*(LCDLine(1)) = 'V';
			*(LCDLine(8)) = 'W';
			*(LCDLine(14)) = 'W';
			*(LCDLine(15)) = 'h';
			*(LCDLine(3)) = ':';
			hex2dec(LCDLine(5),MPPT_GetPi(1),3,0);
			hex2dec(LCDLine(10),MPPT_GetEi(1),4,0); 
		break;
		case cMenuMPPT:
			*(LCDLine(0)) = 'M';
			*(LCDLine(1)) = 'P';
			*(LCDLine(2)) = 'P';
			*(LCDLine(3)) = 'T';
			*(LCDLine(4)) = '1';
			*(LCDLine(5)) = ':';
			*(LCDLine(15)) = '%:';
			hex2dec(LCDLine(7),MPPT_GetMPPT(0),1,0);
			hex2dec(LCDLine(10),MPPT_GetInc(0),1,0);
			hex2dec(LCDLine(12),MPPT_GetPWM(0),3,0);
			LCD_SendLineToLCD(0);
			LCD_ClearLine();
			*(LCDLine(0)) = 'M';
			*(LCDLine(1)) = 'P';
			*(LCDLine(2)) = 'P';
			*(LCDLine(3)) = 'T';
			*(LCDLine(4)) = '2';
			*(LCDLine(5)) = ':';
			*(LCDLine(15)) = '%:';
			hex2dec(LCDLine(7),MPPT_GetMPPT(1),1,0);
			hex2dec(LCDLine(10),MPPT_GetInc(1),1,0);
			hex2dec(LCDLine(12),MPPT_GetPWM(1),3,0); 
			break;
		case cMenuOut:
			*(LCDLine(0)) = 'O';
			*(LCDLine(1)) = 'u';
			*(LCDLine(2)) = 't';
			*(LCDLine(3)) = ':';
			*(LCDLine(9)) = 'V';
			*(LCDLine(15)) = 'A';
			hex2dec(LCDLine(4),MPPT_GetVo(),5,1);
			hex2dec(LCDLine(12),MPPT_GetCo()/10,3,1);
			LCD_SendLineToLCD(0);
			LCD_ClearLine();
			*(LCDLine(14)) = 'W';
			*(LCDLine(8)) = 'W';
			*(LCDLine(15)) = 'h';
			*(LCDLine(3)) = 0xF4;
			hex2dec(LCDLine(5),MPPT_GetPo(),3,0);
			
			hex2dec(LCDLine(10),MPPT_GetEo(),4,0);
			if (255 == MPPT_GetRout())
			{
				//*(LCDLine(0)) = '-';
				*(LCDLine(1)) = '-';
				//*(LCDLine(2)) = '-';
			}
			else
			{	
				hex2dec(LCDLine(0),MPPT_GetRout(),3,0); 
			}
		break;
		case cMenuTotEnergy1:
			*(LCDLine(0)) = 'P';
			*(LCDLine(1)) = 'V';
			*(LCDLine(2)) = '1';
			*(LCDLine(3)) = ':';
			*(LCDLine(13)) = 'k';
			*(LCDLine(14)) = 'W';
			*(LCDLine(15)) = 'h';
			
			u32Temp = EM_GetU32(D_E1);
			u32Temp /=100;
			
			hex2dec(LCDLine(7),(word)u32Temp,6,1);
			break;
		case cMenuTotEnergy2:	

			*(LCDLine(0)) = 'P';
			*(LCDLine(1)) = 'V';
			*(LCDLine(2)) = '2';
			*(LCDLine(3)) = ':';
			*(LCDLine(13)) = 'k';
			*(LCDLine(14)) = 'W';
			*(LCDLine(15)) = 'h';
			u32Temp = EM_GetU32(D_E2);
			u32Temp /=100;
			
			hex2dec(LCDLine(7),(word)u32Temp,6,1);
		break;
		case cMenuTotEnergyOut:
			*(LCDLine(0)) = 'O';
			*(LCDLine(1)) = 'u';
			*(LCDLine(2)) = 't';
			*(LCDLine(3)) = ':';
			*(LCDLine(13)) = 'k';
			*(LCDLine(14)) = 'W';
			*(LCDLine(15)) = 'h';
			
			u32Temp = EM_GetU32(D_Eo);
			u32Temp /=100;
			hex2dec(LCDLine(7),(word)u32Temp,6,1);

			break;
		case cMenuDiag:
			*(LCDLine(0)) = 'T';
			*(LCDLine(1)) = 'e';
			*(LCDLine(2)) = 'm';
			*(LCDLine(3)) = 'p';
			*(LCDLine(4)) = ':';
			
			*(LCDLine(9)) = 'C';
			*(LCDLine(15)) = 'C';
			*(LCDLine(14)) = 0xDF;
			*(LCDLine(8)) = 0xDF;
			
			hex2dec(LCDLine(5),Temp_Get(0),3,0);
			hex2dec(LCDLine(11),Temp_Get(1),3,0);
			
			LCD_SendLineToLCD(0);
			LCD_ClearLine();
			*(LCDLine(0)) = 'D';
			*(LCDLine(1)) = 'T';
			*(LCDLine(2)) = 'C';
			*(LCDLine(4)) = ':';
			hex2text_b(LCDLine(6),EM_GetU8(D_DTC));
			
			*(LCDLine(10)) = 'F';
			*(LCDLine(11)) = 'a';
			*(LCDLine(12)) = 'n';
			*(LCDLine(14)) = ':';
		
			hex2dec(LCDLine(15),Temp_GetFan(),1,0);
		break;
		case cMenuCalVS1:
			*(LCDLine(0)) = 'V';
			*(LCDLine(15)) = 'V';
			*(LCDLine(1)) = 'S';
			*(LCDLine(2)) = '1';
			hex2dec(LCDLine(11),MPPT_GetVi(0),4,1);
			hex2dec(LCDLine(5),EM_GetU16(P_VS1),5,0);
		break;
		case cMenuCalVS2:
			*(LCDLine(0)) = 'V';
			*(LCDLine(15)) = 'V';
			*(LCDLine(1)) = 'S';
			*(LCDLine(2)) = '2';
			hex2dec(LCDLine(11),MPPT_GetVi(1),4,1);
			hex2dec(LCDLine(5),EM_GetU16(P_VS2),5,0);
		break;
		case cMenuCalVSo:
			*(LCDLine(0)) = 'V';
			*(LCDLine(15)) = 'V';
			*(LCDLine(1)) = 'S';
			*(LCDLine(2)) = 'o';
			hex2dec(LCDLine(10),MPPT_GetVo(),5,1);
			hex2dec(LCDLine(4),EM_GetU16(P_VSo),5,0);
		break;
		case cMenuCalCS1:
			*(LCDLine(0)) = 'C';
			*(LCDLine(15)) = 'A';
			*(LCDLine(1)) = 'S';
			*(LCDLine(2)) = '1';
			hex2dec(LCDLine(11),MPPT_GetCi(0),4,2);
			hex2dec(LCDLine(4),EM_GetU16(P_CS1),5,0);
		break;
		case cMenuCalCS1_offs:
		    *(LCDLine(0)) = 'C';
			*(LCDLine(15)) = 'A';
			*(LCDLine(1)) = 'S';
			*(LCDLine(2)) = '1';
			*(LCDLine(3)) = 'o';
			*(LCDLine(4)) = 'f';
			hex2dec(LCDLine(12),IOGetADCF(Ai_CS1),4,0);
			hex2dec(LCDLine(6),EM_GetU8(P_CS1_offs),3,0);
		break;
		case cMenuCalCS2:
		    *(LCDLine(0)) = 'C';
			*(LCDLine(15)) = 'A';
			*(LCDLine(1)) = 'S';
			*(LCDLine(2)) = '2';
			hex2dec(LCDLine(11),MPPT_GetCi(1),4,2);
			hex2dec(LCDLine(4),EM_GetU16(P_CS2),5,0);
		break;
		case cMenuCalCS2_offs:
		*(LCDLine(0)) = 'C';
			*(LCDLine(15)) = 'A';
			*(LCDLine(1)) = 'S';
			*(LCDLine(2)) = '2';
			*(LCDLine(3)) = 'o';
			*(LCDLine(4)) = 'f';
			hex2dec(LCDLine(12),IOGetADCF(Ai_CS2),4,0);
			hex2dec(LCDLine(6),EM_GetU8(P_CS2_offs),3,0);
		break;
		case cMenuCalCSo:
	 	    *(LCDLine(0)) = 'C';
			*(LCDLine(15)) = 'A';
			*(LCDLine(1)) = 'S';
			*(LCDLine(2)) = 'o';
			hex2dec(LCDLine(11),MPPT_GetCo(),4,2);
			hex2dec(LCDLine(4),EM_GetU16(P_CSo),5,0);
		break;
		case cMenuCalCSo_offs:
		*(LCDLine(0)) = 'C';
			*(LCDLine(15)) = 'A';
			*(LCDLine(1)) = 'S';
			*(LCDLine(2)) = 'o';
			*(LCDLine(3)) = 'o';
			*(LCDLine(4)) = 'f';
			hex2dec(LCDLine(12),IOGetADCF(Ai_Io),4,0);;
			hex2dec(LCDLine(6),EM_GetU8(P_CSo_offs),3,0);
		break;
		case cMenuCalT_U0_1:
			*(LCDLine(0)) = 'U';
			//*(LCDLine(15)) = 'V';
			*(LCDLine(1)) = '0';
			*(LCDLine(2)) = '1';
			hex2dec(LCDLine(13),EM_GetU8(P_T_U0_1),3,0);
			hex2dec(LCDLine(5),IOGetADCF(Ai_Temp1),4,0);
		break;
		case cMenuCalT_U0_2:
			*(LCDLine(0)) = 'U';
			//*(LCDLine(15)) = 'V';
			*(LCDLine(1)) = '0';
			*(LCDLine(2)) = '2';
			hex2dec(LCDLine(13),EM_GetU8(P_T_U0_2),3,0);
			hex2dec(LCDLine(5),IOGetADCF(Ai_Temp2),4,0);
		break;
		case cMenuCalT_T0:
			*(LCDLine(0)) = 'T';
			*(LCDLine(14)) = 0xDF;
			*(LCDLine(15)) = 'C';
			*(LCDLine(1)) = '0';
			hex2dec(LCDLine(11),EM_GetU8(P_T_T0),3,0);
		break;
		case cMenuCalT_SCALE_1:
			*(LCDLine(0)) = 'T';
			*(LCDLine(1)) = 's';
			*(LCDLine(2)) = 'c';
			*(LCDLine(3)) = '1';
			hex2dec(LCDLine(13),EM_GetU8(P_T_SCALE_1),3,0);
		break;
		case cMenuCalT_SCALE_2:
			*(LCDLine(0)) = 'T';
			*(LCDLine(1)) = 's';
			*(LCDLine(2)) = 'c';
			*(LCDLine(3)) = '2';
			hex2dec(LCDLine(13),EM_GetU8(P_T_SCALE_2),3,0);
		break;
		case cMenuCalT_LIM:
		    *(LCDLine(0)) = 'T';
		    *(LCDLine(14)) = 0xDF;
			*(LCDLine(15)) = 'C';
			*(LCDLine(1)) = 'l';
			*(LCDLine(2)) = 'i';
			*(LCDLine(3)) = 'm';
			hex2dec(LCDLine(11),EM_GetU8(P_T_LIM),3,0);
		break;
		case cMenuCalT_FAN_OFF:
		    *(LCDLine(0)) = 'T';
		    *(LCDLine(14)) = 0xDF;
			*(LCDLine(15)) = 'C';
			*(LCDLine(1)) = 'f';
			*(LCDLine(2)) = 'a';
			*(LCDLine(3)) = 'n';
			*(LCDLine(5)) = 'o';
			*(LCDLine(6)) = 'f';
			*(LCDLine(7)) = 'f';
			hex2dec(LCDLine(11),EM_GetU8(P_F_OFF),3,0);
		break;
			case cMenuCalT_FAN_L1:
		    *(LCDLine(0)) = 'T';
		    *(LCDLine(14)) = 0xDF;
			*(LCDLine(15)) = 'C';
			*(LCDLine(1)) = 'f';
			*(LCDLine(2)) = 'a';
			*(LCDLine(3)) = 'n';
			*(LCDLine(5)) = 'l';
			*(LCDLine(6)) = 'v';
			*(LCDLine(7)) = '1';
			hex2dec(LCDLine(11),EM_GetU8(P_F_LEV1),3,0);
		break;
		case cMenuCalT_FAN_L2:
		    *(LCDLine(0)) = 'T';
		    *(LCDLine(14)) = 0xDF;
			*(LCDLine(15)) = 'C';
			*(LCDLine(1)) = 'f';
			*(LCDLine(2)) = 'a';
			*(LCDLine(3)) = 'n';
			*(LCDLine(5)) = 'l';
			*(LCDLine(6)) = 'v';
			*(LCDLine(7)) = '2';
			hex2dec(LCDLine(11),EM_GetU8(P_F_LEV2),3,0);
		break;
		case cMenuCalUstart:
		    *(LCDLine(0)) = 'U';
			*(LCDLine(15)) = 'V';
			*(LCDLine(1)) = 'o';
			*(LCDLine(2)) = 'n';
			hex2dec(LCDLine(12),EM_GetU8(P_U_START),3,0);
		break;
		case cMenuCalUstop:
		    *(LCDLine(0)) = 'U';
			*(LCDLine(15)) = 'V';
			*(LCDLine(1)) = 'o';
			*(LCDLine(2)) = 'f';
			*(LCDLine(3)) = 'f';
			hex2dec(LCDLine(12),EM_GetU8(P_U_STOP),3,0);
		break;
		case cMenuCalUMax:
			*(LCDLine(0)) = 'U';
			*(LCDLine(15)) = 'V';
			*(LCDLine(1)) = 'm';
			*(LCDLine(2)) = 'a';
			*(LCDLine(3)) = 'x';
			hex2dec(LCDLine(12),EM_GetU8(P_MAX_U_OUT),3,0);
		break;
		case cMenuCalUCFG:
			*(LCDLine(0)) = 'D';
			*(LCDLine(1)) = 'T';
			*(LCDLine(2)) = 'C';
			*(LCDLine(3)) = ':';
			hex2text_b(LCDLine(5),EM_GetU8(D_DTC));
		    *(LCDLine(8)) = 'C';
			*(LCDLine(9)) = 'F';
			*(LCDLine(10)) = 'G';
			*(LCDLine(11)) = ':';
			hex2dec(LCDLine(13),EM_GetU8(P_CFG),3,0);
			//*(LCDLine(13)) = EM_GetU8(P_CFG);
		break;	
		case cMenuCalP_MAX:
			*(LCDLine(0)) = 'P';
			*(LCDLine(15)) = 'W';
			//*(LCDLine(1)) = '_';
			*(LCDLine(1)) = 'm';
			*(LCDLine(2)) = 'a';
			*(LCDLine(3)) = 'x';
			hex2dec(LCDLine(12),EM_GetU8(P_MAX),3,0);
			break;
		case cMenuCalP_MPPT_TYP:
			switch (EM_GetU8(P_MPPT_TYP))
			{
				case 0:
				*(LCDLine(14)) = 'P';
				*(LCDLine(15)) = 'O';
				break;
				case 1:
				*(LCDLine(13)) = 'P';
				*(LCDLine(14)) = 'O';
				*(LCDLine(15)) = 'M';
				break;
				default:
				*(LCDLine(14)) = 'C';
				*(LCDLine(15)) = 'V';
				break;
			}	
		
			*(LCDLine(0)) = 'M';
			*(LCDLine(1)) = 'P';
			*(LCDLine(2)) = 'P';
			*(LCDLine(3)) = 'T';
			*(LCDLine(4)) = ':';
			break;
		case cMenuCalP_PWM_START:
			*(LCDLine(0)) = 'P';
			*(LCDLine(1)) = 'W';
			*(LCDLine(2)) = 'M';
			*(LCDLine(3)) = 's';
			*(LCDLine(4)) = 't';
			*(LCDLine(5)) = 'a';
			*(LCDLine(6)) = 'r';
			*(LCDLine(7)) = 't';
			hex2dec(LCDLine(12),EM_GetU8(P_PWM_START),3,0);	
			*(LCDLine(15)) = '%';		
		break;	
		case cMenuCalP_PWM_STEP:
			*(LCDLine(0)) = 'P';
			*(LCDLine(1)) = 'W';
			*(LCDLine(2)) = 'M';
			*(LCDLine(3)) = 's';
			*(LCDLine(4)) = 't';
			*(LCDLine(5)) = 'e';
			*(LCDLine(6)) = 'p';
			hex2dec(LCDLine(12),EM_GetU8(P_PWM_STEP),3,0);
			*(LCDLine(15)) = '%';			
		break;
		case cMenuCalP_PWM_MAX:
			*(LCDLine(0)) = 'P';
			*(LCDLine(1)) = 'W';
			*(LCDLine(2)) = 'M';
			*(LCDLine(3)) = 'm';
			*(LCDLine(4)) = 'a';
			*(LCDLine(5)) = 'x';
			hex2dec(LCDLine(12),EM_GetU8(P_PWM_MAX),3,0);
			*(LCDLine(15)) = '%';			
		break;
		case cMenuCalP_PWM_PER:
			*(LCDLine(0)) = 'P';
			*(LCDLine(1)) = 'W';
			*(LCDLine(2)) = 'M';
			*(LCDLine(3)) = 'p';
			*(LCDLine(4)) = 'e';
			*(LCDLine(5)) = 'r';
			*(LCDLine(6)) = 'i';
			*(LCDLine(7)) = 'o';
			*(LCDLine(8)) = 'd';
			*(LCDLine(15)) = 'S';
			*(LCDLine(14)) = 0xE4;
			hex2dec(LCDLine(10),EM_GetU8(P_PWM_PERIOD),4,1);
		break;									
		default:
		break;
	}
	LCD_SendLineToLCD(1);
}


static void Menu_Manage(void)
{		
	//handle menu values
	if(sMENU.bEditMode)
	{
		//change menu value
		switch(sMENU.uMenu) 
		{
			case cMenuDiag:
					
			break;
			case cMenuTotEnergy1:
				if ((sMENU.uIncr)||(sMENU.uDecr))
				{
					EM_GetU32(D_E1) = 0;
				}
			break;
			case cMenuTotEnergy2:
				if ((sMENU.uIncr)||(sMENU.uDecr))
				{
					EM_GetU32(D_E2) = 0;
				}
			break;
			case cMenuTotEnergyOut:
				if ((sMENU.uIncr)||(sMENU.uDecr))
				{
					EM_GetU32(D_Eo) = 0;
				}
			break;
			case cMenuCalVS1:
				EM_GetU16(P_VS1) += sMENU.uIncr;
				if ((sMENU.uIncr) && (EM_GetU16(P_VS1)>6000)) {EM_GetU16(P_VS1)=5000;}
				if ((sMENU.uDecr) && (EM_GetU16(P_VS1)<5000)) {EM_GetU16(P_VS1)=6000;}
				EM_GetU16(P_VS1) -= sMENU.uDecr;
				
			break;
			case cMenuCalVS2:
				EM_GetU16(P_VS2) += sMENU.uIncr;
				if ((sMENU.uIncr) && (EM_GetU16(P_VS2)>6000)) {EM_GetU16(P_VS2)=5000;}
				if ((sMENU.uDecr) && (EM_GetU16(P_VS2)<5000)) {EM_GetU16(P_VS2)=6000;}
				EM_GetU16(P_VS2) -= sMENU.uDecr;
			break;
			case cMenuCalVSo:
				EM_GetU16(P_VSo) += sMENU.uIncr;
				if ((sMENU.uIncr) && (EM_GetU16(P_VSo)>23000)) {EM_GetU16(P_VSo)=20000;}
				if ((sMENU.uDecr) && (EM_GetU16(P_VSo)<20000)) {EM_GetU16(P_VSo)=23000;}
				EM_GetU16(P_VSo) -= sMENU.uDecr;
				
			break;
			case cMenuCalCS1:
				EM_GetU16(P_CS1) += sMENU.uIncr;
				if ((sMENU.uIncr) &&(EM_GetU16(P_CS1)>1200)) {EM_GetU16(P_CS1)=700;}
				if ((sMENU.uDecr) &&(EM_GetU16(P_CS1)<700)) {EM_GetU16(P_CS1)=1200;}
				EM_GetU16(P_CS1) -= sMENU.uDecr;
				
			break;
			case cMenuCalCS1_offs:
				EM_GetU8(P_CS1_offs) += sMENU.uIncr;
				EM_GetU8(P_CS1_offs) -= sMENU.uDecr;
			break;
			case cMenuCalCS2:
				EM_GetU16(P_CS2) += sMENU.uIncr;
				if ((sMENU.uIncr) &&(EM_GetU16(P_CS2)>1200)) {EM_GetU16(P_CS2)=700;}
				if ((sMENU.uDecr) &&(EM_GetU16(P_CS2)<700)) {EM_GetU16(P_CS2)=1200;}
				EM_GetU16(P_CS2) -= sMENU.uDecr;
			break;
			case cMenuCalCS2_offs:
				EM_GetU8(P_CS2_offs) += sMENU.uIncr;
				EM_GetU8(P_CS2_offs) -= sMENU.uDecr;
			break;
			case cMenuCalCSo:
				EM_GetU16(P_CSo) += sMENU.uIncr;
				if ((sMENU.uIncr) &&(EM_GetU16(P_CS2)>800)) {EM_GetU16(P_CS2)=400;}
				if ((sMENU.uDecr) &&(EM_GetU16(P_CS2)<400)) {EM_GetU16(P_CS2)=800;}
				EM_GetU16(P_CSo) -= sMENU.uDecr;
				
			break;
			
			case cMenuCalP_MPPT_TYP:
				EM_GetU8(P_MPPT_TYP) += sMENU.uIncr;
				if ((sMENU.uIncr) &&(EM_GetU8(P_MPPT_TYP)>2)) {EM_GetU8(P_MPPT_TYP)=0;}
				if ((sMENU.uDecr) &&(EM_GetU8(P_MPPT_TYP)<1)) {EM_GetU8(P_MPPT_TYP)=2;}
				EM_GetU8(P_MPPT_TYP) -= sMENU.uDecr;
				
			break;
			case cMenuCalCSo_offs:
				EM_GetU8(P_CSo_offs) += sMENU.uIncr;
				EM_GetU8(P_CSo_offs) -= sMENU.uDecr;
			break;
			case cMenuCalT_U0_1:
				EM_GetU8(P_T_U0_1) += sMENU.uIncr;
				EM_GetU8(P_T_U0_1) -= sMENU.uDecr;
			break;
			case cMenuCalT_U0_2:
				EM_GetU8(P_T_U0_2) += sMENU.uIncr;
				EM_GetU8(P_T_U0_2) -= sMENU.uDecr;
			break;
			case cMenuCalT_T0:
				EM_GetU8(P_T_T0) += sMENU.uIncr;
				EM_GetU8(P_T_T0) -= sMENU.uDecr;
			break;
			case cMenuCalT_SCALE_1:
				EM_GetU8(P_T_SCALE_1) += sMENU.uIncr;
				EM_GetU8(P_T_SCALE_1) -= sMENU.uDecr;
			break;
			case cMenuCalT_SCALE_2:
				EM_GetU8(P_T_SCALE_2) += sMENU.uIncr;
				EM_GetU8(P_T_SCALE_2) -= sMENU.uDecr;
			break;
			case cMenuCalT_LIM:
				EM_GetU8(P_T_LIM) += sMENU.uIncr;
				EM_GetU8(P_T_LIM) -= sMENU.uDecr;
			break;
			case cMenuCalT_FAN_OFF:
				EM_GetU8(P_F_OFF) += sMENU.uIncr;
				EM_GetU8(P_F_OFF) -= sMENU.uDecr;
			break;
			case cMenuCalT_FAN_L1:
				EM_GetU8(P_F_LEV1) += sMENU.uIncr;
				EM_GetU8(P_F_LEV1) -= sMENU.uDecr;
			break;
			case cMenuCalT_FAN_L2:
				EM_GetU8(P_F_LEV2) += sMENU.uIncr;
				EM_GetU8(P_F_LEV2) -= sMENU.uDecr;
			break;
			case cMenuCalUstart:
				EM_GetU8(P_U_START) += sMENU.uIncr;
				EM_GetU8(P_U_START) -= sMENU.uDecr;
			break;
			case cMenuCalUstop:
				EM_GetU8(P_U_STOP) += sMENU.uIncr;
				EM_GetU8(P_U_STOP) -= sMENU.uDecr;
			break;
			case cMenuCalUMax:	
				EM_GetU8(P_MAX_U_OUT) += sMENU.uIncr;
				EM_GetU8(P_MAX_U_OUT) -= sMENU.uDecr;
			break;
			case cMenuCalUCFG:
				EM_GetU8(P_CFG) += sMENU.uIncr;
				EM_GetU8(P_CFG) -= sMENU.uDecr;
				if ((sMENU.uIncr) || (sMENU.uDecr))
				{
					EM_GetU8(D_DTC) = 0;
				}
			break;
			case cMenuCalP_MAX:
				EM_GetU8(P_MAX) += sMENU.uIncr;
				EM_GetU8(P_MAX) -= sMENU.uDecr;
			break;
		
			case cMenuCalP_PWM_START:
				if (sMENU.uIncr)
				{
					EM_GetU8(P_PWM_START) += sMENU.uIncr;
					if (EM_GetU8(P_PWM_STEP)>50)
					{
						EM_GetU8(P_PWM_STEP) = 1;
					}	
				}
				if (sMENU.uDecr)
				{
					EM_GetU8(P_PWM_START) -= sMENU.uDecr;
					if (EM_GetU8(P_PWM_START)<1)
					{
						EM_GetU8(P_PWM_START) = 50;
					}
				}	
			break;
			case cMenuCalP_PWM_STEP:
				if (sMENU.uIncr)
				{
					EM_GetU8(P_PWM_STEP) += sMENU.uIncr;
					if (EM_GetU8(P_PWM_STEP)>20)
					{
						EM_GetU8(P_PWM_STEP) = 1;
					}	
				}
				if (sMENU.uDecr)
				{
					EM_GetU8(P_PWM_STEP) -= sMENU.uDecr;
					if (EM_GetU8(P_PWM_STEP)<1)
					{
						EM_GetU8(P_PWM_STEP) = 20;
					}
				}	
			break;	
			case cMenuCalP_PWM_MAX:
				if (sMENU.uIncr)
				{
					EM_GetU8(P_PWM_MAX) += sMENU.uIncr;
					if (EM_GetU8(P_PWM_MAX)>100)
					{
						EM_GetU8(P_PWM_MAX) = 0;
					}	
				}
				if (sMENU.uDecr)
				{
					EM_GetU8(P_PWM_MAX) -= sMENU.uDecr;
					if (EM_GetU8(P_PWM_MAX)>100)
					{
						EM_GetU8(P_PWM_MAX) = 100;
					}
				}	
			break;	
			
			case cMenuCalP_PWM_PER:
			if (sMENU.uIncr)
			{
				EM_GetU8(P_PWM_PERIOD) += sMENU.uIncr;
				if (EM_GetU8(P_PWM_PERIOD)>210)
				{
					EM_GetU8(P_PWM_PERIOD) = 30;//330kHz	
				}	
			}	
			if(sMENU.uDecr)	
			{
				EM_GetU8(P_PWM_PERIOD) -= sMENU.uDecr;
				if (EM_GetU8(P_PWM_PERIOD)>210)
				{
					EM_GetU8(P_PWM_PERIOD) = 210;//50kHz	
				}	
			}	
			break;						
			default:
			break;
		}
	}
	sMENU.uIncr = 0;
	sMENU.uDecr = 0; //consume button press	
}


