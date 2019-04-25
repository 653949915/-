

/***************************************************************************************************
	* Copyright (c) 2016, Biohermes
	* All rights reserved.
	* 文件名称： QuectelMC20.c
	* 摘 要：    MC20模块
	* 当前版本： V1.0, , 2016-01-05
	* 更改记录： 无
	* 关机状态下,MC20串口可能会发送乱码出来，增加两个继电器通断MC20和MCU的串口
***************************************************************************************************/
//#include "QuectelMC20.h"

//C库
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "head.h"
#include "BC95.h"

#ifdef   NB_BC95

//static  uint8_t AT_QISEND[]   = {"AT+QISEND=10\r\n"};

static  uint8_t AT_AT[]         = {"AT\r\n"};                            //连接测试命令
static  uint8_t AT_CGSN[]       = {"AT+CGSN=1\r\n"};                     //查询设备IMEI号
static  uint8_t AT_CIMI[]       = {"AT+CIMI\r\n"};                       //查询USIM卡IMSI号
static  uint8_t AT_NNMI_C[]     = {"AT+NNMI?\r\n"};                      //查看下行数据通知
static  uint8_t AT_NNMI[]       = {"AT+NNMI=1\r\n"};                     //查看下行数据通知
static  uint8_t AT_NCDP_C[]     = {"AT+NCDP?\r\n"};                      //查询 IOT 平台 IP 地址
static  uint8_t AT_CGATT_C[]    = {"AT+CGATT?\r\n"};                    //查看模块是否附着网络成功
static  uint8_t AT_CCLK_C[]     = {"AT+CCLK?\r\n"};                      //获取网络时间
//       
static  uint8_t AT_CFUN_N[]     = {"AT+CFUN=0\r\n"};                      //设置电话功能
static  uint8_t AT_NCDP[]       = {"AT+NCDP=117.60.157.137,5683\r\n"};    //设置IP
static  uint8_t AT_CFUN_F[]     = {"AT+CFUN=1\r\n"};                      //设置电话功能
static  uint8_t AT_NRB[]        = {"AT+NRB\r\n"};                         //重启

//AT+CFUN=0
//AT+NCDP=117.60.157.137,5683
//AT+NCDP=117.78.47.187,5683
//AT+NCDP=112.93.129.154,5683
//AT+CFUN=1
//AT+NRB


 uint8_t fbuff[1]   = {'"'};


// uint8_t NCDP_HW_17[19] = {"117.60.157.137,5683"};                      //

 uint8_t NCDP_HW_17[19] = {"117.60.157.137,5683"};                      //
	
uint8_t  BC95_IMEI[IMEI_SIZE]  = {0};             //BC95的IMEI号
uint8_t  SIM_IMSI [IMSI_SIZE]  = {0};             //BC95的IMEI号
uint8_t  BC95_CLOCK[30]={0};                      //BC95网络时间
	
	
//static u8 CGSNbuff[15]={0};
//static u8 CIMIbuff[15]={0};




struct retstruct
{
    u8 ret1;
    u8 ret2;
}s_stRetData;

u16 g_u16OverTimeCnt=0;                             //超时倒计时计数器，每秒自减1
u8  RxDataBuff[RX_BUFF_LEN];                         //中断接收数组

       u16  g_u8RxIndexW=0;                         //中断接收数组写指针
static u16  s_u8RxIndexR=0;                         //中断接收数组读指针



//初始化PA8为输出口.并使能这两个口的时钟		    

void BC95_REST_Init(void)
{
 
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	 //使能PA端口时钟
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;				  //GSM_POWER-->PA.8 端口配置 开关机
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 	//推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//IO口速度为50MHz
 GPIO_Init(GPIOA, &GPIO_InitStructure);					    //根据设定参数初始化GPIOA.8
 GPIO_SetBits(GPIOA,GPIO_Pin_8);						        //PA.8 输出高
		
}
 


void BC95_SendString(uint8_t *combuff ,uint16_t len)
{
	uint16_t t;
	for(t=0;t<len;t++)
	 {
		  USART_SendData(BC95_UART, combuff[t]);//向串口1发送数据
			
			while(USART_GetFlagStatus(BC95_UART,USART_FLAG_TC)!=SET);//等待发送结束
	
   }
}

void BC95_SendByte(uint8_t combuff)
{
  //    delay_us(500);
		USART_SendData(BC95_UART, combuff);//向串口1发送数据
	
		while(USART_GetFlagStatus(BC95_UART,USART_FLAG_TC)!=SET);//等待发送结束
}


