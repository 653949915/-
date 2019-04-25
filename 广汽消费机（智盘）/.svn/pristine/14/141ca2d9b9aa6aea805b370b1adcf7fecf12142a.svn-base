/***************************************************************************************
 * 工程名  ：W5500模块－客户端模式例程
 * 描述    ：W5500的端口0工作在客户端模式:主动与《TCP&UDP测试工具》上创建的服务端连接,
 *			 并且以500ms的时间间隔定时给服务端发送字符串"\r\nWelcome To YiXinElec!\r\n",同时将接
 *			 收到服务端发来的数据回发给服务端。
 * 实验平台：用户STM32开发板 + YIXIN_W5500以太网(TCP/IP)模块
 * 硬件连接：   PC5 -> W5500_RST0     PB5  
 *             PC4 -> W5500_INT      PB4
 *             PA4 -> W5500_SCS      PB12
 *             PA5 -> W5500_SCK      PB13
 *             PA6 -> W5500_MISO     PB14
 *             PA7 -> W5500_MOSI     PB15
 * 库版本  ：ST_v3.5


端口0 TCP客户端模式
端口1 TCP服务端模式

***************************************************************************************/

/*例程网络参数*/
//网关：192.168.1.1
//掩码:	255.255.255.0
//物理地址：0C 29 AB 7C 00 01
//本机IP地址:192.168.1.199
//端口0的端口号：5000
//端口0的目的IP地址：192.168.1.100
//端口0的目的端口号：6000

#include "stm32f10x.h"		
#include "head.h"			
#include <string.h>


void RCC_Configuration(void);		//设置系统时钟为72MHZ(这个可以根据需要改)
void NVIC_Configuration(void);		//STM32中断向量表配配置
void Timer2_Init_Config(void);		//Timer2初始化配置
void System_Initialization(void);	//STM32系统初始化函数(初始化STM32时钟及外设)
void Delay(unsigned int d);			//延时函数(ms)

unsigned int Timer2_Counter=0; //Timer2定时器计数变量(ms)
unsigned int W5500_Send_Delay_Counter=0; //W5500发送延时计数变量(ms)

/*******************************************************************************
* 函数名  : W5500_Initialization
* 描述    : W5500初始货配置
* 输入    : 无
* 输出    : 无
* 返回值  : 无
* 说明    : 无
*******************************************************************************/
void W5500_Initialization(void)
{
	W5500_Init();		//初始化W5500寄存器函数
	Detect_Gateway(0);	//检查网关服务器 
	Detect_Gateway(1);	//检查网关服务器 
	Detect_Gateway(2);	//检查网关服务器 
	
	Socket_Init(0);		//指定Socket(0~7)初始化,初始化端口0	
  Socket_Init(1);		//指定Socket(0~7)初始化,初始化端口1
	Socket_Init(2);		//指定Socket(0~7)初始化,初始化端口2
	
}

/*******************************************************************************
* 函数名  : Load_Net_Parameters
* 描述    : 装载网络参数
* 输入    : 无
* 输出    : 无
* 返回值  : 无
* 说明    : 网关、掩码、物理地址、本机IP地址、端口号、目的IP地址、目的端口号、端口工作模式
*******************************************************************************/
void Load_Net_Parameters(void)
{
	Gateway_IP[0] = 192;//加载网关参数
	Gateway_IP[1] = 168;
	Gateway_IP[2] = 1;
	Gateway_IP[3] = 1;

	Sub_Mask[0]=255;//加载子网掩码
	Sub_Mask[1]=255;
	Sub_Mask[2]=255;
	Sub_Mask[3]=0;

	Phy_Addr[0]=0x0c;//加载物理地址
	Phy_Addr[1]=0x29;
	Phy_Addr[2]=0xab;
	Phy_Addr[3]=0x7c;
	Phy_Addr[4]=0x00;
	Phy_Addr[5]=0x01;

	IP_Addr[0]=192;//加载本机IP地址
	IP_Addr[1]=168;
	IP_Addr[2]=1;
	IP_Addr[3]=245;
 /*********************************************************/
	S0_Port[0] = 0x13;//加载端口0的端口号5000 
	S0_Port[1] = 0x88;

	S0_DIP[0]=192;//加载端口0的目的IP地址
	S0_DIP[1]=168;
	S0_DIP[2]=0;
	S0_DIP[3]=101;
//	
	S0_DPort[0] = 0x17;//加载端口0的目的端口号6000
	S0_DPort[1] = 0x70;
	

/***********************************************************/	

/***********************************************************/
	S1_Port[0] = 0x13;//加载端口1的端口号5000 
	S1_Port[1] = 0x88;

//	S0_DIP[0]=192;//加载端口0的目的IP地址
//	S0_DIP[1]=168;
//	S0_DIP[2]=1;
//	S0_DIP[3]=190;
//	
//	S0_DPort[0] = 0x17;//加载端口0的目的端口号6000
//	S0_DPort[1] = 0x70;

    InitLocalIPGateway();              //初始化本地IP、子网掩码、网关

  	Init_MAC_Address();                //初始化Mac地址
//	
  	InitRemoteIPandPORT();             //远程IP端口初始化





//	UDP_DIPR[0]=192;//加载端口0的目的IP地址
//	UDP_DIPR[1]=168;
//	UDP_DIPR[2]=1;
//	UDP_DIPR[3]=101;

	UDP_DPORT[0] = 0x13;//加载端口0的端口号5000 
	UDP_DPORT[1] = 0x88;



	S0_Mode=TCP_CLIENT ;        //加载端口0的工作模式,TCP客户端模式
	S1_Mode=TCP_SERVER;         //加载端口1的工作模式,TCP服务端模式
	S2_Mode=UDP_MODE;           //加载端口1的工作模式,UDP模式
/***********************************************************/	
	
}

