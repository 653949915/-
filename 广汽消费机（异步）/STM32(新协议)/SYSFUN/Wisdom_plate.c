#include "Head.h"

#include "Wisdom_plate.h"

#ifdef   WISDOM_PLATE


u8   WP_RxDataBuff[50];                         //中断接收数组

u16  WP_u8RxIndexW=0;                           //中断接收数组写指针

u8   WP_clearcycle=0;                           //清除串口数据计数


u8   WP_updatareturnfalg=0;                           //实时上传返回标志


u8  WP_UserBalance[4]={0X00,0X00,0X00,0X00};	  //卡上余额
 
u8  WP_Consum_Amount[4] ={0X00,0X00,0X00,0X00};	  //消费金额

//u8   Server_Returndata[20]={0};                //服务器返回的数据
 
 
u8  WP_defNOnetBalance[4]={0X38,0X90,0X08,0X00};	  //无网络时默认余额     //低位在前

u8  WP_defNOretBalance[4]={0X99,0X99,0X99,0X00};	  //无网络时默认余额     //低位在前

u8  WP_defNOcardBalance[4]={0X00,0X00,0X00,0X00};	  //无IC卡时默认余额

u16  wpOverTimeCnt=0;                        //超时退出计数

uint8_t  WP_readcard_ret=0 ;               //读卡返回读头号


uint8_t  WP_retcycle=0 ;               //读卡返回

//u8   USART4_RX_CRLF=0;

uint8_t  wp_Consumpidbuff[4] = {0};                   //消费时的卡号

 
 uint8_t  WP_Card_Read_falg=0 ;                 //读卡标志

 uint8_t  WP_Consumption_falg=0 ;               //消费标志




void WP_SendString(uint8_t *combuff ,uint16_t len)
{
	uint16_t t;
	for(t=0;t<len;t++)
	 {
		  USART_SendData(WP_UART, combuff[t]);//向串口1发送数据
			
			while(USART_GetFlagStatus(WP_UART,USART_FLAG_TC)!=SET);//等待发送结束
	
   }
}

void WP_SendByte(uint8_t combuff)
{
  //    delay_us(500);
		USART_SendData(WP_UART, combuff);//向串口1发送数据
	
		while(USART_GetFlagStatus(WP_UART,USART_FLAG_TC)!=SET);//等待发送结束
}



//u8 UPloadRecord_Ack(u16 overtime)
//{
//   wpOverTimeCnt = overtime;
//	 WP_updatareturnfalg =0 ;  //实时上传返回标志
//	
//		if(WP_updatareturnfalg)
//		{
//			return 1;
//		}
//		if (wpOverTimeCnt == 0)                      //超时退出
//				return 0;
//	
//}

//u8 WP_CheckCard_Ack(u16 overtime)
//{
//	 uint8_t ret = 0;
//	
//   wpOverTimeCnt = overtime;
//	 
//    while (1)
//    {
//			ret = WP_CheckCard();
//			
//        if(ret)
//				{		
//				  return ret;
//				}
//        if (wpOverTimeCnt == 0)                      //超时退出
//            return 0;
//	 }
//}




void   InitWPCombuff(void)//初始化串口通讯缓冲区
{

WP_u8RxIndexW=0; 

}

//01      5a 3c | 12 | 01 | 00 | 00 00 00 00 | 00 00 00 00 00 00 00 00 | 00 00 00 00 | 01 | DB
//02      5A 3C | 12 | 02 | 00 | 00 | 00 00 00 00 00 00 00 12 34 56 78 | 12 34 00 00 | 5C | DB
//03      5A 3C | 12 | 03 | 00 | 00 | 00 00 00 00 00 00 00 12 34 56 78 | 12 34 00 00 | 5D | DB



//        5A 3C | 16 | 01 | 00 | 00 | 00 00 00 00 00 00 00  12 34 56 78 | 12 34 00 00 | 00 00 00 00 | 5B | DB

