//========================================================================
// 文件名:  LCD_Dis.c
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

void Delay_40US()   //误差 0us
{
    unsigned char a,b;
    for(b=1;b>0;b--)
        for(a=10;a>0;a--);
}

//========================================================================
// 函数: void delay2(unsigned char i)
// 描述: 延时函数
//		delay2(0):延时518us 518-2*256=6
//　　delay2(1):延时7us
//　　delay2(10):延时25us 25-20=5
//　　delay2(20):延时45us 45-40=5
//　　delay2(100):延时205us 205-200=5
//　　delay2(200):延时405us 405-400=5
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
			TimeDelay(100);	  //消抖动
			if(key1==0)	  //确认按键被按下
			{
				while(!key1);//松手检测
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
// GPIO_SetBits(GPIOC, GPIO_Pin_12);//预置为高
	
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOE, &GPIO_InitStructure);
 
}






//========================================================================
// 函数: void LCD_Init(void)
// 描述: LCD初始化程序，主要在里面完成端口初始化以及LCD模块的复位
//========================================================================
void LCD_Init(void)
{
	LCD_Ctrl_GPIO();
	LCD_Ctrl_Out();
	LCD_Ctrl_In();
	//SS和SCK预先设置为高电平
	//SPI_SCK = 0;
	//SPI_CS = 0;
	SPI_SCK_CLR();
	SPI_SS_CLR();
	
	//LCD_PS = 0;//0 Serial
//	LCD_PS_CLR();//0 Serial
	//LCD 状态脚
	//LCD_RST = 0;
	LCD_RST_CLR();
	TimeDelay(500);				    	//延时大概10ms左右
	//LCD_RST = 1;
	LCD_RST_SET();
}
//========================================================================
// 函数: void SPI_SSSet(unsigned char Status)
// 描述: 置SS线状态
//========================================================================
void SPI_SSSet(unsigned char Status)
{
	if(Status)							//判断是要置SS为低还是高电平？
	{
		delay2(10);//3us
		//SPI_SCK = 1;					//SCK置高
		SPI_SCK_SET();
		delay2(10);//3us
		//SPI_SCK = 0;					//SCK置低
		SPI_SCK_CLR();
		delay2(10);//3us
		//SPI_CS = 1;						//SS置高电平
		SPI_SS_SET();
	}
	else
	{
		//SPI_CS = 0;						//SS置低电平
		SPI_SS_CLR();
		delay2(10);//3us
		//SPI_SCK = 1;					//SCK置高
		SPI_SCK_SET();
		delay2(10);//3us
		//SPI_SCK = 0;					//SCK置低
		SPI_SCK_CLR();
		delay2(10);//3us
	}
}
//========================================================================
// 函数: void SPI_Send(unsigned char Data)
// 描述: 通过串行SPI口输送一个byte的数据置模组
//========================================================================
void SPI_Send(unsigned char Data)
{
	unsigned char i=0;
	for(i=0;i<8;i++)
	{
		
		if(Data&0x80)
			//SPI_SDA = 1;							//SDA置高
			SPI_SDA_SET();
		else 
			//SPI_SDA = 0;						//SDA置低
			SPI_SDA_CLR();
		//SPI_SCK = 1;								//SCK置高
		SPI_SCK_SET();
		delay2(10);//2us
		//SPI_SCK = 0;								//SCK置低
		SPI_SCK_CLR();
		delay2(10);//2us
		Data = Data<<1;							//数据左移一位
	}
}


//========================================================================
// 函数: void PutString(unsigned int x,unsigned int y,unsigned char *p,unsigned char type)
// 描述: 在x、y为起始坐标处写入一串标准ASCII字符串
//========================================================================
void PutString(unsigned int x,unsigned int y,unsigned char *p)
{
	//显示ASCII字符串
	SPI_SSSet(1);															//SS置高电平	
	SPI_Send(SYN_BYTE);//CMD
	SPI_Send(CMD_ASC_DISPLAY);								//传送指令ASC_STR_DISPLAY
	SPI_Send(SYN_BYTE|0X01);//DATA
	SPI_Send((unsigned char)(x>>8));					//要显示字符的左上角的X轴位置
	SPI_Send((unsigned char)x);
	SPI_Send((unsigned char)(y>>8));					//要显示字符的左上角的Y轴位置
	SPI_Send((unsigned char)y);
	
	while(*p!=0)
	{
		SPI_Send(*p);														//要显示的字符串数据
		p++;
	}
	SPI_SSSet(0);															//完成操作置SS低电平
}