/***************************************************************************************************
 * 函 数 名: QuectelBC95_Rest
 * 功能描述: BC95 硬件复位
 * 函数说明: 
 * 调用函数: 无
 * 全局变量: 无
 * 输　　入: 无
 * 返　　回: 无
***************************************************************************************************/
void QuectelBC95_Rest(void)
{
	BC95REST =0;         //复位引脚拉低 500ms
	
	delay_ms(500);
	delay_ms(500);
	
	BC95REST =1;
	
}

/***************************************************************************************************
 * 函 数 名: QuectelBC95_SendCmd
 * 功能描述: BC95底层发送命令
 * 函数说明: 
 * 调用函数: 无
 * 全局变量:
 * 输　　入: *string 需要发送的字符串指针
 * 返　　回: 无
***************************************************************************************************/
 void QuectelBC95_SendCmd(const u8 *string)
{
    u8 i = 0;
    
    while (string[i] != 0)
    {
        if (string[i] == '*')
        {
            BC95_SendByte('"');
        }
        else
        {
            BC95_SendByte(string[i]);
        }
        i++;
    }
    s_u8RxIndexR = 0;
    g_u8RxIndexW = 0;
}

/***************************************************************************************************
 * 函 数 名: GetAckData
 * 功能描述: 比较接收的数据和给定字符串是否相同
 * 函数说明: 无
 * 调用函数: 无
 * 全局变量: 无
 * 输　　入: buff 需要比较的数组， *string给定字符串指针
 * 返　　回: 状态
***************************************************************************************************/
 u8 GetAckData(char *string, u16 overtime)
{
    u8 j=0;
    
    g_u16OverTimeCnt = overtime;
    while (1)
    {
        if (s_u8RxIndexR != g_u8RxIndexW)
        {
					
            if (string[j] == RxDataBuff[s_u8RxIndexR])
                j++;
            else
                j = 0;
            if (string[j] == 0)
                return BC95_OK;
            s_u8RxIndexR++;
            if (s_u8RxIndexR > RX_BUFF_LEN-1)
                s_u8RxIndexR = 0;
        }
        if (g_u16OverTimeCnt == 0)                      //超时退出
            return OVER_TIME;
    }
}

/***************************************************************************************************
 * 函 数 名: ExpectReceData
 * 功能描述: 比较接收的数据和给定字符串是否相同，然后接收剩下的数据
 * 函数说明: ret结构暂时只包括两个返回值。
 * 调用函数: 无
 * 全局变量: 无
 * 输　　入: *string给定字符串指针, overtime超时时间， ret接收数据值结构体
 * 返　　回: 状态
***************************************************************************************************/
 u8 ExpectReceData(char *string, u16 overtime, struct retstruct* ret)
{
    u8 i = 0, j = 0, k = 0;
    u8 str[2][5];               //接收ascii码字符串缓存，暂只接收两个数据
    
    g_u16OverTimeCnt = overtime;
    while (1)                   //先判断前面固定字符串是否正确
    {
        if (s_u8RxIndexR != g_u8RxIndexW)
        {
            if (string[j] == RxDataBuff[s_u8RxIndexR])
                j++;
            else
                j = 0;
            s_u8RxIndexR++;
            if (s_u8RxIndexR > RX_BUFF_LEN-1)
                s_u8RxIndexR = 0;
            if (string[j] == 0)
                break;
        }
        if (g_u16OverTimeCnt == 0)                      //超时退出
            return OVER_TIME;
    }
    i = 0;
    j = 1;                  //数据存放从第二个字节开始，第一个字节存放个数
    while (1)
    {
        if (s_u8RxIndexR != g_u8RxIndexW)
        {
            if (RxDataBuff[s_u8RxIndexR] == ',')
            {
                str[i][0] = j - 1;              //保存接收到的字符个数
                j = 1;
                i++;
            }
            else if (RxDataBuff[s_u8RxIndexR] == '\r')
            {
                k = 1;
            }
            else if (RxDataBuff[s_u8RxIndexR] == '\n')
            {
                if (k)
                {
                    str[i][0] = j - 1;          //\r\n为结束符
                    break;
                }
                else
                {
                    i = 0;
                    j = 1;
                }
            }
            else
            {
                str[i][j] = RxDataBuff[s_u8RxIndexR];
                j++;
            }
            s_u8RxIndexR++;
            if (s_u8RxIndexR > RX_BUFF_LEN-1)
                s_u8RxIndexR = 0;
        }
        if (g_u16OverTimeCnt == 0)                      //超时退出
            return OVER_TIME;
    }
    if (str[0][0] == 2)
        ret->ret1 = (str[0][1]-'0')*10 + (str[0][2]-'0');
    else
        ret->ret1 = (str[0][1]-'0');
    if (str[1][0] == 2)
        ret->ret2 = (str[1][1]-'0')*10 + (str[1][2]-'0');
    else
        ret->ret2 = (str[1][1]-'0');
    return BC95_OK;
}




