
#include "io_cfg.h"




void IO_Init1(void);
byte IOGetOSFlag(void);
byte IOGetBut1(void);
byte IOGetBut2(void);
word IOGetADCF(byte i); 
void IO_Init2(void);

typedef enum{
	 Ai_CS2 ,   
	 Ai_CS1 ,   
	 Ai_U2 ,    
	 Ai_U1 ,    
	 Ai_Temp1 , 
	 Ai_Temp2,  
	 Ai_Io ,    
	 Ai_Uo,
	 Ai_NUM 
}tAI;	 


