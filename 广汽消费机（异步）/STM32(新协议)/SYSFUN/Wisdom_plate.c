#include "Head.h"

#include "Wisdom_plate.h"

#ifdef   WISDOM_PLATE


u8   WP_RxDataBuff[50];                         //�жϽ�������

u16  WP_u8RxIndexW=0;                           //�жϽ�������дָ��

u8   WP_clearcycle=0;                           //����������ݼ���


u8   WP_updatareturnfalg=0;                           //ʵʱ�ϴ����ر�־


u8  WP_UserBalance[4]={0X00,0X00,0X00,0X00};	  //�������
 
u8  WP_Consum_Amount[4] ={0X00,0X00,0X00,0X00};	  //���ѽ��

//u8   Server_Returndata[20]={0};                //���������ص�����
 
 
u8  WP_defNOnetBalance[4]={0X38,0X90,0X08,0X00};	  //������ʱĬ�����     //��λ��ǰ

u8  WP_defNOretBalance[4]={0X99,0X99,0X99,0X00};	  //������ʱĬ�����     //��λ��ǰ

u8  WP_defNOcardBalance[4]={0X00,0X00,0X00,0X00};	  //��IC��ʱĬ�����

u16  wpOverTimeCnt=0;                        //��ʱ�˳�����

uint8_t  WP_readcard_ret=0 ;               //�������ض�ͷ��


uint8_t  WP_retcycle=0 ;               //��������

//u8   USART4_RX_CRLF=0;

uint8_t  wp_Consumpidbuff[4] = {0};                   //����ʱ�Ŀ���

 
 uint8_t  WP_Card_Read_falg=0 ;                 //������־

 uint8_t  WP_Consumption_falg=0 ;               //���ѱ�־




void WP_SendString(uint8_t *combuff ,uint16_t len)
{
	uint16_t t;
	for(t=0;t<len;t++)
	 {
		  USART_SendData(WP_UART, combuff[t]);//�򴮿�1��������
			
			while(USART_GetFlagStatus(WP_UART,USART_FLAG_TC)!=SET);//�ȴ����ͽ���
	
   }
}

void WP_SendByte(uint8_t combuff)
{
  //    delay_us(500);
		USART_SendData(WP_UART, combuff);//�򴮿�1��������
	
		while(USART_GetFlagStatus(WP_UART,USART_FLAG_TC)!=SET);//�ȴ����ͽ���
}



//u8 UPloadRecord_Ack(u16 overtime)
//{
//   wpOverTimeCnt = overtime;
//	 WP_updatareturnfalg =0 ;  //ʵʱ�ϴ����ر�־
//	
//		if(WP_updatareturnfalg)
//		{
//			return 1;
//		}
//		if (wpOverTimeCnt == 0)                      //��ʱ�˳�
//				return 0;
//	
//}

//u8 WP_CheckCard_Ack(u16 overtime)
//{
//	 uint8_t ret = 0;
//	
//   wpOverTimeCnt = overtime;
//	 
//    while (1)
//    {
//			ret = WP_CheckCard();
//			
//        if(ret)
//				{		
//				  return ret;
//				}
//        if (wpOverTimeCnt == 0)                      //��ʱ�˳�
//            return 0;
//	 }
//}




void   InitWPCombuff(void)//��ʼ������ͨѶ������
{

WP_u8RxIndexW=0; 

}

//01      5a 3c | 12 | 01 | 00 | 00 00 00 00 | 00 00 00 00 00 00 00 00 | 00 00 00 00 | 01 | DB
//02      5A 3C | 12 | 02 | 00 | 00 | 00 00 00 00 00 00 00 12 34 56 78 | 12 34 00 00 | 5C | DB
//03      5A 3C | 12 | 03 | 00 | 00 | 00 00 00 00 00 00 00 12 34 56 78 | 12 34 00 00 | 5D | DB



//        5A 3C | 16 | 01 | 00 | 00 | 00 00 00 00 00 00 00  12 34 56 78 | 12 34 00 00 | 00 00 00 00 | 5B | DB

