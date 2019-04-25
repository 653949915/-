#include "Head.h"

#include "MenuFun.h"




uint8_t  Mmenu_NUM =0;             //主菜单项号

uint8_t  Mmenu_Shou_Mode =0;       //菜单显示模式

uint8_t  Smenu_Shou_NUM =0;        //子菜单编号

uint8_t  Shou_Selection_box =0;    //选择框

uint8_t  Menu_Fun_NUM=0;           //功能菜单编号

SMENU SmenuUse=            //用户管理子菜单
                {
								 0x00,     //对应主菜单号
								 1,        //子菜单个数
								 0,        //当前子菜单号
								 0,
								 0,
								 0
								};

SMENU SmenuComm=           //通讯设置子菜单号
								{
								 0x10,     //对应主菜单号
								 3,        //子菜单个数
								 0,        //当前子菜单号
								 0,
								 0,
								 0
								};								
								
SMENU SmenuSys=            //系统子菜单号
								{
								 0x20,     //对应主菜单号
								 3,        //子菜单个数
								 0,        //当前子菜单号
								 0,
								 0,
								 0
								};								
								
SMENU SmenuData=           //数据子菜单号
								{
								 0x30,     //对应主菜单号
								 4,        //子菜单个数
								 0,        //当前子菜单号
								 0,
								 0,
								 0
								};								
	

SMENU SmenuConsume=        //消费子菜单号
								{
								 0x40,     //对应主菜单号
								 7,        //子菜单个数
								 0,        //当前子菜单号
								 0,
								 0,
								 0
								};	


SMENU SmenuAccess=        //门禁子菜单号
								{
								 0x50,     //对应主菜单号
								 3,        //子菜单个数
								 0,        //当前子菜单号
								 0,
								 0,
								 0
								};								

SMENU SmenuDrive=        //U盘管理子菜单号
								{
								 0x50,     //对应主菜单号
								 2,        //子菜单个数
								 0,        //当前子菜单号
								 0,
								 0,
								 0
								};


SMENU SmenuAuto=        //自动测试子菜单号
								{
								 0x60,     //对应主菜单号
								 4,        //子菜单个数
								 0,        //当前子菜单号
								 0,
								 0,
								 0
								};								
								
								
								
SMENU SmenuSysInfo=           //系统信息子菜单号
								{
								 0x70,     //对应主菜单号
								 3,        //子菜单个数
								 0,        //当前子菜单号
								 0,
								 0,
								 0
								};

						
uint8_t  MenuMainBuf[MMENU_NO][20]={  //主菜单

{"1.用户管理"},
{"2.通讯设置"},
{"3.系统设置"},
{"4.数据管理"},
{"5.消费管理"},
{"6.U盘管理"},
{"7.自动测试"},
{"8.系统信息"},
};
	

uint8_t  MenuUsebuf[MMENU_NO][20]={    //用户管理    1

{"1.修改管理员密码"},
};
		

uint8_t  MenuCommbuf[MMENU_NO][30]={     //通讯设置  2

#ifdef   Move_Version     //是4g通讯
{"1.设置服务器IP"},
{"2.设置本机IP"},
{"3.恢复出厂值"},
	
#elif Standard_Version   //标准版本
{"1.设置服务器IP"},
{"2.设置本机IP"},
{"3.恢复出厂值"},

#elif WIFI_Version      //WIFI版本
{"1.设置服务器IP"},
{"2.配置WiFi密码"},
{"3.恢复出厂值"},

#endif		


};

uint8_t  MenuSysbuf[MMENU_NO][20]={     //系统设置  3
{"1.网络同步时间"},
{"2.手动设置时间"},
{"3.音量设置"},
};

uint8_t  MenuDatabuf[MMENU_NO][20]={     //数据管理  4

{"1.清除所有记录"},
{"2.查看容量"},
{"3.查询消费总额"},
{"4.清除消费总额"},
};

uint8_t  MenuConsumebuf[MMENU_NO][20]={     //消费管理  5

{"1.设定为变值扣费"},
{"2.设定为定值扣费"},
{"3.设置为计次扣费"},
{"4.设置为菜单扣费"},
{"5.设置定值扣费金额"},
{"6.设置普通就餐时段"},
{"7.设置菜单扣费金额 "},
{""},
{"9.设置新增扣款金额"},
{"10.设置新增扣款时段"},
};

