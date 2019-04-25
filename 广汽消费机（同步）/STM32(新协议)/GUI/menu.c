
#include "43inchGUI.h"

#include "head.h"




u8  func_index;      //序号

u8  Menu_mode =0;      //菜单模式  1 菜单模式 0 按键消费模式

u8  Menu_password_falg =0;      //菜单模式密码是否正确  1正确 0 不正确

//u8 temp_test=0;


u8 keytmp[6]={'-','-','-','-','-','-'}; 


u8 keyouttime[2];	  //按键输入 继电器退出时间显示
u8 machnobuf[6];    //按键输入 修改机号显示
	
u32  DISPLAY_CHAR1[14] = {
	        
	            '0', //0x00
							'1', //0x01
							'2', //0x02
							'3', //0x03
							'4', //0x04
							'5', //0x05
							'6', //0x06
							'7', //0x07
							'8', //0x08
							'9', //0x09
							'*', //0x0A				  
	            '0', //0x00
			       	'#', //0x0B
	            '-'  
};



typedef struct
{
	u8 guicurrent;//当前状态索引号
	u8 up;     //向上
	u8 down;	 //向下
	u8 enter;  //确定
	u8 exit;   //退出
	void (*guicurrent_operation)(void); //当前状态应该执行的操作
} Menu_table;


void (*guicurrent_operation_index)(void);//


typedef struct
{
	u8 guicurrent;  //当前状态索引号
	u8 Correct;     //正确
	u8 Error;       //错误

	void (*right_wrong_index)(void); //当前状态应该执行的操作
} right_wrong;

void (*right_wrong_index)(void);//

Menu_table  table[154]=
{
  {0, 0 ,0 ,0 ,0 ,(*fun0)},    // 第 1 级  主界面
	
	{1 ,2 ,3 ,4 ,5 ,(*fun1)},    //  主界面
	
	{2 ,2 ,3 ,4 ,5 ,(*fun2)},    //  上翻
	{3 ,2 ,3 ,4 ,5 ,(*fun3)},    //  下翻 	
	{4 ,2 ,3 ,4 ,5 ,(*fun4)},    //  确定	
	{5 ,2 ,4 ,4 ,5 ,(*fun5)},    //  取消		
	
	{6 ,7 ,8 ,9 ,10 ,(*fun6)},    //  用户设置 0
	{7 ,7 ,8 ,9 ,10 ,(*fun7)},    //  上翻
	{8 ,7 ,8 ,9 ,10 ,(*fun8)},    //  下翻
	{9 ,7 ,8 ,9 ,10 ,(*fun9)},    // 	确定	
	{10,7 ,8 ,9 ,10 ,(*fun10)},   //  取消
	
	{11,12 ,13 ,14 ,15 ,(*fun11)},    //  通讯设置 1
	{12,12 ,13 ,14 ,15 ,(*fun12)},    // 	上翻
	{13,12 ,13 ,14 ,15 ,(*fun13)},    //  下翻	
	{14,12 ,13 ,14 ,15 ,(*fun14)},    // 	确定	
	{15,12 ,13 ,14 ,15 ,(*fun15)},    //  取消	
		
	{16,17 ,18 ,19 ,20 ,(*fun16)},    //   系统设置 2
	{17,17 ,18 ,19 ,20 ,(*fun17)},    // 	 上翻
	{18,17 ,18 ,19 ,20 ,(*fun18)},    //   下翻
	{19,17 ,18 ,19 ,20 ,(*fun19)},    // 	 确定
	{20,17 ,18 ,19 ,20 ,(*fun20)},    // 	 取消
	
	{21 , 22, 23,  24, 25 ,(*fun21) },   //	 数据管理 3
	{22 , 22 ,23 , 24, 25 ,(*fun22) },   //	 上翻		
	{23 , 22 ,23 , 24, 25 ,(*fun23) },   //	 下翻
	{24 , 22 ,23 , 24, 25 ,(*fun24) },   //	 确定
	{25 , 22, 23 , 24, 25 ,(*fun25) },   //	 取消
	
	{26 , 27 ,28 , 29, 30 ,(*fun26) },   //	  消费管理 4
	{27 , 27 ,28 , 29, 30 ,(*fun27) },   //	  上翻
	{28 , 27 ,28 , 29, 30 ,(*fun28) },   //	  下翻
	{29 , 27, 28,  29, 30 ,(*fun29) },   //	  确定
	{30 , 27, 28,  29, 30 ,(*fun30) },   //	  取消

	{31 , 32 ,33 , 34, 35 ,(*fun36) },   //	 	U盘管理	5
	{32 , 32 ,33 , 34, 35 ,(*fun37) },   //	  上翻
	{33 , 32 ,33 , 34, 35 ,(*fun38) },   //		下翻
	{34 , 32 ,33 , 34, 35 ,(*fun39) },   //   确定
	{35 , 32 ,33 , 34, 35 ,(*fun40) },   //	  取消
	
	{36 , 37 , 38, 39, 40 ,(*fun41) },   //	  自动测试  6
	{37 , 37 , 38, 39, 40 ,(*fun42) },   //	  上翻
	{38 , 37 , 38, 39, 40 ,(*fun43) },   //	  下翻
	{39 , 37 , 38, 39, 40 ,(*fun44) },   //	  确定		
	{40 , 37 , 38, 39, 40 ,(*fun45) },   //	  取消
	
	{41 , 42 , 43, 44, 45 ,(*fun46) },   //		系统信息  7 
	{42 , 42 , 43, 44, 45 ,(*fun47) },   //	  上翻
	{43 , 42 , 43, 44, 45 ,(*fun48) },   //	  下翻		
	{44 , 42 , 43, 44, 45 ,(*fun49) },   //	  确定
	{45 , 42 , 43, 44, 45 ,(*fun50) },   //	  取消

	
	
	
	{46 , 47 , 48,  49, 50 ,(*fun51) },   //	         9
	{47 , 47 , 48,  49, 50 ,(*fun52) },   //	上翻		
	{48 , 47 , 48,  49, 50 ,(*fun53) },   //	下翻
	{49 , 47 , 48,  49, 50 ,(*fun54) },   //	确定	
	{50 , 47 , 48,  49, 50 ,(*fun55) },   //  取消
	
	{51 , 32 ,33 , 34, 35 ,(*fun31) },   //	  门禁管理 5
	{52 , 32 ,33 , 34, 35 ,(*fun32) },   //	  上翻
	{53 , 32 ,33 , 34, 35 ,(*fun33) },   //   下翻
	{54 , 32 ,33 , 34, 35 ,(*fun34) },   //	  确定
	{55 , 32 ,33 , 34, 35 ,(*fun35) },   //	  取消
	
	{56 , 57 , 58,  59, 60, (*fun56) },   //	 		     10
	{57 , 57 , 58,  59, 60 ,(*fun57) },   //	
	{58 , 57 , 58,  59, 60 ,(*fun58) },   //		
	{59 , 57 , 58,  59, 60 ,(*fun59) },   //	
	{60 , 57 , 58,  59, 60 ,(*fun60) },   //	

	{61 , 52 , 53,  54, 55 ,(*fun51) },   //	         11
	{62 , 52 , 53,  54, 55 ,(*fun52) },   //	上翻		
	{63 , 52 , 53,  54, 55 ,(*fun53) },   //	下翻
	{64 , 52 , 53,  54, 55 ,(*fun54) },   //	确定	
	{65 , 52 , 53,  54, 55 ,(*fun55) },   //  取消
	
	{66 , 57 , 58,  59, 60, (*fun56) },   //	 		    12
	{67 , 57 , 58,  59, 60 ,(*fun57) },   //	
	{68 , 57 , 58,  59, 60 ,(*fun58) },   //		
	{69 , 57 , 58,  59, 60 ,(*fun59) },   //	
	{70 , 57 , 58,  59, 60 ,(*fun60) },   //	

	{71 , 52 , 53,  54, 55 ,(*fun51) },   //	        13
	{72 , 52 , 53,  54, 55 ,(*fun52) },   //	上翻		
	{73 , 52 , 53,  54, 55 ,(*fun53) },   //	下翻
	{74 , 52 , 53,  54, 55 ,(*fun54) },   //	确定	
	{75 , 52 , 53,  54, 55 ,(*fun55) },   //  取消
	
	{76 , 57 , 58,  59, 60, (*fun56) },   //	 		   14
	{77 , 57 , 58,  59, 60 ,(*fun57) },   //	
	{78 , 57 , 58,  59, 60 ,(*fun58) },   //		
	{79 , 57 , 58,  59, 60 ,(*fun59) },   //	
	{80 , 57 , 58,  59, 60 ,(*fun60) },   //	

  /*                给登录菜单用            */	
	{81 , 82 , 83,  84, 85 ,(*fun81) },   // 	   按键输入管理员密码       
	{82 , 82 , 83,  84, 85 ,(*fun82) },   //		 上翻
	{83 , 82 , 83,  84, 85 ,(*fun83) },   //	   下翻
	{84 , 82 , 83,  84, 85 ,(*fun84) },   //		 确定
	{85 , 82 , 83,  84, 85 ,(*fun85) },   //  	 取消
	
	{86 , 57 , 58,  59, 60, (*fun86) },   //	 		   
	{87 , 57 , 58,  59, 60 ,(*fun87) },   //	
	{88 , 57 , 58,  59, 60 ,(*fun88) },   //		
	{89 , 57 , 58,  59, 60 ,(*fun89) },   //	
	{90 , 57 , 58,  59, 60 ,(*fun90) },   //	

	
	{91 , 52 , 53,  54, 55 ,(*fun51) },   //	        
	{92 , 52 , 53,  54, 55 ,(*fun52) },   //		
	{93 , 52 , 53,  54, 55 ,(*fun53) },   //	
	{94 , 52 , 53,  54, 55 ,(*fun54) },   //		
	{95 , 52 , 53,  54, 55 ,(*fun55) },   //  	
	{96 , 57 , 58,  59, 60, (*fun56) },   //	 		   
	{97 , 57 , 58,  59, 60 ,(*fun57) },   //	
	{98 , 57 , 58,  59, 60 ,(*fun58) },   //		
	{99 , 57 , 58,  59, 60 ,(*fun59) },   //	
	{100, 57 , 58,  59, 60 ,(*fun60) },   //
	
	

};



 right_wrong  right_wrongbuff[64]={

{0, 2, 1, (*fun28)},   //	功能主界面

{1, 2, 1, (*fun28)},   //	确认

{2, 3, 2, (*fun28)},   // 返回

{3, 1, 3, (*fun28)},   //	

 };

 
