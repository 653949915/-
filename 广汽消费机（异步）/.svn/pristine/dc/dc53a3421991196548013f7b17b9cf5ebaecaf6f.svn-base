//#include "ds1302.h"
//#include "delay.h"
#include "head.h"  
//初始化时间定义
  u8 time_buf[8] ={0X20}; 
volatile  u8 time_buftx[8]= {0x20,0x17,0x01,0x20,0x11,0x58,0x30,0x05};//初始时间2017年6月1号23点59分55秒 星期二
//DS1302初始化 
void DS1302_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3 |GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOE, &GPIO_InitStructure);
	
	GPIO_SetBits(GPIOE, GPIO_Pin_3);                 //PE3拉高 数据
	GPIO_ResetBits(GPIOE, GPIO_Pin_2 | GPIO_Pin_4);  //PE2，PE4置低
}

//向DS1302写入一个字节数据
void DS1302_Write_Byte(u8 addr, u8 data)
{
  u8 i;
	DS1302_RST = 0;      //停止DS1302总线
	delay_us(10);
	DS1302_RST = 1;      //启动DS1302总线
	addr = addr & 0xFE;  //最低位置零，写数据
	DS1302_IO_OUT();
	for(i = 0; i < 8; i ++)  //写地址
	{
	  if (addr & 0x01)
			DS1302_DATA_OUT = 1;
		else
			DS1302_DATA_OUT = 0;
		
		DS1302_SCK = 1;    //产生时钟
		delay_us(10);
		DS1302_SCK = 0;
		addr = addr>>1;
	}
	for (i = 0; i < 8; i ++) //写数据
	{
	  if(data & 0x01)
			DS1302_DATA_OUT = 1;
		else
			DS1302_DATA_OUT = 0;
		
		DS1302_SCK = 1;   //产生时钟
		delay_us(10);
		DS1302_SCK = 0;
	  data = data>>1;
	}
	DS1302_RST = 0;      //停止DS1302总线
}

//从DS1302读出一个字节数据
u8 DS1302_Read_Byte(u8 addr)
{
  u8 i,temp;
	DS1302_RST = 0;      //停止DS1302总线
	delay_us(10);
	DS1302_RST = 1;      //启动DS1302总线
	addr = addr | 0x01;  //最低位置高，读数据
	DS1302_IO_OUT();
	for(i = 0; i < 8; i ++)  //写地址
	{
	  if (addr & 0x01)
			DS1302_DATA_OUT = 1;
		else
			DS1302_DATA_OUT = 0;
		
		DS1302_SCK = 1;    //产生时钟
		delay_us(10);
		DS1302_SCK = 0;
		addr = addr>>1;
	}
	DS1302_IO_IN();
	for (i = 0; i < 8; i ++) //读数据
	{
	  temp = temp >> 1;
		if(DS1302_DATA_IN)
			temp |= 0x80;
		else
			temp &= 0x7F;
		
		DS1302_SCK = 1;   //产生时钟
		delay_us(10);
		DS1302_SCK = 0;
	}
	DS1302_RST = 0;      //停止DS1302总线
	return temp;
}


u8 GetWeek(u8 y, u8 m, u8 d)
{
	u8 ty,tm,td;	
	u8  week[] = {2,3,4,5,6,7,1};



	ty = (y / 16 * 10) + (y & 15) + 2000;
	tm = (m / 16 * 10) + (m & 15);
	td = (d / 16 * 10) + (d & 15);

	if (tm <= 2)
	{
		ty -= 1;
		tm += 12;
	}

	return week[(td + 2 * tm + 3 * (tm + 1) / 5 + ty + ty / 4 - ty / 100 + ty / 400) % 7];
}



//向DS1302写入时间数据
void DS1302_Write_Time(u8 *time_buftx)
{
	
  DS1302_Write_Byte(ds1302_control_add, 0x00);      //关闭写保护
  DS1302_Write_Byte(ds1302_sec_add, 0x80);          //暂停时钟
	DS1302_Write_Byte(ds1302_charger_add, 0xA9);      //涓流充电
	DS1302_Write_Byte(ds1302_year_add,time_buftx[1]);		//年 
	DS1302_Write_Byte(ds1302_month_add,time_buftx[2]);	//月 
	DS1302_Write_Byte(ds1302_date_add,time_buftx[3]);		//日 
	DS1302_Write_Byte(ds1302_hr_add,time_buftx[4]);		  //时 
	DS1302_Write_Byte(ds1302_min_add,time_buftx[5]);		//分
	DS1302_Write_Byte(ds1302_sec_add,time_buftx[6]);		//秒
	DS1302_Write_Byte(ds1302_day_add,time_buftx[7]);		//周 
	DS1302_Write_Byte(ds1302_control_add,0x80);		    //打开写保护 
}

