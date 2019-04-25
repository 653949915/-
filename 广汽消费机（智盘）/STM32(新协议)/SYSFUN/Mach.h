#ifndef	__MACH_H__
#define	__MACH_H__ 
#include "sys.h"	
/**********************************************************
//外部变量声明
**********************************************************/
//extern uchar idata machno[];

extern u8  machno[];

extern u8  machno_ASCII[];   //机号ASCII 8字节

extern u8  encodemachno[];

extern u8  TYPE_SIZE ;
extern u8  MACH_TYPE[];

/**********************************************************
//外部函数声明
**********************************************************/
void InitMachno(void);
void SaveMachno(u8 *m);

#endif

