#include "Head.h"

/**********************************************************
//变量定义
**********************************************************/
static u32 back_bgroupfull;     //分组满 标志
 u32       back_bfindcard;      //名单里面发现卡 标志
 u8        back_curgroup;       //0开始   分组号
 u32       back_groupidx;//1开始    分组区名单编号
 u32       back_groupcount;//0开始  分组区名单数量
 u32       back_commidx;//1开始     公共区名单编号
 u32       back_commcount;//0开始   公共区名单数量

//---------------------------------------------------------

/**********************************************************
//保存分组名单数！
**********************************************************/
void Back_SaveGroupCount(void)
{
	u8 tmp[2];

	tmp[0] = (unsigned char)((back_groupcount & 0xFFFF) >> 8);//高位
	tmp[1] = (unsigned char)(back_groupcount & 0xFF);//低位

	AT24CXX_Write(BACK_NUM_START + back_curgroup * 2, tmp, 2);          //保存组号
}  

/**********************************************************
//读取黑名单 单组分组名单数
**********************************************************/
u16 Back_GetGroupCount(void)
{
	u8 tmp[2];
	//union TwoByte ic2;
	

	AT24CXX_Read(BACK_NUM_START + back_curgroup * 2, tmp, 2);        //读取组号
	//I2CPageRead(NUM_START + curgroup * 2, 2, &(ic2.c[0]));
	return (tmp[0] * 256 + tmp[1]);
	//return (ic2.i);
}

/**********************************************************
//保存公共区名单数
**********************************************************/
void Back_SaveCommCount(void)
{
	u8 tmp[2];


	tmp[0] = (unsigned char)((back_commcount & 0xFFFF) >> 8);//高位
	tmp[1] = (unsigned char)(back_commcount & 0xFF);//低位

	AT24CXX_Write(BACK_COMM_POS, tmp, 2);
}

/**********************************************************
//读取黑名单公共区名单数！
**********************************************************/
u16 Back_GetCommCount(void)
{
	u8 tmp[2];
 	//union TwoByte ic2; 


	AT24CXX_Read(BACK_COMM_POS, tmp, 2);
	//I2CPageRead(COMM_POS, 2, &(ic2.c[0]));

	return (tmp[0] * 256 + tmp[1]);
	//return (ic2.i);
}  

/**********************************************************
//黑名单组起始地址
**********************************************************/
unsigned long Back_GetGroupAddress(void)
{
	unsigned long i;

	i  = back_curgroup;         //分组号  29组中其中一组 
	i *= BACK_GROUP_SPACE;           //组空间*组号
	i += BACK_GROUP_ST;              //再加上名单起始地址

	return (i);
	
	
}

/**********************************************************
//黑名单公共区名单数
**********************************************************/
void Back_InitName(void)
{
	back_commcount = Back_GetCommCount();
} 

/**********************************************************
//确定黑名单分组
**********************************************************/
void Back_MakeGroup(void)
{

	back_commidx = 0;
	back_groupidx = 0;

	back_bfindcard = 0;
	back_bgroupfull = 0;	

	//curgroup = idbuff[CARD_SIZE-1] % GROUP_NUM;
	back_curgroup = GetSum(idbuff, CARD_SIZE) % BACK_GROUP_NUM;   //IC卡序列号之和除组数 =分组号
	back_groupcount = Back_GetGroupCount(); //读单组名单数量

	if (back_groupcount == BACK_GROUP_RECORD) //如果分组名单数量已满  
	{
		back_bgroupfull = 1;
	}
}  

/**********************************************************
//寻找黑名单卡号
**********************************************************/
void Back_FindCardno(void)
{
	u16  i,addr;
	u8 tmpcard[CARD_SIZE];


	Back_MakeGroup();//很关键！  //确定分组

	//组内查询--------------------------
	addr = Back_GetGroupAddress(); //组起始地址
	for (i = 0; i < back_groupcount; i++)
	{
		//CLR_DOG();			
		AT24CXX_Read(addr,tmpcard ,  CARD_SIZE);

		if (MyStrEQ(idbuff, tmpcard, CARD_SIZE)) //找到卡号
			 { 
				back_bfindcard = 1;           
				back_groupidx = i + 1; 
				return; 
				}

		addr += NAME_SIZE;//下一名单
	}

	//公共区内查询--------------------------------
	if (back_bgroupfull)//组内没找到且组满了，在公共区找
	{
		addr = BACK_GROUP_END_ST;//开始地址
		for (i = 0; i < back_commcount; i++)
		{
			//CLR_DOG();			
			AT24CXX_Read(addr,tmpcard  , CARD_SIZE  );
	
			if (MyStrEQ(idbuff, tmpcard, CARD_SIZE)) //找到卡号
			{ 
				back_bfindcard = 1;
				back_commidx = i + 1; 
				return; 
			}

			addr += NAME_SIZE;//下一名单
		}
	}
} 


/**********************************************************
//删除黑名单一张卡。影响数量！
**********************************************************/
u8 Back_AddOneCardno(u8 *cardno)
{


	MyStrCPY(idbuff, cardno, CARD_SIZE);

	Back_FindCardno();

	if (back_bfindcard) 
	{ 	
		
		return 0; 
	}
	else 
	{ 
		Back_AddCardno();	
		
		return 1; 
	}
}


