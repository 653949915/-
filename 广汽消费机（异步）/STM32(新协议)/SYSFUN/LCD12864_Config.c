#include "Head.h"

#include "LCD12864_Config.h"

u8  Show_moneybuf[20]={0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X20,0X20,0X20,0X20,0X20,0X20};  //消费金额

uint8_t LCDtimebuf[16]={0};

uint32_t  Display_Time_outcount = 0 ;


/****************关闭待机显示*******************/
void  Clear_Standby_Display(void)
{
	showStandby=0;          //关闭待机显示

	Standbycount=0;

}


/****************关闭待机显示*******************/
void  Clear_Standby_Display_Time(uint32_t count)
{
	
	
	showStandby=0;          //关闭待机显示

	Standbycount = SECOND_CYCLE*count;

//	statuscnt = count;
	
	Show_Refresh_coun =SECOND_CYCLE*count;
	
  Standbytime = SECOND_CYCLE*count;
	
}






/****************最终清除刷卡数据*******************/
void  EndClear_Pay_Card_Data(void)
{
//	memset(ICcard_frequencybf ,0,2);         //次数清0
	
//	memset(blk0+8 ,0,8);         //姓名清0
	
	
	
}











