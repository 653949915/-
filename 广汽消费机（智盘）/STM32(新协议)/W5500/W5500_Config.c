/***************************************************************************************
 * ������  ��W5500ģ�飭�ͻ���ģʽ����
 * ����    ��W5500�Ķ˿�0�����ڿͻ���ģʽ:�����롶TCP&UDP���Թ��ߡ��ϴ����ķ��������,
 *			 ������500ms��ʱ������ʱ������˷����ַ���"\r\nWelcome To YiXinElec!\r\n",ͬʱ����
 *			 �յ�����˷��������ݻط�������ˡ�
 * ʵ��ƽ̨���û�STM32������ + YIXIN_W5500��̫��(TCP/IP)ģ��
 * Ӳ�����ӣ�   PC5 -> W5500_RST0     PB5  
 *             PC4 -> W5500_INT      PB4
 *             PA4 -> W5500_SCS      PB12
 *             PA5 -> W5500_SCK      PB13
 *             PA6 -> W5500_MISO     PB14
 *             PA7 -> W5500_MOSI     PB15
 * ��汾  ��ST_v3.5


�˿�0 TCP�ͻ���ģʽ
�˿�1 TCP�����ģʽ

***************************************************************************************/

/*�����������*/
//���أ�192.168.1.1
//����:	255.255.255.0
//�����ַ��0C 29 AB 7C 00 01
//����IP��ַ:192.168.1.199
//�˿�0�Ķ˿ںţ�5000
//�˿�0��Ŀ��IP��ַ��192.168.1.100
//�˿�0��Ŀ�Ķ˿ںţ�6000

#include "stm32f10x.h"		
#include "head.h"			
#include <string.h>


void RCC_Configuration(void);		//����ϵͳʱ��Ϊ72MHZ(������Ը�����Ҫ��)
void NVIC_Configuration(void);		//STM32�ж�������������
void Timer2_Init_Config(void);		//Timer2��ʼ������
void System_Initialization(void);	//STM32ϵͳ��ʼ������(��ʼ��STM32ʱ�Ӽ�����)
void Delay(unsigned int d);			//��ʱ����(ms)

unsigned int Timer2_Counter=0; //Timer2��ʱ����������(ms)
unsigned int W5500_Send_Delay_Counter=0; //W5500������ʱ��������(ms)

/*******************************************************************************
* ������  : W5500_Initialization
* ����    : W5500��ʼ������
* ����    : ��
* ���    : ��
* ����ֵ  : ��
* ˵��    : ��
*******************************************************************************/
void W5500_Initialization(void)
{
	W5500_Init();		//��ʼ��W5500�Ĵ�������
	Detect_Gateway(0);	//������ط����� 
	Detect_Gateway(1);	//������ط����� 
	Detect_Gateway(2);	//������ط����� 
	
	Socket_Init(0);		//ָ��Socket(0~7)��ʼ��,��ʼ���˿�0	
  Socket_Init(1);		//ָ��Socket(0~7)��ʼ��,��ʼ���˿�1
	Socket_Init(2);		//ָ��Socket(0~7)��ʼ��,��ʼ���˿�2
	
}

