/*************************************************************************
 *
 *
 *    (c) Copyright Olimex 2010
 *
 *    File name   : extcon_test.h
 *    Description : External connectors test
 *
 *    History :
 *    1. Date        : 25, January 2010
 *       Author      : Aleksandar Mitev
 *       Description : Create
 *
 **************************************************************************/

#ifndef _EXT_CON_TEST
#define _EXT_CON_TEST

// definition of the used ports array
typedef enum _PORTS_USED {
	GPIOA, GPIOB, GPIOC
} PORTS_USED;	

// definition of ports names
#define PORTS_NAMES(name) const ROM char* name[] = \
	   { "PORTA", "PORTB", "PORTC" }


// structure defining a pin
typedef struct _PIN {
	PORTS_USED GPIO_Port;
	BYTE GPIO_Pin;
} PIN;

// pin manipulation functions
BYTE ReadPin(const ROM PIN *pPin);
void ClearPin(const ROM PIN *pPin);
void SetPin(const ROM PIN *pPin);
void MakePinOutput(const ROM PIN* pPin);
void MakePinInput(const ROM PIN* pPin);


#endif // _EXT_CON_TEST



