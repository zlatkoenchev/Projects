#include "types.h"
#include "app_Menu.h"
#include "drv_lcd.h"
#include "app_RTC.h"
#include "drv_io.h"
#include "drv_air_sens.h"
#include "app_TempReg.h"
#include "app_ProgTemp.h"
#include "app_Presence.h"
#include "app_win_sens.h"


#define EDIT_TIME 60
#define ONSECDOT 50
#define HALFSEC 25


typedef enum
{ 
    MN_MAIN,
    MN_CLOCK         
}TMenu;

typedef enum {
    LN_1,
    LN_2,
    LN_3,
    LN_4,
} TMenu;

static uint8 Menu;
static uint8 Line;
static uint8 u8temp;
static uint8 u8editmode;
static uint8 u8menuswitch;
static uint8 dotctr;
static uint8 TempHumFlag;


//08:23   12.mar
//________________

//-23.5 0C

static void DrawClrLastLines(void) {
    LCD_XY(0, 3);
    LCD_ClearLine();
    LCD_ClearLine();
    LCD_ClearLine();
}

static void DrawTimeDate(void){
    LCD_XY(0, 0);
    //08:23   12.mar
    if (RTC_IsTimeOk())
    {
        LCD_BCDNumber(DateTime.Hours, FALSE);
        LCD_Char(':');
        LCD_BCDNumber(DateTime.Minutes,TRUE);
        LCD_String("   ");
               
        LCD_BCDNumber(DateTime.Day,FALSE);
        LCD_Char(' '); 
        
        switch(DateTime.Month)
        {
            case 1:
                LCD_String("Jan");
                break;
            case 2:
                LCD_String("Feb");
                break;
            case 3:
                LCD_String("Mar");
                break;
            case 4:
                LCD_String("Apr");
                break;
            case 5:
                LCD_String("May");
                break;
            case 6:
                LCD_String("Jun");
                break;
            case 7:
                LCD_String("Jul");
                break;
            case 8:
                LCD_String("Aug");
                break;
            case 9:
                LCD_String("Sep");
                break;
            case 0x10:
                LCD_String("Okt");
                break;
            case 0x11:
                LCD_String("Nov");
                break;
            case 0x12:
                LCD_String("Dec");
                break;
            default:
                break;
        }
    }
    else
    {
        LCD_ClearLine();
    }
}

static void DrawLargeTemp(sint16 t) {
    //0..8 sign
    //9..23 dig
    //24..36 dig
    //38..41 point
    //43..56 dig
    //58..62 0
    //63..69 C
    LCD_XY(1, 4);
    if ( t < 0 )
    {
        t = -t;
        LCD_LargeMinus();
    }
    else
    {
        LCD_LargePlus();
    }
    LCD_XY(43, 3);
    u8temp = t % 10;
    
    LCD_LargeDigit(u8temp);
    LCD_XY(24, 3);
    t = t / 10;
    u8temp = t % 10;
    LCD_LargeDigit(u8temp);
    LCD_XY(9, 3);
    t = t / 10;
    LCD_LargeDigit((uint8) (t));
    
    LCD_XY(38, 5);
    LCD_LargeDot();
    
    LCD_XY(57, 3);
    LCD_Char('@'); 
    LCD_Char('C'); 
}

static void DrawLargeHum(void) {
    
    LCD_XY(20, 3);
    u8temp = AirS_GetHum() / 10;
    LCD_LargeDigit(u8temp);
    LCD_XY(35, 3);
    u8temp = AirS_GetHum() % 10;
    LCD_LargeDigit(u8temp);
   
    LCD_XY(54, 3);
    LCD_Char('%');
    LCD_Char('R');
    LCD_Char('h');
}

static void DrawLargeTime(void) {
    LCD_XY(10, 3);
    if (RTC_IsTimeOk()) {
        if (DateTime.Hours & 0xF0) {
            LCD_LargeDigit(DateTime.Hours>>4);
        }
        LCD_XY(24, 3);
        LCD_LargeDigit(DateTime.Hours & 0x0f);
        LCD_XY(40, 3);
        LCD_Large2Dots(dotctr < HALFSEC);
        LCD_XY(47, 3);
        LCD_LargeDigit(DateTime.Minutes >> 4);
        LCD_XY(61, 3);
        LCD_LargeDigit(DateTime.Minutes & 0x0f);
    } else {
       DrawClrLastLines();
    };
    
    //0..8 sign
    //9..23 dig
    //24..36 dig
    //38..41 point
    //43..56 dig
    //58..62 0
    //63..69 C
  
}

