#include "Head.h"

u32 idcycle=0; //两次读同一张卡间距
u8  idcycleflag=0;
u8  oldID[CARD_SIZE]; //记录上次读卡卡号
u8  PasswordMask[6];  //密码掩码 加密

// union FourByte leftcount;
 u8  curSection; //当前读写扇区
 u8  cardPW[PASSWORD_SIZE]; //卡密码

 u8  blk0[BLOCK_SIZE];   //0块
 u8  blk1[BLOCK_SIZE];   //1块
 u8  blk2[BLOCK_SIZE];   //2块
 u8  blk3[BLOCK_SIZE];   //3块

 u32 isAdmin;       //管理卡
 u32 isICSetting;   //设置卡标志
 u32 isValidICPW;   //有效IC卡密码
 u32 isValidICData; //读取到块数据


 u8 blk6[]={0x12,0x34,0x56,};

 uint8_t Pay_Carderr_Code = 0;       // 刷卡错误代号 

 uint8_t Pay_Head_Code = 0;       // 刷卡读头号

 uint8_t Enable_Pay_Card = 1;       // 允许刷卡标志

/**********************************************************
//检查读卡
**********************************************************/
void CheckCard(void)
{
#ifdef WITH_RC522_FUNC    //带RC522功能
	
	Pay_Head_Code =0;
	
	if (FindICCard())
		{						
		 ProcessCard(1);                //刷卡机读卡			

     Pay_Head_Code =1;			
		}
#endif	
		
	if (ProcessWG1())
		{		
			ProcessCard(2);                //韦根读头刷卡	
				
      Pay_Head_Code =2;			
		}
		
	if (ProcessWG2())
		{		
			ProcessCard(3);                //韦根读头刷卡	
	
      Pay_Head_Code =3;			
		}
		
	if (ProcessQR_Commu())
		{
		  ProcessCard(QRread_styp);                //二维码读头  
			
			Pay_Head_Code =QRread_styp;
		}	
}



