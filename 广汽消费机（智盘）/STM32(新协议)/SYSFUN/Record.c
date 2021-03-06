#include  "Head.h"


#define   UPDATA 

/**********************************************************
//变量定义
**********************************************************/



 uint32_t  recordcount;                  //记录数量	

 uint8_t   rdtemporary_count=0;         //数卡记录临时存储计数  eeprom

 uint32_t   rdrealtime_up_count=0;         //数卡记录实时上传数量 flash

 uint32_t  stopdate_addr=0;               // 新增数据末端地址

 uint8_t  recorddata[RECORD_SIZE]={0X00};            //flash存储的数据（30字节）
 
  uint8_t  recorddataup[RECORD_SIZE]={0X00};            //flash存储的数据（30字节）
 
//static union FourByte Debit_money;
 
 uint8_t  temporarydata[300]={0X00};            //数卡记录临时存储  //实时上传用
 
 uint32_t  temporarycuraddr;     //刷卡记录存储地址 实时上传用
 
 uint16_t  uploadflash_cycle =0;         //实时上传保存到flash时间计数
 
 uint32_t  Flow_number =0;                //流水号
 
 u8  UserBalance[4]={0X00,0X00,0X00,0X00};	  //卡上余额
 
 u8  Consum_Amount[4] ={0X00,0X00,0X00,0X00};	  //消费金额
 
 u8  def_Consum_Amount[4] ={0X00,0X00,0X00,0X00};	  //消费金额
 
 uint32_t  Actual_Card_number =0;                //实际数卡数量
 
 uint32_t  Err_Card_number =0;                   //错误数卡数量
 
 uint32_t  Operation_Comm_number =0;             //操作命令数量
 
 uint8_t  def_dataZero[12]={0x00,0X00,0X00,0X00,0X00};     //定义数据0
 
 uint8_t  maxrecordcount_err =0;             //超出最大容量
 
 uint8_t  recordcount_err =0;                //存储错误计数
 
/**********************************************************
//常量定义
**********************************************************/
u8  ALL_NULL[] = {0xFF,0xFF,0xFF,0xFF}; 							  

//记录操作-------------------------------------------------	 

/**********************************************************
//初始记录存储个数  
**********************************************************/

void InitRecord(void)
{

	union FourByte ic4; 
	
	union FourByte icfn;   //流水号
	
	ic4.i = 0;
	
	icfn.i = 0;

	AT24CXX_Read( RECORD_POS  ,&(ic4.c[0]) ,  4);
	
	AT24CXX_Read( FLOW_NUMBER_POS  ,&(icfn.c[0]) ,  4);
	
	recordcount = ic4.i;
		
	Flow_number = icfn.i;
	
}
/**********************************************************
//保存记录数量
**********************************************************/
void SaveRecordCount(void)
{
	union FourByte ic4; 
	
	union FourByte icFN;
	
	ic4.i = recordcount; 
	
	icFN.i = Flow_number; 
	
	AT24CXX_Write( RECORD_POS, &(ic4.c[0]) , 4);
	
	AT24CXX_Write( FLOW_NUMBER_POS, &(icFN.c[0]) , 4);
	
}		 


/**********************************************************
//初始化实际数卡数量
**********************************************************/

void InitActual_CardCount(void)
{
	union FourByte ic4; 
		
	ic4.i = 0;
	
	AT24CXX_Read( ACTUAL_CARD_POS  ,&(ic4.c[0]) ,  4);
	
	Actual_Card_number = ic4.i;
		
}


/**********************************************************
//初始操作命令数量
**********************************************************/

void InitOperation_CommCount(void)
{

	union FourByte ic4; 
		
	ic4.i = 0;
	
	AT24CXX_Read( OPERATION_COMM_POS  ,&(ic4.c[0]) ,  4);
	
	Operation_Comm_number = ic4.i;
		
}

/**********************************************************
//初始错误数卡数量
**********************************************************/

