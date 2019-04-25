#include "Head.h"


/******************第0块**********************/
unsigned char ICcardbuff[]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};     //IC卡内部存储卡号 ASCII

u8 ICcardNameASCII[8]={0X00};

 /******************第1块**********************/
		u8 blk1_Time[4]={0X04,0X01,0X00,0X00};	                           //IC卡内部存储时间（第1块）

		u8 ICcard_frequencyBUFF[4]={0};                                       //刷卡次数（字符串形式）
		u8 ICcard_frequencybf[2]={0};
/*
  1.打卡时段的设置,一天分12个不同的时段，根据当前打卡的时间判断在哪个时间段，并返回对应时间段的值

*/
	u8 blk3buff[16]={0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X07, 0X80,0X69,0XFF,0XFF,0XFF,0XFF,0XFF ,0XFF};
unsigned char Time_slot[60] ={0X00,0X00,0X01,0X59,0X01,   //0  1  2  3  4     //
															0X02,0X00,0X03,0X59,0X02,   //5  6  7  8  9
															0X04,0X00,0X05,0X59,0X03,   //10 11 12 13 14
															0X06,0X00,0X07,0X59,0X04,   //15 16 17 18 19
															0X08,0X00,0X09,0X59,0X05,   //20 21 22 23 24
															0X10,0X00,0X11,0X59,0X06,   //25 26 27 28 29
															0X12,0X00,0X13,0X59,0X07,   //30 31 32 33 34
															0X14,0X00,0X15,0X59,0X08,   //35 36 37 38 39
															0X16,0X00,0X17,0X59,0X09,   //40 41 42 43 44
															0X18,0X00,0X19,0X59,0X10,   //45 46 47 48 49
															0X20,0X00,0X21,0X59,0X11,   //50 51 52 53 54
															0X22,0X00,0X23,0X59,0X12    //55 56 57 58 59

                             } ;
unsigned char Time_slot_1[60] ={0X00,0X00,0X01,0X59,0X01,   //0  1  2  3  4     //
															 0X02,0X00,0X03,0X59,0X02,   //5  6  7  8  9
															 0X04,0X00,0X05,0X59,0X03,   //10 11 12 13 14
															 0X06,0X00,0X07,0X59,0X04,   //15 16 17 18 19
															 0X08,0X00,0X09,0X59,0X05,   //20 21 22 23 24
															 0X10,0X00,0X11,0X59,0X06,   //25 26 27 28 29
															 0X12,0X00,0X13,0X59,0X07,   //30 31 32 33 34
															 0X14,0X00,0X15,0X59,0X08,   //35 36 37 38 39
															 0X16,0X00,0X17,0X59,0X09,   //40 41 42 43 44
															 0X18,0X00,0X19,0X59,0X10,   //45 46 47 48 49
															 0X20,0X00,0X21,0X59,0X11,   //50 51 52 53 54
															 0X22,0X00,0X23,0X59,0X12    //55 56 57 58 59

                             } ;


unsigned long TIME_time_slot;         //当前时间值数值 = 时*60 + 分钟

u8  Current_time_value[1]={0X00};     //不同打卡时段对应返回值缓冲区

u32 Time_interval_flag;               //打卡延时标记,1-表示能刷卡,0-表示不能刷

//static union FourByte leftcount;

/*
返回值：无
读取当前的时间值并转换成数值
*/

