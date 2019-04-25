#include "Head.h"

#include "Volume.h"






/**********************************************************
//初始化音量大小
**********************************************************/

void InitVolume(void)
{
 
	uint8_t Volumebuf[2]={0};
	
	AT24CXX_Read( VOLUME_IDX  ,Volumebuf , 1);
	
}



/*
设置音量
*/
void SET_Volume(uint8_t *Val)
{
	uint8_t  valbuf[10]={0x00,0x30,0x31};
	
	uint8_t  valbuf1[5]={0x5b ,0x76 ,0x31,0x031,0x5d};
	
	
	
	if(Val[0] <5)
	{
		valbuf[0]	= Val[0] *2; 
		
	}
	else 
	{
	 valbuf[0] = 7 + Val[0] ; 
	
	}
	
	getDectoBCD(valbuf[0], valbuf, 1);
	
	HexToStr(valbuf+1,  valbuf,  1);
	
  MyStrCPY(valbuf1 +2, valbuf +1, 2);
	
//  RS485_Send_Data(valbuf1 ,5); 
	
	SYN6288_Send(SYN6288CMD_VOICE_PLAY ,SYN6288CMD_VOICE_PLAY , valbuf1 ,5);
	
	
	AT24CXX_Write1( VOLUME_IDX  ,Val , 1);
	
//	InitVolume();
}








