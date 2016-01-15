#include "LCDTEST.h"
#include "T6963C.h"
/*------------------全局变量--------------------*/

    uint8 NianYueRi[] = "2013/12/25";
    uint8 ShiFenMiao[]= "08:00:00";
    uint8 NaoZhong[]="08:32";


extern uint8  time_flag_0;
extern  uint8 LCD_flag;
extern uint8  ALARM_flag;
/********************************************************************************************************

** 函数名称 ：RTCInit()

** 函数功能 ：初始化实时时钟

** 入口参数 ：无

** 出口参数 ：无

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
  wr_xd(addr_w,0x40);                   //文本显示区首地址
  wr_xd(addr_t,0x42);                   //图形显示区首地址
  wr_td(width,0x00,0x41);               //文本显示区宽度
  wr_td(width,0x00,0x43);               //图形显示区宽度
  wr_comm(0x81);                        //逻辑"异或"
  wr_td(0x56,0x00,0x22);                //CGRAM偏置地址设置
  wr_comm(0x9c);                        //启用文本显示,启用图形显示
}
/****************************************************************************

* 名称：PrintShiFenMiao()

* 功能：显示时钟

* 入口参数：x,y 	显示位置的坐标

* 出口参数：无

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
* 名称：PrintShiFenMiao()
* 功能：显示时钟
* 入口参数：x,y 	显示位置的坐标
* 出口参数：无
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
* 名称：PrintXingQi()
* 功能：显示时钟
* 入口参数：x,y 	显示位置的坐标
* 出口参数：无
****************************************************************************/
void PrintXingQi(uint8 x,uint8 y)
{
  switch(DOW)
  {
  case 1:disp_hz(x,y,"星期一");;break;        
  case 2:disp_hz(x,y,"星期二");break;
  case 3:disp_hz(x,y,"星期三");break;
  case 4:disp_hz(x,y,"星期四");break;
  case 5:disp_hz(x,y,"星期五");break;
  case 6:disp_hz(x,y,"星期六");break;
  case 7:disp_hz(x,y,"星期天");break;
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
   case 0:disp_hz(x+3,y,"关设置");break;
   case 1:disp_hz(x+3,y,"设置年");break;
   case 2:disp_hz(x+3,y,"设置月");break;
   case 3:disp_hz(x+3,y,"设置日");break;
   case 4:disp_hz(x+3,y,"设置时");break;
   case 5:disp_hz(x+3,y,"设置分");break;
   case 6:disp_hz(x+3,y,"闹钟时");break;
   case 7:disp_hz(x+3,y,"闹钟分");break;
   default:break;
  }
}

void Print_year(unsigned char x,unsigned char y)
{
  unsigned char Leap_flag=Leap_year();
  switch(Leap_flag)
  {
   case 0:disp_hz(x,y,"平年");break;
   case 1:disp_hz(x,y,"闰年");break;
   default:break;
  }
}

void LCD_PRINT(void)
{
    Init();
    clrram();
    while(LCD_flag)
    {
    disp_img(0,16,64,nBitmapDot);    //显示图画
    PrintNianYueRi(0,8);
    PrintShiFenMiao(1,9);
    PrintXingQi(10,4);
    disp_hz(0,5,"闹钟");         //显示汉字
    Print_Alarm(4,11);
    ALARM_Switch();
    Print_year(1,6);
    Print_Set(6,6);
    disp_hz(3,7,"城建暮晨");         //显示汉字
    
    
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
   disp_img(0,16,128,nBitmapDot);    //显示图画
   ALARM_Enable();
   //Delayms(300);
   UART0_Init();
   Uart_Print();
   Init();
   disp_img(0,16,128,nBitmapDot_left);    //显示图画
   ALARM_Enable();
   //Delayms(300);
   UART0_Init();
   Uart_Print();
   Init();
   disp_img(0,16,128,nBitmapDot);    //显示图画
   ALARM_Enable();
   //Delayms(300);
   UART0_Init();
   Uart_Print();
   Init();
   disp_img(0,16,128,nBitmapDot_right);    //显示图画
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
    disp_hz(10,5,"闹钟关");         //显示汉字
  }
  else
  {
    disp_hz(10,5,"闹钟开");         //显示汉字
  }
  
}