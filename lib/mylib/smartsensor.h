#ifndef SMARTSENSOR_H
#define SMARTSENSOR_H

#include "stm32f4xx.h"

#include "hw_config.h"




void USART1_Puts(char *str);
bool USART1_Gets(char *str);
void USART1_Putc(unsigned char c);
//void USART1_Init(uint32_t speed);
void printf_hex(char *str);

void SmartSensorCMD_TX(char *str);
bool SmartSensorCMD_RX(char *str);
bool DeSmartSensorPacketData(char *str);

//void TIM_Configuration(void);
//void TimerStart(void);
//void TimerStop(void);

//Smart Sensor Packet
typedef struct{
	uint8_t 	StarTx;
	uint32_t 	DataFlag;
	uint8_t 	DataSum;
	uint8_t 	EndTx;
}SmartSensorDataPacket;

//[0]X axix
//[1]Y axix
//[2]Z axix

typedef struct {
	float Temperature, Humidity;
  float Light;
  float Pressure;
  float Gyro[3], Acc[3], Mag[3]; 
  u16 MIC_PDM;
  float Attitude[3];
  float Rotation[3];
}SensorData;


typedef union {
	char ch[4];
	float f;
} conv_t;
#define CAtoF(trg, conv, data, i) do {\
	conv.ch[0] = data[i];		\
	conv.ch[1] = data[i+1]; \
	conv.ch[2] = data[i+2]; \
	conv.ch[3] = data[i+3]; \
	trg = conv.f;						\
} while(0);

#endif /*SMARTSENSOR_H*/

