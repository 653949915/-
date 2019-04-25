#ifndef __24CXX_2_H
#define __24CXX_2_H
#include "myiic_2.h"   
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途

//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////

#define AT24C01_2		127
#define AT24C02_2		255
#define AT24C04_2		511
#define AT24C08_2		1023
#define AT24C16_2		2047
#define AT24C32_2		4095
#define AT24C64_2	  8191
#define AT24C128_2	16383
#define AT24C256_2	32767  
#define AT24C512_2	65535 

#define EE_TYPE_2   AT24C512_2
					  
u8 AT24CXX_2_ReadOneByte(u16 ReadAddr);							               //指定地址读取一个字节
void AT24CXX_2_WriteOneByte(u16 WriteAddr,u8 DataToWrite);		     //指定地址写入一个字节
void AT24CXX_2_WriteLenByte(u16 WriteAddr,u32 DataToWrite,u8 Len); //指定地址开始写入指定长度的数据
u32 AT24CXX_2_ReadLenByte(u16 ReadAddr,u8 Len);					           //指定地址开始读取指定长度数据
void AT24CXX_2_Write(u16 WriteAddr,u8 *pBuffer,u16 NumToWrite);	   //从指定地址开始写入指定长度的数据
void AT24CXX_2_Read(u16 ReadAddr,u8 *pBuffer,u16 NumToRead);   	   //从指定地址开始读出指定长度的数据

// void  I2CPageWrite(u16 address, u8 *date , u16 number);
void I2CPageRead_2(u16 address,u8 *date , u8 number );

void AT24CXX_2_Write1(u16 WriteAddr,u8 *pBuffer,u16 NumToWrite);




u8 AT24CXX_2_Check(void);  //检查器件
void AT24CXX_2_Init(void); //初始化IIC
void AT24C256Check_2(void); //检测at24C256
#endif



















