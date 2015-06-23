																																	  /*
 * V_GUI.c
 *
 *  Created on: 2012年3月23日
 *      Author: power
 */

#include "V_GUI.h"
#include "font.h"
//#include "font.c"
extern unsigned short int DISPLAY_RAM[16][10] ;


/*──────────────────────────────────────────────────────────────────────────────
函數名稱：LCD_WriteLine
功能描述：在指定座標畫直線
輸    入：	x0	= A點行座標
		y0	= A點列座標
		x1	= B點行座標
		y1	= B點列座標
		color	= 線顏色
輸    出：None
返    回：None
──────────────────────────────────────────────────────────────────────────────*/
void V_GUI_WriteLine(unsigned short int x0, unsigned short int y0, unsigned short int x1, unsigned short int y1,unsigned short int Color)
{
 	unsigned short int x,y;
 	unsigned short int dx;// = abs(x1 - x0);
 	unsigned short int dy;// = abs(y1 - y0);

	if(y0 == y1)
	{
		if(x0 <= x1)
		{
			x = x0;
		}
		else
		{
			x	= x1;
			x1	= x0;
		}
  		while(x <= x1)
  		{
   			V_GUI_WriteDot(x, y0, Color);
   			x ++;
  		}
  		return;
	}
	else if(y0 > y1)
	{
		dy = y0 - y1;
	}
	else
	{
		dy = y1 - y0;
	}
 
 	if(x0 == x1)
	{
		if(y0 <= y1)
		{
			y = y0;
		}
		else
		{
			y	= y1;
			y1	= y0;
		}
  		while(y <= y1)
  		{
   			V_GUI_WriteDot(x0, y, Color);
   			y ++;
  		}
  		return;
	}
	else if(x0 > x1)
 	{
		dx	= x0 - x1;
  		x	= x1;
  		x1	= x0;
  		y	= y1;
  		y1	= y0;
 	}
 	else
 	{
		dx=x1-x0;
  		x = x0;
  		y = y0;
 	}

 	if(dx == dy)
 	{
  		while(x <= x1)
  		{

   			x ++;
			if(y > y1)
			{
				y --;
			}
			else
			{
   				y ++;
			}
   			V_GUI_WriteDot(x, y, Color);
  		}
 	}
 	else
 	{
 		V_GUI_WriteDot(x, y, Color);
  		if(y < y1)
  		{
   			if(dx > dy)
   			{
    			s16 p = dy * 2 - dx;
    			s16 twoDy = 2 * dy;
    			s16 twoDyMinusDx = 2 * (dy - dx);
    			while(x < x1)
    			{
     				x ++;
     				if(p < 0)
     				{
      					p += twoDy;
     				}
     				else
     				{
      					y ++;
      					p += twoDyMinusDx;
     				}
     				V_GUI_WriteDot(x, y,Color);
    			}
   			}
   			else
   			{
    			s16 p = dx * 2 - dy;
    			s16 twoDx = 2 * dx;
    			s16 twoDxMinusDy = 2 * (dx - dy);
    			while(y < y1)
    			{
     				y ++;
     				if(p < 0)
     				{
      					p += twoDx;
     				}
     				else
     				{
      					x ++;
      					p += twoDxMinusDy;
     				}
     				V_GUI_WriteDot(x, y, Color);
    			}
   			}
  		}
  		else
  		{
   			if(dx > dy)
   			{
    			s16 p = dy * 2 - dx;
    			s16 twoDy = 2 * dy;
	    		s16 twoDyMinusDx = 2 * (dy - dx);
    			while(x < x1)
    			{
     				x ++;
     				if(p < 0)
	     			{
    	  				p += twoDy;
     				}
     				else
     				{
      					y --;
	      				p += twoDyMinusDx;
    	 			}
     				V_GUI_WriteDot(x, y,Color);
    			}
   			}
	   		else
   			{
    			s16 p = dx * 2 - dy;
    			s16 twoDx = 2 * dx;
	    		s16 twoDxMinusDy = 2 * (dx - dy);
    			while(y1 < y)
    			{
     				y --;
     				if(p < 0)
	     			{
    	  				p += twoDx;
     				}
     				else
     				{
      					x ++;
	      				p += twoDxMinusDy;
    	 			}
     				V_GUI_WriteDot(x, y,Color);
    			}
   			}
  		}
 	}
}


