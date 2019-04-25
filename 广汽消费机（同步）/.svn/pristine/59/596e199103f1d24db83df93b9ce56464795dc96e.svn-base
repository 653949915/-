#ifndef	__SYSVAR_H__
#define	__SYSVAR_H__
#include "sys.h"	


/**********************************************************
//外部变量声明
**********************************************************/

	
extern u8  showStandby;//显示日期
extern u32 Standbycount;//不显示日期时计时计数
extern u32 Standbytime ;//进入主界面时间


extern u8 showtime;//显示时间
extern u32 timecount;//不显示时间时计时计数

extern u8 sys_status; //机器所处状态
extern u32 statuscnt; //状态计时周期数


extern u8 keyVal;      //按键值

extern u8 cycle;     //状态分析计数


extern u32 output1state ;    //开门状态
extern u32 output1time ;     //退出开门计数

extern u32 output2state ;    //开门状态
extern u32 output2time ;     //退出开门计数


extern u32 badd; //增加卡
extern u32 bdel; //删除卡

extern u8  idbuff[];
extern u8  ICidbuff[];

extern volatile u32  inPCOM;    //串口数据处理状态


extern  u8  sysvar[];      //系统参数
extern  u8  extvar[];      //扩展参数
extern  u8  repea_time[];  //刷卡延时
extern  u8  output_time[]; //继电器输出延时
extern  u8  whiteallow[];  //白名单是否开启 
extern  u8  interval_time[];    //数卡间隔延时

extern u16  Show_Refresh_coun ;    //显示刷新计数 

extern  u8 meumflag;

extern  u8  Check_the_balance ;    //查询余额状态

extern  u8  refund_the_balance ;   //误刷退款状态

/**********************************************************
//机器状态
**********************************************************/
#define NORMAL_STATUS		      0x01 //正常状态
#define IN_SET_STATUS		      0x02 //编程状态

#define KEY_KEY_STATUS		    0x03 //按键状态
#define KEY_PLUS_STATUS		    0x04 //+ 号状态

#define IN_CONSUMPT_STATUS		0x05 //消费状态

#define IN_MENU_STATUS		    0x06 //菜单状态
#define IN_FUN_STATUS		      0x07 //功能状态
#define IN_QUERY_STATUS		    0x08 //查询状态
#define IN_REFUND_STATUS		  0x09 //退款状态 


#define CALL_SHOW_STATUS	0x04 //来电显示
#define IN_FIND_STATUS		0x08 //呼入查询
#define OUT_FIND_STATUS		0x10 //呼出查询



#define KEY_ASTERISK			 11 //*
#define KEY_POUND				   12 //#

#define KEY_SET				     13 //菜单
#define KEY_FUNCTION		   18 //打印
#define KEY_QUERY		       19 //查询
#define KEY_CONFIRM		     16 //确认

#define KEY_CLEAN		       17 //清除
#define KEY_UPTURN		     14 //上翻
#define KEY_DOWNTURN		   15 //下翻

#define KEY_PLUS		       KEY_POUND // +
#define KEY_SPOT		       KEY_ASTERISK // .
#define KEY_MENU		       13 //菜单


#define KEY_END		   50 //确认#
#define	KEY_EXIT			5 //按键复位

#define OPEN_REL1()				  RELAY1 = 0    //打开继电器1
#define CLOSE_REL1()				RELAY1 = 1    //关闭继电器1

#define OPEN_REL2()				  RELAY2 = 0    //打开继电器2
#define CLOSE_REL2()				RELAY2 = 1    //关闭继电器2
/**********************************************************
//定时器定时相关
**********************************************************/
#define DELAY_MS		   100  //定时器每次定时100ms
#define SECOND_CYCLE	(1000 / DELAY_MS) //每秒循环周期
#define MINUTE_CYCLE	(SECOND_CYCLE * 60L) //每分钟循环周期

/**********************************************************
//COM通讯相关
**********************************************************/
#define	COM_START		0x2A // = '*'，起始位
#define	COM_END			0x7E // = '~'，停止位
#define	COM_SIZE		2048 //通讯数据长度
#define	COM_REC			0 //485接收
#define	COM_SEND		1 //485发送


/**********************************************************
//定义结构
**********************************************************/
union TwoByte //高低 低高
{
	uint32_t  i;
	u8 c[2];
}; 



union FourByte //高低低高，例如：ic4.i=0x01020304; ic4.c[0]=0x01 ... ic4.c[3]=0x04
{
	uint32_t i;
	u8 c[4];
}; 	


union EightByte //高低低高，例如：ic4.i=0x01020304; ic4.c[0]=0x01 ... ic4.c[3]=0x04
{
	uint32_t i;
	u8 c[8];
}; 	




/**********************************************************
//外部函数声明
**********************************************************/


void AnalyzeWorkStatus(void);//工作状态分析
void InitOutput(void);   //初始化输出
void BeginOutput1(void);  //继电器1开始输出
void EndOutput1(void);    //继电器1结束输出

void BeginOutput2(void);  //继电器2开始输出
void EndOutput2(void);    //继电器2结束输出

void CheckInit(void);    //检查初始化
void Get_ChipInfo(void); //获取芯片参数

#endif
