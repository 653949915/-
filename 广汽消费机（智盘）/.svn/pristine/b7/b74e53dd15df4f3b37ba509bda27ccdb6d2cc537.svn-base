#ifndef __STMFLASH_H__
#define __STMFLASH_H__
#include "sys.h"  

//用户根据自己的需要设置
#define STM32_FLASH_SIZE 256 	 		//所选STM32的FLASH容量大小(单位为K)
#define STM32_FLASH_WREN 1              //使能FLASH写入(0，不是能;1，使能)
//////////////////////////////////////////////////////////////////////////////////////////////////////

//FLASH起始地址
#define STM32_FLASH_BASE 0x08000000 	//STM32 FLASH的起始地址


/*
说明：
1.   FLASH_START_ADDR 存放起始地址开始存放Bootloader引导程序
2.   FLASH_APP1_ADDR  存放真正的应用程序，程序最大可104K
3.   FLASH_APP2_ADDR  存放上位机下发的固件
4.   FLASH_END_ADDR   存放用户数据，包含不仅限于：固件更新标志

注意：以下FLASH地址分配只适用于256K FLASH空间的单片机，如果是其他型号单片机需要重新定义。

*/

#define FLASH_START_ADDR  0x08000000 	  //（0K） STM32 FLASH的起始地址   //保留0X08000000~0X08005FFF的空间为IAP使用  24K

#define FLASH_APP1_ADDR		0x08006000  	// (第24K) 第一个应用程序起始地址(存放在FLASH)  //保留0X08006000~0X0801FFFF 的空间为IAP使用   104K(0X1A000)
										
#define FLASH_APP2_ADDR		0x08020000  	// (第128K)第二个应用程序起始地址(存放在FLASH)  //保留0X08020000~0X08039FFF 的空间为新程序使用 104K(0X1A000)											
											
#define FLASH_DATA_ADDR		0x0803A000  	// (第232K)用户数据存放起始地址(存放在FLASH)    //保留0X0803A000~0X0803FFFF 的空间为升级标志 24K(0X6000)

#define FLASH_END_ADDR		0x08040000    //  FLASH结束地址

#define FLASH_APP_SIZE    0X1A000       //  应用程序大小 104K



//FLASH解锁键值
 

u16 STMFLASH_ReadHalfWord(u32 faddr);		  //读出半字  
void STMFLASH_WriteLenByte(u32 WriteAddr,u32 DataToWrite,u16 Len);	//指定地址开始写入指定长度的数据
u32 STMFLASH_ReadLenByte(u32 ReadAddr,u16 Len);						//指定地址开始读取指定长度数据
void STMFLASH_Write(u32 WriteAddr,u16 *pBuffer,u16 NumToWrite);		//从指定地址开始写入指定长度的数据
void STMFLASH_Read(u32 ReadAddr,u16 *pBuffer,u16 NumToRead);   		//从指定地址开始读出指定长度的数据

void STMFLASH_Erase(u32 WriteAddr,u16 NumToWrite);

//测试写入
void Test_Write(u32 WriteAddr,u16 WriteData);								   
#endif

















