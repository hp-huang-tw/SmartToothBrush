//
//  main.c
//  gracet C
//
//  Created by stitchmos on 2015/6/1.
//  Copyright (c) 2015? WMLAB @NCU. All rights reserved.
//
#include "stdio.h"
#include "math.h"
#include "stm32f4xx.h"
#include "hw_config.h"
#include "smartsensor.h"
#include "tm_stm32f4_ili9341.h"


#define _CONVT_FLOAT_  // if convert the raw data to float

extern char TimeOutFlag;
extern SensorData SData;

typedef struct Grafcet{
	int x0;
	int x1;
	int x2;
	int x3;
	int x4;
	int x5;
	int x6;
	
	int R0;
	int R1;
	int R2;
	int R3_4;
	int R5;
	int R6;
	
	int x50;
	int x51;
	int R50;
	
	int count;


}GG;


void grafcet_G0(GG*);
void action_G0(GG*);
void initial_G0(GG*);

void grafcet_G1_2(GG*);
void runBrushTooth(GG*);
void transmitData(GG*);

void grafcet_G3(GG*);
void getSmartSensorValue(GG*);

void grafcet_G4(GG*);
void showResult(GG*);

void grafcet_G5(GG*);
void goSubGrafcet_G50(GG*);
void action_G50(GG*);

void grafcet_G50(GG*);
void initial_G5(GG*);

void grafcet_G51(GG*);
void getGesture(GG*);

void grafcet_G6(GG*);
void turnoff(void);

char cc[3];
int tmp = 100;
char c[20]= "Temperature=";

char s;
int i;
char RxBuffer[200];  
char U_direction[20]= "BRUSH_UP    ";
char D_direction[20]= "BRUSH_DOWN  ";
char N_direction[20]= "BRUSH_NORMAL";

//初始位置
float initial_x=0,initial_y=0,initial_z=0;
float x=0, y=0, z=0;
int tmpx, tmpy, tmpz;
char L_direction[20]= "BRUSH_LEFT ";
char R_direction[20]= "BRUSH_RIGHT";

//左0右1
int flag_LR=0;	
int count = 0;
bool flag_temp;
bool flag_acc;
bool flag_mag;

int main(void) {
	// insert code here...
	GG G;
	G.x0 = 1;
	G.x1 = 0;
	G.x2 = 0;
	G.x3 = 0;
	G.x4 = 0;
	G.x5 = 0;
	G.x6 = 0;
	
	G.R0 = 0;
	G.R1 = 0;
	G.R2 = 0;
	G.R3_4 = 0;
	G.x50 = 0;
	G.x51 = 0;
	
	G.R5 = 0;
	G.R50 = 0;
	G.R6 = 0;
	
	while(1){
		grafcet_G0(&G);
	}
	
}


void grafcet_G0(GG *G){
	
	if(G->x0 == 1 && G->R0 == 1) grafcet_G1_2(G);
	
	//平行運作
	if(G->x1 == 1 && G->R1 == 1) grafcet_G3(G);
	if(G->x2 == 1 && G->R2 == 1) grafcet_G4(G);

	//合併
	if(G->x3 == 1 && G->x4 == 1 && G->R3_4 == 1)
		grafcet_G5(G);
	
	if(G->x5 == 1 ){
		//繼續抓資料, G1_2()
		if (G->R5 == 1) grafcet_G1_2(G);
		//結束, G6()
		else if(G->R6 ==1) grafcet_G6(G);
	}
	
	action_G0(G);
}

void action_G0(GG *G){
	if(G->x0 == 1) initial_G0(G);
	if(G->x1 == 1) runBrushTooth(G);
	if(G->x2 == 1) transmitData(G);
	if(G->x3 == 1) getSmartSensorValue(G);
	if(G->x4 == 1) showResult(G);
	if(G->x5 == 1) goSubGrafcet_G50(G);
	if(G->x6 == 1) turnoff();
}

void initial_G0(GG *G){
	hw_config();
	/* Initialize LCD */
	TM_ILI9341_Init();
	/* Fill LCD with gray color */
	TM_ILI9341_Fill(ILI9341_COLOR_GRAY);
	/* Select orientation */
	TM_ILI9341_Rotate(TM_ILI9341_Orientation_Landscape_1);
	/* Initialize Touch */
	TM_ILI9341_DrawRectangle(30,30,50,50,ILI9341_COLOR_BLACK);

	G->R0 = 1;
}

//goSubGrafcet_G50
void goSubGrafcet_G50(GG *G){
	//第一次進入G50, active G->x50
	if(G->x50 == 0 && G->x51 == 0) grafcet_G50(G);
	if(G->x50 == 1 && G->R50 == 1) grafcet_G51(G);
	action_G50(G);
}

//action_G50
void action_G50(GG *G){
	if(G->x50 == 1) initial_G5(G);
	if(G->x51 == 1) getGesture(G);
}

void grafcet_G1_2(GG *G){
	G->x0 = 0;
	G->x1 = 1;
	G->x2 = 1;
	if (G->x5 == 1) G->x5 = 0;
}

void runBrushTooth(GG *G){
	count++;
	flag_temp = FALSE;
	flag_acc = FALSE;
	flag_mag = FALSE;

	TimerStart();
	TimerReset();
	while(TimeOutFlag==0);

	SmartSensorCMD_TX("AT");
	if(SmartSensorCMD_RX(RxBuffer))

	//Enable 溫度計
	SmartSensorCMD_TX("AT+TEMP,E");
	if(SmartSensorCMD_RX(RxBuffer))
	
	//Enable 加速度計   
	SmartSensorCMD_TX("AT+ACC,E");
	if(SmartSensorCMD_RX(RxBuffer))
	  
	//Enable 磁力計
	SmartSensorCMD_TX("AT+MAG,E");
	if(SmartSensorCMD_RX(RxBuffer))

	G->R5 = 0;
	G->R0 = 0;
	G->R1 = 1;
};

