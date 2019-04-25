#ifndef	__COMCMD_H__
#define	__COMCMD_H__
#include "sys.h"				


/***************************************
通讯协议各部分长度
***************************************/

#define	  AGR_HEAD_SIZE    1             // 头
#define	  AGR_CODE_SIZE    5             // 流水号
#define	  AGR_MACH_SIZE    4             // 机号
#define	  AGR_TYPE_SIZE    1             // 类型
#define	  AGR_CMD_SIZE     1             // 命令
#define	  AGR_LEN_SIZE     2             // 数据长度
#define	  AGR_DATA_SIZE    0L             // 数据
#define	  AGR_ROX_SIZE     1             // 异或校验
#define	  AGR_RETAIN_SIZE  4             // 保留字节
#define	  AGR_END_SIZE     3             // 尾


/***************************************
通讯协议各部分位置
***************************************/
#define	  AGR_HEAD_POS    0            // 头
#define	  AGR_CODE_POS    1           // 流水号
#define	  AGR_MACH_POS    6            // 机号
#define	  AGR_TYPE_POS    10             // 类型
#define	  AGR_CMD_POS     11             // 命令
#define	  AGR_LEN_POS     12             // 数据长度
#define	  AGR_LEN_POS2    13             // 数据长度
#define	  AGR_DATA_POS    14             // 数据

#define	  AGR_ROX_POS     15            // 异或校验
#define	  AGR_RETAIN_POS  16             // 保留字节
#define	  AGR_END_POS     19             // 尾

#define	  AGR_MAXEND_POS     22             // 最大长度





#define	  AGR_FIXED_SIZE    (AGR_HEAD_SIZE + AGR_CODE_SIZE + AGR_MACH_SIZE + AGR_TYPE_SIZE + AGR_CMD_SIZE + AGR_LEN_SIZE)       // 固定长度

#define	  AGR_MAXFIXED_SIZE (AGR_FIXED_SIZE +AGR_ROX_SIZE + AGR_END_SIZE)       // 固定长度

//#define	  AGR_LEN_POS       (AGR_FIXED_SIZE - 2)     //数据长度的位置


#define	  RETURN_SUCCESS_POS       0     //数据长度的位置
#define	  RETURN_SUCCESS_SIZE      2     //数据长度

#define	  RETURN_ERR_POS           RETURN_SUCCESS_SIZE     //数据长度的位置
#define	  RETURN_ERR_SIZE          4     //数据长度

/**********************************************************
//变量定义。
**********************************************************/

extern  uint32_t   comidx;    //串口接收数据个数
extern  u8   endcount;    //结束标志  ~  计数

extern  u8   endcount_4g;    //结束标志  ~  计数
extern  uint8_t   combuff[]; 

extern  uint32_t  Data_length;                                         //数据长度

extern  uint8_t   communication_data[];   //通讯缓冲区
/**********************************************************
//外部函数声明
**********************************************************/
void ProcessRS485(void);    ////处理485通讯

void Process_com_data(void);  //命令数据处理

void InitCombuff(void);     //初始化串口通讯缓冲区

void Send_ReyurnGETCommand_Value( uint8_t *data ,uint16_t len );

void EchoCommand(uint8_t *data , uint8_t len);     //回写命令。

void SetWhiteGroupName(void);
void ClearWhiteName(void);

void TEST_GQ(void);

void Send_Power_Signal(void);

void AutoUP_GPS_Information(void);  //自动上报GPS信息

void Network_Synchronization_Time(void);   //网络同步时间命令

#endif


