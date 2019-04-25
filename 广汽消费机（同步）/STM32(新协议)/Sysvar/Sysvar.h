#ifndef	__SYSVAR_H__
#define	__SYSVAR_H__
#include "sys.h"	


/**********************************************************
//�ⲿ��������
**********************************************************/

	
extern u8  showStandby;//��ʾ����
extern u32 Standbycount;//����ʾ����ʱ��ʱ����
extern u32 Standbytime ;//����������ʱ��


extern u8 showtime;//��ʾʱ��
extern u32 timecount;//����ʾʱ��ʱ��ʱ����

extern u8 sys_status; //��������״̬
extern u32 statuscnt; //״̬��ʱ������


extern u8 keyVal;      //����ֵ

extern u8 cycle;     //״̬��������


extern u32 output1state ;    //����״̬
extern u32 output1time ;     //�˳����ż���

extern u32 output2state ;    //����״̬
extern u32 output2time ;     //�˳����ż���


extern u32 badd; //���ӿ�
extern u32 bdel; //ɾ����

extern u8  idbuff[];
extern u8  ICidbuff[];

extern volatile u32  inPCOM;    //�������ݴ���״̬


extern  u8  sysvar[];      //ϵͳ����
extern  u8  extvar[];      //��չ����
extern  u8  repea_time[];  //ˢ����ʱ
extern  u8  output_time[]; //�̵��������ʱ
extern  u8  whiteallow[];  //�������Ƿ��� 
extern  u8  interval_time[];    //���������ʱ

extern u16  Show_Refresh_coun ;    //��ʾˢ�¼��� 

extern  u8 meumflag;

extern  u8  Check_the_balance ;    //��ѯ���״̬

extern  u8  refund_the_balance ;   //��ˢ�˿�״̬

/**********************************************************
//����״̬
**********************************************************/
#define NORMAL_STATUS		      0x01 //����״̬
#define IN_SET_STATUS		      0x02 //���״̬

#define KEY_KEY_STATUS		    0x03 //����״̬
#define KEY_PLUS_STATUS		    0x04 //+ ��״̬

#define IN_CONSUMPT_STATUS		0x05 //����״̬

#define IN_MENU_STATUS		    0x06 //�˵�״̬
#define IN_FUN_STATUS		      0x07 //����״̬
#define IN_QUERY_STATUS		    0x08 //��ѯ״̬
#define IN_REFUND_STATUS		  0x09 //�˿�״̬ 


#define CALL_SHOW_STATUS	0x04 //������ʾ
#define IN_FIND_STATUS		0x08 //�����ѯ
#define OUT_FIND_STATUS		0x10 //������ѯ



#define KEY_ASTERISK			 11 //*
#define KEY_POUND				   12 //#

#define KEY_SET				     13 //�˵�
#define KEY_FUNCTION		   18 //��ӡ
#define KEY_QUERY		       19 //��ѯ
#define KEY_CONFIRM		     16 //ȷ��

#define KEY_CLEAN		       17 //���
#define KEY_UPTURN		     14 //�Ϸ�
#define KEY_DOWNTURN		   15 //�·�

#define KEY_PLUS		       KEY_POUND // +
#define KEY_SPOT		       KEY_ASTERISK // .
#define KEY_MENU		       13 //�˵�


#define KEY_END		   50 //ȷ��#
#define	KEY_EXIT			5 //������λ

#define OPEN_REL1()				  RELAY1 = 0    //�򿪼̵���1
#define CLOSE_REL1()				RELAY1 = 1    //�رռ̵���1

#define OPEN_REL2()				  RELAY2 = 0    //�򿪼̵���2
#define CLOSE_REL2()				RELAY2 = 1    //�رռ̵���2
/**********************************************************
//��ʱ����ʱ���
**********************************************************/
#define DELAY_MS		   100  //��ʱ��ÿ�ζ�ʱ100ms
#define SECOND_CYCLE	(1000 / DELAY_MS) //ÿ��ѭ������
#define MINUTE_CYCLE	(SECOND_CYCLE * 60L) //ÿ����ѭ������

/**********************************************************
//COMͨѶ���
**********************************************************/
#define	COM_START		0x2A // = '*'����ʼλ
#define	COM_END			0x7E // = '~'��ֹͣλ
#define	COM_SIZE		2048 //ͨѶ���ݳ���
#define	COM_REC			0 //485����
#define	COM_SEND		1 //485����


/**********************************************************
//����ṹ
**********************************************************/
union TwoByte //�ߵ� �͸�
{
	uint32_t  i;
	u8 c[2];
}; 



union FourByte //�ߵ͵͸ߣ����磺ic4.i=0x01020304; ic4.c[0]=0x01 ... ic4.c[3]=0x04
{
	uint32_t i;
	u8 c[4];
}; 	


union EightByte //�ߵ͵͸ߣ����磺ic4.i=0x01020304; ic4.c[0]=0x01 ... ic4.c[3]=0x04
{
	uint32_t i;
	u8 c[8];
}; 	




/**********************************************************
//�ⲿ��������
**********************************************************/


void AnalyzeWorkStatus(void);//����״̬����
void InitOutput(void);   //��ʼ�����
void BeginOutput1(void);  //�̵���1��ʼ���
void EndOutput1(void);    //�̵���1�������

void BeginOutput2(void);  //�̵���2��ʼ���
void EndOutput2(void);    //�̵���2�������

void CheckInit(void);    //����ʼ��
void Get_ChipInfo(void); //��ȡоƬ����

#endif
