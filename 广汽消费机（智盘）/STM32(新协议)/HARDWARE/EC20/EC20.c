

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

#include "head.h"

#include "EC20.h"
//C库
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define         EC20_OK                 0                               //OK
#define         STRING_ERR              1                               //非预期返回字符串
#define         CONNECT_ERR             2                               //与模块连接错误
#define         QUERY_BAUD_ERR          3                               //波特率错误
#define         CLOSE_SOCKET_ERR        4
#define         CLOSE_CONTEXT_ERR       5
#define         SQ_ERR                  6                               //信号查询错误
#define         REG_ERR                 7                               //网络注册失败
#define         GREG_ERR                8                               //GPRS附着失败
#define         SET_CONTEXT_ERR         9
#define         ACT_CONTEXT_ERR         10
#define         QUERY_ACT_ERR           11
#define         SET_SOCKET_ERR          12
#define         ENTER_DATA_MODE_ERR     13
#define         QUERY_SOCKET_ERR        14
#define         RESET_ERR               15
#define         DEFAULT_ERR             16
#define         QUERY_PIN_ERR           17                              //无SIM卡，或SIM卡有PIN码
#define         BACK_TO_TRAN_ACCESS_MODE_ERR    18
#define         OVER_TIME               19
#define         CPIN_ERR                20
#define         CGREG_ERR               21
#define         QGPSLOC_ERR             22


#define         MC20_RESET_ON            P
#define         MC20_RESET_OFF           P




//#define SMS
#define TCP
//#define TELL

/***************************************************************************************************
//#define       CONTEXT_ID              1                               //Context profile ID
//#define       APN                     *CMNET*                         //接入点名称
***************************************************************************************************/
//static const u8 AT_QICSGP[]   = {"AT+QICSGP=1,*CMNET*\r\n"};            //设置APN


/***************************************************************************************************
//#define       IPADDRESS               *58.214.239.78*                 //IP
//#define       REMOTE_PORT             55555                           //远程Port
//#define       SERVICE_TYPE            *TCP*                           //Service type
***************************************************************************************************/
//static const u8 AT_QIOPEN[]   = {"AT+QIOPEN=*TCP*,*122.228.19.57*,21413\r\n"};  //Context profile

//static const u8 AT_QIOPEN[]   = {"AT+QIOPEN=*TCP*,*59.41.64.85*,22446\r\n"};  //Context profile

//static const u8 AT_QIOPEN[]   = {"AT+QIOPEN=1,0,*TCP*,*120.078.087.149*,23232,0,2\r\n"};  //科坦百度云服务器  

//static const u8 AT_QIOPEN[]   = {"AT+QIOPEN=1,0,*TCP*,*103.46.128.41*,37984,0,2\r\n"};  //科坦花生壳服务器  

static const u8 AT_AT[]       = {"AT\r\n"};                             //连接测试命令

static const u8 AT_ATE0[]     = {"ATE0\r\n"};                           //不需要回显

//static const u8 AT_CSQ[]      = {"AT+CSQ\r\n"};                         //查询信号强度
//static const u8 AT_QRST[]     = {"AT+QRST=1,0\r\n"};                    //模块复位

static const u8 AT_QPOWD[]    = {"AT+QPOWD=0\r\n"};                       //关闭模块

static const u8 AT_CPIN[]     = {"AT+CPIN=?\r\n"};                        //检查SIM卡状态

static const u8 AT_CREG_C[]   = {"AT+CREG?\r\n"};                         //CS服务

static const u8 AT_CGREG_C[]  = {"AT+CGREG?\r\n"};                        //PS服务

static const u8 AT_QICLOSE[]  = {"AT+QICLOSE=0\r\n"};                     //关闭sokect

static const u8 AT_QGPS[]     = {"AT+QGPS=1\r\n"};                        //打开GPS

static const u8 AT_QGPSCFG[]     = {"AT+QGPSCFG=*outport*,*uartdebug*\r\n"};    //选择输出方式                    //打开GPS

static const u8 AT_QGPSLOC[]     = {"AT+QGPSLOC=0\r\n"};                    //查看GPS信息

