#ifndef	__WG1_H__
#define	__WG1_H__
#include "sys.h" 
/**********************************************************
//�ⲿ��������
**********************************************************/
#define WG1_COUNT			34
#define WG1_CARD_SIZE		((WG1_COUNT - 2) / 8)
#define WG1_INIT_CYCLE		3 //(SECOND_CYCLE / 2)


#define WG1_DATA0 PCin(0)// PC0
#define WG1_DATA1 PCin(1)// PC1


extern u8 wg1idx;
extern u8 wg1cycle;

/**********************************************************
//�ⲿ��������

**********************************************************/

void InitWG1(void);
u32 ProcessWG1(void);

void EXTIX_Init_WG1(void);//�ⲿ�жϳ�ʼ��		
#endif
