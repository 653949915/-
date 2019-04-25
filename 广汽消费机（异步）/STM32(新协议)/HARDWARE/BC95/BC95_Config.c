#include "head.h"

#include "BC95_Config.h"
//C库
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>   
uint8_t  CMDMessage_Dtag[2];                                           //消息序号，自动累加，去重

KT_DEVICE_INFO   bc95_device_info = {0, 0, 0, 0, 0, 0, 0, 0, 0};

#ifdef   NB_BC95

uint8_t  BC95REffective_data[512]={0};           //NB接收的有效数据


uint8_t  BC95_Send_buff[1024]={0X41, 0X54, 0X2B, 0X4E, 0X4D, 0X47, 0X53, 0X3D,0x30, 0X36, 0X35, 0X2C};      //BC95最终发送的数据

uint8_t  BC95_USER_buff[254]={0};      //BC95用户数据

uint8_t  BatteryLevel[1]={0X50};                            //电池电量，Byte型，取值0~100

uint8_t  SignalStrength[4]={0XFF, 0XFF, 0XFF, 0XCD};        //信号强度，Int型

//uint8_t  BC95_IMEI[15]={0};                                 //模组ID号。String(ISO-8859-1)类型

//uint8_t  SIM_IMSI[15]={0};                                  //sim卡号。String(ISO-8859-1)类型

uint8_t  Internet_Time_Stamp[8]={0};                        //时间戳，Long型。设备当前时间，为毫秒数
//uint8_t  Networktimebuf[20];                                //调整后的网络时间


BC95_USER_DATATURE   bc95_cmduser_data ={ {0}, 0, 0 ,0};

char *getnb_rebuff() 
	{
			return ( char *)&RxDataBuff;
	}

char *redata_nb;

	
//处理4G通讯

void ProcessNB_Commu(void)
	{
		char *dataPtr = NULL;
		char numBuf[10];
		int num = 0;
		int numer = 0;
		
//		u8   DEF_MACHNO[] = {0X51,0X05,0X07,0X01};
//		u8	 ch;
			
		if(USART1_RX_CRLF)           //在收到 \r\n
		{
			redata_nb = getnb_rebuff(); 
			
			if(strstr(redata_nb,"Neul"))	               //检测到开机信息
			{
				bc95_device_info.initStep = INITSTEP_AT;
				
				Beep(2, SHORT_BEEP); 	

        InitBC95Combuff();				
				return;
			}			
			if(strstr(redata_nb,"NO CARRIER"))	         //检测到服务器断线
			{
		//		ec20_device_info.initStep = INITSTEP_QICLOSE;
				
		//		QuectelEC20_Network_Init(2);       //重启
		//		Beep(3, SHORT_BEEP); 		
				return;
			}		
			
			if(strstr(redata_nb,"+NNMI:"))	               //收到平台发送来的数据
			{
			  Beep(1, SHORT_BEEP);
				
				 dataPtr = strchr(redata_nb, ':');							//搜索'}'
	
					if(dataPtr != NULL)									//如果找到了
					{
						 dataPtr++;
						 while(*dataPtr >= '0' && *dataPtr <= '9')		//判断是否是下发的命令控制数据
							{
								numBuf[num++] = *dataPtr++;
							}
							
							numer = atoi((const char *)numBuf);				//转为数值形式
							
							dataPtr = dataPtr + 1;
							
							memset(BC95REffective_data ,0,numer*2+1);         //清0
							
							memcpy(BC95REffective_data ,dataPtr ,numer*2);
							
							RS485_Send_Data(BC95REffective_data,	numer*2);			
							
				//			Write_SOCK_Data_Buffer(0, BC95REffective_data, numer*2 );	
							
							
			     }
				
				
				InitBC95Combuff();	
			
			}
		}
    
		else     //非AT配置模式
		{

		}
	}

	
	
		/***************************************************************************************************
 * 函 数 名: User_Control_Command_Send
 * 功能描述: 用户控制命令响应
 * 函数说明: 无
 * 调用函数: 无
 * 全局变量: 无
 * 输　　入:   Code_type             代码类型 （设备指令）
	            TLV_type               参数类型 （传感器）
	            data                   数据内容
	            len                    数据内容长度
	
	
 * 返　　回: 处理结果
***************************************************************************************************/

