
#include  "config.h"
#include  "intrinsics.h"
#include "RTC.h"
#include "EINT.h"
#include "LCDTEST.h"

void Init()
{
   PINSEL0 &= 0x0FFFFFFF;
   PINSEL0 |= 0xA0000000;
   PINSEL1 = 0x00000301;                       // 设置管脚连接，P0.20设置为EINT0
   PINSEL1&=0X0FFFFFFF;
   PINSEL0 &=0xF0000000;		                        // 设置I/O连接到UART1
   IO0DIR |=  0x0fffffff; 
   //IO0CLR |=0Xe0000000;
   IO0CLR |=0Xe000000f;
   IO0SET |=0X10000000;

   
   
  // UART0_Init();
   EINT_Init();
   LCD_Init ();            //液晶初始化
   Get_time( );
}
extern uint8  Leap_flag;                          
uint8  rcv_data; 
/****************************************************************************
* 名称：main()
* 功能：万年历显示。利用中断按键控制显示状态，分别显示年，日期，时分，秒和星期4个
状态,KEY1按键用来切换显示状态
****************************************************************************/

int  main(void)
{
  
   
   //uint8 *addr=&IRQ_Eint3;
   // FIQ_Init(13);
   TargetResetInit(); //仿真时目标不不需要初始化，本实验仿真时此语句需要屏蔽。


   Init();
   RTC_Init ();
   RTC_Ring();
   TRQ_ALARM_OFF();
  while(1)
  {
   LCD_SELECT();
   //ALARM_Enable();
  }
   //while(1)
   //{
      //Uart_Print();
      //Delayms(1000);
  //} 
}