#include "Optocoupler.h"

//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途

//光耦输入驱动代码	   

//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	   

//初始化PC6.7.8为输出口.并使能这个口的时钟		    
//LED IO初始化
void OPTOCOUPLER_Init(void)
{
 
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);	 //使能PC端口时钟
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8;				     //光耦123-->PC.6.78 端口配置
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		                       //推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		                       //IO口速度为50MHz
 GPIO_Init(GPIOC, &GPIO_InitStructure);					                             //根据设定参数初始化GPIOA.8
 GPIO_SetBits(GPIOC,GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8);						           //PC.6.7.8   输出高
	 	
}
 

