/*******************************************************************************
* ������  : Load_Net_Parameters
* ����    : װ���������
* ����    : ��
* ���    : ��
* ����ֵ  : ��
* ˵��    : ���ء����롢�����ַ������IP��ַ���˿ںš�Ŀ��IP��ַ��Ŀ�Ķ˿ںš��˿ڹ���ģʽ
*******************************************************************************/
void Load_Net_Parameters(void)
{
	Gateway_IP[0] = 192;//�������ز���
	Gateway_IP[1] = 168;
	Gateway_IP[2] = 1;
	Gateway_IP[3] = 1;

	Sub_Mask[0]=255;//������������
	Sub_Mask[1]=255;
	Sub_Mask[2]=255;
	Sub_Mask[3]=0;

	Phy_Addr[0]=0x0c;//���������ַ
	Phy_Addr[1]=0x29;
	Phy_Addr[2]=0xab;
	Phy_Addr[3]=0x7c;
	Phy_Addr[4]=0x00;
	Phy_Addr[5]=0x01;

	IP_Addr[0]=192;//���ر���IP��ַ
	IP_Addr[1]=168;
	IP_Addr[2]=1;
	IP_Addr[3]=245;
 /*********************************************************/
	S0_Port[0] = 0x13;//���ض˿�0�Ķ˿ں�5000 
	S0_Port[1] = 0x88;

	S0_DIP[0]=192;//���ض˿�0��Ŀ��IP��ַ
	S0_DIP[1]=168;
	S0_DIP[2]=0;
	S0_DIP[3]=101;
//	
	S0_DPort[0] = 0x17;//���ض˿�0��Ŀ�Ķ˿ں�6000
	S0_DPort[1] = 0x70;
	

/***********************************************************/	

/***********************************************************/
	S1_Port[0] = 0x13;//���ض˿�1�Ķ˿ں�5000 
	S1_Port[1] = 0x88;

//	S0_DIP[0]=192;//���ض˿�0��Ŀ��IP��ַ
//	S0_DIP[1]=168;
//	S0_DIP[2]=1;
//	S0_DIP[3]=190;
//	
//	S0_DPort[0] = 0x17;//���ض˿�0��Ŀ�Ķ˿ں�6000
//	S0_DPort[1] = 0x70;

    InitLocalIPGateway();              //��ʼ������IP���������롢����

  	Init_MAC_Address();                //��ʼ��Mac��ַ
//	
  	InitRemoteIPandPORT();             //Զ��IP�˿ڳ�ʼ��





//	UDP_DIPR[0]=192;//���ض˿�0��Ŀ��IP��ַ
//	UDP_DIPR[1]=168;
//	UDP_DIPR[2]=1;
//	UDP_DIPR[3]=101;

	UDP_DPORT[0] = 0x13;//���ض˿�0�Ķ˿ں�5000 
	UDP_DPORT[1] = 0x88;



	S0_Mode=TCP_CLIENT ;        //���ض˿�0�Ĺ���ģʽ,TCP�ͻ���ģʽ
	S1_Mode=TCP_SERVER;         //���ض˿�1�Ĺ���ģʽ,TCP�����ģʽ
	S2_Mode=UDP_MODE;           //���ض˿�1�Ĺ���ģʽ,UDPģʽ
/***********************************************************/	
	
}

/*******************************************************************************
* ������  : W5500_Socket_Set
* ����    : W5500�˿ڳ�ʼ������
* ����    : ��
* ���    : ��
* ����ֵ  : ��
* ˵��    : �ֱ�����4���˿�,���ݶ˿ڹ���ģʽ,���˿�����TCP��������TCP�ͻ��˻�UDPģʽ.
*			�Ӷ˿�״̬�ֽ�Socket_State�����ж϶˿ڵĹ������
*******************************************************************************/
void W5500_Socket_Set(void)
{
	if(S0_State==0)//�˿�0��ʼ������
	{
		if(S0_Mode==TCP_SERVER)//TCP������ģʽ 
		{
			if(Socket_Listen(0)==TRUE)
				S0_State=S_INIT;
			else
				S0_State=0;
		}
		else if(S0_Mode== TCP_CLIENT)//TCP�ͻ���ģʽ 
		{
			if(Socket_Connect(0)==TRUE)
				S0_State=S_INIT;
			else
				S0_State=0;
		}
		else//UDPģʽ 
		{
			if(Socket_UDP(0)==TRUE)
				S0_State=S_INIT|S_CONN;
			else
				S0_State=0;
		}
	}
	
	if(S1_State==0)//�˿�0��ʼ������
		{
			if(S1_Mode==TCP_SERVER)//TCP������ģʽ 
			{
				if(Socket_Listen(1)==TRUE)
					S1_State=S_INIT;
				else
					S1_State=0;
			}
			else if(S1_Mode== TCP_CLIENT)//TCP�ͻ���ģʽ 
			{
				if(Socket_Connect(1)==TRUE)
					S1_State=S_INIT;
				else
					S1_State=0;
			}
			else//UDPģʽ 
			{
				if(Socket_UDP(1)==TRUE)
					S1_State=S_INIT|S_CONN;
				else
					S1_State=0;
			}
		}
	
	if(S2_State==0)//�˿�0��ʼ������
	{
		if(S2_Mode==TCP_SERVER)//TCP������ģʽ 
		{
			if(Socket_Listen(2)==TRUE)
				S2_State=S_INIT;
			else
				S2_State=0;
		}
		else if(S2_Mode==TCP_CLIENT)//TCP�ͻ���ģʽ 
		{
			if(Socket_Connect(2)==TRUE)
				S2_State=S_INIT;
			else
				S2_State=0;
		}
		else//UDPģʽ 
		{
			if(Socket_UDP(2)==TRUE)
				S2_State=S_INIT|S_CONN;
			else
				S2_State=0;
		}
	}
		
		
		
		
	
}

