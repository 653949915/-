#ifndef	__RJ45CMD_H__
#define	__RJ45CMD_H__
#include "sys.h"				


extern uint8_t   TcpClient_databuff[];   //网口通讯缓冲区

extern uint8_t   UDPClient_databuff[];   //UDPClient通讯缓冲区

extern uint8_t   TcpServer_databuff[];   //TcpServer通讯缓冲区

void ProcessTCPClient(void);             //处理网络络客户端数据  TCPClient

void ProcessTCPServer(void);             //处理网络客服户端数据  TCPServer

void ProcessUDPClient(void);             //处理网络UDP客户端数据 UDPClient

void InitTcpClient(void);

#endif


