#ifndef	__CONSUM_CONFIG_H__
#define	__CONSUM_CONFIG_H__

#include "sys.h"

//#define KEY_SIZE 20

/**********************************************************
//�ⲿ��������
**********************************************************/

extern  uint8_t   Machine_category[] ;                   //�������

extern u8  UserBalance[];	  //�������
 
extern u8  Consum_Amount[] ;	  //���ѽ��
 
extern uint8_t	Fixed_consum_Moneybuf[];                    //��ֵ�۷�ʱ���
 
extern uint8_t	Fixed_consum_Timerbuf[];                    //��ֵ�۷�ʱ���	
 
extern uint8_t	 Carte_consum_Moneybuf[];            //�˵��۷ѽ��	
 
extern uint8_t	 Consum_TimerBit[];                   //����ʱ�α�־	��⵱ǰˢ��ʱ���Ƿ���ʱ����

extern union     EightByte  Consum_Allmoney;              //�����ܽ��

extern uint8_t   Sub_Maximum_Limitbuf[];              //���������޶�

extern uint8_t   RefundMoneybuf[] ;             //�˿���

extern uint8_t   RefundICcardbuf[] ;             //�˿��
/**********************************************************
//�ⲿ��������
**********************************************************/


void SaveMachine_Category(void);         //����������
void SaveFixed_consumption_Money(void);  //���涨ֵ�۷ѽ��
void SaveFixed_consumption_Timer(void);  //���涨ֵ�۷�ʱ��
void InitFixed_consumption_Money(void);  //��ʼ����ֵ�۷ѽ��
void InitFixed_consumption_Timer(void);  //��ʼ����ֵ�۷�ʱ��
void InitCarte_consum_Money(void);      //��ʼ���˵��۷ѽ��
void SaveCarte_consum_Money(void);      //����˵��۷ѽ��

void Consum_Time_Detection(void);       //����ʱ�μ��

void DeleteConsumption_All_Money(void); //��������ܶ�
void SaveConsumption_All_Money(void);   //���������ܶ�
void InitConsumption_All_Money(void);   //��ʼ�������ܶ�
void SaveSub_Maximum_Limit(void);      //���浱�������޶�
void InitSub_Maximum_Limit(void);      //��ʼ�����������޶�





#endif