void BC95_User_Send_DATA(uint8_t Code_type, uint8_t TLV_type , uint8_t  *data , uint16_t len)
{

	union TwoByte  Length;

	BC95_USER_buff[0]   = Code_type  ;        //代码类型
	
	Length.i = len + 3;                                  //长度
	turn_2_data(BC95_USER_buff +1 ,Length.c);  //拷贝数据长度
	
	BC95_USER_buff[3] = TLV_type  ;              //参数类型
	
	Length.i = len ;                                       //长度
	turn_2_data(BC95_USER_buff +4 ,Length.c);                      //拷贝数据长度

  MyStrCPY(BC95_USER_buff +6, data, len);         //拷贝数据内容

}
	


		
/***************************************************************************************************
 * 函 数 名: User_Reports_Message_Send
 * 功能描述: 用户上报消息发送
 * 函数说明: 无
 * 调用函数: 无
 * 全局变量: 无
 * 输　　入: 无
 * 返　　回: 处理结果
***************************************************************************************************/

void User_Reports_Message_Send(uint8_t *data, uint16_t len)
	{
		
			union TwoByte  Length;                             //字段序号4~11部分的总长度
			static	union TwoByte  Dtag;                               //消息序号，自动累加，去重
			
	//		Power_ADC();     //读取电池电量
				
			uint8_t Reports_Message_data[255]={0};		              //发送的数据
				
			uint8_t  Version[1] = {0};                                  //版本号                          		
			uint8_t	 Message_Type[1]={0XF0};                            //消息类型
			uint8_t  Message_Length[2];                                 //字段序号4~11部分的总长度 
			uint8_t  Message_Dtag[2];                                   //消息序号，自动累加，去重
			uint8_t  Checksumbuf[1]={0};                                //和校验
			uint8_t  New_linebuf[2]={0X0D,0X0A};                         //回车换行				
			
			Version[0]	=	 0xF1;			                       	               //版本号
			Length.i=46+len;				                                         //数据长度（消息类型后面的数据长度）
			Dtag.i++;		                                                     //流水号+1
	
	   turn_2_data(Message_Length ,Length.c);                            //字节调转  消息长度
	   MyStrCPY(Message_Dtag ,Dtag.c,2);                                 //字节调转   消息序号
	
     MyStrCPY(Reports_Message_data,    Version, 1);                   //版本号
				 
		 MyStrCPY(Reports_Message_data+1,  Message_Type, 1);              //消息类型
				 
		 MyStrCPY(Reports_Message_data+2,  Message_Length, 2);	          //字段序号4~11部分的总长度
				 
		 MyStrCPY(Reports_Message_data+4,  Message_Dtag, 2);		          //消息序号，自动累加，去重

     MyStrCPY(Reports_Message_data+6,  BatteryLevel, 1);	            //电池电量，Byte型，取值0~100

		 MyStrCPY(Reports_Message_data+7,  SignalStrength, 4);	          //信号强度，Int型

     MyStrCPY(Reports_Message_data+11, BC95_IMEI, 15);	               //模组ID号。String(ISO-8859-1)类型

     MyStrCPY(Reports_Message_data+26, SIM_IMSI, 15);					         //sim卡号。String(ISO-8859-1)类型

     MyStrCPY(Reports_Message_data+41, Internet_Time_Stamp, 8);				 //时间戳，Long型。设备当前时间，为毫秒数
		 		 
		 MyStrCPY(Reports_Message_data+49, data, len);					           //用户数据
		
     Checksumbuf[0] = GetSum(Reports_Message_data,Length.i+3);         //和校验计算

		 MyStrCPY(Reports_Message_data+49+len, Checksumbuf, 1);					    //和校验
						 
	   HexToStr(BC95_Send_buff+12,  Reports_Message_data, Length.i+4);    //转成字符串
			
     MyStrCPY(BC95_Send_buff+(Length.i+4)*2+12, New_linebuf, 2);					    //回车

     DecTostr_bc95(BC95_Send_buff+8, Length.i+4);                            //数量
               
	  // HAL_UART_Transmit(&huart1, BC95_Send_buff, (Length.i+4)*2+14, 1000);//发送数据	
	
     BC95_SendString(BC95_Send_buff ,(Length.i+4)*2+14)   ;               //发送数据
	}


	
	/***************************************************************************************************
 * 函 数 名: User_Control_Command_Send
 * 功能描述: 用户控制命令响应
 * 函数说明: 无
 * 调用函数: 无
 * 全局变量: 无
 * 输　　入: data    数据内容
            len      数据长度
 * 返　　回: 处理结果
***************************************************************************************************/

