#ifndef __WIFI_H
#define __WIFI_H			 
#include "sys.h"	 								  




void WIFISendcard( u8 strlen);     //WIFI���Ϳ���

void WIFISendPassword(const u8 *str, u8 strlen);   //WiFi��������

void WIFIBeat(void);  //������
void InitWIFI(void);  //WIFI��ز�����ʼ��
void ProcessWIFI(void);  //����WiFi���յ�������	

extern u32 wificmd;
extern u32 wificycle;

extern u32 wifisend;     
extern u32 wifisendcycle;















#endif	   
















