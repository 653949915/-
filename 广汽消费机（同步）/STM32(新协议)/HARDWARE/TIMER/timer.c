
#include "led.h"
#include "OLED_config.h"
#include "head.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途

//定时器 驱动代码 	   

//注意：定时器2已经被W5500使用，请勿使用

//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////   	 
u8 timerdelay;
u8 timerdelaysec;
//通用定时器3中断初始化
//这里时钟选择为APB1的2倍，而APB1为36M
//arr：自动重装值。
//psc：时钟预分频数
//这里使用的是定时器3!
void TIM3_Int_Init(u16 arr,u16 psc)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //时钟使能
	
	//定时器TIM3初始化
	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	4999
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值  7199
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //根据指定的参数初始化TIMx的时间基数单位
 
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE ); //使能指定的TIM3中断,允许更新中断

	//中断优先级NVIC设置
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  //TIM3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //先占优先级0级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //从优先级3级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //初始化NVIC寄存器


	TIM_Cmd(TIM3, ENABLE);  //使能TIMx					 
}



void TIM7_Int_Init(u16 arr,u16 psc)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE); //时钟使能
	
	//定时器TIM7初始化
	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	4999
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值  7199
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM7, &TIM_TimeBaseStructure); //根据指定的参数初始化TIMx的时间基数单位
 
	TIM_ITConfig(TIM7,TIM_IT_Update,ENABLE ); //使能指定的TIM7中断,允许更新中断

	//中断优先级NVIC设置
	NVIC_InitStructure.NVIC_IRQChannel = TIM7_IRQn;  //TIM3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //先占优先级0级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 4;  //从优先级3级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //初始化NVIC寄存器


	TIM_Cmd(TIM7, ENABLE);  //使能TIMx					 
}




/// TIM2中断优先级配置
void TIM2_NVIC_Configuration(void)
{
    NVIC_InitTypeDef NVIC_InitStructure; 
    
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);  													
    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;	  
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;	
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

/*
 * TIM_Period / Auto Reload Register(ARR) = 1000   TIM_Prescaler--71 
 * 中断周期为 = 1/(72MHZ /72) * 1000 = 1ms
 *
 * TIMxCLK/CK_PSC --> TIMxCNT --> TIM_Period(ARR) --> 中断 且TIMxCNT重置为0重新计数 
 */
//void TIM2_Configuration(void)
//{
//    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
//		
//		/* 设置TIM2CLK 为 72MHZ */
//    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 , ENABLE);
//    //TIM_DeInit(TIM2);
//	
//	/* 自动重装载寄存器周期的值(计数值) */
//    TIM_TimeBaseStructure.TIM_Period=1000;
//	
//    /* 累计 TIM_Period个频率后产生一个更新或者中断 */
//	  /* 时钟预分频数为72 */
//    TIM_TimeBaseStructure.TIM_Prescaler= 71;
//	
//		/* 对外部时钟进行采样的时钟分频,这里没有用到 */
//    TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;
//	
//    TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; 
//    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
//	
//    TIM_ClearFlag(TIM2, TIM_FLAG_Update);
//	
//    TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
//		
//    TIM_Cmd(TIM2, ENABLE);																		
//    
//    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 , DISABLE);		/*先关闭等待使用*/    
//}



//定时器3中断服务程序
void TIM3_IRQHandler(void)   //TIM3中断  每次定时100ms
{
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)  //检查TIM3更新中断发生与否
		{
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update  );  //清除TIMx更新中断标志 
	//	LED1=!LED1;
			
/*************************************************
		非待机状态计数	
******************************************************/
			
		 if(showStandby==0)       //待机显示标志位
		   {
		    Standbycount++;          //待机显示计数		 		 				 
		   }

 /*************************************************
		非工作状态计数	
******************************************************/
			 
		if (MY_STATUS_NOT(NORMAL_STATUS))  //如果在非工作状态
	   {
		   statuscnt++;    //状态计时周期数

	   }		
/*************************************************
		非关门状态计数	
******************************************************/	

		if (output1state) 
		 { 				 
		 output1time++; 
		 
		 }  //如果是开门 ，退出开门计数++

		 
		if (output2state) 
		 { 				 
		 output2time++; 
		 
		 }  //如果是开门 ，退出开门计数++
	
 if(idcycleflag)
 {
//		if (idcycle < DELAY_MS * interval_time[0])   //重复打卡时间计数

//			{ 
			idcycle++;
	 
	 
	 
//			}
 }
 /*************************************************
		    清除按键计数
******************************************************/
	
	if (g_u16OverTimeCnt)                  //AT指令超时计数
      g_u16OverTimeCnt--;

	if (AT_InterOverTimeCnt)                  //AT指令间隔超时计数
      AT_InterOverTimeCnt--;	
	
  if (upOverTimeCnt)	   {upOverTimeCnt-- ;}
	
 
  if (Standbytime)        Standbytime--;
      
	
/*************************************************
		状态分析计数	
******************************************************/	 	
 
		cycle++;    //状态分析计数
 
 /**************************************************
	    延时函数计数
	**************************************************/
   timerdelay++;
	if(timerdelay==10)
		{
			timerdelay=0;
	    timerdelaysec--;
	
	}
  /**************************************************
	   退出菜单模式
	**************************************************/

	
	/**************************************************
	   实时上传记录保存计数
	**************************************************/	
	
	if(rdtemporary_count)
	{	uploadflash_cycle++;}

	
	/**************************************************
	   发送心跳计数
	**************************************************/		
	if(kt_beat_info.flag)
	{
	  kt_beat_info.count ++;
	}
	
	
	/**************************************************
	   显示刷新计数
	**************************************************/

	 if(Show_Refresh_coun)
	   Show_Refresh_coun--;
	
	
		}
		

}


/*
************************************************************
*	函数名称：	TIM7_IRQHandler
*
*	函数功能：	Timer7更新中断服务函数
*
*	入口参数：	无
*
*	返回参数：	无
*
*	说明：		
************************************************************
*/
void TIM7_IRQHandler(void)
{

	if(TIM_GetITStatus(TIM7, TIM_IT_Update) != RESET)
	{
		TIM_ClearITPendingBit(TIM7, TIM_IT_Update  );  //清除TIMx更新中断标志 

		
	}

}

//void TIM2_IRQHandler(void)
//{
//	if ( TIM_GetITStatus(TIM2 , TIM_IT_Update) != RESET ) 
//	{	
//	
//				timer2_isr();	
//	
//		TIM_ClearITPendingBit(TIM2 , TIM_FLAG_Update);  	

//	}		 	
//}



void timedelay_s(u8 t)    //延时函数 单位 秒
{
timerdelaysec=t;
	while (timerdelaysec);
}









