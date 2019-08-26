#ifndef APP_BATH_H
#define APP_BATH_H

#define MAX_U_DUTY 46
#define MAX_C_DUTY 22

typedef enum {
    HTR_OFF,
    HTR_100P,
    HTR_REG1,
    HTR_REG2,
    HTR_WAIT
} THtr;	


typedef struct {
    
}TBATHPAR;

void App_Init(void);	
void App_Task(void);
void App_Task1s(void);
void App_Task1Min(void);
uint8 App_GetShower(void);
uint8 App_GetBathState(void);
uint8 App_GetLampState(void);
extern THtr eHtr;
#define App_GetHtrState() eHtr
#endif