void  Menu_key_set(void)
{
	uint8_t   Menu_keyval=NULL;
	
	keyVal =  tmKeyscan();  
	
 if((keyVal!=NULL) ) // 如果有按键按下
	{		
		   Beep(1, SHORT_BEEP);
		
		if(keyVal==0X0A)
		{
		  keyVal =0;
		}
			
  Menu_keyval = keyVal;

//	if(!Menu_mode)	      //按键模式
//	{
	if(Menu_keyval ==KEY_SET)  		    //菜单
		{
			ClrScreen();  //清屏	
			delay_ms(1);
			Show_Refresh_coun=0;
			INIT_KEY_BUFF();    //按键数量清零		
			
			func_index=81;//				
			
			Menu_mode =1;    //按键进入菜单模式
			
			guicurrent_operation_index=table[func_index].guicurrent_operation;
	
			(*guicurrent_operation_index)();//执行当前操作函数																
		}			
	else if(Menu_keyval ==KEY_QUERY)   //查询键
		{
			ClrScreen();  //清屏	
			delay_ms(1);
			Show_Refresh_coun=0;
			
			Standbytime =   SECOND_CYCLE*30;   //30秒后进入主界面
			
			INIT_KEY_BUFF();    //按键数量清零				
		
		  SET_MY_STATUS( IN_QUERY_STATUS);	
			
			SYN6288_Send(SYN6288CMD_VOICE_PLAY ,SYN6288CMDPARAM_PLAY_MUSIC0,"请刷卡" ,6);
					
      return ;			
		}
		
	else if(Menu_keyval ==KEY_FUNCTION)   //打印键(退款)
		{
			ClrScreen();  //清屏	
			delay_ms(1);
			Show_Refresh_coun=0;
			
			Standbytime =   SECOND_CYCLE*30;   //30秒后进入主界面
			
			INIT_KEY_BUFF();    //按键数量清零				
		
		  SET_MY_STATUS( IN_REFUND_STATUS);	
			
			SYN6288_Send(SYN6288CMD_VOICE_PLAY ,SYN6288CMDPARAM_PLAY_MUSIC0,"退款请刷卡" ,10);
					
      return ;			
		}		
				
	if(!Menu_mode)	      //按键扣款模式
	{			
		{
			if((keyVal >KEY_SET)&&(keyVal != KEY_CLEAN)&&(keyVal != KEY_CONFIRM))
			{return ;};
			
			CheckKEY(keyVal);    //处理按键	
		}
	}
	else
	{	
	  Standbytime =   SECOND_CYCLE*30;   //30秒后进入主界面
		
		switch(Menu_keyval)
			{
			
				case KEY_UPTURN:     //上翻
						{
							ClrScreen();  //清屏	
							delay_ms(1);
							Show_Refresh_coun=0;
							
							INIT_KEY_BUFF();    //按键数量清零
							
							func_index=table[func_index].up;    //向上翻  
							
					    guicurrent_operation_index=table[func_index].guicurrent_operation;
	
	            (*guicurrent_operation_index)();//执行当前操作函数		
							
							break;
						}
			
				 case KEY_DOWNTURN:   //下翻
						{
			
							ClrScreen();  //清屏	
							delay_ms(1);
							Show_Refresh_coun=0;
							
							INIT_KEY_BUFF();    //按键数量清零
							
							func_index=table[func_index].down;//向下翻
							
							
					    guicurrent_operation_index=table[func_index].guicurrent_operation;
	
	            (*guicurrent_operation_index)();//执行当前操作函数								
							
							break;			
						}
				 case KEY_CONFIRM:         //确认
							{	
								ClrScreen();  //清屏	
								delay_ms(1);
								
								Show_Refresh_coun=0;
								INIT_KEY_BUFF();    //按键数量清零		
							
								func_index=table[func_index].enter;//回车	
								
								guicurrent_operation_index=table[func_index].guicurrent_operation;
				
								(*guicurrent_operation_index)();//执行当前操作函数								
								
								menu_keyidx =0;
													
							//	memset(menu_keybuff, 0, 40);   //清0
								
								break;
								}
			
				case  KEY_CLEAN:		    //清除
							{			
								ClrScreen();  //清屏	
								delay_ms(1);
								Show_Refresh_coun=0;
								
								INIT_KEY_BUFF();    //按键数量清零		
								
								func_index=table[func_index].exit;//		

								guicurrent_operation_index=table[func_index].guicurrent_operation;
						
								(*guicurrent_operation_index)();//执行当前操作函数			
								
								menu_keyidx =0;
								
								memset(menu_keybuff, 0, 40);   //清0
								
								break;
							}
			
				case  KEY_SET:		    //菜单
					{			
						ClrScreen();  //清屏	
						delay_ms(1);
						Show_Refresh_coun=0;
						INIT_KEY_BUFF();    //按键数量清零		
						
						func_index=81;//				

						guicurrent_operation_index=table[func_index].guicurrent_operation;
				
						(*guicurrent_operation_index)();//执行当前操作函数			
						
						break;
					}				
											
			 default: 
						 {
							 
							 if((keyVal >=KEY_SPOT))
			           {return ;};
							 	 
						   Menu_CheckKEY(keyVal);    //处理按键
							
							 ClrScreen();  //清屏	
							 delay_ms(1);
							 Show_Refresh_coun=0;
								
							 INIT_KEY_BUFF();    //按键数量清零		
							 
							break;
					   }
		     }			
			}						
	}		
}


