#include "Head.h"

#include "LCD12864_Config.h"

u8  Show_moneybuf[20]={0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X20,0X20,0X20,0X20,0X20,0X20};  //消费金额

uint8_t LCDtimebuf[16]={0};

uint32_t  Display_Time_outcount = 0 ;


/****************关闭待机显示*******************/
void  Clear_Standby_Display(void)
{
	showStandby=0;          //关闭待机显示

	Standbycount=0;

}


/****************关闭待机显示*******************/
void  Clear_Standby_Display_Time(uint32_t count)
{
	
	
	showStandby=0;          //关闭待机显示

	Standbycount = SECOND_CYCLE*count;

//	statuscnt = count;
	
	Show_Refresh_coun =SECOND_CYCLE*count;
	
  Standbytime = SECOND_CYCLE*count;
	
}






/****************最终清除刷卡数据*******************/
void  EndClear_Pay_Card_Data(void)
{
//	memset(ICcard_frequencybf ,0,2);         //次数清0
	
//	memset(blk0+8 ,0,8);         //姓名清0
	
	
	
}

		/*************待机时显示时间************/
void LCD12864_Standby(void)	
	{
		
	u8 const LCDweekASCII[]={"日一二三四五六七一"};	
	
	DS1302_Read_Time();       //读时间
	
	HexToStr(LCDtimebuf,  time_buf,  8);	

	/****************第一行*******************/
	if(ec20_device_info.netWork)
	{
	 LCD_Write_String(0,1,"广汽研究院  4G");
	}
	
	else
  {
	 LCD_Write_String(0,1,"广汽研究院 4Gx");
	}
	
	/****************第二行*******************/

	LCD_Write_String_NUM(2,1,LCDtimebuf,4);          //年
	LCD_Write_String(2,3,"年");
	LCD_Write_String_NUM(2,4,LCDtimebuf+4,2);       //月
	LCD_Write_String(2,5,"月");
  LCD_Write_String_NUM(2,6,LCDtimebuf+6,2);        //日
	LCD_Write_String(2,7,"日");
	
	/****************第三行*******************/
	
	LCD_Write_String_NUM(3,0,LCDtimebuf+8,2);          //时
	LCD_Write_String(3,1,"时");
	LCD_Write_String_NUM(3,2,LCDtimebuf+10,2);         //分
	LCD_Write_String(3,3,"分");
  LCD_Write_String_NUM(3,4,LCDtimebuf+12,2);         //秒
	LCD_Write_String(3,5,"秒");
	
	LCD_Write_String_NUM(3,7,LCDweekASCII+time_buf[7]*2,2);        //周
	
	
	LCD_Write_String(4,3,"请刷卡") ;

	}

/****************************************************
	
	LCD12864 显示按键
*****************************************************/

void LCD12864_ShowKeyValue(void)
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
	
	HexToStr(LCDtimebuf,  time_buf,  8);	
	
	/****************第一行*******************/

	LCD_Write_String_NUM(1,1,LCDtimebuf,4);          //年
	LCD_Write_String(1,3,"年");
	LCD_Write_String_NUM(1,4,LCDtimebuf+4,2);       //月
	LCD_Write_String(1,5,"月");
  LCD_Write_String_NUM(1,6,LCDtimebuf+6,2);        //日
	LCD_Write_String(1,7,"日");
	
	
///****************第三行*******************/

	LCD_Write_String(3,0,"金额：");
	
	LCD_Write_String(3,3,tmp);
	
}


/****************************************************
	
	LCD12864 显示刷卡内容

输入 : type   表示错误代码

*****************************************************/

