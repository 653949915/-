#include "Optocoupler.h"

//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;

//����������������	   

//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	   

//��ʼ��PC6.7.8Ϊ�����.��ʹ������ڵ�ʱ��		    
//LED IO��ʼ��
void OPTOCOUPLER_Init(void)
{
 
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);	 //ʹ��PC�˿�ʱ��
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8;				     //����123-->PC.6.78 �˿�����
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		                       //�������
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		                       //IO���ٶ�Ϊ50MHz
 GPIO_Init(GPIOC, &GPIO_InitStructure);					                             //�����趨������ʼ��GPIOA.8
 GPIO_SetBits(GPIOC,GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8);						           //PC.6.7.8   �����
	 	
}
 

