/**********************************************************
//处理卡42876DC5
**********************************************************/
void  ProcessCard(u8 stype)
{

//	uint8_t  querydatabuf[30]={0x00};
		u8 querydatabuf[]={  0x2A,0x18,0x04,0x18,0x00,0x01,0x51,0x05,0x07,0x01,
		                     0xA4,0x6D,0x00,0x06,0x01,0x02,0x03,0x04,0x05,0x06,
		                     0X00,0xFF,0xFF,0xFF,0xFF,0x7E,0x7E,0x7E	};
	
	
//	u8  nolimited[] = {0x42,0x87,0x6D,0xC5};

	 uint8_t nolimited[] = {0x95,0x30,0x48,0x2B};    //羊城通

//	//	/***********************待机状态不允许刷卡*********************************/	
//	 
//		if((GetWorkStatus(NORMAL_STATUS))&&(Machine_category[0] != 0x02))
//			{
//				return ;
//	  
//			}			 
//	//	/***********************************************************************/		 
	 
	 Pay_Carderr_Code = PAY_OK;             //清除错误代码标志

   LED2_fun(2 , SHORT_BEEP);
	 
/***********************将IC卡卡号转换成广汽研究院卡号格式*********************************/	

		if(stype!=4)	
		{
				GAEI_IC_Conversion(idbuff,idbuff); 
		}	
		
	/***********************同一张卡只读取一次*********************************/	
	if ( (idcycle < (2 * interval_time[0]+10)) && MyStrEQ(idbuff, oldID, CARD_SIZE))
		{
				idcycle = 0;  //两次读同一张卡间距
			
			  return;
		}	 		
		
		MyStrCPY(oldID, idbuff, CARD_SIZE);	
				
	  idcycleflag =0;	  //重复数卡间隔计数开始停止
		
	  idcycle = 0;  //两次读同一张卡间距		
			
//	  SYN6288_Send(SYN6288CMD_VOICE_PLAY ,SYN6288CMDPARAM_PLAY_MUSIC0,"soundb" ,6);		

	//	/***********************待机状刷卡态查询余额*********************************/	
	 
		if((GetWorkStatus(NORMAL_STATUS))&&(Machine_category[0] != 0x02))
			{
				goto inspect_balance ;
	  
			}			 
	//	/***********************************************************************/			
		
		
#ifdef   WISDOM_PLATE     //是智盘

		
#else		     //不是智盘		
			
	if(Check_the_balance)    //余额查询
	 {
		 inspect_balance:
		 
		 Beep(1, SHORT_BEEP);
		 
		 MyStrCPY(querydatabuf + AGR_MACH_POS, machno, MACH_SIZE);//机号	
		 
		 idbuff[14] =  stype;    //拷贝读头号
		 
		 MyStrCPY(querydatabuf + 16,idbuff,4); //拷贝卡号
		 
		 querydatabuf[AGR_ROX_POS + 6 -1] = GetXOR(querydatabuf + AGR_DATA_POS, 6);//xor检验位		 
		 
	   MyStrCPY(communication_data,querydatabuf,28);	 
		 		 
		 if  ((COMM_MODE>>0)&0x01)			
			{
				communication_data[10] =0xA1;
				RS485_Send_Data(communication_data, AGR_MAXEND_POS + 6);		
			}
		 if  ((COMM_MODE>>1)&0x01)
			{
				communication_data[10] =0xA2;
				Write_SOCK_Data_Buffer(1,communication_data, AGR_MAXEND_POS + 6);
			}
		 if  ((COMM_MODE>>2)&0x01)
			{
				communication_data[10] =0xA3;
				Write_SOCK_Data_Buffer(0,communication_data, AGR_MAXEND_POS + 6);
			}
		 if  ((COMM_MODE>>3)&0x01)
			{
				communication_data[10] =0xA4;

				EC20_SendString(communication_data, AGR_MAXEND_POS + 6);
			}
		 
		memset(communication_data ,0,sizeof(u8)*52);         //清0	
			
		 idcycleflag =1;      //重复数卡间隔计数开始 2019-02-21
			
	 	return;
	 }		
	 

	if(refund_the_balance)    //退款操作
	 {
		if( !MyStrEQ(idbuff, RefundICcardbuf, CARD_SIZE))
		{
			  Pay_Carderr_Code = PAY_REFUND_CARD_ERR;       //卡号错误
			
			  goto ProcessCardend;
		
		}    
	 }	
		if(Consum_TimerBit[0]==0)	               //非就餐时段不允许刷卡
		{
//			Beep(1, SHORT_BEEP);
			
//			SYN6288_Send(SYN6288CMD_VOICE_PLAY ,SYN6288CMDPARAM_PLAY_MUSIC0,"sounda" ,6);
			
			Pay_Carderr_Code = PAY_NO_CONSUM_TIMER_ERR;       //非就餐时间段
			
			goto ProcessCardend;
		}
			
		if(GetWorkStatus(KEY_KEY_STATUS))        //按键状态不允许刷卡
		{
			
//			SYN6288_Send(SYN6288CMD_VOICE_PLAY ,SYN6288CMDPARAM_PLAY_MUSIC0,"sounda" ,6);
			
			idcycleflag =1;	  //重复数卡间隔计数开始停止
			
	//		Beep(1, SHORT_BEEP);
		
			return;
		}
#endif		 
	
	 if(maxrecordcount_err)
		{
		
			Pay_Carderr_Code = EXCEED_MAX_RECORD_ERR;          //超出最大容量
						
			goto ProcessCardend;
		}

		
		//0、超级卡
		if (MyStrEQ(idbuff, nolimited, CARD_SIZE))
		{
			BeginOutput1();
			
			BeginOutput2();
			
			return;
		}
        		
	//设置管理卡	//管理卡	//设置卡	//增加或删除卡
			
	DS1302_Read_Time();       //读时间	
		
	Beep(1, SHORT_BEEP);	
		
//	SYN6288_Send(SYN6288CMD_VOICE_PLAY ,SYN6288CMDPARAM_PLAY_MUSIC0,"soundb" ,6);
			
  memcpy( oldQRID , idbuff , 4 );	
		
//	MyStrCPY(oldID, idbuff, CARD_SIZE);
	
	Arrange_Record(stype ,0);         //整理刷卡数据

	UPloadRecord(3);        //实时上传数据
	 
	updatareturnfalg =0 ;  //实时上传返回标志 置0

	
#ifdef   WISDOM_PLATE     //是智盘

		 upOverTimeCnt =18;          //
	
#else		     //不是智盘

		 upOverTimeCnt =30;         
#endif	
	
	
ProcessCardend:

	

	 Card_Markok = 1;     //有刷卡

//	 idcycleflag =1;      //重复数卡间隔计数开始 2019-02-21
	
	 Enable_Pay_Card = 0; //不允许刷卡
}