/*──────────────────────────────────────────────────────────────────────────────
函數名稱：LCD_WriteCircle
功能描述：在指定座標畫圓，可填充
輸    入：	cx	= 圓心的 'X' 座標
		cy	= 圓心的 'Y' 座標
		r	= 圓的半徑
		Color= 線顏色
		Fill	= 填充選擇
輸    出：None
返    回：None
──────────────────────────────────────────────────────────────────────────────*/
void V_GUI_WriteCircle(unsigned short int cx,unsigned short int cy,unsigned short int r,unsigned short int Color,unsigned char Fill)
{
	unsigned short int x,y;
	s16 delta,tmp;
	x = 0;
	y = r;
	delta = 3 - (r << 1);

	while(y > x)
	{
		if(Fill)
		{
			V_GUI_WriteLine(cx + x, cy + y, cx - x, cy + y, Color);
			V_GUI_WriteLine(cx + x, cy - y, cx - x, cy - y, Color);
			V_GUI_WriteLine(cx + y, cy + x, cx - y, cy + x, Color);
			V_GUI_WriteLine(cx + y, cy - x, cx - y, cy - x, Color);
		}
		else
		{
			V_GUI_WriteDot(cx + x, cy + y, Color);
			V_GUI_WriteDot(cx - x, cy + y, Color);
			V_GUI_WriteDot(cx + x, cy - y, Color);
			V_GUI_WriteDot(cx - x, cy - y, Color);
			V_GUI_WriteDot(cx + y, cy + x, Color);
			V_GUI_WriteDot(cx - y, cy + x, Color);
			V_GUI_WriteDot(cx + y, cy - x, Color);
			V_GUI_WriteDot(cx - y, cy - x, Color);
		}
		x ++;
		if(delta >= 0)
		{
			y --;
			tmp = (x << 2);
			tmp -=(y << 2);
			delta +=(tmp);
		}
		else
		{
			delta +=((x << 2) + 1);
		}
	}
}


/*──────────────────────────────────────────────────────────────────────────────
函數名稱：LCD_WriteRectangle
功能描述：在指定區域畫矩形，可填充顏色
輸    入：	x0	= A點行座標
		y0	= A點列座標
		x1	= B點行座標
		y1	= B點列座標
		color	= 線顏色
		Fill	= 填充選擇
輸    出：None
返    回：None
──────────────────────────────────────────────────────────────────────────────*/
void V_GUI_WriteRectangle(unsigned short int x0, unsigned short int y0, unsigned short int x1, unsigned short int y1,unsigned short int Color,unsigned char Fill)
{
	if(Fill)
	{
		unsigned short int i;
		if(x0 > x1)
		{
			i = x1;
			x1= x0;
		}
		else
		{
			i = x0;
		}
		for(;i <= x1; i ++)
		{
			V_GUI_WriteLine(i, y0, i, y1, Color);
		}
		return;
	}
	V_GUI_WriteLine(x0, y0, x0, y1, Color);
	V_GUI_WriteLine(x0, y1, x1, y1, Color);
	V_GUI_WriteLine(x1, y1, x1, y0, Color);
	V_GUI_WriteLine(x1, y0, x0, y0, Color);
}


/*──────────────────────────────────────────────────────────────────────────────
函數名稱：LCD_WriteSquare
功能描述：在指定區域畫正方形，可填充顏色
輸    入：	x0	= A點行座標
		y0	= A點列座標
		with	= 邊長
		color	= 線顏色
		Fill	= 填充選擇
輸    出：None
返    回：None
──────────────────────────────────────────────────────────────────────────────*/
void V_GUI_WriteSquare(unsigned short int x0, unsigned short int y0, unsigned short int with, unsigned short int Color,unsigned char Fill)
{
	V_GUI_WriteRectangle(x0, y0, x0 + with, y0 + with, Color, Fill);
}

