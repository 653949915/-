#ifndef	__LCD12864_H__
#define	__LCD12864_H__

#include "sys.h"

//#define KEY_SIZE 20

/**********************************************************
//外部变量声明
**********************************************************/

/* USER CODE BEGIN 0 */

	
//CS=P1^2;	    //片选信号 rs
//SID=P1^3;		//数据信号 rw
//SCLK=P1^4;		//时钟信号 e
//RST=P1^6;		//复位信号
//CH = P1^5;		//并行、串行选择信号

#define LCDSID_H   GPIOE->BSRR=GPIO_Pin_8
#define LCDSID_L   GPIOE->BRR=GPIO_Pin_8 

#define LCDCS_H    GPIOE->BSRR=GPIO_Pin_7
#define LCDCS_L    GPIOE->BRR=GPIO_Pin_7

#define LCDSCLK_H  GPIOE->BSRR=GPIO_Pin_9
#define LCDSCLK_L  GPIOE->BRR=GPIO_Pin_9

#define LCDBLA_H  GPIOE->BSRR=GPIO_Pin_11
#define LCDBLA_L  GPIOE->BRR=GPIO_Pin_11


#define x1    0x80
#define x2    0x88
#define ylcd     0x80
#define comm  0
#define dat   1
//extern u32 key;      //按键值



/**********************************************************
//外部函数声明
**********************************************************/

void Delay_Lcd(u16 us);
void Display_Img(u8 const *img);
void LCD_Write_Number(u8 s);  // 数字显示函数
void LCD_Write_String(u8 X,u8 Y,uc8  *s);
void LCD_Set_XY( u8 X, u8 Y );
void Clr_Scr(void);//清屏函数
void Send_Byte(u8 bbyte) ;
void Write_Char(u8 start, u8 ddata);
void Lcd_Init(void) ;
void Delaynms(u16 di) ;

void Lcds_Config(void);

void LCD_Write_String_NUM(u8 X,u8 Y, uc8  *s ,u8 len);



#endif
