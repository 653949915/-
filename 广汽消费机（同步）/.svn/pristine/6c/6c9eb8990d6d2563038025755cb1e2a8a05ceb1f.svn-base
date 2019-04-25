#ifndef __RS485_H
#define __RS485_H			 
#include "sys.h"	 								  
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途

//RS485驱动 代码	   

//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////
	  		  	
#define RS485_UART		USART2	//定义485的串口.

//模式控制
#define RS485_TX_EN		PAout(1)	//485模式控制.0,接收;1,发送.


void  RS485_Init(void);
void  RS485_Send_Data(uint8_t *buf,uint16_t len);
void  RS485_Send_One_Data(u8 combuff);


#endif	   
















