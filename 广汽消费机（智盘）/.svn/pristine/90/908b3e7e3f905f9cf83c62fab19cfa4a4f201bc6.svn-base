#include "sysrest.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途

//蜂鸣器驱动代码	   

//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	   

//初始化PC15为输入口.并使能这个口的时钟		    
//系统参数恢复出厂设置按键初始化
void SYSREST_KEY_Init(void)
{
 
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);	 //使能GPIOD端口时钟
 
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;				       //SYSREST-->PC.15 端口配置
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		       //上拉输入
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	     //速度为50MHz
 GPIO_Init(GPIOB, &GPIO_InitStructure);	                 //根据参数初始化GPIOC.15
 
 GPIO_SetBits(GPIOB,GPIO_Pin_1);                       //输入0，复位键不按下

}
