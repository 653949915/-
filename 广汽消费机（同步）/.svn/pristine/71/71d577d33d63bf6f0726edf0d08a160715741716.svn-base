#ifndef	__MENUFUN_H__
#define	__MENUFUN_H__

#include "sys.h"


#define    MAIN_MENU_MODE       0X01      //主菜单模式
#define    MAIN_SUB_MODE        0X02      //子菜单模式






/*定义主菜单宽度，以及最大菜单个数*/
#define  MMENU_WIDTH            20    
#define  MMENU_NO               12

/*定义子菜单宽度，以及最大菜单个数*/
#define  SMENU_WIDTH            20    
#define  SMENU_NO               8

/**********************************************************
//外部变量声明
**********************************************************/

typedef struct
{
  uint8_t  mmenu_no;    //对应主菜单项号
	
	uint8_t  no;          //子菜单个数

	uint8_t  stste;       //所选择的子菜单号

	uint8_t  a;          //备用

	uint8_t  b;          //备用

	uint8_t  c;          //备用
	
	
}SMENU;



//extern  uint8_t  MenuIcobuf[8][20];
//	
//extern	uint8_t  MenuUserbuf[8][20];
//	
//extern	uint8_t  MenuCommbuf[8][30];

extern  uint8_t  Mmenu_NUM ;       //主菜单项号

extern  uint8_t  Mmenu_Shou_Mode ;       //菜单显示模式

extern  uint8_t  Smenu_Shou_NUM ;        //子菜单编号

extern  uint8_t  Menu_Fun_NUM;           //功能菜单编号

extern  uint8_t  Shou_Selection_box ;    //选择框
/**********************************************************
//外部函数声明
**********************************************************/

extern   SMENU   SmenuUse;
extern   SMENU   SmenuComm;
extern   SMENU   SmenuSys;
extern   SMENU   SmenuData;
extern   SMENU   SmenuConsume;
extern   SMENU   SmenuAccess;
extern   SMENU   SmenuDrive;
extern   SMENU   SmenuAuto;
extern   SMENU   SmenuSysInfo;



void   Show_Menudata(void);



#endif