//        5A 3C | 16 | 02 | 00 | 00 | 00 00 00 00 00 00 00  12 34 56 78 | 12 34 00 00 | 12 34 00 00 | 5B | DB

//        5A 3C | 16 | 03 | 00 | 00 | 00 00 00 00 00 00 00  12 34 56 78 | 12 34 00 00 | 12 34 00 00 | 5C | DB



/***************************************************************************************************
 * 函 数 名: 
 * 功能描述: 智盘串口发送数据给下位机，下位机进行命令响应返回
 * 函数说明: 
 * 调用函数: 无
 * 全局变量: 无
 * 输　　入:    cmdtyp    命令号     01 读卡  02 消费   03 交易确认
               Result    结果位
 * 返　　回: 无
***************************************************************************************************/

void Wisdom_plate_Return(uint8_t cmdtyp, uint8_t Result)
{
	uint8_t  WPreturnbufflen=22;
	
  uint8_t  WPreturnbuff[27]={0X5A, 0X3C, 0X16, 0X01, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00 ,0X12, 0X34, 0X56, 0X78, 0X12, 0X34, 0X00, 0X00 ,0X00, 0X00 ,0X00, 0X00,0X5B, 0XDB};

	uint8_t  wp_UserBalancebuf[4] ={0x00};
		
	uint8_t  testsuanfabuf1[4]={0x00};
		
	union    FourByte i4;
		
 MyStrCPY(wp_UserBalancebuf, WP_UserBalance, 4);        //拷贝卡上余额
		
 i4.i = getBCDtoDec(wp_UserBalancebuf, 4);              //数据格式转换
		
 WPreturnbuff[3]	=cmdtyp ;          //命令号
 WPreturnbuff[4]  =Result;           //结果位
	
 MyStrCPY(WPreturnbuff+13, idbuff, CARD_SIZE);       //拷贝卡号
	
 MyStrCPY(WPreturnbuff+17, i4.c, 4);        //拷贝卡上余额
		
// MyStrCPY(WPreturnbuff+17, WP_UserBalance, CARD_SIZE);        //拷贝卡上余额
		
// MyStrCPY(WPreturnbuff+21, WP_Consum_Amount, CARD_SIZE);      //拷贝消费金额		
	
 MyStrCPY(WPreturnbuff+21, testsuanfabuf1, CARD_SIZE);      //拷贝消费金额			
	
		
 WPreturnbuff[WPreturnbufflen + 3] = GetSum(WPreturnbuff + 3, WPreturnbufflen);     //和校验
	
 WP_SendString(WPreturnbuff ,27);
				
}



