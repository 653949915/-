#ifndef __USART_H
#define __USART_H
#include "stdio.h"	
#include "sys.h" 
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;

//����1��ʼ��		   

#define USART_REC_LEN  			530  	//�����������ֽ��� 200
#define EN_USART1_RX 			1		//ʹ�ܣ�1��/��ֹ��0������1����
	  	
extern u8  USART1_RX_CRLF;       //UART2���� \r\n  ���

extern u16 USART_RX_STA;         		//����״̬���	
//����봮���жϽ��գ��벻Ҫע�����º궨��
void uart_init(u32 bound);
void uart2_init(u32 bound);
void uart3_init(u32 bound);

extern u8   u1_Rec_Over_Flag;           //������ɱ�־
extern u8   u1_RxTimeout;               //���ڽ��ճ�ʱ��   
extern u32  u1_Rec_Len;                   //Rec_LenΪ���յ����ַ�����

#ifdef   WISDOM_PLATE     //������
void uart4_init(u32 bound);
#endif	
#endif


