#include "Head.h"

/**********************************************************
//变量定义
**********************************************************/

u8  machno[MACH_SIZE]; //机号 4字节

u8  machno_ASCII[8];   //机号ASCII 8字节




/**********************************************************
//读取机号
**********************************************************/
void InitMachno(void)
{

	AT24CXX_Read(MACH_ST, machno , MACH_SIZE);   	//读机号

	HexToStr(machno_ASCII,  machno,  4);	
	 
}

/**********************************************************
//保存机号
**********************************************************/
void SaveMachno(u8 *m)
{
	u8 Machno_mm[8];

	Machno_mm[0] = m[0];  //
	Machno_mm[1] = m[1];  //
	Machno_mm[2] = m[2];  //
	Machno_mm[3] = m[3];  //	
 AT24CXX_Write(MACH_ST, Machno_mm , MACH_SIZE);   	//写机号
	
	InitMachno();

}




