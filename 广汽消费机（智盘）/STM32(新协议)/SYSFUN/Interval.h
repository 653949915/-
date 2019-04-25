#ifndef	__INTERVAL_H__
#define	__INTERVAL_H__
#include "sys.h"				


/**********************************************************
//�������塣
**********************************************************/

extern  u32 btimeseg;             //ʱ�μ��ͨ����־

extern u32 bHoliday;              //�ڼ��ձ�־

extern u32 bChannel;              //ͨ��ʱ�α�־

extern u32 bHolitimeseg;          //�ڼ���ʱ�μ��ͨ����־

extern u8 Permission_Period[];    //�Ž�ʱ��Ȩ�޻�����

extern u8 Passage_Timebuff[];       //ͨ��ʱ�λ�����

extern u8 Holiday_Vacationsbuff[];       //�ڼ���ʱ�λ�����

extern u8 Permission_Periodbuff[];    //�Ž�ʱ��Ȩ��
//extern  u8   
//extern  u8   




/**********************************************************
//�ⲿ��������
**********************************************************/

void Time_Interval_Detection(void);         //����Ž�ʱ��

void HolidayTime_Interval_Detection(void);  //���ڼ���ʱ��

void Holiday_Detection(void);               //����Ƿ�ڼ���

void Channel_Time_Detection(void);          //���ͨ��ʱ��

void InitTime_Interval_Detection(void);     //��ʼ���Ž�ʱ��

void InitPassage_Time(void);                //��ʼ��ͨ��ʱ��

void InitPassage_TimeEnable(void);          //��ʼ��ͨ��ʹ��

void InitHoliday_Vacations(void);           //��ʼ���ڼ���

extern u8  Check_Passage_Enable(void);      //���ͨ��ʱ��ʹ��

#endif