/*******************************************************************************
* 函数名  : W5500_Socket_Set
* 描述    : W5500端口初始化配置
* 输入    : 无
* 输出    : 无
* 返回值  : 无
* 说明    : 分别设置4个端口,根据端口工作模式,将端口置于TCP服务器、TCP客户端或UDP模式.
*			从端口状态字节Socket_State可以判断端口的工作情况
*******************************************************************************/
void W5500_Socket_Set(void)
{
	if(S0_State==0)//端口0初始化配置
	{
		if(S0_Mode==TCP_SERVER)//TCP服务器模式 
		{
			if(Socket_Listen(0)==TRUE)
				S0_State=S_INIT;
			else
				S0_State=0;
		}
		else if(S0_Mode== TCP_CLIENT)//TCP客户端模式 
		{
			if(Socket_Connect(0)==TRUE)
				S0_State=S_INIT;
			else
				S0_State=0;
		}
		else//UDP模式 
		{
			if(Socket_UDP(0)==TRUE)
				S0_State=S_INIT|S_CONN;
			else
				S0_State=0;
		}
	}
	
	if(S1_State==0)//端口0初始化配置
		{
			if(S1_Mode==TCP_SERVER)//TCP服务器模式 
			{
				if(Socket_Listen(1)==TRUE)
					S1_State=S_INIT;
				else
					S1_State=0;
			}
			else if(S1_Mode== TCP_CLIENT)//TCP客户端模式 
			{
				if(Socket_Connect(1)==TRUE)
					S1_State=S_INIT;
				else
					S1_State=0;
			}
			else//UDP模式 
			{
				if(Socket_UDP(1)==TRUE)
					S1_State=S_INIT|S_CONN;
				else
					S1_State=0;
			}
		}
	
	if(S2_State==0)//端口0初始化配置
	{
		if(S2_Mode==TCP_SERVER)//TCP服务器模式 
		{
			if(Socket_Listen(2)==TRUE)
				S2_State=S_INIT;
			else
				S2_State=0;
		}
		else if(S2_Mode==TCP_CLIENT)//TCP客户端模式 
		{
			if(Socket_Connect(2)==TRUE)
				S2_State=S_INIT;
			else
				S2_State=0;
		}
		else//UDP模式 
		{
			if(Socket_UDP(2)==TRUE)
				S2_State=S_INIT|S_CONN;
			else
				S2_State=0;
		}
	}
		
		
		
		
	
}

/*******************************************************************************
* 函数名  : Process_Socket_Data
* 描述    : W5500接收并发送接收到的数据
* 输入    : s:端口号
* 输出    : 无
* 返回值  : 无
* 说明    : 本过程先调用S_rx_process()从W5500的端口接收数据缓冲区读取数据,
*			然后将读取的数据从Rx_Buffer拷贝到Temp_Buffer缓冲区进行处理。
*			处理完毕，将数据从Temp_Buffer拷贝到Tx_Buffer缓冲区。调用S_tx_process()
*			发送数据。
*******************************************************************************/
void Process_Socket_Data(SOCKET s)
{
	unsigned short size;
	size=Read_SOCK_Data_Buffer(s, S0_Rx_Buffer);
	memcpy(S0_Tx_Buffer, S0_Rx_Buffer, size);			
	Write_SOCK_Data_Buffer(s, S0_Tx_Buffer, size);
	  
}





