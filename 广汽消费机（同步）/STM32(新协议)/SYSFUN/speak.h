#ifndef	__SPEAK_H__
#define	__SPEAK_H__
#include  "sys.h"




/*SYN6288 命令*/

#define  SYN6288CMD_VOICE_PLAY            0X01              //合成播放语音
#define  SYN6288CMD_STOP_SYNTHES          0X02              //停止合成
#define  SYN6288CMD_PAUSE_SYNTHES         0X03              //暂停合成
#define  SYN6288CMD_RECOVERY_SYNTHES      0X04              //恢复合成
#define  SYN6288CMD_STATE_QUERY           0X21              //状态查询
#define  SYN6288CMD_POWER_DOWN            0X88              //芯片休眠
#define  SYN6288CMD_SET_BPS               0X32              //设置波特率



/*SYN6288 命令参数*/


#define  SYN6288CMDPARAM_PLAY_MUSIC0     0X00              //背景音乐无 GB2312格式
#define  SYN6288CMDPARAM_PLAY_MUSIC1     0X08              //背景音乐1 GB2312格式       
#define  SYN6288CMDPARAM_PLAY_MUSIC2     0X10              //背景音乐2 GB2312格式
#define  SYN6288CMDPARAM_PLAY_MUSIC3     0X18              //背景音乐3 GB2312格式
#define  SYN6288CMDPARAM_PLAY_MUSIC4     0X20              //背景音乐4 GB2312格式
#define  SYN6288CMDPARAM_PLAY_MUSIC5     0X28              //背景音乐5 GB2312格式

//#define KEY_SIZE 20Voice playback

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



/**********************************************************
//外部函数声明
**********************************************************/

#define SPEAK_SDA    PBout(7)// PB7

#define SC8002_SHDN  PBout(6)// PB6


void SC50X0_SDA(unsigned char data);


void SPEAK_USART_TX_init(void);

void MUSART1_SendData(uint8_t data);
void SPEAKUART_SendString(uint8_t *speakcombuff ,uint16_t len);

void  SYN6288_Send(uint8_t function ,uint8_t Cmdparam , uint8_t *data ,uint8_t len);
#endif
