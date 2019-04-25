#ifndef	__HEARTBEAT_H__
#define	__HEARTBEAT_H__

#include "sys.h"

/**********************************************************
//�ⲿ��������
**********************************************************/

typedef struct
{
	
	uint8_t       flag ; 		  //��������
	uint16_t      count ; 	  //����ֵ
	uint8_t       err ;	      //������
	uint8_t       errtype ;	  //����ֵ
	uint8_t       reverse ;		//Ԥ��
	uint8_t       reverse2;		//Ԥ��2

} KT_CYCLE_INFO;



extern  KT_CYCLE_INFO   kt_beat_info ;


/**********************************************************
//�ⲿ��������
**********************************************************/


void  Init_Heartbeat(void);                            //��������������ʼ��
void  Heartbeat_Send(uint8_t  stype);                 //��������	


#endif