/*
   检查刷卡权限

输入：stype    读头号

*/

void Check_Card_Limit (uint8_t  stype )
{
			
	/***********************检查白名单	*********************************/
  if(whiteallow[0]==0xBB)                    //如果开启检测白名单
		{
		
			FindCardno();                          //查找白名单
			
		  if (!bfindcard)                        //如果没名单，直接退出
			{
			//	RS485_Send_Data(idbuff ,4);         //测试用		
		
				Beep(4, SHORT_BEEP);
							
				Pay_Carderr_Code = PAY_WHITEALLOW_WRR;             //错误代码 白名单错误
				goto Pay_Card_end;		
			}	
	//   RS485_Send_Data(Permission_Periodbuff ,2);       //测试用			
			/***********************检查通行权限	*********************************/							
//		Holiday_Detection();      //检测是否节假日	
		
		if(bHoliday)	
			{
				HolidayTime_Interval_Detection();
							
			 if(!bHolitimeseg)				           //不在设定时段内
					{
						
					Beep(4, SHORT_BEEP);
						
					Pay_Carderr_Code = PAY_HOLIDAY_ERR;             //错误代码 节假日错误
						
				  goto Pay_Card_end;	
						
					}				
			}
	  else	
			{					
				Time_Interval_Detection();     //检测时段
					
				if(!btimeseg)				           //不在设定时段内
					{
						
					Beep(4, SHORT_BEEP);
						
					Pay_Carderr_Code = PAY_TIME_INTERVAL_ERR;             //错误代码 时间段错误
				  goto Pay_Card_end;	
						
					}
				}					
		}
		
/***********************检查黑名单	*********************************/	
  Back_FindCardno();                     //查找黑名单
		
  if (back_bfindcard)                    //如果有名单，直接退出
			 {			
			//	RS485_Send_Data(ICidbuff ,4);       //测试用				

				Beep(4, SHORT_BEEP);			
				 
				Pay_Carderr_Code = PAY_BACK_ERR;             //错误代码 黑名单错误
				goto Pay_Card_end;		
				}	
					
/***********************检查消费限额	*********************************/	
	
		if(Sub_Maximum_Limitbuf[0]==0x01)                    //如果开启检测消费限额
			{						
				if( MyStrCMP(Consum_Amount+1 ,  Sub_Maximum_Limitbuf + 1, 3) <=2)        //消费金额对比							
				{
				
				}
				else
				{
							Pay_Carderr_Code = PAY_EXCEED_LIMIT_SECOND_ERR;             //错误代码 超出当次限额
					
						 goto Pay_Card_end;
				}	
			}
								
/***********************韦根还是控制器读卡	*********************************/
	
//	if (stype==1) //控制器读卡
//			{				
//				if (extvar[0]==0X00)   //如果不需要读写卡内容
//						{						
//							if (extvar[1]==0X01) //检查密码
//									{
//										if (!isValidICPW)               //如果密码错误
//												{ 														            													
//														Beep(4, SHORT_BEEP);	
//													
//													  Pay_Carderr_Code = PAY_SECTOR_PASSW_ERR;             //错误代码 扇区密码错误
//				                    goto Pay_Card_end;	
//												}											
//									}									
//																	 													
//							 goto Pay_Card_end;											
//						}
//				            
//				else //需要读写卡内容
//						{
//							if (isValidICData)       
//									{										
//											u8 readresult; 

//											readresult = AnalyzeSectionData(); //分析扇区数据

//											if (readresult != SECTION_RD_SUCC) //扇区数据无效
//												{
//												//	return 0;
//												}
//																														  
///******************************************刷卡延时检测	****************************************************/			
//										//	DS1302_Read_Time();     //读取DS1302的时间						
//											if(Time_interval_fun()!=TIME_INTERVAL_SUCC)   //刷卡延时处理
//													{									
//														 Beep(4, SHORT_BEEP);						
//														 Pay_Carderr_Code = PAY_DELAYED_ERR;             //错误代码 数卡延时错误
//														 goto Pay_Card_end;	
//													}		
///*******************************************************************************************************/	
//																				
//										  ProcessICCard();          //处理IC卡块数据
//														
////											Beep(1, SHORT_BEEP);				
//									
//											BeginOutput1();		
//									}
//							else
//									{
//										Beep(4, SHORT_BEEP);	
//										
//										Pay_Carderr_Code = PAY_SECTOR_PASSW_ERR;             //错误代码 读写扇区错误
//				            goto Pay_Card_end;										
//									}												
//				    }
//			}
//	
//	else //韦根读卡，无法检验密码
//			{
//      Pay_Carderr_Code = PAY_OK; 				
//		  }	
			
		 Pay_Card_end:                //刷卡结束
     Pay_Carderr_Code = Pay_Carderr_Code;

}




