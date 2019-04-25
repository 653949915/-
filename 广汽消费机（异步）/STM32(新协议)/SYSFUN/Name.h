#ifndef	__NAME_H__
#define	__NAME_H__
#include "sys.h"	

/**********************************************************
//�ⲿ��������
**********************************************************/
extern  u32  bfindcard;
extern  u8   curgroup;//0��ʼ
extern  uint32_t  groupidx;//1��ʼ
extern  uint32_t  groupcount;//0��ʼ
extern  uint32_t  commidx;//1��ʼ
extern  uint32_t  commcount;//0��ʼ	

/**********************************************************
//�ⲿ��������
**********************************************************/
void InitName(void);
u32 GetGroupCount(void);
void SaveGroupCount(void);
void SaveCommCount(void);
void FindCardno(void);
void AddCardno(void);
void DelCardno(void);
void DelAllCardno(void);
u8 DelOneCardno(u8 *cardno);
u8 AddOneCardno(u8 *cardno);
void AddorDelCardno(void);
uint32_t GetGroupAddress(void);
u16 GetCommCount(void);




#endif


