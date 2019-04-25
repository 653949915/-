#ifndef	__WG2_H__
#define	__WG2_H__
#include "sys.h" 
/**********************************************************
//�ⲿ��������
**********************************************************/
#define WG2_COUNT			34
#define WG2_CARD_SIZE		((WG2_COUNT - 2) / 8)
#define WG2_INIT_CYCLE		3 //(SECOND_CYCLE / 2)


#define WG2_DATA0 PCin(2)// PC2
#define WG2_DATA1 PCin(3)// PC3


extern u8 wg2idx;
extern u8 wg2cycle;

/**********************************************************
//�ⲿ��������

**********************************************************/

void InitWG2(void);
u32 ProcessWG2(void);

void EXTIX_Init_WG2(void);//�ⲿ�жϳ�ʼ��		
#endif