void User_Control_Command_Send(uint8_t *data, uint16_t len)
	{		 

    uint8_t Control_Command_data[255]={0};		                            //发送的数据
		
		 union TwoByte  Length;                                              //字段序号4~11部分的总长度
	   union TwoByte  Dtag;                                                //消息序号，自动累加，去重			
		 uint8_t  Version[1] = {0};                                          //版本号                          		
		 uint8_t	Message_Type[1]={0XF3};                                    //消息类型
		 uint8_t  Message_Length[2];                                         //字段序号4~11部分的总长度 
		 uint8_t  Message_Dtag[2];                                           //消息序号，自动累加，去重
		 uint8_t  Checksumbuf[1]={0};                                        //和校验
		 uint8_t  New_linebuf[2]={0X0D,0X0A};                                //回车换行
//		 uint8_t  datalenbuff[2]={0X00};                                //回车换行		
		 
	   Version[0]	=	 0x01;				                                    //版本赋值
	   Length.i=3+len;				                                        //计算数据长度(消息类型后面的数据长度)
	//   Dtag.i++;		                                                //消息序号加1		 
		 MyStrCPY(Message_Dtag, CMDMessage_Dtag, 2);                    //消息序号
		 
	   turn_2_data(Message_Length ,Length.c);                          //字节调转  消息长度(消息类型后面的数据长度)
		 
	   MyStrCPY(Message_Dtag ,Dtag.c,2);                               //拷贝消息序号 
			
     MyStrCPY(Control_Command_data,    Version, 1);                  //版本号
				 
		 MyStrCPY(Control_Command_data+1,  Message_Type, 1);             //消息类型
				 
		 MyStrCPY(Control_Command_data+2,  Message_Length, 2);	         //字段序号4~11部分的总长度
				 
		 MyStrCPY(Control_Command_data+4,  CMDMessage_Dtag, 2);		         //消息序号，自动累加，去重
		 		 
		 MyStrCPY(Control_Command_data+6, data, len);					           //用户数据
		
     Checksumbuf[0] = GetSum(Control_Command_data,Length.i+3);       //和校验计算

		 MyStrCPY(Control_Command_data+6+len, Checksumbuf, 1);					 //和校验
						 
	   HexToStr(BC95_Send_buff+12,Control_Command_data, Length.i+4);   //转成字符串
			
     MyStrCPY(BC95_Send_buff+(Length.i+4)*2+12, New_linebuf, 2);		 //回车

     DecTostr_bc95(BC95_Send_buff+8, Length.i+4);                            //数量(总长) 
	
	//   HAL_UART_Transmit(&huart1, BC95_Send_buff, (Length.i+4)*2+14, 500);//发送数据	
	
	   BC95_SendString(BC95_Send_buff ,(Length.i+4)*2+14)   ;        //发送数据	
	
	}
	

