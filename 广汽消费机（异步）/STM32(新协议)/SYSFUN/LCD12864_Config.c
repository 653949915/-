#include "Head.h"

#include "LCD12864_Config.h"

u8  Show_moneybuf[20]={0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X20,0X20,0X20,0X20,0X20,0X20};  //���ѽ��

uint8_t LCDtimebuf[16]={0};

uint32_t  Display_Time_outcount = 0 ;


/****************�رմ�����ʾ*******************/
void  Clear_Standby_Display(void)
{
	showStandby=0;          //�رմ�����ʾ

	Standbycount=0;

}


/****************�رմ�����ʾ*******************/
void  Clear_Standby_Display_Time(uint32_t count)
{
	
	
	showStandby=0;          //�رմ�����ʾ

	Standbycount = SECOND_CYCLE*count;

//	statuscnt = count;
	
	Show_Refresh_coun =SECOND_CYCLE*count;
	
  Standbytime = SECOND_CYCLE*count;
	
}






/****************�������ˢ������*******************/
void  EndClear_Pay_Card_Data(void)
{
//	memset(ICcard_frequencybf ,0,2);         //������0
	
//	memset(blk0+8 ,0,8);         //������0
	
	
	
}











