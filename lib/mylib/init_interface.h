#ifndef __INIT_INTERFACE_H
#define __INIT_INTERFACE_H

#include "stm32f4xx_gpio.h"
#include "stm32f4xx_spi.h"
#include "stm32f4xx_usart.h"


void GPIO_init(void);
void GPIO_Configureation(void);
void TIM_Config(void);
void SPI_init(void);
#endif  //__INIT_INTERFACE_H