void gettimetobcd()
	{
//			DS1302_Read_Time();     //读取DS1302的时间

    TIME_time_slot=HextoBCD(time_buf[4])*60 + HextoBCD(time_buf[5]);    //将时间的时分转换成数值
	
	}
	

	/*
	
返回值：无
判断当前打卡的时刻在定义的哪一个时间段，
	并将对应值输出给 Current_time_value
*/

	
	void Set_Time_slot_1(void)
	{
		u32 i;
		u8 tmp1,tmp2;
		for (i = 0; i < 12; i++)
	{
		tmp1 = MyStrCMP(time_buf + 4, Time_slot_1 + i * 4+i, 2);
		tmp2 = MyStrCMP(time_buf + 4, Time_slot_1 + i * 4 + 2+i, 2);
		if ((tmp1 >= 2) && (tmp2 <= 2)) //包含边界
		{
			
//			btimeseg = 1;
//			itimeseg = i;
	
			   Current_time_value[0]=Time_slot_1[(i+1)*4+i];
			break;
		}
	}
}
	
	
/*
	
	对比的是IC卡第1块blk1[4]-blk1[7]

	
	重复刷卡打卡延时函数（0-250分钟）
返回值：无
根据卡里面写的时间跟当前时间对比，是否允许刷卡。
*/

	
u32 Time_interval_fun(void)
	{
	
		
		unsigned long Blk1_Time_interval;       //IC卡的时间（时间转换成分钟值）
		
		unsigned long Difference_Time_interval;   //当前时间（时间转换成分钟值） - IC卡时间（时间转换成分钟值）
		
//		union TwoByte Difference;         //测试用
		
		
	//	MyStrCPY(blk1_Time, blk1+4, 4);          //将扇区块里面的时间复制给 blk1_Time
		
		//SendString(blk1_Time,4);    //测试
		
		gettimetobcd();                                                             //读取DS302 时间
	
		if((blk1_Time[1]!=time_buf[3])||(blk1_Time[0]!=time_buf[2]))
		{
		   return  TIME_INTERVAL_SUCC;	
		
		}
		
		
	  Blk1_Time_interval = HextoBCD(blk1_Time[2])*60 + HextoBCD(blk1_Time[3]);    //将读取的IC卡的时分转换成数值
	
		if(TIME_time_slot<Blk1_Time_interval)
		{ TIME_time_slot += 1440;  }                                                 //跨天
		
		Difference_Time_interval=TIME_time_slot-Blk1_Time_interval;                  //机器时间与IC卡存储的时间的差值
		
//		Difference.i = Difference_Time_interval;                                   //机器时间与IC卡存储的时间的差值(测试用)


		
		
		if(Difference_Time_interval >=( repea_time[0])* 1)                   //机器时间与IC卡时间差值大于设定刷卡延时时间
			{		
				
//  				SendString( Difference.c , 2);    //测试			
//				  SendString(sysvar+2,1);    //测试				
				
				return  TIME_INTERVAL_SUCC;                                         //允许刷卡
			}	
			
//		      SendString( Difference.c , 2);    //测试			
	//			  SendString(sysvar+2,1);    //测试                                			    
				return  TIME_INTERVAL_ERR;				   //否则不允许刷卡		
	}

/***********************************************************
	金额自动加1
	夸月金额置1
************************************************************/
	
u32 Debit_fun(void)
		{
//				u8 blk1_Time1[4]={0X04,0X01,0X00,0X00};		
			u8 Debit_money_value[3]={0x00,0x01,0x00};                                    //扣款金额
			unsigned long balance;                                                      //余额
			u8 balance_BCD[3]={0X00};
					MyStrCPY(blk1_Time, blk1+4, 4);                                         //将扇区块里面的时间复制给 blk1_Time
//			gettimetobcd();                                                             //读取DS302 时间
			MyStrCPY(Debit_money.c, blk1, 4);                                             
				if(blk1_Time[0]!=time_buf[2])                                              //如果跨月，金额置为1元
				{
				Debit_money.c[0]=0X00;
				Debit_money.c[1]=0X01;
				Debit_money.c[2]=0X00;
					
				Debit_money.c[3] = GetXOR(Debit_money.c, 3);                               //金额校验
					
		//		SendString(blk1_Time ,1);                 //测试用	
					
	   //   SendString(time_buf+2 ,1);                 //测试用	
				}
				else
				{
		
	      balance =(getBCDtoDec(Debit_money.c, 3)+getBCDtoDec(Debit_money_value, 3));         //卡上余额+扣款金额
					
				getDectoBCD(balance, balance_BCD, 3);                    //
					
				Debit_money.c[0] = balance_BCD[0];
				Debit_money.c[1] = balance_BCD[1];
				Debit_money.c[2] = balance_BCD[2];
				Debit_money.c[3] = GetXOR(Debit_money.c, 3);
					
	
	//	SendString(Debit_money.c ,4);                 //测试用				
				}					

				return 1;
				
		}
	
	
	

