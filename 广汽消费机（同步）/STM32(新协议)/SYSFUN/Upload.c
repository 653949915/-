#include "Head.h"

#include "Upload.h"



u8  UP_UserBalance[4]={0X00,0X00,0X00,0X00};	  //�������
 
u8  UP_Consum_Amount[4] ={0X00,0X00,0X00,0X00};	  //���ѽ��

u8   Server_Returndata[30]={0};                //���������ص�����

u8  UP_defNOnetBalance[4]={0X38,0X90,0X0D,0X00};	  //������ʱĬ�����     //��λ��ǰ

u8  UP_defNOretBalance[4]={0X88,0X88,0X88,0X88};	  //������ʱĬ�����     //��λ��ǰ

u8  UP_defNOcardBalance[4]={0X00,0X00,0X00,0X00};	  //��IC��ʱĬ�����

uint8_t updatareturnfalg =0 ;  //ʵʱ�ϴ����ر�־

u16  upOverTimeCnt=0;                        //��ʱ�˳�����

u8   Card_Markok=0;                          //��ˢ���ı��

u8   Local_Check_Card_falg=0;                //���ؼ�鿨Ȩ�ޱ�־

u8   Offline_Online_falg=0;                      //����ʱ����-���߱�־ 

/*********************************************

����ʵʱ�ϴ�����

**********************************************/
void  ProcessReal_time_upload(void)
{
//	uint8_t  i =0;
#ifdef   WISDOM_PLATE     //������
	
uint8_t	WP_Pay_Carderr_Code =0;         //���ظ����̵Ĵ������         
	
#endif		
	
	
  if(Card_Markok ==0)      //���û��ˢ�� ֱ�ӷ���
	{
		
		return ;

	}
	
	if(Pay_Carderr_Code!=0)
	{
	 goto  play_card;
	}

	
	Local_Check_Card_falg=0;          //����У��
	
	if(ec20_device_info.netWork)   //������
	{	

		if((updatareturnfalg ==0)&&(upOverTimeCnt))     //δ�յ����������ػ��߳�ʱ
				{
					return ;
				}	
				
		if(updatareturnfalg)    //�������з���
			{
				
	//			RS485_Send_Data(Server_Returndata,	30);
	/*********************************  �������������ص�����		****************************************/	

				DelUPloadRecord(Server_Returndata);     //ɾ��ʵʱδ�ϴ�����
				
		    MyStrCPY(idbuff, Server_Returndata +4, CARD_SIZE);       //��������
				
				MyStrCPY(UserBalance, Server_Returndata +12, CARD_SIZE);        //�����������

		    MyStrCPY(Consum_Amount, Server_Returndata +8, CARD_SIZE);       //�������ѽ��
	
				MyStrCPY(recorddata + 26, Server_Returndata, 4);           //��ˮ��    4�ֽ�				
				
				MyStrCPY(recorddata + 25, recorddataup + 25, 1);           //ͨѶ����    1�ֽ�					
				
				Pay_Carderr_Code  =  Server_Returndata[17];      //���ش�����븳ֵ
				
				Offline_Online_falg =1;
							
			}
		else                           //�������޷���
			{			
				Offline_Online_falg =0;
				
					MyStrCPY(recorddata + 4, recorddataup +4, 4);                //���� 4�ֽ�
					MyStrCPY(recorddata + 26, recorddataup + 26, 4);           //��ˮ��    4�ֽ�
	        MyStrCPY(recorddata + 24, recorddataup + 24 , 1);          //��ͷ��   1�ֽ�				
				  MyStrCPY(recorddata + 25, recorddataup + 25, 1);           //ͨѶ����    1�ֽ�			
				
				
				if(GetWorkStatus(IN_CONSUMPT_STATUS))        //����״̬����ͨ��
					{
						
						MyStrCPY(Consum_Amount, keymoneybuff, CARD_SIZE);        //���������Ľ��

				    MyStrCPY(UserBalance, UP_defNOretBalance, CARD_SIZE);       //����Ĭ�ϵĽ��	ffff
											
						Local_Check_Card_falg=1;    //���ؼ��ˢ��Ȩ��
					}
				else if	(Machine_category[0] != 0x01)//��ֵ�۷� 
				{
						MyStrCPY(Consum_Amount +2, Fixed_consum_Moneybuf +Consum_TimerBit[1]*2, 2);        //������ֵ�Ľ��

				    MyStrCPY(UserBalance, UP_defNOretBalance, CARD_SIZE);       //����Ĭ�ϵĽ��	ffff
											
						Local_Check_Card_falg=1;    //���ؼ��ˢ��Ȩ��
				
				}			

				else if	(Machine_category[0] != 0x02)//�ƴο۷� 
				{
						MyStrCPY(Consum_Amount , UP_defNOcardBalance, CARD_SIZE);        //�����ƴεĽ��

				    MyStrCPY(UserBalance, UP_defNOretBalance, CARD_SIZE);       //����Ĭ�ϵĽ��	ffff
											
						Local_Check_Card_falg=1;    //���ؼ��ˢ��Ȩ��				
				}				
				else    //������״̬��ʾ����
				{
						Pay_Carderr_Code = SYS_NET_CONNECT_FAIL;   //������
					
				}	


				
			}					
	}		
	else        //������
	{
		Offline_Online_falg =0;
		
		MyStrCPY(recorddata + 4, recorddataup +4, 4);                //���� 4�ֽ�
		MyStrCPY(recorddata + 26, recorddataup + 26, 4);           //��ˮ��    4�ֽ�
		MyStrCPY(recorddata + 24, recorddataup + 24 , 1);          //��ͷ��   1�ֽ�				
		MyStrCPY(recorddata + 25, recorddataup + 25, 1);           //ͨѶ����    1�ֽ�	
		
		if(GetWorkStatus(IN_CONSUMPT_STATUS))        //����״̬ ����ͨ��
			{	
				
				MyStrCPY(UserBalance,   UP_defNOretBalance, CARD_SIZE);        //����Ĭ�ϵĽ��	1234

				MyStrCPY(Consum_Amount, keymoneybuff, CARD_SIZE);              // ���������Ľ��
				  
				Local_Check_Card_falg=1;    //���ؼ��ˢ��Ȩ��
			}
		else if	(Machine_category[0] != 0x01)//��ֵ�۷� 
		{
				MyStrCPY(Consum_Amount+2, Fixed_consum_Moneybuf +Consum_TimerBit[1]*2, 2);        //������ֵ�Ľ��

				MyStrCPY(UserBalance, UP_defNOretBalance, CARD_SIZE);       //����Ĭ�ϵĽ��	ffff
									
				Local_Check_Card_falg=1;    //���ؼ��ˢ��Ȩ��		
		}			
			
		else if	(Machine_category[0] != 0x02)//�ƴο۷� 
		{
				MyStrCPY(Consum_Amount, UP_defNOcardBalance, CARD_SIZE);        //�����ƴεĽ��

				MyStrCPY(UserBalance, UP_defNOretBalance, CARD_SIZE);       //����Ĭ�ϵĽ��	ffff
									
				Local_Check_Card_falg=1;    //���ؼ��ˢ��Ȩ��		
		}					
	
		else
			{
				Pay_Carderr_Code = SYS_NO_NETWORK;
			}	



			
	}
	
	if(Local_Check_Card_falg)
	{		
		
	  Check_Card_Limit (Pay_Head_Code);      //���ˢ��Ȩ��
		
		if(GetWorkStatus(IN_CONSUMPT_STATUS)||(Machine_category[0] != 0x01)||(Machine_category[0] != 0x02)||(Machine_category[0] != 0x03))        //����״̬ ����ʵʱ�ϴ���¼
			{
				
				
/********************����Ҫ���������******************************/	
				
				if(Pay_Carderr_Code!=0X00)
				{				
		    		recorddata[23] = Pay_Carderr_Code;	   			
				}
								
				Add_UpdataRecord(0);          //����ʵʱ�ϴ���¼		

/********************************************************/
							
			}		
	}
	
	if(GetWorkStatus(IN_CONSUMPT_STATUS)||(Machine_category[0] != 0x01)||(Machine_category[0] != 0x02)||(Machine_category[0] != 0x03))   //ֻ��������״̬���߶�ֵ�ű�������
		{
			 AddRecord(Pay_Head_Code ,0);          //�洢��¼
							
			 delay_ms(1);
			
			 UndoPressKEY();//��������
			
			 if(Pay_Carderr_Code == PAY_OK)    //   
				{
				 SaveActual_CardCount(); 				 
				}
				else                         // 
				{				
				 SaveErr_CardCount();			//���������������
				}			
		}	
			
					
						
play_card:			
				
				
     LCD_ShowPlay_Card(Pay_Carderr_Code);       //LCD��ʾ
	
	   Card_Markok=0;

     Enable_Pay_Card=1;   //����ˢ��			
				
		 idcycleflag =1;      //�ظ��������������ʼ 2019-02-21
		 
		 	Asynchronous_QR_falg =0 ;      //�Ͳͱ�־
}





















