#ifndef _TM1650_H_
#define _TM1650_H_
//#include "stm32f10x.h"
#include "sys.h"
//设置接口的 pin
#define TM16_RCC        RCC_APB2Periph_GPIOD			//RCC
#define TM16_PORT       GPIOD					//PORT
#define TM16_SDA        GPIO_Pin_0			//SDA
#define TM16_SCL        GPIO_Pin_1			//SCL
#define TM16_ReadSDA() 	GPIO_ReadInputDataBit(TM16_PORT,TM16_SDA)		//读取SDA

#define TM16_SDA_H GPIO_SetBits(TM16_PORT,TM16_SDA)
#define TM16_SDA_L GPIO_ResetBits(TM16_PORT,TM16_SDA)
#define TM16_SCL_H GPIO_SetBits(TM16_PORT,TM16_SCL)
#define TM16_SCL_L GPIO_ResetBits(TM16_PORT,TM16_SCL)

#define TM16_delay(x)    {delay_us(x);} //  {dtmelay(x);}		//设置延时函数,方便移植，可修改为自己的延时函数

void TM16_INIT(unsigned char brig);		//初始化TM1650,  参数为亮度 0-7
void TM16_Display(unsigned char data,unsigned char di);//显示函数，data为显示的数据，0-99，di设置是否显示小数点，0为都不显示小数点，1为第一位显示小数点，2为第二位显示小数点，3为第一位和第二位都显示小数点

//***********读按键命令*************************************
unsigned char TM1650_FD650_READ(void );

uint8_t  tmKeyscan(void);

#endif
