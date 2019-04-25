//========================================================================
// �ļ���:  LCD_Dis.c
//========================================================================
#include "LCD_Config.h"

#include "head.h"


//#include "stm32f10x_lib.h"


void TimeDelay(unsigned int Timers)
{
	unsigned int i;
	while(Timers)
	{
		Timers--;
		for(i=0;i<1000;i++);
	}
}

void Delay_40US()   //��� 0us
{
    unsigned char a,b;
    for(b=1;b>0;b--)
        for(a=10;a>0;a--);
}

//========================================================================
// ����: void delay2(unsigned char i)
// ����: ��ʱ����
//		delay2(0):��ʱ518us 518-2*256=6
//����delay2(1):��ʱ7us
//����delay2(10):��ʱ25us 25-20=5
//����delay2(20):��ʱ45us 45-40=5
//����delay2(100):��ʱ205us 205-200=5
//����delay2(200):��ʱ405us 405-400=5
//========================================================================
void delay2(unsigned int i)
{	
	unsigned int j;
	while(--i)
	{
   		for(j=0;j<1;j++);
	}
} 

unsigned char GetKey(void)
{
	/*
	if(key1==0)
	{
			TimeDelay(100);	  //������
			if(key1==0)	  //ȷ�ϰ���������
			{
				while(!key1);//���ּ��
				return 1;
			}
	}
	*/
	return 0;
}

void LedON(unsigned char on)
{
	if(on)
	{
			;//LED = 1;
	}
	else
	{
			;//LED = 0;
	}
}


void LCD_Config(void)
{
// SPI_InitTypeDef  SPI_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;

 /*PC4-A0*/
// GPIO_SetBits(GPIOC, GPIO_Pin_12);//Ԥ��Ϊ��
	
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOE, &GPIO_InitStructure);
 
}






//========================================================================
// ����: void LCD_Init(void)
// ����: LCD��ʼ��������Ҫ��������ɶ˿ڳ�ʼ���Լ�LCDģ��ĸ�λ
//========================================================================
void LCD_Init(void)
{
	LCD_Ctrl_GPIO();
	LCD_Ctrl_Out();
	LCD_Ctrl_In();
	//SS��SCKԤ������Ϊ�ߵ�ƽ
	//SPI_SCK = 0;
	//SPI_CS = 0;
	SPI_SCK_CLR();
	SPI_SS_CLR();
	
	//LCD_PS = 0;//0 Serial
//	LCD_PS_CLR();//0 Serial
	//LCD ״̬��
	//LCD_RST = 0;
	LCD_RST_CLR();
	TimeDelay(500);				    	//��ʱ���10ms����
	//LCD_RST = 1;
	LCD_RST_SET();
}
//========================================================================
// ����: void SPI_SSSet(unsigned char Status)
// ����: ��SS��״̬
//========================================================================
void SPI_SSSet(unsigned char Status)
{
	if(Status)							//�ж���Ҫ��SSΪ�ͻ��Ǹߵ�ƽ��
	{
		delay2(10);//3us
		//SPI_SCK = 1;					//SCK�ø�
		SPI_SCK_SET();
		delay2(10);//3us
		//SPI_SCK = 0;					//SCK�õ�
		SPI_SCK_CLR();
		delay2(10);//3us
		//SPI_CS = 1;						//SS�øߵ�ƽ
		SPI_SS_SET();
	}
	else
	{
		//SPI_CS = 0;						//SS�õ͵�ƽ
		SPI_SS_CLR();
		delay2(10);//3us
		//SPI_SCK = 1;					//SCK�ø�
		SPI_SCK_SET();
		delay2(10);//3us
		//SPI_SCK = 0;					//SCK�õ�
		SPI_SCK_CLR();
		delay2(10);//3us
	}
}
//========================================================================
// ����: void SPI_Send(unsigned char Data)
// ����: ͨ������SPI������һ��byte��������ģ��
//========================================================================
void SPI_Send(unsigned char Data)
{
	unsigned char i=0;
	for(i=0;i<8;i++)
	{
		
		if(Data&0x80)
			//SPI_SDA = 1;							//SDA�ø�
			SPI_SDA_SET();
		else 
			//SPI_SDA = 0;						//SDA�õ�
			SPI_SDA_CLR();
		//SPI_SCK = 1;								//SCK�ø�
		SPI_SCK_SET();
		delay2(10);//2us
		//SPI_SCK = 0;								//SCK�õ�
		SPI_SCK_CLR();
		delay2(10);//2us
		Data = Data<<1;							//��������һλ
	}
}


