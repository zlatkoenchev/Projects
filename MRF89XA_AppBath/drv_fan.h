	
typedef enum{
	FAN_OFF,
    FAN_LOW,
    FAN_HI,
	FAN_START
		
}TFanState;

void FanDrv_Init(void);
	
void FanDrv_Task(void);

void FanDrv_Task1Min(void);

void FanDrv_ReqLow(uint8 time);

void FanDrv_ForceLow(uint8 time);

void FanDrv_ReqHi(uint8 time);

void FanDrv_ForceOff(void);

extern TFanState eFS;
#define  FanDrv_GetState() eFS

uint8 FanDrv_GetLoTime(void);
uint8 FanDrv_GetHiTime(void);