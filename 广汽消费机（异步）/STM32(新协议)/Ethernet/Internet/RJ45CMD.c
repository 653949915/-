#include "Head.h"

 uint8_t   TcpClient_databuff[COM_SIZE];   //TcpClientͨѶ������

 uint8_t   TcpServer_databuff[COM_SIZE];   //TcpServerͨѶ������

 uint8_t   UDPClient_databuff[50];   //UDPClientͨѶ������




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
	
	if (!MyStrEQ(TcpClient_databuff + 1, machno, 4) && 
		!MyStrEQ(TcpClient_databuff + 1, DEF_MACHNO, 4)) { return 0; }

	Data_length=separate_value_2_1(TcpClient_databuff+7);         	//2�ֽڵ�ַ�ϲ�	
		//		printf("%ld",Data_length);
			
	ch = GetXOR(TcpClient_databuff + 9, Data_length );
		
	if (ch != TcpClient_databuff[Data_length + 9]) { return 0; }//������

	return 1;

}

/**********************************************************
//��������ͨѶ
**********************************************************/
void ProcessTCPClient(void)
{	
	if (!CheckTCPClientData()) { goto com_end; } //������� 
	
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
	
	if (!MyStrEQ(TcpServer_databuff + 1, machno, 4) && 
		!MyStrEQ(TcpServer_databuff + 1, DEF_MACHNO, 4)) { return 0; }

	Data_length=separate_value_2_1(TcpServer_databuff+7);         	//2�ֽڵ�ַ�ϲ�		
			
//printf("%ld",Data_length);
		
	ch = GetXOR(TcpServer_databuff + 9, Data_length );
		
	if (ch != TcpServer_databuff[Data_length + 9]) { return 0; }//������

	return 1;

}

/**********************************************************
//��������ͨѶ
**********************************************************/
void ProcessTCPServer(void)
{	
	if (!CheckTCPServerData()) { goto com_end; } //������� 
	
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
					
			  MyStrCPY(ConfigMsgUDPbuff+1,machno,4);
					
				MyStrCPY(ConfigMsgUDPbuff+5,ConfigMsg.mac,EEPROM_MSG_LEN);	           
							
			  MyStrCPY(ConfigMsgUDPbuff+5+EEPROM_MSG_LEN,MACH_TYPE,TYPE_SIZE);	
					
        MyStrCPY(ConfigMsgUDPbuff+23,testbuf,1);	
					
				sendto(SOCK_UDPS,ConfigMsgUDPbuff,24, remote_ip, remote_port);                /*W5500�ѽ��յ������ݷ��͸�Remote*/
										
				}
			}
			
	