/**********************************************************
//处理卡42876DC5
**********************************************************/
void  WP_ProcessCard(u8 stype)
{

//	u8  nolimited[] = {0x42,0x87,0x6D,0xC5};

//	 uint8_t nolimited[] = {0x95,0x30,0x48,0x2B};    //羊城通

	 Pay_Carderr_Code = PAY_OK;             //清除错误代码标志
	
	//设置管理卡	//管理卡	//设置卡	//增加或删除卡
	
	/***********************同一张卡只读取一次*********************************/	
//	if ( (idcycle < (2 * interval_time[0]+2))   &&   MyStrEQ(idbuff, oldID, CARD_SIZE))
//		{
//				idcycle = 0;  //两次读同一张卡间距
//			
//			  return;
//		}
//	
//	idcycleflag =0;	
//		
//	idcycle = 0;  //两次读同一张卡间距	
//		
//	MyStrCPY(oldID, idbuff, CARD_SIZE);
//	
////  DS1302_Read_Time();     //读取DS1302的时间	
//		
//	SYN6288_Send(SYN6288CMD_VOICE_PLAY ,SYN6288CMDPARAM_PLAY_MUSIC0,"soundb" ,6);
		
		
	/***********************检查白名单	*********************************/
  if(whiteallow[0]==0xBB)                    //如果开启检测白名单
		{
			FindCardno();                          //查找白名单
			
		  if (!bfindcard)                        //如果没名单，直接退出
			{
			//	RS485_Send_Data(idbuff ,4);         //测试用		
		
				Beep(4, SHORT_BEEP);
							
				Pay_Carderr_Code = PAY_WHITEALLOW_WRR;             //错误代码 白名单错误
				goto Pay_Card_end;		
			}	
	//   RS485_Send_Data(Permission_Periodbuff ,2);       //测试用			
			/***********************检查通行权限	*********************************/							
		Holiday_Detection();      //检测是否节假日	
		
		if(bHoliday)	
			{
				HolidayTime_Interval_Detection();
							
			 if(!bHolitimeseg)				           //不在设定时段内
					{
						
					Beep(4, SHORT_BEEP);
						
					Pay_Carderr_Code = PAY_HOLIDAY_ERR;             //错误代码 节假日错误
						
				  goto Pay_Card_end;	
						
					}				
			}
	else	
			{
					
				Time_Interval_Detection();     //检测时段
					
				if(!btimeseg)				           //不在设定时段内
					{
						
					Beep(4, SHORT_BEEP);
						
					Pay_Carderr_Code = PAY_TIME_INTERVAL_ERR;             //错误代码 时间段错误
						
				  goto Pay_Card_end;	
						
					}
				}					
		}
		
/***********************检查黑名单	*********************************/	
  Back_FindCardno();                     //查找黑名单
		
  if (back_bfindcard)                    //如果有名单，直接退出
			 {			
			//	RS485_Send_Data(ICidbuff ,4);       //测试用				

				Beep(4, SHORT_BEEP);			
				 
				Pay_Carderr_Code = PAY_BACK_ERR;             //错误代码 黑名单错误
				 
				goto Pay_Card_end;		
				}	
					
	
								
/***********************韦根还是控制器读卡	*********************************/
	
	if (stype==1) //控制器读卡
			{				
				if (extvar[0]==0X00)   //如果不需要读写卡内容
						{						
							if (extvar[1]==0X01) //检查密码
									{
										if (!isValidICPW)               //如果密码错误
												{ 
												
//														OLEDPasswordREE();       //OLED显示扇区密码错误
														//OLEDcard();              //显示序列号						    
													
														Beep(4, SHORT_BEEP);	
													
													  Pay_Carderr_Code = PAY_SECTOR_PASSW_ERR;             //错误代码 扇区密码错误
													
				                    goto Pay_Card_end;	
												}											
									}									
																	 
//					  	OLEDPasswordZQ();			 	 //OLED显示扇区密码正确
						//	OLEDcard();            //显示序列号
						//	OLEDName();		           //显示姓名
									
								
							 goto Pay_Card_end;		
//					  	AddRecord(0);			       //存储记录
//							BeginOutput1();					 //继电器输出				
//	            Beep(1, SHORT_BEEP);		 //蜂鸣器发声		


									
						}
				            
				else //需要读写卡内容
						{
							if (isValidICData)       
									{										
											u8 readresult; 

											readresult = AnalyzeSectionData(); //分析扇区数据

											if (readresult != SECTION_RD_SUCC) //扇区数据无效
												{
												//	return 0;
												}
																				
										  
/******************************************刷卡延时检测	****************************************************/			
										//	DS1302_Read_Time();     //读取DS1302的时间						
											if(Time_interval_fun()!=TIME_INTERVAL_SUCC)   //刷卡延时处理
													{									
//														 OLEDClock_delay();                     //OLED显示重复刷卡
//														 OLEDICcard();			                    //显示IC卡内部卡号
														 Beep(4, SHORT_BEEP);						
														 Pay_Carderr_Code = PAY_DELAYED_ERR;             //错误代码 数卡延时错误
														 goto Pay_Card_end;	
													}		
/*******************************************************************************************************/	
																				
										  ProcessICCard();          //处理IC卡块数据
														
//											OLEDPasswordZQ();			    //OLED显示扇区密码正确
								//			OLEDcard();              //显示序列号									
								//		  OLEDName();		            //显示姓名
//											Beep(1, SHORT_BEEP);				
									
											BeginOutput1();		
									}
							else
									{
//										OLEDSector_Read_Failure();   //OLED显示扇区读取失败
//										OLEDcard();                  //显示序列号
										Beep(4, SHORT_BEEP);	
										
										Pay_Carderr_Code = PAY_SECTOR_PASSW_ERR;             //错误代码 读写扇区错误
				            goto Pay_Card_end;										
									}												
				    }
			}
	
	else //韦根读卡，无法检验密码
			{
		//		Beep(1, SHORT_BEEP);
				

      Pay_Carderr_Code = PAY_OK; 				
			 }	
			
		 Pay_Card_end:                //刷卡结束

//	idcycleflag =1;      //重复数卡间隔计数开始  2019-02-21
			 idcycle = 0;
}




