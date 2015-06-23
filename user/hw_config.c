/******************************************************************************
 *	FileName: System_setting
 *	Author:	MIAT Lab.
 *****************************************************************************/
#include "stm32f4xx.h"
#include "hw_config.h"

ErrorStatus HSEStartUpStatus;
char TimeOutFlag;

void hw_config(void)
{
	SystemInit();	
	
	UART1_Init(9600);
	UART6_Init(9600);

	TIM_Configuration();
}

void UART1_Init(uint32_t buadrate)
{
	USART_InitTypeDef USART_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);  
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

	GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_USART1);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_USART1);

	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; 
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF; 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure); 


	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; 
	GPIO_Init(GPIOA, &GPIO_InitStructure); 

	USART_InitStructure.USART_BaudRate =buadrate;//9600; 
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1; 
	USART_InitStructure.USART_Parity = USART_Parity_No; 
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; 
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;  
	USART_Init(USART1, &USART_InitStructure); 

	USART_Cmd(USART1, ENABLE);
}

void UART2_Init(uint32_t buadrate)
{
	USART_InitTypeDef USART_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);  
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

	GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_USART2);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_USART2);

	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; 
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF; 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure); 


	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3; 
	GPIO_Init(GPIOA, &GPIO_InitStructure); 

	USART_InitStructure.USART_BaudRate =buadrate; 
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1; 
	USART_InitStructure.USART_Parity = USART_Parity_No; 
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; 
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;  
	USART_Init(USART2, &USART_InitStructure); 

	USART_Cmd(USART2, ENABLE);
}

void UART6_Init(uint32_t buadrate)
{
	USART_InitTypeDef USART_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);  
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART6, ENABLE);

	GPIO_PinAFConfig(GPIOG, GPIO_PinSource14, GPIO_AF_USART6);
	GPIO_PinAFConfig(GPIOG, GPIO_PinSource9, GPIO_AF_USART6);

	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; 
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF; 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOG, &GPIO_InitStructure); 


	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; 
	GPIO_Init(GPIOG, &GPIO_InitStructure); 

	USART_InitStructure.USART_BaudRate =buadrate; 
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1; 
	USART_InitStructure.USART_Parity = USART_Parity_No; 
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; 
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;  
	USART_Init(USART6, &USART_InitStructure); 

	USART_Cmd(USART6, ENABLE);
}


void printf_hex(char *str)
{
	int i;
	
	i=0;
	//printf("HEX:");
	while(str[i]!='\n')
	{
		printf("0x%x ",str[i]);
		i++;
	}

	printf("\r\n");
}

void USART1_Puts(char * str)
{
	while(*str)
	{
		USART_SendData(USART1, *str++);

		while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
	}
}
void USART2_Puts(char * str)
{
	while(*str)
	{
		USART_SendData(USART2, *str++);

		while(USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET);
	}
}
void USART6_Puts(char * str)
{
	while(*str)
	{
		USART_SendData(USART6, *str++);

		while(USART_GetFlagStatus(USART6, USART_FLAG_TXE) == RESET);
	}
}

