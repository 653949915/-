#ifndef	__DEFAULT_H__
#define	__DEFAULT_H__
#include "sys.h"	
/**********************************************************
//�ⲿ��������
**********************************************************/
extern  u8 isection;
extern  u8  password[];

/**********************************************************
//�ⲿ��������
**********************************************************/
void LoadDefaultValue(void);

void LoadnNetDefaultValue(void);

void SetPassword(u8 *pw, u8 stype);

void Initnewdate_addr(void);

void  LoadnEC20DefaultValue(void);
#endif



