#ifndef _TM1650_H_
#define _TM1650_H_
//#include "stm32f10x.h"
#include "sys.h"
//���ýӿڵ� pin
#define TM16_RCC        RCC_APB2Periph_GPIOD			//RCC
#define TM16_PORT       GPIOD					//PORT
#define TM16_SDA        GPIO_Pin_0			//SDA
#define TM16_SCL        GPIO_Pin_1			//SCL
#define TM16_ReadSDA() 	GPIO_ReadInputDataBit(TM16_PORT,TM16_SDA)		//��ȡSDA

#define TM16_SDA_H GPIO_SetBits(TM16_PORT,TM16_SDA)
#define TM16_SDA_L GPIO_ResetBits(TM16_PORT,TM16_SDA)
#define TM16_SCL_H GPIO_SetBits(TM16_PORT,TM16_SCL)
#define TM16_SCL_L GPIO_ResetBits(TM16_PORT,TM16_SCL)

#define TM16_delay(x)    {delay_us(x);} //  {dtmelay(x);}		//������ʱ����,������ֲ�����޸�Ϊ�Լ�����ʱ����

void TM16_INIT(unsigned char brig);		//��ʼ��TM1650,  ����Ϊ���� 0-7
void TM16_Display(unsigned char data,unsigned char di);//��ʾ������dataΪ��ʾ�����ݣ�0-99��di�����Ƿ���ʾС���㣬0Ϊ������ʾС���㣬1Ϊ��һλ��ʾС���㣬2Ϊ�ڶ�λ��ʾС���㣬3Ϊ��һλ�͵ڶ�λ����ʾС����

//***********����������*************************************
unsigned char TM1650_FD650_READ(void );

uint8_t  tmKeyscan(void);

#endif