void  fun0(void)
{ 
	if(Standbycount>10)    //1秒
		{				  
			Standbycount=0;        //计数置0		
						
			delay_ms(1);
			
			INIT_KEY_BUFF();       //按键数量清零
			
      memset(keymoneybuff,0,4);
			
			u32_monetbuf =0;
			
			Clear_Key_Status();    //清除按键状态
			  
			showStandby=1;         //显示待机状态
			
		}	
		                                                                                                                                                                                                                                                           
	 if (statuscnt > 8)		//退出编程模式时间20秒
					
     {		SET_MY_STATUS(NORMAL_STATUS);		  }   //进入工作状态	
		 
	 
	//	AnalyzeWorkStatus(); //工作状态分析
}


/*主界面初始化*/
void  fun1(void)
{	
	  Mmenu_Shou_Mode = MAIN_MENU_MODE;     //主菜单模式
	
		SET_MY_STATUS(IN_MENU_STATUS);	   //进入菜单状态
	
	  Menu_password_falg =1;	
	
}

/*主界面上翻*/
void  fun2(void)
{

  if(Mmenu_NUM==0)  Mmenu_NUM=0;
	else
	    Mmenu_NUM--;	
}
	
/*主界面下翻*/
void  fun3(void)
{	
	Mmenu_NUM+=1;
	
	if( Mmenu_NUM > MMENU_NO-1 )  Mmenu_NUM = MMENU_NO-1;
}



/*主界面确认*/
void  fun4(void)
{
 // Mmenu_NUM =0;
	
	func_index=Mmenu_NUM*5+6;//
	
	Mmenu_Shou_Mode=MAIN_SUB_MODE;    //子菜单模式
	
  Smenu_Shou_NUM =Mmenu_NUM;    //子菜单编号
	
	guicurrent_operation_index=table[func_index].guicurrent_operation;
	
	(*guicurrent_operation_index)();//执行当前操作函数	

}


/*主界面清除*/
void  fun5(void)
{    
	Mmenu_NUM =0;
	
	func_index=0;//
	
	guicurrent_operation_index=table[func_index].guicurrent_operation;
	
	(*guicurrent_operation_index)();//执行当前操作函数	
	
	Menu_mode =0;    //按键进入消费模式	
	
	Standbytime =   0;   //0秒后进入主界面
}



/*用户子菜单初始化*/
void  fun6(void)
{
	
}
	
/*用户子菜单上翻*/
void  fun7(void)
{
	
	
	if(SmenuUse.stste==0)   SmenuUse.stste=0;
	else
	SmenuUse.stste--;	

}

/*用户子菜单下翻*/
void  fun8(void)
{
	
	SmenuUse.stste+=1;
	if(SmenuUse.stste > SmenuUse.no-1)  SmenuUse.stste = SmenuUse.no-1;
	
}


/*用户子菜单确定*/
void  fun9(void)
{
  uint8_t i;
  
  i = SmenuUse.stste | SmenuUse.mmenu_no ;
	
	Menu_Fun_NUM  = i ; 
	
	if(GetWorkStatus(IN_FUN_STATUS))    //是功能设置状态
	{
	   SetWorkStatus(IN_MENU_STATUS);   //回到子菜单界面
	
		//用户处理函数
		switch(i)
		{
		  case   0x00:   
									{
																	
									  AT24CXX_Write(PROGRAMM_POS, menu_keybuff,PROGRAMM_SIZE); 
																											
									}          break;
	
			default:      break;
			
		}	
	}
	else
	{   //进入功能状态
		
	   SetWorkStatus(IN_FUN_STATUS);   //进入功能设置状态
	}
}
	
/*用户子菜单清除*/
void  fun10(void)
{
	if(GetWorkStatus(IN_FUN_STATUS))    //是功能设置状态
	{
	   SetWorkStatus(IN_MENU_STATUS);   //回到子菜单界面
	
			func_index=6;//
	
			guicurrent_operation_index=table[func_index].guicurrent_operation;
			
			(*guicurrent_operation_index)();//执行当前操作函数		
			
		
	}
	else  //子菜单界面
	{   
		
			func_index=1;//
	
			guicurrent_operation_index=table[func_index].guicurrent_operation;
			
			(*guicurrent_operation_index)();//执行当前操作函数		
			
			SmenuUse.stste=0;      //子菜单编号置0
			
			fun1();                 //进入到主菜单界面
	}
}	
	

