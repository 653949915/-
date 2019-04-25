#ifndef	__CONSUM_CONFIG_H__
#define	__CONSUM_CONFIG_H__

#include "sys.h"

//#define KEY_SIZE 20

/**********************************************************
//外部变量声明
**********************************************************/

extern  uint8_t   Machine_category[] ;                   //机器类别

extern u8  UserBalance[];	  //卡上余额
 
extern u8  Consum_Amount[] ;	  //消费金额
 
extern uint8_t	Fixed_consum_Moneybuf[];                    //定值扣费时金额
 
extern uint8_t	Fixed_consum_Timerbuf[];                    //定值扣费时间段	
 
extern uint8_t	 Carte_consum_Moneybuf[];            //菜单扣费金额	
 
extern uint8_t	 Consum_TimerBit[];                   //消费时段标志	检测当前刷卡时间是否在时段内

extern union     EightByte  Consum_Allmoney;              //消费总金额

extern uint8_t   Sub_Maximum_Limitbuf[];              //当次消费限额

extern uint8_t   RefundMoneybuf[] ;             //退款金额

extern uint8_t   RefundICcardbuf[] ;             //退款卡号
/**********************************************************
//外部函数声明
**********************************************************/


void SaveMachine_Category(void);         //保存机器类别
void SaveFixed_consumption_Money(void);  //保存定值扣费金额
void SaveFixed_consumption_Timer(void);  //保存定值扣费时段
void InitFixed_consumption_Money(void);  //初始化定值扣费金额
void InitFixed_consumption_Timer(void);  //初始化定值扣费时段
void InitCarte_consum_Money(void);      //初始化菜单扣费金额
void SaveCarte_consum_Money(void);      //保存菜单扣费金额

void Consum_Time_Detection(void);       //消费时段检查

void DeleteConsumption_All_Money(void); //清除消费总额
void SaveConsumption_All_Money(void);   //保存消费总额
void InitConsumption_All_Money(void);   //初始化消费总额
void SaveSub_Maximum_Limit(void);      //保存当次消费限额
void InitSub_Maximum_Limit(void);      //初始化当次消费限额





#endif
