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
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_2  | GPIO_Pin_6;	//SCK、MOSI
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	//GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
    GPIO_PinAFConfig(GPIOE, GPIO_PinSource2, GPIO_AF_SPI4);
    GPIO_PinAFConfig(GPIOE, GPIO_PinSource6, GPIO_AF_SPI4);
    GPIO_Init(GPIOE, &GPIO_InitStructure);
    
	GPIO_InitStructure.GPIO_Pin		= GPIO_Pin_8 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 ;		 //列  A、B、C和D
	GPIO_InitStructure.GPIO_Speed	= GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode	= GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType   = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin		= GPIO_Pin_4 | GPIO_Pin_7;	  //LT(SHCP)、EN
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
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);//使能定時器2時鐘
	TIM_DeInit(TIM2);//復位定時ん

	/* Time base configuration */
	// け頻率 = ((1 + TIM_Prescaler) / 72000000) * (1 + TIM_Period)
	// 1uS = ((1 + 71) / 72000000) * (1 + 2)
	
	//tim_init.TIM_Prescaler			= 71;	  //1uS = (1+TIM_Prescaler)/8000000  =>  TIM_Prescaler = 7   因為SIOC是8MHz(石英晶體震盪器)
	tim_init.TIM_Prescaler			= 71;
	//tim_init.TIM_Period				= 499;	  //從499開始數，499、500、501、502、...、1023、1024(一共526個)，直到溢位(1024)，產生Timer中斷，即每526uS產生一次Timer中斷
	tim_init.TIM_Period				= 499;
	tim_init.TIM_ClockDivision		= 0;
	tim_init.TIM_RepetitionCounter	= 0;
	tim_init.TIM_CounterMode		= TIM_CounterMode_Up;  //上數
	TIM_TimeBaseInit(TIM2, &tim_init);
	
	TIM_ClearFlag(TIM2, TIM_FLAG_Update);		//除 LED_TIM 溢出中斷標誌
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);	//LED_TIM 溢出中斷允許.
	TIM_Cmd(TIM2, ENABLE);                      //動 LED_TIM 計數

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
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;		//SPI設置為雙線雙向全雙工
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_16b;						//SPI發送接收 16 位幀結構
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;							//設置為主 SPI
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;								//時鐘懸空低
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;							//數據捕獲於第一個時鐘沿
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;								//內部 NSS 信號有 SSI位控制
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4;		//波特率預分頻值為 4	      APB2/8=72MHz/8=9MHz
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;						//數據傳輸從 MSB 位開始
	SPI_InitStructure.SPI_CRCPolynomial = 7;
	SPI_Init(SPI4, &SPI_InitStructure);
	/* Enable SPI1  */
	SPI_Cmd(SPI4, ENABLE);
	
	TIM_Config();
}
