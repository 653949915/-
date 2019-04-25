#include "sys.h"
#include "usart.h"	  
#include "head.h"
////////////////////////////////////////////////////////////////////////////////// 	 
#include  <stdio.h>
#include "stm32f10x.h"
//////////////////////////////////////////////////////////////////
//加入以下代码,支持printf函数,而不需要选择use MicroLIB	  
#if 1
#pragma import(__use_no_semihosting)             
//标准库需要的支持函数                 
struct __FILE 
{ 
	int handle; 

}; 

FILE __stdout;       
//定义_sys_exit()以避免使用半主机模式    
_sys_exit(int x) 
{ 
	x = x; 
} 
//重定义fputc函数 
int fputc(int ch, FILE *f)
{      
	while((USART2->SR&0X40)==0);//循环发送,直到发送完毕   
    USART2->DR = (u8) ch;      
	return ch;
}
#endif
//加入以下代码,支持printf函数,而不需要选择use MicroLIB	  

u8   u1_Rec_Over_Flag=0;           //接收完成标志
u8   u1_RxTimeout=100;              //串口1接收超时；   
u32  u1_Rec_Len;                   //Rec_Len为接收到的字符个数

 
#if EN_USART1_RX   //如果使能了接收
//串口1中断服务程序
 	
u16 USART_RX_STA=0;       //接收状态标记	  
	
u8  USART1_RX_CRLF=0;       //UART2接收 \r\n  标记


void uart_init(u32 bound){
  //GPIO端口设置
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);	//使能USART1，GPIOA时钟
  
	//USART1_TX   GPIOA.9
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.9
   
  //USART1_RX	  GPIOA.10初始化
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//PA10
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.10  

  //Usart1 NVIC 配置
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2 ;//抢占优先级2
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;		//子优先级0
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
  
   //USART 初始化设置

	USART_InitStructure.USART_BaudRate = bound;//串口波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式

  USART_Init(USART1, &USART_InitStructure); //初始化串口1
  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//开启串口接受中断
  USART_Cmd(USART1, ENABLE);                    //使能串口1 
	USART_GetFlagStatus(USART1, USART_FLAG_TC);   // /* 清发送成功标志*/ 句解决第1个字节无法正确发送出去的问题 

}

void uart2_init(u32 bound){
  //GPIO端口设置
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	//使能USART1，GPIOA时钟
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);	//使能USART1，GPIOA时钟
	
	//USART2_TX   GPIOA.2
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; //PA.9
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.9
   
  //USART2_RX	  GPIOA.3初始化
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;//PA10
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.10  

  //Usart2 NVIC 配置
  NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2 ;//抢占优先级2
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;		//子优先级1
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
  
   //USART 初始化设置

	USART_InitStructure.USART_BaudRate = bound;//串口波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式

  USART_Init(USART2, &USART_InitStructure); //初始化串口2
  USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//开启串口接受中断
  USART_Cmd(USART2, ENABLE);                    //使能串口2 
	USART_GetFlagStatus(USART2, USART_FLAG_TC);   // /* 清发送成功标志*/ 句解决第1个字节无法正确发送出去的问题 

}

void uart3_init(u32 bound){
  //GPIO端口设置
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);	//使能USART3
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	  //GPIOB时钟
	
	
	//USART3_TX   GPIOB.10
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; //PB.10
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
  GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIOB.10
   
  //USART3_RX	  GPIOB.11初始化
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;//PB11
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
  GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIOB.11  

  //Usart3 NVIC 配置
  NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2 ;//抢占优先级2
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;		//子优先级2
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
  
   //USART 初始化设置

	USART_InitStructure.USART_BaudRate = bound;//串口波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式

  USART_Init(USART3, &USART_InitStructure);     //初始化串口3
  USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);//开启串口接受中断
  USART_Cmd(USART3, ENABLE);                    //使能串口3 
	USART_GetFlagStatus(USART3, USART_FLAG_TC);   // /* 清发送成功标志*/ 句解决第1个字节无法正确发送出去的问题 

}

