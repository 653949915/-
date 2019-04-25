#include "Head.h"
#include <ctype.h>

/**********************************************************
//常量定义
**********************************************************/

/**********************************************************
//字符串相等比较。1相等，0不等
**********************************************************/
u32 MyStrEQ(u8 *a, u8 *b, u16 ilen)
{
	u16 i;

	for (i = 0; i < ilen; i++)
	{
		if (a[i] != b[i]) return 0;
	}

	return 1;
}

/**********************************************************
//字符串赋值。d目的字符串，r源字符串
**********************************************************/
void  MyStrCPY(uint8_t *d, uint8_t *r, u16 ilen)
{
	u16 i;

	for (i = 0; i < ilen; i++)
	{
		d[i] = r[i];
	}
}

/**********************************************************
//返回按字节XOR校验操作结果
**********************************************************/
u8  GetXOR(uint8_t *ptr, uint32_t len)
{
	uint32_t i,r;

	r = 0;
	for (i = 0; i < len; i++)
	{
		r ^= ptr[i];
	}

	return r;
}

/**********************************************************
//字符串比较。a<b 1小于，a=b   2 相等2；a>b 3大于
**********************************************************/
u8 MyStrCMP(u8 *a, u8 *b, u8 len)
{
	u8 i;

	for (i = 0; i < len; i++)
	{
		if (a[i] < b[i]) { return 1; }
		else if (a[i] > b[i]) { return 3; }
	}

	return 2;
}

/**********************************************************
//蜂鸣器发声。持续 idelay 毫秒；打开与关闭匹配
**********************************************************/
void Beep(u8 count, u32 idelay)
{
	while (count--)
	{
		OpenSPK();//打开蜂鸣器
		delay_ms(idelay);//持续 idelay ms
		CloseSPK();//关闭蜂鸣器
		delay_ms(idelay);//延时
		
//		if (count) //最后一次发声不用延时
//		{
//			delay_ms(SHORT_BEEP);//延时
//		}	
		
	}
}


/**********************************************************
//蜂鸣器发声。持续 idelay 毫秒；打开与关闭匹配
**********************************************************/
void LED1_fun( u8 count, u32 idelay)
{
	while (count--)
	{
		LED1 =1;              //关灯
		delay_ms(idelay);    //持续 idelay ms
		LED1 =0;          //开灯
		delay_ms(idelay);    //延时
	}
	
}


/**********************************************************
//蜂鸣器发声。持续 idelay 毫秒；打开与关闭匹配
**********************************************************/
void LED2_fun( u8 count, u32 idelay)
{
	while (count--)
	{
		LED2 =1;              //关灯
		delay_ms(idelay);    //持续 idelay ms
		LED2 =0;          //开灯
		delay_ms(idelay);    //延时
	}
	
}

/**********************************************************
//求和
**********************************************************/
u8 GetSum(u8 *b, u8 icount)
{
	u8 i, j; 

	j = 0;
	
	for (i = 0; i < icount; i++)
	{
		j += b[i]; 
	} 
	 
	return j;
}

/*******************************************************************************
// C prototype : void HexToStr(BYTE *pbDest, BYTE *pbSrc, int nLen)
// parameter(s): [OUT] pbDest - 存放目标字符串
// [IN] pbSrc - 输入16进制数的起始地址
// [IN] nLen - 16进制数的字节数
// return value: 
// remarks : 将16进制数转化为字符串
*******************************************************************************/
void HexToStr(unsigned char *pbDest,  unsigned char *pbSrc,  unsigned char nLen)
{
	char	ddl,ddh;
	int i;

	for (i=0; i<nLen; i++)
	{
	  ddh = 48 + pbSrc[i] / 16;
	  
	  ddl = 48 + pbSrc[i] % 16;
	  
	  if (ddh > 57) ddh = ddh + 7;
	  
	  if (ddl > 57) ddl = ddl + 7;
	  
	  pbDest[i*2] = ddh;
	  
	  pbDest[i*2+1] = ddl;
	}

	pbDest[nLen*2] = '\0';
}




