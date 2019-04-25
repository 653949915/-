#ifndef	__RJ45CMD_H__
#define	__RJ45CMD_H__
#include "sys.h"				

typedef  void (*pFunction)(void);





extern uint8_t   TcpClient_databuff[];   //网口通讯缓冲区

extern uint8_t   UDPClient_databuff[];   //UDPClient通讯缓冲区

extern uint8_t   TcpServer_databuff[];   //TcpServer通讯缓冲区

void ProcessTCPClient(void);             //处理网络络客户端数据  TCPClient

void ProcessTCPServer(void);             //处理网络客服户端数据  TCPServer

void ProcessUDPClient(void);             //处理网络UDP客户端数据 UDPClient

void InitTcpClient(void);


void Init_MAC_Address(void);      //初始化Mac地址
void InitRemoteIPandPORT(void);   //初始化远端IP和端口号
void InitLocalIPGateway(void);    //初始化本地IP、子网掩码、网关



void reboot(void);                //STM32系统软复位函数  

#endif