static const u8 AT_QGPSEND[]     = {"AT+QGPSEND\r\n"};                    //关闭GPS

static const uint8_t AT_CGSN[]       = {"AT+CGSN\r\n"};                          //查询设备IMEI号

static const uint8_t AT_CIMI[]       = {"AT+CIMI\r\n"};                            //查询USIM卡IMSI号

 u8 AT_QIOPEN_IP[]   = {"AT+QIOPEN=1,0,*TCP*,*120.078.087.149*,23232,0,2\r\n"};  //自定义服务器IP

 
 
struct retstruct
{
    u8 ret1;
    u8 ret2;
}s_stRetData;

u16 g_u16OverTimeCnt=0;                               //超时倒计时计数器，每100毫秒自减1

u16 AT_InterOverTimeCnt=0;                             //AT指令间隔超时倒计时计数器，每100毫秒自减1

u8 RxDataBuff[RX_BUFF_LEN];                         //中断接收数组

       u16  g_u8RxIndexW=0;                               //中断接收数组写指针
static u16  s_u8RxIndexR=0;                             //中断接收数组读指针


uint8_t   EC20GPSBUF[500] = {0};        //GPS接收数据缓冲区

uint16_t  EC20GPSLEN = 0;               //接收到的GPS数据长度
 
uint8_t  gl_imei[20]={0};
uint8_t  gl_imsi[20]={0};

//初始化PA8为输出口.并使能这两个口的时钟		    

void EC20_REST_Init(void)
{
 
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	 //使能PA端口时钟
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;				  //GSM_POWER-->PA.8 端口配置 开关机
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 	//推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//IO口速度为50MHz
 GPIO_Init(GPIOA, &GPIO_InitStructure);					    //根据设定参数初始化GPIOA.8
 GPIO_SetBits(GPIOA,GPIO_Pin_8);						        //PA.8 输出高
		
}
 


void EC20_SendString(uint8_t *ec20combuff ,uint16_t len)
{
	uint16_t t;
	for(t=0;t<len;t++)
	 {
		  USART_SendData(EC20_UART, ec20combuff[t]);//向串口1发送数据
			
			while(USART_GetFlagStatus(EC20_UART,USART_FLAG_TC)!=SET);//等待发送结束
	
   }
}

void EC20_SendByte(uint8_t combuff2)
{
  //    delay_us(500);
		USART_SendData(EC20_UART, combuff2);//向串口1发送数据
	
		while(USART_GetFlagStatus(EC20_UART,USART_FLAG_TC)!=SET);//等待发送结束
}


/***************************************************************************************************
 * 函 数 名: QuectelEC20_Rest
 * 功能描述: EC20 硬件复位
 * 函数说明: 
 * 调用函数: 无
 * 全局变量: 无
 * 输　　入: 无
 * 返　　回: 无
***************************************************************************************************/
void QuectelEC20_Rest(void)
{
	
	ec20_device_info.netWork =0;
	
	EC20REST =0;         //复位引脚拉低 500ms
	
	delay_ms(500);
	delay_ms(500);
	
	EC20REST =1;
	
	InitEC20Combuff();
}

