/*************************************************************************
 *
 *
 *    (c) Copyright Olimex 2010
 *
 *    File name   : LEDs_control.h
 *    Description : Functions to control the LEDs onthe board
 *
 *    History :
 *    1. Date        : 25, January 2010
 *       Author      : Aleksandar Mitev
 *       Description : Create
 *
 **************************************************************************/

#ifndef _LEDS_CONTROL
#define _LEDS_CONTROL

#if !defined (_EXT_CON_TEST)
	#error "Please provide declarations of 'PORTS_USED' and definitions of function to manipulate pins"
#endif

typedef struct _LED_PIN {
	PORTS_USED GPIO_Port;
	BYTE GPIO_Pin;
} LED_PIN;

extern const ROM int NumberOfLeds;

void LED_InitializeAll(void);

void LED_allON(void);

void LED_allOFF(void);

void LED_on(BYTE index);

void LED_off(BYTE index);

void LED_toggle(BYTE index);

#endif // _LEDS_CONTROL



