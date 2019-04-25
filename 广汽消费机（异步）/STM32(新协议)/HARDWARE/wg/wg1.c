#include "Head.h"

/**********************************************************
//��������
**********************************************************/


u8  wg1cycle;
u8  wg1idx; //Τ�����ո���
u8  wg1cardno[WG1_COUNT]; //Τ������
static u32 bwg1;

//�ⲿ�ж�0�������
void EXTIX_Init_WG1(void)
{
 
 	EXTI_InitTypeDef EXTI_InitStructure;
 	NVIC_InitTypeDef NVIC_InitStructure;

  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	//ʹ�ܸ��ù���ʱ��

    //GPIOC.0 �ж����Լ��жϳ�ʼ������   �½��ش���
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource0);

  	EXTI_InitStructure.EXTI_Line=EXTI_Line0;	//KEY2
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	 	//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���

   //GPIOC.1	  �ж����Լ��жϳ�ʼ������ �½��ش��� //KEY1
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource1);
  	EXTI_InitStructure.EXTI_Line=EXTI_Line1;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;	
  	EXTI_Init(&EXTI_InitStructure);	  	//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���

    NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;			//ʹ�ܰ���DATA0���ڵ��ⲿ�ж�ͨ��
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x03;	//��ռ���ȼ�3�� 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x03;					//�����ȼ�2
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
  	NVIC_Init(&NVIC_InitStructure);


  	NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;			//ʹ�ܰ���DATA1���ڵ��ⲿ�ж�ͨ��
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x03;	//��ռ���ȼ�3 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x04;					//�����ȼ�1 
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
  	NVIC_Init(&NVIC_InitStructure);  	  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���

 
}


//�ⲿ�ж�0������� 
//void EXTI15_10_IRQHandler(void)
void EXTI0_IRQHandler(void)	

{
if(EXTI_GetITStatus(EXTI_Line0)!=RESET)//�ж�ĳ�����ϵ��ж��Ƿ���   �ж�10
{
		if (!bwg1)
	{
		wg1cardno[wg1idx++] = 0; //Τ��DATA0����

////		INT_CLKO &= 0xEF; //1110 1111
////		INT_CLKO |= 0x10; //0001 0000
 	  	WG1_DATA0 = 1;

		if (wg1idx == WG1_COUNT)
		{
			bwg1 = 1;
			wg1idx = 0;
		}
	}
	
EXTI_ClearITPendingBit(EXTI_Line0); //��� LINE �ϵ��жϱ�־λ
}
}		


void EXTI1_IRQHandler(void)	
{

if(EXTI_GetITStatus(EXTI_Line1)!=RESET)//�ж�ĳ�����ϵ��ж��Ƿ���   �ж�11
{

		if (!bwg1)
	{
		wg1cardno[wg1idx++] = 1; //Τ��DATA1����

//		INT_CLKO &= 0xDF; //1101 1111
//		INT_CLKO |= 0x20; //0010 0000
		WG1_DATA1 = 1;

		if (wg1idx == WG1_COUNT)
		{
			bwg1 = 1;
			wg1idx = 0;
		}
	}	
	
EXTI_ClearITPendingBit(EXTI_Line1); //��� LINE �ϵ��жϱ�־λ
}

}
 


/**********************************************************
//��ʼ��Τ��
**********************************************************/
void InitWG1(void)
{
	u8 i;
//	u8 key;
	
//	if (wgidx == 4) //Τ��������2014-10-11
//	{
//		key = 0;
//		for (i = 0; i < 4; i++)
//		{
//			key <<= 1;
//			key |= wgcardno[i];
//		}

//		//SendChar(key); //������

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
//����Τ������
**********************************************************/
static u32 CheckWG1Data(void)
{
	u8 i, p, im;

	im = WG1_COUNT / 2;

	//żУ��
	p = wg1cardno[0];
	for (i = 1; i < im; i++)
	{
		p = p ^ wg1cardno[i];
	}
	if (p != 0) return 0;

	//��У��
	p = wg1cardno[WG1_COUNT - 1];
	for (i = im; i < WG1_COUNT - 1; i++)
	{
		p = p ^ wg1cardno[i];
	}
	if (p != 1) return 0;

	return 1;
}

/**********************************************************
//��ÿ���
**********************************************************/
 void GetWG1Cardno(void)
{
	u8 i,j;
	u8 tmp[WG1_CARD_SIZE];

	for (i = 0; i < WG1_CARD_SIZE; i++)  //��λ��ǰ
	{
		tmp[i] = 0x00;
		for (j = 1; j < 9; j++)
		{
			tmp[i] <<= 1;
			tmp[i] |= wg1cardno[i * 8 + j];
		}
	}

	for (i = 0; i < WG1_CARD_SIZE; i++)  //��λ��ǰ
	{
		idbuff[i] = tmp[WG1_CARD_SIZE - 1 - i];
	}
//MyStrCPY(idbuff, ucArray_ID, 4);//ȡ����		
// HexToStr(cardbuff,idbuff, 4);//����λ���к�ת��Ϊ8λ�ַ�����ʽ	
}

/**********************************************************
//����Τ������
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