/*******************************************************************************
* ������  : Process_Socket_Data
* ����    : W5500���ղ����ͽ��յ�������
* ����    : s:�˿ں�
* ���    : ��
* ����ֵ  : ��
* ˵��    : �������ȵ���S_rx_process()��W5500�Ķ˿ڽ������ݻ�������ȡ����,
*			Ȼ�󽫶�ȡ�����ݴ�Rx_Buffer������Temp_Buffer���������д���
*			������ϣ������ݴ�Temp_Buffer������Tx_Buffer������������S_tx_process()
*			�������ݡ�
*******************************************************************************/
void Process_Socket_Data(SOCKET s)
{
	unsigned short size;
	size=Read_SOCK_Data_Buffer(s, S0_Rx_Buffer);
	memcpy(S0_Tx_Buffer, S0_Rx_Buffer, size);			
	Write_SOCK_Data_Buffer(s, S0_Tx_Buffer, size);
	  
}





/*******************************************************************************
* ������  : Process_Socket_PROT0_Send
* ����    : W5500����ָ�������ַ���
* ����    : *Tx_Buffer123��Ҫ���͵��ַ���,len���ݳ���
* ���    : ��
* ����ֵ  : ��
* ˵��    : �����̳���
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
* ������  : Process_Socket_PROT1_Send
* ����    : W5500����ָ�������ַ���
* ����    : *Tx_Buffer123��Ҫ���͵��ַ���,len���ݳ���
* ���    : ��
* ����ֵ  : ��
* ˵��    : �����̳���
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
* ������  : Process_Socket_PROT0_Send
* ����    : W5500����ָ�������ַ���
* ����    : *Tx_Buffer123��Ҫ���͵��ַ���,len���ݳ���
* ���    : ��
* ����ֵ  : ��
* ˵��    : �����̳���
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
* ������  : Process_Socket_PROT1_Send
* ����    : W5500����ָ�������ַ���
* ����    : *Tx_Buffer123��Ҫ���͵��ַ���,len���ݳ���
* ���    : ��
* ����ֵ  : ��
* ˵��    : �����̳���
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
* ������  : Process_Socket_PROT1_Send
* ����    : W5500����ָ�������ַ���
* ����    : *Tx_Buffer123��Ҫ���͵��ַ���,len���ݳ���
* ���    : ��
* ����ֵ  : ��
* ˵��    : �����̳���
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
* ������  : W5500_SYSTEM_Init
* ����    : W5500��ʼ������
* ����    : ��
* ���    : ��
* ����ֵ  : int:����ֵΪһ��16λ������
* ˵��    : ��
*******************************************************************************/
void W5500_SYSTEM_Init(void)
{
	System_Initialization();	//STM32ϵͳ��ʼ������(��ʼ��STM32����)
	Load_Net_Parameters();		//װ���������	
	W5500_Hardware_Reset();		//Ӳ����λW5500
	W5500_Initialization();		//W5500��ʼ������	
	
}

