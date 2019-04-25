
#include  "Head.h"

/**********************************************************
//��������
**********************************************************/

/**********************************************************
//��������
**********************************************************/


u8 keyidx;//�ַ����ո���
u8 keybuff[KEY_SIZE];//���յ��ַ�

u8 menu_keyidx =0;//�ַ����ո���

u8 menu_keyidx_MAX =0;//�˵�ģʽ�����ַ������ո���

u8 menu_keybuff[50];//���յ��ַ�


u8 keymoneybuff[4]={0};//�����Ľ��

uint32_t keymoney32buff=  0x00000000;//�����Ľ��

uint8_t  keymoneyCentsbuff[10]= {0};//�����Ľ�� ��

uint8_t  keymoneyplusbuff[10]= {0};//���� + �ŵ��ܽ��

uint32_t u32_monetbuf = 0;        //�������ܶ�U32��ʽ

KEY_STATUS_INFO    key_status_info;


void Menu_CheckKEY(u8 keyVal)
{
	
	if(menu_keyidx>=menu_keyidx_MAX)    
		{
			menu_keyidx =0;	
		}	
	
	menu_keybuff[menu_keyidx ++] = keyVal;
		

	
}


/**********************************************************
//��鰴��
**********************************************************/
void CheckKEY(u8 keyVal)
{
  uint8_t i;
	
  uint32_t u32_keymonetbuf = 0;
  uint8_t  u8_keymoneybuff[4] = {0x00};	
	
	Clear_Standby_Display();     //�رմ�����ʾ
	
	statuscnt = 0;       //�˳�����ģʽ����
	
	if(key_status_info.spotfalg)   //��С����
	{
	//	if((key_status_info.spotcount >2)&&((keyVal!=KEY_CLEAN)&&(keyVal!=KEY_CONFIRM)&&(keyVal!=KEY_PLUS)))      //С�����2λ���� ȷ��  ���  +  ����������Ч   180519
				
		if((key_status_info.spotcount >=2)&&((keyVal!=KEY_CLEAN)&&(keyVal!=KEY_CONFIRM)&&(keyVal!=KEY_PLUS)))      //С�����2λ���� ȷ��  ���  +  ����������Ч 
			{	
				return;
			}
			if(keyVal==KEY_SPOT)     //�ٰ�С���� ��Ч
			{
				return;
			}
			
		key_status_info.spotcount++;     //С����󰴼�����
	}
	
 else if((keyidx>=6)&&((keyVal!=KEY_CLEAN)&&(keyVal!=KEY_CONFIRM)&&(keyVal!=KEY_PLUS)&&((keyVal!=KEY_SPOT) )))     //û��С�����������������6λ����
	{
     return;

	}
	
	keybuff[keyidx++] = keyVal;
		

 if(keyVal!=33)
	{	
    Show_Refresh_coun =0;
		
		if ((keyVal == KEY_PLUS)&&(key_status_info.normalfalg ==1))      //5���а��� �� # or +  ������״̬��   
			{   
				SetWorkStatus (KEY_PLUS_STATUS);	   //����+��״̬
			
				key_status_info.spotfalg =0;
				key_status_info.spotcount =0;
				
				Standbytime =   SECOND_CYCLE*30;   //30������������
								
				key_status_info.plusfalg =1;      //+ ��״̬    

				keymoney32buff = 0;
				keymoneyCentsbuff[0]=0;
				keymoneyCentsbuff[1]=0;
					
				
				for( i= 0;i <keyidx -1  ;i++)
				{	
					if(keybuff[i]  == KEY_SPOT)
					{			
						MyStrCPY(keymoneyCentsbuff , keybuff+i+1, keyidx -2-i);         //��Ǯ �� ����
						
						break ;
					}
					else
					 {		 
						keymoney32buff = (keybuff[i]|(keymoney32buff<<4)) ;            //��Ǯ Ԫ ����
					 }			
				}
			
			keymoney32buff = (keymoney32buff<<8)|(keymoneyCentsbuff[0]<<4)|keymoneyCentsbuff[1];
				
			separate_value_1_4(keymoney32buff,u8_keymoneybuff) ;
					
      u32_keymonetbuf = getBCDtoDec(u8_keymoneybuff , 4);	

      u32_monetbuf = u32_monetbuf + u32_keymonetbuf;
				
			getDectoBCD(u32_monetbuf, keymoneybuff, 4);	
				

			INIT_KEY_BUFF();    //������������

				return;		
			}
	  if((key_status_info.plusfalg ==0)&&(key_status_info.normalfalg ==0))       //û��+�� ������״̬
				{
					
					SetWorkStatus(KEY_KEY_STATUS);	  // ���밴��״̬
					
					Standbytime =   SECOND_CYCLE*10;   //10������������
					
					Show_Refresh_coun =0;
					
					key_status_info.normalfalg = 1;
				}
					
		 if(keyVal==KEY_SPOT)     //���� .
			{
			
				key_status_info.spotfalg =1;
											
			}
			
			ProcessKEYCMD();
					
	}    //��������״̬���°�������		
}