/*******************************************************************************
* 函数名  : Process_Socket_PROT0_Send
* 描述    : W5500发送指定长度字符串
* 输入    : *Tx_Buffer123需要发送的字符串,len数据长度
* 输出    : 无
* 返回值  : 无
* 说明    : 非例程程序
*******************************************************************************/

void Process_Socket_PROT0_Send(u8 *Tx_Buffer123 ,u16 len)
{
			if(S0_State == (S_INIT|S_CONN))
			{
				S0_Data&=~S_TRANSMITOK;

				Write_SOCK_Data_Buffer(0, Tx_Buffer123, len);	
			}
}

/*******************************************************************************
* 函数名  : Process_Socket_PROT1_Send
* 描述    : W5500发送指定长度字符串
* 输入    : *Tx_Buffer123需要发送的字符串,len数据长度
* 输出    : 无
* 返回值  : 无
* 说明    : 非例程程序
*******************************************************************************/

void Process_Socket_PROT1_Send(u8 *Tx_Buffer123 ,u16 len)
{
			if(S1_State == (S_INIT|S_CONN))
			{
				S1_Data&=~S_TRANSMITOK;

				Write_SOCK_Data_Buffer(1, Tx_Buffer123, len);	
			}
}

/*******************************************************************************
* 函数名  : Process_Socket_PROT0_Send
* 描述    : W5500发送指定长度字符串
* 输入    : *Tx_Buffer123需要发送的字符串,len数据长度
* 输出    : 无
* 返回值  : 无
* 说明    : 非例程程序
*******************************************************************************/

void Process_Socket_PROT0_Receive(SOCKET s)
{
	unsigned short size;
	size=Read_SOCK_Data_Buffer(s, S0_Rx_Buffer);
	memcpy(TcpClient_databuff, S0_Rx_Buffer, size);		
//  TEST_GQ();
		
	ProcessTCPClient();
}

/*******************************************************************************
* 函数名  : Process_Socket_PROT1_Send
* 描述    : W5500发送指定长度字符串
* 输入    : *Tx_Buffer123需要发送的字符串,len数据长度
* 输出    : 无
* 返回值  : 无
* 说明    : 非例程程序
*******************************************************************************/

void Process_Socket_PROT1_Receive(SOCKET s)
{
	unsigned short size;
	size=Read_SOCK_Data_Buffer(s, S1_Rx_Buffer);
	memcpy(TcpServer_databuff, S1_Rx_Buffer, size);		
//  TEST_GQ();
		
  ProcessTCPServer();
	
}

/*******************************************************************************
* 函数名  : Process_Socket_PROT1_Send
* 描述    : W5500发送指定长度字符串
* 输入    : *Tx_Buffer123需要发送的字符串,len数据长度
* 输出    : 无
* 返回值  : 无
* 说明    : 非例程程序
*******************************************************************************/

void Process_Socket_PROT2_Receive(SOCKET s)
{
	unsigned short size;
	size=Read_SOCK_Data_Buffer(s, S2_Rx_Buffer);
				
	UDP_DIPR[0] = S2_Rx_Buffer[0];
	UDP_DIPR[1] = S2_Rx_Buffer[1];
	UDP_DIPR[2] = S2_Rx_Buffer[2];
	UDP_DIPR[3] = S2_Rx_Buffer[3];

	UDP_DPORT[0] = S2_Rx_Buffer[4];
	UDP_DPORT[1] = S2_Rx_Buffer[5];
			
	memcpy(UDPClient_databuff, S2_Rx_Buffer+8, size-8);			
	
  ProcessUDPClient();
	
}




/*******************************************************************************
* 函数名  : W5500_SYSTEM_Init
* 描述    : W5500初始化函数
* 输入    : 无
* 输出    : 无
* 返回值  : int:返回值为一个16位整形数
* 说明    : 无
*******************************************************************************/
void W5500_SYSTEM_Init(void)
{
	System_Initialization();	//STM32系统初始化函数(初始化STM32外设)
	Load_Net_Parameters();		//装载网络参数	
	W5500_Hardware_Reset();		//硬件复位W5500
	W5500_Initialization();		//W5500初始货配置	
	
}