//        5A 3C | 16 | 02 | 00 | 00 | 00 00 00 00 00 00 00  12 34 56 78 | 12 34 00 00 | 12 34 00 00 | 5B | DB

//        5A 3C | 16 | 03 | 00 | 00 | 00 00 00 00 00 00 00  12 34 56 78 | 12 34 00 00 | 12 34 00 00 | 5C | DB



/***************************************************************************************************
 * �� �� ��: 
 * ��������: ���̴��ڷ������ݸ���λ������λ������������Ӧ����
 * ����˵��: 
 * ���ú���: ��
 * ȫ�ֱ���: ��
 * �䡡����:    cmdtyp    �����     01 ����  02 ����   03 ����ȷ��
               Result    ���λ
 * ��������: ��
***************************************************************************************************/

void Wisdom_plate_Return(uint8_t cmdtyp, uint8_t Result)
{
	uint8_t  WPreturnbufflen=22;
	
  uint8_t  WPreturnbuff[27]={0X5A, 0X3C, 0X16, 0X01, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00 ,0X12, 0X34, 0X56, 0X78, 0X12, 0X34, 0X00, 0X00 ,0X00, 0X00 ,0X00, 0X00,0X5B, 0XDB};

	uint8_t  wp_UserBalancebuf[4] ={0x00};
		
	uint8_t  testsuanfabuf1[4]={0x00};
		
	union    FourByte i4;
		
 MyStrCPY(wp_UserBalancebuf, WP_UserBalance, 4);        //�����������
		
 i4.i = getBCDtoDec(wp_UserBalancebuf, 4);              //���ݸ�ʽת��
		
 WPreturnbuff[3]	=cmdtyp ;          //�����
 WPreturnbuff[4]  =Result;           //���λ
	
 MyStrCPY(WPreturnbuff+13, idbuff, CARD_SIZE);       //��������
	
 MyStrCPY(WPreturnbuff+17, i4.c, 4);        //�����������
		
// MyStrCPY(WPreturnbuff+17, WP_UserBalance, CARD_SIZE);        //�����������
		
// MyStrCPY(WPreturnbuff+21, WP_Consum_Amount, CARD_SIZE);      //�������ѽ��		
	
 MyStrCPY(WPreturnbuff+21, testsuanfabuf1, CARD_SIZE);      //�������ѽ��			
	
		
 WPreturnbuff[WPreturnbufflen + 3] = GetSum(WPreturnbuff + 3, WPreturnbufflen);     //��У��
	
 WP_SendString(WPreturnbuff ,27);
				
}



