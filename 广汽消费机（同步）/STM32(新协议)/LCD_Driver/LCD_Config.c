

#include "Head.h"

#include "LCD_Config.h"

uint8_t  num_lcd[]={"0123456789 :.-"};	

	
uint8_t  MenuShowBuf[14][20]={
{""}


};

		/*************待机时显示时间************/
void LCD_Standby(void)	
	{
		
	u8 const LCDweekASCII[]={"日一二三四五六日一"};	
	
  u8	Show_Time_LCD[]={"2018年06月20日 星期三  14:39"};
	
	u8	Up_Count_LCD[]={"00001"};
	
  u8	Show_up_countbuf[4]={0x00};	
  u8	Show_up_count   [8]={0x00};		
	
	u8 t;
	
	DS1302_Read_Time();       //读时间
	
	HexToStr(LCDtimebuf,  time_buf,  8);	

	memcpy(Show_Time_LCD,   LCDtimebuf,4);       //2018
	memcpy(Show_Time_LCD+6, LCDtimebuf+4,2);   //06
	memcpy(Show_Time_LCD+10, LCDtimebuf+6,2);   //20		
	memcpy(Show_Time_LCD+10, LCDtimebuf+6,2);   //20	
	memcpy(Show_Time_LCD+19, LCDweekASCII+time_buf[7]*2,2);   //三		
	memcpy(Show_Time_LCD+23, LCDtimebuf+8,2);   //14	
	memcpy(Show_Time_LCD+26, LCDtimebuf+10,2);   //39	
	
	ClrScreen();   //LCD清屏函数 
	delay_ms(5);
	
//  DrawIcon(0,0,1);        //显示图片
	
	SetBG_Color(LCD_DARK);
//	
	SetDisplayInvert(0);
	
	SetFontType((LCD_ASC16_FONT<<4)|LCD_HZK32_FONT);
	
	SetFG_Color(LCD_WHITE);
	
	PutString(90,10,"T机号:");		//在指定位置开始显示ASCII字符串
	
	PutString(190,10,machno_ASCII);

#ifdef   WISDOM_PLATE    //是智盘

  PutString(100,80,"智盘结算模式");

#else	

  if      (Machine_category[0] == 0x01)   	PutString(100,80,"变值扣费模式");		//在指定位置开始显示ASCII字符串

	else if (Machine_category[0] == 0x02)    
          {						
					 PutString(100,80,"定值扣费模式"); 									
					}
	
	else if (Machine_category[0] == 0x03)     PutString(100,80,"计次扣费模式");		//在指定位置开始显示ASCII字符串
#endif	

	if(Consum_TimerBit[0])
	{
	  if (Machine_category[0] == 0x02)    
          {						
					 	uint8_t  consumbuf[4]={0};
						uint8_t  consumbufshow[]={"扣款金额：00.00元"};				
						
						HexToStr(consumbuf,  Fixed_consum_Moneybuf +Consum_TimerBit[1]*2,  2);
											
						memcpy(consumbufshow+10,  consumbuf,  1);     //  拷贝 										
						memcpy(consumbufshow+11,  consumbuf+1,1);     //  拷贝    
						memcpy(consumbufshow+13,  consumbuf+2,1);     //  拷贝 			
						memcpy(consumbufshow+14,  consumbuf+3,1);     //  拷贝 	
									
					  PutString(50,140,consumbufshow);		//在指定位置开始显示ASCII字符串				
					}
			
	}
	else
	{
		
		SetFG_Color(LCD_RED);
		
	  PutString(50,140,"非就餐时段,请勿刷卡");		//在指定位置开始显示ASCII字符串	
		
		SetFG_Color(LCD_WHITE);
		
	}				
					
//	SetFG_Color(LCD_GREEN);
	
	if(ec20_device_info.netWork)
		{			
			
		  PutString(350,10,"4G");
		}
		else
		{
		
	    SetFG_Color(LCD_RED);  //设置前景色和背景色						
		  PutString(348,10,"4G");		
			SetFontType((LCD_ASC12_FONT<<4)|LCD_HZK24_FONT); //设置字体  1代表16点阵，2代表24点阵，3代表32点阵		
			PutString(380,15,"X");						
		}
	
		if(rdrealtime_up_count)  //有未上传的数据
		{		

			 getDectoBCD(rdrealtime_up_count, Show_up_countbuf, 4);
			
				Show_up_count[0]= (Show_up_countbuf[0]>>4)&0X0F;
				Show_up_count[1]= (Show_up_countbuf[0]>>0)&0X0F;
				
				Show_up_count[2]= (Show_up_countbuf[1]>>4)&0X0F;
			
				Show_up_count[3]= (Show_up_countbuf[1]>>0)&0X0F;
				
				Show_up_count[4]= (Show_up_countbuf[2]>>4)&0X0F;
				Show_up_count[5]= (Show_up_countbuf[2]>>0)&0X0F;
				
				Show_up_count[6]= (Show_up_countbuf[3]>>4)&0X0F;
				Show_up_count[7]= (Show_up_countbuf[3]>>0)&0X0F;
				
				for(t =3;t< 7 ;t++)
				{
					 if( Show_up_count[t] ==0X00)
					 {
						 Show_up_count[t] = 10; 
					 }	 
					 else
					 {
						break;
					 } 
				}		
	
				Up_Count_LCD[0] = num_lcd[Show_up_count[3]];
				Up_Count_LCD[1] = num_lcd[Show_up_count[4]];
				Up_Count_LCD[2] = num_lcd[Show_up_count[5]];
				Up_Count_LCD[3] = num_lcd[Show_up_count[6]];
				Up_Count_LCD[4] = num_lcd[Show_up_count[7]];

			//	DrawRect(10,10,70,30,LCD_RED,1);             //画矩形框
				
				
				SetFG_Color(LCD_RED);  //设置前景色和背景色	
				SetFontType((LCD_ASC12_FONT<<4)|LCD_HZK24_FONT); //设置字体  1代表16点阵，2代表24点阵，3代表32点阵	
			  PutString(12,12,Up_Count_LCD);
							
		}
		else 
		{
			
			
				DrawRect(10,10,20,30,LCD_GREEN,1);
				SetFontType((LCD_ASC12_FONT<<4)|LCD_HZK24_FONT); //设置字体  1代表16点阵，2代表24点阵，3代表32点阵		
				SetFG_Color(LCD_WHITE);  //设置前景色和背景色	
        PutString(12,12,"0");
		}	
	SetFG_Color(LCD_WHITE);  //设置前景色和背景色		
	SetFontType((LCD_ASC12_FONT<<4)|LCD_HZK24_FONT); //设置字体  1代表16点阵，2代表24点阵，3代表32点阵		
	PutString(30,200,Show_Time_LCD); //显示时间
			
}

/****************************************************
	
	LCD12864 显示刷卡内容

输入 : type   表示错误代码

*****************************************************/