/**********************************************************
//分析扇区数据
**********************************************************/
u8 AnalyzeSectionData(void)
{
//	u8 ICcard[4]={0x00,0x00,0x00,0x00};      //IC卡内部存储的卡号缓冲区
//	u8 ICcard_Flip[4];                       //IC卡内部存储的卡号缓冲区（字节调转）

/*
	第0块Blk0
	
	AAAAAAAA 0000BBCC DDDDDDDD DDDDDDDD
	
			AAAAAAAA：卡号（纯数字）
			BB：组号（16进制）
			CC：卡号长度
			DDDDDDDD DDDDDDDD：姓名，不足16位后面补20
	*/
	
//  MyStrCPY(ICcard, blk0, 4);   
//	
//  turn_4_data(ICcard_Flip,ICcard);     //将4位卡号顺序调转
//	
//	MyStrCPY(ICidbuff, ICcard_Flip, 4); 

  MyStrCPY(ICcardNameASCII,blk0+8,8);   //姓名拷贝






	
	/*第1块Blk1
	AAAABBCC DDDDDDDD EEEEFF00 GGHHHHHH
	
			AAAA：卡上金额（元）
			BB：卡上金额（分）
			CC：3字节金额值校验字
			DDDDDDDD：打卡时间（月日时分）
			EEEE：卡日消费金额（元）
			FF：卡日消费次数
			GG：卡上报餐标记
			HHHHHH：报餐时间（日时分）
	*/


  Debit_fun();
	
	ICcard_frequencybf[0] = Debit_money.c[0];
	ICcard_frequencybf[1] = Debit_money.c[1];
	
	    
	
	/*
	  第2块
	（普通考勤机，收费机卡号相关结构）
	0000AAAA AAAABBCC (00) 0000DDDD 000000
	
			AAAAAAAA：卡号（纯数字）
			BB：组号（16进制）
			CC：卡消费限次次数（16进制）卡上每日限次与分组时段限次
			DDDD：卡消费限额（元）
	*/
	
		MyStrCPY(ICidbuff, blk2+2, 4);  
	
	  HexToStr(ICcardbuff,ICidbuff, 4);//将四位序列号转换为8位字符串形式
	
	
	
	/*
	第3块
	
	00000000 0000FF07 8069AAAA AAAAAAAA
	
			FF078069:为卡上默认值
			AAAAAAAAAAAA：卡密码	
	*/
	

	

	return SECTION_RD_SUCC;
}

//---------------------------------------------------------

/**********************************************************
//写数据块。iblk区块(0..2)
**********************************************************/
u32 BlockWrite(u8 iblk, u8 *buff)
{		  
	//  u8  guangqipass[PASSWORD_SIZE]={0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};
	
		//curSection
		
		
//	u32 isec1=15;
//   u8 isec2=15;
	//u8 isec1=1;
		
		//校验A密码
	if (PcdAuthState(PICC_AUTHENT1A, isection*4+3, cardPW , idbuff) != MI_OK)	
	{
		return 0;
	}

	if (PcdWrite(isection * 4 + iblk  ,buff) != MI_OK) //写卡 isec * 4 + 0
	{
		return 0;
	}

	return 1;
}

/**********************************************************
//写第1块
//0123456789012345
//xxxxnyrsfm000000：xxxx剩余次数；nyrsfm年月日时分秒。
**********************************************************/
u32 WriteBlock1(void)
{
	//u8 blkBUF[16];

	blk1[0]=Debit_money.c[0];
	blk1[1]=Debit_money.c[1];
	blk1[2]=Debit_money.c[2];
	blk1[3]=Debit_money.c[3];
	
	//最近一次刷卡时间
	MyStrCPY(blk1 + 4, time_buf+2, 4);
	
	if (BlockWrite(1, blk1)) //写卡成功
	{
		return 1;
	}
	else
	{
		return 0;//写卡失败
	}
}	

/**********************************************************
//处理IC卡
**********************************************************/
uint8_t  ProcessICCard(void)
{

	  Debit_fun();                      //金额处理
	
	if (!WriteBlock1())                //写卡成功
		{	        
		return 0;
		}
				
	return 1;						
}	
	
	



