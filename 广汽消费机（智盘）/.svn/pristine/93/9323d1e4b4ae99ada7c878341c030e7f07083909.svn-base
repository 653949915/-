#ifndef __HEAD_H
#define __HEAD_H


 #define WITH_RC522_FUNC //带RC522功能

// #define WITH_EC20GPS_FUNC //带GPS功能


//#define   LCD12864

#define   WISDOM_PLATE     //智盘

//#define  Door_Access_Machine   //门禁机

//#define   Attendance_machine   //考勤机

#define  Consumer_machine  //消费机

#ifdef  Door_Access_Machine   //门禁机

	#define  MACHINE_CATEGORY     0X20   //机器类别     0X10--考勤    0X20--门禁   0X30--消费  
  
#endif	
	
#ifdef   Attendance_machine   //考勤机

  #define  MACHINE_CATEGORY     0X10   //机器类别     0X10--考勤    0X20--门禁   0X30--消费 
#endif


#ifdef   Consumer_machine    //消费机

  #define  MACHINE_CATEGORY     0X40   //机器类别     0X10--考勤    0X20--门禁   0X30--消费 
	
#endif


/*
通讯版本

*/



#define     Move_Version           //4G版
//#define   Standard_Version     //标准版
//#define   WIFI_Version         //WIFI版



	
#ifdef   Move_Version     //是4g通讯									
									
#elif    Standard_Version   //标准版本		
									
#elif    WIFI_Version      //WIFI版本									 
											 
#endif





#define COMM_MODE      0X08   //通讯模式  0X01--485   0X02--TCPS  0X04--TCPC   0X08--4G

#include <stdio.h>
#include <string.h>	


//硬件外设驱动

#include "led.h"
#include "key.h"
#include "beep.h"
#include "24cxx.h" 
#include "myiic.h"
#include "24cxx_2.h" 
#include "myiic_2.h"
#include "relay.h"
#include "spi.h"
#include "W25QXX.h"
#include "rs485.h"	
#include "wg1.h"
#include "wg2.h"
#include "wdg.h"
#include "Optocoupler.h"
#include "sysrest.h"
#include "rs485.h"	
#include "EC20.h"
#include "stmflash.h"


//crc
#include "crc.h"

//IAP
#include "iap.h"

#include "W5500_Config.h"
#include "W5500.h"	
#include "RJ45CMD.h"
/*app函数头文件*/

#include "RJ45CMD.h"

//系统mingzi
#include "timer.h"
#include "usart.h"
#include "sys.h"
#include "delay.h"
//RC522

#include "rc522_config.h"
#include "rc522_function.h"


//DS1302
#include "DS1302.h"
//GUI
#include "menu.h"
#include "MenuFun.h"

#include "sysvar.h"

//系统功能
#include "keyfun.h"
#include "AT24C256.h"
#include "syscomm.h"
#include "COMCMD.h"
#include "Name.h"
#include "BlackName.h"
#include "CardProcess.h"
#include "Pass.h"
#include "Default.h"
#include "Record.h"
#include "Mach.h"
#include "WIFI.h"	 
#include "Cardrw.h"
#include "Interval.h"
#include "EC20fun.h"
#include "QR_code.h"
#include "speak.h"
#include "Heartbeat.h"
#include "LCD12864.h"
#include "LCD12864_Config.h"
#include "Upload.h"
#include "tm1650.h"
#include "Volume.h"
#include "Consum_Config.h"
#include "IAP_UpData.h"


//#include "43inch_Config.h"

#include "LCD_Dis.h"
#include "LCD_Config.h"

#ifdef   WISDOM_PLATE
 #include "Wisdom_plate.h"
#endif



#define USART1BOUND				115200     //串口1波特率
#define USART2BOUND				9600       //串口2波特率
#define USART3BOUND				9600     //串口3波特率

#ifdef   WISDOM_PLATE     //是智盘
#define USART4BOUND				19200     //串口3波特率
#endif	
	
	
#define TIM3ARR		999     //定时器3的自动重装值  定时1000为100ms 
#define TIM3PSC		7199    //定时器3的预分频值




#endif

