

/***************************************************************************************************
***********/


#include "head.h"

#include "QR_code.h"


u8   QR_RxDataBuff[50];                         //中断接收数组

u16  QR_u8RxIndexW=0;                               //中断接收数组写指针

u8   USART3_RX_CRLF=0;

uint8_t  QR_ReadDatabuf[20]={0};

uint8_t  QR_Readtohex[8]={0};

uint8_t  ProcessQR_QRRead(void );

uint8_t  ProcessQR_ICRead(void );

uint8_t QRread_styp=0;                         //二维码读头度取到的数据类型  3--IC卡 4--二维码

uint8_t  oldQRID[4]={0x00};

uint8_t  Asynchronous_QR_falg=0;      //异步二维码，客餐订餐标识


char *getQR_rebuff() 
	{
			return ( char *)&QR_RxDataBuff;
	}

char *redata_QR;


void QR_SendString(uint8_t *combuff_QR ,uint16_t len)
{
	uint16_t t;
	for(t=0;t<len;t++)
	 {
		  USART_SendData(QR_UART, combuff_QR[t]);//向串口1发送数据
			
			while(USART_GetFlagStatus(QR_UART,USART_FLAG_TC)!=SET);//等待发送结束
	
   }
}

void QR_SendByte(uint8_t combuff1)
{
  //    delay_us(500);
		USART_SendData(QR_UART, combuff1);//向串口1发送数据
	
		while(USART_GetFlagStatus(QR_UART,USART_FLAG_TC)!=SET);//等待发送结束
}


	//二维码读头清空缓冲区
void cleanQR_bcrebuff(void)
{
    uint16_t i=0;
	
    i=	48;
	
	QR_u8RxIndexW=0;
	while(i)
	{
	 QR_RxDataBuff[--i]=0;

	}
}

	/**********************************************************
//初始化二维码读头串口通讯缓冲区
**********************************************************/
void InitQRCombuff(void)
{
	cleanQR_bcrebuff();
	
	QR_u8RxIndexW=0;
	
	USART3_RX_CRLF=0;
}


 uint8_t ProcessQR_Commu(void)         	//处理二维码通讯
	{
		char *p;
    char b[] = ":";
		
		QRread_styp=0;
		
		if(USART3_RX_CRLF)           //在收到 \r\n
		{

			
			redata_QR = getQR_rebuff(); 
			
//			SYN6288_Send(SYN6288CMD_VOICE_PLAY ,SYN6288CMDPARAM_PLAY_MUSIC0,"soundb" ,6);
						
			
			if(strstr(redata_QR,"ketanQR:"))	               //检测到开机信息
				{		
					p = strstr(redata_QR,"GQ");          //检测广汽标志
					if(NULL == p)		
					{
						Beep(4, SHORT_BEEP);
					     //报警非法码
						
						SYN6288_Send(SYN6288CMD_VOICE_PLAY ,SYN6288CMDPARAM_PLAY_MUSIC0,"无效二维码" ,10);
						
					}
					else
					{								
						p =NULL;
						p=strstr(redata_QR,b);
					 
						if(NULL != p)
						{
							p+=3;		
											
							memset(QR_ReadDatabuf, 0, 18);   //清0
								
							memcpy(QR_ReadDatabuf, (const int8_t *)p, 14 );   	

							if(ProcessQR_QRRead())
							{										
								
								QRread_styp =4;			
								
							}
							else 
								{
	//								SYN6288_Send(SYN6288CMD_VOICE_PLAY ,SYN6288CMDPARAM_PLAY_MUSIC0,"sounda" ,6);
									
									Beep(4, SHORT_BEEP);
								
									QRread_styp =0;
								}						
							}
					 }		
				 }
			else if(strstr(redata_QR,"ketanIC:"))	               //检测到开机信息
				{
				p=strstr(redata_QR,b);
			 
				if(NULL != p)
				{
					p+=1;		
									
					memset(QR_ReadDatabuf, 0, 8);   //清0
						
					memcpy(QR_ReadDatabuf, (const int8_t *)p, 8 );   
					
					ProcessQR_ICRead();
					
					QRread_styp =5;
					
			//		ProcessCard(4);                //二维码读头
				 }						
				}		
			
	  InitQRCombuff();			
				
		 return QRread_styp;		
				
	  }
		
		 return 0;				
}




uint8_t  ProcessQR_QRRead(void )
{

	Asynchronous_QR_falg =0 ;      //客餐标志
	
		StrToHex(QR_Readtohex,QR_ReadDatabuf,7);		
		
	//  QR_SendString(ketanbuf1 ,4)	;      //发送数据
	
	

	if(QR_Readtohex[6]!=GetXOR(QR_Readtohex,6))  //异或校验
		{
			return 0 ;
		}
	else if(QR_Readtohex[1]!=time_buf[3])     //校验日
		{		
			return 0 ;		
		}		
		
	else if((QR_Readtohex[0]&0x0F)!=(((time_buf[2]>>4)&0x0F)*10 + (time_buf[2]&0x0F)))    //校验月
		{
		
		return 0 ;
		
		}
		
	else 
	{		
		 memcpy(idbuff, QR_Readtohex +2 , 4 );
	
		if((idbuff[0]&0xF0) !=0X10)	     //如果是非员工餐票
		{
			 Asynchronous_QR_falg =1 ;      //客餐标志
		}		
		
		
		if (  MyStrEQ(idbuff, oldQRID, CARD_SIZE))
				{					
						return 0;
				}		
		
//		 memcpy( oldQRID , idbuff , 4 );
		
		
		return 1;
	}		
		

	//  HexToStr(cardbuff,idbuff, 4);//将四位序列号转换为8位字符串形式		显示用

}


uint8_t  ProcessQR_ICRead(void )
{	
		StrToHex(QR_Readtohex,QR_ReadDatabuf,4);		
		
	//  QR_SendString(ketanbuf1 ,4)	;      //发送数据

	  memcpy(idbuff, QR_Readtohex, 4 );

//	  HexToStr(cardbuff,idbuff, 4);//将四位序列号转换为8位字符串形式		显示用

	return 1;
}








