#include "EINT.h"

uint8  time_flag=1;
uint8  time_flag_0=0;
uint8  LCD_flag=0;

uint8  Leap_flag=0;
uint8  ALARM_flag=0;  //if is 1,alarm if on;else is 0,alarm is off.


void   IRQ_Eint3(void)
{  
   Get_time();
   LCD_flag=1;
   Delayms(20);    //延时10MS,防止按键断开时有干扰而误操作
   if((IO0PIN&KEY1)==0)
   {  
     
       time_flag_0=0;
       
   
   }
  while((EXTINT&0x08)!=0)
   EXTINT = 0x08;					// 清除EINT3中断标志
    VICVectAddr = 0x00;
}

void   IRQ_Eint2(void)
{ 
   Get_time();
   Delayms(20);    //延时10MS,防止按键断开时有干扰而误操作
   if((IO0PIN&KEY2)==0)
   { 
     
   switch(time_flag_0)
   {
   case 0:ALARM_flag=~ALARM_flag;break;
   case 1:YEAR++;Leap_flag=Leap_year();break;
   case 2:MONTH++;
          if(MONTH==13)MONTH=1;
          break;
   case 3:DOM++;DOW++;
          if(DOM==0)DOM=1;
          else if(DOW==0)DOW=1;
          break;
   case 4:HOUR++;
          if(HOUR==24)HOUR=0;
          break;
   case 5:MIN++;
          if(MIN==60)MIN=0;
          break;
   case 6:ALHOUR++;
          if(ALHOUR==24)ALHOUR=0;
          break;
   case 7:ALMIN++;
          if(ALMIN==60){ALMIN=0;ALHOUR++;}
          break;
   default:break;
   }
   
   }
  while((EXTINT&0x04)!=0)
   EXTINT = 0x04;					// 清除EINT3中断标志
    VICVectAddr = 0x00;
}
void   IRQ_Eint1(void)
{
   Get_time();  
   Delayms(10);    //延时10MS,防止按键断开时有干扰而误操作
   if((IO0PIN&KEY3)==0)
   { 
     
    switch(time_flag_0)
   {
   case 0:TRQ_ALARM_OFF();break;
   case 1:YEAR--;Leap_flag=Leap_year();break;
   case 2:MONTH--;
          if(MONTH==13)MONTH=1;
          break;
   case 3:DOM--;DOW--;
          if(DOM==0)DOM=1;
          else if(DOW==0)DOW=1;
          break;
   case 4:HOUR--;
          if(HOUR==24)HOUR=0;
          break;
   case 5:MIN--;
          if(MIN==63)MIN=59;
          break;
   case 6:ALHOUR--;
          if(ALHOUR==31)ALHOUR=23;
          break;
   case 7:ALMIN--;
          if(ALMIN==63)ALMIN=59;
          break;
   default:break;
   }
   }
  while((EXTINT&0x02)!=0)
   EXTINT = 0x02;					// 清除EINT3中断标志
   VICVectAddr = 0x00;
}

void   IRQ_Eint0(void)
{ 
   Delayms(20);    //延时10MS,防止按键断开时有干扰而误操作
   if((IO0PIN&KEY4)==0)
   {  
    time_flag_0++;
     if(time_flag_0==8)
     {
       time_flag_0=1;
       Get_time();
     }
   }
  while((EXTINT&0x01)!=0)
   EXTINT = 0x01;					// 清除EINT3中断标志
    VICVectAddr = 0x00;
}

void   IRQ_COUNT(void)
{
   Leap_flag=Leap_year();
   max_day(Leap_flag);
   ILR|=0x01;
    VICVectAddr = 0x00;
}

void   IRQ_RTC(void)
{  
  // do{
   //music();
 // }
  PINSEL1&=0X0FFFFFFF;
  IO0DIR |=0Xf0000000;
  IO0SET |=0Xe0000000;
  IO0CLR |=0X10000000;
  VICIntEnClear |= (1<<14);	               // 关闭EINT0中断
  time_flag_0=0;
}

void TRQ_ALARM_OFF(void)
{

  IO0DIR |=0Xf0000000;
  //IO0SET |=0Xf0000000;
  IO0CLR |=0Xf0000000;
  IO0SET |=0X10000000;
  VICIntEnable |= (1<<14);	               // 使能EINT0中断
}

