#include "sys.h"		    
 
#include "delay.h"
#include "head.h"
//////////////////////////////////////////////////////////////////////////////////	 

//////////////////////////////////////////////////////////////////////////////////
									 
//初始化IO

void  RS485_Init(void)
{  
  GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);//使能GPIOA时钟
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;				 //PA1端口配置
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOA, &GPIO_InitStructure);
 
  RS485_TX_EN=0;			//默认为接收模式
 
}

//RS485发送len个字节.
//buf:发送区首地址
//len:发送的字节数(为了和本代码的接收匹配,这里建议不要超过64个字节)
void  RS485_Send_Data(uint8_t *buf,	uint16_t len)
{
	uint16_t t;
	RS485_TX_EN=1;			//设置为发送模式
  	for(t=0;t<len;t++)		//循环发送数据
	{	
	  USART_SendData(RS485_UART,buf[t]);		
		while(USART_GetFlagStatus(RS485_UART, USART_FLAG_TC) == RESET);	  
	
	}	 
 
//	while(USART_GetFlagStatus(RS485_UART, USART_FLAG_TC) == RESET);		
	  
	RS485_TX_EN=0;				//设置为接收模式	
}

//
//combuff:需要发送的字符
//
void  RS485_Send_One_Data(u8 combuff_485)
{

	RS485_TX_EN=1;			//设置为发送模式	
	
	USART_SendData(RS485_UART, combuff_485);//向串口1发送数据
	
	while(USART_GetFlagStatus(RS485_UART,USART_FLAG_TC)!=SET);//等待发送结束
	  
	RS485_TX_EN=0;				//设置为接收模式	
}




















