

typedef enum {
	But1,
	But2,
	BUT_NUM
}tButtons;

 

#define BUT_TASK_PERIOD_MS 40
#define MS(x)  ((x)/BUT_TASK_PERIOD_MS)
#define AUTO_REPEAT_TIME MS(500)
#define MIN_REP_TIME MS(40)
#define LONG_PR_TIME MS(2500)


void But_Init(void);

void But_Task(void);

byte But_GetBi(byte button);