uint8_t  MenuAccessbuf[MMENU_NO][20]={     //门禁管理  6

{"1.开门延时"},
{"2.开门延时"},
{"3.开门延时"},
};

uint8_t  MenuDrivebuf[MMENU_NO][20]={     //U盘管理  7

{"1.U盘下载数据"},
{"2.U盘升级"},
};


uint8_t  MenuAutobuf[MMENU_NO][20]={     //自动测试  8

{"1.机器自检"},
{"2.键盘测试"},
{"3.IC卡测试"},
{"4.二维码测试"},

};

uint8_t  MenuSysInfobuf[MMENU_NO][20]={     //系统信息  9

{"1.设备信息"},
{"2.固件信息"},
{"3.厂商信息"},
};




/**/
void   Show_Menudata(void)
{
	uint8_t i;

//	memset(MenuShowBuf, 0, 10);   //清0
	
	if(Mmenu_Shou_Mode == MAIN_MENU_MODE)  //主菜单模式
	{
	for(i=0;i<MMENU_NO;i++)
		{
			memcpy(MenuShowBuf[i],MenuMainBuf[i],20);
		}
		Shou_Selection_box = Mmenu_NUM;
	}
	else if(Mmenu_Shou_Mode == MAIN_SUB_MODE)    //子菜单模式
		{
		 switch(Smenu_Shou_NUM)      //子菜单编号
		 {
				case 0:     //用户管理
					{
					for(i=0;i<MMENU_NO;i++)
						{
							memcpy(MenuShowBuf[i],MenuUsebuf[i],20);
						}		
						Shou_Selection_box = SmenuUse.stste;
						break;
					}
				case 1:     //通讯设置
				{
					for(i=0;i<MMENU_NO;i++)
						{
							memcpy(MenuShowBuf[i],MenuCommbuf[i],30);
						}			
						
						Shou_Selection_box = SmenuComm.stste;
					break;
				} 

				case 2:     //系统设置设置
				{
					for(i=0;i<MMENU_NO;i++)
						{
							memcpy(MenuShowBuf[i],MenuSysbuf[i],20);
						}			
						
						Shou_Selection_box = SmenuSys.stste;
					break;
				}	
				
				case 3:     //数据管理
				{
					for(i=0;i<MMENU_NO;i++)
						{
							memcpy(MenuShowBuf[i],MenuDatabuf[i],20);
						}			
						
						Shou_Selection_box = SmenuData.stste;
					break;
				}			

				case 4:     //消费管理
				{
					for(i=0;i<MMENU_NO;i++)
						{
							memcpy(MenuShowBuf[i],MenuConsumebuf[i],20);
						}			
						
						Shou_Selection_box = SmenuConsume.stste;
					break;
				}		

//				case 5:     //门禁管理
//				{
//					for(i=0;i<MMENU_NO;i++)
//						{
//							memcpy(MenuShowBuf[i],MenuAccessbuf[i],20);
//						}			
//						
//						Shou_Selection_box = SmenuAccess.stste;
//					break;
//				}	
				
				case 5:     //U盘管理
				{
					for(i=0;i<MMENU_NO;i++)
						{
							memcpy(MenuShowBuf[i],MenuDrivebuf[i],20);
						}			
						
						Shou_Selection_box = SmenuDrive.stste;
					break;
				}	

				case 6:     //自动测试
				{
					for(i=0;i<MMENU_NO;i++)
						{
							memcpy(MenuShowBuf[i],MenuAutobuf[i],20);
						}			
						
						Shou_Selection_box = SmenuAuto.stste;
					break;
				}					
				
				case 7:     //系统信息
				{
					for(i=0;i<MMENU_NO;i++)
						{
							memcpy(MenuShowBuf[i],MenuSysInfobuf[i],20);
						}			
						
						Shou_Selection_box = SmenuSysInfo.stste;
					break;
				}	
				
       default:    break;			
		 }
	}
}





















