#include "Head.h"


//---------------------------------------------------------
/**********************************************************
//设置读写扇区与密码：01FFFFFFFFFFFF
**********************************************************/
void SetPassword(u8 *pw,u8 set)
{
	u8 i;

	isection = pw[0];
	
	
	for (i = 0; i < PASSWORD_SIZE; i++)
	{
		password[i] = pw[i+1];
	}
	
	AT24CXX_WriteOneByte(SECTION_POS, isection);//写序列号
	
	AT24CXX_Write(PASSWORD_ST,password  , PASSWORD_SIZE);//写密码
	
	InitPassword();  //初始化读写扇区与密码
}

/**********************************************************
//初始化读写扇区与密码
**********************************************************/
void InitPassword(void)
{
	u8 i;

	isection= AT24CXX_ReadOneByte(SECTION_POS);

	for (i = 0; i < PASSWORD_SIZE; i++)
	{
		password[i] = AT24CXX_ReadOneByte(PASSWORD_ST + i);
	}
}

/**********************************************************
//获取读写密码。
**********************************************************/
void GetPassword(u8 *pw)
{
//	u8 i;

//	for (i = 0; i < 6; i++) 
//	{ 
//		pw[i] = 0xFF; 
//	}

	MyStrCPY(pw, password, 6);
	
	
//	if (!MyStrEQ(password, pw, 6)) //非默认密码(FF FF FF FF FF FF)
//	{
//		for (i = 0; i < 6; i++) 
//		{ 
//			pw[i] = password[i] ^ PasswordMask[i];//0,1,2,3用CRC速度有点慢！
//		}		
//	}
}

void GetIsectiond(u8 *pw)
{
//	u8 i;

//	for (i = 0; i < 6; i++) 
//	{ 
//		pw[i] = 0xFF; 
//	}

	MyStrCPY(pw, password, 6);
	
	
//	if (!MyStrEQ(password, pw, 6)) //非默认密码(FF FF FF FF FF FF)
//	{
//		for (i = 0; i < 6; i++) 
//		{ 
//			pw[i] = password[i] ^ PasswordMask[i];//0,1,2,3用CRC速度有点慢！
//		}		
//	}
}