//==========================================================
//	函数名称：	EDP_NewBuffer
//
//	函数功能：	申请内存
//
//	入口参数：	edpPacket：包结构体
//				size：大小
//
//	返回参数：	无
//
//	说明：		1.可使用动态分配来分配内存
//				2.可使用局部或全局数组来指定内存
//==========================================================
void EDP_NewBuffer(EDP_PACKET_STRUCTURE *edpPacket, uint32_t size)
{
	
	uint32_t i = 0;

	if(edpPacket->_data == NULL)
	{
		edpPacket->_memFlag = MEM_FLAG_ALLOC;
		
		edpPacket->_data = (uint8_t *)EDP_MallocBuffer(size);
		if(edpPacket->_data != NULL)
		{
			edpPacket->_len = 0;
			
			edpPacket->_size = size;

			for(; i < edpPacket->_size; i++)
				edpPacket->_data[i] = 0;
		}
	}
	else
	{
		edpPacket->_memFlag = MEM_FLAG_STATIC;
		
		for(; i < edpPacket->_size; i++)
			edpPacket->_data[i] = 0;
		
		edpPacket->_len = 0;
		
		if(edpPacket->_size < size)
			edpPacket->_data = NULL;
	}

}

//==========================================================
//	函数名称：	EDP_DeleteBuffer
//
//	函数功能：	释放数据内存
//
//	入口参数：	edpPacket：包结构体
//
//	返回参数：	无
//
//	说明：		当使用的局部或全局数组时不释放内存
//==========================================================
void EDP_DeleteBuffer(EDP_PACKET_STRUCTURE *edpPacket)
{

	if(edpPacket->_memFlag == MEM_FLAG_ALLOC)
		EDP_FreeBuffer(edpPacket->_data);
	
	edpPacket->_data = NULL;
	edpPacket->_len = 0;
	edpPacket->_size = 0;
	edpPacket->_memFlag = MEM_FLAG_NULL;

}



//==========================================================
//	函数名称：	EDP_PacketCmdResp
//
//	函数功能：	命令回复组包
//
//	入口参数：	cmdid：命令的cmdid(随命令下发)
//				    cmdid_len：cmdid长度
//				    req：命令
//				    req_len：命令长度
//				    edpPacket：包指针
//
//	返回参数：	0-成功		1-失败
//
//	说明：		
//==========================================================
_Bool EDP_PacketCmdResp(const int8_t *cmdid, uint16_t cmdid_len, const int8_t *resp, uint32_t resp_len, EDP_PACKET_STRUCTURE *edpPacket)
{
	
	uint32_t remain_len = cmdid_len + resp_len + (resp_len ? 6 : 2);
	
	EDP_NewBuffer(edpPacket, remain_len + 5);
	if(edpPacket->_data == NULL)
		return 1;
	
	//Byte0：CMDRESP消息------------------------------------------------------------
	edpPacket->_data[edpPacket->_len++] = CMDRESP;
	
	//写入剩余长度------------------------------------------------------------------
	//edpPacket->_len += WriteRemainlen(edpPacket->_data, remain_len, edpPacket->_len);
	
	//写入cmdid长度------------------------------------------------------------------
	edpPacket->_data[edpPacket->_len++] = cmdid_len >> 8;
	edpPacket->_data[edpPacket->_len++] = cmdid_len & 0x00FF;
	
	//写入cmdid----------------------------------------------------------------------
	memcpy((int8_t *)edpPacket->_data + edpPacket->_len, cmdid, cmdid_len);
	edpPacket->_len += cmdid_len;
	
	if(resp_len)
	{
		//写入req长度-----------------------------------------------------------------
		edpPacket->_data[edpPacket->_len++] = (int8_t)(resp_len >> 24);
		edpPacket->_data[edpPacket->_len++] = (int8_t)(resp_len >> 16);
		edpPacket->_data[edpPacket->_len++] = (int8_t)(resp_len >> 8);
		edpPacket->_data[edpPacket->_len++] = (int8_t)(resp_len & 0x00FF);
		
		//写入req---------------------------------------------------------------------
		memcpy((int8_t *)edpPacket->_data + edpPacket->_len, resp, resp_len);
		
		edpPacket->_len += resp_len;
	}

	return 0;
}