/*通讯子菜单初始化*/
void  fun11(void)
{



}	
	
/*通讯子菜单上翻*/
void  fun12(void)
{
		uint8_t i;
	
	if(GetWorkStatus(IN_FUN_STATUS))    //是功能设置状态
	{
		i = SmenuComm.stste | SmenuComm.mmenu_no ;
	
			//用户处理函数
		switch(i)
		{
		  case   0x10:  { menu_keyidx=0;  }      break;                                               //设置4G服务器IP和端口号
			case   0x11:  {if(menu_keyidx>12) menu_keyidx-=12; else menu_keyidx=0;  }      break;         //设置TCP本机IP
					
			default:      break;
			
		}
	}
	else
	{
		if(SmenuComm.stste==0)   SmenuComm.stste=0;
		else
		SmenuComm.stste--;	
	}
}	
	
/*通讯子菜单下翻*/	
void  fun13(void)
{
	uint8_t i;
	
	if(GetWorkStatus(IN_FUN_STATUS))    //是功能设置状态
	{
		i = SmenuComm.stste | SmenuComm.mmenu_no ;
		
			//用户处理函数
		switch(i)
		{
		  case   0x10:  { menu_keyidx=12;  }      break;         //设置4G服务器IP和端口号  
			case   0x11:  { menu_keyidx+=12; if(menu_keyidx>menu_keyidx_MAX) menu_keyidx=0; }      break;         //设置TCP本机IP
			default:      break;
		}
	}
	else
	{		
		SmenuComm.stste+=1;
		if(SmenuComm.stste > SmenuComm.no-1)  SmenuComm.stste = SmenuComm.no-1;
	}
}	
	
/*通讯子菜单确定*/		
void  fun14(void)
{
  uint8_t i;
  
	uint8_t  menuIPbuf[17];
  uint8_t  menuIPASCIIbuf[40];
  uint8_t  t;
	uint32_t  port;
	
	

  i = SmenuComm.stste | SmenuComm.mmenu_no ;
	
	Menu_Fun_NUM  = i ; 
	
	if(GetWorkStatus(IN_FUN_STATUS))    //是功能设置状态
	{
	   SetWorkStatus(IN_MENU_STATUS);   //回到子菜单界面
	
		//用户处理函数
		switch(i)
		{
		  case   0x10:     //设置服务器IP和端口号
									 {		
									  union	TwoByte  p2;

						        	/*  处理4G远端IP   */			 
										 HexToStr(menuIPASCIIbuf,  menu_keybuff,  17);
										 
										 for(t =0;t < 17; t++)
										 {
											 memcpy(menuIPbuf+t, menuIPASCIIbuf+1+t*2 ,1);       //  拷贝 ip								 																		 
										 }
										 
											AT24CXX_Write(TCP4G_REMOTE_IPandPort_POS,menuIPbuf,17);	              //24C512写IP
												 
											Init_EC20_Remote_IP();                                                //初始化IP
										 
	
									        	/*  处理有线tcp远端IP   */																		
										for(t =0;t < 12; t+=3)
										 {
												menuIPASCIIbuf[t/3]	= menu_keybuff[t]*100 + menu_keybuff[t+1]*10 + menu_keybuff[t+2];
																																																					 
										 }			

                     port = menu_keybuff[12]*10000 + menu_keybuff[13]*1000 + menu_keybuff[14]*100 + menu_keybuff[15]*10 + menu_keybuff[16];

										 p2.i =port;
										 																			 
										 menuIPASCIIbuf[4] = p2.c[1];
										 menuIPASCIIbuf[5] = p2.c[0];
										 															
                     AT24CXX_Write(TCP_REMOTE_IPandPort_POS,menuIPASCIIbuf,6);	              //24C512写IP									 
										 
  	                 InitRemoteIPandPORT();             //远程IP端口初始化
										 
								//			QuectelEC20_Rest();		            //复位模块	
							
									//	 RS485_Send_Data(menuIPbuf,	menu_keyidx_MAX);								 								 													 
									 }           break;     

#ifdef   Move_Version     //是4g通讯

				  case   0x11:    //设置TCP本机IP
									{
									
										for(t =0;t < menu_keyidx_MAX; t+=3)
										 {
												menuIPASCIIbuf[t/3]	= menu_keybuff[t]*100 + menu_keybuff[t+1]*10 + menu_keybuff[t+2];
																																																					 
										 }
										
										 AT24CXX_Write(TCP_LOCAL_IP_POS,menuIPASCIIbuf,12);	  //24C512写IP
										
								//		RS485_Send_Data(menuIPASCIIbuf,	12);	
																								
									}             break;							 
									 
									 
									 
#elif    Standard_Version   //标准版本								 

		  case   0x11:    //设置TCP本机IP
									{
									
										for(t =0;t < menu_keyidx_MAX; t+=3)
										 {
												menuIPASCIIbuf[t/3]	= menu_keybuff[t]*100 + menu_keybuff[t+1]*10 + menu_keybuff[t+2];
																																																					 
										 }
										
										 AT24CXX_Write(TCP_LOCAL_IP_POS,menuIPASCIIbuf,12);	  //24C512写IP
										
								//		RS485_Send_Data(menuIPASCIIbuf,	12);	
																								
									}             break;
									
									
									

									
#elif    WIFI_Version      //WIFI版本									 


				case   0x11:    //配置WiFi密码
									{
								
								


										
									}           break;
									
									
															 
#endif											 
									 
//		  case   0x12:     //设置TCP/IP服务器IP地址
//									{
//									  union	TwoByte  p2;
//																				
//										for(t =0;t < 12; t+=3)
//										 {
//												menuIPASCIIbuf[t/3]	= menu_keybuff[t]*100 + menu_keybuff[t+1]*10 + menu_keybuff[t+2];
//																																																					 
//										 }			

//                     port = menu_keybuff[12]*10000 + menu_keybuff[13]*1000 + menu_keybuff[14]*100 + menu_keybuff[15]*10 + menu_keybuff[16];

//										 p2.i =port;
//										 																			 
//										 menuIPASCIIbuf[4] = p2.c[1];
//										 menuIPASCIIbuf[5] = p2.c[0];
//										 															
//                     AT24CXX_Write(TCP_REMOTE_IPandPort_POS,communication_data +AGR_FIXED_SIZE,6);	              //24C512写IP
//										 
//										 RS485_Send_Data(menuIPASCIIbuf,	6);	
//										 
//									}				break;
							
		  case   0x12:    //恢复网络出厂设置
									{
																		
					         	LoadnEC20DefaultValue();				
							
								      //menu_keybuff
								
									}           break;									
									
		
			default:      break;
			
		}	
	}
	else
	{   //进入功能状态
		 switch(i)
				{
					case   0x10:     //设置4G服务器IP和端口号
											 {			
												 for(t =0;t < 17; t++)
													{
													 menu_keybuff[t]= ec20_remoteipbuf[t]-0X30;													
													}																											 										 										 
											 }   break;
											 
					case   0x11:    //设置TCP本机IP
											{
												
												 AT24CXX_Read(TCP_LOCAL_IP_POS,menuIPASCIIbuf,12);
												
											
												for(t =0;t < 36; t+=3)
												 {
														menu_keybuff[t] 	= menuIPASCIIbuf[t/3]/100 ;
														menu_keybuff[t+1]	= menuIPASCIIbuf[t/3]%100/10;			
                            menu_keybuff[t+2]	= menuIPASCIIbuf[t/3]%100%10; 													 
												 }
																																						
											}             break;											 
											 											 											 																				 
					default:      break;									 																		 
				 }		
				
		 SetWorkStatus(IN_FUN_STATUS);   //进入功能设置状态									 
	
	}
	
}	
/*通讯子菜单清除*/	
void  fun15(void)
{
	if(GetWorkStatus(IN_FUN_STATUS))    //是功能设置状态
	{
	   SetWorkStatus(IN_MENU_STATUS);   //回到子菜单界面
	
			func_index=11;//
	
			guicurrent_operation_index=table[func_index].guicurrent_operation;
			
			(*guicurrent_operation_index)();//执行当前操作函数		
			
		
	}
	else  //子菜单界面
	{   
		
			func_index=1;//
	
			guicurrent_operation_index=table[func_index].guicurrent_operation;
			
			(*guicurrent_operation_index)();//执行当前操作函数		
			
			SmenuComm.stste=0;      //子菜单编号置0
			
			fun1();                 //进入到主菜单界面
	}
	
	
}	
	
	