/*
�� ���� 0x01
-----------------------------------------------------------------------------------------------------------------

����̨������
;//  5a 3c | 12 | 01 | 00 | 00 00 00 00 | 00 00 00 00 00 00 00 00 | 00 00 00 00 | 01 | DB   
;//  ͷ    | �� | ��  | �� | ������ | ������ | ������ | У | β
;//  ��    | �� | ��  | ˮ |        |       |        | �� | ��

pos���أ�
;// 5A 3C | 16 | 01 | 00 | 00 | 00 00 00 00 00 00 00 12 34 56 78| 12 34 00 00 |00 00 00 00 | 5B | DB
;  //  ͷ | �� | �� | �� | �� | ����11�ֽ� hex����|  ���4�ֽ�  | ������| У | β
;  //  �� | �� | �� | �� | �� | ���Ȳ���ǰ�油0    |  hex ����    |       | �� | ��
         |  ��λΪ��    |
                                                 |  ��λ��ǰ    |

����    5a 3c 12 01 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 01 DB 

*/
/***
void  Wisdom_plate_Card_Read(void)
{
  uint8_t  ret=0 ;
	
	uint8_t  reterr=0 ;
	
static	uint8_t  procretfalg=0 ;        //c������շ��ص�����
	
	
//	uint8_t  reterrtest[4]={0} ;
	
//	ret  = WP_CheckCard_Ack(1);

 // WP_readcard_ret = WP_CheckCard();
	
  ret  =  WP_readcard_ret ;
	
//	 Write_SOCK_Data_Buffer(0, reterrtest, 1 );               // ������
	
	
  if(ret)    //������ 
	{
	  if(ec20_device_info.netWork)
		{
		  wpOverTimeCnt =20;
			
			MyStrCPY(Consum_Amount, WP_RxDataBuff+17, 4);           //�ۿ��� 4�ֽ�
			
			Arrange_Record(ret ,1);  //��������
			
			UPloadRecord(3);        //ʵʱ�ϴ�����
	
      WP_updatareturnfalg =0 ;  //ʵʱ�ϴ����ر�־
			
			procretfalg =1;

		}
		else                            //û������
		{
				  MyStrCPY(WP_UserBalance, WP_defNOnetBalance, CARD_SIZE);        //�����������   Ĭ��ֵ
				 
				  MyStrCPY(WP_Consum_Amount, WP_defNOcardBalance, CARD_SIZE);      //�������ѽ��
			
			    reterr =0;
						
			goto 	CRend ;	
		}
		
	//	Wisdom_plate_Return(0X01,0);          //��Ӧ����
	
//	  ProcessCard(ret);                //��������			
	}
//	else                                      //û�ҵ���
//	{
//		MyStrCPY(WP_UserBalance,   WP_defNOcardBalance, CARD_SIZE);        //�����������   Ĭ��ֵ
//	 
//		MyStrCPY(WP_Consum_Amount, WP_defNOcardBalance, CARD_SIZE);      //�������ѽ��

//		reterr =4;
//		
////	goto 	CRend ;
//	}
	
	
if((ec20_device_info.netWork)&&procretfalg)
{	
//	 reterrtest[0]  =ec20_device_info.netWork;
//	
//	Write_SOCK_Data_Buffer(0, reterrtest, 1 );               // ������
	
	if((WP_updatareturnfalg ==0)&&(wpOverTimeCnt))
	{
		return ;
	}
	if(WP_updatareturnfalg)    //�������з���
		{
				   	
			//�������������ص�����				
			 MyStrCPY(WP_UserBalance, Server_Returndata +12, CARD_SIZE);        //�����������

			 MyStrCPY(WP_Consum_Amount, WP_defNOcardBalance, CARD_SIZE);      //�������ѽ��	
			
		}
	else                           //�������޷���
		{
			MyStrCPY(WP_UserBalance, WP_defNOretBalance, CARD_SIZE);        //�����������   Ĭ��ֵ
		 
			MyStrCPY(WP_Consum_Amount, WP_defNOcardBalance, CARD_SIZE);      //�������ѽ��
		}

reterr =0;	
procretfalg =0;
goto 	CRend ;		
}


if(WP_readcard_ret==0)                                      //û�ҵ���
	{
		MyStrCPY(WP_UserBalance,   WP_defNOcardBalance, CARD_SIZE);        //�����������   Ĭ��ֵ
	 
		MyStrCPY(WP_Consum_Amount, WP_defNOcardBalance, CARD_SIZE);      //�������ѽ��

		reterr =4;
		
	}


CRend:

  Wisdom_plate_Return(0X01,reterr);            //��Ӧ����	
	
  MyStrCPY(wp_Consumpidbuff, idbuff, 4);           //�ۿ�ʱ�Ŀ���
	
	WP_Card_Read_falg =0 ;
	
	
//	if(WP_retcycle>=2)
//	{
//	  WP_retcycle= 0;
//		WP_readcard_ret =0;
//	}
}

***/

