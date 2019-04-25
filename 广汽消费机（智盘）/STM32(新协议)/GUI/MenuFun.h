#ifndef	__MENUFUN_H__
#define	__MENUFUN_H__

#include "sys.h"


#define    MAIN_MENU_MODE       0X01      //���˵�ģʽ
#define    MAIN_SUB_MODE        0X02      //�Ӳ˵�ģʽ






/*�������˵���ȣ��Լ����˵�����*/
#define  MMENU_WIDTH            20    
#define  MMENU_NO               12

/*�����Ӳ˵���ȣ��Լ����˵�����*/
#define  SMENU_WIDTH            20    
#define  SMENU_NO               8

/**********************************************************
//�ⲿ��������
**********************************************************/

typedef struct
{
  uint8_t  mmenu_no;    //��Ӧ���˵����
	
	uint8_t  no;          //�Ӳ˵�����

	uint8_t  stste;       //��ѡ����Ӳ˵���

	uint8_t  a;          //����

	uint8_t  b;          //����

	uint8_t  c;          //����
	
	
}SMENU;



//extern  uint8_t  MenuIcobuf[8][20];
//	
//extern	uint8_t  MenuUserbuf[8][20];
//	
//extern	uint8_t  MenuCommbuf[8][30];

extern  uint8_t  Mmenu_NUM ;       //���˵����

extern  uint8_t  Mmenu_Shou_Mode ;       //�˵���ʾģʽ

extern  uint8_t  Smenu_Shou_NUM ;        //�Ӳ˵����

extern  uint8_t  Menu_Fun_NUM;           //���ܲ˵����

extern  uint8_t  Shou_Selection_box ;    //ѡ���
/**********************************************************
//�ⲿ��������
**********************************************************/

extern   SMENU   SmenuUse;
extern   SMENU   SmenuComm;
extern   SMENU   SmenuSys;
extern   SMENU   SmenuData;
extern   SMENU   SmenuConsume;
extern   SMENU   SmenuAccess;
extern   SMENU   SmenuDrive;
extern   SMENU   SmenuAuto;
extern   SMENU   SmenuSysInfo;



void   Show_Menudata(void);



#endif