/*系统子菜单初始化*/	
void  fun16(void)
{
	
}	

/*系统子菜单上翻*/		
void  fun17(void)
{
	if(SmenuSys.stste==0)   SmenuSys.stste=0;
	else
	SmenuSys.stste--;	
}	
	
/*系统子菜单下翻*/		
void  fun18(void)
{
	SmenuSys.stste+=1;
	if(SmenuSys.stste > SmenuSys.no-1)  SmenuSys.stste = SmenuSys.no-1;

}
/*系统子菜单确定*/		
void  fun19(void)
{
  uint8_t i =0;
  
  uint8_t t =0;	
	
	uint8_t  menuSysbuf[17];
//  uint8_t  menuIPASCIIbuf[40];
	
  i = SmenuSys.stste | SmenuSys.mmenu_no ;
	
	Menu_Fun_NUM  = i ; 
	
	if(GetWorkStatus(IN_FUN_STATUS))    //是功能设置状态
	{
	   SetWorkStatus(IN_MENU_STATUS);   //回到子菜单界面
	
		//用户处理函数
		switch(i)
		{
			
		  case   0x20:     Network_Synchronization_Time(); 	       break;     //网络同步时间
			
		  case   0x21:   {      //设置时间、日期
																 
											 for(t =0;t < 12; t+=2)
											 {												 
												 menuSysbuf[t/2] =  (menu_keybuff[t]<<4)|menu_keybuff[t+1];																														 
											 }
				
									     SetNowTime(menuSysbuf+1);     //设置时间		 
											 
									   //  RS485_Send_Data(menuSysbuf,	12);	
		
										 }          break;
		  case   0x22:   SET_Volume(menu_keybuff); 	       break;   
		  case   0x23:                                     break;
		  case   0x24:                                     break;
		
			default:      break;
			
		}	
	}
	else
	{   //进入功能状态
			switch(i)
			{
				case   0x21:   {      //读取时间日期
																	 
												 for(t =0;t < 12; t+=2)
												 {												 
													 menu_keybuff[t] =  time_buf[t/2]>>4;

													 menu_keybuff[t+1] =time_buf[t/2]&0X0F;																					 
												 }						
											 }          break;
				
				case   0x22:   {         //设置音量
					
				                   AT24CXX_Read( VOLUME_IDX  ,menuSysbuf , 1);
				
				                   menu_keybuff[0] =  menuSysbuf[0];
									
												}        break;   
				case   0x23:                                     break;
				case   0x24:                                     break;
			
				default:      break;
				
			}		
			
	   SetWorkStatus(IN_FUN_STATUS);   //进入功能设置状态			
	}
	
}
	
/*系统子菜单清除*/		
void  fun20(void)
{
	if(GetWorkStatus(IN_FUN_STATUS))    //是功能设置状态
	{
	    SetWorkStatus(IN_MENU_STATUS);   //回到子菜单界面
	
			func_index=16;//
	
			guicurrent_operation_index=table[func_index].guicurrent_operation;
			
			(*guicurrent_operation_index)();//执行当前操作函数		
					
	}
	else  //子菜单界面
	{   
		
			func_index=1;//
	
			guicurrent_operation_index=table[func_index].guicurrent_operation;
			
			(*guicurrent_operation_index)();//执行当前操作函数		
			
			SmenuSys.stste=0;      //子菜单编号置0
			
			fun1();                 //进入到主菜单界面
	}
}	

/*数据子菜单初始化*/	
void  fun21(void)
{
}

/*数据子菜单上翻*/	
void  fun22(void)
{
	
	if(SmenuData.stste==0)   SmenuData.stste=0;
	else
	SmenuData.stste--;	
	
}	
/*数据子菜单下翻*/	
void  fun23(void)
{
	
	SmenuData.stste+=1;
	if(SmenuData.stste > SmenuData.no-1)  SmenuData.stste = SmenuData.no-1;
	
}
/*数据子菜单确定*/
void  fun24(void)
{
  uint8_t i;
  
  i = SmenuData.stste | SmenuData.mmenu_no ;
	
	Menu_Fun_NUM  = i ; 
	
	if(GetWorkStatus(IN_FUN_STATUS))    //是功能设置状态
	{
	   SetWorkStatus(IN_MENU_STATUS);   //回到子菜单界面
	
		//用户处理函数
				switch(i)
				{
				  case   0x30: { DelRecord();                    }         break;                                      //清除所有刷卡记录
//				  case   0x31:   SET_Volume(menu_keybuff);         break;              //查看容量
//				  case   0x32: {  DeleteConsumption_All_Money(); }         break;                                      //查看消费总额
				  case   0x33: {  DeleteConsumption_All_Money(); }         break;                                      //清除消费总额			
					
					
					default:      break;
					
				}	
	}
	else
	{   //进入功能状态
		
	   SetWorkStatus(IN_FUN_STATUS);   //进入功能设置状态
	}	
}

