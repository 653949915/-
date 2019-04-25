#ifndef	__CARDPROCESS_H__
#define	__CARDPROCESS_H__
#include "sys.h"	
#include "AT24C256.h"	




#define	 PAY_OK	                      0X00   // 刷卡OK
#define	 PAY_WHITEALLOW_WRR	          0X01   // 白名单错误
#define	 PAY_HOLIDAY_ERR              0X02   // 节假日错误
#define	 PAY_TIME_INTERVAL_ERR        0X03   // 时间段错误
#define	 PAY_BACK_ERR                 0X04   // 黑名单错误
#define	 PAY_DELAYED_ERR              0X05   // 刷卡延时错误
#define	 PAY_SECTOR_PASSW_ERR         0X06   // 扇区密码错误
#define	 PAY_RW_SECTOR_ERR            0X07   // 读写扇区错误


#define	 EXCEED_MAX_RECORD_ERR        0X10   // 超出最大存储数量  
#define	 EXCEED_RECORDERRCOUNT_ERR    0X11   // 存储错误数量


#define	 PAY_NO_MONEY_ERR             0X20   // 余额不足
#define	 PAY_EXCEED_LIMIT_SECOND_ERR  0X21   // 超出当次限额
#define	 PAY_EXCEED_LIMIT_DAY_ERR     0X22   // 超出当日限额(只针对服务器)
#define	 PAY_MEAL_TIME_ERR            0X23   // 就餐时间段错误
#define	 PAY_REPEAT_COLLAR_ERR        0X24   // 重复领餐
#define	 PAY_NO_RESERVATION_ERR       0X25   // 未订餐
#define	 PAY_NO_CONSUM_TIMER_ERR      0X26   // 非就餐时间段



#define	 SYS_NO_NETWORK               0XF1   //无网络
#define	 SYS_NET_CONNECT_FAIL         0XF2   //网络连接失败


#define	CARD_DELAY_CYCLE	SECOND_CYCLE   //1秒计数
#define SUM_SECTIONS		16    //扇区数量
#define BLOCK_SIZE			16    //块数据长度

/**********************************************************
//外部变量声明
**********************************************************/
extern u32 idcycle; //两次读同一张卡间距
extern u8  idcycleflag;
extern u8  oldID[]; //记录上次读卡卡号
extern u8  PasswordMask[];//密码掩码

extern u8  curSection; //当前读写扇区
extern u8  cardPW[]; //卡密码

extern u8  blk0[];
extern u8  blk1[];
extern u8  blk2[];
extern u8  blk3[];

extern u32 isAdmin;
extern u32 isICSetting;
extern u32 isValidICPW;   //有效IC卡密码
extern u32 isValidICData; //读取到块数据

extern uint8_t Pay_Carderr_Code ;       // 刷卡错误代号 

extern uint8_t Pay_Head_Code ;       // 刷卡读头号

extern uint8_t Enable_Pay_Card ;       // 允许刷卡标志
/**********************************************************
//外部函数声明
**********************************************************/

extern   u32 FindICCard(void);
 
void ProcessCard(u8 stype);
void CheckCard(void);
void ReadSectionData(u8  isec);
void ProcessSettingByCard(void);

#ifdef   WISDOM_PLATE     //是智盘
uint8_t WP_CheckCard(void);
#endif	
void Check_Card_Limit (uint8_t  stype );
#endif





