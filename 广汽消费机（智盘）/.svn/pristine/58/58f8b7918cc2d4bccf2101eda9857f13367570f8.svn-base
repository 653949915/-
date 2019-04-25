#include "Head.h"


#include "Consum_Config.h"



 uint8_t   Machine_category[2] ={0};             //机器类别
 
 uint8_t	 Fixed_consum_Moneybuf[16];            //定值扣费时金额
 
 uint8_t	 Fixed_consum_Timerbuf[32];            //定值扣费时间段	
 
 uint8_t	 Carte_consum_Moneybuf[18];            //菜单扣费金额	
	
 uint8_t	 Consum_TimerBit[2] ={0};              //消费时段标志	检测当前刷卡时间是否在时段内

 union     EightByte  Consum_Allmoney;            //消费总金额

 uint8_t   Sub_Maximum_Limitbuf[5];              //当次消费限额



/**********************************************************
//保存机器类别
**********************************************************/
void SaveMachine_Category(void)
{
	AT24CXX_Write(INSTALL_POS_IDX,  Machine_category , 1);    //机器类型
	
	if(Machine_category[0] == 0xff)
	{
	  Machine_category[0] =0x01;	
	}			
}


/**********************************************************
//保存定值扣费金额
**********************************************************/
void SaveFixed_consumption_Money(void)
{
	
	AT24CXX_Write(FIXED_CONSUMPTION_MONEY,  Fixed_consum_Moneybuf , 8);    //写定值扣费金额
	
}

/**********************************************************
//保存定值扣费时间段
**********************************************************/
void SaveFixed_consumption_Timer(void)
{
	
	AT24CXX_Write(FIXED_CONSUMPTION_TIMER,  Fixed_consum_Timerbuf , 16);    //写定值扣费时间段
	
}


/**********************************************************
//初始化定值扣费金额
**********************************************************/
void InitFixed_consumption_Money(void)
{
	
	AT24CXX_Read(FIXED_CONSUMPTION_MONEY,  Fixed_consum_Moneybuf , 8);    //读定值扣费金额
	
}

/**********************************************************
//初始化消费总额
**********************************************************/
void InitConsumption_All_Money(void)
{
	AT24CXX_Read(CONSUMPTION_ALL_MONEY,  Consum_Allmoney.c , 6);    //
	
//	RS485_Send_Data(Consum_Allmoney.c,	4);
}

/**********************************************************
//保存消费总额
**********************************************************/
void SaveConsumption_All_Money(void)
{

	AT24CXX_Write(CONSUMPTION_ALL_MONEY,  Consum_Allmoney.c , 6);    //
	
//	 RS485_Send_Data(Consum_Allmoney.c,	4);

}

/**********************************************************
//清除消费总额
**********************************************************/
void DeleteConsumption_All_Money(void)
{
	uint8_t  moneybuf[12]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
	
	AT24CXX_Write(CONSUMPTION_ALL_MONEY,  moneybuf , 4);    //
	
	Consum_Allmoney.i =0;
	
}



/**********************************************************
//初始化定值扣费时间段
**********************************************************/
void InitFixed_consumption_Timer(void)
{
	
	AT24CXX_Read(FIXED_CONSUMPTION_TIMER,  Fixed_consum_Timerbuf , 16);    //读定值扣费时间段
	
}


/**********************************************************
//保存菜单扣费金额
**********************************************************/
void SaveCarte_consum_Money(void)
{
	
	AT24CXX_Write(CARTE_CONSUMPTION_MONEY,  Carte_consum_Moneybuf , 18);    //写菜单扣费金额
	
}

/**********************************************************
//初始化菜单扣费金额
**********************************************************/
void InitCarte_consum_Money(void)
{
	
	AT24CXX_Read(CARTE_CONSUMPTION_MONEY,  Carte_consum_Moneybuf , 18);    //读菜单扣费金额
	
}


/**********************************************************
//保存当次消费限额
**********************************************************/
void SaveSub_Maximum_Limit(void)
{
	
	AT24CXX_Write(SBU_MAXIMUM_LIMIT,  Sub_Maximum_Limitbuf , 3);    //写当次消费限额
	
}

/**********************************************************
//初始化当次消费限额
**********************************************************/
void InitSub_Maximum_Limit(void)
{
	
	AT24CXX_Read(SBU_MAXIMUM_LIMIT,  Sub_Maximum_Limitbuf , 3);    //读当次消费限额
	
}




void Consum_Time_Detection(void)       //消费时段检查
{
	u8 i;
	u8 tmp1 , tmp2;
	
  Consum_TimerBit[0] = Consum_TimerBit[1] =0;

	for(i=0;i<8;i++)
	{
		tmp1 = MyStrCMP(time_buf + 4, Fixed_consum_Timerbuf + i*4 , 2);         //扣款时段对比
		tmp2 = MyStrCMP(time_buf + 4, Fixed_consum_Timerbuf + i*4  + 2, 2);
		if ((tmp1 >= 2) && (tmp2 <= 2)) //包含边界
				{
          
					Consum_TimerBit[0] = 1;
					
					Consum_TimerBit[1] = i;
					
					break;
				}													
	}

}


