/**********************************************************
//��������״̬���°���������������ϸ������������©��
**********************************************************/
void ProcessKEYCMD(void)
{		
	uint8_t  i;
	uint8_t  t=0;
  uint32_t u32_keymonetbuf = 0;
  uint8_t  u8_keymoneybuff[4] = {0x00};		
	

	if ((keybuff[0] == KEY_CONFIRM)&&(key_status_info.plusfalg==0)) //1����һ�� ȷ��
		{
			UndoPressKEY();//��������
		}
		
	else  if (keybuff[0] == KEY_CLEAN)    //2����һ�� ���
		{
			UndoPressKEY();//��������
		}
		
	else  if (keybuff[0] == KEY_PLUS)    //3����һ�� + �ż�
		{
			UndoPressKEY();//��������
		}		
				
	else	if ((keyidx > 1) && (keybuff[keyidx - 1 ] == KEY_CLEAN)) //�����һ���� ���)
	{
		
		UndoPressKEY();//��������
		
		return;
	}
		
	if ((keyidx > 1) && (keybuff[keyidx - 1] == KEY_CONFIRM)) //�����һ���� ȷ��)
	{	
		
		if(GetWorkStatus(IN_CONSUMPT_STATUS))
			{			
				 keyidx-=1;
				 return ;
			}
				

//				
//		for( i= 0;i <keyidx -1  ;i++)
//		{	
//		  if(keybuff[i]  == KEY_SPOT)
//		  {			
//				MyStrCPY(keymoneyCentsbuff , keybuff+i+1, keyidx -2-i);         //��Ǯ �� ����
//				
//				break ;
//			}
//			else
//       {		 
//				keymoney32buff = (keybuff[i]|(keymoney32buff<<4)) ;            //��Ǯ Ԫ ����
//			 }			
//		}
//		
//		keymoney32buff = (keymoney32buff<<8)|(keymoneyCentsbuff[0]<<4)|keymoneyCentsbuff[1];
//		
//		separate_value_1_4(keymoney32buff,keymoneybuff) ;
		
		
	
		SetWorkStatus(IN_CONSUMPT_STATUS);	  // ��������״̬
		
		Standbytime =   SECOND_CYCLE*30;      //30������������
		
		Show_Refresh_coun=0;
		
		SYN6288_Send(SYN6288CMD_VOICE_PLAY ,SYN6288CMDPARAM_PLAY_MUSIC0,"��ˢ��" ,6);
		
		
		keymoney32buff = 0;
		keymoneyCentsbuff[0]=0;
		keymoneyCentsbuff[1]=0;	
		
		for( i= 0;i <keyidx -1  ;i++)
		{	
			if(keybuff[i]  == KEY_SPOT)
			{			
				MyStrCPY(keymoneyCentsbuff , keybuff+i+1, keyidx -2-i);         //��Ǯ �� ����
				
				break ;
			}
			else
			 {		 
				keymoney32buff = (keybuff[i]|(keymoney32buff<<4)) ;            //��Ǯ Ԫ ����
			 }			
		 }
			
		keymoney32buff = (keymoney32buff<<8)|(keymoneyCentsbuff[0]<<4)|keymoneyCentsbuff[1];
			
		separate_value_1_4(keymoney32buff,u8_keymoneybuff) ;
				
		u32_keymonetbuf = getBCDtoDec(u8_keymoneybuff , 4);	

		u32_monetbuf = u32_monetbuf + u32_keymonetbuf;
			
		getDectoBCD(u32_monetbuf, keymoneybuff, 4);			
		
		
		Show_moneybuf[0]= (keymoneybuff[0]>>4)&0X0F;
		Show_moneybuf[1]= (keymoneybuff[0]>>0)&0X0F;
		
		Show_moneybuf[2]= (keymoneybuff[1]>>4)&0X0F;
		Show_moneybuf[3]= (keymoneybuff[1]>>0)&0X0F;
		
		Show_moneybuf[4]= (keymoneybuff[2]>>4)&0X0F;
		Show_moneybuf[5]= (keymoneybuff[2]>>0)&0X0F;
		
		Show_moneybuf[6]= (keymoneybuff[3]>>4)&0X0F;
		Show_moneybuf[7]= (keymoneybuff[3]>>0)&0X0F;
	
		for(t =0;t< 5 ;t++)
		{
			 if( Show_moneybuf[t] ==0X00)
			 {
				 Show_moneybuf[t] = 10; 
			 }	 
			 else
			 {
				break;
			 } 
		}
		return;		
	}
		
}