void LCD12864_ShowPlay_Card(uint8_t  type)
{
  uint8_t t = 0;
	
	uint8_t    Namebuff[10]   ={0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20};    //姓名
	
	uint8_t    US_Balance[8]   ={0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20};    //余额
	uint8_t    CO_Amount[8]    ={0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20};  //金额

//	MyStrCPY(Namebuff,blk0+8 , 8);   //姓名
  MyStrCPY(Namebuff, Server_Returndata +18, 10);        //拷贝姓名
	
//	RS485_Send_Data(Server_Returndata +18, 10);                //
	
	
//	HexToStr(US_Balance,  UserBalance,   4);   //余额
//	HexToStr(CO_Amount,  Consum_Amount,  4);   //金额
	
	Clear_Standby_Display();     //关闭待机显示
	Clr_Scr() ;            //LCD12864清屏函数
	delay_ms(1);
	LCDBLA_H;             //打开背光

	
/****************第一行*******************/
if(type==PAY_NO_MONEY_ERR)
{

 LCD_Write_String(1,0,"余额不足") ;	
}		
else 
{
	LCD_Write_String_NUM(1,1,LCDtimebuf,4);          //年
	LCD_Write_String(1,3,"年");
	LCD_Write_String_NUM(1,4,LCDtimebuf+4,2);       //月
	LCD_Write_String(1,5,"月");
  LCD_Write_String_NUM(1,6,LCDtimebuf+6,2);        //日
	LCD_Write_String(1,7,"日");
}
if((type==PAY_OK)||(type==PAY_NO_MONEY_ERR))                                  //正确
	{
		
   SYN6288_Send(SYN6288CMD_VOICE_PLAY ,SYN6288CMDPARAM_PLAY_MUSIC0,"谢谢" ,4);
		
	 //LCD_Write_String(4,1,"谢谢，请通行") ;
		
		
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

/******************************* end ****************************************/	

	
	
/****************第二行*******************/

	LCD_Write_String(2,0,"姓名：");

  LCD_Write_String_NUM(2,3,Namebuff,10);

/****************第三行*******************/

	LCD_Write_String(3,0,"消费");

	LCD_Write_Number(11);          // 数字显示函数 ：
		
	LCD_Write_Number(CO_Amount[0]);// 数字显示函数
	LCD_Write_Number(CO_Amount[1]);// 数字显示函数
	LCD_Write_Number(CO_Amount[2]);// 数字显示函数
	LCD_Write_Number(CO_Amount[3]);// 数字显示函数
	LCD_Write_Number(CO_Amount[4]);// 数字显示函数
	LCD_Write_Number(CO_Amount[5]);// 数字显示函数
	LCD_Write_Number(12);          // 数字显示函数 .
	LCD_Write_Number(CO_Amount[6]);// 数字显示函数
	LCD_Write_Number(CO_Amount[7]);// 数字显示函数


	LCD_Write_String(3,7,"元");

/****************第四行*******************/	
	
	LCD_Write_String(4,0,"余额");

	LCD_Write_Number(11);           // 数字显示函数 ：
		
	LCD_Write_Number(US_Balance[0]);// 数字显示函数
	LCD_Write_Number(US_Balance[1]);// 数字显示函数
	LCD_Write_Number(US_Balance[2]);// 数字显示函数
	LCD_Write_Number(US_Balance[3]);// 数字显示函数
	LCD_Write_Number(US_Balance[4]);// 数字显示函数
	LCD_Write_Number(US_Balance[5]);// 数字显示函数
	LCD_Write_Number(12);           // 数字显示函数 .
	LCD_Write_Number(US_Balance[6]);// 数字显示函数
	LCD_Write_Number(US_Balance[7]);// 数字显示函数

	LCD_Write_String(4,7,"元");		
	
	
}

//else if(type==PAY_NO_MONEY_ERR)                //余额不足
//	{
//		
////		SC50X0_SDA(0x1D);       //
//		
////	  LCD_Write_String(4,0,"余额不足") ;
//	}


else if(type==PAY_WHITEALLOW_WRR)                //白名单错误
	{
		
//		SC50X0_SDA(0x1D);       // 29 无权限
		
	 	  LCD_Write_String(4,0,"非白名单") ;
		
		SYN6288_Send(SYN6288CMD_VOICE_PLAY ,SYN6288CMDPARAM_PLAY_MUSIC0,"非白名单" ,8);
		
	}
	
	else if(type==PAY_HOLIDAY_ERR)                   //节假日错误
	{
		
	  LCD_Write_String(4,0,"此节假日无权限") ;
		
	SYN6288_Send(SYN6288CMD_VOICE_PLAY ,SYN6288CMDPARAM_PLAY_MUSIC0,"节假日无权限" ,12);
	}
	
	else if(type==PAY_TIME_INTERVAL_ERR)             //时间段错误
	{
		SYN6288_Send(SYN6288CMD_VOICE_PLAY ,SYN6288CMDPARAM_PLAY_MUSIC0,"无权限" ,6);
		
	  LCD_Write_String(4,0,"此时间段无权限") ;
	}
	
	else if(type==PAY_BACK_ERR)                      //黑名单错误
	{

		SYN6288_Send(SYN6288CMD_VOICE_PLAY ,SYN6288CMDPARAM_PLAY_MUSIC0,"黑名单" ,6);
		
	  LCD_Write_String(4,0,"警告，黑名单") ;
	}
	
	else if(type==PAY_DELAYED_ERR)                      //数卡延时错误
	{
		
		SYN6288_Send(SYN6288CMD_VOICE_PLAY ,SYN6288CMDPARAM_PLAY_MUSIC0,"重复刷卡" ,8);
		
	  LCD_Write_String(4,0,"请勿重复刷卡") ;
	}
	
	else if(type==PAY_SECTOR_PASSW_ERR)                      //扇区密码错误
	{
		
		SYN6288_Send(SYN6288CMD_VOICE_PLAY ,SYN6288CMDPARAM_PLAY_MUSIC0,"扇区密码错误" ,12);
		
	  LCD_Write_String(4,0,"扇区密码错误") ;
	}
	
	else if(type==PAY_RW_SECTOR_ERR)                      //读写扇区错误
	{
		SYN6288_Send(SYN6288CMD_VOICE_PLAY ,SYN6288CMDPARAM_PLAY_MUSIC0,"读写扇区错误" ,12);
		
	  LCD_Write_String(4,0,"读写扇区错误") ;
	}	

	else if(type==SYS_NO_NETWORK)                      //无网络
	{
		SYN6288_Send(SYN6288CMD_VOICE_PLAY ,SYN6288CMDPARAM_PLAY_MUSIC0,"无网络" ,6);
		
	 	LCD_Write_String(4,0,"请检查网络！");
	}		
	
	else if(type==SYS_NET_CONNECT_FAIL)                      //  网络连接失败
			
	{
		SYN6288_Send(SYN6288CMD_VOICE_PLAY ,SYN6288CMDPARAM_PLAY_MUSIC0,"网络连接失败" ,12);
		
	  	LCD_Write_String(4,0,"请重新刷卡！");
	}	
	
	

	
}



