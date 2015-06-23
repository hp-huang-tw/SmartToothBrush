#include "init_interface.h"


void GPIO_init()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOB | RCC_AHB1Periph_GPIOC | RCC_AHB1Periph_GPIOE, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI4, ENABLE);
}
void GPIO_Configureation(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
   
	//SPI1 
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_2  | GPIO_Pin_6;	//SCK�BMOSI
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	//GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
    GPIO_PinAFConfig(GPIOE, GPIO_PinSource2, GPIO_AF_SPI4);
    GPIO_PinAFConfig(GPIOE, GPIO_PinSource6, GPIO_AF_SPI4);
    GPIO_Init(GPIOE, &GPIO_InitStructure);
    
	GPIO_InitStructure.GPIO_Pin		= GPIO_Pin_8 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 ;		 //�C  A�BB�BC�MD
	GPIO_InitStructure.GPIO_Speed	= GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode	= GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType   = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin		= GPIO_Pin_4 | GPIO_Pin_7;	  //LT(SHCP)�BEN
	GPIO_InitStructure.GPIO_Speed	= GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode	= GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType   = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
}
void TIM_Config()
{
	TIM_TimeBaseInitTypeDef tim_init;
	NVIC_InitTypeDef nvic_init;

	/* TIM2 clock enable */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);//�ϯ�w�ɾ�2����
	TIM_DeInit(TIM2);//�_��w����

	/* Time base configuration */
	// Ƶ�W�v = ((1 + TIM_Prescaler) / 72000000) * (1 + TIM_Period)
	// 1uS = ((1 + 71) / 72000000) * (1 + 2)
	
	//tim_init.TIM_Prescaler			= 71;	  //1uS = (1+TIM_Prescaler)/8000000  =>  TIM_Prescaler = 7   �]��SIOC�O8MHz(�ۭ^����_����)
	tim_init.TIM_Prescaler			= 71;
	//tim_init.TIM_Period				= 499;	  //�q499�}�l�ơA499�B500�B501�B502�B...�B1023�B1024(�@�@526��)�A���췸��(1024)�A����Timer���_�A�Y�C526uS���ͤ@��Timer���_
	tim_init.TIM_Period				= 499;
	tim_init.TIM_ClockDivision		= 0;
	tim_init.TIM_RepetitionCounter	= 0;
	tim_init.TIM_CounterMode		= TIM_CounterMode_Up;  //�W��
	TIM_TimeBaseInit(TIM2, &tim_init);
	
	TIM_ClearFlag(TIM2, TIM_FLAG_Update);		//�� LED_TIM ���X���_�лx
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);	//LED_TIM ���X���_���\.
	TIM_Cmd(TIM2, ENABLE);                      //�� LED_TIM �p��

	nvic_init.NVIC_IRQChannel					= TIM2_IRQn;
	//nvic_init.NVIC_IRQChannelPreemptionPriority	= 0;
	nvic_init.NVIC_IRQChannelPreemptionPriority	= 1;
	nvic_init.NVIC_IRQChannelSubPriority		= 1;
	nvic_init.NVIC_IRQChannelCmd				= ENABLE;
	NVIC_Init(&nvic_init);
}

void SPI_init()
{
	SPI_InitTypeDef  SPI_InitStructure;

	/* SPI configuration -------------------------------------------------------*/
	SPI_I2S_DeInit(SPI4);
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;		//SPI�]�m�����u���V�����u
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_16b;						//SPI�o�e���� 16 ��V���c
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;							//�]�m���D SPI
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;								//�����a�ŧC
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;							//�ƾڮ����Ĥ@�Ӯ����u
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;								//���� NSS �H���� SSI�챱��
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4;		//�i�S�v�w���W�Ȭ� 4	      APB2/8=72MHz/8=9MHz
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;						//�ƾڶǿ�q MSB ��}�l
	SPI_InitStructure.SPI_CRCPolynomial = 7;
	SPI_Init(SPI4, &SPI_InitStructure);
	/* Enable SPI1  */
	SPI_Cmd(SPI4, ENABLE);
	
	TIM_Config();
}
