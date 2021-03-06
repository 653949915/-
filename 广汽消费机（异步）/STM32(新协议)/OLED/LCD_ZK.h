//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途

//
//  文 件 名   : LCD_ZK.H
//  版 本 号   : v2.0
//  作    者   :
//  生成日期   : 2014-0101
//  最近修改   : 
//  功能描述   : 字库版 OLED SPI接口演示例程(STM32系列)
//              说明: 
//              ------------------------以下为OLED显示所用到的接�----------------------------------------
//              GND    电源地
//              VCC  接5V或3.3v电源
//              D0   PA2（CLK）
//              D1   PA3（DIN）
//              RES  PA4
//              DC   PA5
//              CS   PA1                
//              --------------------------以上为OLED显示所用到的接口--------------------------------------
//              ------------------------以下为OLED字库部分所用到的接�----------------------------------------
//              OUT   PB10	SPI	
//              IN  	PB11
//              SCK   PB9
//              CS2   PB7                
//              --------------------------以上为OLED字库部分所用到的接口--------------------------------------
// 修改历史   :
// 日    期   : 


//******************************************************************************/
//#include "sys.h"
#define _LCD_ZK_H_
#ifdef _LCD_ZK_H_




/*LCD 12864*/
#define RS_H GPIO_SetBits(GPIOE,GPIO_Pin_9) //RS=1   4PIN
#define RS_L GPIO_ResetBits(GPIOE,GPIO_Pin_9) //RS=0

#define RW_H GPIO_SetBits(GPIOE,GPIO_Pin_8) //RW=1    5PIN
#define RW_L GPIO_ResetBits(GPIOE,GPIO_Pin_8);  //RW = 0

#define EN_H GPIO_SetBits(GPIOE,GPIO_Pin_7);    //EN = 1   6PIN
#define EN_L GPIO_ResetBits(GPIOE,GPIO_Pin_7);  //EN = 0

//#define RST_H GPIO_SetBits(GPIOE,GPIO_Pin_10);    //EN = 1   6PIN
//#define RST_L GPIO_ResetBits(GPIOE,GPIO_Pin_10);  //EN = 0




/* the macro definition to trigger the led on or off 
 * 1 - off
 - 0 - on
 */
//#define ON  0
//#define OFF 1

//带参宏，可以像内联函数一样使用
#define lcd_cs1(a)	if (a)	\
					GPIO_SetBits(GPIOE,GPIO_Pin_7);\
					else		\
					GPIO_ResetBits(GPIOE,GPIO_Pin_7)

#define lcd_rs(a)	if (a)	\
					GPIO_SetBits(GPIOE,GPIO_Pin_8);\
					else		\
					GPIO_ResetBits(GPIOE,GPIO_Pin_8)

#define lcd_reset(a)	if (a)	\
					GPIO_SetBits(GPIOE,GPIO_Pin_9);\
					else		\
					GPIO_ResetBits(GPIOE,GPIO_Pin_9)

#define lcd_sid(a)	if (a)	\
					GPIO_SetBits(GPIOE,GPIO_Pin_10);\
					else		\
					GPIO_ResetBits(GPIOE,GPIO_Pin_10)

#define lcd_sclk(a)	if (a)	\
					GPIO_SetBits(GPIOE,GPIO_Pin_11);\
					else		\
					GPIO_ResetBits(GPIOE,GPIO_Pin_11)
					
			/************ 字库   *************/		
					
#define Rom_CS(a)	if (a)	\
					GPIO_SetBits(GPIOE,GPIO_Pin_13);\
					else		\
					GPIO_ResetBits(GPIOE,GPIO_Pin_13)

#define Rom_SCK(a)	if (a)	\
					GPIO_SetBits(GPIOE,GPIO_Pin_12);\
					else		\
					GPIO_ResetBits(GPIOE,GPIO_Pin_12)

#define Rom_OUT(a)	if (a)	\
					GPIO_SetBits(GPIOE,GPIO_Pin_15);\
					else		\
					GPIO_ResetBits(GPIOE,GPIO_Pin_15)

#define Rom_IN(a)	if (a)	\
					GPIO_SetBits(GPIOE,GPIO_Pin_14);\
					else		\
					GPIO_ResetBits(GPIOE,GPIO_Pin_14)

#define ROM_OUT    GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_15)

extern unsigned char const bmp1[];
extern unsigned char const jiong1[];
extern unsigned char const lei1[];
extern unsigned char  NUMBER[11][16];
extern unsigned char  SMALLNUMBER[12][12];
void display_graphic_12x12(unsigned int page,unsigned char column,unsigned char *dp);			
					
/*写指令到LCD模块*/
void transfer_command_lcd(int data1);   
/*写数据到LCD模块*/
void transfer_data_lcd(int data1);
/*延时*/
void delay(int n_ms);               
/*LCD模块初始化*/
void OLED_Init(void);
void lcd_address(unsigned char page,unsigned char column);
/*全屏清屏*/
void clear_screen(void);
/*显示128x64点阵图像*/
void display_128x64(const unsigned char *dp);
/*显示132x64点阵图像*/
//void display_132x64(unsigned char *dp);
/*显示16x16点阵图像、汉字、生僻字或16x16点阵的其他图标*/
void display_graphic_16x16(unsigned int page,unsigned int column,const unsigned char *dp);
/*显示8x16点阵图像、ASCII, 或8x16点阵的自造字符、其他图标*/
void display_graphic_8x16(unsigned int page,unsigned char column,unsigned char *dp);
/*显示5*7点阵图像、ASCII, 或5x7点阵的自造字符、其他图标*/
void display_graphic_5x7(unsigned int page,unsigned char column,unsigned char *dp);
/****送指令到晶联讯字库IC***/
void send_command_to_ROM( unsigned char datu );
/****从晶联讯字库IC中取汉字或字符数据（1个字节）***/
static unsigned char get_data_from_ROM(void);
/*从相关地址（addrHigh：地址高字节,addrMid：地址中字节,addrLow：地址低字节）中连续读出DataLen个字节的数据到 pBuff的地址*/
/*连续读取*/
void get_n_bytes_data_from_ROM(unsigned char addrHigh,unsigned char addrMid,unsigned char addrLow,unsigned char *pBuff,unsigned char DataLen );
/******************************************************************/
void display_GB2312_string(unsigned char y,unsigned char x,unsigned char *text);
void display_string_5x7(unsigned char y,unsigned char x,unsigned char *text);


void OLED_GPIO_Config(void);

#endif
