#ifndef	__WISDOM_PLATE_H__
#define	__WISDOM_PLATE_H__

#include  "sys.h"

//Wisdom_plate




#define WP_UART		UART4	//定义EC20的串口.



/**********************************************************
//外部变量声明
**********************************************************/

extern  u8   WP_RxDataBuff[];                         //中断接收数组

extern  u16  WP_u8RxIndexW;                               //中断接收数组写指针
	
extern	u8   WP_clearcycle;                           //清除串口数据计数
	
//extern  u8   Server_Returndata[];                //服务器返回的数据

extern  u8   WP_updatareturnfalg;                           //实时上传返回标志

extern  u16  wpOverTimeCnt;                        //超时退出计数

extern  u8  WP_UserBalance[];	  //卡上余额
 
extern  u8  WP_Consum_Amount[] ;	  //消费金额

extern  uint8_t  wp_Consumpidbuff[] ;                   //消费时的卡号

/**********************************************************
//外部函数声明
**********************************************************/


void   InitWPCombuff(void);  //初始化串口通讯缓冲区

void   Process_Wisdom_plate(void);       //处理智盘串口通讯

void  Process_Wisdom_plate_Card(void );

void Wisdom_plate_Return(uint8_t cmdtyp, uint8_t Result);  //响应智盘命令

#endif
