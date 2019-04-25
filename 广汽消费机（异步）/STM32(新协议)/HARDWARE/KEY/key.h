#ifndef __KEY_H
#define __KEY_H	 
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 

//按键驱动代码	   

//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////   	 
	 
typedef union         
{
  u8 byte;
  struct
   {
     u8 B0:1;
     u8 B1:1;
     u8 B2:1;
     u8 B3:1;
     u8 B4:1;
     u8 B5:1;
     u8 B6:1;
     u8 B7:1;
   }BITS;
}BYTE_T;
                                    //       00000000
//#define KEY_LINEOUT_ROWIN()  { GPIOD->CRH&=0xFFFF0000 ;GPIOD->CRH|=0x00008888 ;GPIOD->CRH&=0xFFFF0000 ;GPIOD->CRH|=0x00003333 ;}  
//#define KEY_LINEIN_ROWOUT()  { GPIOD->CRH&=0xFFFF0000 ;GPIOD->CRH|=0x00003333 ;GPIOD->CRH&=0xFFFF0000 ;GPIOD->CRH|=0x00008888 ;}

//#define KEY_LINEOUT_ROWIN()  { GPIOD->CRH&=0x00000000 ;GPIOD->CRH|=0x33338888 ;}  
//#define KEY_LINEIN_ROWOUT()  { GPIOD->CRH&=0x00000000 ;GPIOD->CRH|=0x88883333 ;}

#define KEY_LINEOUT_ROWIN()  { GPIOD->CRH&=0x00000000 ;GPIOD->CRH|= 0x88883333;}  
#define KEY_LINEIN_ROWOUT()  { GPIOD->CRH&=0x00000000 ;GPIOD->CRH|= 0x33338888;}

#define LONG_TIME  30
#define KEY_LINE    GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15
#define KEY_ROW     GPIO_Pin_8 |GPIO_Pin_9 |GPIO_Pin_10|GPIO_Pin_11

void KEY_Init(void);//IO初始化
u8 Keyscan(void);
#endif




