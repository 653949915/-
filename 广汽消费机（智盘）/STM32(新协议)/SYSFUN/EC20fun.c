#include "Head.h"

#include "EC20fun.h"

KT_DEVICE_INFO   ec20_device_info = {0, 0, 0, 0, 0, 0, 0, 0, 0};


uint8_t  ec20_remoteipbuf[18]={0};     //远端IP端口


char *get4g_rebuff() 
	{
			return ( char *)&RxDataBuff;
	}

char *redata_4g;

	
//处理4G通讯

void Process4G_Commu(void)
	{
		u8   DEF_MACHNO[] = {0X51,0X05,0X07,0X01};
		u8	 ch;
			
		if(u1_Rec_Over_Flag == 0)
		 {
			return;
		 }	
		
		u1_Rec_Over_Flag =0;
		
		if(USART1_RX_CRLF)           //在收到 \r\n
		{
			redata_4g = get4g_rebuff(); 
			
			if(strstr(redata_4g,"RDY"))	               //检测到开机信息
			{
		//		AT_InterOverTimeCnt=10;
				
				ec20_device_info.initStep = INITSTEP_AT;
								
			//	AT_InterOverTimeCnt=10;
				
				Beep(2, SHORT_BEEP); 		
				return;
			}			
			if(strstr(redata_4g,"NO CARRIER"))	         //检测到服务器断线
			{
				ec20_device_info.initStep = INITSTEP_QICLOSE;
				ec20_device_info.netWork =0;
				
			
		//		QuectelEC20_Network_Init(2);       //重启
		//		Beep(3, SHORT_BEEP); 		
				return;
			}		
			InitEC20Combuff();
		}
    
		else     //非AT配置模式
		{
			if (endcount_4g < 3) return;
			
			endcount_4g = 0;
				
			if (g_u8RxIndexW < 10) { goto com_rst; }	

			if (RxDataBuff[0] != '*') { goto com_end ; }

			if (!MyStrEQ(RxDataBuff + AGR_MACH_POS, machno, 4) && 
				!MyStrEQ(RxDataBuff + AGR_MACH_POS, DEF_MACHNO, 4)) { goto com_end ; }
				
			Data_length=separate_value_2_1(RxDataBuff+AGR_LEN_POS);         	//2字节地址合并
				
			ch = GetXOR(RxDataBuff + AGR_DATA_POS, Data_length );          
				
			if (ch != RxDataBuff[Data_length + AGR_DATA_POS]) { goto com_end ; }//异或检验
						
			if (RxDataBuff[AGR_TYPE_POS]==0XA4)
			{
				 kt_beat_info.count=0;
				
				 memcpy(communication_data, RxDataBuff, RX_BUFF_LEN /*sizeof(RxDataBuff)*/);	
				
				 Process_com_data();
			
			//	 InitCombuff();
			}
				
			com_end:
				InitEC20Combuff();

			com_rst:
				inPCOM = 0;
		}
	}

/************************************************
4g远端IP端口初始化
***************************************************/

void Init_EC20_Remote_IP(void)
{

  AT24CXX_Read(TCP4G_REMOTE_IPandPort_POS,ec20_remoteipbuf,17);	                /*写远端IP端口号*/
  
	if((ec20_remoteipbuf[0]==0xff)&&(ec20_remoteipbuf[1]==0xff)&&(ec20_remoteipbuf[2]==0xff)&&(ec20_remoteipbuf[3]==0xff))
		{
      LoadnEC20DefaultValue();        //出厂值
		}
		else 
		{
			MyStrCPY(AT_QIOPEN_IP +21 , ec20_remoteipbuf,    3);//120
			MyStrCPY(AT_QIOPEN_IP +25 , ec20_remoteipbuf+3,  3);//078
			MyStrCPY(AT_QIOPEN_IP +29 , ec20_remoteipbuf+6,  3);//087
			MyStrCPY(AT_QIOPEN_IP +33,  ec20_remoteipbuf+9,  3);//149
			MyStrCPY(AT_QIOPEN_IP +38,  ec20_remoteipbuf+12, 5);//23232
		
		}
}















