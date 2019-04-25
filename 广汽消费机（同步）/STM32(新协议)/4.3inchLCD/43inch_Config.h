#ifndef	__43INCH_CONFIG_H__
#define	__43INCH_CONFIG_H__

#include "sys.h"

//#define KEY_SIZE 20

/**********************************************************
//外部变量声明
**********************************************************/

	
//extern u8  showStandby;//显示日期






/**********************************************************
//外部函数声明
**********************************************************/


void Boot_Display_43inch(void);      //开机显示

void ShowPlay_Card_43inch(uint8_t  type);      //刷卡显示


void Standby_43inch(void)	;    //待机时显示时间
	

#endif
