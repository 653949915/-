#include "Head.h"

#include "Heartbeat.h"


KT_CYCLE_INFO   kt_beat_info = {0, 0, 0, 0, 0, 0};

//发送心跳变量初始化
void Init_Heartbeat(void)
	{
		kt_beat_info.flag =1;
		kt_beat_info.count =0;
		kt_beat_info.err =0; 
		
	}

	
//发送心跳	
void  Heartbeat_Send(uint8_t  stype)
{

	u8 Heartbeatbuf[]={  0x2A,0x18,0x04,0x18,0x00,0x01,0x51,0x05,0x07,0x01,
		                      0xA1,0x36,0x00,0x04,0X2A,0X51,0X05,0X07,0xEE,0xFF,
		                      0xFF,0xFF,0xFF,0x7E,0x7E,0x7E	};
	
		MyStrCPY(Heartbeatbuf + AGR_MACH_POS, machno, MACH_SIZE);//机号		
													
		MyStrCPY(Heartbeatbuf + AGR_DATA_POS, machno, MACH_SIZE);//记录
		  
	  Heartbeatbuf[AGR_ROX_POS + MACH_SIZE -1] = GetXOR(Heartbeatbuf + AGR_DATA_POS, MACH_SIZE);//xor检验位
	
  //  Heartbeatbuf[10] =0xA0|stype;
													
		if   ((COMM_MODE>>0)&0x01)			
		{
			Heartbeatbuf[10] =0xA1;
			RS485_Send_Data(Heartbeatbuf, AGR_MAXEND_POS + MACH_SIZE);		
		}
		 if  ((COMM_MODE>>1)&0x01)
		{
			Heartbeatbuf[10] =0xA2;
			Write_SOCK_Data_Buffer(1,Heartbeatbuf, AGR_MAXEND_POS + MACH_SIZE);
		}
		 if  ((COMM_MODE>>2)&0x01)
		{
			Heartbeatbuf[10] =0xA3;
			Write_SOCK_Data_Buffer(0,Heartbeatbuf, AGR_MAXEND_POS + MACH_SIZE);
		}
		 if  ((COMM_MODE>>3)&0x01)
		{
			Heartbeatbuf[10] =0xA4;
			EC20_SendString(Heartbeatbuf, AGR_MAXEND_POS + MACH_SIZE);
		}

}
	