/**********************************************************
//��������
**********************************************************/
void UndoPressKEY(void)
{
	INIT_KEY_BUFF();    //������������
	
	SET_MY_STATUS(NORMAL_STATUS);   //�˻�����״̬
	
	showStandby=1;         //��ʾ����״̬
	
  memset(keymoneybuff,0,4);
	
	u32_monetbuf =0;
	
	Clear_Key_Status( );   //�������״̬
}


/**********************************************************
//���ù���״̬
**********************************************************/
void SetWorkStatus(u8 curStatus)
{
	sys_status = curStatus;

	if (MY_STATUS_IS(NORMAL_STATUS)) //����״̬
	{
	//	showStandby=1;
	}
}

/**********************************************************
//��ȡ����״̬
**********************************************************/
uint8_t GetWorkStatus(u8 curStatus)
{
	//statuscnt = 0;
	//status = curStatus;

	if (sys_status ==curStatus) //����״̬
	{
    return  1;

	}
	
	 return  0;
	
}







/**********************************************************
//�������״̬
//��ʽ
**********************************************************/
void  Clear_Key_Status(void )
	{

		key_status_info.err =0; 		    //��������
		key_status_info.errcount =0; 	  //�������
		
		key_status_info.normalfalg =0;	  //����״̬��־
	  key_status_info.normalcount =0;	  //����״̬��������
	  key_status_info.normalpos =0;	    //����״̬����λ��
		
		
		key_status_info.spotfalg =0;	  //С�����־
		key_status_info.spotcount =0;	  //С����󰴼�����
		key_status_info.spotpos =0;	    //С����󰴼�λ��
		
		key_status_info.nospotfalg =0;	//��С�����־
		key_status_info.nospotcount =0;	//��С����󰴼�����
		key_status_info.nospotpos =0;	  //��С����󰴼�λ��
		
		key_status_info.plusfalg =0;		//+ �ű�־
		key_status_info.pluscount =0;		//+ �ź󰴼�����
		key_status_info.pluspos =0;		  //+ �ź󰴼�λ��
		
		key_status_info.keyclock  =0 ;  //��������
		
		key_status_info.reverse2 =0;		//Ԥ��2
	

	}