/****************************管理卡设置*************************************/
void ProcessSettingByCard(void)

{
	
// u8  blk0[BLOCK_SIZE];   //0块
// u8  blk1[BLOCK_SIZE];   //1块
// u8  blk2[BLOCK_SIZE];   //2块
// u8  blk3[BLOCK_SIZE];   //3块
	

//SendString(blk0 ,BLOCK_SIZE);

//SendString(blk6 ,3);
//	
//SendString(blk1 ,BLOCK_SIZE);
	
//SendString(blk6 ,3);

//SendString(blk2 ,BLOCK_SIZE);

//	SendString(blk6 ,3);
	
//SendString(blk3 ,BLOCK_SIZE);	
	
//ProcessICCard();
	
}



/****************************************************************/
//找到要进行读写的卡
/****************************************************************/
 u32 FindICCard(void)
	{
		u8 ucArray_ID [ 4 ];  //先后存放IC卡的类型和UID(IC卡序列号)
		u8 ucStatusReturn;    //返回状态

		//PcdAntennaOn();//开启天线

		isAdmin = 0;
		isICSetting = 0;
		isValidICPW = 0;            //IC卡扇区密码校验标志
		isValidICData = 0;          //读取到块数据


			if ( ( ucStatusReturn = PcdRequest ( PICC_REQALL, ucArray_ID ) ) != MI_OK )  //寻卡
							
				ucStatusReturn = PcdRequest ( PICC_REQALL, ucArray_ID );	//若失败再次寻卡
						 if(	ucStatusReturn!=	MI_OK )
						 {
						 return 0;
						 }
					
									//防冲突
				ucStatusReturn	 =  PcdAnticoll ( ucArray_ID );
							if (ucStatusReturn != MI_OK)
							{
								return 0;
							}
							
					//选定卡片
			 ucStatusReturn    =  PcdSelect ( ucArray_ID );  
						if (ucStatusReturn != MI_OK)
						{
							return 0;
						}

				MyStrCPY(idbuff, ucArray_ID, 4);//取卡号	
						
				ReadSectionData(isection);//读扇区数据			
							
	//    if (isValidICData)    ProcessSettingByCard();//处理卡设置参数  (管理卡)
							
	//      HexToStr(cardbuff,ucArray_ID, 4);//将四位序列号转换为8位字符串形式	
									
				if (!isValidICPW)               //如果密码错误
				{ 														            													
						return 0;
				}				
						
				return 1;		
	 }



