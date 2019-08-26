

#define PIN_SCE   LATA7  //Pin 3 on LCD
#define PIN_RESET LATA1 //Pin 4 on LCD
#define PIN_DC    LATB2  //Pin 5 on LCD


void LCD_Init(void);
void LCD_ClearLCD(void);
void LCD_XY(uint8 x, uint8 y);
void LCD_String(const char *characters);
void LCD_LargeDigit(uint8 dig);
void LCD_ClearLine(void);
void LCD_Char(uint8 character);
void LCD_NumberXX(uint8 digit, uint8 bLzero);
void LCD_LargeDot(void);
void LCD_LargeMinus(void);
void LCD_LargePlus(void);
void LCD_BitmapV(uint8 bmp);
void LCD_BCDNumber(uint8 digit, uint8 bLzero);
void LCD_Large2Dots(uint8 bON);