void LCD_ShowPlay_Card(uint8_t type)      
	{
		
  uint8_t  t = 0;
	
	uint8_t    Namebuff[10]    ={0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20};    // 姓名
	uint8_t    US_Balance[8]   ={0X0B,0X0B,0X0B,0X0B,0X0B,0X0B,0X0B,0X0B};    // 余额
	uint8_t    CO_Amount[8]    ={0X0B,0X0B,0X0B,0X0B,0X0B,0X0B,0X0B,0X0B};    // 金额

	uint8_t    US_Balance_Show[10]   ={0X0B,0X0B,0X0B,0X0B,0X0B,0X0B,0X0B,0X0B,0x00,0x00};    // 余额	
	uint8_t    CO_Amount_Show[10]   ={0X0B,0X0B,0X0B,0X0B,0X0B,0X0B,0X0B,0X0B,0x00,0x00};    // 余额		
	
	uint8_t    Balance_Plus_minus = 0;    //余额正负号
	
  MyStrCPY(Namebuff, Server_Returndata +18, 10);        //拷贝姓名
	
  Balance_Plus_minus = Server_Returndata[28];        //拷贝姓名		
	
	
#ifdef   WISDOM_PLATE    //是智盘

		
#else		
			
#endif		
//	Clear_Standby_Display();     //关闭待机显示
	
	Clear_Standby_Display_Time(2);
	
	
		
	ClrScreen();  //清屏	
	delay_ms(5);
	
	SetBG_Color(LCD_DARK);
	
	SetDisplayInvert(0);
	
	SetFontType((LCD_ASC16_FONT<<4)|LCD_HZK32_FONT);
	
	SetFG_Color(LCD_WHITE);	
	
if((type==PAY_OK)||(type==PAY_NO_MONEY_ERR))                                  //正确
	{
		
	
		
		if(recorddata[25] == 0X6F)         //通讯命令    1字节
			{
			
				PutString (25  ,150," 退款成功");
			
				 return;
			}	
										
  /********************** 处理消费金额数据 ************************************/	
	
	CO_Amount[0]= (Consum_Amount[0]>>4)&0X0F;
	CO_Amount[1]= (Consum_Amount[0]>>0)&0X0F;
	
	CO_Amount[2]= (Consum_Amount[1]>>4)&0X0F;
	CO_Amount[3]= (Consum_Amount[1]>>0)&0X0F;
	
	CO_Amount[4]= (Consum_Amount[2]>>4)&0X0F;
	CO_Amount[5]= (Consum_Amount[2]>>0)&0X0F;
	
	CO_Amount[6]= (Consum_Amount[3]>>4)&0X0F;
	CO_Amount[7]= (Consum_Amount[3]>>0)&0X0F;
	
	for(t =0;t< 5 ;t++)
	{
	   if( CO_Amount[t] ==0X00)
		 {
		   CO_Amount[t] = 10; 
		 }	 
		 else
		 {
		  break;
		 } 
	}	
/***********************************************************************/		
	
/********************** 处理余额数据 ************************************/		
	
	US_Balance[0]= (UserBalance[0]>>4)&0X0F;
	US_Balance[1]= (UserBalance[0]>>0)&0X0F;
	
	US_Balance[2]= (UserBalance[1]>>4)&0X0F;
	US_Balance[3]= (UserBalance[1]>>0)&0X0F;
	
	US_Balance[4]= (UserBalance[2]>>4)&0X0F;
	US_Balance[5]= (UserBalance[2]>>0)&0X0F;
	
	US_Balance[6]= (UserBalance[3]>>4)&0X0F;
	US_Balance[7]= (UserBalance[3]>>0)&0X0F;
	
	for(t =0;t< 5 ;t++)
	{
	   if( US_Balance[t] ==0X00)
		 {
		   US_Balance[t] = 10; 
		 }	 
		 else
		 {
		  break;
		 } 
	}
	
	if(type==PAY_OK)                //刷卡成功
		{
//		 SYN6288_Send(SYN6288CMD_VOICE_PLAY ,SYN6288CMDPARAM_PLAY_MUSIC0,"谢谢" ,4);
					
//			BeginOutput1();           //打开继电器1
			
//			BeginOutput2();           //打开继电器1
			
			SYN6288_Send(SYN6288CMD_VOICE_PLAY ,SYN6288CMDPARAM_PLAY_MUSIC0,"soundb" ,6);		
		}

	else if(type==PAY_NO_MONEY_ERR)                //余额不足
		{
			
  		 SYN6288_Send(SYN6288CMD_VOICE_PLAY ,SYN6288CMDPARAM_PLAY_MUSIC0,"余额不足" ,8);
							
			  PutString (100  ,45,"余额不足");
			
		}	
		
	CO_Amount_Show[0]       = num_lcd[CO_Amount[0]];
	CO_Amount_Show[1]       = num_lcd[CO_Amount[1]];
	CO_Amount_Show[2]       = num_lcd[CO_Amount[2]];
	CO_Amount_Show[3]       = num_lcd[CO_Amount[3]];
	CO_Amount_Show[4]       = num_lcd[CO_Amount[4]];															
	CO_Amount_Show[5]       = num_lcd[CO_Amount[5]];
	CO_Amount_Show[6]       = num_lcd[12];					
	CO_Amount_Show[7]       = num_lcd[CO_Amount[6]];					
	CO_Amount_Show[8]       = num_lcd[CO_Amount[7]];		

	US_Balance_Show[0]      = num_lcd[US_Balance[0]];
	US_Balance_Show[1]      = num_lcd[US_Balance[1]];
	US_Balance_Show[2]      = num_lcd[US_Balance[2]];
	US_Balance_Show[3]      = num_lcd[US_Balance[3]];
	US_Balance_Show[4]      = num_lcd[US_Balance[4]];															
	US_Balance_Show[5]      = num_lcd[US_Balance[5]];
	US_Balance_Show[6]      = num_lcd[12];					
	US_Balance_Show[7]      = num_lcd[US_Balance[6]];					
	US_Balance_Show[8]      = num_lcd[US_Balance[7]];	
		
/******************************* end ****************************************/	
	

	
/****************第二行*******************/
	
	SetBG_Color(LCD_DARK);
	
	SetDisplayInvert(0);
	
	SetFontType((LCD_ASC16_FONT<<4)|LCD_HZK32_FONT);
	
	SetFG_Color(LCD_WHITE);
	
  if(Offline_Online_falg)	 
	{
	  PutString (100,10,"在线消费");	
	}
	else 
	{
	  PutString (100,10,"脱机消费");	
	
	}
	
  PutString (25,100,"用    户:");	
	
  PutString (180,100,Namebuff);	

  PutString (25  ,150,"消费金额:");
	
  PutString (180  ,150,CO_Amount_Show);				

  PutString (350 ,150,"元");		

	
	if(Balance_Plus_minus ==1)      	
	 {
		 if(t==0) t=1;
		 
	 	US_Balance_Show[t-1]      = num_lcd[13];
	 }
	
	
	
//if (Balance_Plus_minus == 1)
//{
//	PutString (25,200,"余   额:-");
//}
//else
//{  
  PutString (25,200,"余    额:");
//}	
	
	PutString (180  ,200,US_Balance_Show);	
	
  PutString (350,200,"元");		
				
}
	
else if(type==PAY_WHITEALLOW_WRR)                //白名单错误
	{
		
		SYN6288_Send(SYN6288CMD_VOICE_PLAY ,SYN6288CMDPARAM_PLAY_MUSIC0,"非白名单" ,8);
		
		PutString (25  ,150,"非白名单");
		
//	  LCD_Write_String(4,0,"非白名单") ;
	}
	
	else if(type==PAY_HOLIDAY_ERR)                   //节假日错误
	{
SYN6288_Send(SYN6288CMD_VOICE_PLAY ,SYN6288CMDPARAM_PLAY_MUSIC0,"节假日无权限" ,12);
		
		PutString (25  ,150,"节假日错误");
//	  LCD_Write_String(4,0,"此节假日无权限") ;
	}
	
	else if(type==PAY_TIME_INTERVAL_ERR)             //时间段错误
	{
    SYN6288_Send(SYN6288CMD_VOICE_PLAY ,SYN6288CMDPARAM_PLAY_MUSIC0,"时间段无权限" ,12);
		
		
		PutString (25  ,150,"时间段错误");
//	  LCD_Write_String(4,0,"此时间段无权限") ;
	}
	
	else if(type==PAY_BACK_ERR)                      //黑名单错误
	{
    SYN6288_Send(SYN6288CMD_VOICE_PLAY ,SYN6288CMDPARAM_PLAY_MUSIC0,"卡异常" ,6);
		
//		PutString (25  ,150,"黑名单卡");		
				PutString (25  ,150,"卡异常");
	}
	
	else if(type==PAY_DELAYED_ERR)                      //数卡延时错误
	{
		
   SYN6288_Send(SYN6288CMD_VOICE_PLAY ,SYN6288CMDPARAM_PLAY_MUSIC0,"重复刷卡" ,8);
		
		
	 PutString (25  ,150,"请勿重复刷卡");
		
		
//	  LCD_Write_String(4,0,"请勿重复刷卡") ;
	}
	
	else if(type==PAY_SECTOR_PASSW_ERR)                      //扇区密码错误
	{
		
    SYN6288_Send(SYN6288CMD_VOICE_PLAY ,SYN6288CMDPARAM_PLAY_MUSIC0,"扇区密码错误" ,12);
		
		PutString (25  ,150,"扇区密码错误");
		
//	  LCD_Write_String(4,0,"扇区密码错误") ;
	}
	
	else if(type==PAY_RW_SECTOR_ERR)                      //读写扇区错误
	{
    SYN6288_Send(SYN6288CMD_VOICE_PLAY ,SYN6288CMDPARAM_PLAY_MUSIC0,"读写扇区错误" ,12);
		
		PutString (25  ,150,"读写扇区错误");
		
//	  LCD_Write_String(4,0,"读写扇区错误") ;
	}	

	else if(type==SYS_NO_NETWORK)                      //无网络
	{
SYN6288_Send(SYN6288CMD_VOICE_PLAY ,SYN6288CMDPARAM_PLAY_MUSIC0,"无网络" ,8);

	
		PutString (25  ,150,"网络未连接");
		
	// 	LCD_Write_String(4,0,"请检查网络！");
	}		
	
	else if(type==SYS_NET_CONNECT_FAIL)                //  网络连接失败
			
	{
   SYN6288_Send(SYN6288CMD_VOICE_PLAY ,SYN6288CMDPARAM_PLAY_MUSIC0,"网络连接失败" ,12);
		
		PutString (25  ,150," 网络连接失败");
		
//	  LCD_Write_String(4,0,"请重新刷卡！");
	}	
	
	else if(type==PAY_EXCEED_LIMIT_SECOND_ERR)                //  消费限额(当次)
			
	{
     SYN6288_Send(SYN6288CMD_VOICE_PLAY ,SYN6288CMDPARAM_PLAY_MUSIC0,"消费限额" ,8);
		
		
			PutString (25  ,150," 超出当次最大消费");
		
	}		
	
	else if(type==PAY_EXCEED_LIMIT_DAY_ERR)                //  消费限额(当日)
			
	{
     SYN6288_Send(SYN6288CMD_VOICE_PLAY ,SYN6288CMDPARAM_PLAY_MUSIC0,"消费限额" ,8);
		
		
			PutString (25  ,150," 超出当日最大消费");
		
	}		
	
	
	else if(type==EXCEED_MAX_RECORD_ERR)                  //  超出最大存储
			
	{	
		  SYN6288_Send(SYN6288CMD_VOICE_PLAY ,SYN6288CMDPARAM_PLAY_MUSIC0,"存储满" ,6);
		
			PutString (25  ,150," 容量已满，请清除");
		
	}		
	
	else if(type==PAY_NO_CONSUM_TIMER_ERR)                  //  非就餐时间段
			
	{
     SYN6288_Send(SYN6288CMD_VOICE_PLAY ,SYN6288CMDPARAM_PLAY_MUSIC0,"非就餐时间" ,10);
		
		
			PutString (25  ,150,"非就餐时间段");

	}		

	else if(type==PAY_REPEAT_COLLAR_ERR)                  //  重复领餐
			
	{
     SYN6288_Send(SYN6288CMD_VOICE_PLAY ,SYN6288CMDPARAM_PLAY_MUSIC0,"重复领餐" ,10);
		
		
			PutString (25  ,150,"重复领餐");

	}			
	
		else if(type==PAY_NO_RESERVATION_ERR)                  //  未订餐
			
	{
     SYN6288_Send(SYN6288CMD_VOICE_PLAY ,SYN6288CMDPARAM_PLAY_MUSIC0,"未订餐" ,10);
		
		 PutString (25  ,150,"未订餐");

	}
	
	
	
	else if(type==EXCEED_RECORDERRCOUNT_ERR)                 //存储错误数量
			
	{
     SYN6288_Send(SYN6288CMD_VOICE_PLAY ,SYN6288CMDPARAM_PLAY_MUSIC0,"存储错误" ,8);
		
		 PutString (25  ,150,"存储出错");
	}	
	
	else if(type==PAY_REFUND_CARD_ERR)                 //退款卡号错误
			
	{
     SYN6288_Send(SYN6288CMD_VOICE_PLAY ,SYN6288CMDPARAM_PLAY_MUSIC0,"错误卡" ,6);
		
		
			PutString (25  ,150,"错误卡");

	}		
	
	memset(Server_Returndata ,0,sizeof(u8)*30);         //清0
	
//		EndClear_Pay_Card_Data();                             //最终清除刷卡数据
	
	
}





/****************************************************
	
	LCD12864 + 号状态显示
*****************************************************/
void ShowKeyValue_Plus(void)
{
		u8  LCD_Show_money[20]={0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00};  //消费金额
	
	
	u32  DISPLAY_CHAR[16] = {
	        
	            '0',//0x00
							'1', //0x01
							'2', //0x02
							'3', //0x03
							'4', //0x04
							'5', //0x05
							'6', //0x06
							'7', //0x07
							'8', //0x08
							'9', //0x09
							'0', //0x0A				  
	            '.', //0x00
			       	'+', //0x0B
	            '.', //0x0B
	            '+', //0x0B
	            '#', //0x0B
};
	
	
	
	u8  i=0; 
	u8  tmp[20]={0}; 
	u32 t=0;
  delay_ms(1);
	
	
 for (i = 0; i < keyidx; i++)
	{
		tmp[t++] = DISPLAY_CHAR[keybuff[i]];				
	
		if(t>10)
		{
		t=0;
		}
	}	

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
	
	LCD_Show_money[0]  =num_lcd[Show_moneybuf[0]];// 数字显示函数
	LCD_Show_money[1]  =num_lcd[Show_moneybuf[1]];// 数字显示函数
	LCD_Show_money[2]  =num_lcd[Show_moneybuf[2]];// 数字显示函数
	LCD_Show_money[3]  =num_lcd[Show_moneybuf[3]];// 数字显示函数
	LCD_Show_money[4]  =num_lcd[Show_moneybuf[4]];// 数字显示函数
	LCD_Show_money[5]  =num_lcd[Show_moneybuf[5]];// 数字显示函数
	LCD_Show_money[6]  =num_lcd[12];// 数字显示函数 .
	LCD_Show_money[7]  =num_lcd[Show_moneybuf[6]];// 数字显示函数
	LCD_Show_money[8]  =num_lcd[Show_moneybuf[7]];// 数字显示函数		
		
	
	
	Clear_Standby_Display();     //关闭待机显示
		
	ClrScreen();  //清屏	

	SetBG_Color(LCD_DARK);
	
	SetDisplayInvert(0);
	
	SetFontType((LCD_ASC16_FONT<<4)|LCD_HZK32_FONT);
	
	SetFG_Color(LCD_WHITE);
///****************第三行*******************/
	
	PutString (150  ,10,"变值扣费");	
	
	PutString (25  ,100,"消费金额:");
	
  PutString (180  ,100,LCD_Show_money);	
	
  PutString (150 , 150,"+");	
	
	PutString (180  ,150,tmp);	
	
	SetFG_Color(LCD_DEEP_BLUE);
	
  SetFontType((LCD_ASC8_FONT<<4)|LCD_HZK16_FONT);

	PutString_cn(100,220,"广州科坦电子技术有限公司");
}



