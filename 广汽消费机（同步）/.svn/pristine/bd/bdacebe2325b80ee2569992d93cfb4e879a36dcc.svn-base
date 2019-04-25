#include "led.h"

//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途

//LED驱动代码	   

//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	   

//初始化PB5和PE5为输出口.并使能这两个口的时钟		    
//LED IO初始化
void LED_Init(void)
{
 
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);	             //使能PB,PE端口时钟
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;		 //LED0.1.2-->PD.5.6.7 端口配置
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		               //推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		               //IO口速度为50MHz
 GPIO_Init(GPIOD, &GPIO_InitStructure);					                     //根据设定参数初始化GPIOD
 GPIO_ResetBits(GPIOD,GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7);						 //PD.5.6.7 输出低


}
 