/*******************************************************************************
* 函数名  : W5500_System_Program
* 描述    : W5500主函数
* 输入    : 无
* 输出    : 无
* 返回值  : int:返回值为一个16位整形数
* 说明    : 无
*******************************************************************************/
void W5500_System_Program(void)
{
		W5500_Socket_Set();                       //W5500端口初始化配置

		if(W5500_Interrupt)                       //处理W5500中断		
		{
			W5500_Interrupt_Process();              //W5500中断处理程序框架
		}
		if((S0_Data & S_RECEIVE) == S_RECEIVE)    //如果Socket0接收到数据
		{
			S0_Data&=~S_RECEIVE;
		//	Process_Socket_Data(0);               //W5500接收并发送接收到的数据			
      Process_Socket_PROT0_Receive(0);      //W5500接收数据并保存至缓冲区			
		}
		
	 if((S1_Data & S_RECEIVE) == S_RECEIVE)      //如果Socket1接收到数据
		{
			S1_Data&=~S_RECEIVE;
		//	Process_Socket_Data(0);               //W5500接收并发送接收到的数据	
		
      Process_Socket_PROT1_Receive(1);      //W5500接收数据并保存至缓冲区	
		}
		
	 if((S2_Data & S_RECEIVE) == S_RECEIVE)    //如果Socket2接收到数据
		{
			S2_Data&=~S_RECEIVE;
			Process_Socket_PROT2_Receive(2);                //W5500接收并发送接收到的数据
				
		}	
		
		
		
		
		
//		else if(W5500_Send_Delay_Counter >= 500)//定时发送字符串
//		{
//			if(S0_State == (S_INIT|S_CONN))
//			{
//				S0_Data&=~S_TRANSMITOK;
//				memcpy(Tx_Buffer, "\r\nWelcome To YiXinElec!\r\n", 23);	
//				
//					printf(" %d \n" , S0_State);
//				
//				Write_SOCK_Data_Buffer(0, Tx_Buffer, 23);//指定Socket(0~7)发送数据处理,端口0发送23字节数据
//			}
//			W5500_Send_Delay_Counter=0;
//		}
		
}



/*******************************************************************************
* 函数名  : NVIC_Configuration
* 描述    : STM32中断向量表配配置
* 输入    : 无
* 输出    : 无
* 返回值  : 无
* 说明    : 设置中断优先组
*******************************************************************************/
void NVIC_Configuration(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;						//定义NVIC初始化结构体

  	/* Set the Vector Table base location at 0x08000000 */
//  NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);				//设置中断优先级组为1，优先组(可设0～4位)
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;				//设置中断向量号
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;	//设置抢先优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;			//设置响应优先级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;				//使能NVIC
	NVIC_Init(&NVIC_InitStructure);

  W5500_NVIC_Configuration();	//W5500 接收引脚中断优先级设置
}

/*******************************************************************************
* 函数名  : Timer2_Init_Config
* 描述    : Timer2初始化配置
* 输入    : 无
* 输出    : 无
* 返回    : 无 
* 说明    : 无
*******************************************************************************/
void Timer2_Init_Config(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);		//使能Timer2时钟
	
	TIM_TimeBaseStructure.TIM_Period = 9;						//设置在下一个更新事件装入活动的自动重装载寄存器周期的值(计数到10为1ms)
	TIM_TimeBaseStructure.TIM_Prescaler = 7199;					//设置用来作为TIMx时钟频率除数的预分频值(10KHz的计数频率)
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;		//设置时钟分割:TDTS = TIM_CKD_DIV1
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;	//TIM向上计数模式
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);				//根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
	 
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE ); 				//使能TIM2指定的中断
	
	TIM_Cmd(TIM2, ENABLE);  									//使能TIMx外设
}

/*******************************************************************************
* 函数名  : TIM2_IRQHandler
* 描述    : 定时器2中断断服务函数
* 输入    : 无
* 输出    : 无
* 返回    : 无 
* 说明    : 无
*******************************************************************************/
void TIM2_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM2, TIM_IT_Update) == SET)
	{
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
		Timer2_Counter++;
		W5500_Send_Delay_Counter++;
	}
}

/*******************************************************************************
* 函数名  : System_Initialization
* 描述    : STM32系统初始化函数(初始化STM32时钟及外设)
* 输入    : 无
* 输出    : 无
* 返回    : 无 
* 说明    : 无
*******************************************************************************/
void System_Initialization(void)
{

  NVIC_Configuration();		//STM32中断向量表配配置
	SPI_Configuration();		//W5500 SPI初始化配置(STM32 SPI1)
	Timer2_Init_Config();		//Timer2初始化配置
	W5500_GPIO_Configuration();	//W5500 GPIO初始化配置	
}

/*******************************************************************************
* 函数名  : Delay
* 描述    : 延时函数(ms)
* 输入    : d:延时系数，单位为毫秒
* 输出    : 无
* 返回    : 无 
* 说明    : 延时是利用Timer2定时器产生的1毫秒的计数来实现的
*******************************************************************************/
void Delay(unsigned int d)
{
	Timer2_Counter=0; 
	while(Timer2_Counter < d);
}
