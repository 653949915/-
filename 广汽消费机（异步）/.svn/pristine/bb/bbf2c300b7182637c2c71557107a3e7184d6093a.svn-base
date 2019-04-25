#ifndef __USART_H
#define __USART_H
#include "stdio.h"	
#include "sys.h" 
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途

//串口1初始化		   

#define USART_REC_LEN  			530  	//定义最大接收字节数 200
#define EN_USART1_RX 			1		//使能（1）/禁止（0）串口1接收
	  	
extern u8  USART1_RX_CRLF;       //UART2接收 \r\n  标记

extern u16 USART_RX_STA;         		//接收状态标记	
//如果想串口中断接收，请不要注释以下宏定义
void uart_init(u32 bound);
void uart2_init(u32 bound);
void uart3_init(u32 bound);

#ifdef   WISDOM_PLATE     //是智盘
void uart4_init(u32 bound);
#endif	
#endif


