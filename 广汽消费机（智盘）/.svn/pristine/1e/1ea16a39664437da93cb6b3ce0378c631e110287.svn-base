#include "Head.h"

/**********************************************************
//变量定义。
**********************************************************/
 u8  isection; //实际读写扇区号
 
 u8  password[PASSWORD_SIZE]; //扇区主密码

#define	  NULL_VALUE		0xFF       //空值

/**********************************************************
//常量定义
**********************************************************/

u8  DEF_SYSVAR[] = {	0x03, //继电器输出延时0
								      0x05, //报警输出次数1
								      0x01, //重复刷卡间隔2
								      0x00,0x00,0xEA,0x60, //长期有效次数3,4,5,6 高低低高存储
								      0x00, //机器安装位置7
								      0x00, //机器分组8
							      	0x01, //机器安装楼层9
							      	0x00  //检查名单10
						  };

u8  DEF_PASS[] = {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0X00,0X01};   //扇区密码

u8  DEF_EXTVAR[] = {	0x00, //电梯外呼
							        0x01, //检查卡密码
						        	0x00, //串口输出楼层控制信息
						        	0x00, //消防输入
						         	0x00,0x00,0x00,0x00,0x00,0x00,0x00
						  }; 

//u8  DEF_PROGRAMM[6] = {0x33,0x35,0x35,0x37,0x36,0x35};   //编程密码

u8  DEF_PROGRAMM[6] = {3,5,5,7,6,5};   //编程密码

//---------------------------------------------------------


/**********************************************************
//装载缺省值
**********************************************************/
void LoadDefaultValue(void)
	{

		//系统参数
	//	AT24CXX_Write(SYSVAR_ST,DEF_SYSVAR , SYSVAR_SIZE);

		//扩展参数
	//	AT24CXX_Write(EXTVAR_ST,DEF_EXTVAR ,   SYSVAR_SIZE);

		//读写扇区与密码
			SetPassword(DEF_PASS, 8);

		//编程密码
	//	AT24CXX_Write(PROGRAMM_POS,DEF_PROGRAMM ,   PROGRAMM_SIZE);

		LoadnEC20DefaultValue();        //4G远端IP出厂值
	}




/**********************************************************
//装载网络缺省值
**********************************************************/
void LoadnNetDefaultValue(void)
	{
		u8  Default_Local_ip[12]={192,168,0,245,255,255,255,0,192,168,0,1};						/*默认本地IP*/
			
		u8  Default_remote_ip[6]={192,168,0,101,0x13,0x88};										        /*远端IP地址和端口号 5000*/
					
    AT24CXX_Write(TCP_LOCAL_IP_POS,Default_Local_ip,12);                          /*写本地IP*/
	
	  AT24CXX_Write(TCP_REMOTE_IPandPort_POS,Default_remote_ip,6);	                /*写远端IP端口号*/
		
		reboot();                                                                     //STM32系统软复位函数(重启系统)					
		
	}

/**********************************************************
//装载4G网络缺省值
**********************************************************/
void LoadnEC20DefaultValue(void)
	{
	
		u8  Default_remote_ip[]={"12007808714923238"};										        /*远端IP地址和端口号*/ 
					
	  AT24CXX_Write(TCP4G_REMOTE_IPandPort_POS,Default_remote_ip,17);	                /*写远端IP端口号*/
		
	//	reboot();                                                                     //STM32系统软复位函数(重启系统)																																	
		
	}





/*******************************************************************************
//初始化新增数据起始地址参数
*******************************************************************************/
void Initnewdate_addr(void)
{
	u8 Initdate[]={0x00,0x00,0x00,0x00};
	
	
	if (AT24CXX_ReadOneByte(NEWDATE_ADDRST) == NULL_VALUE)	
	{																					   
   		AT24CXX_Write(NEWDATE_ADDRST, Initdate , 4);		
	}
}



