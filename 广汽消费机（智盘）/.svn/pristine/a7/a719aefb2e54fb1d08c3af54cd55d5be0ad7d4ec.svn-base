#include "Head.h"

/**********************************************************
//变量定义
**********************************************************/


u8  wg1cycle;
u8  wg1idx; //韦根接收个数
u8  wg1cardno[WG1_COUNT]; //韦根接收
static u32 bwg1;

//外部中断0服务程序
void EXTIX_Init_WG1(void)
{
 
 	EXTI_InitTypeDef EXTI_InitStructure;
 	NVIC_InitTypeDef NVIC_InitStructure;

  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	//使能复用功能时钟

    //GPIOC.0 中断线以及中断初始化配置   下降沿触发
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource0);

  	EXTI_InitStructure.EXTI_Line=EXTI_Line0;	//KEY2
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	 	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器

   //GPIOC.1	  中断线以及中断初始化配置 下降沿触发 //KEY1
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource1);
  	EXTI_InitStructure.EXTI_Line=EXTI_Line1;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;	
  	EXTI_Init(&EXTI_InitStructure);	  	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器

    NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;			//使能按键DATA0所在的外部中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x03;	//抢占优先级3， 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x03;					//子优先级2
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure);


  	NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;			//使能按键DATA1所在的外部中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x03;	//抢占优先级3 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x04;					//子优先级1 
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure);  	  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器

 
}


//外部中断0服务程序 
//void EXTI15_10_IRQHandler(void)
void EXTI0_IRQHandler(void)	

{
if(EXTI_GetITStatus(EXTI_Line0)!=RESET)//判断某个线上的中断是否发生   中断10
{
		if (!bwg1)
	{
		wg1cardno[wg1idx++] = 0; //韦根DATA0输入

////		INT_CLKO &= 0xEF; //1110 1111
////		INT_CLKO |= 0x10; //0001 0000
 	  	WG1_DATA0 = 1;

		if (wg1idx == WG1_COUNT)
		{
			bwg1 = 1;
			wg1idx = 0;
		}
	}
	
EXTI_ClearITPendingBit(EXTI_Line0); //清除 LINE 上的中断标志位
}
}		


void EXTI1_IRQHandler(void)	
{

if(EXTI_GetITStatus(EXTI_Line1)!=RESET)//判断某个线上的中断是否发生   中断11
{

		if (!bwg1)
	{
		wg1cardno[wg1idx++] = 1; //韦根DATA1输入

//		INT_CLKO &= 0xDF; //1101 1111
//		INT_CLKO |= 0x20; //0010 0000
		WG1_DATA1 = 1;

		if (wg1idx == WG1_COUNT)
		{
			bwg1 = 1;
			wg1idx = 0;
		}
	}	
	
EXTI_ClearITPendingBit(EXTI_Line1); //清除 LINE 上的中断标志位
}

}
 


/**********************************************************
//初始化韦根
**********************************************************/
void InitWG1(void)
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

	bwg1 = 0;
	wg1idx = 0;
	wg1cycle = 0;

	WG1_DATA0 = 1;
	WG1_DATA1 = 1;

	for (i = 0; i < WG1_COUNT; i++)
	{
		wg1cardno[i] = 0x00;
	}


}

/**********************************************************
//检验韦根数据
**********************************************************/
static u32 CheckWG1Data(void)
{
	u8 i, p, im;

	im = WG1_COUNT / 2;

	//偶校验
	p = wg1cardno[0];
	for (i = 1; i < im; i++)
	{
		p = p ^ wg1cardno[i];
	}
	if (p != 0) return 0;

	//奇校验
	p = wg1cardno[WG1_COUNT - 1];
	for (i = im; i < WG1_COUNT - 1; i++)
	{
		p = p ^ wg1cardno[i];
	}
	if (p != 1) return 0;

	return 1;
}

/**********************************************************
//获得卡号
**********************************************************/
 void GetWG1Cardno(void)
{
	u8 i,j;
	u8 tmp[WG1_CARD_SIZE];

	for (i = 0; i < WG1_CARD_SIZE; i++)  //高位在前
	{
		tmp[i] = 0x00;
		for (j = 1; j < 9; j++)
		{
			tmp[i] <<= 1;
			tmp[i] |= wg1cardno[i * 8 + j];
		}
	}

	for (i = 0; i < WG1_CARD_SIZE; i++)  //低位在前
	{
		idbuff[i] = tmp[WG1_CARD_SIZE - 1 - i];
	}
//MyStrCPY(idbuff, ucArray_ID, 4);//取卡号		
// HexToStr(cardbuff,idbuff, 4);//将四位序列号转换为8位字符串形式	
}

/**********************************************************
//处理韦根卡号
**********************************************************/
u32 ProcessWG1(void)
{
	u32 b;
	if (wg1cycle > WG1_INIT_CYCLE)
	{
		InitWG1();
	}

	b = 0;
	if (bwg1)
	{
		if (CheckWG1Data())
		{
			b = 1;
			GetWG1Cardno();
		}
		InitWG1();	
	}
	return b;
}