//========================================================================
// ����: void PutString(unsigned int x,unsigned int y,unsigned char *p,unsigned char type)
// ����: ��x��yΪ��ʼ���괦д��һ����׼ASCII�ַ���
//========================================================================
void PutString(unsigned int x,unsigned int y,unsigned char *p)
{
	//��ʾASCII�ַ���
	SPI_SSSet(1);															//SS�øߵ�ƽ	
	SPI_Send(SYN_BYTE);//CMD
	SPI_Send(CMD_ASC_DISPLAY);								//����ָ��ASC_STR_DISPLAY
	SPI_Send(SYN_BYTE|0X01);//DATA
	SPI_Send((unsigned char)(x>>8));					//Ҫ��ʾ�ַ������Ͻǵ�X��λ��
	SPI_Send((unsigned char)x);
	SPI_Send((unsigned char)(y>>8));					//Ҫ��ʾ�ַ������Ͻǵ�Y��λ��
	SPI_Send((unsigned char)y);
	
	while(*p!=0)
	{
		SPI_Send(*p);														//Ҫ��ʾ���ַ�������
		p++;
	}
	SPI_SSSet(0);															//��ɲ�����SS�͵�ƽ
}

//========================================================================
// ����: void PutString_cn(unsigned int x,unsigned int y,unsigned char *p,unsigned char type)
// ����: ��x��yΪ��ʼ���괦д��һ�������ַ���
//========================================================================
void PutString_cn(unsigned int x,unsigned int y,unsigned char *p)
{
	SPI_SSSet(1);															//SS�øߵ�ƽ	
	SPI_Send(SYN_BYTE);//CMD
	SPI_Send(CMD_HZ_DISPLAY);		
	SPI_Send(SYN_BYTE|0X01);//DATA							//����ָ��HZ_STR_DISPLAY
	SPI_Send((unsigned char)(x>>8));					//Ҫ��ʾ�ַ������Ͻǵ�X��λ��
	SPI_Send((unsigned char)x);
	SPI_Send((unsigned char)(y>>8));					//Ҫ��ʾ�ַ������Ͻǵ�Y��λ��
	SPI_Send((unsigned char)y);
	while(*p!=0)
	{
		SPI_Send(*(p++));
		SPI_Send(*(p++));
	}
	SPI_SSSet(0);															//��ɲ�����SS�͵�ƽ
}


//========================================================================
// ����: void ClrScreen(void)
// ����: ����������ִ��ȫ��Ļ���
//========================================================================
void ClrScreen(void)
{
	//��������
	SPI_SSSet(1);												//SS�øߵ�ƽ
	SPI_Send(SYN_BYTE);//CMD
	SPI_Send(CMD_CLEAR_SCREEN	);				//��ָ��CLEAR_SCREEN
	SPI_SSSet(0);												//��ɲ�����SS�͵�ƽ
}

//========================================================================
// ����: void SetBG_Color(unsigned int BGColor)
// ����: ���ñ���ɫ
//========================================================================
void SetBG_Color(unsigned int BGColor)
{
	
	SPI_SSSet(1);														//SS�øߵ�ƽ
	SPI_Send(SYN_BYTE);//CMD
	SPI_Send(CMD_SET_BG_COLOR);									//��ָ��SET_BG_COLOR
	SPI_Send(SYN_BYTE|0X01);//DATA
	SPI_Send((unsigned char)(BGColor>>8));  //����ɫ��16bit RGB565
	SPI_Send((unsigned char)BGColor);
	SPI_SSSet(0);														//��ɲ�����SS�͵�ƽ
}

