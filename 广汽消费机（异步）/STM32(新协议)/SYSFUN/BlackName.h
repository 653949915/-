#ifndef	__BACKNAME_H__
#define	__BACKNAME_H__
#include "sys.h"	

/**********************************************************
//外部变量声明
**********************************************************/
extern  u32  back_bfindcard;
extern  u8   back_curgroup;//0开始
extern  u32  back_groupidx;//1开始
extern  u32  back_groupcount;//0开始
extern  u32  back_commidx;//1开始
extern  u32  back_commcount;//0开始	

/**********************************************************
//外部函数声明
**********************************************************/
void Back_InitName(void);
u16  Back_GetGroupCount(void);
void Back_SaveGroupCount(void);
void Back_SaveCommCount(void);
void Back_FindCardno(void);
void Back_AddCardno(void);
void Back_DelCardno(void);
void Back_DelAllCardno(void);
extern u8 Back_DelOneCardno(u8 *cardno);
extern u8 Back_AddOneCardno(u8 *cardno);
void Back_AddorDelCardno(void);

u16 Back_GetCommCount(void);
unsigned long Back_GetGroupAddress(void);


#endif