/*──────────────────────────────────────────────────────────────────────────────
函數名稱：LCD_WriteByteWord
功能描述：顯示一個 8*16 字元
輸    入：	Xpos 	= X開始座標
		Ypos 	= Y開始座標
		Back_SW 	= 背景控制
		Color 	= 字元顏色
		ASCII	= ASCII字元
輸    出：None
返    回：None
──────────────────────────────────────────────────────────────────────────────*/
void V_GUI_WriteByteWord(unsigned char Xpos, unsigned short int Ypos, unsigned char Back_SW, unsigned short int Color, unsigned char ASCII)
{
	unsigned char Ascii_Data, Number, Number_2;
	for(Number = 0; Number < 16; Number ++)
	{//ASCII_8_16
		//Ascii_Data = AsciiLib[((ASCII - 32) * 16) + Number];
		Ascii_Data = ASCII_8_16[((ASCII - 32) * 16) + Number];
		for(Number_2 = 0; Number_2 < 8; Number_2 ++)
		{
			if ((Ascii_Data & (0x80 >> Number_2)) != 0)
			{						 
				V_GUI_WriteDot(Xpos + Number_2, Ypos + Number, Color);
			}	else if (Back_SW)
				{
					V_GUI_WriteDot(Xpos + Number_2, Ypos + Number, !Color);
				}
		}
	}
}



/*──────────────────────────────────────────────────────────────────────────────
函數名稱：LCD_Write16_24ASCII
功能描述：顯示一個 16*24 字元
輸    入：	Xpos 	= X開始座標
		Ypos 	= Y開始座標
		Back_SW 	= 背景控制
		Color 	= 字元顏色
		ASCII	= ASCII字元
輸    出：None
返    回：None
──────────────────────────────────────────────────────────────────────────────*/
void V_GUI_Write16_24ASCII(unsigned char Xpos, unsigned short int Ypos, unsigned char Back_SW, unsigned short int Color, unsigned char ASCII)
{
	unsigned char Number, Number_2;
	unsigned short int Ascii_Data;
	for(Number = 0; Number < 24; Number ++)
	{
		Ascii_Data = ASCII_Table[((ASCII - 32) * 24) + Number];
		for(Number_2 = 0; Number_2 < 16; Number_2 ++)
		{
			if ((Ascii_Data & (0x01 << Number_2)) != 0)
			{						 
				V_GUI_WriteDot(Xpos + Number_2, Ypos + Number, Color);
			}	else if (Back_SW)
				{
					V_GUI_WriteDot(Xpos + Number_2, Ypos + Number, !Color);
				}
		}
	}
}



/*──────────────────────────────────────────────────────────────────────────────
函數名稱：FindHzCode
功能描述：查找漢字引導碼
輸    入：*HzASCII = 中文字元
輸    出：None
返    回："Number" = 引導碼
──────────────────────────────────────────────────────────────────────────────*/
unsigned short int FindHzCode(unsigned char *HzASCII)
{
	unsigned short int Number = 0;
    HZTypeDef *ptGb16 = (HZTypeDef *)BIG5HZ_16;
	while(ptGb16[Number].QuWeiCode[0] > 0x80)
	{
		//── 查找漢字引導碼 ──
		if ((*HzASCII == ptGb16[Number].QuWeiCode[0]) && (*(HzASCII + 1) == ptGb16[Number].QuWeiCode[1]))
		{
			return(Number);		// 找到字元並返回引導碼!
		}
		Number ++;
		if(Number > (sizeof(BIG5HZ_16) / sizeof(HZTypeDef) - 1))//── 搜索下標約束 ─
		{              
			return(0);			// 未找到字元!
		}
	}
    return(0);					// 無此字元!
}



