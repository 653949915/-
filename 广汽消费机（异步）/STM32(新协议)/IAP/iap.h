#ifndef __IAP_H__
#define __IAP_H__
#include "sys.h"  





typedef  void (*iapfun)(void);				//定义一个函数类型的参数.


/*
说明：
1.   FLASH_START_ADDR 存放起始地址开始存放Bootloader引导程序
2.   FLASH_APP1_ADDR  存放真正的应用程序，程序最大可104K
3.   FLASH_APP2_ADDR  存放上位机下发的固件
4.   FLASH_END_ADDR   存放用户数据，包含不仅限于：固件更新标志

注意：以下FLASH地址分配只适用于256K FLASH空间的单片机，如果是其他型号单片机需要重新定义。

*/

//#define FLASH_START_ADDR  0x08000000 	  //（0K） STM32 FLASH的起始地址   //保留0X08000000~0X08005FFF的空间为IAP使用  24K

//#define FLASH_APP1_ADDR		0x08006000  	// (第24K) 第一个应用程序起始地址(存放在FLASH)  //保留0X08006000~0X0801FFFF 的空间为IAP使用   104K(0X1A000)
										
//#define FLASH_APP2_ADDR		0x08020000  	// (第128K)第二个应用程序起始地址(存放在FLASH)  //保留0X08020000~0X08039FFF 的空间为新程序使用 104K(0X1A000)											
											
//#define FLASH_DATA_ADDR		0x0803A000  	// (第232K)用户数据存放起始地址(存放在FLASH)    //保留0X0803A000~0X0803FFFF 的空间为新程序使用 24K(0X6000)

//#define FLASH_END_ADDR		0x08040000    //  FLASH结束地址


void iap_load_app(u32 appxaddr);			//执行flash里面的app程序
void iap_load_appsram(u32 appxaddr);		//执行sram里面的app程序
void iap_write_appbin(u32 appxaddr,u8 *appbuf,u32 applen);	//在指定地址开始,写入bin
#endif







































