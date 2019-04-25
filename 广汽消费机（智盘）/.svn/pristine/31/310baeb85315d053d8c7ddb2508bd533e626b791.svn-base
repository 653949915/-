#ifndef	__KEYFUN_H__
#define	__KEYFUN_H__
#include "sys.h"	




typedef struct
{
	
	unsigned char err ; 		    //错误类型
	unsigned char errcount ; 	  //错误计数

	unsigned char spotfalg ;	  //小数点标志
	unsigned char spotcount ;	  //小数点后按键数量
	unsigned char spotpos ;	    //小数点后按键位置
	
	unsigned char normalfalg ;	  //正常状态标志
	unsigned char normalcount ;	  //正常状态按键数量
	unsigned char normalpos ;	    //正常状态按键位置
	
	unsigned char nospotfalg ;	//非小数点标志
	unsigned char nospotcount ;	//非小数点后按键数量
	unsigned char nospotpos ;	  //非小数点后按键位置
	
	unsigned char plusfalg ;		//+ 号标志
	unsigned char pluscount ;		//+ 号后按键数量
	unsigned char pluspos ;		  //+ 号后按键位置
	
	unsigned char keyclock;		  //按键锁定
		
	unsigned char reverse2;		//预留2

} KEY_STATUS_INFO;


extern KEY_STATUS_INFO    key_status_info;


#define KEY_SIZE 20                         //按键计数的个数
#define INIT_KEY_BUFF()	keyidx = 0          //按键数量清零
#define SET_MY_STATUS(mystatus)	SetWorkStatus(mystatus)   //设置工作状态
#define MY_STATUS_IS(mystatus)	(sys_status == mystatus)  //编程状态
#define MY_STATUS_NOT(mystatus)	(sys_status != mystatus)  //非编程状态


//#define PASSWORD_SIZE	6 //编程密码长度

/**********************************************************
//外部变量声明
**********************************************************/

extern u8 keyidx;//字符接收个数
extern u8 keybuff[];//接收的字符

extern u8 keymoneybuff[];//按键的金额

extern u8 menu_keyidx;//字符接收个数

extern u8 menu_keybuff[];//接收的字符
extern u8 menu_keyidx_MAX ;//菜单模式按键字符最大接收个数

extern uint32_t u32_monetbuf;        //按键的总额U32格式

/**********************************************************
//外部函数声明
**********************************************************/

void CheckKEY(u8 keyVal);//检查按键

void Menu_CheckKEY(u8 keyVal); //菜单检查按键

void UndoPressKEY(void);   //撤消按键
void InvalidOperate(void); //无效操作
void ExitSetStatus(void);  //退出编程状态

void ProcessKEYCMD(void);  //处理【正常状态】下按键命令
void SetWorkStatus(u8 curStatus);  //设置工作状态


void ChangeSetPassword(void);//修改编程密码
void OpenSetPassword(void);  //修改开门密码

void SetDatetime(void);//设置日期时间


/**********************************************************
//读取工作状态
**********************************************************/
uint8_t GetWorkStatus(u8 curStatus);

void  Clear_Key_Status(void );
#endif








