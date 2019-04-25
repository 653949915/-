#include "Head.h"

 uint8_t   TcpClient_databuff[COM_SIZE];   //TcpClient通讯缓冲区

 uint8_t   TcpServer_databuff[COM_SIZE];   //TcpServer通讯缓冲区

 uint8_t   UDPClient_databuff[50];   //UDPClient通讯缓冲区




/**********************************************************
//初始化网络客户端缓冲区
**********************************************************/

void InitTcpClient(void)
{
 memset(TcpClient_databuff,0,sizeof(TcpClient_databuff));

}	


/**********************************************************
//网口TCP客服端通讯数据检验
**********************************************************/
u32 CheckTCPClientData(void)
{
	u8   DEF_MACHNO[] = {0X51,0X05,0X07,0X01};

  u8	 ch;
	
  Data_length =0;

	if (TcpClient_databuff[0] != '*') { return 0; }
	
	if (!MyStrEQ(TcpClient_databuff + 1, machno, 4) && 
		!MyStrEQ(TcpClient_databuff + 1, DEF_MACHNO, 4)) { return 0; }

	Data_length=separate_value_2_1(TcpClient_databuff+7);         	//2字节地址合并	
		//		printf("%ld",Data_length);
			
	ch = GetXOR(TcpClient_databuff + 9, Data_length );
		
	if (ch != TcpClient_databuff[Data_length + 9]) { return 0; }//异或检验

	return 1;

}

/**********************************************************
//处理网络通讯
**********************************************************/
void ProcessTCPClient(void)
{	
	if (!CheckTCPClientData()) { goto com_end; } //检查数据 
	
//	 memcpy( communication_data, TcpClient_databuff,sizeof(TcpClient_databuff));
				
	if (TcpClient_databuff[5]==0XA3)
	{
     memcpy( communication_data, TcpClient_databuff,sizeof(TcpClient_databuff));
		 Process_com_data();
		
		InitTcpClient();
		}
	
	com_end:
	  InitTcpClient(); 
}

/**********************************************************
//初始化网络服务端缓冲区
**********************************************************/

void InitTcpServer(void)
{
 memset(TcpServer_databuff,0,sizeof(TcpServer_databuff));

}	


/**********************************************************
//网口TCP服务端通讯数据检验
**********************************************************/
u32 CheckTCPServerData(void)
{
	u8   DEF_MACHNO[] = {0X51,0X05,0X07,0X01};

  u8	 ch;
	
  Data_length =0;

	if (TcpServer_databuff[0] != '*') { return 0; }
	
	if (!MyStrEQ(TcpServer_databuff + 1, machno, 4) && 
		!MyStrEQ(TcpServer_databuff + 1, DEF_MACHNO, 4)) { return 0; }

	Data_length=separate_value_2_1(TcpServer_databuff+7);         	//2字节地址合并		
			
//printf("%ld",Data_length);
		
	ch = GetXOR(TcpServer_databuff + 9, Data_length );
		
	if (ch != TcpServer_databuff[Data_length + 9]) { return 0; }//异或检验

	return 1;

}

/**********************************************************
//处理网络通讯
**********************************************************/
void ProcessTCPServer(void)
{	
	if (!CheckTCPServerData()) { goto com_end; } //检查数据 
	
//	 memcpy( communication_data, TcpClient_databuff,sizeof(TcpClient_databuff));
				
	if (TcpServer_databuff[5]==0XA2)
	{
     memcpy( communication_data, TcpServer_databuff,sizeof(TcpServer_databuff));
		 Process_com_data();
		
		InitTcpServer();
		}
	
	com_end:
	  InitTcpServer(); 
}


/**********************************************************
//处理网络UDP通讯
**********************************************************/
void ProcessUDPClient(void)
		{
     u8  UDPCHECK_SIZE = 15;
     u8  UDPCHECK_BUFF[] = "Are You Device?";
     u8  ConfigMsgUDPbuff[40]={0X7B};
     u8  testbuf[1]={0X7D};
		 
		//	UDPClient_databuff

		
	  if(MyStrEQ(UDPClient_databuff,UDPCHECK_BUFF,UDPCHECK_SIZE))
				{				
					
			  MyStrCPY(ConfigMsgUDPbuff+1,machno,4);
					
				MyStrCPY(ConfigMsgUDPbuff+5,ConfigMsg.mac,EEPROM_MSG_LEN);	           
							
			  MyStrCPY(ConfigMsgUDPbuff+5+EEPROM_MSG_LEN,MACH_TYPE,TYPE_SIZE);	
					
        MyStrCPY(ConfigMsgUDPbuff+23,testbuf,1);	
					
				sendto(SOCK_UDPS,ConfigMsgUDPbuff,24, remote_ip, remote_port);                /*W5500把接收到的数据发送给Remote*/
										
				}
			}
			
	




