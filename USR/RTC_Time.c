
#include  "config.h"
#include  "intrinsics.h"
#include "RTC.h"
#include "EINT.h"
#include "LCDTEST.h"

void Init()
{
   PINSEL0 &= 0x0FFFFFFF;
   PINSEL0 |= 0xA0000000;
   PINSEL1 = 0x00000301;                       // ���ùܽ����ӣ�P0.20����ΪEINT0
   PINSEL1&=0X0FFFFFFF;
   PINSEL0 &=0xF0000000;		                        // ����I/O���ӵ�UART1
   IO0DIR |=  0x0fffffff; 
   //IO0CLR |=0Xe0000000;
   IO0CLR |=0Xe000000f;
   IO0SET |=0X10000000;

   
   
  // UART0_Init();
   EINT_Init();
   LCD_Init ();            //Һ����ʼ��
   Get_time( );
}
extern uint8  Leap_flag;                          
uint8  rcv_data; 
/****************************************************************************
* ���ƣ�main()
* ���ܣ���������ʾ�������жϰ���������ʾ״̬���ֱ���ʾ�꣬���ڣ�ʱ�֣��������4��
״̬,KEY1���������л���ʾ״̬
****************************************************************************/

int  main(void)
{
  
   
   //uint8 *addr=&IRQ_Eint3;
   // FIQ_Init(13);
   TargetResetInit(); //����ʱĿ�겻����Ҫ��ʼ������ʵ�����ʱ�������Ҫ���Ρ�


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