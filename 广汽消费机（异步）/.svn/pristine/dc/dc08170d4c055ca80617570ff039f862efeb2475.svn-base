#ifndef	__BC95_CONFIG_H__
#define	__BC95_CONFIG_H__

#include "sys.h"
#include "EC20fun.h"



#define EDP_MallocBuffer	malloc

#define EDP_FreeBuffer		free
/*--------------------------------内存分配方案标志--------------------------------*/
#define MEM_FLAG_NULL		0
#define MEM_FLAG_ALLOC		1
#define MEM_FLAG_STATIC		2


/* 命令响应 */

#define CMDRESP  0xF3

typedef struct Buffer
{
	uint8_t	*_data;		//协议数据
	
	uint32_t	_len;		//写入的数据长度
	
	uint32_t	_size;		//缓存总大小
	
	uint8_t	_memFlag;	//内存使用的方案：0-未分配	1-使用的动态分配		2-使用的固定内存
	
} EDP_PACKET_STRUCTURE;


typedef struct 
{
	uint8_t	  *data;		      //协议数据
	
	uint8_t	  Code_type;		//代码类型
	
	uint8_t	  TLV_type;		  //参数类型 
	
	uint16_t	len;	      //数据长度
	
} BC95_USER_DATATURE;


extern BC95_USER_DATATURE   bc95_cmduser_data;

extern KT_DEVICE_INFO   bc95_device_info;

void ProcessNB_Commu(void);  

void  BC95_User_Send_DATA(uint8_t Code_type, uint8_t TLV_type , uint8_t  *data , uint16_t len);

void  User_Reports_Message_Send(uint8_t *data, uint16_t len);

void  User_Control_Command_Send(uint8_t *data, uint16_t len);

void Nettime_Tran(void);                                   //时间戳转换



#endif