bool USART1_Gets(char *str)
{
	  int RxCounter;
	
		RxCounter=0;
		TimerStart();
		do
		{	
			TimerReset();
		  /* Loop until the USART1 Receive Data Register is not empty */
      while((USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET)&&(TimeOutFlag==0))
      { }
			if(TimeOutFlag==1)
			{	
				str[RxCounter++]='\n'; 
			}
      /* Store the received byte in RxBuffer */
      else str[RxCounter++] = USART_ReceiveData(USART1);  
			//USART_ClearFlag(USART1, USART_FLAG_RXNE);
	  }
	  while(str[RxCounter-1]!='\n');
		//RxCounter++;
		str[RxCounter++]=0;
		TimerStop();
		if(TimeOutFlag==1)
    { 
		  str[RxCounter++]=0;
			printf("UART1 Not Connected\n");
			return FALSE;
		}	
    else
		{
			return TRUE; 
    }			
		//*length=RxCounter;
		//if(RxCounter==0) return 0; else return 1;
}
bool USART2_Gets(char *str)
{
	  int RxCounter;
	
		RxCounter=0;
		TimerStart();
		do
		{	
			TimerReset();
		  /* Loop until the USART2 Receive Data Register is not empty */
      while((USART_GetFlagStatus(USART2, USART_FLAG_RXNE) == RESET)&&(TimeOutFlag==0))
      { }
			if(TimeOutFlag==1)
			{	
				str[RxCounter++]='\n'; 
			}
      /* Store the received byte in RxBuffer */
      else str[RxCounter++] = USART_ReceiveData(USART2);  
			//USART_ClearFlag(USART2, USART_FLAG_RXNE);
	  }
	  while(str[RxCounter-1]!='\n');
		//RxCounter++;
		str[RxCounter++]=0;
		TimerStop();
		if(TimeOutFlag==1)
    { 
		  str[RxCounter++]=0;
			printf("UART 2 Not Connected\n");
			return FALSE;
		}	
    else
		{
			return TRUE; 
    }			
		//*length=RxCounter;
		//if(RxCounter==0) return 0; else return 1;
}
bool USART6_Gets(char *str)
{
	  int RxCounter;
	
		RxCounter=0;
		TimerStart();
		do
		{	
			TimerReset();
		  /* Loop until the USART6 Receive Data Register is not empty */
      while((USART_GetFlagStatus(USART6, USART_FLAG_RXNE) == RESET)&&(TimeOutFlag==0))
      { }
			if(TimeOutFlag==1)
			{	
				str[RxCounter++]='\n'; 
			}
      /* Store the received byte in RxBuffer */
      else str[RxCounter++] = USART_ReceiveData(USART6);  
			//USART_ClearFlag(USART6, USART_FLAG_RXNE);
	  }
	  while(str[RxCounter-1]!='\n');
		//RxCounter++;
		str[RxCounter++]=0;
		TimerStop();
		if(TimeOutFlag==1)
    { 
		  str[RxCounter++]=0;
			printf("UART 6 Not Connected\n");
			return FALSE;
		}	
    else
		{
			return TRUE; 
    }			
		//*length=RxCounter;
		//if(RxCounter==0) return 0; else return 1;
}
void USART1_Putc(unsigned char c)
{
    USART_SendData(USART1, c);
	
    while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET );
}

void USART2_Putc(unsigned char c)
{
    USART_SendData(USART2, c);
	
    while(USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET );
}
void USART6_Putc(unsigned char c)
{
    USART_SendData(USART6, c);
	
    while(USART_GetFlagStatus(USART6, USART_FLAG_TXE) == RESET );
}


void TimerStart(void)
{
	TimeOutFlag=0;
	TIM_SetCounter(TIM2, 0);

  /* TIM2 enable counter */ 
  TIM_Cmd(TIM2, ENABLE); 	  	
}
void TimerReset(void)
{
	TIM_Cmd(TIM2, DISABLE);
	TIM_SetCounter(TIM2, 0);	
	TIM_Cmd(TIM2, ENABLE);
}
void TimerStop(void)
{
	/* TIM2 enable counter */
  TIM_Cmd(TIM2, DISABLE); 	  
}
void TIM_Configuration(void)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	uint16_t PrescalerValue = 0;
	
//    In this example TIM2 input clock (TIM2CLK) is set to 4 * APB1 clock (PCLK1), 
//    since TIMPRE bit from RCC_DCKCFGR register is set.   
//      TIM2CLK = 4 * PCLK1
//      PCLK1 = HCLK / 4 
//      => TIM4CLK = HCLK = SystemCoreClock
//          
//    To get TIM2 counter clock at 12000Hz, the prescaler is computed as follows:
//       Prescaler = (TIM2CLK / TIM2 counter clock) - 1
//       Prescaler = (SystemCoreClock /12000Hz) - 1
//                                              
//    To get TIM2 output clock at 1Hz, the period (ARR)) is computed as follows:
//       ARR = (TIM2 counter clock / TIM2 output clock) - 1
//           = 12000-1	
	
  /* TIM4 clock enable */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	TIM_DeInit(TIM2);
  RCC_TIMCLKPresConfig(RCC_TIMPrescActivated);
  /* Compute the prescaler value */
  PrescalerValue = (uint16_t) (SystemCoreClock / 12000) - 1;

  /* Time base configuration */
  TIM_TimeBaseStructure.TIM_Period = 12000-1;
  TIM_TimeBaseStructure.TIM_Prescaler = PrescalerValue;
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
	
	TIM_ClearFlag(TIM2, TIM_FLAG_Update);		
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	TIM_Cmd(TIM2, ENABLE);                    
	
	/* Enable the TIM2 Interrupt */ 
  NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn; 
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; 
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0; 
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
  NVIC_Init(&NVIC_InitStructure); 
	
}

