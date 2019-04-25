#ifndef __QR_CODE_H
#define __QR_CODE_H
#include "sys.h"


#define QR_UART		USART3	//定义二维码的串口.


void QR_SendString(uint8_t *combuff ,uint16_t len);

void QR_SendByte(uint8_t combuff);



extern u8   QR_RxDataBuff[];                         //中断接收数组

extern u16  QR_u8RxIndexW;                           //中断接收数组写指针

extern u8   USART3_RX_CRLF;


void InitQRCombuff(void);


uint8_t ProcessQR_Commu(void);         	//处理二维码通讯

extern uint8_t QRread_styp;                         //二维码读头度取到的数据类型  3--IC卡 4--二维码

extern uint8_t  oldQRID[];


extern uint8_t  Asynchronous_QR_falg;      //异步二维码，客餐订餐标识


#endif