/****************************************************
	
	LCD12864 消费状态显示
*****************************************************/

void LCD12864_Show_Consump_Pattern(void)
{
//	u8  Show_moneybuf[20]={0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X20,0X20,0X20,0X20,0X20,0X20};  //消费金额

//	u8 t=0;
//	u8 i=0;
//		
//	
//	Show_moneybuf[0]= (keymoneybuff[0]>>4)&0X0F;
//	Show_moneybuf[1]= (keymoneybuff[0]>>0)&0X0F;
//	
//	Show_moneybuf[2]= (keymoneybuff[1]>>4)&0X0F;
//	Show_moneybuf[3]= (keymoneybuff[1]>>0)&0X0F;
//	
//	Show_moneybuf[4]= (keymoneybuff[2]>>4)&0X0F;
//	Show_moneybuf[5]= (keymoneybuff[2]>>0)&0X0F;
//	
//	Show_moneybuf[6]= (keymoneybuff[3]>>4)&0X0F;
//	Show_moneybuf[7]= (keymoneybuff[3]>>0)&0X0F;
//	
//	
//	for(i =0;i< 6 ;i++)
//	{
//	   if( Show_moneybuf[i] ==0X00)
//			   Show_moneybuf[i] = 10;
//		 else
//		 {
//		  break;
//		 } 
//	}
	
	HexToStr(LCDtimebuf,  time_buf,  8);	
	
	/****************第一行*******************/

	LCD_Write_String_NUM(1,1,LCDtimebuf,4);          //年
	LCD_Write_String(1,3,"年");
	LCD_Write_String_NUM(1,4,LCDtimebuf+4,2);       //月
	LCD_Write_String(1,5,"月");
  LCD_Write_String_NUM(1,6,LCDtimebuf+6,2);        //日
	LCD_Write_String(1,7,"日");
	
///****************第三行*******************/

LCD_Write_String(2,0,"消费");
	
LCD_Write_Number(11);// 数字显示函数 ：
	
LCD_Write_Number(Show_moneybuf[0]);// 数字显示函数
LCD_Write_Number(Show_moneybuf[1]);// 数字显示函数
LCD_Write_Number(Show_moneybuf[2]);// 数字显示函数
LCD_Write_Number(Show_moneybuf[3]);// 数字显示函数
LCD_Write_Number(Show_moneybuf[4]);// 数字显示函数
LCD_Write_Number(Show_moneybuf[5]);// 数字显示函数
LCD_Write_Number(12);// 数字显示函数 .
LCD_Write_Number(Show_moneybuf[6]);// 数字显示函数
LCD_Write_Number(Show_moneybuf[7]);// 数字显示函数


LCD_Write_String(2,7,"元");
///****************第四行*******************/	
	
	LCD_Write_String(4,2,"请刷卡");
		
}







/****************************************************

	LCD12864 显示无网络

  输入参数： type   type=1 提示： 请检查网络！
                   type=2  提示：请重新刷卡！

*****************************************************/

void LCD12864_Show_NoNet(uint8_t  type)
{

	Clear_Standby_Display();     //关闭待机显示
//	Clr_Scr() ;                  //LCD12864清屏函数
//	delay_ms(1);
//	LCDBLA_H;                    //打开背光
	

	/****************第一行*******************/

	LCD_Write_String_NUM(1,1,LCDtimebuf,4);          //年
	LCD_Write_String(1,3,"年");
	LCD_Write_String_NUM(1,4,LCDtimebuf+4,2);       //月
	LCD_Write_String(1,5,"月");
  LCD_Write_String_NUM(1,6,LCDtimebuf+6,2);        //日
	LCD_Write_String(1,7,"日");
	
//	LCD_Write_String_NUM(1,3,Numbuff,4);
	
	
/****************第二行*******************/

//	LCD_Write_String(2,0,"余额查询失败");

  

/****************第三行*******************/

	LCD_Write_String(2,0,"余额查询失败");



/****************第四行*******************/	
	
	if(type==1)
	{
	LCD_Write_String(4,0,"请检查网络！");
	}

	else if(type ==2)
	{
	LCD_Write_String(4,0,"请重新刷卡！");
	
	}
	
	

}











