
#include "head.h"



void LCD_CLS(void);




#define LCD_SHOW_SPACE	'-' //日期分割符

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
							'*', //0x0A				  
	            '0',//0x00
			       	'#', //0x0B
	            '.', //0x0B
	            '+', //0x0B
	            '#', //0x0B
};




/***** 检测AT24C02失败时显示 *****/
void  OLED24C256check(void)     
			{
//		display_GB2312_string(0,18,"科坦门禁系统");	
//		display_GB2312_string(2,18,"未检测到：");		
		display_GB2312_string(4,18,"AT24C256ERR");	

			}



/****** 0LED显示IC卡的 序列号********/
	void OLEDcard(void)		
	{			
		int t;		
		
      for(t=0;t<9;t++)
	     {
//			switch (cardbuff[t])
//			{																			
//				case 0X30: cardbuff[t] = '0'; break; //0
//				case 0X31: cardbuff[t] = '1'; break; //1
//				case 0X32: cardbuff[t] = '2'; break; //2
//				case 0X33: cardbuff[t] = '3'; break; //3
//				case 0X34: cardbuff[t] = '4'; break; //4
//				case 0X35: cardbuff[t] = '5'; break; //5
//				case 0X36: cardbuff[t] = '6'; break; //6
//				case 0X37: cardbuff[t] = '7'; break; //7
//				case 0X38: cardbuff[t] = '8'; break; //8
//				case 0X39: cardbuff[t] = '9'; break; //9
//				case 0X41: cardbuff[t] = 'A'; break; //A
//				case 0X42: cardbuff[t] = 'B'; break; //B
//				case 0X43: cardbuff[t] = 'C'; break; //C
//				case 0X44: cardbuff[t] = 'D'; break; //D
//				case 0X45: cardbuff[t] = 'E'; break; //E
//				case 0X46: cardbuff[t] = 'F'; break; //F
//				default:break;
//			}
		}
		/*************第一行显示卡号*************/		
		//科坦门禁系统
//		display_GB2312_string(4,32,"科坦门禁");
//		display_GB2312_string(4,18,"科坦门禁系统");		
	/*************第二行显示卡号*************/
		display_GB2312_string(4,5,"卡号:");	
//   display_GB2312_string(4,45,cardbuff);			
		/***********最后一行显示时间日期******/
   //    OLEDtime();
	}

	
/****** 0LED显示姓名********/
	void OLEDName(void)	
	{
		  display_GB2312_string(4,5,"姓名:");	
		  display_GB2312_string(4,45,ICcardNameASCII);	
		
	
	
	}

	

	
		/****** 0LED显示错误，非白名单********/
	void OLEDNOWhitelist(void)		
	{	
					 clear_screen();         //屏幕清零
				   showStandby=0;          //关闭待机显示
	         Standbycount=0;

				
		    display_GB2312_string(6,9,"错误：非白名单");	
		
	}
	
		/****** 0LED显示错误，黑名单********/
	void OLEDBlacklist(void)		
	{	
					 clear_screen();         //屏幕清零
				   showStandby=0;          //关闭待机显示
	         Standbycount=0;

					
		    display_GB2312_string(6,9,"错误：黑名单");	
		
	}	
	
		/****** 0LED显示错误，扇区密码错误********/
	void OLEDPasswordREE(void)		
	{	
					 clear_screen();         //屏幕清零
				   showStandby=0;          //关闭待机显示
	         Standbycount=0;

					
		    display_GB2312_string(6,9,"扇区密码错误");	
		
	}		
	
			/****** 0LED显示错误，扇区密码正确********/
	void OLEDPasswordZQ(void)		
	{	
					 clear_screen();         //屏幕清零
				   showStandby=0;          //关闭待机显示
	         Standbycount=0;

					
		    display_GB2312_string(6,9,"扇区密码正确");	
		
	}	
	
	
			/****** 0LED显示错误，重复刷卡********/