/***************************************************************************************************
 * 函 数 名: ExpectReceData
 * 功能描述: 比较接收的数据和给定字符串是否相同，然后接收剩下的数据
 * 函数说明: ret结构暂时只包括两个返回值。
 * 调用函数: 无
 * 全局变量: 无
 * 输　　入: *string给定字符串指针, overtime超时时间， ret接收数据值结构体
 * 返　　回: 状态
***************************************************************************************************/
 uint8_t ExpectReceData_1(unsigned char *string, uint16_t overtime, uint8_t *ret)
{
    uint8_t  j = 0, k = 0;
//    u8 str[2][15];               //接收ascii码字符串缓存，暂只接收两个数据
    
	g_u16OverTimeCnt = overtime;
	
    while (1)                   //先判断前面固定字符串是否正确
    {
        if (s_u8RxIndexR != g_u8RxIndexW)
        {
            if (string[j] == RxDataBuff[s_u8RxIndexR])
                j++;
            else
                j = 0;
            s_u8RxIndexR++;
            if (s_u8RxIndexR > RX_BUFF_LEN-1)
                s_u8RxIndexR = 0;
            if (string[j] == 0)
                break;
        }
				
				/* 超时，5000ms */
				if(g_u16OverTimeCnt == 0) 
					{
							
							return OVER_TIME;
					}			
				
    }
		
  //  i = 0;
    j = 0;                  //
    while (1)
    {
        if (s_u8RxIndexR != g_u8RxIndexW)
        {
			
						ret[k] = RxDataBuff[s_u8RxIndexR];
             k++;     
             s_u8RxIndexR++;			

//            if (s_u8RxIndexR > (RX_BUFF_LEN-1))
//                s_u8RxIndexR = 0;						

				//	UART4Send_Data(RxDataBuff,	100);   //测试用  g_u8RxIndexW
				
					
						if ((RxDataBuff[s_u8RxIndexR-1] == '\r')&&RxDataBuff[s_u8RxIndexR] == '\n')//&&(RxDataBuff[s_u8RxIndexR-1] == 'O')&&(RxDataBuff[s_u8RxIndexR] == 'K'))						
							{
  							  s_u8RxIndexR = 0;	
               //   g_u8RxIndexW = 0;									
								  k=0;
								return BC95_OK; 
						    //  break;						
							}		
        }				
				  /* 超时，5000ms */
		      if(g_u16OverTimeCnt == 0) 
            {
       //         printf("Timeout To Enter Sleep!!\r\n");
                
                return OVER_TIME;
            }	
  //  return BC95_OK;						
    }

		    
}


/**********************************************************
//BC95发送AT    测试设备是否在线
**********************************************************/
void QuectelBC95_AT(void )
{
uint8_t ret = 0;
	QuectelBC95_SendCmd(AT_AT);
	ret = GetAckData("OK\r\n",5);         //	
	if (ret == BC95_OK)
		{
	   bc95_device_info.initStep ++;
	   bc95_device_info.errcount =0;
	  }
	else 
	{
		bc95_device_info.err = CONNECT_ERR;
		bc95_device_info.errcount++;
	}
}

/**********************************************************
//BC95发送AT+CGSN=1    查询设备IMEI号
**********************************************************/
void QuectelBC95_CGSN(void )
{
uint8_t ret = 0;
uint8_t retbuf[20]={0};

QuectelBC95_SendCmd(AT_CGSN);                             //查询设备IMEI号

ret = ExpectReceData_1("+CGSN:", 10, retbuf);		//500ms
		
	if (ret == BC95_OK)
		{		
		 MyStrCPY(BC95_IMEI, retbuf, IMEI_SIZE);		
		//	UART4Send_Data(CGSNbuff,	IMEI_SIZE);   //测试用
	   bc95_device_info.initStep ++;
	   bc95_device_info.errcount =0;
	  }
	else 
	{
		bc95_device_info.err = CGSN_ERR;
		bc95_device_info.errcount++;
	}
}