/*──────────────────────────────────────────────────────────────────────────────
函數名稱：LCD_Writer16_16Chiese
功能描述：顯示中文字元
輸    入：	Xpos		= X開始座標
		Ypos		= Y開始座標
		Back_SW	= 背景控制
		Color	= 字元顏色
		*HzASCII	= 中文字元
輸    出：None
返    回：None
──────────────────────────────────────────────────────────────────────────────*/
void V_GUI_Writer16_16Chiese(unsigned char Xpos, unsigned short int Ypos,unsigned char Back_SW, unsigned short int Color, unsigned char *HzASCII) 
{
	unsigned char Number = 0, Number_2;
	unsigned short int Ascii_L, Ascii_R, qUWei;							// 漢字左右半邊資料緩存！
	HZTypeDef *ptGb16 = (HZTypeDef *)BIG5HZ_16;				// 聲明並指向 "GBHZ_16"	的資料結構
	
	qUWei = FindHzCode(HzASCII);							// 獲取漢字引導碼

	for(Number = 0; Number < 16; Number ++)					// 顯示一個漢字
	{
		Ascii_L = ptGb16[qUWei].HZDotCode[Number * 2];		// 獲取漢字左邊資料
		Ascii_R = ptGb16[qUWei].HZDotCode[Number * 2 + 1];	// 獲取漢字右邊資料

		for(Number_2 = 0; Number_2 < 8; Number_2 ++)		// 顯示一行資料
		{
			if ((Ascii_L & (0x80 >> Number_2)) != 0)
			{						 
				V_GUI_WriteDot(Xpos + Number_2, Ypos + Number, Color);
			}	else if (Back_SW)							// 背景控制
				{
					V_GUI_WriteDot(Xpos + Number_2, Ypos + Number, !Color);
				}
			if ((Ascii_R & (0x80 >> Number_2)) != 0)
			{
				V_GUI_WriteDot(Xpos + 8 + Number_2, Ypos + Number, Color);
			}	else if (Back_SW)							// 背景控制
				{
					V_GUI_WriteDot(Xpos + 8 + Number_2, Ypos + Number, !Color);
				}			
		}
	}
}



