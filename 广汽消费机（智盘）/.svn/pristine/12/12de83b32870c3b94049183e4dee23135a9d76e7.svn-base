#ifndef __EC20_H
#define __EC20_H
#include "sys.h"



/*************************************************************
初始化步骤
**************************************************************/


#define         INITSTEP_START             0                             //待机
#define         INITSTEP_AT                1                             // 
#define         INITSTEP_ATE0              2                             // 
#define         INITSTEP_CPIN              3                             // 
#define         INITSTEP_CREG              4                             // 
#define         INITSTEP_CGREG             5                             // 
#define         INITSTEP_QIOPEN            6                             // 
#define         INITSTEP_QICLOSE           7                             // 
#define         INITSTEP_IMEI              12                             // 
#define         INITSTEP_IMSI              13                             //

#define         INITSTEP_QGPS              8                             // 
#define         INITSTEP_QGPSCFG           9                             // 
#define         INITSTEP_QGPSLOC           10                             // 
#define         INITSTEP_QGPSEND           11                             // 

#define EC20_UART		USART1	//定义EC20的串口.

#define     RX_BUFF_LEN        COM_SIZE                          //接收缓存数组长度

#define EC20REST  PAout(8)                                  // PA8	 EC20复位引脚

extern  u8 AT_QIOPEN_IP[] ;     //自定义服务器IP端口


extern u8 QuectelEC20_ConnectNet(void);

extern u16 g_u16OverTimeCnt;                                //秒倒计时计数器，要求每秒自减1

extern u16 AT_InterOverTimeCnt;                             //AT指令间隔超时倒计时计数器，每100毫秒自减1

extern u16 g_u8RxIndexW;                                    //串口接收计数器写计数器， 上限为RxDataBuff数组长度 RX_BUFF_LEN

extern u8  RxDataBuff[];                                    //串口接收BUFF

void EC20_REST_Init(void);                                  //EC20模块

void QuectelEC20_Network_Init(uint8_t star);                        // EC20网络配置

void InitEC20Combuff(void) ;                              //初始化EC20串口通讯缓冲区


void QuectelEC20_Rest(void);               //EC20 硬件复位
void EC20_SendString(uint8_t *combuff ,uint16_t len);

extern uint8_t   EC20GPSBUF[] ;        //GPS接收数据缓冲区

extern uint16_t  EC20GPSLEN ;               //接收到的GPS数据长度

extern  uint8_t  gl_imei[];
extern  uint8_t  gl_imsi[];



#endif


