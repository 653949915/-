#include "Head.h"

/**********************************************************
//变量定义
**********************************************************/
 u32             bgroupfull;   //分组满 标志
 u32             bfindcard;    //名单里面发现卡 标志
 u8              curgroup;//0开始   分组号
 uint32_t        groupidx;//1开始    分组区名单编号
 uint32_t        groupcount;//0开始  分组区名单数量
 uint32_t        commidx;//1开始     公共区名单编号
 uint32_t        commcount;//0开始   公共区名单数量

u8 addnamebuff[6]={0X00};            //追加名单

u8 Permission_Periodbuff[2];    //门禁时段权限


//---------------------------------------------------------

/**********************************************************
//保存分组名单数！
**********************************************************/
void SaveGroupCount(void)
{
	u8 tmp[2];

	tmp[0] = (u8 )((groupcount & 0xFFFF) >> 8);//高位
	tmp[1] = (u8 )(groupcount & 0xFF);//低位

	AT24CXX_2_Write(NUM_START + curgroup * 2, tmp, 2);
}  

/**********************************************************
//读取分组名单数
**********************************************************/
u32 GetGroupCount(void)
{
	u8 tmp[2];
	
	AT24CXX_2_Read(NUM_START + curgroup * 2, tmp, 2);

	return (tmp[0] * 256 + tmp[1]);
	
}

/**********************************************************
//保存公共区名单数
**********************************************************/
void SaveCommCount(void)
{
	u8 tmp[2];

	tmp[0] = (unsigned char)((commcount & 0xFFFF) >> 8);//高位
	
	tmp[1] = (unsigned char)(commcount & 0xFF);//低位

	AT24CXX_2_Write(COMM_POS, tmp, 2);
}

/**********************************************************
//读取公共区名单数！
**********************************************************/
u16 GetCommCount(void)
{
	u8 tmp[2];
 	//union TwoByte ic2; 


	AT24CXX_2_Read(COMM_POS, tmp, 2);
	//I2CPageRead(COMM_POS, 2, &(ic2.c[0]));

	return (tmp[0] * 256 + tmp[1]);
	//return (ic2.i);
}  

/**********************************************************
//组起始地址
**********************************************************/
uint32_t GetGroupAddress(void)
{
	uint32_t i;

	i  = curgroup; 
	i *= GROUP_SPACE;
	i += GROUP_ST;

	return (i);
}

/**********************************************************
//公共区名单数
**********************************************************/
void InitName(void)
{
	commcount = GetCommCount();
	
	
} 

/**********************************************************
//确定分组
**********************************************************/
void MakeGroup(void)
{

	commidx = 0;
	groupidx = 0;

	bfindcard = 0;
	bgroupfull = 0;	

	//curgroup = idbuff[CARD_SIZE-1] % GROUP_NUM;
	curgroup = GetSum(idbuff, CARD_SIZE) % GROUP_NUM;   //IC卡序列号之和除组数   分组号
	
	groupcount = GetGroupCount(); //读组名单数量

	if (groupcount == GROUP_RECORD) //如果分组名单数量已满  
	{
		bgroupfull = 1;
	}
}  

/**********************************************************
//寻找卡号
**********************************************************/
void FindCardno(void)
{
	u32  i,addr;
	u8 tmpcard[CARD_SIZE+2];
	
	Permission_Periodbuff[0]= 0X00;
	
//	RS485_Send_Data(idbuff,4);                 //测试用 输出卡号	
	bfindcard=0;
	MakeGroup();//很关键！  //确定分组

	//组内查询--------------------------
	addr = GetGroupAddress(); //组起始地址
	
	for (i = 0; i < groupcount; i++)
	{
		//CLR_DOG();			
		AT24CXX_2_Read(addr,tmpcard , CARD_SIZE+2);	
		
     MyStrCPY(Permission_Periodbuff, tmpcard+4, 2);//取门禁时段	
		
		if (MyStrEQ(idbuff, tmpcard, CARD_SIZE)) //找到卡号
		{ 
			bfindcard = 1;
			groupidx = i + 1; 
			
	//		RS485_Send_Data(tmpcard,6);
			
			return; 
		}

		addr += (NAME_SIZE+2);//下一名单
	}

	//公共区内查询--------------------------------
	if (bgroupfull)//组内没找到且组满了，在公共区找
	{
		addr = COMM_ST;//开始地址
		
		for (i = 0; i < commcount; i++)
		{
			//CLR_DOG();			
			AT24CXX_2_Read(addr,tmpcard  , CARD_SIZE+2);
	
			MyStrCPY(Permission_Periodbuff, tmpcard+4, 2);//取门禁时段	
			
			if (MyStrEQ(idbuff, tmpcard, CARD_SIZE)) //找到卡号
			{ 
				
				bfindcard = 1;
				commidx = i + 1; 
				return; 
			}

			addr += (NAME_SIZE+2);//下一名单
		}
	}
	
} 

/**********************************************************
//增加一张卡号
**********************************************************/
void AddCardno(void)
{
	u32 addr;
	
	if (bgroupfull) //分组满，增加到公共区
	{
		if (commcount == COMM_SIZE) //公共区满
		{
			ERR_BEEP();
			return;
		}
		addr = COMM_ST + commcount * (NAME_SIZE+2);
		commcount++;
		SaveCommCount();
	}

	else//增加到组内
	{ 
		addr = GetGroupAddress() + groupcount * (NAME_SIZE+2);
		groupcount++;
		SaveGroupCount();
	}

	AT24CXX_2_Write1(addr,addnamebuff ,CARD_SIZE+2  );//保存卡号

}


