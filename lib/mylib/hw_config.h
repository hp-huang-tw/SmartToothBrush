#ifndef __HW_CONFIG_H
#define __HW_CONFIG_H

#include "stm32f4xx.h"
#include "system_stm32f4xx.h"
#include "stdio.h"
#include "init_interface.h"

typedef enum {FALSE = 0, TRUE = !FALSE} bool;

void hw_config(void);
void UART1_Init(uint32_t buadrate);
void UART2_Init(uint32_t buadrate);
void UART6_Init(uint32_t buadrate);

void USART1_Puts(char *str);
bool USART1_Gets(char *str);
void USART1_Putc(unsigned char c);
void USART2_Puts(char *str);
bool USART2_Gets(char *str);
void USART2_Putc(unsigned char c);

void USART6_Puts(char *str);
bool USART6_Gets(char *str);
void USART6_Putc(unsigned char c);

void printf_hex(char *str);

void TimerStart(void);
void TimerReset(void);
void TimerStop(void);
void TIM_Configuration(void);

#endif  //__HW_CONFIG_H