//========================================================================
// 函数: void PutString_cn(unsigned int x,unsigned int y,unsigned char *p,unsigned char type)
// 描述: 在x、y为起始坐标处写入一串汉字字符串
//========================================================================
void PutString_cn(unsigned int x,unsigned int y,unsigned char *p)
{
	SPI_SSSet(1);															//SS置高电平	
	SPI_Send(SYN_BYTE);//CMD
	SPI_Send(CMD_HZ_DISPLAY);		
	SPI_Send(SYN_BYTE|0X01);//DATA							//传送指令HZ_STR_DISPLAY
	SPI_Send((unsigned char)(x>>8));					//要显示字符的左上角的X轴位置
	SPI_Send((unsigned char)x);
	SPI_Send((unsigned char)(y>>8));					//要显示字符的左上角的Y轴位置
	SPI_Send((unsigned char)y);
	while(*p!=0)
	{
		SPI_Send(*(p++));
		SPI_Send(*(p++));
	}
	SPI_SSSet(0);															//完成操作置SS低电平
}


//========================================================================
// 函数: void ClrScreen(void)
// 描述: 清屏函数，执行全屏幕清除
//========================================================================
void ClrScreen(void)
{
	//清屏操作
	SPI_SSSet(1);												//SS置高电平
	SPI_Send(SYN_BYTE);//CMD
	SPI_Send(CMD_CLEAR_SCREEN	);				//送指令CLEAR_SCREEN
	SPI_SSSet(0);												//完成操作置SS低电平
}

//========================================================================
// 函数: void SetBG_Color(unsigned int BGColor)
// 描述: 设置背景色
//========================================================================
void SetBG_Color(unsigned int BGColor)
{
	
	SPI_SSSet(1);														//SS置高电平
	SPI_Send(SYN_BYTE);//CMD
	SPI_Send(CMD_SET_BG_COLOR);									//送指令SET_BG_COLOR
	SPI_Send(SYN_BYTE|0X01);//DATA
	SPI_Send((unsigned char)(BGColor>>8));  //背景色，16bit RGB565
	SPI_Send((unsigned char)BGColor);
	SPI_SSSet(0);														//完成操作置SS低电平
}

//========================================================================
// 函数: SetFG_Color(unsigned int FGColor)
// 描述: 设置前景色
//========================================================================
void SetFG_Color(unsigned int FGColor)
{
	SPI_SSSet(1);														//SS置高电平
	SPI_Send(SYN_BYTE);//CMD
	SPI_Send(CMD_SET_FG_COLOR);									//送指令SET_FG_COLOR
	SPI_Send(SYN_BYTE|0X01);//DATA
	SPI_Send((unsigned char)(FGColor>>8));	//前景色，16bit RGB565
	SPI_Send((unsigned char)FGColor);
	SPI_SSSet(0);														//完成操作置SS低电平
}
//========================================================================
// 函数: void PutBitmap(unsigned int x,unsigned int y,unsigned long p)
// 描述: 在SetWindows 后，以window 为区域显示彩色位图
//========================================================================
void PutBitmap(unsigned char *p,unsigned long length)
{
	unsigned long temp=0;
	SPI_SSSet(1);														//SS置高电平
	SPI_Send(SYN_BYTE);//CMD
	SPI_Send(CMD_WR_MEMSTART);							//送指令CMD_WR_MEMSTART
	SPI_Send(SYN_BYTE|0X01);//DATA
	while(temp<length)
	{
	
		SPI_Send(*(p++));
		SPI_Send(*(p++));
		temp+=2;
	
	}
	SPI_SSSet(0);													//完成操作置SS低电平
}