/*
二 读卡 0x01
-----------------------------------------------------------------------------------------------------------------

结算台发出：
;//  5a 3c | 12 | 01 | 00 | 00 00 00 00 | 00 00 00 00 00 00 00 00 | 00 00 00 00 | 01 | DB   
;//  头    | 长 | 命  | 流 | 无意义 | 无意义 | 无意义 | 校 | 尾
;//  部    | 度 | 令  | 水 |        |       |        | 验 | 标

pos返回：
;// 5A 3C | 16 | 01 | 00 | 00 | 00 00 00 00 00 00 00 12 34 56 78| 12 34 00 00 |00 00 00 00 | 5B | DB
;  //  头 | 长 | 命 | 结 | 保 | 卡号11字节 hex编码|  余额4字节  | 无意义| 校 | 尾
;  //  部 | 度 | 令 | 果 | 留 | 长度不够前面补0    |  hex 编码    |       | 验 | 标
         |  单位为分    |
                                                 |  低位在前    |

发送    5a 3c 12 01 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 01 DB 

*/
/***
void  Wisdom_plate_Card_Read(void)
{
  uint8_t  ret=0 ;
	
	uint8_t  reterr=0 ;
	
static	uint8_t  procretfalg=0 ;        //c处理接收返回的数据
	
	
//	uint8_t  reterrtest[4]={0} ;
	
//	ret  = WP_CheckCard_Ack(1);

 // WP_readcard_ret = WP_CheckCard();
	
  ret  =  WP_readcard_ret ;
	
//	 Write_SOCK_Data_Buffer(0, reterrtest, 1 );               // 测试用
	
	
  if(ret)    //检查读卡 
	{
	  if(ec20_device_info.netWork)
		{
		  wpOverTimeCnt =20;
			
			MyStrCPY(Consum_Amount, WP_RxDataBuff+17, 4);           //扣款金额 4字节
			
			Arrange_Record(ret ,1);  //数据整理
			
			UPloadRecord(3);        //实时上传数据
	
      WP_updatareturnfalg =0 ;  //实时上传返回标志
			
			procretfalg =1;

		}
		else                            //没有网络
		{
				  MyStrCPY(WP_UserBalance, WP_defNOnetBalance, CARD_SIZE);        //拷贝卡上余额   默认值
				 
				  MyStrCPY(WP_Consum_Amount, WP_defNOcardBalance, CARD_SIZE);      //拷贝消费金额
			
			    reterr =0;
						
			goto 	CRend ;	
		}
		
	//	Wisdom_plate_Return(0X01,0);          //响应智盘
	
//	  ProcessCard(ret);                //处理卡数据			
	}
//	else                                      //没找到卡
//	{
//		MyStrCPY(WP_UserBalance,   WP_defNOcardBalance, CARD_SIZE);        //拷贝卡上余额   默认值
//	 
//		MyStrCPY(WP_Consum_Amount, WP_defNOcardBalance, CARD_SIZE);      //拷贝消费金额

//		reterr =4;
//		
////	goto 	CRend ;
//	}
	
	
if((ec20_device_info.netWork)&&procretfalg)
{	
//	 reterrtest[0]  =ec20_device_info.netWork;
//	
//	Write_SOCK_Data_Buffer(0, reterrtest, 1 );               // 测试用
	
	if((WP_updatareturnfalg ==0)&&(wpOverTimeCnt))
	{
		return ;
	}
	if(WP_updatareturnfalg)    //服务器有返回
		{
				   	
			//拷贝服务器返回的数据				
			 MyStrCPY(WP_UserBalance, Server_Returndata +12, CARD_SIZE);        //拷贝卡上余额

			 MyStrCPY(WP_Consum_Amount, WP_defNOcardBalance, CARD_SIZE);      //拷贝消费金额	
			
		}
	else                           //服务器无返回
		{
			MyStrCPY(WP_UserBalance, WP_defNOretBalance, CARD_SIZE);        //拷贝卡上余额   默认值
		 
			MyStrCPY(WP_Consum_Amount, WP_defNOcardBalance, CARD_SIZE);      //拷贝消费金额
		}

reterr =0;	
procretfalg =0;
goto 	CRend ;		
}


if(WP_readcard_ret==0)                                      //没找到卡
	{
		MyStrCPY(WP_UserBalance,   WP_defNOcardBalance, CARD_SIZE);        //拷贝卡上余额   默认值
	 
		MyStrCPY(WP_Consum_Amount, WP_defNOcardBalance, CARD_SIZE);      //拷贝消费金额

		reterr =4;
		
	}


CRend:

  Wisdom_plate_Return(0X01,reterr);            //响应智盘	
	
  MyStrCPY(wp_Consumpidbuff, idbuff, 4);           //扣款时的卡号
	
	WP_Card_Read_falg =0 ;
	
	
//	if(WP_retcycle>=2)
//	{
//	  WP_retcycle= 0;
//		WP_readcard_ret =0;
//	}
}

***/