void InitErr_CardCount(void)
{

	union FourByte ic4; 
		
	ic4.i = 0;
	
	AT24CXX_Read( ERR_CARD_POS  ,&(ic4.c[0]) ,  4);
	
	Err_Card_number = ic4.i;
		
}

/**********************************************************
//保存实际数卡数量
**********************************************************/
void SaveActual_CardCount(void)
{
	union FourByte ic4; 
	
	Actual_Card_number+=1;
	
	ic4.i = Actual_Card_number; 
	
	AT24CXX_Write( ACTUAL_CARD_POS, &(ic4.c[0]) , 4);
	
	
}

/**********************************************************
//保存错误数卡数量
**********************************************************/
void SaveErr_CardCount(void)
{
	union FourByte ic4; 
	
	Err_Card_number+=1;
	
	ic4.i = Err_Card_number ; 
	
	AT24CXX_Write( ERR_CARD_POS, &(ic4.c[0]) , 4);
	
}


/**********************************************************
//保存操作命令数量
**********************************************************/
void SaveOperation_CommCount(void)
{
	union FourByte ic4; 
	
	Operation_Comm_number+=1;
	
	ic4.i = Operation_Comm_number; 
	
	AT24CXX_Write( OPERATION_COMM_POS, &(ic4.c[0]) , 4);
	
}


/**********************************************************
//保存存储错误
**********************************************************/
void SaveRecordcount_Err(void)
{
	
	uint8_t  Recordcount_errbuf[4]={0};
	
	Recordcount_errbuf[0] = maxrecordcount_err;
	
	Recordcount_errbuf[2] = recordcount_err;
	
	AT24CXX_Write( ERR_RECORDERRCOUNT_POS, Recordcount_errbuf , 4);
	
}


/**********************************************************
//初始存储错误
**********************************************************/

void InitRecordcount_Err(void)
{  
	uint8_t  Recordcount_errbuf[4]={0};
	
	AT24CXX_Read( ERR_RECORDERRCOUNT_POS  ,Recordcount_errbuf ,  4);
	
  maxrecordcount_err =	Recordcount_errbuf[0] ;
	
  recordcount_err    =	Recordcount_errbuf[2]  ;
	
	if(maxrecordcount_err==0xff)
	{
		maxrecordcount_err =0;
			
		recordcount_err =0;	
			
		SaveRecordcount_Err();
		
	}
	
	
	
}



/**********************************************************
//删除所有记录
**********************************************************/
void DelRecord(void)
{
	u8 DEF_MACHNO[] = {0x00,0x00,0x00,0x00};
	
	recordcount = 0;
	
	Flow_number = 0;
	
  Actual_Card_number =0;                //实际数卡数量
 
  Err_Card_number =0;                   //错误数卡数量
 
  Operation_Comm_number =0;             //操作命令数量	
	
	AT24CXX_Write( RECORD_POS,          DEF_MACHNO,   4);		// 初始化数据采集起始地址
	
	AT24CXX_Write( FLOW_NUMBER_POS,     DEF_MACHNO,   4);		// 初始化数据采集起始地址
	
	AT24CXX_Write( ACTUAL_CARD_POS  ,   DEF_MACHNO ,  4);   //初始化实际数卡数量
	
	AT24CXX_Write( ERR_CARD_POS  ,      DEF_MACHNO ,  4);   //初始错误数卡数量
	
	AT24CXX_Write( OPERATION_COMM_POS  ,DEF_MACHNO ,  4);  //初始操作命令数量
	
	SPI_Flash_Erase_Sector(0);
		
	SaveRecordCount();
}	 	

/**********************************************************
//初始化实时上传记录存储个数  
**********************************************************/

void Init_UpdataRecord(void)
{

	union FourByte ic4; 
	
	ic4.i = 0;
	
	AT24CXX_Read( UPDATA_RECORD_POS  ,&(ic4.c[0]) ,  4);
	
	rdrealtime_up_count = ic4.i;
	
}
/**********************************************************
//保存实时上传记录数量
**********************************************************/
void Save_UpdataRecordCount(void)
{
	union FourByte ic4; 
	
	ic4.i = rdrealtime_up_count; 
	
	AT24CXX_Write( UPDATA_RECORD_POS, &(ic4.c[0]) , 4);
	
}		 