//========================================================================
// 函数: void SetDisplayOnOff(unsigned char OnOff)
// 描述: lcd 显示开关
//========================================================================
void SetDisplayOnOff(unsigned char OnOff) 
{
	SPI_SSSet(1);														//SS置高电平	
	SPI_Send(SYN_BYTE);//CMD
	if(OnOff)
		SPI_Send(CMD_SET_DISPLAY_ON);					//传送指令CMD_SET_DISPLAY_ON
	else
		SPI_Send(CMD_SET_DISPLAY_OFF);				//传送指令CMD_SET_DISPLAY_OFF
	SPI_SSSet(0);														//完成操作置SS低电平
}

//========================================================================
// 函数: void SetDisplayInvert(unsigned char flag)
// 描述: 字符显示背景色开关
//========================================================================
void SetDisplayInvert(unsigned char flag) 
{
	SPI_SSSet(1);													//SS置高电平	
	SPI_Send(SYN_BYTE);//CMD
	if(flag)
		SPI_Send(CMD_SET_DISPLAY_INVERT);					//传送指令CMD_SET_DISPLAY_INVERT
	else
		SPI_Send(CMD_SET_DISPLAY_NO_INVERT);
	SPI_SSSet(0);													//完成操作置SS低电平
}

//========================================================================
// 函数: void SetWindows()
// 描述: lcd 显示窗口设置
//========================================================================
void SetWindows(unsigned int ColStartAddr,unsigned int RowStartAddr,unsigned int Width,unsigned int Height)
{
	SPI_SSSet(1);																//SS置高电平	
	SPI_Send(SYN_BYTE);//CMD
	SPI_Send(CMD_SET_WINDOW);											//传送指令CMD_SET_WINDOW
	SPI_Send(SYN_BYTE|0X01);//DATA
	SPI_Send((unsigned char)(ColStartAddr>>8));		//起点X轴坐标
	SPI_Send((unsigned char)ColStartAddr);
	SPI_Send((unsigned char)(RowStartAddr>>8));		//起点Y轴坐标
	SPI_Send((unsigned char)RowStartAddr);
	SPI_Send((unsigned char)(Width>>8));					//window 宽度
	SPI_Send((unsigned char)Width);
	SPI_Send((unsigned char)(Height>>8));					//window 高度
	SPI_Send((unsigned char)Height);
	SPI_SSSet(0);																	//完成操作置SS低电平
}

//========================================================================
// 函数: void SetFontType(void)
// 描述: 字库选择命令
//========================================================================
void SetFontType(unsigned char FontType)
{
	
	SPI_SSSet(1);									//SS置高电平	
	SPI_Send(SYN_BYTE);//CMD
	SPI_Send(CMD_SET_FONT_TYPE);					//传送指令CMD_SET_FONT_TYPE
	SPI_Send(SYN_BYTE|0X01);//DATA
	SPI_Send(FontType);
	SPI_SSSet(0);
	
}

//========================================================================
// 函数: void DrawPoint(void)
// 描述: 指定坐标画点
//========================================================================
void DrawPoint(unsigned int ColStartAddr,unsigned int RowStartAddr,unsigned int wcolor)
{
	SPI_SSSet(1);																//SS置高电平
	SPI_Send(SYN_BYTE);//CMD
	SPI_Send(CMD_DRAW_POINT);										//传送指令 CMD_DRAW_POINT
	SPI_Send(SYN_BYTE|0X01);//DATA
	SPI_Send((unsigned char)(ColStartAddr>>8));
	SPI_Send((unsigned char)ColStartAddr);
	SPI_Send((unsigned char)(RowStartAddr>>8));
	SPI_Send((unsigned char)RowStartAddr);
	SPI_Send((unsigned char)(wcolor>>8));
	SPI_Send((unsigned char)wcolor);
	SPI_SSSet(0);																//完成操作置SS低电平
}

