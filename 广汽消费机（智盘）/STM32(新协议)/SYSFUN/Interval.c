
#include "head.h"

u32 btimeseg;     //门禁时段检测通过标志

u32 itimeseg=0;   //在哪个门禁时段

u32 bHoliday;     //节假日标志

u32 bChannel;     //通道时段标志

u32 bHolitimeseg;     //节假日时段检测通过标志

u8 Permission_Period[32];           //门禁时段缓冲区

u8 Passage_Timebuff[32];            //通道时段缓冲区

u8 Passage_Enablebuff[6];            //通道使能缓冲区

u8 Holiday_Vacationsbuff[40];       //节假日时段缓冲区

u8 Passage_EnableVerbuff[6]={0X45, 0X6E, 0X61, 0X62, 0X6C, 0X65};            //通道使能验证缓冲区



/********************************************	***********************************
检测门禁时段 说明：刷卡时，检测当前时段。 当前时间在此时段内才允许通过
*******************************************************************************/

void Time_Interval_Detection(void)
{
	u8 i;
	
  u8 tmp1,tmp2;
  
  u8 testbitbuff[1];  
	
	btimeseg = 0;
	
			/*****************检测4个时段******************/
	for(i=0;i<4;i++)
		{
			testbitbuff[0]=((Permission_Periodbuff[0]&0x0f)>>i)&0x01;

			if(	testbitbuff[0]==0x01)
				{
				//	 RS485_Send_Data(testbitbuff,1);//集中发送	
					tmp1 = MyStrCMP(time_buf + 4, Permission_Period + i*4 , 2);         //门禁时段对比
					tmp2 = MyStrCMP(time_buf + 4, Permission_Period + i*4  + 2, 2);
					if ((tmp1 >= 2) && (tmp2 <= 2)) //包含边界
							{
								btimeseg = 1;         //门禁时段标志 置1	
						//		itimeseg = i;
								break;
							}					
				}
		}
}

u8  Check_Passage_Enable(void)
 {
	u8 temp=0;
	
  temp=MyStrCMP(Passage_Enablebuff, Passage_EnableVerbuff , 6);

	if(temp==2)
	{ return 1;}
	 
	else
	{return 0;}
 }
/********************************************	***********************************
检测是否通道时段
*******************************************************************************/
void Channel_Time_Detection(void)
  {
	u8 i;
	u8 tmp1,tmp2;
	
	bChannel=0;
	/*****************检测8个时段******************/
  for(i=0;i<8;i++)
		{
					tmp1 = MyStrCMP(time_buf + 4, Passage_Timebuff + i*4 , 2);        // //通道时段对比
					tmp2 = MyStrCMP(time_buf + 4, Passage_Timebuff + i*4  + 2, 2);
					if ((tmp1 >= 2) && (tmp2 <= 2)) //包含边界
							{
								bChannel = 1;				//通道时段标志 置1		
								break;
							}					
		}
	}
	

/********************************************	***********************************
检测是否节假日   先检查周末 再检查日期
*******************************************************************************/

void Holiday_Detection(void)
  {
	u8 i;
	u8 tmp1,tmp2;
	u8 testbitbuff[1];
	u8 weekbuff[7]={0X01,0X02,0X03,0X04,0X05,0X06,0X07};	
		
	bHoliday=0;
	
	for(i=0;i<7;i++) 
		{
			testbitbuff[0]=(Holiday_Vacationsbuff[36]>>i)&0x01;		
			if(	testbitbuff[0]==0x01)
				{
					if(weekbuff[i]==time_buf[7])
					{				
						bHoliday = 1;						//节假日标志 置1		
												
						break;
					}		
	     	}
			}
	if(bHoliday==0)	     //不是周末，再检查日期
	{
	/*****************检测10个时段******************/
		for(i=0;i<9;i++)   
			{
				tmp1 = MyStrCMP(time_buf + 2, Holiday_Vacationsbuff + i*4 , 2);        // //节假日对比
				tmp2 = MyStrCMP(time_buf + 2, Holiday_Vacationsbuff + i*4  + 2, 2);
				if ((tmp1 >= 2) && (tmp2 <= 2)) //包含边界
						{
							bHoliday = 1;						//节假日标志 置1									
							break;
						}					
			}
		
	}
	}

	
/********************************************	***********************************
检测节假日时段 说明：刷卡时，检测当前时段。 当前时间在此时段内才允许通过
*******************************************************************************/

void HolidayTime_Interval_Detection(void)
{
	u8 i;
	
  u8 tmp1,tmp2;
  
  u8 testbitbuff[1];  
	
	bHolitimeseg = 0;
	
			/*****************检测4个时段******************/
	for(i=0;i<4;i++)
		{
			testbitbuff[0]=((Permission_Periodbuff[0]&0xF0)>>(i+4))&0x01;

			if(	testbitbuff[0]==0x01)
				{
					// RS485_Send_Data(testbitbuff,1);//集中发送	
					tmp1 = MyStrCMP(time_buf + 4, Permission_Period+16 + i*4 , 2);         //门禁时段对比
					tmp2 = MyStrCMP(time_buf + 4, Permission_Period+16 + i*4  + 2, 2);
					if ((tmp1 >= 2) && (tmp2 <= 2)) //包含边界
							{
								bHolitimeseg = 1;         //节假日时段标志 置1	
								break;
							}					
				}
		}
}
	
	
/********************************************	***********************************
门禁时段初始化   8个时段  其中4个工作日时段，4个节假日时段，总共32个字节
*******************************************************************************/


void InitTime_Interval_Detection(void)
{

AT24CXX_Read(PERMISSION_PERIOD_POS,  Permission_Period , 32 );    //24C512读门禁时段

	delay_ms(100);
}

/********************************************	***********************************
通道时段初始化   8个时段  总共32个字节
*******************************************************************************/

void InitPassage_Time(void)
{

AT24CXX_Read(PASSAGE_TIME_POS,Passage_Timebuff ,32);	              //24C512读通道时段
	
		delay_ms(100);

}

/********************************************	***********************************
通道使能初始化   8个字节
*******************************************************************************/

void InitPassage_TimeEnable(void)
{

    AT24CXX_Read(PASSAGE_TIME_ENABLE_POS,Passage_Enablebuff ,6);	              //24C512读通道时段
	
		delay_ms(100);

}



/********************************************	***********************************
节假日初始化   10个节假日 + 周末    总共41个字节
*******************************************************************************/

void InitHoliday_Vacations(void)
{

  AT24CXX_Read( HOLIDAY_VACATIONS_POS, Holiday_Vacationsbuff, 37 );	              //24C512读节假日

		delay_ms(100);
	
}



