#ifndef	__CARDRW_H__
#define	__CARDRW_H__ 

#include "sys.h"
#include "sysvar.h"
/**********************************************************
//常量定义
**********************************************************/
#define SET_BY_CARD			'*' //用卡设置参数

#define SECTION_RD_SUCC		0x00 //扇区读取成功
#define CHECK_PW_ERROR		0x01 //密码认证错误
#define BLOCK_RD_ERROR		0x02 //块读取错误
#define TIME_SEG_ERROR		0x03 //时间段错误
#define LEFT_COUNT_ERROR	0x04 //剩余次数错误
#define SPACE_TIME_ERROR	0x05 //间隔时间错误
#define VALID_DATE_ERROR	0x06 //有效日期错误
#define CARD_GROUP_ERROR	0x07 //分组错误，2014-12-16

#define TIME_INTERVAL_SUCC		0x08 //刷卡延时 允许刷卡
#define TIME_INTERVAL_ERR		  0x09 //刷卡延时 不允许刷卡
/**********************************************************
//外部变量声明
**********************************************************/


extern u8  Current_time_value[];
 
extern u32 Time_interval_flag;
 
static union FourByte Debit_money={0};
 
extern unsigned char  ICcardbuff[];
 
extern 	u8 ICcard_frequencyBUFF[];                                       //刷卡次数（字符串形式）

	extern	u8 ICcard_frequencybf[2];

extern u8 ICcardNameASCII[];
/**********************************************************
//外部函数声明
**********************************************************/
//u32 FindICCard(void);
uint8_t  ProcessICCard(void);
void Set_Time_slot(void);     //打卡时段

void Set_Time_slot_1(void);     //打卡时段

extern  u32 Time_interval_fun(void);   //打卡延时
		
extern	u8 AnalyzeSectionData(void);

extern  u32 WriteBlock1(void);

extern unsigned char Time_slot[];
#endif

