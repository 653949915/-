#ifndef __MYIIC_2_H
#define __MYIIC_2_H
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途

//IIC驱动 代码	   

//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////

//IO方向设置
 
#define SDA_2_IN()  {GPIOE->CRL&=0XFF0FFFFF;GPIOE->CRL|=(u32)8<<4*5;}
#define SDA_2_OUT() {GPIOE->CRL&=0XFF0FFFFF;GPIOE->CRL|=(u32)3<<4*5;}

//IO操作函数	 
#define IIC_2_SCL    PEout(6) //SCL
#define IIC_2_SDA    PEout(5) //SDA	 
#define READ_2_SDA   PEin(5)  //输入SDA 

//IIC所有操作函数
void IIC_2_Init(void);                //初始化IIC的IO口				 
void IIC_2_Start(void);				//发送IIC开始信号
void IIC_2_Stop(void);	  			//发送IIC停止信号
void IIC_2_Send_Byte(u8 txd);			//IIC发送一个字节
u8 IIC_2_Read_Byte(unsigned char ack);//IIC读取一个字节
u8 IIC_2_Wait_Ack(void); 				//IIC等待ACK信号
void IIC_2_Ack(void);					//IIC发送ACK信号
void IIC_2_NAck(void);				//IIC不发送ACK信号

void IIC_2_Write_One_Byte(u8 daddr,u8 addr,u8 data);
u8 IIC_2_Read_One_Byte(u8 daddr,u8 addr);	  
#endif
















