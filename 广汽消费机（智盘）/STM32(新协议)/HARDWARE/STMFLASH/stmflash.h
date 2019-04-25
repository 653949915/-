#ifndef __STMFLASH_H__
#define __STMFLASH_H__
#include "sys.h"  

//�û������Լ�����Ҫ����
#define STM32_FLASH_SIZE 256 	 		//��ѡSTM32��FLASH������С(��λΪK)
#define STM32_FLASH_WREN 1              //ʹ��FLASHд��(0��������;1��ʹ��)
//////////////////////////////////////////////////////////////////////////////////////////////////////

//FLASH��ʼ��ַ
#define STM32_FLASH_BASE 0x08000000 	//STM32 FLASH����ʼ��ַ


/*
˵����
1.   FLASH_START_ADDR �����ʼ��ַ��ʼ���Bootloader��������
2.   FLASH_APP1_ADDR  ���������Ӧ�ó��򣬳�������104K
3.   FLASH_APP2_ADDR  �����λ���·��Ĺ̼�
4.   FLASH_END_ADDR   ����û����ݣ������������ڣ��̼����±�־

ע�⣺����FLASH��ַ����ֻ������256K FLASH�ռ�ĵ�Ƭ��������������ͺŵ�Ƭ����Ҫ���¶��塣

*/

#define FLASH_START_ADDR  0x08000000 	  //��0K�� STM32 FLASH����ʼ��ַ   //����0X08000000~0X08005FFF�Ŀռ�ΪIAPʹ��  24K

#define FLASH_APP1_ADDR		0x08006000  	// (��24K) ��һ��Ӧ�ó�����ʼ��ַ(�����FLASH)  //����0X08006000~0X0801FFFF �Ŀռ�ΪIAPʹ��   104K(0X1A000)
										
#define FLASH_APP2_ADDR		0x08020000  	// (��128K)�ڶ���Ӧ�ó�����ʼ��ַ(�����FLASH)  //����0X08020000~0X08039FFF �Ŀռ�Ϊ�³���ʹ�� 104K(0X1A000)											
											
#define FLASH_DATA_ADDR		0x0803A000  	// (��232K)�û����ݴ����ʼ��ַ(�����FLASH)    //����0X0803A000~0X0803FFFF �Ŀռ�Ϊ������־ 24K(0X6000)

#define FLASH_END_ADDR		0x08040000    //  FLASH������ַ

#define FLASH_APP_SIZE    0X1A000       //  Ӧ�ó����С 104K



//FLASH������ֵ
 

u16 STMFLASH_ReadHalfWord(u32 faddr);		  //��������  
void STMFLASH_WriteLenByte(u32 WriteAddr,u32 DataToWrite,u16 Len);	//ָ����ַ��ʼд��ָ�����ȵ�����
u32 STMFLASH_ReadLenByte(u32 ReadAddr,u16 Len);						//ָ����ַ��ʼ��ȡָ����������
void STMFLASH_Write(u32 WriteAddr,u16 *pBuffer,u16 NumToWrite);		//��ָ����ַ��ʼд��ָ�����ȵ�����
void STMFLASH_Read(u32 ReadAddr,u16 *pBuffer,u16 NumToRead);   		//��ָ����ַ��ʼ����ָ�����ȵ�����

void STMFLASH_Erase(u32 WriteAddr,u16 NumToWrite);

//����д��
void Test_Write(u32 WriteAddr,u16 WriteData);								   
#endif

