void  Wisdom_plate_Card_Read(void)
{
	uint8_t  reterr=0 ;
	
	if(WP_readcard_ret)    //检查读卡，检测到卡 
		{
			
			MyStrCPY(WP_UserBalance,   WP_defNOcardBalance, 4);        //拷贝卡上余额   默认值
		 
			MyStrCPY(WP_Consum_Amount, WP_defNOcardBalance, 4);      //拷贝消费金额
			
			reterr=0 ;
			
		}
	else                                      //没找到卡
		{
			MyStrCPY(idbuff,           WP_defNOcardBalance, CARD_SIZE);        //拷贝IC卡卡号   默认值
			
	//		MyStrCPY(WP_UserBalance,   WP_defNOcardBalance, CARD_SIZE);        //拷贝卡上余额   默认值
		 
//			MyStrCPY(WP_Consum_Amount, WP_defNOcardBalance, CARD_SIZE);        //拷贝消费金额

			reterr =4;
		
		}

	 Wisdom_plate_Return(0X01,reterr);            //响应智盘	
		
//	 MyStrCPY(wp_Consumpidbuff, idbuff, 4);           //扣款时的卡号
	
	 WP_Card_Read_falg =0 ;
	
}






/***

三 消费 0x02
-----------------------------------------------------------------------------------------------------------------

结算台发出（常规）：
;//  5A 3C | 12 | 02 | 00 | 00 | 00 00 00 00 00 00 00 12 34 56 78 | 12 34 00 00 | 5C | DB
;//  头   | 长 | 命 | 流 | 保 | 卡号11字节 hex编码 |   消费金额  | 校 | 尾
;//   部  | 度 | 令 | 水 | 留 | 长度不够前面补0     |             | 验 | 标
结算台发出（密码验证）：
;//  5A 3C | 16 | 02  | 00 | 00 | 00 00 00 00 00 00 00 12 34 56 78 | 12 34 00 00 | 00 00 00 00 | 5C | DB   
;//  头   | 长 | 命 | 流 | 保    | 卡号11字节 hex编码                | 消费金额    | 消费密码     | 校 | 尾
;//  部   | 度 | 令 | 水 | 留    | 长度不够前面补0                   |             |             | 验 | 标


pos返回：
;//  5A 3C | 16 | 02 | 00 | 00 | 00 00 00 00 00 00 00  12 34 56 78 | 12 34 00 00 | 12 34 00 00 | 5B | DB
;//  头 部 | 长 | 命  | 结 | 保  | 卡号11字节 hex编码 |  余额4字节  | 消费金额    | 校 | 尾
;//        | 度 | 令  | 果 | 留  | 长度不够前面补0     |  hex 编码    |             | 验 | 标
                                                    |  单位为分    |
 
                                                   |  低位在前    |


        0 表示成功
        1 表示失败
        3 表示超过消费限额（比如超过单餐，或者单日消费限额）
        4 表示交易未决（由于抽卡过快，pos机不知道交易是否成功），返回未决指令后，结算台会进入未决状态，等待pos机再次返回，定义见后文
        5 卡被禁用
        6 需要验证密码（将会重新发起带密码的支付）
        10 卡已损坏
        14 余额不足
        105 设备不可用（尝试重新连接）
        111 设备结算区满，需要同步（停止交易，发起结算）

***/

//             5a 3c 12 01 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 01 DB

//  5A 3C 12 02 00 00 00 00 00 00 00 00 00 12 34 56 78 12 34 00 00 5C DB


