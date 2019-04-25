#ifndef	__HEARTBEAT_H__
#define	__HEARTBEAT_H__

#include "sys.h"

/**********************************************************
//外部变量声明
**********************************************************/

typedef struct
{
	
	uint8_t       flag ; 		  //计数类型
	uint16_t      count ; 	  //计数值
	uint8_t       err ;	      //错误数
	uint8_t       errtype ;	  //错误值
	uint8_t       reverse ;		//预留
	uint8_t       reverse2;		//预留2

} KT_CYCLE_INFO;



extern  KT_CYCLE_INFO   kt_beat_info ;


/**********************************************************
//外部函数声明
**********************************************************/


void  Init_Heartbeat(void);                            //发送心跳变量初始化
void  Heartbeat_Send(uint8_t  stype);                 //发送心跳	


#endif
