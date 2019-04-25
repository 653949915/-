#include "head.h"

 uint8_t   TcpClient_databuff[COM_SIZE];   //TcpClientͨѶ������

 uint8_t   TcpServer_databuff[COM_SIZE];   //TcpServerͨѶ������

 uint8_t   UDPClient_databuff[50];         //UDPClientͨѶ������

/**********************************************************
//��ʼ������ͻ��˻�����
**********************************************************/

void InitTcpClient(void)
{
 memset(TcpClient_databuff,0,sizeof(TcpClient_databuff));

}	


/**********************************************************
//����TCP�ͷ���ͨѶ���ݼ���
**********************************************************/
u32 CheckTCPClientData(void)
{
	u8   DEF_MACHNO[] = {0X51,0X05,0X07,0X01};

  u8	 ch;
	
  Data_length =0;

	if (TcpClient_databuff[0] != '*') { return 0; }
	
	if (!MyStrEQ(TcpClient_databuff + AGR_MACH_POS, machno, 4) && 
		!MyStrEQ(TcpClient_databuff + AGR_MACH_POS, DEF_MACHNO, 4)) { return 0; }

	Data_length=separate_value_2_1(TcpClient_databuff+AGR_LEN_POS);         	//2�ֽڵ�ַ�ϲ�	
		//		printf("%ld",Data_length);
			
	ch = GetXOR(TcpClient_databuff + AGR_DATA_POS, Data_length );
		
	if (ch != TcpClient_databuff[Data_length + AGR_DATA_POS]) { return 0; }//������

	return 1;

}

/**********************************************************
//��������ͨѶ
**********************************************************/
void ProcessTCPClient(void)
{	
	if (!CheckTCPClientData()) { goto com_end; } //������� 
	
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
//��ʼ���������˻�����
**********************************************************/

void InitTcpServer(void)
{
 memset(TcpServer_databuff,0,sizeof(TcpServer_databuff));

}	


/**********************************************************
//����TCP�����ͨѶ���ݼ���
**********************************************************/
u32 CheckTCPServerData(void)
{
	u8   DEF_MACHNO[] = {0X51,0X05,0X07,0X01};

  u8	 ch;
	
  Data_length =0;

	if (TcpServer_databuff[0] != '*') { return 0; }
	
	if (!MyStrEQ(TcpServer_databuff + AGR_MACH_POS, machno, 4) && 
		!MyStrEQ(TcpServer_databuff + AGR_MACH_POS, DEF_MACHNO, 4)) { return 0; }

	Data_length=separate_value_2_1(TcpServer_databuff + AGR_LEN_POS);         	//2�ֽڵ�ַ�ϲ�		
			
//printf("%ld",Data_length);
		
	ch = GetXOR(TcpServer_databuff + AGR_DATA_POS, Data_length );
		
	if (ch != TcpServer_databuff[Data_length + AGR_DATA_POS]) { return 0; }//������

	return 1;

}

/**********************************************************
//��������ͨѶ
**********************************************************/
void ProcessTCPServer(void)
{	
	if (!CheckTCPServerData()) { goto com_end; } //������� 
	
//	 memcpy( communication_data, TcpClient_databuff,sizeof(TcpClient_databuff));
				
	if (TcpServer_databuff[AGR_TYPE_POS]==0XA2)
	{
     memcpy( communication_data, TcpServer_databuff,sizeof(TcpServer_databuff));
		
		 Process_com_data();    //����Server�յ�������
		
		//InitTcpServer();        //���Server�յ�������
		}
	
	com_end:
	  InitTcpServer(); 
}


/**********************************************************
//��������UDPͨѶ
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
					
			  MyStrCPY(ConfigMsgUDPbuff+1,machno,4);         //��������
					
				MyStrCPY(ConfigMsgUDPbuff+5,Phy_Addr,6);	     //����Mac��ַ       

        MyStrCPY(ConfigMsgUDPbuff+11,IP_Addr,4);	     //��������IP 

			  MyStrCPY(ConfigMsgUDPbuff+15,Sub_Mask,4);	     //������������ 
					
				MyStrCPY(ConfigMsgUDPbuff+19,Gateway_IP,4);	   //��������
																
        MyStrCPY(ConfigMsgUDPbuff+23,testbuf,1);	
//					
//				sendto(SOCK_UDPS,ConfigMsgUDPbuff,24, remote_ip, remote_port);                /*W5500�ѽ��յ������ݷ��͸�Remote*/
				Write_SOCK_Data_Buffer(2, ConfigMsgUDPbuff, 24);                  /*W5500�ѽ��յ������ݷ��͸�Remote*/
								
				}
		}
	