static void DrawRegPower(void){
    u8temp = REG_GetLevel();
    LCD_XY(67, 5);
    if (0xFF == u8temp) {
        LCD_Char('F');
        LCD_Char(' ');
    }
    else  {
        if (u8temp > 0)   {
            LCD_BitmapV(0xC0);
            LCD_BitmapV(0xC0);   
        }
        else   {
            LCD_BitmapV(0x0);
            LCD_BitmapV(0x0);
        }
        LCD_BitmapV(0x0);
        if (u8temp > 25) {
            LCD_BitmapV(0xF0);
            LCD_BitmapV(0xF0);
        }
        else  {
            LCD_BitmapV(0x0);
            LCD_BitmapV(0x0);
        }
        LCD_BitmapV(0x0);
        if (u8temp > 50) {
            LCD_BitmapV(0xFC);
            LCD_BitmapV(0xFC);
        }
        else   {
            LCD_BitmapV(0x0);
            LCD_BitmapV(0x0);
        }
        LCD_BitmapV(0x0);
        if (u8temp > 75) {
            LCD_BitmapV(0xFF);
            LCD_BitmapV(0xFF);
        } else {
            LCD_BitmapV(0x0);
            LCD_BitmapV(0x0);
        }
    }
    //draw presence
    LCD_XY(79, 3);
    if (WIN_IsOpen()){
        LCD_Char('W');
    }
    else if (PRS_RoomPresence())    {
        LCD_Char('P');
    }
    else    {
        LCD_Char(' ');
    }
}

static void DrawSetTempText(void) {
    LCD_XY(0, 2);
    if (u8editmode)    {
        u8editmode--;
        if (dotctr < HALFSEC) {
            LCD_String(" Set Temp");
        } else {
            LCD_ClearLine();
        }
    }
    else {
        LCD_ClearLine();
    }

}

void MNU_Init(void){
    Menu = MN_MAIN;
    dotctr = Line = u8editmode = 0;
    u8menuswitch = 255;
    LCD_ClearLCD();
}

void MNU_Task(void){
    switch (Menu)
    {
        //date, temp
        case MN_MAIN:
            switch (Line)
            {
                case 0:
                    DrawTimeDate();
                break;    
                case 1:
                    if (u8editmode)  {
                        DrawLargeTemp(PRG_GetSetTemp());
                    }
                    else  {
                        if ((TempHumFlag & 1) || (AirS_GetHum()==255)){
                            DrawLargeTemp(AirS_GetTemp());
                        }
                        else {
                            DrawLargeHum();
                        }
                    }
                break;
                case 2:
                    if ((TempHumFlag & 1) || (u8editmode) || (AirS_GetHum() == 255)) {
                        DrawRegPower();
                    }
                break; 
                case 3:
                    DrawSetTempText();
                    if (u8editmode) {
                        u8menuswitch = 1;//force back screen
                    } else {
                        u8menuswitch--;
                        if (0==u8menuswitch) {
                           u8menuswitch = 65;
                           DrawClrLastLines(); 
                           DrawSetTempText();
                           Menu = MN_CLOCK;
                        }
                    }
                    break; 
            }
        break;
        
        //clock, date
        case MN_CLOCK:
            switch (Line) {
                case 0:
                    DrawTimeDate();
                    break;
                case 1:
                    DrawLargeTime();
                    break;
                case 2:
                    break;
                case 3:
                    u8menuswitch--;
                    if (0 == u8menuswitch) {
                        u8menuswitch = 35;
                        DrawClrLastLines();
                        Menu = MN_MAIN;
                        TempHumFlag ^= 1;
                    }
                    break;
            }
            break;
    }
    Line++;
    if (Line > 3) {
        Line = 0;
    }
}

void MNU_TaskButton(void) {
    if (IO_GetSW1Press())    {
        if (u8editmode){
            PRG_SetNewTemp(1);
        }
        else {
            DrawClrLastLines();
        }
        u8menuswitch = 40;
        Menu = MN_MAIN;
        u8editmode = EDIT_TIME;
    }
    else if (IO_GetSW2Press()) {
        if (u8editmode) {
            PRG_SetNewTemp(-1);
        }else {
            DrawClrLastLines();
        }
        u8menuswitch = 40;
        Menu = MN_MAIN;
        u8editmode = EDIT_TIME;
    }
    dotctr++;
    if (dotctr > ONSECDOT) {
        dotctr = 0;
    }
    
}