//从DS302读出时钟数据
void DS1302_Read_Time(void)  
{
	time_buf[1] = DS1302_Read_Byte(ds1302_year_add);		   //年 
	time_buf[2] = DS1302_Read_Byte(ds1302_month_add);		   //月 
	time_buf[3] = DS1302_Read_Byte(ds1302_date_add);		   //日 
	time_buf[4] = DS1302_Read_Byte(ds1302_hr_add);		     //时 
	time_buf[5] = DS1302_Read_Byte(ds1302_min_add);		     //分 
	time_buf[6] = (DS1302_Read_Byte(ds1302_sec_add))&0x7f; //秒，屏蔽秒的第7位，避免超出59
	time_buf[7] = DS1302_Read_Byte(ds1302_day_add);		     //周 	
	
	
//time_buf[7]=	GetWeek(time_buf[1],time_buf[2],time_buf[3]);
	
}

void DS1302_Get_sysTime(u8 *systime) 
{
	u8 t;
	
	DS1302_Read_Time();

	for (t=0;t<7;t++)
	{
	systime[t]=time_buf[t+1];
	
	}

}


//DS1302向上层返回时间数据
void DS1302_Get_Time(u8 *time)
{
	DS1302_Read_Time();
	time[0]=(time_buf[0]>>4);   //年   
  time[1]=(time_buf[0]&0x0f);
   
  time[2]=(time_buf[1]>>4);   
  time[3]=(time_buf[1]&0x0f);
  
  time[4]=(time_buf[2]>>4);   //月  
  time[5]=(time_buf[2]&0x0f);

  time[6]=(time_buf[3]>>4);   //日   
  time[7]=(time_buf[3]&0x0f);
   
  time[8]=(time_buf[7]&0x07); //星期
   
  time[9]=(time_buf[4]>>4);   //时   
  time[10]=(time_buf[4]&0x0f);   

  time[11]=(time_buf[5]>>4);  //分   
  time[12]=(time_buf[5]&0x0f);   

  time[13]=(time_buf[6]>>4);  //秒
  time[14]=(time_buf[6]&0x0f);
}




///**********************************************************
////读取当前时间，进行序列号检查！
//**********************************************************/
//void ReadNowTime(void)
//{
//	uchar i,c;
//	uchar time[7];

//	NOP();

//	berrtime = 0;  
//	GetDS1302(0x81, time, 7);//秒,分,时,日,月,星期,年  

//	systime[0] = time[6];	//0  1  2  3  4  5    6
//	systime[1] = time[4];	//年,月,日,时,分,秒,星期
//	systime[2] = time[3];	//0  1  2  3  4  5  6
//	systime[3] = time[2];	
//	systime[4] = time[1]; 
//	systime[5] = time[0];//时分秒
//	systime[6] = time[5];//周

//	if (MyStrCMP(systime, MIN_TIME, 6) == 1) //读取的时间不能小于最小时间
//	{
//		ReadLastUseTime();
//		return;
//	}

//	for (i = 0; i < 7; i++) //出现字母
//	{
//		c = (systime[i] & 0xF0) >> 4;
//		if (c >= 0x0A)
//		{
//			ReadLastUseTime();
//			return;
//		}

//		c = systime[i] & 0x0F;
//		if (c >= 0x0A)
//		{
//			ReadLastUseTime();
//			return;
//		}
//	}
//}

///**********************************************************
////设置当前时间
//**********************************************************/
void SetNowTime(u8 *p)
{
	u8 time[8];

	
 // time[0] = 0X20;  //年
	time[1] = p[0];  //年
	time[2] = p[1];  //月
	time[3] = p[2];  //日
	time[4] = p[3];  //时
	time[5] = p[4];  //分
	time[6] = p[5];  //秒
	time[7] = GetWeek(p[0], p[1], p[2]);//周

	DS1302_Write_Time(time);
}





