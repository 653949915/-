#ifndef __BC95_H
#define __BC95_H
#include "sys.h"

#define   IMEI_SIZE            15                //IMEI号 长度
#define   IMSI_SIZE            15                //IMSI号 长度

/*************************************************************
初始化步骤
**************************************************************/

#define         INITSTEP_START             0                             //待机
#define         INITSTEP_AT                1                             // 
#define         INITSTEP_CGSN              2                             // 
#define         INITSTEP_CIMI              3                             // 
#define         INITSTEP_NNMI_C            4                             // 
#define         INITSTEP_NNMI              5                             // 
#define         INITSTEP_NCDP_C            6                             // 
#define         INITSTEP_CFUN_N            7                             // 
#define         INITSTEP_NCDP              8                             // 
#define         INITSTEP_CFUN_F            9                             // 
#define         INITSTEP_NRB               10                             // 
#define         INITSTEP_CGATT_C           11                             // 
#define         INITSTEP_CCLK_C            12                             // 
                           // 
/*************************************************************
返回错误码
**************************************************************/
#define         BC95_OK                 0                               //OK
#define         STRING_ERR              1                               //非预期返回字符串
#define         CONNECT_ERR             2                               //与模块连接错误
#define         QUERY_BAUD_ERR          3                               //波特率错误
#define         CLOSE_SOCKET_ERR        4
#define         CLOSE_CONTEXT_ERR       5
#define         SQ_ERR                  6                               //信号查询错误
#define         REG_ERR                 7                               //网络注册失败
#define         GREG_ERR                8                               //GPRS附着失败
#define         SET_CONTEXT_ERR         9
#define         ACT_CONTEXT_ERR         10

#define         CGSN_ERR                11
#define         CIMI_ERR                12
#define         NNMI_C_ERR              13
#define         NNMI_ERR                14
#define         NCDP_C_ERR              15
#define         CFUN_N_ERR              16
#define         NCDP_ERR                17
#define         CFUN_F_ERR              18
#define         NRB_ERR                 19
#define         CGATT_C_ERR             20
#define         CCLK_C_ERR              21

#define         QUERY_PIN_ERR           50                              //无SIM卡，或SIM卡有PIN码
#define         BACK_TO_TRAN_ACCESS_MODE_ERR    51
#define         OVER_TIME               52


#define  BC95_UART		USART1	//定义EC20的串口.

#define  RX_BUFF_LEN        COM_SIZE                          //接收缓存数组长度

#define  BC95REST  PAout(8)                                  // PA8	 EC20复位引脚

extern u16 g_u16OverTimeCnt;                                //秒倒计时计数器，要求每秒自减1

extern u16 g_u8RxIndexW;                                    //串口接收计数器写计数器， 上限为RxDataBuff数组长度 RX_BUFF_LEN

extern u8  RxDataBuff[];                                    //串口接收BUFF

//extern uint16_t g_u16OverTimeCnt;                                      //秒倒计时计数器，要求每秒自减1
extern    uint8_t  BC95_IMEI[]  ;             //BC95的IMEI号
extern    uint8_t  SIM_IMSI []  ;             //BC95的IMEI号
extern  	uint8_t  BC95_CLOCK[];              //BC95网络时间

extern    uint8_t  BC95_USER_buff[];      //BC95用户数据
void InitBC95Combuff(void);  //初始化BC95串口通讯缓冲区


void QuectelBC95_ConnectNet(uint8_t star);

void BC95_SendString(uint8_t *combuff ,uint16_t len);
#endif


