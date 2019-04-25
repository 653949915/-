#ifndef __TIMER_H
#define __TIMER_H
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途

//定时器 驱动代码	   

//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////   


void TIM3_Int_Init(u16 arr,u16 psc);
 void timedelay_s(u8 t);
void TIM7_Int_Init(u16 arr,u16 psc);	 
 void TIM2_NVIC_Configuration(void);
void TIM2_Configuration(void);
#endif
