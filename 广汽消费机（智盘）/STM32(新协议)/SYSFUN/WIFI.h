#ifndef __WIFI_H
#define __WIFI_H			 
#include "sys.h"	 								  




void WIFISendcard( u8 strlen);     //WIFI发送卡号

void WIFISendPassword(const u8 *str, u8 strlen);   //WiFi发送密码

void WIFIBeat(void);  //心跳包
void InitWIFI(void);  //WIFI相关参数初始化
void ProcessWIFI(void);  //处理WiFi接收到的数据	

extern u32 wificmd;
extern u32 wificycle;

extern u32 wifisend;     
extern u32 wifisendcycle;















#endif	   
