/*数据子菜单取消*/
void  fun25(void)
{
	
 if(GetWorkStatus(IN_FUN_STATUS))    //是功能设置状态
	{
	   SetWorkStatus(IN_MENU_STATUS);   //回到子菜单界面
	
			func_index=21;//
	
			guicurrent_operation_index=table[func_index].guicurrent_operation;
			
			(*guicurrent_operation_index)();//执行当前操作函数		
			
		
	}
	else  //子菜单界面
	{   
		
			func_index=1;//
	
			guicurrent_operation_index=table[func_index].guicurrent_operation;
			
			(*guicurrent_operation_index)();//执行当前操作函数		
			
			SmenuData.stste=0;      //子菜单编号置0
			
			fun1();                 //进入到主菜单界面
	}
}


/*消费子菜单初始化*/	
void  fun26(void)
{
}	

/*消费子菜单上翻*/	
void  fun27(void)
{
	uint8_t i;
	
	if(GetWorkStatus(IN_FUN_STATUS))    //是功能设置状态
	{
		i = SmenuConsume.stste | SmenuConsume.mmenu_no ;
			
			//用户处理函数
		switch(i)
		{
		  case   0x44:  {if(menu_keyidx>4) menu_keyidx-=4; else menu_keyidx=0;  }      break;         ////定值扣费金额  
			case   0x45:  {if(menu_keyidx>8) menu_keyidx-=8; else menu_keyidx=0;  }      break;         ////定值扣费时段
			case   0x46:  {if(menu_keyidx>8) menu_keyidx-=8; else menu_keyidx=0;  }      break;         ////菜单扣费金额		
			
			
			default:      break;
			
		}
	}
	else
	{
		if(SmenuConsume.stste==0)   SmenuConsume.stste=0;
		else
		SmenuConsume.stste--;		
	}
}
/*消费子菜单下翻*/	
void  fun28(void)
{
	uint8_t i;
	
	if(GetWorkStatus(IN_FUN_STATUS))    //是功能设置状态
	{
		i = SmenuConsume.stste | SmenuConsume.mmenu_no ;
			
			//用户处理函数
		switch(i)
		{
		  case   0x44:  { menu_keyidx+=4; if(menu_keyidx>menu_keyidx_MAX) menu_keyidx=0;  }      break;         ////定值扣费金额  
			case   0x45:  { menu_keyidx+=8; if(menu_keyidx>menu_keyidx_MAX) menu_keyidx=0; }      break;         ////定值扣费时段
			case   0x46:  { menu_keyidx+=8; if(menu_keyidx>menu_keyidx_MAX) menu_keyidx=0; }      break;         ////菜单扣费金额			
			default:      break;
			
		}
	}
	else
	{		
		SmenuConsume.stste+=1;
		if(SmenuConsume.stste > SmenuConsume.no-1)  SmenuConsume.stste = SmenuConsume.no-1;
		
	}
	
}
/*消费子菜单确定*/	
void  fun29(void)
{
  uint8_t i;
	
	uint8_t t;
  uint8_t  menuConsumebuf[20];
//  uint8_t  menuConsumeASCIIbuf[40];
	
	
  i = SmenuConsume.stste | SmenuConsume.mmenu_no ;
	
	Menu_Fun_NUM  = i ; 
	
	if(GetWorkStatus(IN_FUN_STATUS))    //是功能设置状态
	{
	   SetWorkStatus(IN_MENU_STATUS);   //回到子菜单界面
	
		//用户处理函数
		switch(i)
		{
		  case   0x40:  { Machine_category[0] =0X01;   SaveMachine_Category();  }      break;         //设定为 变值扣费  
			
		  case   0x41:  { Machine_category[0] =0X02;   SaveMachine_Category();	}	     break;         //设定为 定值扣费 
			
		  case   0x42:  { Machine_category[0] =0X03;   SaveMachine_Category();  }      break;         //设定为 计次扣费 
			
		  case   0x43:  { Machine_category[0] =0X04;   SaveMachine_Category();  }      break;         //设定为 菜单扣费		
			
		  case   0x44:   //定值扣费金额
										{										
											for(t=0 ; t<menu_keyidx_MAX ;t+=2 )
											{										
												menuConsumebuf[t/2]= 	(menu_keybuff[t]<<4)|menu_keybuff[t+1];										
											}	
											
                      memcpy(Fixed_consum_Moneybuf, menuConsumebuf ,8);       //  拷贝 金额
											
											SaveFixed_consumption_Money();  //保存定值扣费金额
                  //    RS485_Send_Data(menuConsumebuf,	8);	
											
										}          break;         
		  case   0x45:   //定值扣费时段
									 {
										  for(t=0 ; t<menu_keyidx_MAX ;t+=2 )
											{										
												menuConsumebuf[t/2]= 	(menu_keybuff[t]<<4)|menu_keybuff[t+1];										
											}			

                      memcpy(Fixed_consum_Timerbuf, menuConsumebuf ,16);       //  拷贝 
											
											SaveFixed_consumption_Timer();  //保存定值扣费时段
											
                 //     RS485_Send_Data(menuConsumebuf,	16);	
											
										}          break;  
									 
		  case   0x46:   //菜单扣费金额
									 {
										  for(t=0 ; t<menu_keyidx_MAX ;t+=2 )
											{										
												menuConsumebuf[t/2]= 	(menu_keybuff[t]<<4)|menu_keybuff[t+1];										
											}			

                      memcpy(Carte_consum_Moneybuf, menuConsumebuf ,18);       //  拷贝 金额
											
                      SaveCarte_consum_Money();      //保存菜单扣费金额
											
                 //     RS485_Send_Data(menuConsumebuf,	16);	
											
										}          break;  										
										
								
										
										        		
			default:      break;
			
		}	
	}
	else
	{   //进入功能状态
		
				switch(i)
								{
									
									case   0x44:   //定值扣费金额
																{										
																	for(t=0 ; t<16 ;t+=2 )
																	{										
																		menu_keybuff[t]= 	  Fixed_consum_Moneybuf[t/2]>>4;		
                                    menu_keybuff[t+1]= 	Fixed_consum_Moneybuf[t/2]&0X0F;									
																	}	
																	
																																		
																}          break;         
									case   0x45:   //定值扣费时段
															 {
																	for(t=0 ; t<32 ;t+=2 )
																	{																												
																		menu_keybuff[t]= 	  Fixed_consum_Timerbuf[t/2]>>4;		
                                    menu_keybuff[t+1]= 	Fixed_consum_Timerbuf[t/2]&0X0F;																			
																	}			
															
																}          break;  
															 
									case   0x46:   //菜单扣费金额
															 {
																	for(t=0 ; t<36 ;t+=2 )
																	{																												
																		menu_keybuff[t]= 	  Carte_consum_Moneybuf[t/2]>>4;		
                                    menu_keybuff[t+1]= 	Carte_consum_Moneybuf[t/2]&0X0F;																			
																	}			
															
																}          break;  		

									case   0x47:   //消费限额金额
															 {
																	for(t=0 ; t<12 ;t+=2 )
																	{																												
																		menu_keybuff[t]= 	  Sub_Maximum_Limitbuf[t/2+1]>>4;		
																		menu_keybuff[t+1]= 	Sub_Maximum_Limitbuf[t/2+1]&0X0F;																			
																	}			
															
																}          break; 		

																
																																																						
									default:      break;
									
								}
				
	   SetWorkStatus(IN_FUN_STATUS);   //进入功能设置状态
	}	
		
	
}
/*消费子菜单清除*/	
void  fun30(void)
{
	
 if(GetWorkStatus(IN_FUN_STATUS))    //是功能设置状态
	{
	   SetWorkStatus(IN_MENU_STATUS);   //回到子菜单界面
	
			func_index=26;//
	
			guicurrent_operation_index=table[func_index].guicurrent_operation;
			
			(*guicurrent_operation_index)();//执行当前操作函数		
			
		
	}
	else  //子菜单界面
	{   
		
			func_index=1;//
	
			guicurrent_operation_index=table[func_index].guicurrent_operation;
			
			(*guicurrent_operation_index)();//执行当前操作函数		
			
			SmenuConsume.stste=0;      //子菜单编号置0
			
			fun1();                 //进入到主菜单界面
	}	
	
}