/*******************************************************************************
* ������  : W5500_System_Program
* ����    : W5500������
* ����    : ��
* ���    : ��
* ����ֵ  : int:����ֵΪһ��16λ������
* ˵��    : ��
*******************************************************************************/
void W5500_System_Program(void)
{
		W5500_Socket_Set();                       //W5500�˿ڳ�ʼ������

		if(W5500_Interrupt)                       //����W5500�ж�		
		{
			W5500_Interrupt_Process();              //W5500�жϴ��������
		}
		if((S0_Data & S_RECEIVE) == S_RECEIVE)    //���Socket0���յ�����
		{
			S0_Data&=~S_RECEIVE;
		//	Process_Socket_Data(0);               //W5500���ղ����ͽ��յ�������			
      Process_Socket_PROT0_Receive(0);      //W5500�������ݲ�������������			
		}
		
	 if((S1_Data & S_RECEIVE) == S_RECEIVE)      //���Socket1���յ�����
		{
			S1_Data&=~S_RECEIVE;
		//	Process_Socket_Data(0);               //W5500���ղ����ͽ��յ�������	
		
      Process_Socket_PROT1_Receive(1);      //W5500�������ݲ�������������	
		}
		
	 if((S2_Data & S_RECEIVE) == S_RECEIVE)    //���Socket2���յ�����
		{
			S2_Data&=~S_RECEIVE;
			Process_Socket_PROT2_Receive(2);                //W5500���ղ����ͽ��յ�������
				
		}	
		
		
		
		
		
//		else if(W5500_Send_Delay_Counter >= 500)//��ʱ�����ַ���
//		{
//			if(S0_State == (S_INIT|S_CONN))
//			{
//				S0_Data&=~S_TRANSMITOK;
//				memcpy(Tx_Buffer, "\r\nWelcome To YiXinElec!\r\n", 23);	
//				
//					printf(" %d \n" , S0_State);
//				
//				Write_SOCK_Data_Buffer(0, Tx_Buffer, 23);//ָ��Socket(0~7)�������ݴ���,�˿�0����23�ֽ�����
//			}
//			W5500_Send_Delay_Counter=0;
//		}
		
}



/*******************************************************************************
* ������  : NVIC_Configuration
* ����    : STM32�ж�������������
* ����    : ��
* ���    : ��
* ����ֵ  : ��
* ˵��    : �����ж�������
*******************************************************************************/
void NVIC_Configuration(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;						//����NVIC��ʼ���ṹ��

  	/* Set the Vector Table base location at 0x08000000 */
//  NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);				//�����ж����ȼ���Ϊ1��������(����0��4λ)
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;				//�����ж�������
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;	//�����������ȼ�
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;			//������Ӧ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;				//ʹ��NVIC
	NVIC_Init(&NVIC_InitStructure);

  W5500_NVIC_Configuration();	//W5500 ���������ж����ȼ�����
}

/*******************************************************************************
* ������  : Timer2_Init_Config
* ����    : Timer2��ʼ������
* ����    : ��
* ���    : ��
* ����    : �� 
* ˵��    : ��
*******************************************************************************/
void Timer2_Init_Config(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);		//ʹ��Timer2ʱ��
	
	TIM_TimeBaseStructure.TIM_Period = 9;						//��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ(������10Ϊ1ms)
	TIM_TimeBaseStructure.TIM_Prescaler = 7199;					//����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ(10KHz�ļ���Ƶ��)
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;		//����ʱ�ӷָ�:TDTS = TIM_CKD_DIV1
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;	//TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);				//����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
	 
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE ); 				//ʹ��TIM2ָ�����ж�
	
	TIM_Cmd(TIM2, ENABLE);  									//ʹ��TIMx����
}

/*******************************************************************************
* ������  : TIM2_IRQHandler
* ����    : ��ʱ��2�ж϶Ϸ�����
* ����    : ��
* ���    : ��
* ����    : �� 
* ˵��    : ��
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
* ������  : System_Initialization
* ����    : STM32ϵͳ��ʼ������(��ʼ��STM32ʱ�Ӽ�����)
* ����    : ��
* ���    : ��
* ����    : �� 
* ˵��    : ��
*******************************************************************************/
void System_Initialization(void)
{

  NVIC_Configuration();		//STM32�ж�������������
	SPI_Configuration();		//W5500 SPI��ʼ������(STM32 SPI1)
	Timer2_Init_Config();		//Timer2��ʼ������
	W5500_GPIO_Configuration();	//W5500 GPIO��ʼ������	
}

/*******************************************************************************
* ������  : Delay
* ����    : ��ʱ����(ms)
* ����    : d:��ʱϵ������λΪ����
* ���    : ��
* ����    : �� 
* ˵��    : ��ʱ������Timer2��ʱ��������1����ļ�����ʵ�ֵ�
*******************************************************************************/
void Delay(unsigned int d)
{
	Timer2_Counter=0; 
	while(Timer2_Counter < d);
}
