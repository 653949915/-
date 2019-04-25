#include "myiic_2.h"
#include "delay.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;

//IIC���� ����	   

//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////
 
//��ʼ��IIC
void IIC_2_Init(void)
{					     
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOE, ENABLE );	//ʹ��GPIOBʱ��
	   
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5|GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;   //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOE, &GPIO_InitStructure);
	GPIO_SetBits(GPIOE,GPIO_Pin_5|GPIO_Pin_6); 	//PB0,PB1 �����
//		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD ;   //�������
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_Init(GPIOE, &GPIO_InitStructure);
//	GPIO_SetBits(GPIOE,GPIO_Pin_0|GPIO_Pin_1); 	//PB0,PB1 �����
	
	
}
//����IIC��ʼ�ź�
void IIC_2_Start(void)
{
	SDA_2_OUT();     //sda�����
	IIC_2_SDA=1;	  	  
	IIC_2_SCL=1;
	delay_us(4);
 	IIC_2_SDA=0;//START:when CLK is high,DATA change form high to low 
	delay_us(4);
	IIC_2_SCL=0;//ǯסI2C���ߣ�׼�����ͻ�������� 
}	  
//����IICֹͣ�ź�
void IIC_2_Stop(void)
{
	SDA_2_OUT();//sda�����
	IIC_2_SCL=0;
	IIC_2_SDA=0;//STOP:when CLK is high DATA change form low to high
 	delay_us(4);
	IIC_2_SCL=1; 
	IIC_2_SDA=1;//����I2C���߽����ź�
	delay_us(4);							   	
}
//�ȴ�Ӧ���źŵ���
//����ֵ��1������Ӧ��ʧ��
//        0������Ӧ��ɹ�
u8 IIC_2_Wait_Ack(void)
{
	u8 ucErrTime=0;
	SDA_2_IN();      //SDA����Ϊ����  
	IIC_2_SDA=1;delay_us(1);	   
	IIC_2_SCL=1;delay_us(1);	 
	while(READ_2_SDA)
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			IIC_2_Stop();
			return 1;
		}
	}
	IIC_2_SCL=0;//ʱ�����0 	   
	return 0;  
} 
//����ACKӦ��
void IIC_2_Ack(void)
{
	IIC_2_SCL=0;
	SDA_2_OUT();
	IIC_2_SDA=0;
	delay_us(2);
	IIC_2_SCL=1;
	delay_us(2);
	IIC_2_SCL=0;
}
//������ACKӦ��		    
void IIC_2_NAck(void)
{
	IIC_2_SCL=0;
	SDA_2_OUT();
	IIC_2_SDA=1;
	delay_us(2);
	IIC_2_SCL=1;
	delay_us(2);
	IIC_2_SCL=0;
}					 				     
//IIC����һ���ֽ�
//���شӻ�����Ӧ��
//1����Ӧ��
//0����Ӧ��			  
void IIC_2_Send_Byte(u8 txd)
{                        
    u8 t;   
	SDA_2_OUT(); 	    
    IIC_2_SCL=0;//����ʱ�ӿ�ʼ���ݴ���
    for(t=0;t<8;t++)
    {              
        //IIC_SDA=(txd&0x80)>>7;
		if((txd&0x80)>>7)
			IIC_2_SDA=1;
		else
			IIC_2_SDA=0;
		txd<<=1; 	  
		delay_us(2);   //��TEA5767��������ʱ���Ǳ����
		IIC_2_SCL=1;
		delay_us(2); 
		IIC_2_SCL=0;	
		delay_us(2);
    }	 
} 	    
//��1���ֽڣ�ack=1ʱ������ACK��ack=0������nACK   
u8 IIC_2_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
	SDA_2_IN();//SDA����Ϊ����
    for(i=0;i<8;i++ )
	{
        IIC_2_SCL=0; 
        delay_us(2);
		IIC_2_SCL=1;
        receive<<=1;
        if(READ_2_SDA)receive++;   
		delay_us(1); 
    }					 
    if (!ack)
        IIC_2_NAck();//����nACK
    else
        IIC_2_Ack(); //����ACK   
    return receive;
}



























