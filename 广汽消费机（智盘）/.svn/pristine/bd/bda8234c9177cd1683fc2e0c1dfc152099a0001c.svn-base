
#include  "Head.h"

/**********************************************************
//常量定义
**********************************************************/

/**********************************************************
//变量定义
**********************************************************/


u8 keyidx;//字符接收个数
u8 keybuff[KEY_SIZE];//接收的字符

u8 menu_keyidx =0;//字符接收个数

u8 menu_keyidx_MAX =0;//菜单模式按键字符最大接收个数

u8 menu_keybuff[50];//接收的字符


u8 keymoneybuff[4]={0};//按键的金额

uint32_t keymoney32buff=  0x00000000;//按键的金额

uint8_t  keymoneyCentsbuff[10]= {0};//按键的金额 分

uint8_t  keymoneyplusbuff[10]= {0};//按键 + 号的总金额

uint32_t u32_monetbuf = 0;        //按键的总额U32格式

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
//检查按键
**********************************************************/
void CheckKEY(u8 keyVal)
{
  uint8_t i;
	
  uint32_t u32_keymonetbuf = 0;
  uint8_t  u8_keymoneybuff[4] = {0x00};	
	
	Clear_Standby_Display();     //关闭待机显示
	
	statuscnt = 0;       //退出按键模式计数
	
	if(key_status_info.spotfalg)   //有小数点
	{
	//	if((key_status_info.spotcount >2)&&((keyVal!=KEY_CLEAN)&&(keyVal!=KEY_CONFIRM)&&(keyVal!=KEY_PLUS)))      //小数点后2位除了 确认  清除  +  其他按键无效   180519
				
		if((key_status_info.spotcount >=2)&&((keyVal!=KEY_CLEAN)&&(keyVal!=KEY_CONFIRM)&&(keyVal!=KEY_PLUS)))      //小数点后2位除了 确认  清除  +  其他按键无效 
			{	
				return;
			}
			if(keyVal==KEY_SPOT)     //再按小数点 无效
			{
				return;
			}
			
		key_status_info.spotcount++;     //小数点后按键数量
	}
	
 else if((keyidx>=6)&&((keyVal!=KEY_CLEAN)&&(keyVal!=KEY_CONFIRM)&&(keyVal!=KEY_PLUS)&&((keyVal!=KEY_SPOT) )))     //没有小数点的情况下最多输入6位数字
	{
     return;

	}
	
	keybuff[keyidx++] = keyVal;
		

 if(keyVal!=33)
	{	
    Show_Refresh_coun =0;
		
		if ((keyVal == KEY_PLUS)&&(key_status_info.normalfalg ==1))      //5、有按键 按 # or +  在正常状态下   
			{   
				SetWorkStatus (KEY_PLUS_STATUS);	   //进入+号状态
			
				key_status_info.spotfalg =0;
				key_status_info.spotcount =0;
				
				Standbytime =   SECOND_CYCLE*30;   //30秒后进入主界面
								
				key_status_info.plusfalg =1;      //+ 号状态    

				keymoney32buff = 0;
				keymoneyCentsbuff[0]=0;
				keymoneyCentsbuff[1]=0;
					
				
				for( i= 0;i <keyidx -1  ;i++)
				{	
					if(keybuff[i]  == KEY_SPOT)
					{			
						MyStrCPY(keymoneyCentsbuff , keybuff+i+1, keyidx -2-i);         //金钱 分 拷贝
						
						break ;
					}
					else
					 {		 
						keymoney32buff = (keybuff[i]|(keymoney32buff<<4)) ;            //金钱 元 处理
					 }			
				}
			
			keymoney32buff = (keymoney32buff<<8)|(keymoneyCentsbuff[0]<<4)|keymoneyCentsbuff[1];
				
			separate_value_1_4(keymoney32buff,u8_keymoneybuff) ;
					
      u32_keymonetbuf = getBCDtoDec(u8_keymoneybuff , 4);	

      u32_monetbuf = u32_monetbuf + u32_keymonetbuf;
				
			getDectoBCD(u32_monetbuf, keymoneybuff, 4);	
				

			INIT_KEY_BUFF();    //按键数量清零

				return;		
			}
	  if((key_status_info.plusfalg ==0)&&(key_status_info.normalfalg ==0))       //没有+号 在正常状态
				{
					
					SetWorkStatus(KEY_KEY_STATUS);	  // 进入按键状态
					
					Standbytime =   SECOND_CYCLE*10;   //10秒后进入主界面
					
					Show_Refresh_coun =0;
					
					key_status_info.normalfalg = 1;
				}
					
		 if(keyVal==KEY_SPOT)     //按键 .
			{
			
				key_status_info.spotfalg =1;
											
			}
			
			ProcessKEYCMD();
					
	}    //处理【正常状态】下按键命令		
}