void  Wisdom_plate_Consumption(void)
{
  uint8_t  ret=0 ;
	
//  uint8_t  reterr=0 ;
	
//	uint8_t  wp_Conmoney[4]={0} ;
	
//	union FourByte Con_money;
	
//	static	uint8_t  procretfalg=0 ;        //c处理接收返回的数据
	
  ret  =  WP_readcard_ret ;

//	MyStrCPY(wp_Consumpidbuff, WP_RxDataBuff+13, 4);           //扣款时的卡号	
			
//	if(!MyStrEQ(wp_Consumpidbuff, idbuff, 4))
//	{
//   	return ;
//	}
		
	if(WP_retcycle ==1)      //是消费指令
	{
	   ProcessCard(ret);        //处理刷卡
		
		 WP_retcycle =0;
	}
		
	/***

if(WP_retcycle ==1)      //是消费指令
	{		
		Local_Check_Card_falg=0;    //本地检查刷卡权限	
		
		if(ec20_device_info.netWork)	          //有网络
		{
			wpOverTimeCnt =15;
			
			MyStrCPY(wp_Conmoney, WP_RxDataBuff+17, 4);           //扣款金额 4字节
					
			MyStrCPY(Con_money.c, wp_Conmoney, 4);           //扣款金额 4字节	
	
			getDectoBCD(Con_money.i, Consum_Amount, 4);
			
		  MyStrCPY(idbuff, wp_Consumpidbuff, 4);           //扣款时的卡号
						
			Arrange_Record(ret ,1);  //数据整理
			
			UPloadRecord(3);        //实时上传数据
		
		  WP_updatareturnfalg =0 ;  //实时上传返回标志	
			
			procretfalg =1;
			
			WP_retcycle =0;
		}
		
		else                            //没有网络
			{
		
				MyStrCPY(WP_Consum_Amount, WP_RxDataBuff+17, 4);           //扣款金额 4字节
											
				MyStrCPY(WP_UserBalance, WP_defNOcardBalance, CARD_SIZE);        //拷贝卡上余额   默认值   88888
         //显示用			 				
				MyStrCPY(Con_money.c, WP_Consum_Amount , 4);           //扣款金额 4字节	
	
			  getDectoBCD(Con_money.i, Consum_Amount, 4);
				
				MyStrCPY(UserBalance, WP_defNOretBalance, CARD_SIZE);           //拷贝余额	
				
        Pay_Carderr_Code = PAY_OK; 	
				
				Local_Check_Card_falg=1;    //本地检查刷卡权限	
				
				reterr =0;
							
				goto 	CONend ;	
			}		
}
			
if(ec20_device_info.netWork) 
{	
	
	//Write_SOCK_Data_Buffer(0, reterrtest, 1 );               // 测试用
	
	if((WP_updatareturnfalg ==0)&&(wpOverTimeCnt))     
			{
			  return ;
			}	
			
	if(WP_updatareturnfalg)    //服务器有返回
		{
					     //拷贝服务器返回的数据				
		 MyStrCPY(WP_UserBalance, Server_Returndata +12, CARD_SIZE);        //拷贝卡上余额
			
		 MyStrCPY(WP_Consum_Amount, Server_Returndata +8, CARD_SIZE);       //拷贝消费金额	
	   //显示用	
		 MyStrCPY(Consum_Amount, WP_Consum_Amount, CARD_SIZE);       //拷贝消费金额			
     MyStrCPY(UserBalance, WP_UserBalance, CARD_SIZE);           //拷贝余额
			
			if(Server_Returndata[17]==PAY_BACK_ERR)
			{
			Pay_Carderr_Code = PAY_BACK_ERR;
			
			reterr =5;		
				
			}
			else if(Server_Returndata[17]==PAY_NO_MONEY_ERR)
			{
				
				Pay_Carderr_Code = PAY_NO_MONEY_ERR;
							
				reterr =14;	
				
			}
			else 
			{		
				
			 Pay_Carderr_Code = PAY_OK;			
				
			 reterr =0;	
			}							     			
		}
	else          //服务器无返回
		{
			
			MyStrCPY(WP_UserBalance, WP_defNOretBalance, CARD_SIZE);        //拷贝卡上余额   默认值FF FF
		 
			MyStrCPY(WP_Consum_Amount, Consum_Amount, CARD_SIZE);      //拷贝消费金额
				
			//显示用	
			MyStrCPY(Consum_Amount, WP_Consum_Amount, CARD_SIZE);       //拷贝消费金额			
      MyStrCPY(UserBalance,   WP_defNOretBalance, CARD_SIZE);           //拷贝余额
			
	    Local_Check_Card_falg=1;    //本地检查刷卡权限		
			
      reterr =0;			
			
			Pay_Carderr_Code = PAY_OK; 	
		}
		
//	reterr =0;	
			
	procretfalg =0;
			
	goto 	CONend ;		
				
}			
		
CONend:

  Wisdom_plate_Return(0X02,reterr);          //响应智盘	

	MyStrCPY(wp_Consumpidbuff, WP_defNOcardBalance, 4);           //扣款时的卡号
	
	if(Local_Check_Card_falg)
	{
	  Check_Card_Limit (ret);    //检查名单
		
		Add_UpdataRecord(0);          //保存实时上传记录
	}

	AddRecord(ret ,0);          //存储记录
									
 if(Pay_Carderr_Code == PAY_OK)     
	{
	 SaveActual_CardCount(); 				//保存有效刷卡数 
	}
	else                         
	{				
	 SaveErr_CardCount();			      //保存错误刷卡数 
	}			
			
//	ShowPlay_Card_43inch(Pay_Carderr_Code) ;     //刷卡显示

	WP_readcard_ret =0;
	
	WP_Consumption_falg =0 ;
	
	**/
	
}



