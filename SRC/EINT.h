#ifndef __EINT_H
#define __EINT_H

#include  "config.h"
#include  "intrinsics.h"
#include  <iolpc2134.h>

#define   KEY1           (1<<20)
#define   KEY2           (1<<15)
#define   KEY3           (1<<14)
#define   KEY4           (1<<16)
#define   KEY5           (1<<25)

#define   LED1           (1<<26)





void   IRQ_Eint3(void);
void   IRQ_Eint2(void);
void   IRQ_Eint1(void);
void   IRQ_Eint0(void);
void   IRQ_RTC(void);
uint8 IRQ_Init(uint8 num,uint8 slot,uint32 addr);
uint8 FIQ_Init(uint8 num);
__irq void FIQ_Handler(void);
void EINT_Init();
void TRQ_ALARM_OFF(void);

#endif