/*──────────────────────────────────────────────────────────────────────────────
函數名稱：V_GUI_WriteString
功能描述：顯示一串字元，支援中英文混合顯示！
輸    入：	Xpos		= X開始座標
		Ypos		= Y開始座標
		Back_SW	= 背景控制
		Color	= 字元顏色
		*STRing	= 待顯示的字串
輸    出：None
返    回：None
──────────────────────────────────────────────────────────────────────────────*/
void V_GUI_WriteString(unsigned char Xpos, unsigned short int Ypos, unsigned char Back_SW, unsigned short int COLOR, unsigned char *STRing)
{
	unsigned char Number_X = Xpos;
	unsigned short int Temp_Y = Ypos;
	while(*STRing)
	{
		if (*STRing < 0x80)		//判斷為非中文
		{	
      //if(Number_X<127)			
			  V_GUI_WriteByteWord(Number_X, Temp_Y, Back_SW, COLOR, *STRing ++);
			Number_X += 8;
			//if (Number_X > 127)//234
			{
//				Number_X = 0;
//				Temp_Y += 16;
//				if (Temp_Y > 15)
//				{
//					Temp_Y = 0;
//				}
			}
		}	else				//判斷為中文
			{
        //if(Number_X<127)			
				V_GUI_Writer16_16Chiese(Number_X, Temp_Y, Back_SW, COLOR, (unsigned char *)STRing);
				Number_X += 16;
				//if (Number_X > 127)//232
				{
//					Number_X = 0;
//					Temp_Y += 16;
//					if (Temp_Y >15)
//					{
//						Temp_Y = 0;
//					}
				}
				*STRing ++;
				*STRing ++;
			}
	}
}
void led_phrase_leftmove(int loop)
{
	unsigned char i,m,n;
	unsigned short int bit,bitn;
	unsigned char nbch=NBWord;
	long int v,w;
	
	while(loop)
	{	
	  for(i=0;i<128;i++)
	  {
			for(m=0;m<16;m++)
			{
			  bitn=DISPLAY_RAM[m][0]&0x8000;
				bitn>>=15;
				
				bit=DISPLAY_RAM[m][1]&0x8000;
				bit>>=15;
				for(n=0;n<nbch-1;n++)
				{
			    DISPLAY_RAM[m][n] <<= 1;
					DISPLAY_RAM[m][n] |= bit;
					if(n<=nbch-3)
					{
				   bit=DISPLAY_RAM[m][n+2]&0x8000;
				   bit>>=15;					
					}
				}
			  DISPLAY_RAM[m][nbch-1] <<= 1;
				DISPLAY_RAM[m][nbch-1] |=  bitn;				
			}
		  for(v=0;v<12;v++)
		    for(w=0;w<32767;w++);
		}
		loop--;
  }
}
void led_phrase_rightmove(int loop )
{
	unsigned char i,m,n;
	unsigned short int bit,bitn;
	unsigned char nbch=NBWord;
	long int v,w;
	
	while(loop)
	{	
	  for(i=0;i<128;i++)
	  {
			for(m=0;m<16;m++)
			{
        bitn=DISPLAY_RAM[m][nbch-1]&0x0001;
				bitn<<=15;
				
				for(n=0;n<nbch;n++)
				{
				  bit=DISPLAY_RAM[m][n]&0x0001;
				  bit<<=15;
				  DISPLAY_RAM[m][n] >>= 1;
					DISPLAY_RAM[m][n] |=bitn;
					bitn=bit;
				}								
			}
		  for(v=0;v<12;v++)
		    for(w=0;w<32767;w++);
		}
		loop--;
  }
}
void led_phrase_up(int loop )
{
	unsigned char i,m,n;
	unsigned short int bit,bitn;
	unsigned char nbch=NBWord;
	long int v,w;
	unsigned short int BUF[NBWord];
	while(loop)
	{	
	  for(i=0;i<16;i++)
	  {
			for(n=0;n<NBWord;n++)
			{
				BUF[n]=DISPLAY_RAM[0][n];
			}			
			for(m=0;m<15;m++)
			{
			  for(n=0;n<NBWord;n++)
			  {
				  DISPLAY_RAM[m][n]=DISPLAY_RAM[m+1][n];        
				}								
			}
			for(n=0;n<NBWord;n++)
			{
				DISPLAY_RAM[15][n]=BUF[n];
			}		
			
		  for(v=0;v<12;v++)
		    for(w=0;w<32767;w++);
		}
		loop--;
  }
}
void led_phrase_down(int loop )
{	
	unsigned char i,m,n;
	unsigned short int bit,bitn;
	unsigned char nbch=NBWord;
	long int v,w;
	unsigned short int BUF[NBWord];
	while(loop)
	{	
	  for(i=0;i<16;i++)
	  {
			for(n=0;n<NBWord;n++)
			{
				BUF[n]=DISPLAY_RAM[15][n];
			}					
			for(m=0;m<15;m++)
			{
			  for(n=0;n<NBWord;n++)
			  {
				  DISPLAY_RAM[15-m][n]=DISPLAY_RAM[(15-m)-1][n];        
				}								
			}
			for(n=0;n<NBWord;n++)
			{
				DISPLAY_RAM[0][n]=BUF[n];
			}		
			
		  for(v=0;v<12;v++)
		    for(w=0;w<32767;w++);
		}
		loop--;
  } 	
}
void twinkling(int loop )
{
	unsigned char i,m,n;
	unsigned short int bit,bitn;
	unsigned char nbch=NBWord;
	long int v,w;
	unsigned short int BUF[NBWord];
	while(loop)
	{	
			for(m=1;m<15;m++)
			{
			  for(n=0;n<NBWord;n++)
			  {
				  DISPLAY_RAM[m][n]=~DISPLAY_RAM[m][n];        
				}								
			}			
		  for(v=0;v<300;v++)
		    for(w=0;w<32767;w++);
			for(m=1;m<15;m++)
			{
			  for(n=0;n<NBWord;n++)
			  {
				  DISPLAY_RAM[m][n]=~DISPLAY_RAM[m][n];        
				}								
			}			
		  for(v=0;v<300;v++)
		    for(w=0;w<32767;w++);
		loop--;
  } 
}