/****************************************************************/
//读扇区数据
/****************************************************************/
 
void ReadSectionData(u8  isec)
{
	u8  blk[BLOCK_SIZE];

	if ((isec == 0) || (isec >= SUM_SECTIONS))   
	{
		return ;
	}
	
	GetPassword(cardPW);  //获取读写密码。
	//校验A密码
		
if (PcdAuthState(PICC_AUTHENT1A, isec*4+3, cardPW , idbuff) != MI_OK)	
		{
			
			return ;
		}
	
	isValidICPW = 1; //密码正确

	//读第0块数据
	if (PcdRead( isec * 4 + 0 ,blk ) != MI_OK)
	{
		return ;
	}
	MyStrCPY(blk0, blk, BLOCK_SIZE);

	//读第1块数据
	if (PcdRead( isec * 4 + 1 ,blk ) != MI_OK)
	{
		return ;
	}
	MyStrCPY(blk1, blk, BLOCK_SIZE);

	//读第2块数据
	if (PcdRead( isec * 4 + 2 ,blk ) != MI_OK)
	{
		return ;
	}
	MyStrCPY(blk2, blk, BLOCK_SIZE);

	//读第3块数据
	if (PcdRead( isec * 4 + 3 ,blk ) != MI_OK)
	{
		return ;
	}
	MyStrCPY(blk3, blk, BLOCK_SIZE);

	
	isValidICData = 1;  //块数据读取成功

}




//void ReadSectionData(u8  isec)
//{
//	u8  blk[BLOCK_SIZE];
//  u8  guangqipass[PASSWORD_SIZE]={0x22,0x38,0x22,0x93,0x20,0x12};
//	
//	u32 isec1=2;

//	//// 检查读写扇区是否0扇区或超出了16个扇区
//	if ((isec1 == 0) || (isec1 >= SUM_SECTIONS))   
//	{
//		return ;
//	}
//	
//	GetPassword(cardPW);  //获取读写密码。

// 
//	//校验A密码
//	if (PcdAuthState(PICC_AUTHENT1A, isec1*4+3, guangqipass , idbuff) != MI_OK)	
//	{
//		return ;
//	}
//	isValidICPW = 1; //密码正确

//	//读第0块数据
//	if (PcdRead( isec1 * 4 + 0 ,blk ) != MI_OK)
//	{
//		return ;
//	}
//	MyStrCPY(blk0, blk, BLOCK_SIZE);

//	//读第1块数据
//	if (PcdRead( isec1 * 4 + 1 ,blk ) != MI_OK)
//	{
//		return ;
//	}
//	MyStrCPY(blk1, blk, BLOCK_SIZE);

//	//读第2块数据
//	if (PcdRead( isec1 * 4 + 2 ,blk ) != MI_OK)
//	{
//		return ;
//	}
//	MyStrCPY(blk2, blk, BLOCK_SIZE);

//	//读第3块数据
//	if (PcdRead( isec1 * 4 + 3 ,blk ) != MI_OK)
//	{
//		return ;
//	}
//	MyStrCPY(blk3, blk, BLOCK_SIZE);

//	isValidICData = 1;  //块数据读取成功
//}