/*门禁子菜单初始化*/	
void  fun31(void)
{
}
/*门禁子菜单上翻*/	
void  fun32(void)
{
	
	if(SmenuAccess.stste==0)   SmenuAccess.stste=0;
	else
	SmenuAccess.stste--;			
	
}	
/*门禁子菜单下翻*/		
void  fun33(void)
{
	
	SmenuAccess.stste+=1;
	if(SmenuAccess.stste > SmenuAccess.no-1)  SmenuAccess.stste = SmenuAccess.no-1;	
	
}
/*门禁子菜单确定*/	
void  fun34(void)
{
	
  uint8_t i;
  
  i = SmenuAccess.stste | SmenuAccess.mmenu_no ;
	
	Menu_Fun_NUM  = i ; 
	
	if(GetWorkStatus(IN_FUN_STATUS))    //是功能设置状态
	{
	   SetWorkStatus(IN_MENU_STATUS);   //回到子菜单界面
	
		//用户处理函数
//		switch(i)
//		{
//		  case   0x20:             break;
//		  case   0x21:   SET_Volume(menu_keybuff);         break;
//		  case   0x22:             break;
//		  case   0x23:             break;
//		
//			default:      break;
//			
//		}	
	}
	else
	{   //进入功能状态
		
	   SetWorkStatus(IN_FUN_STATUS);   //进入功能设置状态
	}		
	
}
/*门禁子菜单取消*/	
void  fun35(void)
{
	
 if(GetWorkStatus(IN_FUN_STATUS))    //是功能设置状态
	{
	   SetWorkStatus(IN_MENU_STATUS);   //回到子菜单界面
	
			func_index=31;//
	
			guicurrent_operation_index=table[func_index].guicurrent_operation;
			
			(*guicurrent_operation_index)();//执行当前操作函数		
			
		
	}
	else  //子菜单界面
	{   
		
			func_index=1;//
	
			guicurrent_operation_index=table[func_index].guicurrent_operation;
			
			(*guicurrent_operation_index)();//执行当前操作函数		
			
			SmenuAccess.stste=0;      //子菜单编号置0
			
			fun1();                 //进入到主菜单界面
	}		
	
}

/*U盘子菜单初始化*/
void  fun36(void)
{
}	
/*U盘子菜单上翻*/	
void  fun37(void)
{
	
	if(SmenuDrive.stste==0)   SmenuDrive.stste=0;
	else
	SmenuDrive.stste--;			
	
}
/*U盘子菜单下翻*/
void  fun38(void)
{
	
	SmenuDrive.stste+=1;
	if(SmenuDrive.stste > SmenuDrive.no-1)  SmenuDrive.stste = SmenuDrive.no-1;		
	
}
/*U盘子菜单确定*/
void  fun39(void)
{
	
  uint8_t i;
  
  i = SmenuDrive.stste | SmenuDrive.mmenu_no ;
	
	Menu_Fun_NUM  = i ; 
	
	if(GetWorkStatus(IN_FUN_STATUS))    //是功能设置状态
	{
	   SetWorkStatus(IN_MENU_STATUS);   //回到子菜单界面
	
		//用户处理函数
//		switch(i)
//		{
//		  case   0x20:             break;
//		  case   0x21:   SET_Volume(menu_keybuff);         break;
//		  case   0x22:             break;
//		  case   0x23:             break;
//		
//			default:      break;
//			
//		}	
	}
	else
	{   //进入功能状态
		
	   SetWorkStatus(IN_FUN_STATUS);   //进入功能设置状态
	}	
	
}
/*U盘子菜单取消*/
void  fun40(void)
{
	
	if(GetWorkStatus(IN_FUN_STATUS))    //是功能设置状态
	{
	   SetWorkStatus(IN_MENU_STATUS);   //回到子菜单界面
	
			func_index=31;//
	
			guicurrent_operation_index=table[func_index].guicurrent_operation;
			
			(*guicurrent_operation_index)();//执行当前操作函数		
			
		
	}
	else  //子菜单界面
	{   
		
			func_index=1;//
	
			guicurrent_operation_index=table[func_index].guicurrent_operation;
			
			(*guicurrent_operation_index)();//执行当前操作函数		
			
			SmenuDrive.stste=0;      //子菜单编号置0
			
			fun1();                 //进入到主菜单界面
	}
	
}

