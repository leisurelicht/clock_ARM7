#ifndef __LCDTEST_H
#define __LCDTEST_H


#include "Config.h"
#include "Target.h"

//#include "intrinsics.h"
#include <string.h>
#include "Delay.h"
#include "RTC.h"

void LCD_Init (void);
void PrintShiFenMiao(uint8 x,uint8 y);
void PrintNianYueRi(uint8 x,uint8 y);
void PrintXingQi(uint8 x,uint8 y);
void LCD_PRINT(void);
void LCD_Waite(void);
void LCD_SELECT(void);
void ALARM_Switch(void);

#endif 