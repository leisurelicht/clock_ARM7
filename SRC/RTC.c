#include "RTC.h"


struct DATE
{
  uint16 year;
  uint8 mon;
  uint8 day;
};

struct TIME
{
  uint8 hour;
  uint8 min;
  uint8 sec;
};

 struct TIME *time;
 extern  uint8 LCD_flag;
 
 extern uint8  ALARM_flag;
/*
*******************************************************************************************************
** 函数名称 ：RTCInit()
** 函数功能 ：初始化实时时钟
** 入口参数 ：无
** 出口参数 ：无
*******************************************************************************************************
*/
void RTC_Init (void)
{
	PREINT = Fpclk / 32768 - 1;	// 设置基准时钟分频器
	PREFRAC = Fpclk - (Fpclk / 32768) * 32768;
	
	CCR   = 0x00;	// 禁止时间计数器
	
	YEAR  = 2012;
	MONTH = 12;
	DOM   = 25;
	DOW   = 3;
	HOUR  = 8;
	MIN   = 0;
	SEC   = 55;
	
	CIIR = 0x01;	// 设置秒值的增量产生1次中断
	CCR  = 0x01;	// 启动RTC
}


void Get_time(void )
{
  
   time->hour=HOUR;
   time->min=MIN;
   time->sec=SEC;
}

uint8 LCD_RESERT(void)
{
   if(HOUR==time->hour)
  {
    if(MIN==time->min)
    {
      if(SEC==((time->sec)+20))
      {return  1;}
    }
  }
  return 0;
}




void Get_Time(struct DATE *d,struct TIME *t)
{
  uint32 times,dates;
  times = CTIME0;
  dates= CTIME1;
    d->year=(dates >> 16) & 0xFFF;
    d->mon= (dates >> 8) & 0X0F;
    d->day=dates & 0x1f;
    t->hour=(times >> 16) &0x1f;
    t->min= (times >> 8) & 0x3f;
    t->sec= times & 0x3f;
    
        
}


void LCD_Set(void)
{
  if(LCD_RESERT()!=0)
  {
     LCD_flag=0;
  }
}

void RTC_Ring()
{
  
  ILR=0X00;
  ALHOUR=8;
  ALMIN=1;
  ALSEC=00;
 // AMR=0XF8;
}


uint8 ALARM_CLOCK()
{
  if(HOUR==ALHOUR)
  {
    if(MIN==ALMIN)
    {
      if(SEC==ALSEC)
      {return  1;}
    }
  }
  return 0;
}

uint8 ALARM_CLOCK_OFF()
{
  if(HOUR==ALHOUR)
  {
    if(MIN==ALMIN)
    {
      if(SEC==10)
      {return  1;}
    }
  }
  return 0;
}




void ALARM_SELECT(void)
{
   if( 1==ALARM_CLOCK())
   {
     IRQ_RTC();
   }
   if (1==LCD_RESERT())
   {
     LCD_flag=0;
   }
}

void ALARM_Enable(void)
{
 
  if(ALARM_flag!=0)
  {
  ALARM_SELECT();
  }
  LCD_Set();
}

unsigned char  Leap_year()
{
  if(YEAR%4==0)
  {
    if(YEAR%100!=0)
    {
    return 1;
    }
  }
  else if(YEAR%400==0)
  {
    return 1;
  }
  else 
    return 0;
}

unsigned char max_day(unsigned char leap_flag)
{
  Get_Week(YEAR,MONTH,DOM);
  if(leap_flag==1&&MONTH==2)
  {
      if(DOM==30)
        {
          DOM=1;
        }
  }
  else if (leap_flag==0&&MONTH==2)
  {
      if(DOM==29)
      {
        {
          DOM=1;
        }
      }
  }
  else if(MONTH==4|MONTH==6|MONTH==9|MONTH==11)
  {
    if(DOM==31)
    {
      DOM=1;
    }
  }

}


void Get_Week(uint8 year,uint8 month,uint8 day)
{

if(month==1||month==2)//判断month是否为1或2　　
{
year--;
month+=12;
}
int c=year/100;
int y=year-c*100;
int week=(c/4)-2*c+(y+y/4)+(13*(month+1)/5)+day-1;
while(week<0){ week+=7; }
week%=7;
switch(week)
{
case 1: DOW=1; break;
case 2: DOW=2; break;
case 3: DOW=3; break;
case 4: DOW=4;break;
case 5: DOW=5; break;
case 6: DOW=6;break;
case 0: DOW=7; break;
}

}