/**********************************************************
//处理【正常状态】下按键命令。各种情况仔细分析，不可遗漏。
**********************************************************/
void ProcessKEYCMD(void)
{		
	uint8_t  i;
	uint8_t  t=0;
  uint32_t u32_keymonetbuf = 0;
  uint8_t  u8_keymoneybuff[4] = {0x00};		
	

	if ((keybuff[0] == KEY_CONFIRM)&&(key_status_info.plusfalg==0)) //1、第一个 确认
		{
			UndoPressKEY();//撤消按键
		}
		
	else  if (keybuff[0] == KEY_CLEAN)    //2、第一个 清除
		{
			UndoPressKEY();//撤消按键
		}
		
	else  if (keybuff[0] == KEY_PLUS)    //3、第一个 + 号键
		{
			UndoPressKEY();//撤消按键
		}		
				
	else	if ((keyidx > 1) && (keybuff[keyidx - 1 ] == KEY_CLEAN)) //（最后一个按 清除)
	{
		
		UndoPressKEY();//撤消按键
		
		return;
	}
		
	if ((keyidx > 1) && (keybuff[keyidx - 1] == KEY_CONFIRM)) //（最后一个按 确认)
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
//				MyStrCPY(keymoneyCentsbuff , keybuff+i+1, keyidx -2-i);         //金钱 分 拷贝
//				
//				break ;
//			}
//			else
//       {		 
//				keymoney32buff = (keybuff[i]|(keymoney32buff<<4)) ;            //金钱 元 处理
//			 }			
//		}
//		
//		keymoney32buff = (keymoney32buff<<8)|(keymoneyCentsbuff[0]<<4)|keymoneyCentsbuff[1];
//		
//		separate_value_1_4(keymoney32buff,keymoneybuff) ;
		
		
	
		SetWorkStatus(IN_CONSUMPT_STATUS);	  // 进入消费状态
		
		Standbytime =   SECOND_CYCLE*30;      //30秒后进入主界面
		
		Show_Refresh_coun=0;
		
		SYN6288_Send(SYN6288CMD_VOICE_PLAY ,SYN6288CMDPARAM_PLAY_MUSIC0,"请刷卡" ,6);
		
		
		keymoney32buff = 0;
		keymoneyCentsbuff[0]=0;
		keymoneyCentsbuff[1]=0;	
		
		for( i= 0;i <keyidx -1  ;i++)
		{	
			if(keybuff[i]  == KEY_SPOT)
			{			
				MyStrCPY(keymoneyCentsbuff , keybuff+i+1, keyidx -2-i);         //金钱 分 拷贝
				
				break ;
			}
			else
			 {		 
				keymoney32buff = (keybuff[i]|(keymoney32buff<<4)) ;            //金钱 元 处理
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
//撤消按键
**********************************************************/
void UndoPressKEY(void)
{
	INIT_KEY_BUFF();    //按键数量清零
	
	SET_MY_STATUS(NORMAL_STATUS);   //退回正常状态
	
	showStandby=1;         //显示待机状态
	
  memset(keymoneybuff,0,4);
	
	u32_monetbuf =0;
	
	Clear_Key_Status( );   //清除按键状态
}


/**********************************************************
//设置工作状态
**********************************************************/
void SetWorkStatus(u8 curStatus)
{
	sys_status = curStatus;

	if (MY_STATUS_IS(NORMAL_STATUS)) //正常状态
	{
	//	showStandby=1;
	}
}

/**********************************************************
//读取工作状态
**********************************************************/
uint8_t GetWorkStatus(u8 curStatus)
{
	//statuscnt = 0;
	//status = curStatus;

	if (sys_status ==curStatus) //正常状态
	{
    return  1;

	}
	
	 return  0;
	
}







/**********************************************************
//清除按键状态
//格式
**********************************************************/
void  Clear_Key_Status(void )
	{

		key_status_info.err =0; 		    //错误类型
		key_status_info.errcount =0; 	  //错误计数
		
		key_status_info.normalfalg =0;	  //正常状态标志
	  key_status_info.normalcount =0;	  //正常状态按键数量
	  key_status_info.normalpos =0;	    //正常状态按键位置
		
		
		key_status_info.spotfalg =0;	  //小数点标志
		key_status_info.spotcount =0;	  //小数点后按键数量
		key_status_info.spotpos =0;	    //小数点后按键位置
		
		key_status_info.nospotfalg =0;	//非小数点标志
		key_status_info.nospotcount =0;	//非小数点后按键数量
		key_status_info.nospotpos =0;	  //非小数点后按键位置
		
		key_status_info.plusfalg =0;		//+ 号标志
		key_status_info.pluscount =0;		//+ 号后按键数量
		key_status_info.pluspos =0;		  //+ 号后按键位置
		
		key_status_info.keyclock  =0 ;  //按键锁定
		
		key_status_info.reverse2 =0;		//预留2
	

	}