void grafcet_2(GG *G){
	G->x0 = 0;
	G->x1 = 1;
	G->x2 = 1;
}

void transmitData(GG *G){
  G->R0 = 0;
  G->R2 = 1;
}

void grafcet_G3(GG *G){
  G->x1 = 0;
  G->x3 = 1;
}

void getSmartSensorValue(GG *G){
  
  //提取溫度計之感測數值
  SmartSensorCMD_TX("AT+TEMP");
  if(SmartSensorCMD_RX(RxBuffer)){    
		#ifdef _CONVT_FLOAT_
			if(DeSmartSensorPacketData(RxBuffer)){
				flag_temp = TRUE;
			}
		#endif
  }
  
  //提取加速度計之感測數值
  SmartSensorCMD_TX("AT+ACC");
  if(SmartSensorCMD_RX(RxBuffer)){       
		#ifdef _CONVT_FLOAT_
			if(DeSmartSensorPacketData(RxBuffer)){
				flag_acc = TRUE;
			}
		#endif
  }
  
  //提取磁力計之感測數值
  SmartSensorCMD_TX("AT+MAG");
  if(SmartSensorCMD_RX(RxBuffer)){     
		#ifdef _CONVT_FLOAT_
			if(DeSmartSensorPacketData(RxBuffer)){
				flag_mag = TRUE;
			}
		#endif
  }

  G->R1 = 0;
  
};

void grafcet_G4(GG *G){
	G->x2 = 0;
	G->x4 = 1;
}

//Show result on PC
void showResult(GG *G){
	printf("\rTemperature=%.3f C \n",SData.Temperature);  
	printf("\rACCx=%.3f, ACCy=%.3f, ACCz=%.3f mg\n",SData.Acc[0],SData.Acc[1],SData.Acc[2]); 
	printf("\rMAGx=%.3f, MAGy=%.3f, MAGz=%.3f mGa\n",SData.Mag[0],SData.Mag[1],SData.Mag[2]); 
	
	G->R2 = 0;
	G->R3_4 = 1;
};

void grafcet_G5(GG *G){
	G->x3 = 0;
	G->x4 = 0;
	G->x5 = 1;
}

void grafcet_G50(GG *G){
	G->x50 = 1;
}

void initial_G5(GG *G){

	//紀錄磁力計初始位置
	if(initial_x==0 && initial_y==0 && initial_z==0 && count == 2){
		initial_x = SData.Mag[0];
		initial_y = SData.Mag[1];
		initial_z = SData.Mag[2];
		TM_ILI9341_Puts(10, 10, "Start!!", &TM_Font_11x18, ILI9341_COLOR_RED, ILI9341_COLOR_BLACK);         
	}
	
	//更新位置
	x = SData.Mag[0];
	y = SData.Mag[1];
	z = SData.Mag[2];

	G->R3_4 = 0;
	G->R50 = 1;

};

void grafcet_G51(GG *G){
	G->x50 = 0;
	G->x51 = 1;
}

//判斷刷牙手勢&顯示結果於LCD
void getGesture(GG *G){
	
	//顯示溫度
	if(flag_temp){
		s = (int)(SData.Temperature)/10 % 10 + '0';
		c[12] = s;
		s = (int)(SData.Temperature) % 10 + '0';
		c[13] = s;
		TM_ILI9341_Puts(10, 70,  c, &TM_Font_11x18, ILI9341_COLOR_RED, ILI9341_COLOR_BLACK);
		flag_temp = FALSE;
	}
	
	//判斷牙刷上下正常方向, 並顯示於LCD
	if(flag_acc){
		if(SData.Acc[2] > 800)
			TM_ILI9341_Puts(10, 40,  U_direction, &TM_Font_11x18, ILI9341_COLOR_YELLOW, ILI9341_COLOR_BLACK);
		else if(SData.Acc[2] < -800)
			TM_ILI9341_Puts(10, 40,  D_direction, &TM_Font_11x18, ILI9341_COLOR_YELLOW, ILI9341_COLOR_BLACK);
		else
			TM_ILI9341_Puts(10, 40,  N_direction, &TM_Font_11x18, ILI9341_COLOR_YELLOW, ILI9341_COLOR_BLACK);
		flag_acc = FALSE;
	}
	
	//判斷牙刷左右方向, 並顯示於LCD
	if(flag_mag){
		if( count > 2) {
			tmpx  = initial_x-SData.Mag[0];
			tmpy  = initial_y-SData.Mag[1];
			
			if( fabs(tmpx) > 150 && fabs(tmpy) > 85)
				TM_ILI9341_Puts(10, 10,  R_direction, &TM_Font_11x18, ILI9341_COLOR_RED, ILI9341_COLOR_BLACK);
			else
				TM_ILI9341_Puts(10, 10,  L_direction, &TM_Font_11x18, ILI9341_COLOR_RED, ILI9341_COLOR_BLACK);
		}
		flag_mag = FALSE;
	}

	G->x51 = 0;
	G->R50 = 0;
	G->R5 = 1;

};

void grafcet_G6(GG *G){
	G->x5 = 0;
	G->x6 = 1;
}

void turnoff(void){
	printf("Bye! \n");
}
