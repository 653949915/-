#include "sysrest.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;

//��������������	   

//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	   

//��ʼ��PC15Ϊ�����.��ʹ������ڵ�ʱ��		    
//ϵͳ�����ָ��������ð�����ʼ��
void SYSREST_KEY_Init(void)
{
 
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);	 //ʹ��GPIOD�˿�ʱ��
 
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;				       //SYSREST-->PC.15 �˿�����
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		       //��������
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	     //�ٶ�Ϊ50MHz
 GPIO_Init(GPIOB, &GPIO_InitStructure);	                 //���ݲ�����ʼ��GPIOC.15
 
 GPIO_SetBits(GPIOB,GPIO_Pin_1);                       //����0����λ��������

}