/****************************************************
	
	LCD12864 显示按键
*****************************************************/

void LCD_ShowKeyValue(void)
{

	u32  DISPLAY_CHAR[16] = {
	        
	            '0',//0x00
							'1', //0x01
							'2', //0x02
							'3', //0x03
							'4', //0x04
							'5', //0x05
							'6', //0x06
							'7', //0x07
							'8', //0x08
							'9', //0x09
							'0', //0x0A				  
	            '.', //0x00
			       	'+', //0x0B
	            '.', //0x0B
	            '+', //0x0B
	            '#', //0x0B
};
	
	
	
	u8  i=0; 
	u8  tmp[20]={0}; 
	u32 t=0;
  delay_ms(1);
 for (i = 0; i < keyidx; i++)
	{
		tmp[t++] = DISPLAY_CHAR[keybuff[i]];				
	
		if(t>10)
		{
		t=0;
		}
	}	

	
	Clear_Standby_Display();     //关闭待机显示
		
	ClrScreen();  //清屏	
	//delay_ms(1);
	
//	DrawIcon(0,0,2); //显示液晶内部储存器的第3幅图片	消费成功	
//	HexToStr(LCDtimebuf,  time_buf,  8);	
	
	/****************第一行*******************/

//	LCD_Write_String_NUM(1,1,LCDtimebuf,4);          //年
//	LCD_Write_String(1,3,"年");
//	LCD_Write_String_NUM(1,4,LCDtimebuf+4,2);       //月
//	LCD_Write_String(1,5,"月");
//  LCD_Write_String_NUM(1,6,LCDtimebuf+6,2);        //日
//	LCD_Write_String(1,7,"日");
	
	SetBG_Color(LCD_DARK);
	
	SetDisplayInvert(0);
	
	SetFontType((LCD_ASC16_FONT<<4)|LCD_HZK32_FONT);
	
	SetFG_Color(LCD_WHITE);
///****************第三行*******************/
	
	
	PutString (150  ,10,"变值扣费");	
	
	PutString (25  ,100,"消费金额:");
	
  PutString (180  ,100,tmp);	
	
//  PutString (350 , 100,"元");	
	
	SetFG_Color(LCD_DEEP_BLUE);
	
  SetFontType((LCD_ASC8_FONT<<4)|LCD_HZK16_FONT);

	PutString_cn(100,220,"广州科坦电子技术有限公司");
}



/****************************************************
	
	LCD12864 消费状态显示
*****************************************************/

void LCD_Show_Consump_Pattern(void)
{
	
	u8  LCD_Show_money[20]={0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00};  //消费金额
	
	HexToStr(LCDtimebuf,  time_buf,  8);	
	
	/****************第一行*******************/

//	LCD_Write_String_NUM(1,1,LCDtimebuf,4);          //年
//	LCD_Write_String(1,3,"年");
//	LCD_Write_String_NUM(1,4,LCDtimebuf+4,2);       //月
//	LCD_Write_String(1,5,"月");
//  LCD_Write_String_NUM(1,6,LCDtimebuf+6,2);        //日
//	LCD_Write_String(1,7,"日");
	
///****************第三行*******************/


	
//LCD_Write_Number(11);// 数字显示函数 ：
//	
//LCD_Write_Number(Show_moneybuf[0]);// 数字显示函数
//LCD_Write_Number(Show_moneybuf[1]);// 数字显示函数
//LCD_Write_Number(Show_moneybuf[2]);// 数字显示函数
//LCD_Write_Number(Show_moneybuf[3]);// 数字显示函数
//LCD_Write_Number(Show_moneybuf[4]);// 数字显示函数
//LCD_Write_Number(Show_moneybuf[5]);// 数字显示函数
//LCD_Write_Number(12);// 数字显示函数 .
//LCD_Write_Number(Show_moneybuf[6]);// 数字显示函数
//LCD_Write_Number(Show_moneybuf[7]);// 数字显示函数

	LCD_Show_money[0]  =num_lcd[Show_moneybuf[0]];// 数字显示函数
	LCD_Show_money[1]  =num_lcd[Show_moneybuf[1]];// 数字显示函数
	LCD_Show_money[2]  =num_lcd[Show_moneybuf[2]];// 数字显示函数
	LCD_Show_money[3]  =num_lcd[Show_moneybuf[3]];// 数字显示函数
	LCD_Show_money[4]  =num_lcd[Show_moneybuf[4]];// 数字显示函数
	LCD_Show_money[5]  =num_lcd[Show_moneybuf[5]];// 数字显示函数
	LCD_Show_money[6]  =num_lcd[12];// 数字显示函数 .
	LCD_Show_money[7]  =num_lcd[Show_moneybuf[6]];// 数字显示函数
	LCD_Show_money[8]  =num_lcd[Show_moneybuf[7]];// 数字显示函数

	Clear_Standby_Display();     //关闭待机显示
		
	ClrScreen();  //清屏	
	delay_ms(5);
	
	SetBG_Color(LCD_DARK);
	
	SetDisplayInvert(0);
	
	SetFontType((LCD_ASC16_FONT<<4)|LCD_HZK32_FONT);
	
	SetFG_Color(LCD_WHITE);

	PutString (150  ,10,"变值扣费");	

	PutString (25   ,100,"消费金额:");
	
  PutString (180  ,100,LCD_Show_money);	

  PutString (350 , 100,"元");	
	
//LCD_Write_String(2,7,"元");
///****************第四行*******************/	
	
	PutString(150,160,"请支付");
			
	SetFG_Color(LCD_BLUE);	
	SetFontType((LCD_ASC8_FONT<<4)|LCD_HZK16_FONT);	
	PutString_cn(100,220,"广州科坦电子技术有限公司");
				
}



/****************************************************
	
	LCD12864 显示主菜单输入密码
*****************************************************/

void LCD_Disp_MenuPassword(void)
{
	
	uint8_t  Function_showbuf[80]={0};
	uint8_t  showASCIIbuf[80]={0};	
	uint8_t  t=0;
	//uint8_t  j=0;
	
	
	menu_keyidx_MAX  =6;
	
	t  = menu_keyidx;

  if	(menu_keyidx >=6)	//{t =0;}
	{
	   DrawRect(23,170,64 ,32,LCD_GREEN,0);    //选择框		
	}
  else
	{
		DrawRect(85+ t*16,106,16 ,32,LCD_GREEN,0);    //选择框		
	}
	
	HexToStr(showASCIIbuf,  menu_keybuff,  menu_keyidx_MAX);
	
	memcpy(Function_showbuf,"密码:      ",13);       //  拷贝
		
 /*               拷贝密码                             */											 
	 memcpy(Function_showbuf+5, showASCIIbuf+1,1);      //  拷贝 1
	 memcpy(Function_showbuf+6, showASCIIbuf+3,1);      //  拷贝 2
	 memcpy(Function_showbuf+7, showASCIIbuf+5,1);      //  拷贝 3
	 memcpy(Function_showbuf+8, showASCIIbuf+7,1);      //  拷贝 4
	 memcpy(Function_showbuf+9, showASCIIbuf+9,1);      //  拷贝 5  
	 memcpy(Function_showbuf+10,showASCIIbuf+11,1);     //  拷贝 6			
	
	
	SetBG_Color(LCD_DARK);     //黑底
	
	SetDisplayInvert(0);        //字符显示背景色开关
	
	SetFontType((LCD_ASC16_FONT<<4)|LCD_HZK32_FONT);
	
	SetFG_Color(LCD_WHITE);

	PutString(5,10, "请按键输入管理员密码") ;		 //第一行  
	
	PutString(5,106, Function_showbuf) ;
	
	PutString(25,170,"确认              取消") ;    

}

/****************************************************
	
	LCD12864 显示主菜单
*****************************************************/

void LCD_Disp_MenuMain(void)
{

	uint16_t i=0;
	
	SetBG_Color(LCD_DARK);     //黑底
	
	SetDisplayInvert(0);        //字符显示背景色开关
	
	SetFontType((LCD_ASC16_FONT<<4)|LCD_HZK32_FONT);
	
	SetFG_Color(LCD_WHITE);

	Show_Menudata();                //处理显示内容
	
	i = Shou_Selection_box;
		
	if(i<7)
	{
		DrawRect(10,10+i*32,300,34,LCD_GREEN,0);
	/****************第一行*******************/	
		
		PutString(25,10, MenuShowBuf[0]) ;
		
	/****************第二行*******************/	

		PutString(25,42, MenuShowBuf[1]) ;

	/****************第三行*******************/	

		PutString(25,74,  MenuShowBuf[2]) ;

	/****************第四行*******************/		
		
		PutString(25,106,MenuShowBuf[3]) ;
			
	/****************第一行*******************/	
		
		PutString(25,138,MenuShowBuf[4]) ;
		
	/****************第二行*******************/	
		
		PutString(25,170,MenuShowBuf[5]) ;

	/****************第三行*******************/	

		PutString(25,202,MenuShowBuf[6]) ;

	/****************第四行*******************/		
	}
	else 
	{
		i=i-7;		
		DrawRect(10,10+i*32,300,34,LCD_GREEN,0);
	/****************第一行*******************/	
		
		PutString(25,10, MenuShowBuf[7]) ;
		
	/****************第二行*******************/	

		PutString(25,42, MenuShowBuf[8]) ;

	/****************第三行*******************/	

		PutString(25,74,  MenuShowBuf[9]) ;

	/****************第四行*******************/		
		
		PutString(25,106,MenuShowBuf[10]) ;
			
	/****************第一行*******************/	
		
		PutString(25,138,MenuShowBuf[11]) ;
		
	/****************第二行*******************/	
		
		PutString(25,170,MenuShowBuf[12]) ;

	/****************第三行*******************/	

		PutString(25,202,MenuShowBuf[13]) ;
	}
	
}



/****************************************************
	
	LCD12864 显示功能
*****************************************************/