void  Wisdom_plate_Card_Read(void)
{
	uint8_t  reterr=0 ;
	
	if(WP_readcard_ret)    //����������⵽�� 
		{
			
			MyStrCPY(WP_UserBalance,   WP_defNOcardBalance, 4);        //�����������   Ĭ��ֵ
		 
			MyStrCPY(WP_Consum_Amount, WP_defNOcardBalance, 4);      //�������ѽ��
			
			reterr=0 ;
			
		}
	else                                      //û�ҵ���
		{
			MyStrCPY(idbuff,           WP_defNOcardBalance, CARD_SIZE);        //����IC������   Ĭ��ֵ
			
	//		MyStrCPY(WP_UserBalance,   WP_defNOcardBalance, CARD_SIZE);        //�����������   Ĭ��ֵ
		 
//			MyStrCPY(WP_Consum_Amount, WP_defNOcardBalance, CARD_SIZE);        //�������ѽ��

			reterr =4;
		
		}

	 Wisdom_plate_Return(0X01,reterr);            //��Ӧ����	
		
//	 MyStrCPY(wp_Consumpidbuff, idbuff, 4);           //�ۿ�ʱ�Ŀ���
	
	 WP_Card_Read_falg =0 ;
	
}






/***

�� ���� 0x02
-----------------------------------------------------------------------------------------------------------------

����̨���������棩��
;//  5A 3C | 12 | 02 | 00 | 00 | 00 00 00 00 00 00 00 12 34 56 78 | 12 34 00 00 | 5C | DB
;//  ͷ   | �� | �� | �� | �� | ����11�ֽ� hex���� |   ���ѽ��  | У | β
;//   ��  | �� | �� | ˮ | �� | ���Ȳ���ǰ�油0     |             | �� | ��
����̨������������֤����
;//  5A 3C | 16 | 02  | 00 | 00 | 00 00 00 00 00 00 00 12 34 56 78 | 12 34 00 00 | 00 00 00 00 | 5C | DB   
;//  ͷ   | �� | �� | �� | ��    | ����11�ֽ� hex����                | ���ѽ��    | ��������     | У | β
;//  ��   | �� | �� | ˮ | ��    | ���Ȳ���ǰ�油0                   |             |             | �� | ��


pos���أ�
;//  5A 3C | 16 | 02 | 00 | 00 | 00 00 00 00 00 00 00  12 34 56 78 | 12 34 00 00 | 12 34 00 00 | 5B | DB
;//  ͷ �� | �� | ��  | �� | ��  | ����11�ֽ� hex���� |  ���4�ֽ�  | ���ѽ��    | У | β
;//        | �� | ��  | �� | ��  | ���Ȳ���ǰ�油0     |  hex ����    |             | �� | ��
                                                    |  ��λΪ��    |
 
                                                   |  ��λ��ǰ    |


        0 ��ʾ�ɹ�
        1 ��ʾʧ��
        3 ��ʾ���������޶���糬�����ͣ����ߵ��������޶
        4 ��ʾ����δ�������ڳ鿨���죬pos����֪�������Ƿ�ɹ���������δ��ָ��󣬽���̨�����δ��״̬���ȴ�pos���ٴη��أ����������
        5 ��������
        6 ��Ҫ��֤���루�������·���������֧����
        10 ������
        14 ����
        105 �豸�����ã������������ӣ�
        111 �豸������������Ҫͬ����ֹͣ���ף�������㣩

***/

//             5a 3c 12 01 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 01 DB

//  5A 3C 12 02 00 00 00 00 00 00 00 00 00 12 34 56 78 12 34 00 00 5C DB


