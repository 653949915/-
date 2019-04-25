#include "relay.h"

//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途

//LED驱动代码	   

//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	   

//初始化PD.4为输出口.并使能这个口的时钟		    
//继电器 IO初始化
void RELAY_Init(void)
{
 
 GPIO_InitTypeDef  GPIO_InitStructure;
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOD/*|RCC_APB2Periph_AFIO*/, ENABLE);	 //使能PD端口时钟 和重定义 端口时钟
	
// GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable,ENABLE);                         //PA15重定义使能
// GPIO_PinRemapConfig(GPIO_Remap_SWJ_NoJTRST,ENABLE);
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;				     //Relay-->PD.4 端口配置
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
 GPIO_Init(GPIOD, &GPIO_InitStructure);					       //根据设定参数初始化GPIOD.4
 GPIO_SetBits(GPIOD,GPIO_Pin_4);						           //PD.4 输出高 关闭继电器
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;				     //Relay-->PA.15 端口配置
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
 GPIO_Init(GPIOB, &GPIO_InitStructure);					       //根据设定参数初始化GPIOA.15
 GPIO_SetBits(GPIOB,GPIO_Pin_6);						           //PA.15 输出高 关闭继电器
 	
}
 

