void LCD_Disp_Function(void)
{
  uint8_t i;
	
	uint8_t t =0 ,j =0 ,z = 0;
		
	uint8_t  Function_showbuf[80]={0};

	uint8_t  Function_show2buf[80]={0};    //第二行

	uint8_t  Function_show3buf[80]={0};    //第三行

	uint8_t  Function_show4buf[80]={0};    //第三行	
	
	uint8_t  Function_show5buf[40]={0};    //第四行	
	
	
	uint8_t  showASCIIbuf[80];
	
	SetBG_Color(LCD_DARK);     //黑底
	
	SetDisplayInvert(0);        //字符显示背景色开关
	
	SetFontType((LCD_ASC16_FONT<<4)|LCD_HZK32_FONT);
	
	SetFG_Color(LCD_WHITE);

  i	= Menu_Fun_NUM ;
	
	switch(i)
		{
			
					  case  0x00:   	                                           //修改管理员密码
									{
											menu_keyidx_MAX  =6;
											
											t  = menu_keyidx;
			
											if	(menu_keyidx >=6)	//{t =0;}
											{
												 DrawRect(23,170,64 ,32,LCD_GREEN,0);    //选择框		
											}
											else
											{
												 DrawRect(122+ t*16,106,16 ,32,LCD_GREEN,0);    //选择框	
											}
																				
										 HexToStr(showASCIIbuf,  menu_keybuff,  menu_keyidx_MAX);
											
										 memcpy(Function_showbuf,"新密码:      ",13);       //  拷贝
											
                   /*               拷贝密码                             */											 
										 memcpy(Function_showbuf+7, showASCIIbuf+1,1);       //  拷贝 1
										 memcpy(Function_showbuf+8, showASCIIbuf+3,1);       //  拷贝 2
										 memcpy(Function_showbuf+9, showASCIIbuf+5,1);       //  拷贝 3
										 memcpy(Function_showbuf+10, showASCIIbuf+7,1);      //  拷贝 4
										 memcpy(Function_showbuf+11, showASCIIbuf+9,1);      //  拷贝 5  
										 memcpy(Function_showbuf+12, showASCIIbuf+11,1);     //  拷贝 6										
									
										/****************显示*******************/	
									
											PutString(5,10, "请按键输入新密码") ;		 //第一行  
											
											PutString(10,106, Function_showbuf) ;
											
											PutString(25,170,"确认              取消") ;         
										}				
										break;
			
		  case   0x10:{                    //设置4G服务器IP
			
			               menu_keyidx_MAX = 17;        //按键输入缓冲区大小
				
				             t  = menu_keyidx;
//				             if          ( t<3)               j=	0;
										 if          (( t>=3)&&( t<6))    t = t+1;
										 else if     (( t>=6)&&( t<9))    t = t+2;
										 else if     (( t>=9)&&( t<12))   t = t+3;				
                     else if     (( t>=12)&&( t<17))  {t = t-12;	j=	50;		}
				
								//		 if	(menu_keyidx >=17)	{t =0; j=	0;  }
										 
											if	(menu_keyidx >=17)	//{t =0;}
											{
												 DrawRect(23,200,64 ,32,LCD_GREEN,0);    //选择框		
											}
											else
											{
												 DrawRect(122+ t*16,90 +j,16 ,32,LCD_GREEN,0);    //选择框		
											}										 									
				
										 HexToStr(showASCIIbuf,  menu_keybuff,  17);			

				             DrawLine(120,120,360,120,LCD_WHITE);    //画线	(IP)	
				
				             DrawLine(120,170,200,170,LCD_WHITE);    //画线	(端口号)
				
						         DrawRect(122+ t*16,90 +j,16 ,32,LCD_GREEN,0);    //选择框						
				
										 memcpy(Function_showbuf, "IP地址:   .   .   .   ",21);       //  拷贝	
										 memcpy(Function_show2buf,"端口号:     ",11);       //  拷贝											 
                   /*               拷贝IP地址                             */											 
										 memcpy(Function_showbuf+7, showASCIIbuf+1,1);       //  拷贝 1
										 memcpy(Function_showbuf+8, showASCIIbuf+3,1);       //  拷贝 9
										 memcpy(Function_showbuf+9, showASCIIbuf+5,1);       //  拷贝 2
				
										 memcpy(Function_showbuf+11, showASCIIbuf+7,1);      //  拷贝 1
										 memcpy(Function_showbuf+12, showASCIIbuf+9,1);      //  拷贝 6  
										 memcpy(Function_showbuf+13, showASCIIbuf+11,1);     //  拷贝 8
				
										 memcpy(Function_showbuf+15, showASCIIbuf+13,1);     //  拷贝 0   
										 memcpy(Function_showbuf+16, showASCIIbuf+15,1);     //  拷贝 0						
										 memcpy(Function_showbuf+17, showASCIIbuf+17,1);     //  拷贝 1   
				
										 memcpy(Function_showbuf+19, showASCIIbuf+19,1);     //  拷贝 1										
										 memcpy(Function_showbuf+20, showASCIIbuf+21,1);     //  拷贝 0   
										 memcpy(Function_showbuf+21, showASCIIbuf+23,1);     //  拷贝 3				
                    /*               拷贝端口号                             */
										 memcpy(Function_show2buf+7,  showASCIIbuf+25,1);     //  拷贝 2						
										 memcpy(Function_show2buf+8,  showASCIIbuf+27,1);     //  拷贝 3   
										 memcpy(Function_show2buf+9,  showASCIIbuf+29,1);     //  拷贝 2										
										 memcpy(Function_show2buf+10, showASCIIbuf+31,1);     //  拷贝 3   
										 memcpy(Function_show2buf+11, showASCIIbuf+33,1);     //  拷贝 2	

				             PutString(5,10, "请按键输入服务器IP、端口") ;		 //第一行                                                               

				             PutString(10,90, Function_showbuf) ;             //第二行
										 
			               PutString(10,140, Function_show2buf) ;          //第三行 
			
			               PutString(25,200,"确认              取消") ;   //第四行
				
				
									}          break;

#ifdef   WIFI_Version     //是WIFI通讯									
			

									
			  case  0x11:{  			    //设置WiFi密码						
										
					           PutString(5,10, "1.打开手机APPWiFi配置工具") ;		 //第一行  
					
					           PutString(5,50, "2.输入WiFi账号密码") ;		 //第一行  
					
					           PutString(5,90, "3.按消费机确定键") ;		 //第一行
					
					           PutString(5,130,"4.点击手机配置按钮") ;		 //第一行
										
										}
										break;


									
#else  	 //是4G通讯或者标准版
									
																															
		  case   0x11: {          //设置本机IP          
			
				
			               menu_keyidx_MAX = 36;        //按键输入缓冲区大小
				
					           t  = menu_keyidx;
										 if          (( t>=3)&&( t<6))    t = t+1;
										 else if     (( t>=6)&&( t<9))    t = t+2;
										 else if     (( t>=9)&&( t<12))   t = t+3;				
                     else if     (( t>=12)&&( t<15)) {t = t-12;	j=	40;		}
										 else if     (( t>=15)&&( t<18)) {t = t-11; j=	40;		}
										 else if     (( t>=18)&&( t<21)) {t = t-10; j=	40;		}
										 else if     (( t>=21)&&( t<24)) {t = t-9;  j=	40;		}
										 else if     (( t>=24)&&( t<27)) {t = t-24;	j=	80;		}
										 else if     (( t>=27)&&( t<30)) {t = t-23; j=	80;		}
										 else if     (( t>=30)&&( t<33)) {t = t-22; j=	80;		}
										 else if     (( t>=33)&&( t<36)) {t = t-21;	j=	80;		}									 							
									//	 if	(menu_keyidx >=36)	{t =0; j=	0;  }			

											if	(menu_keyidx >=36)	//{t =0;}
											{
												 DrawRect(23,200,64 ,32,LCD_GREEN,0);    //选择框		
											}
											else
											{
												 DrawRect(122+ t*16,60 +j,16 ,32,LCD_GREEN,0);    //选择框			
											}

										 
						    //     DrawRect(122+ t*16,60 +j,16 ,32,LCD_GREEN,0);    //选择框		
										 
										 HexToStr(showASCIIbuf,  menu_keybuff,  menu_keyidx_MAX);	
										 
										 memcpy(Function_showbuf, "IP地址:   .   .   .   ",21);       //  拷贝	
				
										 memcpy(Function_show2buf,"子掩码:   .   .   .   ",21);       //  拷贝									
				
				             memcpy(Function_show3buf,"网  关:   .   .   .   ",21);       //  拷贝											 
										 
				
                   /*               拷贝IP地址                             */											 
										 memcpy(Function_showbuf+7, showASCIIbuf+1,1);       //  拷贝 1
										 memcpy(Function_showbuf+8, showASCIIbuf+3,1);       //  拷贝 9
										 memcpy(Function_showbuf+9, showASCIIbuf+5,1);       //  拷贝 2
				
										 memcpy(Function_showbuf+11, showASCIIbuf+7,1);      //  拷贝 1
										 memcpy(Function_showbuf+12, showASCIIbuf+9,1);      //  拷贝 6  
										 memcpy(Function_showbuf+13, showASCIIbuf+11,1);     //  拷贝 8
				
										 memcpy(Function_showbuf+15, showASCIIbuf+13,1);     //  拷贝 0   
										 memcpy(Function_showbuf+16, showASCIIbuf+15,1);     //  拷贝 0						
										 memcpy(Function_showbuf+17, showASCIIbuf+17,1);     //  拷贝 1   
				
										 memcpy(Function_showbuf+19, showASCIIbuf+19,1);     //  拷贝 1										
										 memcpy(Function_showbuf+20, showASCIIbuf+21,1);     //  拷贝 0   
										 memcpy(Function_showbuf+21, showASCIIbuf+23,1);     //  拷贝 3			

                   /*               拷贝子网掩码                             */											 
										 memcpy(Function_show2buf+7, showASCIIbuf+25,1);       //  拷贝 2
										 memcpy(Function_show2buf+8, showASCIIbuf+27,1);       //  拷贝 5
										 memcpy(Function_show2buf+9, showASCIIbuf+29,1);       //  拷贝 5
				
										 memcpy(Function_show2buf+11, showASCIIbuf+31,1);      //  拷贝 2
										 memcpy(Function_show2buf+12, showASCIIbuf+33,1);      //  拷贝 5  
										 memcpy(Function_show2buf+13, showASCIIbuf+35,1);     //  拷贝 5
				
										 memcpy(Function_show2buf+15, showASCIIbuf+37,1);     //  拷贝 2   
										 memcpy(Function_show2buf+16, showASCIIbuf+39,1);     //  拷贝 5						
										 memcpy(Function_show2buf+17, showASCIIbuf+41,1);     //  拷贝 5   
				
										 memcpy(Function_show2buf+19, showASCIIbuf+43,1);     //  拷贝 2										
										 memcpy(Function_show2buf+20, showASCIIbuf+45,1);     //  拷贝 5   
										 memcpy(Function_show2buf+21, showASCIIbuf+47,1);     //  拷贝 5	
				
				
                   /*               拷贝网关                             */											 
										 memcpy(Function_show3buf+7, showASCIIbuf+49,1);       //  拷贝 1
										 memcpy(Function_show3buf+8, showASCIIbuf+51,1);       //  拷贝 9
										 memcpy(Function_show3buf+9, showASCIIbuf+53,1);       //  拷贝 2
				
										 memcpy(Function_show3buf+11, showASCIIbuf+55,1);      //  拷贝 1
										 memcpy(Function_show3buf+12, showASCIIbuf+57,1);      //  拷贝 6  
										 memcpy(Function_show3buf+13, showASCIIbuf+59,1);     //  拷贝 8
				
										 memcpy(Function_show3buf+15, showASCIIbuf+61,1);     //  拷贝 0   
										 memcpy(Function_show3buf+16, showASCIIbuf+63,1);     //  拷贝 0						
										 memcpy(Function_show3buf+17, showASCIIbuf+65,1);     //  拷贝 0   
				
										 memcpy(Function_show3buf+19, showASCIIbuf+67,1);     //  拷贝 0										
										 memcpy(Function_show3buf+20, showASCIIbuf+69,1);     //  拷贝 0   
										 memcpy(Function_show3buf+21, showASCIIbuf+71,1);     //  拷贝 1					
								
				
				             PutString(5,10, "请按键输入本机IP") ;		 //第一行                                                               

				             PutString(10,60, Function_showbuf) ;             //第二行
										 
			               PutString(10,100, Function_show2buf) ;          //第三行 
			
				             PutString(10,140, Function_show3buf) ;          //第三行
				
			               PutString(25,200,"确认              取消") ;   //第四行				
								
			
										}            break;			
			
	#endif								
//		  case   0x12: {                  //设置TCP远端IP
//						         menu_keyidx_MAX = 17;        //按键输入缓冲区大小
//				
//				             t  = menu_keyidx;
////				             if          ( t<3)               j=	0;
//										 if          (( t>=3)&&( t<6))     t = t+1;
//										 else if     (( t>=6)&&( t<9))     t = t+2;
//										 else if     (( t>=9)&&( t<12))    t = t+3;				
//                     else if     (( t>=12)&&( t<17))  {t = t-12;	j=	50;		}
//				
//										// if	(menu_keyidx >=17)	{t =0; j=	0;  }
//											if	(menu_keyidx >=17)	//{t =0;}
//											{
//												 DrawRect(23,200,64 ,32,LCD_GREEN,0);    //选择框		
//											}
//											else
//											{
//												  DrawRect(122+ t*16,90 +j,16 ,32,LCD_GREEN,0);    //选择框				
//											}										 
//										 										
//				
//										 HexToStr(showASCIIbuf,  menu_keybuff,  17);			

//				             DrawLine(120,120,360,120,LCD_WHITE);    //画线	(IP)	
//				
//				             DrawLine(120,170,200,170,LCD_WHITE);    //画线	(端口号)
//				
////						         DrawRect(122+ t*16,90 +j,16 ,32,LCD_GREEN,0);    //选择框						
//				
//										 memcpy(Function_showbuf, "IP地址:   .   .   .   ",21);       //  拷贝	
//										 memcpy(Function_show2buf,"端口号:     ",11);       //  拷贝											 
//                   /*               拷贝IP地址                             */				
//										 memcpy(Function_showbuf+7, showASCIIbuf+1,1);       //  拷贝 1
//										 memcpy(Function_showbuf+8, showASCIIbuf+3,1);       //  拷贝 9
//										 memcpy(Function_showbuf+9, showASCIIbuf+5,1);       //  拷贝 2
//				
//										 memcpy(Function_showbuf+11, showASCIIbuf+7,1);      //  拷贝 1
//										 memcpy(Function_showbuf+12, showASCIIbuf+9,1);      //  拷贝 6  
//										 memcpy(Function_showbuf+13, showASCIIbuf+11,1);     //  拷贝 8
//				
//										 memcpy(Function_showbuf+15, showASCIIbuf+13,1);     //  拷贝 0   
//										 memcpy(Function_showbuf+16, showASCIIbuf+15,1);     //  拷贝 0						
//										 memcpy(Function_showbuf+17, showASCIIbuf+17,1);     //  拷贝 1   
//				
//										 memcpy(Function_showbuf+19, showASCIIbuf+19,1);     //  拷贝 1										
//										 memcpy(Function_showbuf+20, showASCIIbuf+21,1);     //  拷贝 0   
//										 memcpy(Function_showbuf+21, showASCIIbuf+23,1);     //  拷贝 3				
//                    /*               拷贝端口号                             */
//										 memcpy(Function_show2buf+7,  showASCIIbuf+25,1);     //  拷贝 2						
//										 memcpy(Function_show2buf+8,  showASCIIbuf+27,1);     //  拷贝 3   
//										 memcpy(Function_show2buf+9,  showASCIIbuf+29,1);     //  拷贝 2										
//										 memcpy(Function_show2buf+10, showASCIIbuf+31,1);     //  拷贝 3   
//										 memcpy(Function_show2buf+11, showASCIIbuf+33,1);     //  拷贝 2	

//				             PutString(5,10, "请按键输入服务器IP、端口") ;		 //第一行                                                               

//				             PutString(10,90, Function_showbuf) ;             //第二行
//										 
//			               PutString(10,140, Function_show2buf) ;          //第三行 
//			
//			               PutString(25,200,"确认              取消") ;   //第四行
//			
//										}            break;										
									



			  case  0x12:{  			    //网络恢复出厂设置						
										
					           PutString(5,10, "您是否需要将网络") ;		 //第一行  
					
					           PutString(5,50, "恢复到出厂值？") ;		 //第一行  
					
					           PutString(25,200,"确认              取消") ;   //第四行
										
										}
										break;
										
		  case   0x20:  {
																
											 PutString(5,10, "自动同步设备时间") ;		 //第一行  
						
//											 PutString(5,50, "所有刷卡记录？") ;		 //第一行  
						
											 PutString(25,200,"确认              取消") ;   //第四行									
									
										}           break;										
										
			
		  case  0x21:{                                  //时间、日期设置
				
								   menu_keyidx_MAX  =12;            //按键输入缓冲区大小 
				
				           t  = menu_keyidx;
				
									 if     (( t>=4)&&( t<6))    t = t+2;
				           else if(( t>=6)&&( t<8))    t = t+4;
				           else if(( t>=8)&&( t<10))   t = t+6;
				           else if(( t>=10)&&( t<12))  t = t+8;	
              //     if	(menu_keyidx >=12)	{t =0;}
						
											if	(menu_keyidx >=12)	//{t =0;}
											{
												 DrawRect(23,170,64 ,32,LCD_GREEN,0);    //选择框		
											}
											else
											{
												  DrawRect(10+ t*16,106,16 ,32,LCD_GREEN,0);    //选择框				
											}									 
									 
								 
						        // DrawRect(10+ t*16,106,16 ,32,LCD_GREEN,0);    //选择框
							
										 HexToStr(showASCIIbuf,  menu_keybuff,  12);
								    
				             memcpy(Function_showbuf, "    年  月  日  时  分",24);       //  拷贝	
										 memcpy(Function_showbuf,   showASCIIbuf+1,1);       //  拷贝 2  年
										 memcpy(Function_showbuf+1, showASCIIbuf+3,1);       //  拷贝 0
										 memcpy(Function_showbuf+2, showASCIIbuf+5,1);       //  拷贝 1
										 memcpy(Function_showbuf+3, showASCIIbuf+7,1);       //  拷贝 8
				
										 memcpy(Function_showbuf+6, showASCIIbuf+9,1);       //  拷贝 0  月
										 memcpy(Function_showbuf+7, showASCIIbuf+11,1);      //  拷贝 7
				
										 memcpy(Function_showbuf+10, showASCIIbuf+13,1);     //  拷贝 0   日
										 memcpy(Function_showbuf+11, showASCIIbuf+15,1);     //  拷贝 9			
				
										 memcpy(Function_showbuf+14, showASCIIbuf+17,1);     //  拷贝 1   时
										 memcpy(Function_showbuf+15, showASCIIbuf+19,1);     //  拷贝 6							
				
										 memcpy(Function_showbuf+18, showASCIIbuf+21,1);     //  拷贝 5   分
										 memcpy(Function_showbuf+19, showASCIIbuf+23,1);     //  拷贝 0						
				
										 /****************第一行*******************/	
									
											PutString(25,10, "请按键输入时间、日期") ;
											
										 /****************第二行*******************/	

											PutString_cn(10,106, Function_showbuf) ;
															
										 /****************第三行*******************/	

											PutString(25,170,"确认              取消") ;     
				
									}
			              break;
		  case  0x22:   	                                           //音量调节
									{
											menu_keyidx_MAX  =1;
											
											HexToStr(showASCIIbuf,  menu_keybuff,  1);
											
											memcpy(Function_showbuf,  "音量等级: ",10);       //  拷贝
	              //      memcpy(Function_showbuf+10, showASCIIbuf,2);     //
											
										/****************第一行*******************/	
									
											PutString(25,10, "请按键输入音量（0-9）") ;
											
										/****************第二行*******************/	

											PutString(200,106, showASCIIbuf) ;
											
											PutString_cn(40,106, Function_showbuf) ;

										/****************第三行*******************/	

											PutString(25,170,"确认              取消") ;         
										}				
										break;
					
		  case   0x30:  {
																
											 PutString(5,10, "您是否需要清除") ;		 //第一行  
						
											 PutString(5,50, "所有刷卡记录？") ;		 //第一行  
						
											 PutString(25,200,"确认              取消") ;   //第四行									
									
										}           break;
		  case   0x31:  {

											uint8_t  maxrecordbuf1[4];
											uint8_t  allrecordbuf1[4];		
				
											uint8_t  maxrecordbuf[8];
											uint8_t  allrecordbuf[8];		
				
                      getDectoBCD(MAX_RECORD , maxrecordbuf1, 3);				
                      getDectoBCD(Actual_Card_number , allrecordbuf1, 3);	   // Actual_Card_number
															
											HexToStr(maxrecordbuf,  maxrecordbuf1,  3);
											HexToStr(allrecordbuf,  allrecordbuf1,  3);
																						
											PutString(5,10, "总容量:") ;		 //第一行 
																							
											PutString(5,50, "已用数量:") ;		 //第一行  	
											PutString(150,10, maxrecordbuf);
											PutString(150,50, allrecordbuf);
											
										}           break;

		  case   0x32:  {			

											uint8_t i;
											
											uint8_t Query_Moneybuf[6]={0x00};
											
											uint8_t Query_MoneyASCIIbuf[14]={0x00};
											
											uint8_t Query_MoneyShowbuf[24]={"消费总额:        .  元"};
				
											getDectoBCD(Consum_Allmoney.i, Query_Moneybuf, 5);
											
											HexToStr(Query_MoneyASCIIbuf,  Query_Moneybuf,  5);
											
											
											for( i=0;i<8;i++)
											{
												Query_MoneyShowbuf[9+i] = Query_MoneyASCIIbuf[i];
											}

											for( i=0;i<2;i++)
											{
												Query_MoneyShowbuf[18+i] = Query_MoneyASCIIbuf[i+8];
											}

											PutString(5,100,Query_MoneyShowbuf);		//在指定位置开始显示ASCII字符串				
				
				
				
				
				
				
				
				             break;
										
			              }

		  case   0x33:  {
			
											 PutString(5,10, "您是否需要清除") ;		 //第一行  
						
											 PutString(5,50, "消费总额？") ;		 //第一行  
						
											 PutString(25,200,"确认              取消") ;   //第四行			
									
										}           break;
									
										
		  case   0x40: {                              //设定为变值扣费模式
			
					           PutString(5,10, "您是否将消费模式") ;		 //第一行  
				
					           PutString(5,50, "设置为变值扣费模式？") ;		 //第一行  				
				
				
				              PutString(25,170,"确认              取消") ; 
			
										}            break;
			
		  case   0x41:  {                              //设定为定值扣费模式
								      PutString(5,10, "您是否将消费模式") ;		 //第一行  
				
					            PutString(5,50, "设置为定值扣费模式？") ;		 //第一行  				
						
				              PutString(25,170,"确认              取消") ; 
							
										}           break;		
			
		  case   0x42:  {                              //设定为计次扣费模式       
											PutString(5,10, "您是否将消费模式") ;		 //第一行  
				
					            PutString(5,50, "设置为计次扣费模式？") ;		 //第一行  				
						
				              PutString(25,170,"确认              取消") ; 
			
										}           break;	

		  case   0x43:  {                              //设定为计次扣费模式       
											PutString(5,10, "您是否将消费模式") ;		 //第一行  
				
					            PutString(5,50, "设置为菜单扣费模式？") ;		 //第一行  				
						
				              PutString(25,170,"确认              取消") ; 
			
										}           break;	
										
			
										
			case   0x44:  {                    //设定定值扣费金额  
				
								        menu_keyidx_MAX  =16;               //按键输入缓冲区大小
								
											 t  = menu_keyidx;
											 if          (( t>=2)&&( t<4))    { t = t+1;            }
											 else if     (( t>=4)&&( t<6))    { t = t-4;  j=  35;   }
											 else if     (( t>=6)&&( t<8))    { t = t-3;	j=  35;	  }
											 else if     (( t>=8)&&( t<10))   { t = t-8;	j=	70;		}
											 else if     (( t>=10)&&( t<12))  { t = t-7;  j=	70;		}
											 else if     (( t>=12)&&( t<14))  { t = t-12; j=	105;  }
											 else if     (( t>=14)&&( t<16))  { t = t-11; j=	105;	}
							 							
									//		 if	(menu_keyidx >=16)	{t =0; j=	0;  }							
		
											if	(menu_keyidx >=16)	//{t =0;}
											{
												 DrawRect(23,200,64 ,32,LCD_GREEN,0);    //选择框		
											}
											else
											{
												 DrawRect(165+ t*16,50 +j,16 ,32,LCD_GREEN,0);    //选择框				
											}

											 
//												DrawRect(165+ t*16,50 +j,16 ,32,LCD_GREEN,0);    //选择框				

				                HexToStr(showASCIIbuf,  menu_keybuff,  16);
				
											  memcpy(Function_showbuf, "早餐金额: 00.00 元",18);       //  拷贝	
											  memcpy(Function_show2buf,"中餐金额: 00.00 元",18);       //  拷贝	
											  memcpy(Function_show3buf,"晚餐金额: 00.00 元",18);       //  拷贝	
											  memcpy(Function_show4buf,"夜宵金额: 00.00 元",18);       //  拷贝					
										   /*               拷贝金额                             */				
											  memcpy(Function_showbuf+10, showASCIIbuf+1,1);       //  拷贝 1
											  memcpy(Function_showbuf+11, showASCIIbuf+3,1);       //  拷贝 9
											  memcpy(Function_showbuf+13, showASCIIbuf+5,1);       //  拷贝 2
											  memcpy(Function_showbuf+14, showASCIIbuf+7,1);      //  拷贝 1
				
											  memcpy(Function_show2buf+10, showASCIIbuf+9,1);      //  拷贝 6  
											  memcpy(Function_show2buf+11, showASCIIbuf+11,1);     //  拷贝 8
											  memcpy(Function_show2buf+13, showASCIIbuf+13,1);     //  拷贝 0   
											  memcpy(Function_show2buf+14, showASCIIbuf+15,1);     //  拷贝 0		
				
											  memcpy(Function_show3buf+10, showASCIIbuf+17,1);     //  拷贝 1  
											  memcpy(Function_show3buf+11, showASCIIbuf+19,1);     //  拷贝 1										
											  memcpy(Function_show3buf+13, showASCIIbuf+21,1);     //  拷贝 0   
											  memcpy(Function_show3buf+14, showASCIIbuf+23,1);     //  拷贝 3				

											  memcpy(Function_show4buf+10,  showASCIIbuf+25,1);     //  拷贝 2						
											  memcpy(Function_show4buf+11,  showASCIIbuf+27,1);     //  拷贝 3   
											  memcpy(Function_show4buf+13,  showASCIIbuf+29,1);     //  拷贝 2										
											  memcpy(Function_show4buf+14, showASCIIbuf+31,1);     //  拷贝 3   
				
			                  PutString(50,10, "设置定值扣费金额") ;		   //第一行  				
				                PutString(5,50,  Function_showbuf) ;		 //第一行 
				                PutString(5,85,  Function_show2buf) ;		 //第一行 
                        PutString(5,120, Function_show3buf) ;		 //第一行  				
			                  PutString(5,155, Function_show4buf) ;		 //第一行 
											
                        PutString(25,200,"确认              取消") ; 		
				
											}          break;										
			
											
		  case   0x45:   {                   //设定定值扣费时段  
				
				               menu_keyidx_MAX  =32;               //按键输入缓冲区大小
				
											 t  = menu_keyidx;
				
											 if          (( t>=2)&&( t<4))    { t = t+1;            }
											 else if     (( t>=4)&&( t<6))    { t = t+3;            }
											 else if     (( t>=6)&&( t<8))    { t = t+4;	      		}
											 
											 else if     (( t>=8)&&( t<10))   { t = t-8;	j=	35;		}
											 else if     (( t>=10)&&( t<12))  { t = t-7;  j=	35;		}
											 else if     (( t>=12)&&( t<14))  { t = t-5;  j=	35;   }
											 else if     (( t>=14)&&( t<16))  { t = t-4;  j=	35;	  }
											 
											 else if     (( t>=16)&&( t<18))  { t = t-16;  j=	70;		}
											 else if     (( t>=18)&&( t<20))  { t = t-15;  j=	70;   }
											 else if     (( t>=20)&&( t<22))  { t = t-13;  j=	70;	  }	
											 else if     (( t>=22)&&( t<24))  { t = t-12;  j=	70;		}
											 
											 else if     (( t>=24)&&( t<26))  { t = t-24;  j=	105;  }
											 else if     (( t>=26)&&( t<28))  { t = t-23;  j=	105;	}
											 else if     (( t>=28)&&( t<30))  { t = t-21;  j=	105;  }
											 else if     (( t>=30)&&( t<32))  { t = t-20;  j=	105;	}
											 
											// if	(menu_keyidx >=32)	{t =0; j=	0;  }							
											if	(menu_keyidx >=32)	//{t =0;}
											{
												 DrawRect(23,200,64 ,32,LCD_GREEN,0);    //选择框		
											}
											else
											{
												 DrawRect(165+ t*16,50 +j,16 ,32,LCD_GREEN,0);    //选择框					
											}								
											 
											 
											 
											 
//												DrawRect(165+ t*16,50 +j,16 ,32,LCD_GREEN,0);    //选择框				

				                HexToStr(showASCIIbuf,  menu_keybuff,  32);
				
											  memcpy(Function_showbuf, "早餐时段: 00.00--00.00",22);       //  拷贝	
											  memcpy(Function_show2buf,"中餐时段: 00.00--00.00",22);       //  拷贝	
											  memcpy(Function_show3buf,"晚餐时段: 00.00--00.00",22);       //  拷贝	
											  memcpy(Function_show4buf,"夜宵时段: 00.00--00.00",22);       //  拷贝					
										   /*               拷贝IP地址                             */				
											  memcpy(Function_showbuf+10,  showASCIIbuf+1,1);       //  拷贝 
											  memcpy(Function_showbuf+11,  showASCIIbuf+3,1);       //  拷贝 
											  memcpy(Function_showbuf+13,  showASCIIbuf+5,1);       //  拷贝 
											  memcpy(Function_showbuf+14,  showASCIIbuf+7,1);      //  拷贝 
											  memcpy(Function_showbuf+17,  showASCIIbuf+9,1);      //  拷贝 
											  memcpy(Function_showbuf+18,  showASCIIbuf+11,1);     //  拷贝 
											  memcpy(Function_showbuf+20,  showASCIIbuf+13,1);     //  拷贝   
											  memcpy(Function_showbuf+21,  showASCIIbuf+15,1);     //  拷贝 		
				
											  memcpy(Function_show2buf+10, showASCIIbuf+17,1);     //  拷贝   
											  memcpy(Function_show2buf+11, showASCIIbuf+19,1);     //  拷贝 										
											  memcpy(Function_show2buf+13, showASCIIbuf+21,1);     //  拷贝    
											  memcpy(Function_show2buf+14, showASCIIbuf+23,1);     //  拷贝 			
											  memcpy(Function_show2buf+17, showASCIIbuf+25,1);     //  拷贝 						
											  memcpy(Function_show2buf+18, showASCIIbuf+27,1);     //  拷贝    
											  memcpy(Function_show2buf+20, showASCIIbuf+29,1);     //  拷贝 										
											  memcpy(Function_show2buf+21, showASCIIbuf+31,1);     //  拷贝  				
								
											  memcpy(Function_show3buf+10,  showASCIIbuf+33,1);     //  拷贝 
											  memcpy(Function_show3buf+11,  showASCIIbuf+35,1);     //  拷贝 
											  memcpy(Function_show3buf+13,  showASCIIbuf+37,1);     //  拷贝 
											  memcpy(Function_show3buf+14,  showASCIIbuf+39,1);     //  拷贝 
											  memcpy(Function_show3buf+17,  showASCIIbuf+41,1);     //  拷贝 
											  memcpy(Function_show3buf+18,  showASCIIbuf+43,1);     //  拷贝   
											  memcpy(Function_show3buf+20,  showASCIIbuf+45,1);     //  拷贝 		
											  memcpy(Function_show3buf+21,  showASCIIbuf+47,1);     //  拷贝  
												
											  memcpy(Function_show4buf+10,  showASCIIbuf+49,1);     //  拷贝 										
											  memcpy(Function_show4buf+11,  showASCIIbuf+51,1);     //  拷贝    
											  memcpy(Function_show4buf+13,  showASCIIbuf+53,1);     //  拷贝 			
											  memcpy(Function_show4buf+14,  showASCIIbuf+55,1);     //  拷贝 						
											  memcpy(Function_show4buf+17,  showASCIIbuf+57,1);     //  拷贝    
											  memcpy(Function_show4buf+18,  showASCIIbuf+59,1);     //  拷贝 										
											  memcpy(Function_show4buf+20,  showASCIIbuf+61,1);     //  拷贝 
											  memcpy(Function_show4buf+21,  showASCIIbuf+63,1);     //  拷贝 

				
			                  PutString(50,10, "设置定值扣费时段") ;		       //第一行  
				                PutString(5,50,  Function_showbuf) ;		       //第一行 
				                PutString(5,85,  Function_show2buf) ;		       //第一行 
                        PutString(5,120, Function_show3buf) ;		       //第一行  				
			                  PutString(5,155, Function_show4buf) ;		       //第一行 
                        PutString(25,200,"确认              取消") ; 				
						
			               }          break;		
			
			case   0x46:    {      //设定菜单扣费金额
				
				
	                      menu_keyidx_MAX  =36;               //按键输入缓冲区大小

			                	t  = menu_keyidx;
				
											 if          (( t>=2)&&( t<4))    { t = t+1;          z =0;  }
											 else if     (( t>=4)&&( t<6))    { t = t+3;          z =108;   }
											 else if     (( t>=6)&&( t<8))    { t = t+4;	      	z =108; 	}
											 
											 else if     (( t>=8)&&( t<10))   { t = t-8;	j=	30;	z =0; 	}
											 else if     (( t>=10)&&( t<12))  { t = t-7;  j=	30;	z =0; 	}
											 else if     (( t>=12)&&( t<14))  { t = t-5;  j=	30; z =108;  }
											 else if     (( t>=14)&&( t<16))  { t = t-4;  j=	30;	z =108;  }
											 
											 else if     (( t>=16)&&( t<18))  { t = t-16;  j=	60;	z =0;	}
											 else if     (( t>=18)&&( t<20))  { t = t-15;  j=	60; z =0;  }
											 else if     (( t>=20)&&( t<22))  { t = t-13;  j=	60;	z =108;  }	
											 else if     (( t>=22)&&( t<24))  { t = t-12;  j=	60;	z =108;	}
											 
											 else if     (( t>=24)&&( t<26))  { t = t-24;  j=	90; z =0; }
											 else if     (( t>=26)&&( t<28))  { t = t-23;  j=	90;	z =0; }
											 else if     (( t>=28)&&( t<30))  { t = t-21;  j=	90; z =108; }
											 else if     (( t>=30)&&( t<32))  { t = t-20;  j=	90; z =108; }										
												
											 else if     (( t>=32)&&( t<34))  { t = t-32;  j=	120; z =0; }
											 else if     (( t>=34)&&( t<36))  { t = t-31;  j=	120;	z =0; }		

											 
											//	DrawRect(88+ t*12 +z,55+j ,12 ,16,LCD_GREEN,0);    //选择框				
	
											if	(menu_keyidx >=36)	//{t =0;}
											{
												 DrawRect(23,200,64 ,32,LCD_GREEN,0);    //选择框		
											}
											else
											{
											   DrawRect(88+ t*12 +z,55+j ,12 ,16,LCD_GREEN,0);    //选择框						
											}								
											 


											 
				                HexToStr(showASCIIbuf,  menu_keybuff,  36);
			
											  memcpy(Function_showbuf, "按键1: 00.00 元  按键2:00.00",32);       //  拷贝	
											  memcpy(Function_show2buf,"按键3: 00.00 元  按键4:00.00",32);       //  拷贝	
											  memcpy(Function_show3buf,"按键5: 00.00 元  按键6:00.00",32);       //  拷贝	
											  memcpy(Function_show4buf,"按键7: 00.00 元  按键8:00.00",32);       //  拷贝					
											  memcpy(Function_show5buf,"按键9: 00.00 元  ",18);       //  拷贝													
												
												/*             拷贝消费金额     */
											  memcpy(Function_showbuf+7,  showASCIIbuf+1,1);       //  拷贝 1 
											  memcpy(Function_showbuf+8,  showASCIIbuf+3,1);       //  拷贝 1
											  memcpy(Function_showbuf+10, showASCIIbuf+5,1);       //  拷贝 1
											  memcpy(Function_showbuf+11, showASCIIbuf+7,1);       //  拷贝 1
				
											  memcpy(Function_showbuf+23, showASCIIbuf+9,1);      //  拷贝 2  
											  memcpy(Function_showbuf+24, showASCIIbuf+11,1);     //  拷贝 2 
											  memcpy(Function_showbuf+26, showASCIIbuf+13,1);     //  拷贝 2   
											  memcpy(Function_showbuf+27, showASCIIbuf+15,1);     //  拷贝 2		
				
											  memcpy(Function_show2buf+7,  showASCIIbuf+17,1);     //  拷贝 3  
											  memcpy(Function_show2buf+8,  showASCIIbuf+19,1);     //  拷贝 3										
											  memcpy(Function_show2buf+10, showASCIIbuf+21,1);     //  拷贝 3   
											  memcpy(Function_show2buf+11, showASCIIbuf+23,1);     //  拷贝 3				

											  memcpy(Function_show2buf+23,  showASCIIbuf+25,1);     //  拷贝 4						
											  memcpy(Function_show2buf+24,  showASCIIbuf+27,1);     //  拷贝 4   
											  memcpy(Function_show2buf+26,  showASCIIbuf+29,1);     //  拷贝 4										
											  memcpy(Function_show2buf+27,  showASCIIbuf+31,1);     //  拷贝 4   				
																								
											  memcpy(Function_show3buf+7,  showASCIIbuf+33,1);     //  拷贝 5  
											  memcpy(Function_show3buf+8,  showASCIIbuf+35,1);     //  拷贝 5										
											  memcpy(Function_show3buf+10, showASCIIbuf+37,1);     //  拷贝 5   
											  memcpy(Function_show3buf+11, showASCIIbuf+39,1);     //  拷贝 5				

											  memcpy(Function_show3buf+23,  showASCIIbuf+41,1);     //  拷贝 6						
											  memcpy(Function_show3buf+24,  showASCIIbuf+43,1);     //  拷贝 6   
											  memcpy(Function_show3buf+26,  showASCIIbuf+45,1);     //  拷贝 6										
											  memcpy(Function_show3buf+27,  showASCIIbuf+47,1);     //  拷贝 6   																
											
											  memcpy(Function_show4buf+7,  showASCIIbuf+49,1);     //  拷贝 7  
											  memcpy(Function_show4buf+8,  showASCIIbuf+51,1);     //  拷贝 7										
											  memcpy(Function_show4buf+10, showASCIIbuf+53,1);     //  拷贝 7   
											  memcpy(Function_show4buf+11, showASCIIbuf+55,1);     //  拷贝 7				

											  memcpy(Function_show4buf+23,  showASCIIbuf+57,1);     //  拷贝 8						
											  memcpy(Function_show4buf+24,  showASCIIbuf+59,1);     //  拷贝 8   
											  memcpy(Function_show4buf+26,  showASCIIbuf+61,1);     //  拷贝 8										
											  memcpy(Function_show4buf+27,  showASCIIbuf+63,1);     //  拷贝 8   																

											  memcpy(Function_show5buf+7,   showASCIIbuf+65,1);     //  拷贝 9						
											  memcpy(Function_show5buf+8,   showASCIIbuf+67,1);     //  拷贝 9   
											  memcpy(Function_show5buf+10,  showASCIIbuf+69,1);     //  拷贝 9										
											  memcpy(Function_show5buf+11,  showASCIIbuf+71,1);     //  拷贝 9   	
																							
			                  PutString(50,10, "设置菜单消费金额") ;		       //第一行  
												
						            SetFontType((LCD_ASC12_FONT<<4)|LCD_HZK24_FONT);											
												
				                PutString(5,50,  Function_showbuf) ;		       //第1行 
				                PutString(5,80,  Function_show2buf) ;		       //第2行 
                        PutString(5,110, Function_show3buf) ;		       //第3行  				
			                  PutString(5,140, Function_show4buf) ;		       //第4行 
			                  PutString(5,170, Function_show5buf) ;		       //第5行 
												
                        PutString(25,200,"确认              取消") ; 				
																			
											}         break;												
	
			  case  0x47:   	                                           //设置消费限额
									{
								
											menu_keyidx_MAX  =6;
//											
//											t  = menu_keyidx;

//		//									if               (( t>=0)&&( t<4))   { t = t;            }										
//											 if          (( t>=4)&&( t<6))   { t = t+1;            }

//	
//																																																	
//											if	(menu_keyidx >=6)	//{t =0;}
//											{
//												 DrawRect(23,170,64 ,32,LCD_GREEN,0);    //选择框		
//											}										 																		
//											else
//											{
//												 DrawRect(122+ t*16,106,16 ,32,LCD_GREEN,0);    //选择框	
//											}										
//										
										 HexToStr(showASCIIbuf,  menu_keybuff,  menu_keyidx_MAX);
											
										 memcpy(Function_showbuf,"金 额:     .  元",17);       //  拷贝
											
                   /*               金额                             */											 
										 memcpy(Function_showbuf+7,  showASCIIbuf+1,1);       //  拷贝 1
										 memcpy(Function_showbuf+8,  showASCIIbuf+3,1);       //  拷贝 2
										 memcpy(Function_showbuf+9,  showASCIIbuf+5,1);       //  拷贝 3
										 memcpy(Function_showbuf+10, showASCIIbuf+7,1);       //  拷贝 3											
										 memcpy(Function_showbuf+12, showASCIIbuf+9,1);       //  拷贝 3											
										 memcpy(Function_showbuf+13, showASCIIbuf+11,1);      //  拷贝 3												
																						
//											memcpy(Function_showbuf,  "金额: ",10);       //  拷贝
//	                    memcpy(Function_showbuf+10, showASCIIbuf,2);     //
											
										/****************第一行*******************/	
									
											PutString(50,10, "  离线消费限制金额：") ;
											
										/****************第二行*******************/	

//											PutString(60,50, "（最大金额500元）") ;	
		               /****************第三行*******************/									

											PutString(10,106, Function_showbuf) ;

										/****************第四行*******************/	

											PutString(25,170,"确认              取消") ;         
										}				
										break;
																												
																					
			case   0x48:  {                    //设定扣费金额  
				
								        menu_keyidx_MAX  =16;               //按键输入缓冲区大小
								
											 t  = menu_keyidx;
											 if          (( t>=2)&&( t<4))    { t = t+1;            }
											 else if     (( t>=4)&&( t<6))    { t = t-4;  j=  35;   }
											 else if     (( t>=6)&&( t<8))    { t = t-3;	j=  35;	  }
											 else if     (( t>=8)&&( t<10))   { t = t-8;	j=	70;		}
											 else if     (( t>=10)&&( t<12))  { t = t-7;  j=	70;		}
											 else if     (( t>=12)&&( t<14))  { t = t-12; j=	105;  }
											 else if     (( t>=14)&&( t<16))  { t = t-11; j=	105;	}
							 							
									//		 if	(menu_keyidx >=16)	{t =0; j=	0;  }							

											if	(menu_keyidx >=16)	//{t =0;}
											{
												 DrawRect(23,200,64 ,32,LCD_GREEN,0);    //选择框		
											}
											else
											{
												 DrawRect(181+ t*16,50 +j,16 ,32,LCD_GREEN,0);    //选择框					
											}

											 
							//					DrawRect(181+ t*16,50 +j,16 ,32,LCD_GREEN,0);    //选择框				

				                HexToStr(showASCIIbuf,  menu_keybuff,  16);
				
											  memcpy(Function_showbuf, "时段1金额: 00.00 元",19);       //  拷贝	
											  memcpy(Function_show2buf,"时段2金额: 00.00 元",19);       //  拷贝	
											  memcpy(Function_show3buf,"时段3金额: 00.00 元",19);       //  拷贝	
											  memcpy(Function_show4buf,"时段4金额: 00.00 元",19);       //  拷贝					
										   /*               拷贝IP地址                             */				
											  memcpy(Function_showbuf+11, showASCIIbuf+1,1);       //  拷贝 1
											  memcpy(Function_showbuf+12, showASCIIbuf+3,1);       //  拷贝 9
											  memcpy(Function_showbuf+14, showASCIIbuf+5,1);       //  拷贝 2
											  memcpy(Function_showbuf+15, showASCIIbuf+7,1);      //  拷贝 1
				
											  memcpy(Function_show2buf+11, showASCIIbuf+9,1);      //  拷贝 6  
											  memcpy(Function_show2buf+12, showASCIIbuf+11,1);     //  拷贝 8
											  memcpy(Function_show2buf+14, showASCIIbuf+13,1);     //  拷贝 0   
											  memcpy(Function_show2buf+15, showASCIIbuf+15,1);     //  拷贝 0		
				
											  memcpy(Function_show3buf+11, showASCIIbuf+17,1);     //  拷贝 1  
											  memcpy(Function_show3buf+12, showASCIIbuf+19,1);     //  拷贝 1										
											  memcpy(Function_show3buf+14, showASCIIbuf+21,1);     //  拷贝 0   
											  memcpy(Function_show3buf+15, showASCIIbuf+23,1);     //  拷贝 3				

											  memcpy(Function_show4buf+11,  showASCIIbuf+25,1);     //  拷贝 2						
											  memcpy(Function_show4buf+12,  showASCIIbuf+27,1);     //  拷贝 3   
											  memcpy(Function_show4buf+14,  showASCIIbuf+29,1);     //  拷贝 2										
											  memcpy(Function_show4buf+15, showASCIIbuf+31,1);     //  拷贝 3   
				
			                  PutString(50,10, "设置时段金额") ;		   //第一行  				
				                PutString(5,50,  Function_showbuf) ;		 //第一行 
				                PutString(5,85,  Function_show2buf) ;		 //第一行 
                        PutString(5,120, Function_show3buf) ;		 //第一行  				
			                  PutString(5,155, Function_show4buf) ;		 //第一行 
											
                        PutString(25,200,"确认              取消") ; 		
				
											}          break;										
			
											
		  case   0x49:   {                   //设定扣费时段  
				
				               menu_keyidx_MAX  =32;               //按键输入缓冲区大小
				
											 t  = menu_keyidx;
				
											 if          (( t>=2)&&( t<4))    { t = t+1;            }
											 else if     (( t>=4)&&( t<6))    { t = t+3;            }
											 else if     (( t>=6)&&( t<8))    { t = t+4;	      		}
											 
											 else if     (( t>=8)&&( t<10))   { t = t-8;	j=	35;		}
											 else if     (( t>=10)&&( t<12))  { t = t-7;  j=	35;		}
											 else if     (( t>=12)&&( t<14))  { t = t-5;  j=	35;   }
											 else if     (( t>=14)&&( t<16))  { t = t-4;  j=	35;	  }
											 
											 else if     (( t>=16)&&( t<18))  { t = t-16;  j=	70;		}
											 else if     (( t>=18)&&( t<20))  { t = t-15;  j=	70;   }
											 else if     (( t>=20)&&( t<22))  { t = t-13;  j=	70;	  }	
											 else if     (( t>=22)&&( t<24))  { t = t-12;  j=	70;		}
											 
											 else if     (( t>=24)&&( t<26))  { t = t-24;  j=	105;  }
											 else if     (( t>=26)&&( t<28))  { t = t-23;  j=	105;	}
											 else if     (( t>=28)&&( t<30))  { t = t-21;  j=	105;  }
											 else if     (( t>=30)&&( t<32))  { t = t-20;  j=	105;	}
											 
										//	 if	(menu_keyidx >=32)	{t =0; j=	0;  }							

											if	(menu_keyidx >=32)	//{t =0;}
											{
												 DrawRect(23,200,64 ,32,LCD_GREEN,0);    //选择框		
											}
											else
											{
												 DrawRect(117+ t*16,50 +j,16 ,32,LCD_GREEN,0);    //选择框				
											}											 

											 
											//	DrawRect(117+ t*16,50 +j,16 ,32,LCD_GREEN,0);    //选择框				

				                HexToStr(showASCIIbuf,  menu_keybuff,  32);
				
											  memcpy(Function_showbuf, "时段1: 00.00--00.00",19);       //  拷贝	
											  memcpy(Function_show2buf,"时段2: 00.00--00.00",19);       //  拷贝	
											  memcpy(Function_show3buf,"时段3: 00.00--00.00",19);       //  拷贝	
											  memcpy(Function_show4buf,"时段4: 00.00--00.00",19);       //  拷贝					
										   /*               拷贝IP地址                             */				
											  memcpy(Function_showbuf+7,  showASCIIbuf+1,1);       //  拷贝 
											  memcpy(Function_showbuf+8,  showASCIIbuf+3,1);       //  拷贝 
											  memcpy(Function_showbuf+10,  showASCIIbuf+5,1);       //  拷贝 
											  memcpy(Function_showbuf+11,  showASCIIbuf+7,1);      //  拷贝 
											  memcpy(Function_showbuf+14,  showASCIIbuf+9,1);      //  拷贝 
											  memcpy(Function_showbuf+15,  showASCIIbuf+11,1);     //  拷贝 
											  memcpy(Function_showbuf+17,  showASCIIbuf+13,1);     //  拷贝   
											  memcpy(Function_showbuf+18,  showASCIIbuf+15,1);     //  拷贝 		
				
											  memcpy(Function_show2buf+7, showASCIIbuf+17,1);     //  拷贝   
											  memcpy(Function_show2buf+8, showASCIIbuf+19,1);     //  拷贝 										
											  memcpy(Function_show2buf+10, showASCIIbuf+21,1);     //  拷贝    
											  memcpy(Function_show2buf+11, showASCIIbuf+23,1);     //  拷贝 			
											  memcpy(Function_show2buf+14, showASCIIbuf+25,1);     //  拷贝 						
											  memcpy(Function_show2buf+15, showASCIIbuf+27,1);     //  拷贝    
											  memcpy(Function_show2buf+17, showASCIIbuf+29,1);     //  拷贝 										
											  memcpy(Function_show2buf+18, showASCIIbuf+31,1);     //  拷贝  				
								
											  memcpy(Function_show3buf+7,  showASCIIbuf+33,1);     //  拷贝 
											  memcpy(Function_show3buf+8,  showASCIIbuf+35,1);     //  拷贝 
											  memcpy(Function_show3buf+10,  showASCIIbuf+37,1);     //  拷贝 
											  memcpy(Function_show3buf+11,  showASCIIbuf+39,1);     //  拷贝 
											  memcpy(Function_show3buf+14,  showASCIIbuf+41,1);     //  拷贝 
											  memcpy(Function_show3buf+15,  showASCIIbuf+43,1);     //  拷贝   
											  memcpy(Function_show3buf+17,  showASCIIbuf+45,1);     //  拷贝 		
											  memcpy(Function_show3buf+18,  showASCIIbuf+47,1);     //  拷贝  
												
											  memcpy(Function_show4buf+7,  showASCIIbuf+49,1);     //  拷贝 										
											  memcpy(Function_show4buf+8,  showASCIIbuf+51,1);     //  拷贝    
											  memcpy(Function_show4buf+10,  showASCIIbuf+53,1);     //  拷贝 			
											  memcpy(Function_show4buf+11,  showASCIIbuf+55,1);     //  拷贝 						
											  memcpy(Function_show4buf+14,  showASCIIbuf+57,1);     //  拷贝    
											  memcpy(Function_show4buf+15,  showASCIIbuf+59,1);     //  拷贝 										
											  memcpy(Function_show4buf+17,  showASCIIbuf+61,1);     //  拷贝 
											  memcpy(Function_show4buf+18,  showASCIIbuf+63,1);     //  拷贝 

				
			                  PutString(50,10, "设置扣费时段") ;		       //第一行  
				                PutString(5,50,  Function_showbuf) ;		       //第一行 
				                PutString(5,85,  Function_show2buf) ;		       //第一行 
                        PutString(5,120, Function_show3buf) ;		       //第一行  				
			                  PutString(5,155, Function_show4buf) ;		       //第一行 
                        PutString(25,200,"确认              取消") ; 				
						
			               }          break;		
																											
		  case   0x70:  {						                                        //设备信息
											PutString(5,10,  "设备名称   科坦消费机") ;								

											PutString(5,60,  "机器型号   KETAN2166") ;
											
											PutString(5,110, "机器编号    20190301") ;

                      PutString(5,160, "出厂日期    20190307") ;

											PutString(5,210, "版本号      20181105") ; 
										
										}           break;
			
		  case   0x71:  {                //固件信息
			
											PutString(5,10 , "固件版本:Ver 2019-04-24") ;								
			
				              PutString(5,60 , "作者:1101000011101100") ;
				
                      PutString(5,110, "     1100100010110101");
				
				              PutString(5,160, "     1100011110111111");
								
										}        break;										 
			
		  case   0x72:  {
			
											PutString(0,10,  "生产厂商：") ;								

				              PutString(10,60,  "广州科坦电子技术有限公司") ;
				
											PutString(0,110,  "联系电话:020-32050029") ;				
					
											PutString(0,160,  "网址:www.ketansoft.com") ;			
								
				         //     PutString(0,210,  "联系邮箱:372396764@qq.com") ;	
				
										}        break;											//厂商信息	
																			
			default:      break;
			
		}	
}