/**********************************************************
//增加黑名单一张卡号
**********************************************************/
void Back_AddCardno(void)
{
	u32 addr;

	if (back_bgroupfull) //分组满，增加到公共区
	{
		if (back_commcount == BACK_COMM_SIZE) //公共区满
		{
			ERR_BEEP();
			return;
		}
		addr = BACK_COMM_ST + back_commcount * NAME_SIZE;
		back_commcount++;
		Back_SaveCommCount();
	}

	else//增加到组内
	{ 
		addr = Back_GetGroupAddress() + back_groupcount * NAME_SIZE;
		back_groupcount++;
		Back_SaveGroupCount();
	}

	AT24CXX_Write(addr,idbuff ,CARD_SIZE  );//保存卡号

}

/**********************************************************
//黑名单公共区是否有分组卡号。仅供删除单张卡号时调用！
**********************************************************/
u32 Back_CommFindCardno(u8 *back_cardno)
{
	u32  i;
	u32  addr;
	u8 tmpcard[NAME_SIZE];


	addr = BACK_GROUP_END_ST;//开始地址		 
	for (i = 0; i < back_commcount; i++)
	{
		//CLR_DOG();
		AT24CXX_Read(addr,back_cardno ,NAME_SIZE );

		if ((GetSum(back_cardno, CARD_SIZE) % BACK_GROUP_NUM) == back_curgroup)
		//if ((cardno[CARD_SIZE-1] % GROUP_NUM) == curgroup) //当前卡属于当前组
		{
			//读最后一张卡
			addr = back_commcount - 1;
			addr = BACK_GROUP_END_ST + addr * NAME_SIZE;	 
			AT24CXX_Read(addr,tmpcard ,NAME_SIZE );
		
			//用最后一张卡覆盖要移走的卡
			addr = i;
			addr = BACK_GROUP_END_ST + addr * NAME_SIZE;
			//cont_wr24cxxx(addr, NAME_SIZE, tmpcard);
			
			AT24CXX_Write(addr,tmpcard , NAME_SIZE);

			back_commcount--;
			Back_SaveCommCount();

			return 1;
		}

		addr += NAME_SIZE;//下一名单
	}

	return 0;
} 

/**********************************************************
//删除黑名单一张卡号
**********************************************************/
void Back_DelCardno(void)
{
	u16  addr,staddr;
	u8 tmpcard[NAME_SIZE];

	if (back_commidx > 0) //要删除的卡号在公共区
	{
		//读最后一张卡
		addr = back_commcount - 1;
		addr = BACK_COMM_ST + addr * NAME_SIZE;	 
		AT24CXX_Read(addr,tmpcard ,  NAME_SIZE);
	
		//用最后一张卡覆盖要删除的卡
		addr = back_commidx - 1;
		addr = BACK_COMM_ST + addr * NAME_SIZE;
		//cont_wr24cxxx(addr, NAME_SIZE, tmpcard);
		AT24CXX_Write(addr,tmpcard ,NAME_SIZE );

		back_commcount--;
		Back_SaveCommCount();
	}

	else //要删除的卡号在分组内
	{
		if (Back_CommFindCardno(tmpcard)) //公共区内有分组类卡号
		{
			addr = back_groupidx - 1;
			addr = Back_GetGroupAddress() + addr * NAME_SIZE;
			//cont_wr24cxxx(addr, NAME_SIZE, tmpcard);
			AT24CXX_Write(addr,tmpcard ,NAME_SIZE );
		}

		else 
		{
			staddr = Back_GetGroupAddress();

			//读最后一张卡
			addr = back_groupcount - 1;
			addr = staddr + addr * NAME_SIZE;	 
			AT24CXX_Read(addr,tmpcard ,NAME_SIZE );
		
			//用最后一张卡覆盖要删除的卡
			addr = back_groupidx - 1;
			addr = staddr + addr * NAME_SIZE;
			//cont_wr24cxxx(addr, NAME_SIZE, tmpcard);
			AT24CXX_Write(addr,tmpcard ,NAME_SIZE );
	
			back_groupcount--;
			Back_SaveGroupCount();
		}
	} 
	
}

/**********************************************************
//删除全部卡号
**********************************************************/
void Back_DelAllCardno(void)
{
	u8  i;
	u8  tmp[BACK_GROUP_NUM * 2];


	for	(i = 0; i < BACK_GROUP_NUM * 2; i++)
	{
		tmp[i] = 0x00;
	} 
	AT24CXX_Write(BACK_NUM_START, tmp ,BACK_GROUP_NUM * 2 ); 	

	back_commcount = 0;       //公共区名单数量=0
	
	Back_SaveCommCount();     //保存公共区名单数
} 

/**********************************************************
//删除黑名单一张卡。影响数量！
**********************************************************/
u8 Back_DelOneCardno(u8 *cardno)
{


	MyStrCPY(idbuff, cardno, CARD_SIZE);

	Back_FindCardno();

	if (back_bfindcard) 
	{ 	
		Back_DelCardno();	
		return 1; 
	}
	else 
	{ 
		return 0; 
	}
}

/**********************************************************
//增加或删除黑名单卡号
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