void	OLEDClock_delay(void)
{
					 clear_screen();         //屏幕清零
				   showStandby=0;          //关闭待机显示
	         Standbycount=0;

				
	display_GB2312_string(6,9,"错误:重复刷卡");	

}
	
		/****** 0LED显示错误，读取失败********/
	void OLEDSector_Read_Failure(void)		
	{	
					 clear_screen();         //屏幕清零
				   showStandby=0;          //关闭待机显示
	         Standbycount=0;
					
		    display_GB2312_string(6,9,"扇区读取失败");	
		
	}		

		/****** 0LED显示错误，写失败********/
	void OLEDSector_Write_Failure(void)		
	{	
					 clear_screen();         //屏幕清零
				   showStandby=0;          //关闭待机显示
	         Standbycount=0;
					
		    display_GB2312_string(6,9,"扇区写失败");	
		
	}

			/****** 0LED显示错误，无权限********/
	void OLEDSector_NO_Jurisdiction(void)		
	{	
					 clear_screen();         //屏幕清零
				   showStandby=0;          //关闭待机显示
	         Standbycount=0;
					
		    display_GB2312_string(6,9,"无权限");	
		
	}
			/****** 0LED显示错误，无权限********/
	void OLEDSector_NO_HOliJurisdiction(void)		
	{	
					 clear_screen();         //屏幕清零
				   showStandby=0;          //关闭待机显示
	         Standbycount=0;
					
		    display_GB2312_string(6,9,"假日无权限");	
		
	}
	

	/****** 0LED显示IC卡的 内部卡号********/
	void OLEDICcard(void)		
	{			
		int t;		
	
      for(t=0;t<4;t++)
	     {
			switch (ICcardbuff[t])
			{
				case 0X30: ICcardbuff[t] = '0'; break; //0
				case 0X31: ICcardbuff[t] = '1'; break; //1
				case 0X32: ICcardbuff[t] = '2'; break; //2
				case 0X33: ICcardbuff[t] = '3'; break; //3
				case 0X34: ICcardbuff[t] = '4'; break; //4
				case 0X35: ICcardbuff[t] = '5'; break; //5
				case 0X36: ICcardbuff[t] = '6'; break; //6
				case 0X37: ICcardbuff[t] = '7'; break; //7
				case 0X38: ICcardbuff[t] = '8'; break; //8
				case 0X39: ICcardbuff[t] = '9'; break; //9
				case 0X41: ICcardbuff[t] = 'A'; break; //A
				case 0X42: ICcardbuff[t] = 'B'; break; //B
				case 0X43: ICcardbuff[t] = 'C'; break; //C
				case 0X44: ICcardbuff[t] = 'D'; break; //D
				case 0X45: ICcardbuff[t] = 'E'; break; //E
				case 0X46: ICcardbuff[t] = 'F'; break; //F
				default:break;
			}
		}
			 
		
//	 		display_graphic_12x12(6,6*19,SMALLNUMBER[ICcardbuff[0]]);
//		  display_graphic_12x12(6,6*20,SMALLNUMBER[ICcardbuff[1]]);
//			display_graphic_12x12(6,6*19,SMALLNUMBER[ICcardbuff[2]]);
//		  display_graphic_12x12(6,6*20,SMALLNUMBER[ICcardbuff[3]]);
//			display_graphic_12x12(6,6*19,SMALLNUMBER[ICcardbuff[4]]);
//		  display_graphic_12x12(6,6*20,SMALLNUMBER[ICcardbuff[5]]);
//			display_graphic_12x12(6,6*19,SMALLNUMBER[ICcardbuff[6]]);
//		  display_graphic_12x12(6,6*20,SMALLNUMBER[ICcardbuff[7]]);
	
//		 SendString(ICcardbuff ,sizeof(ICcardbuff));
		/*************第一行显示卡号*************/		
   display_GB2312_string(4,5,"卡号：");	
   display_GB2312_string(4,51,ICcardbuff);		
	/*************第二行显示卡号*************/
//		   display_GB2312_string(6,5,"次数：");	
//   display_GB2312_string(6,51,ICcard_frequency_BUFF);		
		
		/***********最后一行显示时间日期******/
   //    OLEDtime();
	//			SendString(ICcardbuff ,15);                 //测试用
		
	}
	
	void OLEDshowfrequency(void)
	{
		
			u32 i;
		
		 HexToStr(ICcard_frequencyBUFF,ICcard_frequencybf, 2);//将金额转换为4位字符串形式 
		
		  for(i=0;i<6;i++)
	     {
			switch (ICcard_frequencyBUFF[i])
			{
				case 0X30: ICcard_frequencyBUFF[i] = '0'; break; //0
				case 0X31: ICcard_frequencyBUFF[i] = '1'; break; //1
				case 0X32: ICcard_frequencyBUFF[i] = '2'; break; //2
				case 0X33: ICcard_frequencyBUFF[i] = '3'; break; //3
				case 0X34: ICcard_frequencyBUFF[i] = '4'; break; //4
				case 0X35: ICcard_frequencyBUFF[i] = '5'; break; //5
				case 0X36: ICcard_frequencyBUFF[i] = '6'; break; //6
				case 0X37: ICcard_frequencyBUFF[i] = '7'; break; //7
				case 0X38: ICcard_frequencyBUFF[i] = '8'; break; //8
				case 0X39: ICcard_frequencyBUFF[i] = '9'; break; //9
			  case 0X41: ICcard_frequencyBUFF[i] = 'A'; break; //A
				case 0X42: ICcard_frequencyBUFF[i] = 'B'; break; //B
				case 0X43: ICcard_frequencyBUFF[i] = 'C'; break; //C
				case 0X44: ICcard_frequencyBUFF[i] = 'D'; break; //D
				case 0X45: ICcard_frequencyBUFF[i] = 'E'; break; //E
				case 0X46: ICcard_frequencyBUFF[i] = 'F'; break; //F

				default:break;
			}
		}	
	 display_GB2312_string(6,5,"次数:");	
   display_GB2312_string(6,51,ICcard_frequencyBUFF);		
	}
	
	