/**********************************************************
//删除所有实时上传记录
**********************************************************/
void Del_UpdataRecord(void)
{
	
	rdrealtime_up_count = 0;
		
	Save_UpdataRecordCount();
}	 	






/**********************************************************
//整理数卡记录
输入参数：  cnt      读头号
           type     是否增加流水号   1、增加  0、流水号置0
输出参数： 无

**********************************************************/
void  Arrange_Record(u8 cnt ,uint8_t type)
{
	u8  ReMachine_type [1]={0X00};       //机器类别
	u8  ReRrror_Code   [1]={0X00};       //错误代码
	u8  Recntbuf       [1]={0X00};              //读头号
	u8  Record_Serial_numbuf[4]={0X22,0X22,0X22,0X22};     //流水号缓冲区
	
	union FourByte recordnum;     //流水号
	
//	MyStrCPY(UserBalance+1, blk1, 2);     //拷贝卡上余额

//#ifdef   WISDOM_PLATE    //是智盘

		uint8_t  wp_Conmoney[4]={0} ;
	
	  union FourByte Con_money;
	
		MyStrCPY(wp_Conmoney, WP_RxDataBuff+17, 4);      //扣款金额 4字节
				
		MyStrCPY(Con_money.c, wp_Conmoney, 4);           //扣款金额 4字节	

		getDectoBCD(Con_money.i, Consum_Amount, 4);     //金额格式转换
	
	  type =1;                                        //消费状态需要增加流水号	
	
//#else		
//			
//	if(GetWorkStatus(IN_CONSUMPT_STATUS))   //消费状态
//	{
//	  MyStrCPY(Consum_Amount , keymoneybuff, 4);    //拷贝消费金额
//		
//		type =1;                //消费状态需要增加流水号
//	}
//	else if(Machine_category[0] == 0x02) //定值扣费
//	{	
//		 uint8_t  moneybuf[4] ={0};
//				
//	   MyStrCPY(moneybuf+2,  Fixed_consum_Moneybuf +Consum_TimerBit[1]*2,  2);
//		
//		 MyStrCPY(Consum_Amount,  moneybuf,  4);
//		
//		 type =1;                //消费状态需要增加流水号
//	}
//	
//	else  if(Machine_category[0] == 0x03) //计次扣费
//	{
//	  MyStrCPY(Consum_Amount , def_Consum_Amount, 4);    //拷贝*默认消费金额  00
//		
//		Consum_Amount[2] = 0x01;
//		
//		type =1;                //消费状态需要增加流水号
//	}	
//	
//	else 
//	{
//	  MyStrCPY(Consum_Amount , def_Consum_Amount, 4);    //拷贝*默认消费金额  00
//		
//		type =1;                //消费状态需要增加流水号
//	}		
//			
//#endif	


	if(type)          //需要增加流水号
	{
		
		recordnum.i=  Flow_number++;		             //刷卡记录流水号 +1	
//	recordnum.i=     recordcount+1;		             //刷卡记录流水号 +1
	  turn_4_data(Record_Serial_numbuf,recordnum.c);
	}
	else                     //命令的流水号是00
	{
		Record_Serial_numbuf[0]=0X00;
		Record_Serial_numbuf[1]=0X00;
		Record_Serial_numbuf[2]=0X00;
		Record_Serial_numbuf[3]=0X00;
	}
	
	Recntbuf[0]       = cnt;                          //读头号赋值
	
#ifdef   Consumer_machine    //消费机

  	ReMachine_type[0] = MACHINE_CATEGORY | Machine_category[0]  ;//机器类别
#else	
	
		ReMachine_type[0] = MACHINE_CATEGORY /*| Machine_category[0]  */ ;//机器类别
	
#endif
	
	ReRrror_Code[0]   = Pay_Carderr_Code  ;           //错误代码
	
	MyStrCPY(recorddata , machno, 4);                 //机号 4字节
	
	MyStrCPY(recorddata+4, idbuff, 4);                //卡号 4字节
		 
	MyStrCPY(recorddata + 8, time_buf+1, 6);          //时间 6字节
	
	MyStrCPY(recorddata + 14, Consum_Amount, 4);      //扣款金额 4字节

	MyStrCPY(recorddata + 18, UserBalance, 4);        //卡上余额 4字节
	
	MyStrCPY(recorddata + 22, ReMachine_type, 1);     //机器类别 1字节	（1.考勤 2.门禁 3.消费 ）  | 数据类型 1字节 （1.扣款 2.定值 3.计次 4.菜单 5.报餐 6.充值 ）  （由一个字节组成）

	MyStrCPY(recorddata + 23, ReRrror_Code, 1);       // 错误代码
	
	MyStrCPY(recorddata + 24, Recntbuf , 1);          //读头号   1字节	（1.读卡器 2.韦根1 3.韦根2   4 读头IC 5   读头 二维码 ）
	
	MyStrCPY(recorddata + 25, communication_data+AGR_CMD_POS, 1);           //通讯命令    1字节	

	MyStrCPY(recorddata + 26, Record_Serial_numbuf, 4);           //流水号    4字节

}