/**********************************************************
//BC95发送AT+CIMI    查询USIM卡IMSI号
**********************************************************/
void QuectelBC95_CIMI(void )
{
uint8_t ret = 0;
uint8_t retbuf[20]={0};

QuectelBC95_SendCmd(AT_CIMI);                          //查询USIM卡IMSI号

ret = ExpectReceData_1("\r\n", 10, retbuf);
			 	
	if (ret == BC95_OK)
		{

		 MyStrCPY(SIM_IMSI, retbuf, IMSI_SIZE);		
		//	UART4Send_Data(SIM_IMSI,	IMSI_SIZE);   //测试用
	   bc95_device_info.initStep ++;
	   bc95_device_info.errcount =0;
	  }
	else 
	{
		bc95_device_info.err = CIMI_ERR;
		bc95_device_info.errcount++;
	}
}

/**********************************************************
//BC95发送AT+NNMI?    查看下行数据通知
**********************************************************/
void QuectelBC95_NNMI_C(void )
{
uint8_t ret = 0;

QuectelBC95_SendCmd(AT_NNMI_C);                             //查看下行数据通知
Write_SOCK_Data_Buffer(0, AT_NNMI_C, sizeof(AT_NNMI_C) );    //测试用
ret = ExpectReceData("\r\n+NNMI:", 10, &s_stRetData);

	if (ret==BC95_OK && (s_stRetData.ret1==0))        //未开启
		{
		 //设置下行通知
	   bc95_device_info.initStep ++;
	   bc95_device_info.errcount =0;
	  }
	else if(ret==BC95_OK && (s_stRetData.ret1==1))     //开启
		{
	   //跳到查询IP
		 bc95_device_info.initStep  =INITSTEP_NCDP_C;      
	   bc95_device_info.errcount =0;
		}
		
	else 
		{
			bc95_device_info.err = NNMI_C_ERR;
			bc95_device_info.errcount++;
		}
}

/**********************************************************
//BC95发送AT+NNMI=1    设置下行数据通知
**********************************************************/
void QuectelBC95_NNMI(void )
{
uint8_t ret = 0;

QuectelBC95_SendCmd(AT_NNMI);
Write_SOCK_Data_Buffer(0, AT_NNMI, sizeof(AT_NNMI) );    //测试用
	
ret = GetAckData("\r\nOK",10);       //设置下行数据通知


	if (ret == BC95_OK)
		{
			
     //跳到查询
	   bc95_device_info.initStep ++;
	   bc95_device_info.errcount =0;
	  }
	else 
	{
		bc95_device_info.err = NNMI_ERR;
		bc95_device_info.errcount++;
	}
}

/**********************************************************
//BC95发送AT+NCDP?    查询 IOT 平台 IP 地址
**********************************************************/
void QuectelBC95_NCDP_C(void )
{
uint8_t ret = 0;
uint8_t retbuf[30]={0};

QuectelBC95_SendCmd(AT_NCDP_C);                             //查询 IOT 平台 IP 地址

ret = ExpectReceData_1("+NCDP:", 10, retbuf);   

 if (ret == BC95_OK)
		{
		// MyStrCPY(IOT_IPretbuf, retbuf, 19);
			
		 if(MyStrEQ(retbuf, NCDP_HW_17, 19))	   //是正确的IP
			 {
				
			   //跳到查询网络是否附着
				 bc95_device_info.initStep = INITSTEP_CGATT_C;
	       bc95_device_info.errcount =0;			  
			 }
			else 
			 {
				 //跳到设置IP
				 bc95_device_info.initStep ++;
	       bc95_device_info.errcount =0;	    
			 }
	  }
	else 
	{
		bc95_device_info.err = NCDP_C_ERR;
		bc95_device_info.errcount++;
	}
}

/**********************************************************
//BC95发送AT+CFUN=0    设置关闭电话功能
**********************************************************/
void QuectelBC95_CFUN_N(void )
{
uint8_t ret = 0;

QuectelBC95_SendCmd(AT_CFUN_N);                      //关闭电话
	
		Write_SOCK_Data_Buffer(0, AT_CFUN_N, sizeof(AT_CFUN_N) );    //测试用
ret = GetAckData("\r\nOK\r\n",10);                         //500ms

	if (ret == BC95_OK)
		{
	   bc95_device_info.initStep ++;
	   bc95_device_info.errcount =0;
	  }
	else 
	{
		bc95_device_info.err = CFUN_N_ERR;
		bc95_device_info.errcount++;
	}
}