//========================================================================
// ����: SetFG_Color(unsigned int FGColor)
// ����: ����ǰ��ɫ
//========================================================================
void SetFG_Color(unsigned int FGColor)
{
	SPI_SSSet(1);														//SS�øߵ�ƽ
	SPI_Send(SYN_BYTE);//CMD
	SPI_Send(CMD_SET_FG_COLOR);									//��ָ��SET_FG_COLOR
	SPI_Send(SYN_BYTE|0X01);//DATA
	SPI_Send((unsigned char)(FGColor>>8));	//ǰ��ɫ��16bit RGB565
	SPI_Send((unsigned char)FGColor);
	SPI_SSSet(0);														//��ɲ�����SS�͵�ƽ
}
//========================================================================
// ����: void PutBitmap(unsigned int x,unsigned int y,unsigned long p)
// ����: ��SetWindows ����window Ϊ������ʾ��ɫλͼ
//========================================================================
void PutBitmap(unsigned char *p,unsigned long length)
{
	unsigned long temp=0;
	SPI_SSSet(1);														//SS�øߵ�ƽ
	SPI_Send(SYN_BYTE);//CMD
	SPI_Send(CMD_WR_MEMSTART);							//��ָ��CMD_WR_MEMSTART
	SPI_Send(SYN_BYTE|0X01);//DATA
	while(temp<length)
	{
	
		SPI_Send(*(p++));
		SPI_Send(*(p++));
		temp+=2;
	
	}
	SPI_SSSet(0);													//��ɲ�����SS�͵�ƽ
}


//========================================================================
// ����: void SetDisplayOnOff(unsigned char OnOff)
// ����: lcd ��ʾ����
//========================================================================
void SetDisplayOnOff(unsigned char OnOff) 
{
	SPI_SSSet(1);														//SS�øߵ�ƽ	
	SPI_Send(SYN_BYTE);//CMD
	if(OnOff)
		SPI_Send(CMD_SET_DISPLAY_ON);					//����ָ��CMD_SET_DISPLAY_ON
	else
		SPI_Send(CMD_SET_DISPLAY_OFF);				//����ָ��CMD_SET_DISPLAY_OFF
	SPI_SSSet(0);														//��ɲ�����SS�͵�ƽ
}

//========================================================================
// ����: void SetDisplayInvert(unsigned char flag)
// ����: �ַ���ʾ����ɫ����
//========================================================================
void SetDisplayInvert(unsigned char flag) 
{
	SPI_SSSet(1);													//SS�øߵ�ƽ	
	SPI_Send(SYN_BYTE);//CMD
	if(flag)
		SPI_Send(CMD_SET_DISPLAY_INVERT);					//����ָ��CMD_SET_DISPLAY_INVERT
	else
		SPI_Send(CMD_SET_DISPLAY_NO_INVERT);
	SPI_SSSet(0);													//��ɲ�����SS�͵�ƽ
}

//========================================================================
// ����: void SetWindows()
// ����: lcd ��ʾ��������
//========================================================================
void SetWindows(unsigned int ColStartAddr,unsigned int RowStartAddr,unsigned int Width,unsigned int Height)
{
	SPI_SSSet(1);																//SS�øߵ�ƽ	
	SPI_Send(SYN_BYTE);//CMD
	SPI_Send(CMD_SET_WINDOW);											//����ָ��CMD_SET_WINDOW
	SPI_Send(SYN_BYTE|0X01);//DATA
	SPI_Send((unsigned char)(ColStartAddr>>8));		//���X������
	SPI_Send((unsigned char)ColStartAddr);
	SPI_Send((unsigned char)(RowStartAddr>>8));		//���Y������
	SPI_Send((unsigned char)RowStartAddr);
	SPI_Send((unsigned char)(Width>>8));					//window ���
	SPI_Send((unsigned char)Width);
	SPI_Send((unsigned char)(Height>>8));					//window �߶�
	SPI_Send((unsigned char)Height);
	SPI_SSSet(0);																	//��ɲ�����SS�͵�ƽ
}

