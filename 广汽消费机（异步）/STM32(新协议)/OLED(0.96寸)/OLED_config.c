
#include "head.h"
#define LCD_SHOW_SPACE	'-' //日期分割符

u32  DISPLAY_CHAR[13] = {
	        
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
	
};




/***** 检测AT24C02失败时显示 *****/
void  OLED24C256check(void)     
			{
		display_GB2312_string(0,18,"科坦门禁系统");	
		display_GB2312_string(2,18,"未检测到：");		
		display_GB2312_string(4,18,"AT24C256");	

			}



/****** 0LED显示IC卡的 序列号********/
	void OLEDcard(void)		
	{			
		int t;		
		
      for(t=0;t<9;t++)
	     {
			switch (cardbuff[t])
			{
				case 0X30: cardbuff[t] = '0'; break; //0
				case 0X31: cardbuff[t] = '1'; break; //1
				case 0X32: cardbuff[t] = '2'; break; //2
				case 0X33: cardbuff[t] = '3'; break; //3
				case 0X34: cardbuff[t] = '4'; break; //4
				case 0X35: cardbuff[t] = '5'; break; //5
				case 0X36: cardbuff[t] = '6'; break; //6
				case 0X37: cardbuff[t] = '7'; break; //7
				case 0X38: cardbuff[t] = '8'; break; //8
				case 0X39: cardbuff[t] = '9'; break; //9
				case 0X41: cardbuff[t] = 'A'; break; //A
				case 0X42: cardbuff[t] = 'B'; break; //B
				case 0X43: cardbuff[t] = 'C'; break; //C
				case 0X44: cardbuff[t] = 'D'; break; //D
				case 0X45: cardbuff[t] = 'E'; break; //E
				case 0X46: cardbuff[t] = 'F'; break; //F
				default:break;
			}
		}
		/*************第一行显示卡号*************/		
		//科坦门禁系统
		display_GB2312_string(0,18,"科坦门禁系统");		
	/*************第二行显示卡号*************/
   display_GB2312_string(3,1,"卡号：");	
   display_GB2312_string(3,46,cardbuff);			
		/***********最后一行显示时间日期******/
       OLEDtime();
	}


/****** 0LED显示时间********/
	void OLEDtime(void)		
	{	
		u8 time[15];            //时间缓冲区		
//	u8 year_6[4];   //年
		u8 month[2];    //月
		u8 day[2];      //日
		u8 times[2];    //时
		u8 branch[2];   //分
		u8 second[2];   //秒
//	u8 week_6[1];   //星期
		int t;	

		DS1302_Get_Time(time);    //读时间
		
     for(t=0;t<15;t++)
	      {
			switch (time[t])
			{
				case 0: time[t] = '0'; break; //0
				case 1: time[t] = '1'; break; //1
				case 2: time[t] = '2'; break; //2
				case 3: time[t] = '3'; break; //3
				case 4: time[t] = '4'; break; //4
				case 5: time[t] = '5'; break; //5
				case 6: time[t] = '6'; break; //6
				case 7: time[t] = '7'; break; //7
				case 8: time[t] = '8'; break; //8
				case 9: time[t] = '9'; break; //9

				default:break;
			}
		}		 		
								month[0]	=time[4];
								month[1]	=time[5];
								day[0]	  =time[6];
								day[1]	  =time[7];
								times[0]	=time[9];
								times[1]	=time[10];
								branch[0]	=time[11];
								branch[1]	=time[12];
								second[0]	=time[13];
								second[1]	=time[14];
	    //2017年   01/18    11:02:30
		display_GB2312_string(6,0,month);     //月
    display_GB2312_string(6,16,"/");      // /
		display_GB2312_string(6,25,day);      //日
		
	  display_GB2312_string(6,56,times);    //时
		display_GB2312_string(6,72,":");      // :
		display_GB2312_string(6,81,branch);   //分
		display_GB2312_string(6,98,":");      // :
		display_GB2312_string(6,107,second);  //秒		
	}

		/*************待机时大字显示时间************/
	void OLEDStandby(void)		
	{   		
		u8 time[15];              //时间缓冲区   		
		DS1302_Get_Time(time);    //读时间
		
/*************第三、第二行显示***************/	
		//大字体		
		
display_graphic_32x32(2,0*16,BIGNUM[time[9]]);
display_graphic_32x32(2,1*16,BIGNUM[time[10]]);
display_graphic_32x32(2,2*16,BIGNUM[10]);
display_graphic_32x32(2,3*16,BIGNUM[time[11]]);
display_graphic_32x32(2,4*16,BIGNUM[time[12]]);
display_graphic_32x32(2,5*16,BIGNUM[10]);
display_graphic_32x32(2,6*16,BIGNUM[time[13]]);
display_graphic_32x32(2,7*16,BIGNUM[time[14]]);
/************************************/

	display_graphic_8x16(6,3*8,NUMBER[time[0]]);
	display_graphic_8x16(6,4*8,NUMBER[time[1]]);	
	display_graphic_8x16(6,5*8,NUMBER[time[2]]);	
	display_graphic_8x16(6,6*8,NUMBER[time[3]]);	
	display_graphic_8x16(6,7*8,NUMBER[10]);
	display_graphic_8x16(6,8*8,NUMBER[time[4]]);	
	display_graphic_8x16(6,9*8,NUMBER[time[5]]);	
	display_graphic_8x16(6,10*8,NUMBER[10]);
	display_graphic_8x16(6,11*8,NUMBER[time[6]]);	
	display_graphic_8x16(6,12*8,NUMBER[time[7]]);			
 
		
				/***********第一行显示*************/
		display_GB2312_string(0,18,"科坦门禁系统");




			
	}		
	
/**********************************************************
//在第最后一行显示按键
**********************************************************/
void ShowKeyValue(void)
{
	u8  i=0; 
	u8  tmp[6]; 
  delay_ms(1);
		for (i = 0; i < keyidx; i++)
	{
		tmp[i] = DISPLAY_CHAR[keybuff[i]];				
	}
	clear_screen();     //屏幕清零
	showStandby=0;      //不显示待机界面
	Standbycount=0;     //返回待机界面计数清零
	/********第一行************/
display_GB2312_string(0,18,"科坦门禁系统");
	
 /********第二行************/
	display_GB2312_string(3,9,"请输入6位密码");
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
	display_GB2312_string(0,18,"科坦门禁系统");
	display_GB2312_string(4,36,"密码错误");
	display_GB2312_string(6,36,"拒绝进入");	
	//timedelay_s(2);

}

/**********************************************************
//在第三行显示密码正确
**********************************************************/
void Showpasscor(void)
{ 
	showStandby=0;
		clear_screen();     //屏幕清零
	  delay_ms(1);
	display_GB2312_string(0,18,"科坦门禁系统");
  display_GB2312_string(4,36,"密码正确");
	display_GB2312_string(6,45,"请进");	
//	timedelay_s(2);
	
}