uint8 IRQ_Init(uint8 num,uint8 slot,uint32 addr)
{
  if (num>31) return 0;
  if (slot>15) return 0;
  
   //VICIntSelect= VICIntSelect&(~(1<<num));
  // *(volatile uint32 *)((&VICVectCntl0)+slot) = 0x20|num;
   //*(volatile uint32 *)((&VICVectCntl0)+slot) = addr;
   VICIntEnable = (1<<num);
   __enable_irq();
   
   return 1;
}

uint8 FIQ_Init(uint8 num)
{
  if(num>31)return 0;
  
  VICIntSelect= VICIntSelect|(1<<num);
  VICIntEnable = (1<<num);
  __enable_fiq();
  return 1;
}
     

 
 __irq void FIQ_Handler(void)
{

  do{
   music();
  }while((EXTINT&0x08)!=0);
  EXTINT = 0x08;					// 清除EINT3中断标志
  VICVectAddr = 0x00;
  
}


void EINT_Init()
{
    /*PINSEL0 &= 0x0FFFFFFF;
    PINSEL0 |= 0x80000000| 0x20000000;
    PINSEL0 |= 0x20000000;
    PINSEL1 = 0x00000301;                       // 设置管脚连接，P0.20设置为EINT0*/
    VICIntSelect = 0x00000000;		       // 设置所有中断分配为IRQ中断
   
   
   EXTMODE  |= 0<<3;				// 设置EINT3中断为边沿触发模式
   EXTPOLAR |= 0<<3;                             // 设置EINT3中断为下降沿触发模式
   VICVectCntl3 = 0x20|17;                      // 0x20表示向量IRQ使能，1<<17表示EINT3在VIC通道14号 
   VICVectAddr3 = (int)IRQ_Eint3;             // 设置中断服务程序地址 
   EXTINT = 1<<3;			        // 清除EINT3中断标志	 EXTINT = 1<<3; 
   VICIntEnable |= (1<<17);		       // 使能EINT3中断
   
   
   EXTMODE  |= 0<<2;				// 设置EINT2中断为边沿触发模式
   EXTPOLAR |= 0<<2;                             // 设置EINT2中断为下降沿触发模式
   VICVectCntl2 = 0x20|16;                      // 0x20表示向量IRQ使能，
   VICVectAddr2 = (int)IRQ_Eint2;             // 设置中断服务程序地址
   EXTINT = 1<<2;			        // 清除EINT0中断标志	 EXTINT = 1<<0;
   VICIntEnable |= (1<<16);	               // 使能EINT0中断
   
   EXTMODE  |= 0<<1;				// 设置EINT2中断为边沿触发模式
   EXTPOLAR |= 0<<1;                             // 设置EINT2中断为下降沿触发模式
   VICVectCntl1 = 0x20|15;                      // 0x20表示向量IRQ使能，
   VICVectAddr1 = (int)IRQ_Eint1;             // 设置中断服务程序地址
   EXTINT = 1<<1;			        // 清除EINT0中断标志	 EXTINT = 1<<0;
   VICIntEnable |= (1<<15);	               // 使能EINT0中断
   
   EXTMODE  |= 0<<0;				// 设置EINT2中断为边沿触发模式
   EXTPOLAR |= 0<<0;                             // 设置EINT2中断为下降沿触发模式
   VICVectCntl4 = 0x20|14;                      // 0x20表示向量IRQ使能，
   VICVectAddr4 = (int)IRQ_Eint0;             // 设置中断服务程序地址
   EXTINT = 1<<0;			        // 清除EINT0中断标志	 EXTINT = 1<<0;
   VICIntEnable |= (1<<14);	               // 使能EINT0中断
   

   VICVectCntl5 = 0x20|13;                      // 0x20表示向量IRQ使能，
   VICVectAddr5 = (int)IRQ_COUNT;             // 设置中断服务程序地址
   ILR|=0x1;
   CIIR |= 0Xf8;
   VICIntEnable |= (1<<13);	               // 使能RTCCIF中断
   
   __enable_irq();                             //允许IRQ中断
} 