/**********************************************************
//保存实时上传记录

如果 typ为1   直接保存数据到flash

**********************************************************/
void Add_UpdataRecord(uint8_t typ)
{
	 if (rdrealtime_up_count >= UPDATA_MAX_RECORD) //最大存储UPDATA_MAX_RECORD记录
		{

			Del_UpdataRecord();     //删除实时上传数据
		}
		
		 temporarycuraddr = UPDATA_POS + rdrealtime_up_count * RECORD_SIZE;                        //存储起始地址+（30字节为一条信息*信息条数=已占用字节数）		
		
	   SPI_Flash_Write(recorddata ,temporarycuraddr, RECORD_SIZE );            //将卡号和打卡时间写到FLASH上	

		 rdrealtime_up_count += 1;       //保存到flash的数量	 

		 Save_UpdataRecordCount();    //保存数量

		
		
//	 MyStrCPY(temporarydata + rdtemporary_count*RECORD_SIZE , recorddata, RECORD_SIZE);           //拷贝记录	
//	 
//	 rdtemporary_count +=1;       //先储存，再计数！
//		
//saverecord:
//	 if((rdtemporary_count>=8)||(typ ==1))
//	 { 
//		 temporarycuraddr = UPDATA_POS + rdrealtime_up_count * RECORD_SIZE;                        //存储起始地址+（30字节为一条信息*信息条数=已占用字节数）
//		 
//		 SPI_Flash_Write(temporarydata ,temporarycuraddr, rdtemporary_count*RECORD_SIZE );            //将卡号和打卡时间写到FLASH上	
//		 
//		 rdrealtime_up_count += rdtemporary_count;       //保存到flash的数量	 

//		 rdtemporary_count = 0;
//		 
//		 Save_UpdataRecordCount();    //保存数量
//	 }

}



