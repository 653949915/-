#ifndef	__UPLOAD_H__
#define	__UPLOAD_H__


#include  "sys.h"

//#define KEY_SIZE 20

/**********************************************************
//�ⲿ��������
**********************************************************/

	
//extern u8  showStandby;//��ʾ����
//extern u32 Standbycount;//����ʾ����ʱ��ʱ����

//extern u8 showtime;//��ʾʱ��
//extern u32 timecount;//����ʾʱ��ʱ��ʱ����

//extern u32 keyidx;//�ַ����ո���
//extern u8 keybuff[];//���յ��ַ�



//extern u32 key;      //����ֵ

extern  uint8_t updatareturnfalg  ;  //ʵʱ�ϴ����ر�־

extern  u16  upOverTimeCnt;          //��ʱ�˳�����

extern  u8   Server_Returndata[];                //���������ص�����

extern  u8   Card_Markok;                          //��ˢ���ı��

extern  u8   Local_Check_Card_falg;                          //���ؼ�鿨Ȩ�ޱ�־

extern  u8   Offline_Online_falg;                      //����ʱ����-���߱�־ 
/**********************************************************
//�ⲿ��������
**********************************************************/


void  ProcessReal_time_upload(void);


#endif
