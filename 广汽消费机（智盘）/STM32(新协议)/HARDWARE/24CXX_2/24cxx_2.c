#include "24cxx_2.h" 
#include "delay.h"
//#include "head.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途

//24CXX驱动 代码(适合24C01~24C16,24C32~256未经过测试!有待验证!)		   


//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////



//初始化IIC接口
void AT24CXX_2_Init(void)
{
	IIC_2_Init();
}
//在AT24CXX指定地址读出一个数据
//ReadAddr:开始读数的地址  
//返回值  :读到的数据
u8 AT24CXX_2_ReadOneByte(u16 ReadAddr)
{				  
	u8 temp=0;		  	    																 
    IIC_2_Start();  
	if(EE_TYPE_2>AT24C16_2)
	{
		IIC_2_Send_Byte(0XA0);	   //发送写命令
		IIC_2_Wait_Ack();
		IIC_2_Send_Byte(ReadAddr>>8);//发送高地址
			 
	}else IIC_2_Send_Byte(0XA0+((ReadAddr/256)<<1));   //发送器件地址0XA0,写数据 	 

	IIC_2_Wait_Ack(); 
  IIC_2_Send_Byte(ReadAddr%256);   //发送低地址
	IIC_2_Wait_Ack();	    
	IIC_2_Start();  	 	   
	IIC_2_Send_Byte(0XA1);           //进入接收模式			   
	IIC_2_Wait_Ack();	 
    temp=IIC_2_Read_Byte(0);		   
    IIC_2_Stop();//产生一个停止条件	  
 //   delay_ms(4);
	return temp;
}
//在AT24CXX指定地址写入一个数据
//WriteAddr  :写入数据的目的地址    
//DataToWrite:要写入的数据
void AT24CXX_2_WriteOneByte(u16 WriteAddr,u8 DataToWrite)
{				   	  	    																 
    IIC_2_Start();  
		IIC_2_Send_Byte(0XA0);	    //发送写命令
		IIC_2_Wait_Ack();
		IIC_2_Send_Byte(WriteAddr>>8);//发送高地址
 		 
	  IIC_2_Wait_Ack();	   
    IIC_2_Send_Byte(WriteAddr%256);   //发送低地址
	  IIC_2_Wait_Ack(); 	 										  		   
	  IIC_2_Send_Byte(DataToWrite);     //发送字节							   
	  IIC_2_Wait_Ack();  		    	   
    IIC_2_Stop();//产生一个停止条件 
	  delay_ms(10);
  	
}

/*---------------------------------页写入-------------------------------------*/
 void  AT24CXX_2_Write(u16 address, u8 *date , u16 number)
{
	u8 i;
	IIC_2_Start();
	
	IIC_2_Send_Byte(0xa0);   				//器件地址
	
	IIC_2_Wait_Ack();      
	
	IIC_2_Send_Byte((address & 0xFFFF) >> 8);			//内存地址高8位
	
	IIC_2_Wait_Ack();  
	
	IIC_2_Send_Byte(address & 0xFF);      	//内存地址低8位
	
	IIC_2_Wait_Ack(); 
	
	for(i=0;i<number;i++)	    
	{	
		IIC_2_Send_Byte(*date++);   		//写入数据	
		
		IIC_2_Wait_Ack(); 	
	} 
	
	IIC_2_Stop();
		
	delay_ms(8);
}



//在AT24CXX里面的指定地址开始写入长度为Len的数据
//该函数用于写入16bit或者32bit的数据.
//WriteAddr  :开始写入的地址  
//DataToWrite:数据数组首地址
//Len        :要写入数据的长度2,4
void AT24CXX_2_WriteLenByte(u16 WriteAddr,u32 DataToWrite,u8 Len)
{  	
	u8 t;
	for(t=0;t<Len;t++)
	{
		AT24CXX_2_WriteOneByte(WriteAddr+t,(DataToWrite>>(8*t))&0xff);
	}												    
}

//在AT24CXX里面的指定地址开始读出长度为Len的数据
//该函数用于读出16bit或者32bit的数据.
//ReadAddr   :开始读出的地址 
//返回值     :数据
//Len        :要读出数据的长度2,4
u32 AT24CXX_2_ReadLenByte(u16 ReadAddr,u8 Len)
{  	
	u8 t;
	u32 temp=0;
	for(t=0;t<Len;t++)
	{
		temp<<=8;
		temp+=AT24CXX_2_ReadOneByte(ReadAddr+Len-t-1); 	 				   
	}
	return temp;												    
}
//检查AT24CXX是否正常
//这里用了24XX的最后一个地址(255)来存储标志字.
//如果用其他24C系列,这个地址要修改
//返回1:检测失败
//返回0:检测成功
u8 AT24CXX_2_Check(void)
{
	u8 temp;
	temp=AT24CXX_2_ReadOneByte(65535);//避免每次开机都写AT24CXX			   
	if(temp==0X55)return 0;		   
	else//排除第一次初始化的情况
	{
		AT24CXX_2_WriteOneByte(65535,0X55);
	    temp=AT24CXX_2_ReadOneByte(65535);	  
		if(temp==0X55)return 0;
	}
	return 1;											  
}

//在AT24CXX里面的指定地址开始读出指定个数的数据
//ReadAddr :开始读出的地址 对24c02为0~255
//pBuffer  :数据数组首地址
//NumToRead:要读出数据的个数
void AT24CXX_2_Read(u16 ReadAddr,u8 *pBuffer,u16 NumToRead)
{
	while(NumToRead)
	{
		*pBuffer++=AT24CXX_2_ReadOneByte(ReadAddr++);	
		NumToRead--;
	}
}  
 


//在AT24CXX里面的指定地址开始写入指定个数的数据
//WriteAddr :开始写入的地址 对24c02为0~255
//pBuffer   :数据数组首地址
//NumToWrite:要写入数据的个数
void AT24CXX_2_Write1(u16 WriteAddr,u8 *pBuffer,u16 NumToWrite)
{
	while(NumToWrite--)
	{
		AT24CXX_2_WriteOneByte(WriteAddr,*pBuffer);
		WriteAddr++;
		pBuffer++;
	}
}
 
void AT24C256Check_2(void)
	{

 	while(AT24CXX_2_Check())//检测不到24c02
	{
//     OLED24C256check();    //显示  AT24C256，Start failed

//	printf("AT24C256,CHECKshibai \r\n");
		delay_ms(10);
		
	}

}