/**********************************************************
//增加记录：

输入参数：  cnt      读头号
           type     是否增加流水号 
输出参数： 无


**********************************************************/
void AddRecord(u8 cnt ,uint8_t type)
{
		u8  ReRrror_Code   [1]={0X00};       //错误代码
	
	uint8_t falsh_readbuf[RECORD_SIZE+1] ={0x00};
	
//  uint8_t  testbuf[4];     //刷卡记录存储地址
	
//	u8  ReMachine_type [1]={0X00};       //机器类别
//	u8  ReRrror_Code   [1]={0X00};       //错误代码
//	u8  Recntbuf       [1]={0X00};              //读头号
//	u8  Record_Serial_numbuf[4]={0X22,0X22,0X22,0X22};     //流水号缓冲区
//	
//	u8  testbuff [4]={0X00,0X00,0X01,0X00};
//	
//	u8  UserBalance[4]={0X00,0X00,0X00,0X00};	  //卡上余额
//	
//	union FourByte recordnum;     //流水号
//	
	uint32_t  curaddr;     //刷卡记录存储地址

//	MyStrCPY(UserBalance+1, blk1, 2);     //拷贝卡上余额
	
	if (recordcount >= MAX_RECORD) //最大存储MAX_RECORD条记录
	{
				
	//	DelRecord();             //删除所有记录（擦除25Q64）
//		recordcount = 0;	

		maxrecordcount_err =1; //超出最大存储数量错误
		
		SaveRecordcount_Err();  //保存存储错误
	}
  
//	if(type)          //需要增加流水号
//	{
//	recordnum.i=     recordcount+1;		             //刷卡记录流水号 +1
//	turn_4_data(Record_Serial_numbuf,recordnum.c);
//	}
//	else                     //命令的流水号是00
//	{
//		Record_Serial_numbuf[0]=0X00;
//		Record_Serial_numbuf[1]=0X00;
//		Record_Serial_numbuf[2]=0X00;
//		Record_Serial_numbuf[3]=0X00;
//	}
//	
//	Recntbuf[0]       = cnt;                         //读头号赋值
//	ReMachine_type[0] = sysvar[7]  ;                 //机器类别
//	ReRrror_Code[0]   = Pay_Carderr_Code  ;          //错误代码
//	
//	MyStrCPY(recorddata , machno, 4);                 //机号 4字节
//	
//	MyStrCPY(recorddata+4, idbuff, 4);                //卡号 4字节
//		 
//	MyStrCPY(recorddata + 8, time_buf+1, 6);          //时间 6字节
//	
//	MyStrCPY(recorddata + 14, testbuff, 4);           //扣款金额 3字节

//	MyStrCPY(recorddata + 18, UserBalance, 4);           //卡上余额 3字节
//	
//	MyStrCPY(recorddata + 22, ReMachine_type, 1);           //机器类别 1字节	（1.考勤 2.门禁 3.消费）  | 数据类型 1字节 （1.扣款  2.计次 3.报餐 4.充值 ）  （由一个字节组成）

//	MyStrCPY(recorddata + 23, ReRrror_Code, 1);             // 错误代码
//	
//	MyStrCPY(recorddata + 24, Recntbuf , 1);                //读头号   1字节	（1.读卡器 2.韦根1 3.韦根2   4 读头IC 5   读头 二维码 ）
//	
//	MyStrCPY(recorddata + 25, communication_data+AGR_CMD_POS, 1);           //通讯命令    1字节	

//	MyStrCPY(recorddata + 26, Record_Serial_numbuf, 4);           //流水号    4字节	
	
	ReRrror_Code[0]   = Pay_Carderr_Code  ;           //错误代码
	
	MyStrCPY(recorddata + 23, ReRrror_Code, 1);       // 错误代码	
	
	MyStrCPY(recorddata + 14, Consum_Amount, 4);      //扣款金额 4字节

	MyStrCPY(recorddata + 18, UserBalance, 4);        //卡上余额 4字节	
//	Arrange_Record( cnt , type);          //整理数卡数据
	
	curaddr = RECORD_ST + recordcount * RECORD_SIZE;//存储起始地址+（30字节为一条信息*信息条数=已占用字节数）
	
	SPI_Flash_Write(recorddata ,curaddr,  RECORD_SIZE );            //将卡号和打卡时间写到FLASH上	

  SPI_Flash_Read(falsh_readbuf ,curaddr,  RECORD_SIZE);
  if(!MyStrEQ(falsh_readbuf,recorddata,RECORD_SIZE))
		{
		   recordcount_err++;
			
			if(recordcount_err>=5)
				{				
					maxrecordcount_err =1; //超出最大存储数量错误
										
					SaveRecordcount_Err();  //保存存储错误
				}							
		}
		else {
		   recordcount_err = 0;
		}

	recordcount += 1;//先储存，再计数！
	
 // getDectoBCD(Consum_Allmoney.i, testbuf, 4);
 
  SaveRecordCount();     //保存流水号和数卡数量
 
//if(GetWorkStatus(IN_CONSUMPT_STATUS)||(Machine_category[0] != 0x01)||(Machine_category[0] != 0x02)||(Machine_category[0] != 0x03))        //按键状态 保存实时上传记录		
if((falsh_readbuf[23]==0x00)&&(falsh_readbuf[25]==0x00))		    //消费状态
{

		if(!MyStrEQ(Consum_Amount, def_dataZero, 4))
		{
				Consum_Allmoney.i += getBCDtoDec(Consum_Amount,	4);
				
			 SaveConsumption_All_Money();   //保存消费总额
		}
}
// RS485_Send_Data(falsh_readbuf,	30);
//  RS485_Send_Data(testbuf,	4);
	 	 
}