//========================================================================
// ����: void SetFontType(void)
// ����: �ֿ�ѡ������
//========================================================================
void SetFontType(unsigned char FontType)
{
	
	SPI_SSSet(1);									//SS�øߵ�ƽ	
	SPI_Send(SYN_BYTE);//CMD
	SPI_Send(CMD_SET_FONT_TYPE);					//����ָ��CMD_SET_FONT_TYPE
	SPI_Send(SYN_BYTE|0X01);//DATA
	SPI_Send(FontType);
	SPI_SSSet(0);
	
}

//========================================================================
// ����: void DrawPoint(void)
// ����: ָ�����껭��
//========================================================================
void DrawPoint(unsigned int ColStartAddr,unsigned int RowStartAddr,unsigned int wcolor)
{
	SPI_SSSet(1);																//SS�øߵ�ƽ
	SPI_Send(SYN_BYTE);//CMD
	SPI_Send(CMD_DRAW_POINT);										//����ָ�� CMD_DRAW_POINT
	SPI_Send(SYN_BYTE|0X01);//DATA
	SPI_Send((unsigned char)(ColStartAddr>>8));
	SPI_Send((unsigned char)ColStartAddr);
	SPI_Send((unsigned char)(RowStartAddr>>8));
	SPI_Send((unsigned char)RowStartAddr);
	SPI_Send((unsigned char)(wcolor>>8));
	SPI_Send((unsigned char)wcolor);
	SPI_SSSet(0);																//��ɲ�����SS�͵�ƽ
}

//========================================================================
// ����: void DrawLine(void)
// ����: ָ�����껭��
//========================================================================
void DrawLine(unsigned int ColStartAddr,unsigned int RowStartAddr,unsigned int ColEndAddr,unsigned int RowEndAddr,unsigned int wcolor)
{
	SPI_SSSet(1);																//SS�øߵ�ƽ
	SPI_Send(SYN_BYTE);//CMD
	SPI_Send(CMD_DRAW_LINE);										//����ָ�� CMD_DRAW_LINE
	SPI_Send(SYN_BYTE|0X01);//DATA
	SPI_Send((unsigned char)(ColStartAddr>>8));
	SPI_Send((unsigned char)ColStartAddr);
	SPI_Send((unsigned char)(RowStartAddr>>8));
	SPI_Send((unsigned char)RowStartAddr);
	SPI_Send((unsigned char)(ColEndAddr>>8));
	SPI_Send((unsigned char)ColEndAddr);
	SPI_Send((unsigned char)(RowEndAddr>>8));
	SPI_Send((unsigned char)RowEndAddr);
	SPI_Send((unsigned char)(wcolor>>8));
	SPI_Send((unsigned char)wcolor);
	SPI_SSSet(0);																//��ɲ�����SS�͵�ƽ
}

//========================================================================
// ����: void DrawLine(void)
// ����: ָ�����껭����

 /*
    ColStartAddr  ����ʼ��ַ
    RowStartAddr  ����ʼ��ַ

    ColEndAddr   �н�����ַ
    RowStartAddr �н�����ַ
    wcolor       ��ɫ
    Transparent  ͸��
*/   

