#include "head.h"		    

u32 wificmd;
u32 wificycle;

u32 wifisend;     
u32 wifisendcycle;

/**********************************************************
//WIFI发送卡号     2A 00 00 01 03 0A 46 45 31 44 38 33 39 46 00 00 0A 7E 7E 7E
**********************************************************/
void WIFISendcard( u8 strlen)
{
	u8 i;
	u32 j;
	u8 tmp[21]= {0X2A ,0X51 ,0X05 ,0X07 ,0X03 ,0X0A};
	
	u8 cardidbuff[8];
	
	wificycle = 0;   //心跳包计数置零
	

		//封装机号
	for (j = 0; j < 3; j++)  
	{
		tmp[j + 1] = machno[j];
	}
	
		//封装卡号
	HexToStr(cardidbuff, idbuff, 4);  //卡号16进制转换成ASCII	

	for (i = 0; i < 8; i++)
	{
		tmp[i + 6] = cardidbuff[i];
	}
	
	tmp[16] = GetXOR(tmp + 1, 17);   //异或校验 第2位至倒数第4位
	tmp[0]=0X2A;
	tmp[17]  = 0x7e;
	tmp[18]  = 0x7e;
	tmp[19]  = 0x7e;
	tmp[20]  = Current_time_value[0];
//	SendString(tmp, strlen);
	
		wifisend = 1;        //WiFi重启计数开始
	  wifisendcycle = 0;   //WiFi重启计数
	
}

/**********************************************************
//WIFI发送密码(总长22)  2A 00 00 05 00 02 00 0A 31 32 33 34 35 36 00 00 00 00 0A 7E 7E 7E  
**********************************************************/
void WIFISendPassword(const u8 *str, u8 strlen)
{
	u32 i;
	u32 t;
	u32 j;
	u8  tmp[20]= {0X2A ,0X51 ,0X05 ,0X07 ,0X02 ,0X0A};
	
	u8 keybuff_SCII[6];
	wificycle = 0;   //心跳包计数置零
	
	//封装机号
	for (j = 0; j < 3; j++)  
	{
		tmp[j + 1] = machno[j];
	}
	
	//封装密码
	
		for (t = 0; t < 6; t++)
	{
		keybuff_SCII[t] = str[t]+0x30;
	}
		
		for (i = 0; i < 6; i++)
	{
		tmp[i + 6] = keybuff_SCII[i];
	}
	
	
//	tmp[6]  = pbDest[0];
//	tmp[7]  = pbDest[1];
	tmp[16] = GetXOR(tmp + 1, 17);   //异或校验 第2位至倒数第4位
	
	tmp[17]  = 0x7e;
	tmp[18]  = 0x7e;
	tmp[19]  = 0x7e;

		
//	SendString(tmp, strlen);
	
		wifisend = 1;        //WiFi重启计数开始
	  wifisendcycle = 0;   //WiFi重启计数
	
}





/**********************************************************
//WIFI心跳
**********************************************************/
void WIFIBeat(void)
{
//	u32 j;

////	u8  tmp[]= {0X2A ,0X51 ,0X05 ,0X07 ,0X01 ,0X00 ,0XF0 ,0X7E ,0X7E ,0X7E};	
//	
//		//封装机号
//	for (j = 0; j < 3; j++)  
//	{
//		tmp[j + 1] = machno[j];
//	}
//	wificycle = 0;	
////	SendString(tmp, 10);
}


///**********************************************************
////检查WIFI数据
//**********************************************************/
//u32 CheckWIFIData(void)
//{
//	if (comidx < 7) { return 0; }

//	if (combuff[3] != comidx) { return 0; }
//	
//	return 1;
//}

/**********************************************************
//处理WIFI通讯
**********************************************************/
void ProcessWIFI(void)
{
	
	wificmd = 0;        //接收到WiFi发送过来的数据
	
	wifisend = 0;       //重启WiFi标志
	wifisendcycle = 0;  //重启WiFi计数
	
//	OPEN_GREEN_LED();

//	if (CheckWIFIData())
//	{
//		switch (combuff[4 + 6]) //处理命令
//		{
//			case 0x30: //00 00 00 0F 00 02 2A 51 05 07 30 00 00 0D 0A  开门
//			{
//		//		ONE_LONG_BEEP(); //长响一声
//				Showpasscor();	
////				BeginOutput();   //打开继电器				
//				break; 
//			}		
//			case 0x31: //00 00 00 0F 00 02 2A 51 05 07 31 00 00 0D 0A  不开门
//			{
//				Showpasserr();
//				Beep(3, SHORT_BEEP); //短响三声
//				break; 
//			}		
//			case 0x32: //00 00 00 0F 00 02 2A 51 05 07 32 00 00 0D 0A  恢复出厂设置
//			{
//							
//			LoadDefaultValue();			
//			clear_screen();           //OLED清屏
//			display_GB2312_string(6,16,"恢复出厂设置");				
//			Beep(3, LONG_BEEP); //短响三声								
//				break; 
//			}						
//			default:  break;
//		}
//	}
	
//	clear_screen();     //屏幕清零

//	showStandby=1;
	InitCombuff();
}

/**********************************************************
//初始化WIFI
**********************************************************/
void InitWIFI(void)
{

//	WIFI_PW = 0;   //	给WiFi上电
	
	wificmd = 0;   // 
	wificycle = 0;
	
	wifisend = 0;
	wifisendcycle = 0;
	
}




