#ifndef __24CXX_H
#define __24CXX_H
#include "myiic.h"   
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;

//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////

#define AT24C01		127
#define AT24C02		255
#define AT24C04		511
#define AT24C08		1023
#define AT24C16		2047
#define AT24C32		4095
#define AT24C64	  8191
#define AT24C128	16383
#define AT24C256	32767  
#define AT24C512	65535 

#define EE_TYPE AT24C512
					  
u8 AT24CXX_ReadOneByte(u16 ReadAddr);							               //ָ����ַ��ȡһ���ֽ�
void AT24CXX_WriteOneByte(u16 WriteAddr,u8 DataToWrite);		     //ָ����ַд��һ���ֽ�
void AT24CXX_WriteLenByte(u16 WriteAddr,u32 DataToWrite,u8 Len); //ָ����ַ��ʼд��ָ�����ȵ�����
u32 AT24CXX_ReadLenByte(u16 ReadAddr,u8 Len);					           //ָ����ַ��ʼ��ȡָ����������
void AT24CXX_Write(u16 WriteAddr,u8 *pBuffer,u16 NumToWrite);	   //��ָ����ַ��ʼд��ָ�����ȵ�����
void AT24CXX_Read(u16 ReadAddr,u8 *pBuffer,u16 NumToRead);   	   //��ָ����ַ��ʼ����ָ�����ȵ�����

// void  I2CPageWrite(u16 address, u8 *date , u16 number);
void I2CPageRead(u16 address,u8 *date , u8 number );

void AT24CXX_Write1(u16 WriteAddr,u8 *pBuffer,u16 NumToWrite);




u8 AT24CXX_Check(void);  //�������
void AT24CXX_Init(void); //��ʼ��IIC
void AT24C256Check(void); //���at24C256
#endif



