//========================================================================
void  DrawRect(unsigned int ColStartAddr,unsigned int RowStartAddr,unsigned int ColEndAddr,unsigned int RowEndAddr,unsigned int wcolor,unsigned char fTransparent)
{
	SPI_SSSet(1);																//SS�øߵ�ƽ
	SPI_Send(SYN_BYTE);//CMD
	SPI_Send(CMD_DRAW_RECT);										//����ָ�� CMD_DRAW_RECT
	SPI_Send(SYN_BYTE|0X01);//DATA
	SPI_Send((unsigned char)(ColStartAddr>>8));
	SPI_Send((unsigned char)ColStartAddr);
	SPI_Send((unsigned char)(RowStartAddr>>8));
	SPI_Send((unsigned char)RowStartAddr);
	SPI_Send((unsigned char)(ColEndAddr>>8));
	SPI_Send((unsigned char)ColEndAddr);
	SPI_Send((unsigned char)(RowEndAddr>>8));
	SPI_Send((unsigned char)RowEndAddr);
	SPI_Send(fTransparent);
	SPI_Send((unsigned char)(wcolor>>8));
	SPI_Send((unsigned char)wcolor);
	SPI_SSSet(0);																//��ɲ�����SS�͵�ƽ
}

//========================================================================
// ����: void DrawIcon(void)
// ����: ָ�����껭ͼƬ
//========================================================================
void DrawIcon(unsigned int ColStartAddr,unsigned int RowStartAddr,unsigned char IconNo)
{
	SPI_SSSet(1);																//SS�øߵ�ƽ
	SPI_Send(SYN_BYTE);//CMD
	SPI_Send(CMD_DRAW_ICON);										//����ָ�� CMD_DRAW_ICON
	SPI_Send(SYN_BYTE|0X01);//DATA
	SPI_Send((unsigned char)(ColStartAddr>>8));
	SPI_Send((unsigned char)ColStartAddr);
	SPI_Send((unsigned char)(RowStartAddr>>8));
	SPI_Send((unsigned char)RowStartAddr);
	SPI_Send(IconNo);
	SPI_SSSet(0);																//��ɲ�����SS�͵�ƽ
}


void DrawTranIcon(unsigned int ColStartAddr,unsigned int RowStartAddr,unsigned char IconNo,unsigned int color)
{
	SPI_SSSet(1);																//SS�øߵ�ƽ
	SPI_Send(SYN_BYTE);//CMD
	SPI_Send(CMD_DRAW_TRAN_ICON);										//����ָ�� CMD_DRAW_ICON
	SPI_Send(SYN_BYTE|0X01);//DATA
	SPI_Send((unsigned char)(ColStartAddr>>8));
	SPI_Send((unsigned char)ColStartAddr);
	SPI_Send((unsigned char)(RowStartAddr>>8));
	SPI_Send((unsigned char)RowStartAddr);
	SPI_Send(IconNo);
	SPI_Send((unsigned char)(color>>8));
	SPI_Send((unsigned char)color);
	SPI_SSSet(0);																//��ɲ�����SS�͵�ƽ
}

//========================================================================
// ����: DrawQRCODE(unsigned int x,unsigned int y,unsigned char size,unsigned char *p)
// ����: ��x��yΪ��ʼ���괦����̬��ά��
//========================================================================
void DrawQRCODE(unsigned int x,unsigned int y,unsigned char size,unsigned char *p)
{
	//��ʾ��̬��ά��
	SPI_SSSet(1);															//SS�øߵ�ƽ	
	SPI_Send(SYN_BYTE);//CMD
	SPI_Send(CMD_DRAW_QRCODE);								//����ָ��CMD_DRAW_QRCODE
	SPI_Send(SYN_BYTE|0X01);//DATA
	SPI_Send((unsigned char)(x>>8));					//Ҫ��ʾ�ַ������Ͻǵ�X��λ��
	SPI_Send((unsigned char)x);
	SPI_Send((unsigned char)(y>>8));					//Ҫ��ʾ�ַ������Ͻǵ�Y��λ��
	SPI_Send((unsigned char)y);
	SPI_Send(size);
	
	while(*p!=0)
	{
		SPI_Send(*p);														//Ҫ��ʾ���ַ�������
		p++;
	}
	SPI_SSSet(0);															//��ɲ�����SS�͵�ƽ
}










