#ifndef	__INTERVAL_H__
#define	__INTERVAL_H__
#include "sys.h"				


/**********************************************************
//变量定义。
**********************************************************/

extern  u32 btimeseg;             //时段检测通过标志

extern u32 bHoliday;              //节假日标志

extern u32 bChannel;              //通道时段标志

extern u32 bHolitimeseg;          //节假日时段检测通过标志

extern u8 Permission_Period[];    //门禁时段权限缓冲区

extern u8 Passage_Timebuff[];       //通道时段缓冲区

extern u8 Holiday_Vacationsbuff[];       //节假日时段缓冲区

extern u8 Permission_Periodbuff[];    //门禁时段权限
//extern  u8   
//extern  u8   




/**********************************************************
//外部函数声明
**********************************************************/

void Time_Interval_Detection(void);         //检查门禁时段

void HolidayTime_Interval_Detection(void);  //检测节假日时段

void Holiday_Detection(void);               //检测是否节假日

void Channel_Time_Detection(void);          //检测通道时段

void InitTime_Interval_Detection(void);     //初始化门禁时段

void InitPassage_Time(void);                //初始化通道时段

void InitPassage_TimeEnable(void);          //初始化通道使能

void InitHoliday_Vacations(void);           //初始化节假日

extern u8  Check_Passage_Enable(void);      //检测通道时段使能

#endif