/****** 0LED显示时间********/
	void OLEDtime(void)		
	{	
		
//	//	u8 timeASCIIBUFF[]={"0","1","2","3","4","5","6","7","8","9"};
//		
//		
//		u8 time[15];            //时间缓冲区		
////	u8 year_6[4];   //年
//		u8 month[2];    //月
//		u8 day[2];      //日
//		u8 times[2];    //时
//		
//		u8 branch[2];   //分
//		u8 second[2];   //秒
////	u8 week_6[1];   //星期
//		u32 t;	

//		DS1302_Get_Time(time);    //读时间
//		
//     for(t=0;t<14;t++)
//	      {
//			switch (time[t])
//			{
//				case 0: time[t] = '0'; break; //0
//				case 1: time[t] = '1'; break; //1
//				case 2: time[t] = '2'; break; //2
//				case 3: time[t] = '3'; break; //3
//				case 4: time[t] = '4'; break; //4
//				case 5: time[t] = '5'; break; //5
//				case 6: time[t] = '6'; break; //6
//				case 7: time[t] = '7'; break; //7
//				case 8: time[t] = '8'; break; //8
//				case 9: time[t] = '9'; break; //9
//				
//							

//				default:break;
//			}
//		}		 		
//								month[0]	 =time[4];
//								month[1]	 =time[5];
//								day[0]	   =time[6];
//								day[1]	   =time[7];
//								times[0]	 =time[9];
//								times[1]	 =time[10];
//		
//								branch[0]	 =time[11];
//								branch[1]	 =time[12];
//								second[0]	 =time[13];
//								second[1]	 =time[14];
//	    //2017年   01/18    11:02:30
//		display_string_5x7(8,8,month);     //月
//    display_string_5x7(8,2*8,"/");      // /
//		display_string_5x7(8,3*8,day);      //日
//		
//	  display_string_5x7(8,5*8,times);    //时
//		display_string_5x7(8,6*8,":");      // :
////		display_string_5x7(8,7*8,branch);   //分
//		
//		
//		display_string_5x7(8,10*8,":");      // :
//		display_string_5x7(8,11*8,second);  //秒		
	}

		/*************待机时大字显示时间************/
	void OLEDStandby(void)		
	{   
//	u8 timeASCIIBUFF[10]={'0','1"','2','3','4','5','6','7','8','9'};		
		u8 time[15];              //时间缓冲区   		
		DS1302_Get_Time(time);    //读时间
		
/*************第三、第二行显示***************/	
		//大字体		
		
//display_graphic_32x32(2,0*16,BIGNUM[time[9]]);
//display_graphic_32x32(2,1*16,BIGNUM[time[10]]);
//display_graphic_32x32(2,2*16,BIGNUM[10]);
//display_graphic_32x32(2,3*16,BIGNUM[time[11]]);
//display_graphic_32x32(2,4*16,BIGNUM[time[12]]);
//display_graphic_32x32(2,5*16,BIGNUM[10]);
//display_graphic_32x32(2,6*16,BIGNUM[time[13]]);
//display_graphic_32x32(2,7*16,BIGNUM[time[14]]);
///************************************/
//	display_string_5x7(8,4+1*6,SMALLNUMBER[time[0]]); 
//	display_string_5x7(8,4+2*6,SMALLNUMBER[time[1]]);
//	display_string_5x7(8,4+3*6,SMALLNUMBER[time[2]]);	
//	display_string_5x7(8,4+4*6,SMALLNUMBER[time[3]]);	
//	display_string_5x7(8,4+5*6,SMALLNUMBER[10]);
//	display_string_5x7(8,4+6*6,SMALLNUMBER[time[4]]);	
//	display_string_5x7(8,4+7*6,SMALLNUMBER[time[5]]);	
//	
//	display_string_5x7(8,4+48,"-");

//	display_string_5x7(8,9*6,SMALLNUMBER[time[6]]);	
//	display_string_5x7(8,10*6,SMALLNUMBER[time[7]]);	
//	
//	
//	display_string_5x7(8,12*6,SMALLNUMBER[9]);
//	display_string_5x7(8,13*6,SMALLNUMBER[time[10]]);	
//	display_string_5x7(8,14*6,":");			
//  display_string_5x7(8,15*6,SMALLNUMBER[time[11]]);
//	display_string_5x7(8,16*6,SMALLNUMBER[time[12]]);	
//	display_string_5x7(8,17*6,":");	
//	display_string_5x7(8,18*6,SMALLNUMBER[time[13]]);
//	display_string_5x7(8,19*6,SMALLNUMBER[time[14]]);	
//    display_graphic_12x12(6,0,  SMALLNUMBER[0]);
	  display_graphic_12x12(6,6,  SMALLNUMBER[time[0]]);
		display_graphic_12x12(6,6*2,SMALLNUMBER[time[1]]);
		display_graphic_12x12(6,6*3,SMALLNUMBER[time[2]]);
		display_graphic_12x12(6,6*4,SMALLNUMBER[time[3]]);
		display_graphic_12x12(6,6*5,SMALLNUMBER[10]);
		display_graphic_12x12(6,6*6,SMALLNUMBER[time[4]]);
		display_graphic_12x12(6,6*7,SMALLNUMBER[time[5]]);
		display_graphic_12x12(6,6*8,SMALLNUMBER[10]);
		display_graphic_12x12(6,6*9,SMALLNUMBER[time[6]]);
		display_graphic_12x12(6,6*10,SMALLNUMBER[time[7]]);
		
		display_graphic_12x12(6,6*13,SMALLNUMBER[time[9]]);
		display_graphic_12x12(6,6*14,SMALLNUMBER[time[10]]);
		
		display_graphic_12x12(6,6*15,SMALLNUMBER[11]);
		
		display_graphic_12x12(6,6*16,SMALLNUMBER[time[11]]);
		display_graphic_12x12(6,6*17,SMALLNUMBER[time[12]]);
		
		display_graphic_12x12(6,6*18,SMALLNUMBER[11]);

		display_graphic_12x12(6,6*19,SMALLNUMBER[time[13]]);
		display_graphic_12x12(6,6*20,SMALLNUMBER[time[14]]);
				/***********第一行显示*************/
		display_GB2312_string(4,32,"科坦门禁");


 //        OLEDtime();
			
	}		
	