//========================================================================
// 函数: void DrawLine(void)
// 描述: 指定坐标画线
//========================================================================
void DrawLine(unsigned int ColStartAddr,unsigned int RowStartAddr,unsigned int ColEndAddr,unsigned int RowEndAddr,unsigned int wcolor)
{
	SPI_SSSet(1);																//SS置高电平
	SPI_Send(SYN_BYTE);//CMD
	SPI_Send(CMD_DRAW_LINE);										//传送指令 CMD_DRAW_LINE
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
	SPI_SSSet(0);																//完成操作置SS低电平
}

//========================================================================
// 函数: void DrawLine(void)
// 描述: 指定坐标画矩形

 /*
    ColStartAddr  列起始地址
    RowStartAddr  行起始地址

    ColEndAddr   列结束地址
    RowStartAddr 行结束地址
    wcolor       颜色
    Transparent  透明
*/   

//========================================================================
void  DrawRect(unsigned int ColStartAddr,unsigned int RowStartAddr,unsigned int ColEndAddr,unsigned int RowEndAddr,unsigned int wcolor,unsigned char fTransparent)
{
	SPI_SSSet(1);																//SS置高电平
	SPI_Send(SYN_BYTE);//CMD
	SPI_Send(CMD_DRAW_RECT);										//传送指令 CMD_DRAW_RECT
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
	SPI_SSSet(0);																//完成操作置SS低电平
}

//========================================================================
// 函数: void DrawIcon(void)
// 描述: 指定坐标画图片
//========================================================================
void DrawIcon(unsigned int ColStartAddr,unsigned int RowStartAddr,unsigned char IconNo)
{
	SPI_SSSet(1);																//SS置高电平
	SPI_Send(SYN_BYTE);//CMD
	SPI_Send(CMD_DRAW_ICON);										//传送指令 CMD_DRAW_ICON
	SPI_Send(SYN_BYTE|0X01);//DATA
	SPI_Send((unsigned char)(ColStartAddr>>8));
	SPI_Send((unsigned char)ColStartAddr);
	SPI_Send((unsigned char)(RowStartAddr>>8));
	SPI_Send((unsigned char)RowStartAddr);
	SPI_Send(IconNo);
	SPI_SSSet(0);																//完成操作置SS低电平
}


void DrawTranIcon(unsigned int ColStartAddr,unsigned int RowStartAddr,unsigned char IconNo,unsigned int color)
{
	SPI_SSSet(1);																//SS置高电平
	SPI_Send(SYN_BYTE);//CMD
	SPI_Send(CMD_DRAW_TRAN_ICON);										//传送指令 CMD_DRAW_ICON
	SPI_Send(SYN_BYTE|0X01);//DATA
	SPI_Send((unsigned char)(ColStartAddr>>8));
	SPI_Send((unsigned char)ColStartAddr);
	SPI_Send((unsigned char)(RowStartAddr>>8));
	SPI_Send((unsigned char)RowStartAddr);
	SPI_Send(IconNo);
	SPI_Send((unsigned char)(color>>8));
	SPI_Send((unsigned char)color);
	SPI_SSSet(0);																//完成操作置SS低电平
}

//========================================================================
// 函数: DrawQRCODE(unsigned int x,unsigned int y,unsigned char size,unsigned char *p)
// 描述: 在x、y为起始坐标处画动态二维码
//========================================================================
void DrawQRCODE(unsigned int x,unsigned int y,unsigned char size,unsigned char *p)
{
	//显示动态二维码
	SPI_SSSet(1);															//SS置高电平	
	SPI_Send(SYN_BYTE);//CMD
	SPI_Send(CMD_DRAW_QRCODE);								//传送指令CMD_DRAW_QRCODE
	SPI_Send(SYN_BYTE|0X01);//DATA
	SPI_Send((unsigned char)(x>>8));					//要显示字符的左上角的X轴位置
	SPI_Send((unsigned char)x);
	SPI_Send((unsigned char)(y>>8));					//要显示字符的左上角的Y轴位置
	SPI_Send((unsigned char)y);
	SPI_Send(size);
	
	while(*p!=0)
	{
		SPI_Send(*p);														//要显示的字符串数据
		p++;
	}
	SPI_SSSet(0);															//完成操作置SS低电平
}