void  Wisdom_plate_Consumption(void)
{
  uint8_t  ret=0 ;
	
//  uint8_t  reterr=0 ;
	
//	uint8_t  wp_Conmoney[4]={0} ;
	
//	union FourByte Con_money;
	
//	static	uint8_t  procretfalg=0 ;        //c������շ��ص�����
	
  ret  =  WP_readcard_ret ;

//	MyStrCPY(wp_Consumpidbuff, WP_RxDataBuff+13, 4);           //�ۿ�ʱ�Ŀ���	
			
//	if(!MyStrEQ(wp_Consumpidbuff, idbuff, 4))
//	{
//   	return ;
//	}
		
	if(WP_retcycle ==1)      //������ָ��
	{
	   ProcessCard(ret);        //����ˢ��
		
		 WP_retcycle =0;
	}
		
	/***

if(WP_retcycle ==1)      //������ָ��
	{		
		Local_Check_Card_falg=0;    //���ؼ��ˢ��Ȩ��	
		
		if(ec20_device_info.netWork)	          //������
		{
			wpOverTimeCnt =15;
			
			MyStrCPY(wp_Conmoney, WP_RxDataBuff+17, 4);           //�ۿ��� 4�ֽ�
					
			MyStrCPY(Con_money.c, wp_Conmoney, 4);           //�ۿ��� 4�ֽ�	
	
			getDectoBCD(Con_money.i, Consum_Amount, 4);
			
		  MyStrCPY(idbuff, wp_Consumpidbuff, 4);           //�ۿ�ʱ�Ŀ���
						
			Arrange_Record(ret ,1);  //��������
			
			UPloadRecord(3);        //ʵʱ�ϴ�����
		
		  WP_updatareturnfalg =0 ;  //ʵʱ�ϴ����ر�־	
			
			procretfalg =1;
			
			WP_retcycle =0;
		}
		
		else                            //û������
			{
		
				MyStrCPY(WP_Consum_Amount, WP_RxDataBuff+17, 4);           //�ۿ��� 4�ֽ�
											
				MyStrCPY(WP_UserBalance, WP_defNOcardBalance, CARD_SIZE);        //�����������   Ĭ��ֵ   88888
         //��ʾ��			 				
				MyStrCPY(Con_money.c, WP_Consum_Amount , 4);           //�ۿ��� 4�ֽ�	
	
			  getDectoBCD(Con_money.i, Consum_Amount, 4);
				
				MyStrCPY(UserBalance, WP_defNOretBalance, CARD_SIZE);           //�������	
				
        Pay_Carderr_Code = PAY_OK; 	
				
				Local_Check_Card_falg=1;    //���ؼ��ˢ��Ȩ��	
				
				reterr =0;
							
				goto 	CONend ;	
			}		
}
			
if(ec20_device_info.netWork) 
{	
	
	//Write_SOCK_Data_Buffer(0, reterrtest, 1 );               // ������
	
	if((WP_updatareturnfalg ==0)&&(wpOverTimeCnt))     
			{
			  return ;
			}	
			
	if(WP_updatareturnfalg)    //�������з���
		{
					     //�������������ص�����				
		 MyStrCPY(WP_UserBalance, Server_Returndata +12, CARD_SIZE);        //�����������
			
		 MyStrCPY(WP_Consum_Amount, Server_Returndata +8, CARD_SIZE);       //�������ѽ��	
	   //��ʾ��	
		 MyStrCPY(Consum_Amount, WP_Consum_Amount, CARD_SIZE);       //�������ѽ��			
     MyStrCPY(UserBalance, WP_UserBalance, CARD_SIZE);           //�������
			
			if(Server_Returndata[17]==PAY_BACK_ERR)
			{
			Pay_Carderr_Code = PAY_BACK_ERR;
			
			reterr =5;		
				
			}
			else if(Server_Returndata[17]==PAY_NO_MONEY_ERR)
			{
				
				Pay_Carderr_Code = PAY_NO_MONEY_ERR;
							
				reterr =14;	
				
			}
			else 
			{		
				
			 Pay_Carderr_Code = PAY_OK;			
				
			 reterr =0;	
			}							     			
		}
	else          //�������޷���
		{
			
			MyStrCPY(WP_UserBalance, WP_defNOretBalance, CARD_SIZE);        //�����������   Ĭ��ֵFF FF
		 
			MyStrCPY(WP_Consum_Amount, Consum_Amount, CARD_SIZE);      //�������ѽ��
				
			//��ʾ��	
			MyStrCPY(Consum_Amount, WP_Consum_Amount, CARD_SIZE);       //�������ѽ��			
      MyStrCPY(UserBalance,   WP_defNOretBalance, CARD_SIZE);           //�������
			
	    Local_Check_Card_falg=1;    //���ؼ��ˢ��Ȩ��		
			
      reterr =0;			
			
			Pay_Carderr_Code = PAY_OK; 	
		}
		
//	reterr =0;	
			
	procretfalg =0;
			
	goto 	CONend ;		
				
}			
		
CONend:

  Wisdom_plate_Return(0X02,reterr);          //��Ӧ����	

	MyStrCPY(wp_Consumpidbuff, WP_defNOcardBalance, 4);           //�ۿ�ʱ�Ŀ���
	
	if(Local_Check_Card_falg)
	{
	  Check_Card_Limit (ret);    //�������
		
		Add_UpdataRecord(0);          //����ʵʱ�ϴ���¼
	}

	AddRecord(ret ,0);          //�洢��¼
									
 if(Pay_Carderr_Code == PAY_OK)     
	{
	 SaveActual_CardCount(); 				//������Чˢ���� 
	}
	else                         
	{				
	 SaveErr_CardCount();			      //�������ˢ���� 
	}			
			
//	ShowPlay_Card_43inch(Pay_Carderr_Code) ;     //ˢ����ʾ

	WP_readcard_ret =0;
	
	WP_Consumption_falg =0 ;
	
	**/
	
}