/*
// C prototype : void StrToHex(BYTE *pbDest, BYTE *pbSrc, int nLen)
// parameter(s): [OUT] pbDest - 输出缓冲区
//	[IN] pbSrc - 字符串
//	[IN] nLen - 16进制数的字节数(字符串的长度/2)
// return value: 
// remarks : 将字符串转化为16进制数
*/
void StrToHex(u8 *pbDest, u8 *pbSrc, int nLen)
{
char h1,h2;
u8 s1,s2;
int i;

for (i=0; i<nLen; i++)
{
h1 = pbSrc[2*i];
h2 = pbSrc[2*i+1];

s1 = toupper(h1) - 0x30;
if (s1 > 9) 
s1 -= 7;

s2 = toupper(h2) - 0x30;
if (s2 > 9) 
s2 -= 7;

pbDest[i] = s1*16 + s2;
}
}

/*
// C prototype : void StrToHex(BYTE *pbDest, BYTE *pbSrc, int nLen)
// parameter(s): [OUT] pbDest - 输出缓冲区
//	[IN] pbSrc - 字符串
//	[IN] nLen - 10进制数的字节数(字符串的长度/2)
// return value: 
// remarks : 将字符串转化为10进制数
*/
void StrTodec(u8 *pbDest, u8 *pbSrc, int nLen)
{
char h1,h2;
u8 s1,s2;
int i;

for (i=0; i<nLen; i++)
{
h1 = pbSrc[2*i];
h2 = pbSrc[2*i+1];

s1 = toupper(h1) - 0x30;
if (s1 > 9) 
s1 -= 7;

s2 = toupper(h2) - 0x30;
if (s2 > 9) 
s2 -= 7;

pbDest[i] = s1*10 + s2;
}
}




//-------------	函数信息 ------------------------------------------
// 函 数 名 : HextoBCD
// 函数描述 : 十六进制码转换成 BCD 码
// 入口参数 : temp: 转化的十进制码
//	返	回 : 转化后的 BCD 码
//	作	者 :
//	日	期 : 2006.11.24
//	说	明 :
//		
//---------------------------------------------------------------


u8 HextoBCD( u8 temp )
{

return ( (temp/16)*10 + temp%16 ) ;

}




/**********************************************************
//求ASCII码值
**********************************************************/
u8 GetASCIIValue(u8 *inValue ,int nLen)
{
	int i;
	char h1,h2;
	for (i=0; i<nLen; i++)
{
h1 = (inValue[i] >> 4) * 10 ;
h2 = inValue[i] & 0x0F;
	
}
	return h1+h2;
}


/**********************************************************
//求BCD码值
**********************************************************/
void GetBCDValue1(u8 *outValue, u8 *inValue,int nLen)
{

	int i;
	char h1;
	for (i=0; i<nLen; i++)
{
h1 = ((inValue[i] / 10) << 4) |	(inValue[i] % 10);
	
	outValue[i]= h1;
}	
	
}

/*******************************************************************************/
// 功能：求权

// 输入： int base	进制基数

//	int times	权级数

// 输出：

// 返回： unsigned long	当前数据位的权//

/*******************************************************************************/
uint32_t power(int base, int times)
{
	int i;

	uint32_t rslt = 1;

	for(i=0; i<times; i++) rslt *= base;

	return rslt;
}
/*******************************************************************************/
// 功能：  BCD 转 10 进制	
//	输入： const unsigned char *bcd	待转换的 BCD 码
//		   int length	BCD 码数据长度
//	输出：		
//	返回： unsigned long	当前数据位的权
//	思路：压缩 BCD 码一个字节所表示的十进制数据范围为 0 ~ 99, 进制为 100
//	先求每个字符所表示的十进制值，然后乘以权
/*******************************************************************************/
uint32_t getBCDtoDec(u8 *bcd, u8 length)
{
	int i, tmp;

	uint32_t dec = 0;

	for(i=0; i<length; i++)
	{
		tmp = ((bcd[i]>>4)&0x0F)*10 + (bcd[i]&0x0F); 

		dec += tmp * power(100, length-1-i);

	}
	return dec;
}



