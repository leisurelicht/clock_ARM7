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
** ��������: FIQ_Exception
** ��������: �����ж��쳣��������û�������Ҫ�Լ��ı����
**
** �䡡��: ��
**
** �䡡��: ��
**
** ȫ�ֱ���: ��
** ����ģ��: ��
********************************************************************************************************/
void FIQ_Exception(void)
{
  while(1);                                 // ��һ���滻Ϊ�Լ��Ĵ���
}

/*********************************************************************************************************
** ��������: TargetInit
** ��������: Ŀ����ʼ�����룬����Ҫ�ĵط����ã�������Ҫ�ı�
** �䡡��: ��
**
** �䡡��: ��
**
** ȫ�ֱ���: ��
** ����ģ��: ��
********************************************************************************************************/
void TargetInit(void)
{
    /* ����Լ��Ĵ��� */
}

/*********************************************************************************************************
** ��������: TargetResetInit
** ��������: ����main����ǰĿ����ʼ�����룬������Ҫ�ı䣬����ɾ��
** �䡡��: ��
**
** �䡡��: ��
**
** ȫ�ֱ���: ��
** ����ģ��: ��
********************************************************************************************************/
void TargetResetInit(void)
{
#ifndef NDEBUG
    MEMMAP = 0x2;                   //remap
#else
    MEMMAP = 0x1;                   //remap
#endif

    /* ����ϵͳ������ʱ�� */
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

    /* ���ô洢������ģ�� */
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

    /* ��ʼ��VIC */
    VICIntEnClear = 0xffffffff;
    VICVectAddr = 0;
    VICIntSelect = 0;

    /* ����Լ��Ĵ��� */

}


