#ifndef UART_H
#define UART_H

#include "Config.h"
#include "LPCUart.h"

void  UART0_Ini(void);
void  UART0_SendStr(uint8 const *str);
#endif