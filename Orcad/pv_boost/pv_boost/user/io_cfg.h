

#ifndef IO_CFG_H
#define IO_CFG_H

/** I N C L U D E S *************************************************/


#define MAX_OS_CNTR         200 /*120us resolution*/							
#define OS_TMR_RELOAD       128

/** L E D ***********************************************************/
        

#define LED1                LATCbits.LATC6
#define LED2                LATCbits.LATC7

#define TST1                LATBbits.LATB5 
#define FAN                 LATBbits.LATB6 

#define BUT1                PORTCbits.RC4
#define BUT2                PORTCbits.RC5

/** ADC *****************************************************/
#define ADC_CS1               (0<<2) | 1
#define ADC_CS2               (1<<2) | 1
#define ADC_U2                (2<<2) | 1
#define ADC_U1                (3<<2) | 1
#define ADC_Uo                (7<<2) | 1
#define ADC_Temp1             (5<<2) | 1
#define ADC_Temp2             (8<<2) | 1
#define ADC_Io                (6<<2) | 1


#define MAX_UOUT               727 //160V

#define BUT_DEB_MASK          0x07

/********************************************************************/
/********************************************************************/
/********************************************************************/


#endif //IO_CFG_H
