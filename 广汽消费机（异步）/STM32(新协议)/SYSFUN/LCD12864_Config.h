#ifndef	__LCD12864_CONFIG_H__
#define	__LCD12864_CONFIG_H__

#include "sys.h"


//#define KEY_SIZE 20

/**********************************************************
//�ⲿ��������
**********************************************************/


extern  u8  Show_moneybuf[];  //���ѽ��

extern  uint8_t LCDtimebuf[];

extern	uint8_t  num_lcd[];	

extern  uint32_t  Display_Time_outcount  ;
/**********************************************************
//�ⲿ��������
**********************************************************/

		/*************����ʱ��ʾʱ��************/
void LCD12864_Standby(void)	;

void LCD12864_ShowKeyValue(void);   //LCD12864 ��ʾ����

void LCD12864_ShowPlay_Card(uint8_t  type);       //	LCD12864 ��ʾˢ������

void  Clear_Standby_Display(void);   

void  Clear_Standby_Display_Time(uint32_t count);

void LCD12864_Show_NoNet(uint8_t  type);

void LCD12864_Show_Consump_Pattern(void);

void LCD_Disp_MenuMain(void);


#endif