/*

交易确认指令

*/
void  Wisdom_plate_Transaction_Confirmation(void)
{

	Wisdom_plate_Return(0X03,0);   
	
}


/**********************************************************
//处理智盘串口通讯
**********************************************************/
void Process_Wisdom_plate(void)
{
	uint16_t WPData_length = 0;
	
	u8 DEF_WPHead[] = {0x5a,0x3c}; 
	
	if (WP_u8RxIndexW < 3) {goto com_rst;}						   					//检测数据量
	
	if (!MyStrEQ(WP_RxDataBuff, DEF_WPHead, 2)) 									//码头校验
	{
		goto com_end;
	}
	
	WPData_length = WP_RxDataBuff[2];             										//获取数据长度
	
/*----------------------------------------------------------------------------*/	
	if (WP_u8RxIndexW != (WPData_length +5))
	{ 
		if (WP_u8RxIndexW  < (WPData_length + 5))  {goto com_rst;}
		
		if (WP_u8RxIndexW  > (WPData_length + 5))  {goto com_end;}
	}
 else 
	{
		if (GetSum(WP_RxDataBuff + 3, WPData_length)!= WP_RxDataBuff[WPData_length + 3]) 	//异或检验
		{goto com_end;}
		
		if (WP_RxDataBuff[WPData_length + 4]!=0xDB) 									//码尾校验
		{goto com_end;}
			
		switch (WP_RxDataBuff[3])													//命令选择
		{
		  	case 0x01:  {	/*WP_readcard_ret = WP_CheckCard();*/  	

//					if(Enable_Pay_Card)
//		      { WP_Card_Read_falg =1;  	}	

      WP_readcard_ret = WP_CheckCard();	     //刷卡机读卡,返回读头号
      Pay_Head_Code  = WP_readcard_ret;
		
		  Wisdom_plate_Card_Read();		 

				}	break;					//读取卡内余额
			
			  case 0x02:    ProcessCard(WP_readcard_ret);            break;				  //消费
			
		  	case 0x03:    Wisdom_plate_Transaction_Confirmation();         break;					//交易确认
			

			
			default: goto com_end;
		}
	}
com_end:	
		InitWPCombuff(); 														// 初始化串口1缓存

com_rst:
	
		WP_clearcycle = 0;   															// 初始化清除缓冲计时
}



void  Process_Wisdom_plate_Card(void )
{
		
	if (WP_Card_Read_falg)               //收到智盘查询余额的指令
	{

      WP_readcard_ret = WP_CheckCard();	     //刷卡机读卡,返回读头号
			
      Pay_Head_Code  = WP_readcard_ret;
		
		  Wisdom_plate_Card_Read();		 
		
		
		
/***********************将IC卡卡号转换成广汽研究院卡号格式*********************************/	

//			if(WP_readcard_ret!=4)	  
//			{
//					GAEI_IC_Conversion(idbuff,idbuff); 
//			}	
						
		
					
	}


}



#endif