/**********************************************************
//在第最后一行显示按键
**********************************************************/
void ShowKeyValue(void)
{
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
//	clear_screen();     //屏幕清零
//	showStandby=0;      //不显示待机界面
//	Standbycount=0;     //返回待机界面计数清零
	/********第一行************/
//display_GB2312_string(0,18,"科坦门禁系统");
	display_GB2312_string(4,8,"请输入6位密码");
 /********第二行************/
//	display_GB2312_string(3,9,"请输入6位密码");
	/*******最后一行*************/
display_GB2312_string(6,16,tmp);//显示按键值
}

/**********************************************************
//在第最后一行显示按键
**********************************************************/
void ShowKeyValue_Plus(void)
{
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
//	clear_screen();     //屏幕清零
	showStandby=0;      //不显示待机界面
	Standbycount=0;     //返回待机界面计数清零
	/********第一行************/
//display_GB2312_string(0,18,"科坦门禁系统");
	display_GB2312_string(4,8,"+");
 /********第二行************/
//	display_GB2312_string(3,9,"请输入6位密码");
	/*******最后一行*************/
display_GB2312_string(6,16,tmp);//显示按键值
}



/**********************************************************
//编程状态显示 在第最后一行显示按键
**********************************************************/
void ShowSTATUS(void)
{
	u8  i=0; 
	u32 t=0;
	u32 j;
	u8  tmp[6]; 
	u32 k=0;
	
	
  delay_ms(1);
		for (i = 0; i < keyidx; i++)
	{

		
		tmp[t++] = DISPLAY_CHAR[keybuff[i]];				
	
	if(t>6)
{
	k=1;
	
	t=0;
		for (j = 0; j < 7; j++)
	{
	tmp[j]=0;
	}
	
	clear_screen();     //屏幕清零
}
	}

	clear_screen();     //屏幕清零
	showStandby=0;      //不显示待机界面
	Standbycount=0;     //返回待机界面计数清零
	/********第一行************/
//display_GB2312_string(0,18,"科坦门禁系统");
	//display_GB2312_string(4,8,"修改密码");
 /********第二行************/
if(k==0)	
	display_GB2312_string(4,8,"请输入6位密码");
	if(k==1)	
	display_GB2312_string(4,8,"再次输入新密码");
	/*******最后一行*************/
display_GB2312_string(6,16,tmp);//显示按键值
}





