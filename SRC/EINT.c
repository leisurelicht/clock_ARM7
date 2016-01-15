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
   Delayms(20);    //��ʱ10MS,��ֹ�����Ͽ�ʱ�и��Ŷ������
   if((IO0PIN&KEY1)==0)
   {  
     
       time_flag_0=0;
       
   
   }
  while((EXTINT&0x08)!=0)
   EXTINT = 0x08;					// ���EINT3�жϱ�־
    VICVectAddr = 0x00;
}

void   IRQ_Eint2(void)
{ 
   Get_time();
   Delayms(20);    //��ʱ10MS,��ֹ�����Ͽ�ʱ�и��Ŷ������
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
   EXTINT = 0x04;					// ���EINT3�жϱ�־
    VICVectAddr = 0x00;
}
void   IRQ_Eint1(void)
{
   Get_time();  
   Delayms(10);    //��ʱ10MS,��ֹ�����Ͽ�ʱ�и��Ŷ������
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
   EXTINT = 0x02;					// ���EINT3�жϱ�־
   VICVectAddr = 0x00;
}

void   IRQ_Eint0(void)
{ 
   Delayms(20);    //��ʱ10MS,��ֹ�����Ͽ�ʱ�и��Ŷ������
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
   EXTINT = 0x01;					// ���EINT3�жϱ�־
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
  VICIntEnClear |= (1<<14);	               // �ر�EINT0�ж�
  time_flag_0=0;
}

void TRQ_ALARM_OFF(void)
{

  IO0DIR |=0Xf0000000;
  //IO0SET |=0Xf0000000;
  IO0CLR |=0Xf0000000;
  IO0SET |=0X10000000;
  VICIntEnable |= (1<<14);	               // ʹ��EINT0�ж�
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
  EXTINT = 0x08;					// ���EINT3�жϱ�־
  VICVectAddr = 0x00;
  
}


void EINT_Init()
{
    /*PINSEL0 &= 0x0FFFFFFF;
    PINSEL0 |= 0x80000000| 0x20000000;
    PINSEL0 |= 0x20000000;
    PINSEL1 = 0x00000301;                       // ���ùܽ����ӣ�P0.20����ΪEINT0*/
    VICIntSelect = 0x00000000;		       // ���������жϷ���ΪIRQ�ж�
   
   
   EXTMODE  |= 0<<3;				// ����EINT3�ж�Ϊ���ش���ģʽ
   EXTPOLAR |= 0<<3;                             // ����EINT3�ж�Ϊ�½��ش���ģʽ
   VICVectCntl3 = 0x20|17;                      // 0x20��ʾ����IRQʹ�ܣ�1<<17��ʾEINT3��VICͨ��14�� 
   VICVectAddr3 = (int)IRQ_Eint3;             // �����жϷ�������ַ 
   EXTINT = 1<<3;			        // ���EINT3�жϱ�־	 EXTINT = 1<<3; 
   VICIntEnable |= (1<<17);		       // ʹ��EINT3�ж�
   
   
   EXTMODE  |= 0<<2;				// ����EINT2�ж�Ϊ���ش���ģʽ
   EXTPOLAR |= 0<<2;                             // ����EINT2�ж�Ϊ�½��ش���ģʽ
   VICVectCntl2 = 0x20|16;                      // 0x20��ʾ����IRQʹ�ܣ�
   VICVectAddr2 = (int)IRQ_Eint2;             // �����жϷ�������ַ
   EXTINT = 1<<2;			        // ���EINT0�жϱ�־	 EXTINT = 1<<0;
   VICIntEnable |= (1<<16);	               // ʹ��EINT0�ж�
   
   EXTMODE  |= 0<<1;				// ����EINT2�ж�Ϊ���ش���ģʽ
   EXTPOLAR |= 0<<1;                             // ����EINT2�ж�Ϊ�½��ش���ģʽ
   VICVectCntl1 = 0x20|15;                      // 0x20��ʾ����IRQʹ�ܣ�
   VICVectAddr1 = (int)IRQ_Eint1;             // �����жϷ�������ַ
   EXTINT = 1<<1;			        // ���EINT0�жϱ�־	 EXTINT = 1<<0;
   VICIntEnable |= (1<<15);	               // ʹ��EINT0�ж�
   
   EXTMODE  |= 0<<0;				// ����EINT2�ж�Ϊ���ش���ģʽ
   EXTPOLAR |= 0<<0;                             // ����EINT2�ж�Ϊ�½��ش���ģʽ
   VICVectCntl4 = 0x20|14;                      // 0x20��ʾ����IRQʹ�ܣ�
   VICVectAddr4 = (int)IRQ_Eint0;             // �����жϷ�������ַ
   EXTINT = 1<<0;			        // ���EINT0�жϱ�־	 EXTINT = 1<<0;
   VICIntEnable |= (1<<14);	               // ʹ��EINT0�ж�
   

   VICVectCntl5 = 0x20|13;                      // 0x20��ʾ����IRQʹ�ܣ�
   VICVectAddr5 = (int)IRQ_COUNT;             // �����жϷ�������ַ
   ILR|=0x1;
   CIIR |= 0Xf8;
   VICIntEnable |= (1<<13);	               // ʹ��RTCCIF�ж�
   
   __enable_irq();                             //����IRQ�ж�
} 