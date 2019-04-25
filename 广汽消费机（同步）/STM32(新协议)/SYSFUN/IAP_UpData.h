#ifndef	__IAP_UpData_H__
#define	__IAP_UpData_H__
#include "sys.h"

#define IAP_SIZE    		1024L


extern  uint32_t iapallcnt ;	                             //升级固件总字节

//#define KEY_SIZE 20

/**********************************************************
//外部变量声明
**********************************************************/

	
//extern u8  showStandby;//显示日期
//extern u32 Standbycount;//不显示日期时计时计数

//extern u8 showtime;//显示时间
//extern u32 timecount;//不显示时间时计时计数

//extern u32 keyidx;//字符接收个数
//extern u8 keybuff[];//接收的字符



//extern u32 key;      //按键值

extern  uint16_t  iapreceivepackcnt ;	                       //升级固件包实际接收的数量


/**********************************************************
//外部函数声明
**********************************************************/


uint8_t  Check_IAP_Start_Updata(uint8_t *data ,uint16_t len);      //固件开始更新前的检查

uint8_t  Handle_IAP_Data(uint8_t *data ,uint16_t len);             //固件内容检测

uint8_t  Check_IAP_END_Updata(void);                               //固件结束检测

void  IAP_OK_System_Boot(void);


u32  False_Random_number(void);      //伪随机数

void SoftReset(void);    //软件复位方式


void  Clear_IAP_OK_System_Boot(void);

#endif
