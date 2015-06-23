#include "smartsensor.h"
#include <string.h>


// char * SensorList[SensorNum]={"AccSensor","MagSensor","GyroSensor","Ambient Light","Pressure","Temperature","Humidity","MIC_L","MIC_R"};
// char * SensorEnableList[SensorEnableNum]={"AccSensor","MagSensor","GyroSensor","Ambient Light","Pressure",
// 											"Temperature","Humidity","MIC_L","MIC_R","Attitude","Displacement","Rotation","Vibration","Shock"};

SmartSensorDataPacket SmartSensorData;

SensorData SData;

extern char SmartSensorTimeOutFlag;
void SmartSensorCMD_TX(char *str)
{
//		printf("TX:");
//		printf("%s\r\n",str);	
printf("\r");	
		USART6_Puts(str);
		USART6_Putc('\n');
}
bool SmartSensorCMD_RX(char *str)
{   
  bool temp;   	
	
//	printf("RX:");		
	temp=USART6_Gets( str);
//	printf_hex(str);
	
	return temp;
}

//void USART1_Init(uint32_t speed)
//{
//  GPIO_InitTypeDef GPIO_InitStructure;	
//	USART_InitTypeDef USART_InitStructure;

//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1| RCC_APB2Periph_GPIOA, ENABLE);
//	
//  /* Configure USART1 Tx (PA.09) as alternate function push-pull */
//  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
//  GPIO_Init(GPIOA, &GPIO_InitStructure);
//	
//  /* Configure USART1 Rx (PA.10) as input floating */
//  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
//  GPIO_Init(GPIOA, &GPIO_InitStructure);
//	

//	USART_InitStructure.USART_BaudRate = speed;
//	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
//	USART_InitStructure.USART_StopBits = USART_StopBits_1;
//	USART_InitStructure.USART_Parity = USART_Parity_No;
//	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
//	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

//	/* USART configuration */
//	USART_Init(USART1, &USART_InitStructure);

//	/* Enable USART1 Receive interrupts */
//	//USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);//開啟SUART1的接收中斷
//	/* Enable USART */
//	USART_Cmd(USART1, ENABLE);
//}

