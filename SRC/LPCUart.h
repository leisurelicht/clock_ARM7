/********************************************************************************************************
- FB-EDU-PARM-LPC2138 UART header file
-
- Author: Kruck Wang(Wang RongHua)
-
- Date: 2009-04-23
-
- Guangzhou Windway Electronic Technology Co., Ltd.
********************************************************************************************************/

#define LCR_WORDLENTH_BIT         0
#define LCR_STOPBITSEL_BIT        2
#define LCR_PARITYENBALE_BIT      3
#define LCR_PARITYSEL_BIT         4
#define LCR_BREAKCONTROL_BIT      6
#define LCR_DLAB_BIT              7

 // Word Length type
typedef enum {
    WordLength5 = 0,
    WordLength6,
    WordLength7,
    WordLength8
} LPC_Uart_WordLenth_t;