#include "Head.h"




/**********************************************************
//常量定义
**********************************************************/

/**********************************************************
//变量定义
**********************************************************/


u8  showStandby=1;//显示待机标志位
u32 Standbycount =30;//不显示待机时计时计数

u32 Standbytime =0;//进入主界面时间


u8 showtime;//显示时间
u32 timecount;//不显示时间时计时计数

u8 sys_status; //机器所处状态
u32 statuscnt; //状态计时周期数

u8 keyVal;      //按键值

u8 cycle;   //状态分析计数

u32 output1state ;    //开门状态
u32	output1time ;     //退出开门计数

u32 output2state ;    //开门状态
u32	output2time ;     //退出开门计数



u32 badd; //增加卡
u32 bdel; //删除卡
u8  idbuff[CARD_SIZE];  //IC卡序列号

u8  ICidbuff[CARD_SIZE];  //IC卡序列号

volatile u32  inPCOM;    //串口数据处理状态


 u8  sysvar[SYSVAR_SIZE]; //系统参数
 u8  extvar[SYSVAR_SIZE]; //扩展参数

 u8  repea_time[1];  //刷卡延时
 u8  output_time[1]; //继电器输出延时
 u8  whiteallow[1]={0X00};
 u8  interval_time[1]={0X00};    //数卡间隔延时
 
 
 u16  Show_Refresh_coun =0;    //显示刷新计数 
 
 
 u8  Check_the_balance =0;    //查询余额状态
 
 u8  refund_the_balance =0;   //误刷退款状态
 
/**********************************************************
//工作状态分析
**********************************************************/

void AnalyzeWorkStatus(void)
{
	if(Standbytime==0)
	{
	  fun5();
	}

	//&& MY_STATUS_NOT(IN_SET_STATUS)
	if (showStandby &&GetWorkStatus(NORMAL_STATUS))  //如果主界面显示标志为1，非编程状态 无按键按下   显示主界面
		{    
			if(!Show_Refresh_coun)
				{
					Show_Refresh_coun = SECOND_CYCLE*30;
					
			//		 LCD12864_Standby();
					LCD_Standby();				
				}  					
		} 

	else if (GetWorkStatus(KEY_PLUS_STATUS)) //OLED_Clear();          //+ 号状态
		{
		
	//		ShowKeyValue_Plus(); 
			
		if(!Show_Refresh_coun)
			{
				ShowKeyValue_Plus();
				
				Show_Refresh_coun=SECOND_CYCLE*5;
			} 
			
		}
		
	else if(GetWorkStatus(KEY_KEY_STATUS))
	{	
 
		if(!Show_Refresh_coun)
		{
		  LCD_ShowKeyValue();
			
			Show_Refresh_coun=SECOND_CYCLE*5;
		} 
		
	}//显示按键 
	
	else if(GetWorkStatus(IN_CONSUMPT_STATUS))   //消费状态显示
	{	
		
		if(!Show_Refresh_coun)
		{
		  LCD_Show_Consump_Pattern();
			Show_Refresh_coun=SECOND_CYCLE*5;
		}  

	}
	
	else if(GetWorkStatus(IN_MENU_STATUS))   //菜单状态
	{	
		
		if(!Show_Refresh_coun)
		{
			if(Menu_password_falg)	
				{
					LCD_Disp_MenuMain();
				} 
			else 
				{
					 LCD_Disp_MenuPassword();     //显示输入密码
				}		
			
			Show_Refresh_coun=SECOND_CYCLE*5;
		}  

	}
	
	else if(GetWorkStatus(IN_FUN_STATUS))   //功能状态
	{	
		
		if(!Show_Refresh_coun)
		{
		  LCD_Disp_Function ();
			
			Show_Refresh_coun=SECOND_CYCLE*10;
		}  
	}	
	
	else if(GetWorkStatus(IN_QUERY_STATUS))   //查询状态
	{	
	//	Check_the_balance =1;
		if(!Show_Refresh_coun)
		{
		  LCD_Disp_Query_Money ();
			
			Show_Refresh_coun=SECOND_CYCLE*10;
			
			Clear_Standby_Display_Time(6);
			
		}
		
	}
	
	else if(GetWorkStatus(IN_REFUND_STATUS))   //退款状态
	{	
	//	Check_the_balance =1;
		if(!Show_Refresh_coun)
		{
		  LCD_Disp_Refund_Money ();
			
			Show_Refresh_coun=SECOND_CYCLE*10;
			
			Clear_Standby_Display_Time(6);
			
		}
		
	}	
	
	
	if(GetWorkStatus(IN_QUERY_STATUS))	
	{ 
	  Check_the_balance =1;
	}
	else if(GetWorkStatus(IN_REFUND_STATUS))
	{
		refund_the_balance =1;
	}
	else
	{
	  Check_the_balance =0;
		
		refund_the_balance =0;
	}
	
	
	
	
	
}

/**********************************************************
//初始化输出
**********************************************************/
void InitOutput(void)
{
	output1state = 0;
	output1time = 0;
	
	output2state = 0;
	output2time = 0;
}

