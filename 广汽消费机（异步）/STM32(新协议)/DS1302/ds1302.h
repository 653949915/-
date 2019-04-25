#ifndef __DS1302_H
#define __DS1302_H
#include "sys.h"

extern  u8 time_buf[8]; 

//IO方向设置
#define DS1302_IO_IN()  {GPIOE->CRL&=0XFFFF0FFF;GPIOE->CRL|=0X00008000;}         
#define DS1302_IO_OUT() {GPIOE->CRL&=0XFFFF0FFF;GPIOE->CRL|=0X00003000;}


//IO操作函数									   
#define	DS1302_DATA_OUT PEout(3) //数据端口	PB1 
#define	DS1302_DATA_IN  PEin(3)  //数据端口	PB1 

#define	DS1302_SCK  PEout(4)       //SCKPB0
#define	DS1302_RST  PEout(2)       //RSTPB10

//DS1302地址定义
#define ds1302_sec_add			  0x80		//秒数据地址
#define ds1302_min_add			  0x82		//分数据地址
#define ds1302_hr_add			    0x84		//时数据地址
#define ds1302_date_add			  0x86		//日数据地址
#define ds1302_month_add		  0x88		//月数据地址
#define ds1302_day_add			  0x8a		//星期数据地址
#define ds1302_year_add			  0x8c		//年数据地址
#define ds1302_control_add		0x8e		//控制数据地址
#define ds1302_charger_add		0x90 		//涓流充电		 
#define ds1302_clkburst_add		0xbe

void DS1302_Init(void);
void DS1302_Write_Byte(u8 addr, u8 data);
u8 DS1302_Read_Byte(u8 addr);
void DS1302_Write_Time(u8 *time_buftx);
void DS1302_Read_Time(void);
void DS1302_Get_Time(u8 *time);
void SetNowTime(u8 *p) ;//设置当前时间
void DS1302_Get_sysTime(u8 *systime) ;
#endif
