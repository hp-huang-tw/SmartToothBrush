																																	  /*
 * V_GUI.c
 *
 *  Created on: 2012�~3��23��
 *      Author: power
 */

#include "V_GUI.h"
#include "font.h"
//#include "font.c"
extern unsigned short int DISPLAY_RAM[16][10] ;


/*�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w
��ƦW�١GLCD_WriteLine
�\��y�z�G�b���w�y�еe���u
��    �J�G	x0	= A�I��y��
		y0	= A�I�C�y��
		x1	= B�I��y��
		y1	= B�I�C�y��
		color	= �u�C��
��    �X�GNone
��    �^�GNone
�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w*/
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


/*�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w
��ƦW�١GLCD_WriteCircle
�\��y�z�G�b���w�y�еe��A�i��R
��    �J�G	cx	= ��ߪ� 'X' �y��
		cy	= ��ߪ� 'Y' �y��
		r	= �ꪺ�b�|
		Color= �u�C��
		Fill	= ��R���
��    �X�GNone
��    �^�GNone
�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w*/
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


/*�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w
��ƦW�١GLCD_WriteRectangle
�\��y�z�G�b���w�ϰ�e�x�ΡA�i��R�C��
��    �J�G	x0	= A�I��y��
		y0	= A�I�C�y��
		x1	= B�I��y��
		y1	= B�I�C�y��
		color	= �u�C��
		Fill	= ��R���
��    �X�GNone
��    �^�GNone
�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w*/
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


/*�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w
��ƦW�١GLCD_WriteSquare
�\��y�z�G�b���w�ϰ�e����ΡA�i��R�C��
��    �J�G	x0	= A�I��y��
		y0	= A�I�C�y��
		with	= ���
		color	= �u�C��
		Fill	= ��R���
��    �X�GNone
��    �^�GNone
�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w*/
void V_GUI_WriteSquare(unsigned short int x0, unsigned short int y0, unsigned short int with, unsigned short int Color,unsigned char Fill)
{
	V_GUI_WriteRectangle(x0, y0, x0 + with, y0 + with, Color, Fill);
}

/*�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w
��ƦW�١GLCD_WriteByteWord
�\��y�z�G��ܤ@�� 8*16 �r��
��    �J�G	Xpos 	= X�}�l�y��
		Ypos 	= Y�}�l�y��
		Back_SW 	= �I������
		Color 	= �r���C��
		ASCII	= ASCII�r��
��    �X�GNone
��    �^�GNone
�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w*/
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



/*�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w
��ƦW�١GLCD_Write16_24ASCII
�\��y�z�G��ܤ@�� 16*24 �r��
��    �J�G	Xpos 	= X�}�l�y��
		Ypos 	= Y�}�l�y��
		Back_SW 	= �I������
		Color 	= �r���C��
		ASCII	= ASCII�r��
��    �X�GNone
��    �^�GNone
�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w*/
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



/*�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w
��ƦW�١GFindHzCode
�\��y�z�G�d��~�r�޾ɽX
��    �J�G*HzASCII = ����r��
��    �X�GNone
��    �^�G"Number" = �޾ɽX
�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w*/
unsigned short int FindHzCode(unsigned char *HzASCII)
{
	unsigned short int Number = 0;
    HZTypeDef *ptGb16 = (HZTypeDef *)BIG5HZ_16;
	while(ptGb16[Number].QuWeiCode[0] > 0x80)
	{
		//�w�w �d��~�r�޾ɽX �w�w
		if ((*HzASCII == ptGb16[Number].QuWeiCode[0]) && (*(HzASCII + 1) == ptGb16[Number].QuWeiCode[1]))
		{
			return(Number);		// ���r���ê�^�޾ɽX!
		}
		Number ++;
		if(Number > (sizeof(BIG5HZ_16) / sizeof(HZTypeDef) - 1))//�w�w �j���U�Ь��� �w
		{              
			return(0);			// �����r��!
		}
	}
    return(0);					// �L���r��!
}



/*�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w
��ƦW�١GLCD_Writer16_16Chiese
�\��y�z�G��ܤ���r��
��    �J�G	Xpos		= X�}�l�y��
		Ypos		= Y�}�l�y��
		Back_SW	= �I������
		Color	= �r���C��
		*HzASCII	= ����r��
��    �X�GNone
��    �^�GNone
�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w*/
void V_GUI_Writer16_16Chiese(unsigned char Xpos, unsigned short int Ypos,unsigned char Back_SW, unsigned short int Color, unsigned char *HzASCII) 
{
	unsigned char Number = 0, Number_2;
	unsigned short int Ascii_L, Ascii_R, qUWei;							// �~�r���k�b���ƽw�s�I
	HZTypeDef *ptGb16 = (HZTypeDef *)BIG5HZ_16;				// �n���ë��V "GBHZ_16"	����Ƶ��c
	
	qUWei = FindHzCode(HzASCII);							// ����~�r�޾ɽX

	for(Number = 0; Number < 16; Number ++)					// ��ܤ@�Ӻ~�r
	{
		Ascii_L = ptGb16[qUWei].HZDotCode[Number * 2];		// ����~�r������
		Ascii_R = ptGb16[qUWei].HZDotCode[Number * 2 + 1];	// ����~�r�k����

		for(Number_2 = 0; Number_2 < 8; Number_2 ++)		// ��ܤ@����
		{
			if ((Ascii_L & (0x80 >> Number_2)) != 0)
			{						 
				V_GUI_WriteDot(Xpos + Number_2, Ypos + Number, Color);
			}	else if (Back_SW)							// �I������
				{
					V_GUI_WriteDot(Xpos + Number_2, Ypos + Number, !Color);
				}
			if ((Ascii_R & (0x80 >> Number_2)) != 0)
			{
				V_GUI_WriteDot(Xpos + 8 + Number_2, Ypos + Number, Color);
			}	else if (Back_SW)							// �I������
				{
					V_GUI_WriteDot(Xpos + 8 + Number_2, Ypos + Number, !Color);
				}			
		}
	}
}



/*�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w
��ƦW�١GV_GUI_WriteString
�\��y�z�G��ܤ@��r���A�䴩���^��V�X��ܡI
��    �J�G	Xpos		= X�}�l�y��
		Ypos		= Y�}�l�y��
		Back_SW	= �I������
		Color	= �r���C��
		*STRing	= ����ܪ��r��
��    �X�GNone
��    �^�GNone
�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w*/
void V_GUI_WriteString(unsigned char Xpos, unsigned short int Ypos, unsigned char Back_SW, unsigned short int COLOR, unsigned char *STRing)
{
	unsigned char Number_X = Xpos;
	unsigned short int Temp_Y = Ypos;
	while(*STRing)
	{
		if (*STRing < 0x80)		//�P�_���D����
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
		}	else				//�P�_������
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