/**********************************************************
//BC95发送AT+NCDP=117.60.157.137,5683    设置接入点IP
**********************************************************/
void QuectelBC95_NCDP(void )
{
uint8_t ret = 0;

QuectelBC95_SendCmd(AT_NCDP);                         //设置接入点IP

		Write_SOCK_Data_Buffer(0, AT_NCDP, sizeof(AT_NCDP) );    //测试用	
	
ret = GetAckData("\r\nOK",10);                     //500ms

	if (ret == BC95_OK)
		{
     //
	   bc95_device_info.initStep ++;
	   bc95_device_info.errcount =0;
	  }
	else 
	{
		bc95_device_info.err = NCDP_ERR;
		bc95_device_info.errcount++;
	}
}

/**********************************************************
//BC95发送AT+CFUN=1    设置开启电话功能
**********************************************************/
void QuectelBC95_CFUN_F(void )
{
uint8_t ret = 0;

QuectelBC95_SendCmd(AT_CFUN_F);                      //开启电话
		Write_SOCK_Data_Buffer(0, AT_CFUN_F, sizeof(AT_CFUN_F) );    //测试用		
	
ret = GetAckData("\r\nOK",10);                         //500ms

	if (ret == BC95_OK)
		{
			
     //
	   bc95_device_info.initStep ++;
	   bc95_device_info.errcount =0;
	  }
	else 
	{
		bc95_device_info.err = CFUN_F_ERR;
		bc95_device_info.errcount++;
	}
}

/**********************************************************
//BC95发送AT+NRB   重启模块
**********************************************************/
void QuectelBC95_NRB(void )
{
uint8_t ret = 0;

QuectelBC95_SendCmd(AT_NRB);                      //重启模块
	
			Write_SOCK_Data_Buffer(0, AT_NRB, sizeof(AT_NRB) );    //测试用	
ret = GetAckData("OK",10);                         //5000ms

	if (ret == BC95_OK)
		{
     //模块会自动重启 跳到开始
	   bc95_device_info.initStep = INITSTEP_START;     
	   bc95_device_info.errcount =0;
	  }
//	else 
//	{
//		
//		bc95_device_info.err = NRB_ERR;
//		bc95_device_info.errcount++;
//	}
}

/**********************************************************
//BC95发送AT+CGATT?    查看模块是否附着网络成功
**********************************************************/
void QuectelBC95_CGATT_C(void )
{
uint8_t ret = 0;

QuectelBC95_SendCmd(AT_CGATT_C);                             //查看模块是否附着网络成功
  
				Write_SOCK_Data_Buffer(0, AT_CGATT_C, sizeof(AT_CGATT_C) );    //测试用	
	
ret = ExpectReceData("\r\n+CGATT:", 5, &s_stRetData );

	if (ret==BC95_OK && (s_stRetData.ret1==1))            //附着成功
		{
			
     //
	   bc95_device_info.initStep ++;
	   bc95_device_info.errcount =0;
	  }
	else  if (ret==BC95_OK && (s_stRetData.ret1==0))    //附着失败
		{
           //重新检查	
			 bc95_device_info.err = CGATT_C_ERR;
			 bc95_device_info.errcount++;
			
		}
	
	else
		{
			 bc95_device_info.err = CGATT_C_ERR;
			 bc95_device_info.errcount++;
		}
}

/**********************************************************
//BC95发送AT+CCLK?    获取网络时间
**********************************************************/
void QuectelBC95_CCLK_C(void )
{
uint8_t ret = 0;
uint8_t retbuf[30]={0};

QuectelBC95_SendCmd(AT_CCLK_C);                             //获取网络时间


Write_SOCK_Data_Buffer(0, AT_CCLK_C, sizeof(AT_CCLK_C) );    //测试用	

ret = ExpectReceData_1("\r\n+CCLK:", 10, retbuf );

 if (ret == BC95_OK)
		{
	   MyStrCPY(BC95_CLOCK, retbuf, 20);
     // MyStrCPY(IOT_IPretbuf, retbuf, 19);
			
		 bc95_device_info.netWork =1;                 //网络连接成功
	   bc95_device_info.initStep = INITSTEP_START;
	   bc95_device_info.errcount =0;

		 Nettime_Tran();          //将网络时间转换成时间戳
			
     BC95_User_Send_DATA(1, 11 , retbuf , 1);
			
     User_Reports_Message_Send(BC95_USER_buff, 7);			
			
	  }
	else 
	{
		bc95_device_info.err = CCLK_C_ERR;
		bc95_device_info.errcount++;
	}
}