/***************************************************************************************************
 * 函 数 名: QuectelEC20_SendCmd
 * 功能描述: EC20底层发送命令
 * 函数说明: 
 * 调用函数: 无
 * 全局变量:
 * 输　　入: *string 需要发送的字符串指针
 * 返　　回: 无
***************************************************************************************************/
static void QuectelEC20_SendCmd(const u8 *string)
{
    u8 i = 0;
    
    while (string[i] != 0)
    {
        if (string[i] == '*')
        {
            EC20_SendByte('"');
        }
        else
        {
            EC20_SendByte(string[i]);
        }
        i++;
    }
		kt_beat_info.count =0;
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
static u8 GetAckData(char *string, u16 overtime)
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
                return EC20_OK;
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
static u8 ExpectReceData(char *string, u16 overtime, struct retstruct* ret)
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
    return EC20_OK;
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
 uint8_t ExpectReceData_1( char *string, uint16_t overtime, uint8_t *ret)
{
    uint16_t  j = 0, k = 0;
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
    j = 0;                  //
    while (1)
    {
        if (s_u8RxIndexR != g_u8RxIndexW)
        {
			
						ret[k] = RxDataBuff[s_u8RxIndexR];
             k++;     
             s_u8RxIndexR++;			

						if (RxDataBuff[s_u8RxIndexR-1] == '\r')//&&(RxDataBuff[s_u8RxIndexR-1] == 'O')&&(RxDataBuff[s_u8RxIndexR] == 'K'))						
							{
  							  s_u8RxIndexR = 0;	
                  EC20GPSLEN	=k;						
								  k=0;
								return EC20_OK; 			
							}		
        }				
				  /* 超时，5000ms */
		      if(g_u16OverTimeCnt == 0) 
            {                
                return OVER_TIME;
            }	
  //  return BC95_OK;						
    }

		    
}








/***************************************************************************************************
 * 函 数 名: QuectelM26_PowerDown
 * 功能描述: 模块复掉电
 * 函数说明: 无
 * 调用函数: 无
 * 全局变量: 无
 * 输　　入: 无
 * 返　　回: 处理结果
***************************************************************************************************/
u8 QuectelEC20_PowerDown(void)
{
    u8 ret;
    QuectelEC20_SendCmd(AT_QPOWD);
    ret = GetAckData("\r\nOK\r\n", 60);
    if (ret != EC20_OK)
        return RESET_ERR;
    else
        return EC20_OK;
}




	//EC20清空缓冲区
void cleanEC20_bcrebuff(void)
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
//初始化EC20串口通讯缓冲区
**********************************************************/
void InitEC20Combuff(void)
{
//	cleanEC20_bcrebuff();
	
	memset(RxDataBuff, 0, sizeof(RxDataBuff));   //清0
	
	endcount_4g = 0;	//结束标志~	
	
	g_u8RxIndexW=0;
	
	s_u8RxIndexR=0;
	
	USART1_RX_CRLF=0;
}



/**********************************************************
//EC20发送AT    测试设备是否在线
**********************************************************/
void QuectelEC20_AT(void )
{
uint8_t ret = 0;
	
	if(AT_InterOverTimeCnt)
		{
		return;
		}
	QuectelEC20_SendCmd(AT_AT);
	ret = GetAckData("OK\r\n",5);                         //有回送和不回送两种可能	
	if (ret == EC20_OK)
		{
	   ec20_device_info.initStep =INITSTEP_ATE0;
	   ec20_device_info.errcount =0;
	  }
	else 
	{
		ec20_device_info.err = CONNECT_ERR;
		ec20_device_info.errcount++;
	}
	
	 AT_InterOverTimeCnt=10;
}

/**********************************************************
//EC20发送ATE0    关闭回显
**********************************************************/
void QuectelEC20_ATE0(void )
{
  uint8_t ret = 0;
	
	if(AT_InterOverTimeCnt)
	{
	return;
	}
	
	QuectelEC20_SendCmd(AT_ATE0);
	ret = GetAckData("OK\r\n",5);                         //设置为不回送模式
	
	if (ret == EC20_OK)
		{
	   ec20_device_info.initStep = INITSTEP_CPIN;
	   ec20_device_info.errcount =0;
	  }
	else 
	{
		ec20_device_info.err = CONNECT_ERR;
		ec20_device_info.errcount++;
	}
	
	AT_InterOverTimeCnt=10;
}

/**********************************************************
//EC20发送AT+CPIN=?    检查SIM卡状态
**********************************************************/
void QuectelEC20_CPIN(void )
{
  uint8_t ret = 0;
	
	if(AT_InterOverTimeCnt)
	{
	return;
	}
	
	QuectelEC20_SendCmd(AT_CPIN);
	ret = GetAckData("OK\r\n",5);                         //检查SIM卡状态
	
	if (ret == EC20_OK)
		{
	   ec20_device_info.initStep = INITSTEP_IMEI ;
	   ec20_device_info.errcount =0;
	  }
	else 
	{
		ec20_device_info.err = CPIN_ERR;
		ec20_device_info.errcount++;
	}
	
	AT_InterOverTimeCnt=10;
}


/**********************************************************
//MC20发送AT+CGSN=1    查询设备IMEI号
**********************************************************/
void QuectelEC20_CGSN(void )
{
uint8_t ret = 0;
uint8_t retbuf[20]={0};

if(AT_InterOverTimeCnt)
{
return;
}

QuectelEC20_SendCmd(AT_CGSN);                             //查询设备IMEI号

ret = ExpectReceData_1("\r\n", 10, retbuf);		//
		
	if (ret == EC20_OK)
		{		
		 memcpy(gl_imei, retbuf, 15);		
		
	   ec20_device_info.initStep = INITSTEP_IMSI;
	   ec20_device_info.errcount =0;
	  }
	else 
	{
		ec20_device_info.err = CONNECT_ERR;
		ec20_device_info.errcount++;
	}
	AT_InterOverTimeCnt=5;
}



/*********************************************************
//BC95发送AT+CIMI    查询USIM卡IMSI号
**********************************************************/
void QuectelEC20_CIMI(void )
{
uint8_t ret = 0;
uint8_t retbuf[20]={0};

if(AT_InterOverTimeCnt)
{
return;
}


QuectelEC20_SendCmd(AT_CIMI);                          //查询USIM卡IMSI号

ret = ExpectReceData_1("\r\n", 10, retbuf);
			 	
	if (ret == EC20_OK)
		{

		 memcpy(gl_imsi, retbuf, 15);		
			
	   ec20_device_info.initStep = INITSTEP_CREG;
	   ec20_device_info.errcount =0;
	  }
	else 
	{
		ec20_device_info.err = CONNECT_ERR;
		ec20_device_info.errcount++;
	}
	AT_InterOverTimeCnt=5;
}



/**********************************************************
//EC20发送AT+CREG?    CS服务
**********************************************************/
void QuectelEC20_CREG(void )
{
  uint8_t ret = 0;
	
	if(AT_InterOverTimeCnt)
	{
	return;
	}
	
  QuectelEC20_SendCmd(AT_CREG_C);                             //CS服务
	ret = ExpectReceData("+CREG: ", 5, &s_stRetData);
	
	if (ret==EC20_OK && (s_stRetData.ret1==0) && (s_stRetData.ret2==1||s_stRetData.ret2==5))
		{
		 ec20_device_info.initStep =INITSTEP_CGREG;
		 ec20_device_info.errcount =0;
		}
	else 
	{
		ec20_device_info.err = REG_ERR;                    //模块未注册到CS域名服务
		ec20_device_info.errcount++;
	}
	
	AT_InterOverTimeCnt=10;
}

/**********************************************************
//EC20发送AT+CGREG?    PS服务
**********************************************************/
void QuectelEC20_CGREG(void )
{
  uint8_t ret = 0;
	
	if(AT_InterOverTimeCnt)
	{
	return;
	}

	QuectelEC20_SendCmd(AT_CGREG_C);                          //PS服务
  ret = ExpectReceData("+CGREG: ", 5, &s_stRetData);
	
  if (ret==EC20_OK && (s_stRetData.ret1==0) && (s_stRetData.ret2==1||s_stRetData.ret2==5))
	{
		
#ifdef  WITH_EC20GPS_FUNC   //GPS

		ec20_device_info.initStep =INITSTEP_QGPS;
#else
		ec20_device_info.initStep =INITSTEP_QIOPEN;
#endif		
		
		
	 ec20_device_info.errcount =0;
	}
	 
	else 
	{
		ec20_device_info.err = CGREG_ERR;                    //模块未使用USIM/LTE网络注册到PS域名服务器
		ec20_device_info.errcount++;
	}
	
	AT_InterOverTimeCnt=10;
}

/**********************************************************
//EC20发送AT+QGPS=1    打开GPS
**********************************************************/
void QuectelEC20_QGPS(void )
{
  uint8_t ret = 0;
	
	if(AT_InterOverTimeCnt)
	{
	return;
	}

	QuectelEC20_SendCmd(AT_QGPS);                          //打开GPS
  ret = GetAckData("OK\r\n",5);                         
	
  if (ret==EC20_OK )
	{
	 ec20_device_info.initStep = INITSTEP_QGPSCFG ;
	 ec20_device_info.errcount =0;
	}
	 
	else 
	{
		ec20_device_info.err = CGREG_ERR;                    //
		ec20_device_info.errcount++;
	}
	
	AT_InterOverTimeCnt=10;
}

/**********************************************************
//EC20发送AT+QGPSCFG="outport","uartdebug"    //选择输出方式
**********************************************************/
void QuectelEC20_QGPSCFG(void )
{
  uint8_t ret = 0;
	
	if(AT_InterOverTimeCnt)
	{
	return;
	}

	QuectelEC20_SendCmd(AT_QGPSCFG);                          //选择输出方式
  ret = GetAckData("OK\r\n",5);                         
	
  if (ret==EC20_OK )
	{
	 ec20_device_info.initStep = INITSTEP_QGPSLOC;
	 ec20_device_info.errcount =0;
	}
	 
	else 
	{
		ec20_device_info.err = CGREG_ERR;                    //
		ec20_device_info.errcount++;
	}
	
	AT_InterOverTimeCnt=10;
}

/**********************************************************
//EC20发送AT+QGPSLOC=0    //查看GPS信息
**********************************************************/
void QuectelEC20_QGPSLOC(void )
{
  uint8_t ret = 0;

	if(AT_InterOverTimeCnt)
	{
	return;
	}

	QuectelEC20_SendCmd(AT_QGPSLOC);                 //查看GPS信息
    ret = GetAckData("OK",10);                          
	
  if (ret==EC20_OK )
	{
	 memcpy ( EC20GPSBUF, RxDataBuff, g_u8RxIndexW );    //拷贝串口接收的数据
		
	 EC20GPSLEN = g_u8RxIndexW ;
	 ec20_device_info.initStep = INITSTEP_QGPSEND;
	 ec20_device_info.errcount =0;
	}
	 
	else 
	{
		ec20_device_info.err = QGPSLOC_ERR;                    //
		ec20_device_info.errcount++;
	}
	
	AT_InterOverTimeCnt=30;
}


/**********************************************************
//EC20发送AT+QGPSEND     //关闭GPS
**********************************************************/
void QuectelEC20_QGPSEND(void )
{
  uint8_t ret = 0;
	
	if(AT_InterOverTimeCnt)
	{
	return;
	}

	QuectelEC20_SendCmd(AT_QGPSEND);                          //选择输出方式
  ret = GetAckData("OK\r\n",5);                         
	
  if (ret==EC20_OK )
	{
	 ec20_device_info.initStep = INITSTEP_QIOPEN;
	 ec20_device_info.errcount =0;
	}
	 
	else 
	{
		ec20_device_info.err = CGREG_ERR;                    //
		ec20_device_info.errcount++;
	}
	
	AT_InterOverTimeCnt=10;
}



/**********************************************************
//EC20发送AT+QIOPEN=1,0,*TCP*,*120.78.87.149*,23232,0,2    连接服务器
**********************************************************/
void QuectelEC20_QIOPEN(void )
{
  uint8_t ret = 0;

	if(AT_InterOverTimeCnt)
	{
	return;
	}
	
  QuectelEC20_SendCmd(AT_QIOPEN_IP);    //启动Socket服务，连接服务器 透传模式
		
  ret = GetAckData("CONNECT", 10);
	
	if (ret == EC20_OK)
	{
//	 Heartbeat_Send(4);                     //发送心跳
		
		Send_Power_Signal();     //发送开机信号
		
		
#ifdef  WITH_EC20GPS_FUNC   //GPS
		delay_ms(1000);
		AutoUP_GPS_Information();       //发送GPS信息
#endif		

		
	 ec20_device_info.netWork =1;
	 ec20_device_info.initStep = INITSTEP_START;
	 ec20_device_info.errcount =0;
		
	 Standbytime =   0;   //0秒后进入主界面
		
	 Show_Refresh_coun =0;	
	}
	 
	else 
	{
		ec20_device_info.err = SET_SOCKET_ERR;                    //连接服务器失败
		
		ec20_device_info.errcount++;
	}
	
	AT_InterOverTimeCnt=10;
}



/**********************************************************
//EC20发送AT+QICLOSE=0    关闭sokect
**********************************************************/
void QuectelEC20_QICLOSE(void )
{
  uint8_t ret = 0;
	
	if(AT_InterOverTimeCnt)
	{
	return;
	}
	
  QuectelEC20_SendCmd(AT_QICLOSE);                //关闭sokect	
  ret = GetAckData("OK\r\n",5);                   //
		 
	if (ret == EC20_OK)
	{
		
		
	 ec20_device_info.initStep = INITSTEP_AT;
	 ec20_device_info.errcount =0;
	}
	
	else 
	{
		ec20_device_info.err = QUERY_SOCKET_ERR;                    //关闭sokect失败
		ec20_device_info.errcount ++ ;
	}
	
	AT_InterOverTimeCnt=10;
}


void QuectelEC20_Network_Init(uint8_t star)
{

	ec20_device_info.err=EC20_OK;
	
	switch(ec20_device_info.initStep)
	{
	  case  INITSTEP_AT:            QuectelEC20_AT();  	          break;         //at
	  case  INITSTEP_ATE0:          QuectelEC20_ATE0();  	        break;	       //关回显
	  case  INITSTEP_CPIN:          QuectelEC20_CPIN();  	        break;	       //检查SIM卡状态	
	  case  INITSTEP_CREG:          QuectelEC20_CREG();  	        break;	       //CS服务
	  case  INITSTEP_CGREG:         QuectelEC20_CGREG();  	      break;	       //PS服务		
	  case  INITSTEP_QIOPEN:        QuectelEC20_QIOPEN();         break;	       //连接服务器
	  case  INITSTEP_QICLOSE:       QuectelEC20_QICLOSE();        break;	       //关闭sokect
	  case  INITSTEP_QGPS:          QuectelEC20_QGPS();           break;	       //打开GPS		
	  case  INITSTEP_QGPSCFG:       QuectelEC20_QGPSCFG();        break;	       //选择输出方式	
	  case  INITSTEP_QGPSLOC:       QuectelEC20_QGPSLOC();        break;	       //查看GPS信息		
	  case  INITSTEP_QGPSEND:       QuectelEC20_QGPSEND();        break;	       //关闭GPS				
	  case  INITSTEP_IMEI:          QuectelEC20_CGSN();           break;	       //查询IMEI号
	  case  INITSTEP_IMSI:          QuectelEC20_CIMI();           break;	       //查询IMSI号	
		
		default:  break;
	}
	
	if((ec20_device_info.errcount>=20)&&((ec20_device_info.err==CONNECT_ERR)||(ec20_device_info.err==CPIN_ERR)||(ec20_device_info.err==REG_ERR)||(ec20_device_info.err==CGREG_ERR)))
	{			
		ec20_device_info.initStep =INITSTEP_START;
		
		QuectelEC20_Rest();		    //复位模块	
		ec20_device_info.netWork =0;
//	  return;
	}
	
	if((ec20_device_info.err==SET_SOCKET_ERR)&&(ec20_device_info.errcount>=2))    //连接服务器失败
		{
		 	ec20_device_info.initStep =INITSTEP_QICLOSE;
		
	//	  QuectelEC20_Rest();		    //复位模块	
		 ec20_device_info.netWork =0;	
		}
		
	if((ec20_device_info.err==QGPSLOC_ERR)&&(ec20_device_info.errcount>=15))    //连接服务器失败
		{
		 	ec20_device_info.initStep =INITSTEP_QIOPEN;
		
	//	  QuectelEC20_Rest();		    //复位模块	
		 ec20_device_info.errcount =0;	
		}		
	
	if((ec20_device_info.err==QUERY_SOCKET_ERR)&&(ec20_device_info.errcount>=2))    //关闭sokect失败
	{
		ec20_device_info.initStep =INITSTEP_START;
		
		QuectelEC20_Rest();		    //复位模块

		ec20_device_info.netWork =0;
	}	
	
}




void   ec20sufatest(void )
{

		
	//inet_addr_(addr,ip );
		
	Write_SOCK_Data_Buffer(0, AT_QIOPEN_IP, sizeof(AT_QIOPEN_IP) );
	
}