/**
*@brief		STM32ϵͳ��λ����
*@param		��
*@return	��
*/
void reboot(void)
{
  pFunction  Jump_To_Application;
  uint32_t JumpAddress;
 // printf(" ϵͳ�����С���\r\n");
  JumpAddress = *(vu32*) (0x00000004);
  Jump_To_Application = (pFunction) JumpAddress;
  Jump_To_Application();
}

		
/**
*@brief		��ʼ������IP���������롢����
*@param		��
*@return	��
*/

void InitLocalIPGateway(void)
		{
			u8  default_Local_ip[12]={192,168,0,245,255,255,255,0,192,168,0,1};										/*Ĭ�ϱ���IP*/

			u8  Local_ipbuff[12]={0};
			
      AT24CXX_Read(TCP_LOCAL_IP_POS,Local_ipbuff,12);

			/***���EEPROM��û��д��ֵ���Ǿ���Ĭ��ֵ****/
    if(( Local_ipbuff[0]==0xFF)&&( Local_ipbuff[1]==0xFF)&&( Local_ipbuff[2]==0xFF)&&( Local_ipbuff[3]==0xFF)	)	
			{
			
					MyStrCPY(IP_Addr,default_Local_ip,4);	            //��������IP 

					MyStrCPY(Sub_Mask,default_Local_ip+4,4);	        //������������ 
						
					MyStrCPY(Gateway_IP,default_Local_ip+8,4);	       //��������	
			
			}
		else 
			{
					MyStrCPY(IP_Addr,Local_ipbuff,4);	       //��������IP 

					MyStrCPY(Sub_Mask,Local_ipbuff+4,4);	      //������������ 
						
					MyStrCPY(Gateway_IP,Local_ipbuff+8,4);	       //��������
								
			}
					
		}





	
/**
*@brief		��ʼ��Զ��IP�Ͷ˿ں�
*@param		��
*@return	��
*/

void InitRemoteIPandPORT(void)
		{
			u8  default_remote_ip[4]={192,168,0,101};										/*Զ��IP��ַ*/
      u8 default_remote_port[2]={0x13,0x88};											/*Զ�˶˿ں�*/
			
			u8 RemoteIPandPortbuff[6];
			
		  AT24CXX_Read(TCP_REMOTE_IPandPort_POS,RemoteIPandPortbuff,6);	  //24C512дIP
			
			/* ����������ǿհף���ʹ��Ĭ��IP�Ͷ˿�*/
			if((RemoteIPandPortbuff[0]==0XFF)&&(RemoteIPandPortbuff[1]==0XFF)&&(RemoteIPandPortbuff[2]==0XFF)&&(RemoteIPandPortbuff[3]==0XFF))
					{
						MyStrCPY(S0_DIP,default_remote_ip,4);                              //��������Զ��IP	
																					
						MyStrCPY(S0_DPort,default_remote_port,2);                              //��������Զ�˶˿�	
						
					}
					
					
					
			MyStrCPY(S0_DIP,RemoteIPandPortbuff,4);                              //��������Զ��IP	
										
//			turn_2_data(ic2.c,RemoteIPandPortbuff+4);                               //�ֽڵ�ת					
					
		  MyStrCPY(S0_DPort,RemoteIPandPortbuff+4,2);                              //��������Զ�˶˿�						
				
			
		}


				
/**
*@brief		��ʼ��Mac��ַ
*@param		��
*@return	��
*/

void Init_MAC_Address(void)
		{
			u8 default_mac[6]={0x00,0x08,0xdc,0x11,0x11,0x11};
			
			u8 MAC_Addressbuff[6]={0x00};
								
      AT24CXX_Read(TCP_THIS_MAC_POS,MAC_Addressbuff,6);	   //24C512��ȡMac��ַ
			
			if((MAC_Addressbuff[0]==0XFF)&&(MAC_Addressbuff[1]==0XFF)&&(MAC_Addressbuff[2]==0XFF)&&(MAC_Addressbuff[3]==0XFF)&&(MAC_Addressbuff[4]==0XFF)&&(MAC_Addressbuff[5]==0XFF))
			{			
				
				MyStrCPY(Phy_Addr,default_mac,6);                              //����Ĭ��Mac
			
			}
			
			else
				
			MyStrCPY(Phy_Addr,MAC_Addressbuff,6);                              //����EEPROM��Mac
						
		}
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		

