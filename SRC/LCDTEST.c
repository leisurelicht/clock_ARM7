#include "LCDTEST.h"
#include "T6963C.h"
/*------------------ȫ�ֱ���--------------------*/

    uint8 NianYueRi[] = "2013/12/25";
    uint8 ShiFenMiao[]= "08:00:00";
    uint8 NaoZhong[]="08:32";


extern uint8  time_flag_0;
extern  uint8 LCD_flag;
extern uint8  ALARM_flag;
/********************************************************************************************************

** �������� ��RTCInit()

** �������� ����ʼ��ʵʱʱ��

** ��ڲ��� ����

** ���ڲ��� ����

*******************************************************************************************************

*/
void LCD_Init(void)
{

  IO0CLR=rst;
  IO0SET=rst;
  delay1(50);
  IO0CLR=ce;
  IO0SET=wr;
  IO0SET=rd;
  wr_xd(addr_w,0x40);                   //�ı���ʾ���׵�ַ
  wr_xd(addr_t,0x42);                   //ͼ����ʾ���׵�ַ
  wr_td(width,0x00,0x41);               //�ı���ʾ�����
  wr_td(width,0x00,0x43);               //ͼ����ʾ�����
  wr_comm(0x81);                        //�߼�"���"
  wr_td(0x56,0x00,0x22);                //CGRAMƫ�õ�ַ����
  wr_comm(0x9c);                        //�����ı���ʾ,����ͼ����ʾ
}
/****************************************************************************

* ���ƣ�PrintShiFenMiao()

* ���ܣ���ʾʱ��

* ��ڲ�����x,y 	��ʾλ�õ�����

* ���ڲ�������

***************************************************************************/
void PrintShiFenMiao(uint8 x,uint8 y)
{
  ShiFenMiao[1] = HOUR % 10 +'0';
  ShiFenMiao[0] = HOUR / 10 +'0';
  ShiFenMiao[4] = MIN % 10 +'0';
  ShiFenMiao[3] = MIN / 10 +'0';
  ShiFenMiao[7] = SEC % 10 +'0';
  ShiFenMiao[6] = SEC / 10 +'0';
  disp_zf(x,y, ShiFenMiao);
}
/****************************************************************************
* ���ƣ�PrintShiFenMiao()
* ���ܣ���ʾʱ��
* ��ڲ�����x,y 	��ʾλ�õ�����
* ���ڲ�������
****************************************************************************/
void PrintNianYueRi(uint8 x,uint8 y)
{
  NianYueRi[3] = YEAR % 10 + '0';
  NianYueRi[2] = YEAR%100/ 10 + '0';
  NianYueRi[1] = YEAR %1000/100 + '0';
  NianYueRi[0] = YEAR /1000 + '0';
  NianYueRi[6] = MONTH % 10 +'0';
  NianYueRi[5] = MONTH / 10 +'0';
  NianYueRi[9] = DOM % 10 +'0';
  NianYueRi[8] = DOM / 10 +'0';
  
  disp_zf(x,y, NianYueRi);
}
/****************************************************************************
* ���ƣ�PrintXingQi()
* ���ܣ���ʾʱ��
* ��ڲ�����x,y 	��ʾλ�õ�����
* ���ڲ�������
****************************************************************************/
void PrintXingQi(uint8 x,uint8 y)
{
  switch(DOW)
  {
  case 1:disp_hz(x,y,"����һ");;break;        
  case 2:disp_hz(x,y,"���ڶ�");break;
  case 3:disp_hz(x,y,"������");break;
  case 4:disp_hz(x,y,"������");break;
  case 5:disp_hz(x,y,"������");break;
  case 6:disp_hz(x,y,"������");break;
  case 7:disp_hz(x,y,"������");break;
  }
}

void Print_Alarm(uint8 x,uint8 y)
{
  NaoZhong[1] = ALHOUR % 10 +'0';
  NaoZhong[0] = ALHOUR / 10 +'0';
  NaoZhong[4] = ALMIN % 10 +'0';
  NaoZhong[3] = ALMIN / 10 +'0';
  disp_zf(x,y,NaoZhong);
}

void Print_Set(unsigned char x,unsigned char y)
{
  switch(time_flag_0)
  {
   case 0:disp_hz(x+3,y,"������");break;
   case 1:disp_hz(x+3,y,"������");break;
   case 2:disp_hz(x+3,y,"������");break;
   case 3:disp_hz(x+3,y,"������");break;
   case 4:disp_hz(x+3,y,"����ʱ");break;
   case 5:disp_hz(x+3,y,"���÷�");break;
   case 6:disp_hz(x+3,y,"����ʱ");break;
   case 7:disp_hz(x+3,y,"���ӷ�");break;
   default:break;
  }
}

void Print_year(unsigned char x,unsigned char y)
{
  unsigned char Leap_flag=Leap_year();
  switch(Leap_flag)
  {
   case 0:disp_hz(x,y,"ƽ��");break;
   case 1:disp_hz(x,y,"����");break;
   default:break;
  }
}

void LCD_PRINT(void)
{
    Init();
    clrram();
    while(LCD_flag)
    {
    disp_img(0,16,64,nBitmapDot);    //��ʾͼ��
    PrintNianYueRi(0,8);
    PrintShiFenMiao(1,9);
    PrintXingQi(10,4);
    disp_hz(0,5,"����");         //��ʾ����
    Print_Alarm(4,11);
    ALARM_Switch();
    Print_year(1,6);
    Print_Set(6,6);
    disp_hz(3,7,"�ǽ�ĺ��");         //��ʾ����
    
    
    ALARM_Enable();
   // Delayms(300);
    }
    clrram();
}

void LCD_Waite(void)
{
  clrram();
  while(!LCD_flag)
  {
   disp_img(0,16,128,nBitmapDot);    //��ʾͼ��
   ALARM_Enable();
   //Delayms(300);
   UART0_Init();
   Uart_Print();
   Init();
   disp_img(0,16,128,nBitmapDot_left);    //��ʾͼ��
   ALARM_Enable();
   //Delayms(300);
   UART0_Init();
   Uart_Print();
   Init();
   disp_img(0,16,128,nBitmapDot);    //��ʾͼ��
   ALARM_Enable();
   //Delayms(300);
   UART0_Init();
   Uart_Print();
   Init();
   disp_img(0,16,128,nBitmapDot_right);    //��ʾͼ��
   ALARM_Enable();
   //Delayms(300);
   UART0_Init();
   Uart_Print();
   Init();
  }
   clrram();
}

void LCD_SELECT(void)
{
   if(!LCD_flag)
   {
   clrram();
   LCD_Waite();
   }
   else if(LCD_flag)
   {
   clrram();
   LCD_PRINT();
   }
}

void ALARM_Switch(void)
{
  if(!ALARM_flag)
  {
    disp_hz(10,5,"���ӹ�");         //��ʾ����
  }
  else
  {
    disp_hz(10,5,"���ӿ�");         //��ʾ����
  }
  
}