/**********************************************************
//在第三行显示密码错误
**********************************************************/
void Showpasserr(void)
{  
	showStandby=0;
		clear_screen();     //屏幕清零
	  delay_ms(1);	
//	display_GB2312_string(0,18,"科坦门禁系统");
	display_GB2312_string(4,36,"密码错误");
	display_GB2312_string(6,36,"拒绝进入");	
	timedelay_s(2);

}

/**********************************************************
//在第三行显示密码正确
**********************************************************/
void Showpasscor(void)
{ 
	showStandby=0;
		clear_screen();     //屏幕清零
	  delay_ms(1);
//	display_GB2312_string(0,18,"科坦门禁系统");
  display_GB2312_string(4,36,"密码正确");
	display_GB2312_string(6,45,"请进");	
//	timedelay_s(2);
	
}

/**********************************************************
//WIFI重启显示
**********************************************************/
void SHOWWIFIRest(void)
{ 
	  showStandby=0;
		clear_screen();     //屏幕清零
	  delay_ms(1);
//	display_GB2312_string(0,18,"科坦门禁系统");
  display_GB2312_string(4,36,"WIFI断网");
	display_GB2312_string(6,45,"重启中...");	
	timedelay_s(1);
	
}

/**********************************************************
//系统恢复出厂
**********************************************************/
void SHOWSYSRest_factory(void)
{ 
	  showStandby=0;
		clear_screen();     //屏幕清零
	  delay_ms(1);
//	display_GB2312_string(0,18,"科坦门禁系统");
  display_GB2312_string(6,16,"恢复出厂设置");
	Beep(3, LONG_BEEP); /*短响三声*/	
	
}
     



#ifdef   LCD12864













#endif