///***************************************************************************************************
// * 函 数 名: QuectelBC95_ConnectNet
// * 功能描述: 模块连接网络
// * 函数说明: 无
// * 调用函数: 无
// * 全局变量: 无
// * 输　　入: 无
// * 返　　回: 处理结果
//***************************************************************************************************/

void QuectelBC95_ConnectNet(uint8_t star)
{

	bc95_device_info.err=BC95_OK;
	
	switch(bc95_device_info.initStep)
	{
	  case  INITSTEP_AT:          delay_ms(1000);  QuectelBC95_AT();  	       break;         //测试设备是否在线
	  case  INITSTEP_CGSN:        delay_ms(1000);  QuectelBC95_CGSN();  	     break;	       //查询设备IMEI号
	  case  INITSTEP_CIMI:        delay_ms(1000);  QuectelBC95_CIMI();  	     break;	       //查询USIM卡IMSI号
	  case  INITSTEP_NNMI_C:      delay_ms(1000);  QuectelBC95_NNMI_C();  	   break;	       //查看下行数据通知
	  case  INITSTEP_NNMI:        delay_ms(1000);  QuectelBC95_NNMI();  	     break;	       //设置下行数据通知
	  case  INITSTEP_NCDP_C:      delay_ms(1000);  QuectelBC95_NCDP_C();  	   break;	       //查询 IOT 平台 IP 地址
	  case  INITSTEP_CFUN_N:      delay_ms(1000);  QuectelBC95_CFUN_N();       break;	       //设置关闭电话功能
	  case  INITSTEP_NCDP:        delay_ms(1000);  QuectelBC95_NCDP();         break;	       //设置接入点IP
	  case  INITSTEP_CFUN_F:      delay_ms(1000);  QuectelBC95_CFUN_F();       break;	       //设置开启电话功能
	  case  INITSTEP_NRB:         delay_ms(1000);  QuectelBC95_NRB();          break;	       //重启模块
	  case  INITSTEP_CGATT_C:     delay_ms(1000);  QuectelBC95_CGATT_C();      break;	       //查看模块是否附着网络成功
	  case  INITSTEP_CCLK_C:      delay_ms(1000);  QuectelBC95_CCLK_C();       break;	       //获取网络时间

		default:  break;
	}
	
	if((bc95_device_info.errcount>=10)&&((bc95_device_info.err==CONNECT_ERR)||(bc95_device_info.err==CGSN_ERR)||(bc95_device_info.err==CIMI_ERR)||(bc95_device_info.err==NNMI_C_ERR)))
	{		
    bc95_device_info.netWork =0;                 //连接网络失败
		
		bc95_device_info.initStep =INITSTEP_START;
		
		QuectelBC95_Rest();		    //复位模块	
		
//	  return;
	}
	
	if((bc95_device_info.errcount>=30)&&(bc95_device_info.err==CGATT_C_ERR))
	{		
    bc95_device_info.netWork =0;                 //连接网络失败
		
		bc95_device_info.initStep =INITSTEP_AT;
		
		QuectelBC95_Rest();		    //复位模块	
		
//	  return;
	}
	
	
	
	if((bc95_device_info.err==NRB_ERR)&&(bc95_device_info.errcount>=2))    //连接服务器失败
		{
			bc95_device_info.netWork =0;                 //连接网络失败
			
		// 	bc95_device_info.initStep =INITSTEP_QICLOSE;
		
		  QuectelBC95_Rest();		    //复位模块	
			
		}
	
//	if((bc95_device_info.err==QUERY_SOCKET_ERR)&&(ec20_device_info.errcount>=3))    //关闭sokect失败
//	{
//		bc95_device_info.netWork =0;                 //连接网络失败
//		
//		bc95_device_info.initStep =INITSTEP_START;
//		
//		QuectelBC95_Rest();		    //复位模块	
//	}	
	
}


	//BC95清空缓冲区
void cleanBC95_bcrebuff(void)
{
    uint16_t i=0;
	
    i=	255;
	
	g_u8RxIndexW=0;
	while(i)
	{
	RxDataBuff[--i]=0;

	}
}







	/**********************************************************
//初始化BC95串口通讯缓冲区
**********************************************************/
void InitBC95Combuff(void)
{
	cleanBC95_bcrebuff();
	
	endcount = 0;	//结束标志~	
	
	g_u8RxIndexW=0;
	
	s_u8RxIndexR=0;
	
	USART1_RX_CRLF=0;
}





#endif

