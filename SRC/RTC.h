#ifndef __RTC_H
#define __RTC_H


#include  "config.h"



void RTC_Init (void);
void RTC_Ring(void);
uint8 ALARM_CLOCK(void);
void ALARM_SELECT(void);
void Get_time(void);
void ALARM_Enable(void);
void LCD_Set(void);
unsigned char  Leap_year();
unsigned char max_day(unsigned char leap_flag);
void Get_Week(uint8 year,uint8 month,uint8 day);
//void Get_Time(struct DATE,struct TIME);

#endif