long GetTick(char *str_time)  
{  
    struct tm stm;  
    int iY, iM, iD, iH, iMin, iS;  
  
    memset(&stm,0,sizeof(stm));  
  
    iY = atoi(str_time);  
    iM = atoi(str_time+5);  
    iD = atoi(str_time+8);  
    iH = atoi(str_time+11);  
    iMin = atoi(str_time+14);  
    iS = atoi(str_time+17);  
  
    stm.tm_year=iY-1900;  
    stm.tm_mon=iM-1;  
    stm.tm_mday=iD;  
    stm.tm_hour=iH;  
    stm.tm_min=iMin;  
    stm.tm_sec=iS;  
  
    /*printf("%d-%0d-%0d %0d:%0d:%0d\n", iY, iM, iD, iH, iMin, iS);*/  
  
    return mktime(&stm);  
} 

void Nettime_Tran(void)
{
  uint8_t i;
	uint8_t test1[4]={0};
	uint8_t test2[4]={0X00,0X00};
	uint8_t test3=0;
  long NETtimel=0;
//	uint64_t NETtimel1=0;
	union EightByte ic8; 
	
char Wtimebuf[30]={0X32, 0X30, 0X31, 0X37, 0X2D, 0X31, 0X32, 0X2D, 0X30, 0X35, 0X20, 0X30, 0X31, 0X3A, 0X31, 0X39, 0X3A, 0X35, 0X37};

uint8_t Wtimebuf1[30]={           0X31, 0X37, 0X2F, 0X31, 0X32, 0X2F, 0X30, 0X36, 0X2C, 0X30, 0X37, 0X3A, 0X31, 0X39, 0X3A, 0X30, 0X34, 0X2B, 0X33, 0X32};

uint8_t  Time_Stamptohex[8]={0};     //最终需要上传的时间戳
	
	MyStrCPY(Wtimebuf1,  BC95_CLOCK, 20);
	
	Wtimebuf[2]=Wtimebuf1[0];    //年
	Wtimebuf[3]=Wtimebuf1[1];
	 
	Wtimebuf[5]=Wtimebuf1[3];    //月
	Wtimebuf[6]=Wtimebuf1[4];
	
	Wtimebuf[8]=Wtimebuf1[6];    //日
	Wtimebuf[9]=Wtimebuf1[7];
	
	test1[0]=Wtimebuf1[9];   
	test1[1]=Wtimebuf1[10];
	
	test3=StrTodec_1(test1,1)+8;			
	DecTostr(test2,test3);	

	Wtimebuf[11]=test2[0];  //时
	Wtimebuf[12]=test2[1];

//	Wtimebuf[11]=Wtimebuf1[9];  //时
//	Wtimebuf[12]=Wtimebuf1[10];
	
	Wtimebuf[14]=Wtimebuf1[12];  //分
	Wtimebuf[15]=Wtimebuf1[13];
	
	test1[0]=Wtimebuf1[15];   
	test1[1]=Wtimebuf1[16];
	
	test3=StrTodec_1(test1,1)+32;			
	DecTostr(test2,test3);	
																	
	Wtimebuf[17]=test2[0];   //秒
	Wtimebuf[18]=test2[1];
		
	NETtimel=GetTick(Wtimebuf);		
		
		
	ic8.i=(uint64_t)NETtimel*1000;
	
	for(i=0;i<8;i++)
	{
	Time_Stamptohex[7-i]=ic8.c[i];
	}
	
	MyStrCPY(Internet_Time_Stamp,Time_Stamptohex, 8);                    //拷贝时间戳
	
	//memcpy(Networktimebuf,Wtimebuf,19);
	
//	HAL_UART_Transmit(&huart1, Networktimebuf, 19, 500);//发送数据	
	
	
//	printf("%ld\n",Wtimebuf);	    //测试用
	
//	UART4Send_Data(Time_Stamptohex,8);   //测试用
	
}
	







#endif