/*主动测试子菜单初始化*/
void  fun41(void)
{
}	
/*主动测试子菜单上翻*/	
void  fun42(void)
{
	
	if(SmenuAuto.stste==0)   SmenuAuto.stste=0;
	else
	SmenuAuto.stste--;		
	
}
/*主动测试子菜单下翻*/
void  fun43(void)
{
	
	SmenuAuto.stste+=1;
	if(SmenuAuto.stste > SmenuAuto.no-1)  SmenuAuto.stste = SmenuAuto.no-1;		
	
}
/*主动测试子菜单确定*/
void  fun44(void)
{
  uint8_t i;
  
  i = SmenuAuto.stste | SmenuAuto.mmenu_no ;
	
	Menu_Fun_NUM  = i ; 
	
	if(GetWorkStatus(IN_FUN_STATUS))    //是功能设置状态
	{
	   SetWorkStatus(IN_MENU_STATUS);   //回到子菜单界面
	
		//用户处理函数
//		switch(i)
//		{
//		  case   0x20:             break;
//		  case   0x21:   SET_Volume(menu_keybuff);         break;
//		  case   0x22:             break;
//		  case   0x23:             break;
//		
//			default:      break;
//			
//		}	
	}
	else
	{   //进入功能状态
		
	   SetWorkStatus(IN_FUN_STATUS);   //进入功能设置状态
	}	
	
}
/*主动测试子菜单取消*/
void  fun45(void)
{
	
	 if(GetWorkStatus(IN_FUN_STATUS))    //是功能设置状态
	{
	   SetWorkStatus(IN_MENU_STATUS);   //回到子菜单界面
	
			func_index=36;//
	
			guicurrent_operation_index=table[func_index].guicurrent_operation;
			
			(*guicurrent_operation_index)();//执行当前操作函数		
			
		
	}
	else  //子菜单界面
	{   
		
			func_index=1;//
	
			guicurrent_operation_index=table[func_index].guicurrent_operation;
			
			(*guicurrent_operation_index)();//执行当前操作函数		
			
			SmenuAuto.stste=0;      //子菜单编号置0
			
			fun1();                 //进入到主菜单界面
	}	
	
}


/*系统信息子菜单初始化*/
void  fun46(void)
{
}

/*系统信息子菜单上翻*/	
void  fun47(void)
	{
		
		if(SmenuSysInfo.stste==0)   SmenuSysInfo.stste=0;
		else
		SmenuSysInfo.stste--;	
		
	}	
/*系统信息子菜单下翻*/	
void  fun48(void)
	{
		
			SmenuSysInfo.stste+=1;
		if(SmenuSysInfo.stste > SmenuSysInfo.no-1)  SmenuSysInfo.stste = SmenuSysInfo.no-1;
		
	}

/*系统信息子菜单确定*/			
void  fun49(void)
{
	
  uint8_t i;
  
  i = SmenuSysInfo.stste | SmenuSysInfo.mmenu_no ;
	
	Menu_Fun_NUM  = i ; 
	
	if(GetWorkStatus(IN_FUN_STATUS))    //是功能设置状态
	{
	   SetWorkStatus(IN_MENU_STATUS);   //回到子菜单界面
	
//		//用户处理函数
//		switch(i)
//		{
//		  case   0x20:             break;
//		  case   0x21:   SET_Volume(menu_keybuff);         break;
//		  case   0x22:             break;
//		  case   0x23:             break;
//		
//			default:      break;
//			
//		}	
	}
	else
	{   //进入功能状态
		
	   SetWorkStatus(IN_FUN_STATUS);   //进入功能设置状态
	}	
	
}

/*系统信息子菜单清除*/	
void  fun50(void)
	{
		
	if(GetWorkStatus(IN_FUN_STATUS))    //是功能设置状态
	{
	   SetWorkStatus(IN_MENU_STATUS);   //回到子菜单界面
	
			func_index=41;//
	
			guicurrent_operation_index=table[func_index].guicurrent_operation;
			
			(*guicurrent_operation_index)();//执行当前操作函数		
			
		
	}
	else  //子菜单界面
	{   
		
			func_index=1;//
	
			guicurrent_operation_index=table[func_index].guicurrent_operation;
			
			(*guicurrent_operation_index)();//执行当前操作函数		
			
			SmenuSys.stste=0;      //子菜单编号置0
			
			fun1();                 //进入到主菜单界面
		
	}
	
}



void  fun51(void)
{
}

void  fun52(void)
{
}	
	
void  fun53(void)
{
}

void  fun54(void)
{
}
void  fun55(void)
{
}

void  fun56(void)
{
}	
	
void  fun57(void)
{
}

void  fun58(void)
{
}

void  fun59(void)
{
}

void  fun60(void)
{
}



void  fun81(void)
{
	Mmenu_Shou_Mode = MAIN_MENU_MODE;     //主菜单模式
	
  SET_MY_STATUS(IN_MENU_STATUS);	   //进入菜单状态
	
	Menu_password_falg =0;	
	
	memset(menu_keybuff, 0, 40);   //清0
	
	menu_keyidx =0;
}

void  fun82(void)
{
}	
	
void  fun83(void)
{
}

void  fun84(void)
{
	uint8_t pass[8]={0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08};
	uint8_t def_pass[6]={0x09,0x07,0x07,0x05,0x02,0x00};
	
	
	AT24CXX_Read(PROGRAMM_POS,pass,PROGRAMM_SIZE);     //从AT24C256读取编程密码
	
	if (MyStrEQ(menu_keybuff , pass, PROGRAMM_SIZE)||MyStrEQ(menu_keybuff , def_pass, PROGRAMM_SIZE)) //密码正确
	{
		memset(menu_keybuff, 0, 40);   //清0
		
		func_index=1;//				
		
		guicurrent_operation_index=table[func_index].guicurrent_operation;

		(*guicurrent_operation_index)();//执行当前操作函数		
	}
	else
		{
		
		  SYN6288_Send(SYN6288CMD_VOICE_PLAY ,SYN6288CMDPARAM_PLAY_MUSIC0,"密码错误" ,8);
				
		}
	
}
void  fun85(void)
{
	Mmenu_NUM =0;
	
	func_index=0;//
	
	guicurrent_operation_index=table[func_index].guicurrent_operation;
	
	(*guicurrent_operation_index)();//执行当前操作函数	
	
	Menu_mode =0;    //按键进入消费模式	
	
	Standbytime =   0;   //0秒后进入主界面
}

void  fun86(void)
{
}	
	
void  fun87(void)
{
}

void  fun88(void)
{
}

void  fun89(void)
{
}

void  fun90(void)
{
	
	
}






void exitbutton(void)  //返回按钮

{
	
//	clear_screen();//清屏
	func_index=table[func_index].exit;//	
	guicurrent_operation_index=table[func_index].guicurrent_operation;
	(*guicurrent_operation_index)();//执行当前操作函数

}

void enterbutton(void)    //确定按键

{

//	clear_screen();//清屏
	func_index=table[func_index].enter;//	确定
	guicurrent_operation_index=table[func_index].guicurrent_operation;
	(*guicurrent_operation_index)();//执行当前操作函数

}




void outmenu(void)    //退出菜单模式
{
	
//		guicurrent_operation_index=table[6].guicurrent_operation;
//	(*guicurrent_operation_index)();//执行当前操作函数
//	
//	    exitbutton();  //返回按钮
//	    	keyidx1=0;   //按键计数清零
//	      clear_screen();//清屏
	
//			display_GB2312_string(0,5,"科坦门禁系统");	
	
       timedelay_s(1);
    
}




//void button_menu(void)    //按下菜单键
//{

//	func_index=1;//	确定
//	guicurrent_operation_index=table[func_index].guicurrent_operation;
//	(*guicurrent_operation_index)();//执行当前操作函数

//}



