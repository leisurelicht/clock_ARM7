/********************************************************************************************************
- FB-EDU-PARM-LPC2138 Configuration file
-
- Author: Kruck Wang(Wang RongHua)
-
- Date: 2009-04-23
-
- Guangzhou Windway Electronic Technology Co., Ltd.
********************************************************************************************************/
#ifndef CONFIG_H
#define CONFIG_H

//定义BOOL变量
#ifndef TRUE
#define TRUE  1
#endif

#ifndef FALSE
#define FALSE 0
#endif

//定义变量类型
typedef unsigned char  uint8;                   /* 无符号8位整型变量                        */
typedef signed   char  int8;                    /* 有符号8位整型变量                        */
typedef unsigned short uint16;                  /* 无符号16位整型变量                       */
typedef signed   short int16;                   /* 有符号16位整型变量                       */
typedef unsigned int   uint32;                  /* 无符号32位整型变量                       */
typedef signed   int   int32;                   /* 有符号32位整型变量                       */
typedef float          fp32;                    /* 单精度浮点数（32位长度）                 */
typedef double         fp64;                    /* 双精度浮点数（64位长度）                 */


/********************************/
/*      LPC2138的寄存器定义     */
/********************************/

#include    <iolpc2138.h>

/*********************************************/
/* 系统设置, Fosc、Fcclk、Fcco、Fpclk必须定义*/	
/*********************************************/
#define Fosc            20000000                    //晶振频率,10MHz~25MHz，应当与实际一至
#define Fcclk           (Fosc * 3)                  //系统频率，必须为Fosc的整数倍(1~32)，且<=60MHZ
#define Fcco            (Fcclk * 4)                 //CCO频率，必须为Fcclk的2、4、8、16倍，范围为156MHz~320MHz
#define Fpclk           (Fcclk / 4) * 2             //VPB时钟频率，只能为(Fcclk / 4)的1、2、4倍

#include    "target.h"

#include    <stdio.h>

#endif