/*

����ȷ��ָ��

*/
void  Wisdom_plate_Transaction_Confirmation(void)
{

	Wisdom_plate_Return(0X03,0);   
	
}


/**********************************************************
//�������̴���ͨѶ
**********************************************************/
void Process_Wisdom_plate(void)
{
	uint16_t WPData_length = 0;
	
	u8 DEF_WPHead[] = {0x5a,0x3c}; 
	
	if (WP_u8RxIndexW < 3) {goto com_rst;}						   					//���������
	
	if (!MyStrEQ(WP_RxDataBuff, DEF_WPHead, 2)) 									//��ͷУ��
	{
		goto com_end;
	}
	
	WPData_length = WP_RxDataBuff[2];             										//��ȡ���ݳ���
	
/*----------------------------------------------------------------------------*/	
	if (WP_u8RxIndexW != (WPData_length +5))
	{ 
		if (WP_u8RxIndexW  < (WPData_length + 5))  {goto com_rst;}
		
		if (WP_u8RxIndexW  > (WPData_length + 5))  {goto com_end;}
	}
 else 
	{
		if (GetSum(WP_RxDataBuff + 3, WPData_length)!= WP_RxDataBuff[WPData_length + 3]) 	//������
		{goto com_end;}
		
		if (WP_RxDataBuff[WPData_length + 4]!=0xDB) 									//��βУ��
		{goto com_end;}
			
		switch (WP_RxDataBuff[3])													//����ѡ��
		{
		  	case 0x01:  {	/*WP_readcard_ret = WP_CheckCard();*/  	

//					if(Enable_Pay_Card)
//		      { WP_Card_Read_falg =1;  	}	

      WP_readcard_ret = WP_CheckCard();	     //ˢ��������,���ض�ͷ��
      Pay_Head_Code  = WP_readcard_ret;
		
		  Wisdom_plate_Card_Read();		 

				}	break;					//��ȡ�������
			
			  case 0x02:    ProcessCard(WP_readcard_ret);            break;				  //����
			
		  	case 0x03:    Wisdom_plate_Transaction_Confirmation();         break;					//����ȷ��
			

			
			default: goto com_end;
		}
	}
com_end:	
		InitWPCombuff(); 														// ��ʼ������1����

com_rst:
	
		WP_clearcycle = 0;   															// ��ʼ����������ʱ
}



void  Process_Wisdom_plate_Card(void )
{
		
	if (WP_Card_Read_falg)               //�յ����̲�ѯ����ָ��
	{

      WP_readcard_ret = WP_CheckCard();	     //ˢ��������,���ض�ͷ��
			
      Pay_Head_Code  = WP_readcard_ret;
		
		  Wisdom_plate_Card_Read();		 
		
		
		
/***********************��IC������ת���ɹ����о�Ժ���Ÿ�ʽ*********************************/	

//			if(WP_readcard_ret!=4)	  
//			{
//					GAEI_IC_Conversion(idbuff,idbuff); 
//			}	
						
		
					
	}


}



#endif