/**********************************************************
//公共区是否有分组卡号。仅供删除单张卡号时调用！
**********************************************************/
u32 CommFindCardno(u8 *cardno)
	{
  u32  i;
	u32  addr;
	u8 tmpcard[NAME_SIZE+2];

	addr = GROUP_END_ST;//开始地址		 
	for (i = 0; i < commcount; i++)
	{
		//CLR_DOG();
		AT24CXX_Read(addr,cardno ,NAME_SIZE+2 );

		if ((GetSum(cardno, CARD_SIZE) % GROUP_NUM) == curgroup)
		//if ((cardno[CARD_SIZE-1] % GROUP_NUM) == curgroup) //当前卡属于当前组
		{
			//读最后一张卡
			addr = commcount - 1;
			addr = COMM_ST + addr * (NAME_SIZE+2);	 
			AT24CXX_Read(addr,tmpcard ,NAME_SIZE+2 );
		
			//用最后一张卡覆盖要移走的卡
			addr = i;
			addr = COMM_ST + addr * (NAME_SIZE+2);
			//cont_wr24cxxx(addr, NAME_SIZE, tmpcard);
			AT24CXX_2_Write1(addr,tmpcard , NAME_SIZE+2);

		
			commcount--;
			SaveCommCount();

			return 1;
		}

		addr += (NAME_SIZE+2);//下一名单
	}

	return 0;	
		
	} 

/**********************************************************
删除一张卡号
**********************************************************/
void DelCardno(void)
{
	u16  addr,staddr;
			
	u8 tmpcard[NAME_SIZE+2]={0X00};

	if (commidx > 0) //要删除的卡号在公共区
	{
		//读最后一张卡
		addr = commcount - 1;
		addr = COMM_ST + addr * (NAME_SIZE+2);	 
		AT24CXX_2_Read(addr,tmpcard ,  NAME_SIZE+2);
	
		//用最后一张卡覆盖要删除的卡
		addr = commidx - 1;
		addr = COMM_ST + addr * (NAME_SIZE+2);
		//cont_wr24cxxx(addr, NAME_SIZE, tmpcard);
				
		AT24CXX_2_Write1(addr,tmpcard ,NAME_SIZE+2 );
		
	  commcount--;
		
		SaveCommCount();
	}

	else //要删除的卡号在分组内
	{
		if (CommFindCardno(tmpcard)) //公共区内有分组类卡号
		{
			addr = groupidx - 1;
			
			addr = GetGroupAddress() + addr * (NAME_SIZE+2);

			AT24CXX_2_Write1(addr,tmpcard ,NAME_SIZE+2 );
		
		
		}

		else 
		{
			staddr = GetGroupAddress();

			//读最后一张卡
			addr = groupcount - 1;
			addr = staddr + addr * (NAME_SIZE+2);	 
			AT24CXX_2_Read(addr,tmpcard ,NAME_SIZE+2);
		
			
			//用最后一张卡覆盖要删除的卡
			addr = groupidx - 1;
			addr = staddr + addr * (NAME_SIZE+2);
			
			AT24CXX_2_Write1(addr,tmpcard ,NAME_SIZE +2);
							
			groupcount--;
			
			SaveGroupCount();
		}
	} 
}

/**********************************************************
//删除全部卡号
**********************************************************/
void DelAllCardno(void)
{
	u8  i;
	
	u8  tmp[GROUP_NUM * 2];

	for	(i = 0; i < GROUP_NUM * 2; i++)
	{
		tmp[i] = 0x00;
	} 
	AT24CXX_2_Write(NUM_START, tmp ,GROUP_NUM * 2 ); 	

	commcount = 0;//公共区
	
	SaveCommCount();
} 

/**********************************************************
//删除一张卡。影响数量！
**********************************************************/
u8 DelOneCardno(u8 *cardno)
{
	MyStrCPY(idbuff, cardno, CARD_SIZE);

	FindCardno();

	if (bfindcard) 
	{ 
		DelCardno();
		return 1; 
	}
	else 
	{ 
		return 0; 
	}
}

/**********************************************************
//增加一张卡。影响数量！
**********************************************************/
u8 AddOneCardno(u8 *cardno)
{
	MyStrCPY(addnamebuff,cardno,CARD_SIZE+2);
	
	MyStrCPY(idbuff, addnamebuff, CARD_SIZE);

	FindCardno();

	if (bfindcard) 
	{ 
		
		return 0; 
	}
	else 
	{ 
		AddCardno();
		return 1; 
	}
}



/**********************************************************
//增加或删除卡号
**********************************************************/
//void AddorDelCardno(void)
//{

//	FindCardno(); //寻卡

//	if (bfindcard) //找到卡
//	{
//		if (badd)
//		{
//			ERR_BEEP(); 
//		}
//		else if (bdel)
//		{
//			DelCardno();
//		}
//	}

//	else //没找到卡
//	{
//		if (badd)
//		{
//			AddCardno();
//		}
//		else if (bdel)
//		{
//			ERR_BEEP();
//		}
//	}
//}




