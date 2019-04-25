#ifndef	__UPLOAD_H__
#define	__UPLOAD_H__


#include  "sys.h"

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

extern  uint8_t updatareturnfalg  ;  //实时上传返回标志

extern  u16  upOverTimeCnt;          //超时退出计数

extern  u8   Server_Returndata[];                //服务器返回的数据

extern  u8   Card_Markok;                          //有刷卡的标记

extern  u8   Local_Check_Card_falg;                          //本地检查卡权限标志

extern  u8   Offline_Online_falg;                      //消费时在线-离线标志 
/**********************************************************
//外部函数声明
**********************************************************/


void  ProcessReal_time_upload(void);


#endif