/****************************************************
	
	LCD12864 显示查询金额
*****************************************************/

void LCD_Disp_Query_Money(void)
{

	PutString(120,10,"查询余额");		//在指定位置开始显示ASCII字符串

  PutString(150,100,"请刷卡");		//在指定位置开始显示ASCII字符串
	
	
}


void LCD_Disp_Refund_Money(void)
{
	uint8_t   Refund_readbuf[RECORD_SIZE]={0};
	uint32_t  addr=0;
	
	uint8_t   RefundasciiMoneybuf[10] ={0x00};
	uint8_t   RefundasciiCardbuf[10]={0x00};
	
	uint8_t   Refundshowbuf1[]={"退款金额:000000.00元"};
	uint8_t   Refundshowbuf2[]={"卡    号:         "};	
	
	uint16_t  i=1;
	
	
	SetBG_Color(LCD_DARK);     //黑底
	
	SetDisplayInvert(0);        //字符显示背景色开关
	
	SetFontType((LCD_ASC16_FONT<<4)|LCD_HZK32_FONT);
	
	SetFG_Color(LCD_WHITE);
	
  addr =  (recordcount-1) * RECORD_SIZE;                        //存储起始地址+（30字节为一条信息*信息条数=已占用字节数）	
	
	SPI_Flash_Read(Refund_readbuf ,addr,  RECORD_SIZE);
	
	while((Refund_readbuf[25] != 0X00)&&(Refund_readbuf[25] != 0X6f))
	{
	
	  addr =  ((recordcount-1)-i) * RECORD_SIZE;                        //存储起始地址+（30字节为一条信息*信息条数=已占用字节数）	
	
	  SPI_Flash_Read(Refund_readbuf ,addr,  RECORD_SIZE);
	
	  i++;
		
		if(i>(recordcount-2))
		{
		return;
		}
		
	}

//		MyStrCPY(RefundMoneybuf ,    recorddata, 30);    //卡号拷贝	
	
	
		if(Refund_readbuf[23] != 0X00)         //错误代码   1字节
		{	
			MyStrCPY(RefundMoneybuf , def_Consum_Amount, 4);    //拷贝*默认消费金额  00
		}
	
		if(Refund_readbuf[25] == 0X6F)         //通讯命令    1字节
		{	
			MyStrCPY(RefundMoneybuf , def_Consum_Amount, 4);    //拷贝*默认消费金额  00
		}
		else
		{
			MyStrCPY(RefundMoneybuf,  Refund_readbuf+14, 4);
		}
		
		if( MyStrEQ(def_Consum_Amount, RefundMoneybuf, 4	))
		{
		
		  MyStrCPY(RefundICcardbuf ,    def_Consum_Amount, 4);    //卡号拷贝
		}
		else
		{
			MyStrCPY(RefundICcardbuf ,    Refund_readbuf+4, 4);    //卡号拷贝	
		
		}
		
	HexToStr(RefundasciiMoneybuf, RefundMoneybuf,  4);    //金额转换
	
	HexToStr(RefundasciiCardbuf,  RefundICcardbuf,  4);	   //卡号转换

  MyStrCPY(Refundshowbuf1+9 ,   RefundasciiMoneybuf, 6);    //金额元拷贝
	
  MyStrCPY(Refundshowbuf1+16,   RefundasciiMoneybuf+6, 2);  //金额角拷贝
	
	MyStrCPY(Refundshowbuf2+9,    RefundasciiCardbuf, 8);        //卡号拷贝
	
	PutString(120,10,"退款请刷卡");		//在指定位置开始显示ASCII字符串

  PutString(10,100,Refundshowbuf1);		//在指定位置开始显示ASCII字符串
	
  PutString(10,150,Refundshowbuf2);		//在指定位置开始显示ASCII字符串	
	
	
}
