bool DeSmartSensorPacketData(char *RxBuffer)
{
  int SensorEnableFlag;
	int i, j;
	float	*pData_Float;
	int		*pData_Int;
	char	*pData_Char;
	unsigned char RxData[255];	
	u8 str_len,data_len,CmdLenght;
	conv_t tmp;
	
	SensorEnableFlag = 0;
	str_len =0;
	if(RxBuffer[str_len]=='\n') {printf("Packet no data\n"); return FALSE;}
	while((RxBuffer[str_len]!=(char)0xfd)&&(RxBuffer[str_len+1]!='\n'))
	{
		str_len++;
	}
	
	SmartSensorData.EndTx = RxBuffer[str_len];	
	
	data_len = RxBuffer[str_len-1];
	
	CmdLenght=str_len-data_len-2-4;
	
	SmartSensorData.StarTx = RxBuffer[CmdLenght];	
	
	//StarTx
	for (i=0, j=0; j<1; i++, j++)
		RxData[i] = RxBuffer[i+CmdLenght];
	pData_Char = (char *)(&RxData[i-1]);
	SmartSensorData.StarTx = *pData_Char;
	
	//DataFlag
	for (j=0; j<4; i++, j++)
		RxData[i] = RxBuffer[i+CmdLenght];
	pData_Int = (int *)(&RxData[i-4]);
	SensorEnableFlag = *pData_Int;

	if(SensorEnableFlag == 0) 
	{
		printf("Sensors data: No Sensors Enable\n\r"); return FALSE;
	}
	else if(SmartSensorData.StarTx==0xFA)
	{
		if( (SensorEnableFlag & 0x00000001) ) 
		{
			//Acc Data bit0
			for (j=0; j<4; i++, j++)
				RxData[i] = RxBuffer[i+CmdLenght];
//			pData_Float = (float *)(&RxData[i-4]);
//			SData.Acc[0]  = *pData_Float;
			CAtoF(SData.Acc[0], tmp, RxData, i-4);
				
			for (j=0; j<4; i++, j++)
				RxData[i] = RxBuffer[i+CmdLenght];
//			pData_Float = (float *)(&RxData[i-4]);
//			SData.Acc[1]  = *pData_Float;
			CAtoF(SData.Acc[1], tmp, RxData, i-4);
				
			for (j=0; j<4; i++, j++)
				RxData[i] = RxBuffer[i+CmdLenght];
//			pData_Float = (float *)(&RxData[i-4]);
//			SData.Acc[2]  = *pData_Float;
			CAtoF(SData.Acc[2], tmp, RxData, i-4);
		}
		if( (SensorEnableFlag & 0x00000002) >> 1 ) 
		{
			//Mag Data bit1
			for (j=0; j<4; i++, j++)
				RxData[i] = RxBuffer[i+CmdLenght];
//			pData_Float = (float *)(&RxData[i-4]);
//			SData.Mag[0]  = *pData_Float;
			CAtoF(SData.Mag[0], tmp, RxData, i-4);
				
			for (j=0; j<4; i++, j++)
				RxData[i] = RxBuffer[i+CmdLenght];
//			pData_Float = (float *)(&RxData[i-4]);
//			SData.Mag[1]  = *pData_Float;
			CAtoF(SData.Mag[1], tmp, RxData, i-4);
				
			for (j=0; j<4; i++, j++)
				RxData[i] = RxBuffer[i+CmdLenght];
//			pData_Float = (float *)(&RxData[i-4]);
//			SData.Mag[2]  = *pData_Float;
			CAtoF(SData.Mag[2], tmp, RxData, i-4);

		}
		if( (SensorEnableFlag & 0x00000004) >> 2 ) 
		{
			//Gyro Data bit2
			for (j=0; j<4; i++, j++)
				RxData[i] = RxBuffer[i+CmdLenght];
//			pData_Float = (float *)(&RxData[i-4]);
//			SData.Gyro[0]  = *pData_Float;
			CAtoF(SData.Gyro[0], tmp, RxData, i-4);
				
			for (j=0; j<4; i++, j++)
				RxData[i] = RxBuffer[i+CmdLenght];
//			pData_Float = (float *)(&RxData[i-4]);
//			SData.Gyro[1]  = *pData_Float;
			CAtoF(SData.Gyro[1], tmp, RxData, i-4);
				
			for (j=0; j<4; i++, j++)
				RxData[i] = RxBuffer[i+CmdLenght];
//			pData_Float = (float *)(&RxData[i-4]);
//			SData.Gyro[2]  = *pData_Float;
			CAtoF(SData.Gyro[2], tmp, RxData, i-4);

		}
		if( (SensorEnableFlag & 0x00000008) >> 3 ) 
		{ //Light Data bit3
			for (j=0; j<4; i++, j++)
				RxData[i] = RxBuffer[i+CmdLenght];
//			pData_Float = (float *)(&RxData[i-4]);
//			SData.Light  = *pData_Float;
			CAtoF(SData.Light, tmp, RxData, i-4);
		}
		if( (SensorEnableFlag & 0x00000010) >> 4 ) 
		{ //Press Data bit4
			for (j=0; j<4; i++, j++)
				RxData[i] = RxBuffer[i+CmdLenght];
//			pData_Float = (float *)(&RxData[i-4]);
//			SData.Pressure  = *pData_Float;
			CAtoF(SData.Pressure, tmp, RxData, i-4);
		}
		if( (SensorEnableFlag & 0x00000020) >> 5 ) 
		{ //Temp Data bit5
			for (j=0; j<4; i++, j++)
				RxData[i] = RxBuffer[i+CmdLenght];
//			pData_Float = (float *)(&RxData[i-4]);
//			SData.Temperature  = *pData_Float;
			CAtoF(SData.Temperature, tmp, RxData, i-4);
		}
		if( (SensorEnableFlag & 0x00000040) >> 6 ) 
		{ //Humi Data bit6 
			for (j=0; j<4; i++, j++)
				RxData[i] = RxBuffer[i+CmdLenght];
//			pData_Float = (float *)(&RxData[i-4]);
//			SData.Humidity  = *pData_Float;
			CAtoF(SData.Humidity, tmp, RxData, i-4);
		}
		if( (SensorEnableFlag & 0x0000080) >> 7 ) 
		{ //MIC_PDM_L Data bit7
			for (j=0; j<4; i++, j++)
				RxData[i] = RxBuffer[i+CmdLenght];
//			pData_Float = (float *)(&RxData[i-4]);
//			SData.MIC_PDM  = *pData_Float;
			CAtoF(SData.MIC_PDM, tmp, RxData, i-4);
		}
		if( (SensorEnableFlag & 0x00000200) >> 9 ) 
		{ //ATTI Data bit9
			for (j=0; j<4; i++, j++)
				RxData[i] = RxBuffer[i+CmdLenght];
//			pData_Float = (float *)(&RxData[i-4]);
//			SData.Attitude[0]  = *pData_Float;
			CAtoF(SData.Attitude[0], tmp, RxData, i-4);
				
			for (j=0; j<4; i++, j++)
				RxData[i] = RxBuffer[i+CmdLenght];
//			pData_Float = (float *)(&RxData[i-4]);
//			SData.Attitude[1]  = *pData_Float;
			CAtoF(SData.Attitude[1], tmp, RxData, i-4);
				
			for (j=0; j<4; i++, j++)
				RxData[i] = RxBuffer[i+CmdLenght];
//			pData_Float = (float *)(&RxData[i-4]);
//			SData.Attitude[2]  = *pData_Float;
			CAtoF(SData.Attitude[2], tmp, RxData, i-4);
		}
	}
// 	//DataSum
// 	for (j=0; j<1; i++, j++)
// 		RxData[i] = RxBuffer[i+CmdLenght];
// 	pData_Char = (char *)(&RxData[i-1]);
// 	SmartSensorData.DataSum = *pData_Char;
	
	//EndTx
// 	for (j=0; j<1; i++, j++)
// 		RxData[i] = RxBuffer[i+CmdLenght];
// 	pData_Char = (char *)(&RxData[i-1]);
// 	SmartSensorData.EndTx = *pData_Char;
// 	
// 	if(SmartSensorData.EndTx==0xFD)
// 	  return TRUE;
// 	else
// 		return FALSE;
	return TRUE;
}