#ifdef   WISDOM_PLATE     //是智盘
void uart4_init(u32 bound){
  //GPIO端口设置
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);	//使能USART3
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);	  //GPIOB时钟
	
	
	//UART4_TX   GPIOC.10
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; //PB.10
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
  GPIO_Init(GPIOC, &GPIO_InitStructure);//初始化GPIOB.10
   
  //USART3_RX	  GPIOB.11初始化
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;//PB11
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
  GPIO_Init(GPIOC, &GPIO_InitStructure);//初始化GPIOB.11  

  //Usart3 NVIC 配置
  NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2 ;//抢占优先级2
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//子优先级2
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
  
   //USART 初始化设置

	USART_InitStructure.USART_BaudRate = bound;//串口波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式

  USART_Init(UART4, &USART_InitStructure);     //初始化串口4
  USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);//开启串口接受中断
  USART_Cmd(UART4, ENABLE);                    //使能串口4 
	USART_GetFlagStatus(UART4, USART_FLAG_TC);   // /* 清发送成功标志*/ 句解决第1个字节无法正确发送出去的问题 

}
#endif	


//combuff:接收缓存首地址
//comidx:读到的数据长度

void USART1_IRQHandler(void)       //串口接收中断，并将接收到得数据发送出
{
 u8 comtmp;
	
 if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)//判断 是否 接收中断  
   { 
		static u8 k=0;
		comtmp = USART_ReceiveData(USART1); 
		 
			 u1_RxTimeout =3;   //定时器每隔10ms中断一次，3次的时间为30ms，超过30ms无数据发送就认定该次发送结束  	 
		 
		if (g_u8RxIndexW < (COM_SIZE-1))
				{
					RxDataBuff[g_u8RxIndexW++] = comtmp;
								
					if (comtmp == COM_END)      //是否检测到结束位
							endcount_4g += 1;          //结束位标志加1
					else
							endcount_4g = 0; 		

					if(k)
						{
						
						 if (comtmp != 0x0A)     
						 {
							 k=0;
							 USART1_RX_CRLF=0;
						 }
						 else	 
						 {
						  USART1_RX_CRLF=1;		
						 }			 	 
						}
					 if (comtmp == 0x0D)
							{
							 k=1;
							 } 				
				}		
						
		else //接收已满
				{
					InitEC20Combuff();//初始化串口通讯缓冲区
					RxDataBuff[g_u8RxIndexW++] = comtmp;
				}						
   }
}

//combuff:接收缓存首地址
//comidx:读到的数据长度

void USART2_IRQHandler(void)       //串口接收中断，并将接收到得数据发送出
{
 u8 comtmp;
	
 if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)//判断 是否 接收中断  
   { 
		comtmp = USART_ReceiveData(USART2); 
		if (comidx < COM_SIZE)
				{
					combuff[comidx++] = comtmp;
					
					if (comtmp == COM_END)      //是否检测到结束位
							endcount += 1;          //结束位标志加1
					else
							endcount = 0; 					
				}				
						
		else //接收已满
				{
					InitCombuff();//初始化串口通讯缓冲区
					combuff[comidx++] = comtmp;
				}						
   }
}

//combuff:接收缓存首地址
//comidx:读到的数据长度

void USART3_IRQHandler(void)       //串口接收中断，并将接收到得数据发送出
{
 u8 comtmp;
	
 if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)//判断 是否 接收中断  
   { 
		static u8 k=0;
		comtmp = USART_ReceiveData(USART3); 
		if (QR_u8RxIndexW < 49)
				{
					QR_RxDataBuff[QR_u8RxIndexW++] = comtmp;
						
					if(k)
						{
						
						 if (comtmp != 0x0A)     
						 {
							 k=0;
							 USART3_RX_CRLF=0;
							
						 }
						 else	 
						 {
						  USART3_RX_CRLF=1;		
						 }			 	 
						}
					
					 if (comtmp == 0x0D)
							{
							 k=1;
							
							 } 				
				}		
						
		else //接收已满
				{
					InitQRCombuff();//初始化串口通讯缓冲区
					QR_RxDataBuff[QR_u8RxIndexW++] = comtmp;
				}						
   }
}





#ifdef   WISDOM_PLATE     //是智盘

void UART4_IRQHandler(void)       //串口接收中断，并将接收到得数据发送出
{
 u8 comtmp;
	
 if(USART_GetITStatus(UART4, USART_IT_RXNE) != RESET)//判断 是否 接收中断  
   { 
		comtmp = USART_ReceiveData(UART4); 
		if (WP_u8RxIndexW < COM_SIZE)
				{
					WP_RxDataBuff[WP_u8RxIndexW++] = comtmp;
									
				}				
						
		else //接收已满
				{
					InitWPCombuff();//初始化串口通讯缓冲区
					
					WP_RxDataBuff[WP_u8RxIndexW++] = comtmp;
				}						
   }
}


#endif	


#endif	