/**********************************************************
//实时上传刷卡记录

**********************************************************/
void UPloadRecord(u8 stype)
{
	u8 UPloadRecordbuf[]={  0x2A,0x18,0x04,0x18,0x00,0x01,0x51,0x05,0x07,0x01,
		                      0xA1,0x30,0x00,0x1E,0x11,0x11,0x11,0x11,0x11,0x11,
		                      0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,
		                      0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,
		                      0x11,0x11,0x11,0x11,0xEE,0xFF,0xFF,0xFF,0xFF,0x7E,
	                        0x7E,0x7E	};
	
		MyStrCPY(UPloadRecordbuf + AGR_MACH_POS, machno, MACH_SIZE);//机号		
													
		MyStrCPY(UPloadRecordbuf + AGR_DATA_POS, recorddata, RECORD_SIZE);//记录 
		  
	  UPloadRecordbuf[AGR_ROX_POS + RECORD_SIZE -1] = GetXOR(UPloadRecordbuf + AGR_DATA_POS, RECORD_SIZE);//xor检验位
	
//    UPloadRecordbuf[10] =0xA0|stype;
		MyStrCPY(recorddataup, recorddata, RECORD_SIZE);//记录
													
		if  ((COMM_MODE>>0)&0x01)			
		{
			UPloadRecordbuf[10] =0xA1;
			RS485_Send_Data(UPloadRecordbuf, AGR_MAXEND_POS + RECORD_SIZE);		
		}
		if  ((COMM_MODE>>1)&0x01)
		{
			UPloadRecordbuf[10] =0xA2;
			Write_SOCK_Data_Buffer(1,UPloadRecordbuf, AGR_MAXEND_POS + RECORD_SIZE);
		}
		if  ((COMM_MODE>>2)&0x01)
		{
			UPloadRecordbuf[10] =0xA3;
			Write_SOCK_Data_Buffer(0,UPloadRecordbuf, AGR_MAXEND_POS + RECORD_SIZE);
		}
		if  ((COMM_MODE>>3)&0x01)
		{
			UPloadRecordbuf[10] =0xA4;
			EC20_SendString(UPloadRecordbuf, AGR_MAXEND_POS + RECORD_SIZE);
		}													
}


/**********************************************************
//删除实时上传刷卡记录
**********************************************************/
void DelUPloadRecord(u8 *rd)
{
	uint8_t  i;
	uint8_t  findrd =0;
  uint8_t rdbuf[RECORD_SIZE];
	
	
	MyStrCPY(rdbuf, rd, 4);
	
	for(i=0;i<=8;i++)
	{
	
	 if(MyStrEQ(temporarydata+RECORD_SIZE*i +26, rdbuf, 4)) //找到记录
	 {
		 findrd =1;
		 break;
	 }
	}
	if(findrd)    //找到记录
	{
	MyStrCPY(temporarydata+ i*RECORD_SIZE ,temporarydata+ (rdtemporary_count-1)*RECORD_SIZE , RECORD_SIZE);                   //

		if(rdtemporary_count)
     rdtemporary_count --;
		
		
		
	}
}


