/**********************************************************
//继电器1开始输出(开门动作)
**********************************************************/
void BeginOutput1(void)
{
	output1state = 1;   //开门标志
	output1time = 0;    //退出开门计数
	OPEN_REL1();
//	LED0=0;
//	LED0=1;
//  SUCCESS();	
}

/**********************************************************
//继电器1结束输出（关门动作）
**********************************************************/
void EndOutput1(void)
{
	output1state = 0;   //开门标志
	output1time = 0;    //退出开门计数

	CLOSE_REL1();	
//	LED0=1;
//	LED0=0;
}

/**********************************************************
//继电器2开始输出(开门动作)
**********************************************************/
void BeginOutput2(void)
{
	output2state = 1;   //开门标志
	output2time = 0;    //退出开门计数
	OPEN_REL2();
//	LED1=0;
//	LED0=1;
//  SUCCESS();	
}

/**********************************************************
//继电器2结束输出（关门动作）
**********************************************************/
void EndOutput2(void)
{
	output2state = 0;   //开门标志
	output2time = 0;    //退出开门计数

	CLOSE_REL2();	
//	LED1=1;
//	LED0=0;
}




/**********************************************************
//检查初始化
**********************************************************/
void CheckInit(void)
{
	

	if (SYSREST_KEY==0)
	{
		delay_ms(100);

		if (SYSREST_KEY==0)
		{
			//while (!PM_RST) ;
			LoadDefaultValue();
		//	APP_RESET();			
	//		 clear_screen();           //OLED清屏
//			display_GB2312_string(4,16,"恢复出厂设置");
//			display_GB2312_string(6,16,"请断电重启");
			while (!SYSREST_KEY) ;			
		}
	}
}





// * 函数名：Get_ChipInfo(void)
// * 描述  ：获取芯片Flash 大小、芯片ID号、烧录日期、固件库版本
// * 输入  ：无
// * 输出  ：串口打印数据
// * 说明  ：
void Get_ChipInfo(void)
{
  const u8 *COMPILED_DATE=__DATE__;//获得编译日期
	const u8 *COMPILED_TIME=__TIME__;//获得编译时间
	union FourByte ic4; 	
  uint32_t ChipUniqueID[3];   //芯片的唯一ID
  u16 STM32_FLASH_SIZE_OFR;       //芯片flash的容量
	u8 u8_ChipUniqueID[12];          //芯片的唯一ID
	u8 u8_STM32_FLASH_SIZE[4];       //芯片flash的容量
	u8 u8_DATE_time[20];             //编译日期/时间
	u8 ic41[4];   
	u8 t;
	u8 Delimiter[]={0X2D,0X2D};
   ChipUniqueID[0] = *(__IO u32 *)(0X1FFFF7F0); // 高字节
   ChipUniqueID[1] = *(__IO u32 *)(0X1FFFF7EC); //
   ChipUniqueID[2] = *(__IO u32 *)(0X1FFFF7E8); // 低字节
   STM32_FLASH_SIZE_OFR= *(u16*)(0x1FFFF7E0);    //闪存容量寄存器  
	
 //  printf(" 芯片的唯一ID为: %X-%X-%X \n", ChipUniqueID[0],ChipUniqueID[1],ChipUniqueID[2]);  
	         //芯片的唯一ID为: 43115120-33385833-5DAFF33
	
 ///  printf(" 芯片flash的容量为: %dK \n", STM32_FLASH_SIZE);  // 芯片flash的容量为: 256K
	//	 RS485_Send_Data(STM32_FLASH_SIZE, 1);
//  printf(" 烧录日期: "__DATE__" - "__TIME__"\n"); //烧录日期: Jul 11 2017 - 15:52:33
      //输出使用固件库版本号
//   printf(" 代码固件库版本: V %d.%d.%d \n",__STM32F10X_STDPERIPH_VERSION_MAIN,__STM32F10X_STDPERIPH_VERSION_SUB1,__STM32F10X_STDPERIPH_VERSION_SUB2);  
	// 代码固件库版本: V 3.5.0 	
	
	
	for(t=0;t<3;t++)
	{
	  ic4.i=ChipUniqueID[t];                    //芯片ID
		
	  turn_4_data(ic41,ic4.c);	   //数据翻转
		
  	MyStrCPY((u8_ChipUniqueID+t*4),ic41,4); 

	}
		
   ic4.i=STM32_FLASH_SIZE_OFR;                     //flash大小
	
	 turn_4_data(u8_STM32_FLASH_SIZE,ic4.c);	   //数据翻转
		

	
		for(t=0;t<11;t++)
			{
				u8_DATE_time[t] = COMPILED_DATE[t];     //时间
			}
		for(t=0;t<8;t++)
			{
		    u8_DATE_time[t+12] = COMPILED_TIME[t];  //日期

			}
			  u8_DATE_time[11]=0X2D;    






			
	 RS485_Send_Data(u8_ChipUniqueID, 12);          //发送芯片ID 
	 RS485_Send_Data(Delimiter, 2);                 //发送分割符 --
	 RS485_Send_Data(u8_STM32_FLASH_SIZE+2, 2);		  //发送flash大小
	 RS485_Send_Data(Delimiter, 2);                 //发送分割符 --					
	 RS485_Send_Data(u8_DATE_time, 20);             //时间、日期
	
}	 	







