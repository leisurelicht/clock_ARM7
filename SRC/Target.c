/********************************************************************************************************
- FB-EDU-PARM-LPC2138 Target Initial file
-
- Author: Kruck Wang(Wang RongHua)
-
- Date: 2009-04-23
-
- Guangzhou Windway Electronic Technology Co., Ltd.
********************************************************************************************************/

#include "Target.h"
#include "Config.h"

 __irq void IRQ_Handler (void)
{
void (*interrupt_function)();
unsigned int vector;

  vector = VICVectAddr;     // Get interrupt vector.
  interrupt_function = (void(*)())vector;
  (*interrupt_function)();  // Call vectored interrupt function.
}
/*********************************************************************************************************
** 函数名称: FIQ_Exception
** 功能描述: 快速中断异常处理程序，用户根据需要自己改变程序
**
** 输　入: 无
**
** 输　出: 无
**
** 全局变量: 无
** 调用模块: 无
********************************************************************************************************/
void FIQ_Exception(void)
{
  while(1);                                 // 这一句替换为自己的代码
}

/*********************************************************************************************************
** 函数名称: TargetInit
** 功能描述: 目标板初始化代码，在需要的地方调用，根据需要改变
** 输　入: 无
**
** 输　出: 无
**
** 全局变量: 无
** 调用模块: 无
********************************************************************************************************/
void TargetInit(void)
{
    /* 添加自己的代码 */
}

/*********************************************************************************************************
** 函数名称: TargetResetInit
** 功能描述: 调用main函数前目标板初始化代码，根据需要改变，不能删除
** 输　入: 无
**
** 输　出: 无
**
** 全局变量: 无
** 调用模块: 无
********************************************************************************************************/
void TargetResetInit(void)
{
#ifndef NDEBUG
    MEMMAP = 0x2;                   //remap
#else
    MEMMAP = 0x1;                   //remap
#endif

    /* 设置系统各部分时钟 */
    PLLCON = 1;
#if (Fpclk / (Fcclk / 4)) == 1
    VPBDIV = 0;
#endif
#if (Fpclk / (Fcclk / 4)) == 2
    VPBDIV = 2;
#endif
#if (Fpclk / (Fcclk / 4)) == 4
    VPBDIV = 1;
#endif

#if (Fcco / Fcclk) == 2
    PLLCFG = ((Fcclk / Fosc) - 1) | (0 << 5);
#endif
#if (Fcco / Fcclk) == 4
    PLLCFG = ((Fcclk / Fosc) - 1) | (1 << 5);
#endif
#if (Fcco / Fcclk) == 8
    PLLCFG = ((Fcclk / Fosc) - 1) | (2 << 5);
#endif
#if (Fcco / Fcclk) == 16
    PLLCFG = ((Fcclk / Fosc) - 1) | (3 << 5);
#endif
    PLLFEED = 0xaa;
    PLLFEED = 0x55;
    while((PLLSTAT & (1 << 10)) == 0);
    PLLCON = 3;
    PLLFEED = 0xaa;
    PLLFEED = 0x55;

    /* 设置存储器加速模块 */
    MAMCR = 0;
#if Fcclk < 20000000
    MAMTIM = 1;
#else
#if Fcclk < 40000000
    MAMTIM = 2;
#else
    MAMTIM = 3;
#endif
#endif
    MAMCR = 2;

    /* 初始化VIC */
    VICIntEnClear = 0xffffffff;
    VICVectAddr = 0;
    VICIntSelect = 0;

    /* 添加自己的代码 */

}