/******************************************************************************/
//  功能：10 进制转 BCD 码

//  输入： int Dec	待转换的十进制数据

//	int length	BCD 码数据长度

//  输出： unsigned char *Bcd	转换后的 BCD 码

//	返回： 0  success

//	思路：原理同 BCD 码转十进制

//  高位在前，低位在后。12345678》》0x12，0x34,0x56,0x78
/******************************************************************************/
void getDectoBCD(u32 Dec, u8 *Bcd, u8 length)
{
	int i;

	int temp;

	for(i=length-1; i>=0; i--)
	{
		temp = Dec%100;

		Bcd[i] = ((temp/10)<<4) + ((temp%10) & 0x0F); Dec /= 100;
	}

}

/*******************************************************************************
/倒转数据
*******************************************************************************/
void turn_4_data(u8*a,u8*b)
{
	a[0]=b[3];
	a[1]=b[2];
	a[2]=b[1];
	a[3]=b[0];
}

/*******************************************************************************
/倒转数据
*******************************************************************************/
void turn_2_data(u8*a,u8*b)
{
	a[0]=b[1];
	a[1]=b[0];

}

/*******************************************************************************
/2个字符型整合成1个整型
*******************************************************************************/
unsigned long separate_value_2_1(u8 *b)
{
	u16 a=0;
	a= b[0]|a;
	a=a<<8;
	a= b[1]|a;
	return a;
}

/*******************************************************************************
/长整型分离成4个字符型
*******************************************************************************/
void separate_value_1_4(u32 a,u8*b)
{
	b[3]= a&0x000000ff;
	
	a=a>>8;
	
	b[2]= a&0x000000ff;
	
	a=a>>8;
	
	b[1]= a&0x000000ff;
	
	a=a>>8;
	
	b[0]= a&0x000000ff;
}

/**********************************************************
//广汽研究院IC卡 卡号转换 
输入：inIC  16进制卡号输入
      OutIC  10进制卡号输出

41 6B A0 29 --> 10513217

**********************************************************/
void  GAEI_IC_Conversion(uint8_t *inIC ,uint8_t *OutIC)
{
	union   FourByte   Icin={0};
	
  MyStrCPY(Icin.c, inIC, 3);        //拷贝姓名

	getDectoBCD(Icin.i,OutIC, 4);
}	


/**********************************************************
//初始化系统参数
**********************************************************/
void InitSysvar(void)
{
	//系统参数
	AT24CXX_Read(SYSVAR_ST, sysvar , SYSVAR_SIZE );
	
	//扩展参数，2014-09-15
	AT24CXX_Read(EXTVAR_ST, extvar , SYSVAR_SIZE);
	
	AT24CXX_Read(CLOCK_DELAY, repea_time , 1);   //刷卡延时
	
	AT24CXX_Read(WHITEYELL, whiteallow , 1);     //是否检查白名单
	
	AT24CXX_Read(INTERVAL_IDX, interval_time , 1);    //数卡间隔延时

	AT24CXX_Read(REL_OUTTIME_IDX,  output_time , 1);   //继电器输出延时
	
	AT24CXX_Read(INSTALL_POS_IDX,  Machine_category , 1);    //机器类型
	
}


/**********************************************************
//保存系统参数
**********************************************************/
void SaveSysvar(u8 * var)
{

	AT24CXX_Write(SYSVAR_ST, var , SYSVAR_SIZE);
	
//	InitSysvar();
}

/**********************************************************
//保存扩展参数
**********************************************************/
void SaveExtvar(u8 * var) 
{
	
	AT24CXX_Write(EXTVAR_ST,var , SYSVAR_SIZE);
//	InitSysvar();
}








































