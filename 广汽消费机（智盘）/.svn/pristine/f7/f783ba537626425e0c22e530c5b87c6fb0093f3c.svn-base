#include "head.h"

 uint8_t   TcpClient_databuff[COM_SIZE];   //TcpClient通讯缓冲区

 uint8_t   TcpServer_databuff[COM_SIZE];   //TcpServer通讯缓冲区

 uint8_t   UDPClient_databuff[50];         //UDPClient通讯缓冲区

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
	
	if (!MyStrEQ(TcpClient_databuff + AGR_MACH_POS, machno, 4) && 
		!MyStrEQ(TcpClient_databuff + AGR_MACH_POS, DEF_MACHNO, 4)) { return 0; }

	Data_length=separate_value_2_1(TcpClient_databuff+AGR_LEN_POS);         	//2字节地址合并	
		//		printf("%ld",Data_length);
			
	ch = GetXOR(TcpClient_databuff + AGR_DATA_POS, Data_length );
		
	if (ch != TcpClient_databuff[Data_length + AGR_DATA_POS]) { return 0; }//异或检验

	return 1;

}

/**********************************************************
//处理网络通讯
**********************************************************/
void ProcessTCPClient(void)
{	
	if (!CheckTCPClientData()) { goto com_end; } //检查数据 
	
//	 memcpy( communication_data, TcpClient_databuff,sizeof(TcpClient_databuff));
				
	if (TcpClient_databuff[AGR_TYPE_POS]==0XA3)
	{
     memcpy( communication_data, TcpClient_databuff,sizeof(TcpClient_databuff));
		 Process_com_data();
		
		//InitTcpClient();
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
	
	if (!MyStrEQ(TcpServer_databuff + AGR_MACH_POS, machno, 4) && 
		!MyStrEQ(TcpServer_databuff + AGR_MACH_POS, DEF_MACHNO, 4)) { return 0; }

	Data_length=separate_value_2_1(TcpServer_databuff + AGR_LEN_POS);         	//2字节地址合并		
			
//printf("%ld",Data_length);
		
	ch = GetXOR(TcpServer_databuff + AGR_DATA_POS, Data_length );
		
	if (ch != TcpServer_databuff[Data_length + AGR_DATA_POS]) { return 0; }//异或检验

	return 1;

}

/**********************************************************
//处理网络通讯
**********************************************************/
void ProcessTCPServer(void)
{	
	if (!CheckTCPServerData()) { goto com_end; } //检查数据 
	
//	 memcpy( communication_data, TcpClient_databuff,sizeof(TcpClient_databuff));
				
	if (TcpServer_databuff[AGR_TYPE_POS]==0XA2)
	{
     memcpy( communication_data, TcpServer_databuff,sizeof(TcpServer_databuff));
		
		 Process_com_data();    //处理Server收到的数据
		
		//InitTcpServer();        //清空Server收到的数据
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
					
			  MyStrCPY(ConfigMsgUDPbuff+1,machno,4);         //拷贝机号
					
				MyStrCPY(ConfigMsgUDPbuff+5,Phy_Addr,6);	     //拷贝Mac地址       

        MyStrCPY(ConfigMsgUDPbuff+11,IP_Addr,4);	     //拷贝本地IP 

			  MyStrCPY(ConfigMsgUDPbuff+15,Sub_Mask,4);	     //拷贝子网掩码 
					
				MyStrCPY(ConfigMsgUDPbuff+19,Gateway_IP,4);	   //拷贝网关
																
        MyStrCPY(ConfigMsgUDPbuff+23,testbuf,1);	
//					
//				sendto(SOCK_UDPS,ConfigMsgUDPbuff,24, remote_ip, remote_port);                /*W5500把接收到的数据发送给Remote*/
				Write_SOCK_Data_Buffer(2, ConfigMsgUDPbuff, 24);                  /*W5500把接收到的数据发送给Remote*/
								
				}
		}
	

/**
*@brief		STM32系统软复位函数
*@param		无
*@return	无
*/
void reboot(void)
{
  pFunction  Jump_To_Application;
  uint32_t JumpAddress;
 // printf(" 系统重启中……\r\n");
  JumpAddress = *(vu32*) (0x00000004);
  Jump_To_Application = (pFunction) JumpAddress;
  Jump_To_Application();
}

		
/**
*@brief		初始化本地IP、子网掩码、网关
*@param		无
*@return	无
*/

void InitLocalIPGateway(void)
		{
			u8  default_Local_ip[12]={192,168,0,245,255,255,255,0,192,168,0,1};										/*默认本地IP*/

			u8  Local_ipbuff[12]={0};
			
      AT24CXX_Read(TCP_LOCAL_IP_POS,Local_ipbuff,12);

			/***如果EEPROM中没有写入值，那就用默认值****/
    if(( Local_ipbuff[0]==0xFF)&&( Local_ipbuff[1]==0xFF)&&( Local_ipbuff[2]==0xFF)&&( Local_ipbuff[3]==0xFF)	)	
			{
			
					MyStrCPY(IP_Addr,default_Local_ip,4);	            //拷贝本地IP 

					MyStrCPY(Sub_Mask,default_Local_ip+4,4);	        //拷贝子网掩码 
						
					MyStrCPY(Gateway_IP,default_Local_ip+8,4);	       //拷贝网关	
			
			}
		else 
			{
					MyStrCPY(IP_Addr,Local_ipbuff,4);	       //拷贝本地IP 

					MyStrCPY(Sub_Mask,Local_ipbuff+4,4);	      //拷贝子网掩码 
						
					MyStrCPY(Gateway_IP,Local_ipbuff+8,4);	       //拷贝网关
								
			}
					
		}





	
/**
*@brief		初始化远端IP和端口号
*@param		无
*@return	无
*/

void InitRemoteIPandPORT(void)
		{
			u8  default_remote_ip[4]={192,168,0,101};										/*远端IP地址*/
      u8 default_remote_port[2]={0x13,0x88};											/*远端端口号*/
			
			u8 RemoteIPandPortbuff[6];
			
		  AT24CXX_Read(TCP_REMOTE_IPandPort_POS,RemoteIPandPortbuff,6);	  //24C512写IP
			
			/* 如果读出来是空白，则使用默认IP和端口*/
			if((RemoteIPandPortbuff[0]==0XFF)&&(RemoteIPandPortbuff[1]==0XFF)&&(RemoteIPandPortbuff[2]==0XFF)&&(RemoteIPandPortbuff[3]==0XFF))
					{
						MyStrCPY(S0_DIP,default_remote_ip,4);                              //拷贝设置远端IP	
																					
						MyStrCPY(S0_DPort,default_remote_port,2);                              //拷贝设置远端端口	
						
					}
					
					
					
			MyStrCPY(S0_DIP,RemoteIPandPortbuff,4);                              //拷贝设置远端IP	
										
//			turn_2_data(ic2.c,RemoteIPandPortbuff+4);                               //字节调转					
					
		  MyStrCPY(S0_DPort,RemoteIPandPortbuff+4,2);                              //拷贝设置远端端口						
				
			
		}


				
/**
*@brief		初始化Mac地址
*@param		无
*@return	无
*/

void Init_MAC_Address(void)
		{
			u8 default_mac[6]={0x00,0x08,0xdc,0x11,0x11,0x11};
			
			u8 MAC_Addressbuff[6]={0x00};
								
      AT24CXX_Read(TCP_THIS_MAC_POS,MAC_Addressbuff,6);	   //24C512读取Mac地址
			
			if((MAC_Addressbuff[0]==0XFF)&&(MAC_Addressbuff[1]==0XFF)&&(MAC_Addressbuff[2]==0XFF)&&(MAC_Addressbuff[3]==0XFF)&&(MAC_Addressbuff[4]==0XFF)&&(MAC_Addressbuff[5]==0XFF))
			{			
				
				MyStrCPY(Phy_Addr,default_mac,6);                              //拷贝默认Mac
			
			}
			
			else
				
			MyStrCPY(Phy_Addr,MAC_Addressbuff,6);                              //拷贝EEPROM的Mac
						
		}
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		

