#include "Head.h"

/**********************************************************
//变量定义
**********************************************************/


u8  wg2cycle;
u8  wg2idx; //韦根接收个数
u8  wg2cardno[WG2_COUNT]; //韦根接收
static u32 bwg2;

//外部中断0服务程序
void EXTIX_Init_WG2(void)
{
 
 	EXTI_InitTypeDef EXTI_InitStructure;
 	NVIC_InitTypeDef NVIC_InitStructure;

  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	//使能复用功能时钟

    //GPIOC.2 中断线以及中断初始化配置   下降沿触发
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource2);
  	EXTI_InitStructure.EXTI_Line=EXTI_Line2;	//KEY2
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	 	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器

   //GPIOC.3	  中断线以及中断初始化配置 下降沿触发 //KEY1
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource3);
  	EXTI_InitStructure.EXTI_Line=EXTI_Line3;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;	
  	EXTI_Init(&EXTI_InitStructure);	  	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器

    NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;			//使能按键DATA0所在的外部中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x03;	//抢占优先级2， 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;					//子优先级3
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure);


  	NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;			//使能按键DATA1所在的外部中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x03;	//抢占优先级2 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;					//子优先级4 
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure);  	  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器
}


//外部中断2服务程序 
//void EXTI15_10_IRQHandler(void)
void EXTI2_IRQHandler(void)	

{
if(EXTI_GetITStatus(EXTI_Line2)!=RESET)//判断某个线上的中断是否发生   中断10
{
		if (!bwg2)
	{
		wg2cardno[wg2idx++] = 0; //韦根DATA0输入

////		INT_CLKO &= 0xEF; //1110 1111
////		INT_CLKO |= 0x10; //0001 0000
 	  	WG2_DATA0 = 1;

		if (wg2idx == WG2_COUNT)
		{
			bwg2 = 1;
			wg2idx = 0;
		}
	}
	
EXTI_ClearITPendingBit(EXTI_Line2); //清除 LINE 上的中断标志位
}
}		

//外部中断3服务程序 

void EXTI3_IRQHandler(void)	
{

if(EXTI_GetITStatus(EXTI_Line3)!=RESET)//判断某个线上的中断是否发生   中断11
{

		if (!bwg2)
	{
		wg2cardno[wg2idx++] = 1; //韦根DATA1输入

//		INT_CLKO &= 0xDF; //1101 1111
//		INT_CLKO |= 0x20; //0010 0000
		WG2_DATA1 = 1;

		if (wg2idx == WG2_COUNT)
		{
			bwg2 = 1;
			wg2idx = 0;
		}
	}	
	
EXTI_ClearITPendingBit(EXTI_Line3); //清除 LINE 上的中断标志位
}

}
 


/**********************************************************
//初始化韦根
**********************************************************/
void InitWG2(void)
{
	u8 i;
//	u8 key;
	
//	if (wgidx == 4) //韦根按键，2014-10-11
//	{
//		key = 0;
//		for (i = 0; i < 4; i++)
//		{
//			key <<= 1;
//			key |= wgcardno[i];
//		}

//		//SendChar(key); //测试用

//		switch (key)
//		{
//			case 0x01: ProcessKEY('1');break;
//			case 0x02: ProcessKEY('2');break;
//			case 0x03: ProcessKEY('3');break;
//			case 0x04: ProcessKEY('4');break;
//			case 0x05: ProcessKEY('5');break;
//			case 0x06: ProcessKEY('6');break;
//			case 0x07: ProcessKEY('7');break;
//			case 0x08: ProcessKEY('8');break;
//			case 0x09: ProcessKEY('9');break;
//			case 0x0A: ProcessKEY('*');break;
//			case 0x00: ProcessKEY('0');break;
//			case 0x0B: ProcessKEY('#');break;
//		}
//	}

	bwg2 = 0;
	wg2idx = 0;
	wg2cycle = 0;

	WG2_DATA0 = 1;
	WG2_DATA1 = 1;

	for (i = 0; i < WG2_COUNT; i++)
	{
		wg2cardno[i] = 0x00;
	}


}

/**********************************************************
//检验韦根数据
**********************************************************/
static u32 CheckWG2Data(void)
{
	u8 i, p, im;

	im = WG2_COUNT / 2;

	//偶校验
	p = wg2cardno[0];
	for (i = 1; i < im; i++)
	{
		p = p ^ wg2cardno[i];
	}
	if (p != 0) return 0;

	//奇校验
	p = wg2cardno[WG2_COUNT - 1];
	for (i = im; i < WG2_COUNT - 1; i++)
	{
		p = p ^ wg2cardno[i];
	}
	if (p != 1) return 0;

	return 1;
}

/**********************************************************
//获得卡号
**********************************************************/
 void GetWG2Cardno(void)
{
	u8 i,j;
	u8 tmp[WG2_CARD_SIZE];

	for (i = 0; i < WG2_CARD_SIZE; i++)  //高位在前
	{
		tmp[i] = 0x00;
		for (j = 1; j < 9; j++)
		{
			tmp[i] <<= 1;
			tmp[i] |= wg2cardno[i * 8 + j];
		}
	}

	for (i = 0; i < WG2_CARD_SIZE; i++)  //低位在前
	{
		idbuff[i] = tmp[WG2_CARD_SIZE - 1 - i];
	}
//MyStrCPY(idbuff, ucArray_ID, 4);//取卡号		
// HexToStr(cardbuff,idbuff, 4);//将四位序列号转换为8位字符串形式	
}

/**********************************************************
//处理韦根卡号
**********************************************************/
u32 ProcessWG2(void)
{
	u32 b;
	if (wg2cycle > WG2_INIT_CYCLE)
	{
		InitWG2();
	}

	b = 0;
	if (bwg2)
	{
		if (CheckWG2Data())
		{
			b = 1;
			GetWG2Cardno();
		}
		InitWG2();	
	}
	return b;
}

