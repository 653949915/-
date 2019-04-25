

/***************************************************************************************************
	* Copyright (c) 2016, Biohermes
	* All rights reserved.
	* �ļ����ƣ� QuectelMC20.c
	* ժ Ҫ��    MC20ģ��
	* ��ǰ�汾�� V1.0, , 2016-01-05
	* ���ļ�¼�� ��
	* �ػ�״̬��,MC20���ڿ��ܻᷢ��������������������̵���ͨ��MC20��MCU�Ĵ���
***************************************************************************************************/
//#include "QuectelMC20.h"

//C��
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "head.h"
#include "BC95.h"

#ifdef   NB_BC95

//static  uint8_t AT_QISEND[]   = {"AT+QISEND=10\r\n"};

static  uint8_t AT_AT[]         = {"AT\r\n"};                            //���Ӳ�������
static  uint8_t AT_CGSN[]       = {"AT+CGSN=1\r\n"};                     //��ѯ�豸IMEI��
static  uint8_t AT_CIMI[]       = {"AT+CIMI\r\n"};                       //��ѯUSIM��IMSI��
static  uint8_t AT_NNMI_C[]     = {"AT+NNMI?\r\n"};                      //�鿴��������֪ͨ
static  uint8_t AT_NNMI[]       = {"AT+NNMI=1\r\n"};                     //�鿴��������֪ͨ
static  uint8_t AT_NCDP_C[]     = {"AT+NCDP?\r\n"};                      //��ѯ IOT ƽ̨ IP ��ַ
static  uint8_t AT_CGATT_C[]    = {"AT+CGATT?\r\n"};                    //�鿴ģ���Ƿ�������ɹ�
static  uint8_t AT_CCLK_C[]     = {"AT+CCLK?\r\n"};                      //��ȡ����ʱ��
//       
static  uint8_t AT_CFUN_N[]     = {"AT+CFUN=0\r\n"};                      //���õ绰����
static  uint8_t AT_NCDP[]       = {"AT+NCDP=117.60.157.137,5683\r\n"};    //����IP
static  uint8_t AT_CFUN_F[]     = {"AT+CFUN=1\r\n"};                      //���õ绰����
static  uint8_t AT_NRB[]        = {"AT+NRB\r\n"};                         //����

//AT+CFUN=0
//AT+NCDP=117.60.157.137,5683
//AT+NCDP=117.78.47.187,5683
//AT+NCDP=112.93.129.154,5683
//AT+CFUN=1
//AT+NRB


 uint8_t fbuff[1]   = {'"'};


// uint8_t NCDP_HW_17[19] = {"117.60.157.137,5683"};                      //

 uint8_t NCDP_HW_17[19] = {"117.60.157.137,5683"};                      //
	
uint8_t  BC95_IMEI[IMEI_SIZE]  = {0};             //BC95��IMEI��
uint8_t  SIM_IMSI [IMSI_SIZE]  = {0};             //BC95��IMEI��
uint8_t  BC95_CLOCK[30]={0};                      //BC95����ʱ��
	
	
//static u8 CGSNbuff[15]={0};
//static u8 CIMIbuff[15]={0};




struct retstruct
{
    u8 ret1;
    u8 ret2;
}s_stRetData;

u16 g_u16OverTimeCnt=0;                             //��ʱ����ʱ��������ÿ���Լ�1
u8  RxDataBuff[RX_BUFF_LEN];                         //�жϽ�������

       u16  g_u8RxIndexW=0;                         //�жϽ�������дָ��
static u16  s_u8RxIndexR=0;                         //�жϽ��������ָ��



//��ʼ��PA8Ϊ�����.��ʹ���������ڵ�ʱ��		    

void BC95_REST_Init(void)
{
 
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	 //ʹ��PA�˿�ʱ��
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;				  //GSM_POWER-->PA.8 �˿����� ���ػ�
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 	//�������
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//IO���ٶ�Ϊ50MHz
 GPIO_Init(GPIOA, &GPIO_InitStructure);					    //�����趨������ʼ��GPIOA.8
 GPIO_SetBits(GPIOA,GPIO_Pin_8);						        //PA.8 �����
		
}
 


void BC95_SendString(uint8_t *combuff ,uint16_t len)
{
	uint16_t t;
	for(t=0;t<len;t++)
	 {
		  USART_SendData(BC95_UART, combuff[t]);//�򴮿�1��������
			
			while(USART_GetFlagStatus(BC95_UART,USART_FLAG_TC)!=SET);//�ȴ����ͽ���
	
   }
}

void BC95_SendByte(uint8_t combuff)
{
  //    delay_us(500);
		USART_SendData(BC95_UART, combuff);//�򴮿�1��������
	
		while(USART_GetFlagStatus(BC95_UART,USART_FLAG_TC)!=SET);//�ȴ����ͽ���
}


/***************************************************************************************************
 * �� �� ��: QuectelBC95_Rest
 * ��������: BC95 Ӳ����λ
 * ����˵��: 
 * ���ú���: ��
 * ȫ�ֱ���: ��
 * �䡡����: ��
 * ��������: ��
***************************************************************************************************/
void QuectelBC95_Rest(void)
{
	BC95REST =0;         //��λ�������� 500ms
	
	delay_ms(500);
	delay_ms(500);
	
	BC95REST =1;
	
}

/***************************************************************************************************
 * �� �� ��: QuectelBC95_SendCmd
 * ��������: BC95�ײ㷢������
 * ����˵��: 
 * ���ú���: ��
 * ȫ�ֱ���:
 * �䡡����: *string ��Ҫ���͵��ַ���ָ��
 * ��������: ��
***************************************************************************************************/
 void QuectelBC95_SendCmd(const u8 *string)
{
    u8 i = 0;
    
    while (string[i] != 0)
    {
        if (string[i] == '*')
        {
            BC95_SendByte('"');
        }
        else
        {
            BC95_SendByte(string[i]);
        }
        i++;
    }
    s_u8RxIndexR = 0;
    g_u8RxIndexW = 0;
}

/***************************************************************************************************
 * �� �� ��: GetAckData
 * ��������: �ȽϽ��յ����ݺ͸����ַ����Ƿ���ͬ
 * ����˵��: ��
 * ���ú���: ��
 * ȫ�ֱ���: ��
 * �䡡����: buff ��Ҫ�Ƚϵ����飬 *string�����ַ���ָ��
 * ��������: ״̬
***************************************************************************************************/
 u8 GetAckData(char *string, u16 overtime)
{
    u8 j=0;
    
    g_u16OverTimeCnt = overtime;
    while (1)
    {
        if (s_u8RxIndexR != g_u8RxIndexW)
        {
					
            if (string[j] == RxDataBuff[s_u8RxIndexR])
                j++;
            else
                j = 0;
            if (string[j] == 0)
                return BC95_OK;
            s_u8RxIndexR++;
            if (s_u8RxIndexR > RX_BUFF_LEN-1)
                s_u8RxIndexR = 0;
        }
        if (g_u16OverTimeCnt == 0)                      //��ʱ�˳�
            return OVER_TIME;
    }
}

/***************************************************************************************************
 * �� �� ��: ExpectReceData
 * ��������: �ȽϽ��յ����ݺ͸����ַ����Ƿ���ͬ��Ȼ�����ʣ�µ�����
 * ����˵��: ret�ṹ��ʱֻ������������ֵ��
 * ���ú���: ��
 * ȫ�ֱ���: ��
 * �䡡����: *string�����ַ���ָ��, overtime��ʱʱ�䣬 ret��������ֵ�ṹ��
 * ��������: ״̬
***************************************************************************************************/
 u8 ExpectReceData(char *string, u16 overtime, struct retstruct* ret)
{
    u8 i = 0, j = 0, k = 0;
    u8 str[2][5];               //����ascii���ַ������棬��ֻ������������
    
    g_u16OverTimeCnt = overtime;
    while (1)                   //���ж�ǰ��̶��ַ����Ƿ���ȷ
    {
        if (s_u8RxIndexR != g_u8RxIndexW)
        {
            if (string[j] == RxDataBuff[s_u8RxIndexR])
                j++;
            else
                j = 0;
            s_u8RxIndexR++;
            if (s_u8RxIndexR > RX_BUFF_LEN-1)
                s_u8RxIndexR = 0;
            if (string[j] == 0)
                break;
        }
        if (g_u16OverTimeCnt == 0)                      //��ʱ�˳�
            return OVER_TIME;
    }
    i = 0;
    j = 1;                  //���ݴ�Ŵӵڶ����ֽڿ�ʼ����һ���ֽڴ�Ÿ���
    while (1)
    {
        if (s_u8RxIndexR != g_u8RxIndexW)
        {
            if (RxDataBuff[s_u8RxIndexR] == ',')
            {
                str[i][0] = j - 1;              //������յ����ַ�����
                j = 1;
                i++;
            }
            else if (RxDataBuff[s_u8RxIndexR] == '\r')
            {
                k = 1;
            }
            else if (RxDataBuff[s_u8RxIndexR] == '\n')
            {
                if (k)
                {
                    str[i][0] = j - 1;          //\r\nΪ������
                    break;
                }
                else
                {
                    i = 0;
                    j = 1;
                }
            }
            else
            {
                str[i][j] = RxDataBuff[s_u8RxIndexR];
                j++;
            }
            s_u8RxIndexR++;
            if (s_u8RxIndexR > RX_BUFF_LEN-1)
                s_u8RxIndexR = 0;
        }
        if (g_u16OverTimeCnt == 0)                      //��ʱ�˳�
            return OVER_TIME;
    }
    if (str[0][0] == 2)
        ret->ret1 = (str[0][1]-'0')*10 + (str[0][2]-'0');
    else
        ret->ret1 = (str[0][1]-'0');
    if (str[1][0] == 2)
        ret->ret2 = (str[1][1]-'0')*10 + (str[1][2]-'0');
    else
        ret->ret2 = (str[1][1]-'0');
    return BC95_OK;
}




/***************************************************************************************************
 * �� �� ��: ExpectReceData
 * ��������: �ȽϽ��յ����ݺ͸����ַ����Ƿ���ͬ��Ȼ�����ʣ�µ�����
 * ����˵��: ret�ṹ��ʱֻ������������ֵ��
 * ���ú���: ��
 * ȫ�ֱ���: ��
 * �䡡����: *string�����ַ���ָ��, overtime��ʱʱ�䣬 ret��������ֵ�ṹ��
 * ��������: ״̬
***************************************************************************************************/
 uint8_t ExpectReceData_1(unsigned char *string, uint16_t overtime, uint8_t *ret)
{
    uint8_t  j = 0, k = 0;
//    u8 str[2][15];               //����ascii���ַ������棬��ֻ������������
    
	g_u16OverTimeCnt = overtime;
	
    while (1)                   //���ж�ǰ��̶��ַ����Ƿ���ȷ
    {
        if (s_u8RxIndexR != g_u8RxIndexW)
        {
            if (string[j] == RxDataBuff[s_u8RxIndexR])
                j++;
            else
                j = 0;
            s_u8RxIndexR++;
            if (s_u8RxIndexR > RX_BUFF_LEN-1)
                s_u8RxIndexR = 0;
            if (string[j] == 0)
                break;
        }
				
				/* ��ʱ��5000ms */
				if(g_u16OverTimeCnt == 0) 
					{
							
							return OVER_TIME;
					}			
				
    }
		
  //  i = 0;
    j = 0;                  //
    while (1)
    {
        if (s_u8RxIndexR != g_u8RxIndexW)
        {
			
						ret[k] = RxDataBuff[s_u8RxIndexR];
             k++;     
             s_u8RxIndexR++;			

//            if (s_u8RxIndexR > (RX_BUFF_LEN-1))
//                s_u8RxIndexR = 0;						

				//	UART4Send_Data(RxDataBuff,	100);   //������  g_u8RxIndexW
				
					
						if ((RxDataBuff[s_u8RxIndexR-1] == '\r')&&RxDataBuff[s_u8RxIndexR] == '\n')//&&(RxDataBuff[s_u8RxIndexR-1] == 'O')&&(RxDataBuff[s_u8RxIndexR] == 'K'))						
							{
  							  s_u8RxIndexR = 0;	
               //   g_u8RxIndexW = 0;									
								  k=0;
								return BC95_OK; 
						    //  break;						
							}		
        }				
				  /* ��ʱ��5000ms */
		      if(g_u16OverTimeCnt == 0) 
            {
       //         printf("Timeout To Enter Sleep!!\r\n");
                
                return OVER_TIME;
            }	
  //  return BC95_OK;						
    }

		    
}


/**********************************************************
//BC95����AT    �����豸�Ƿ�����
**********************************************************/
void QuectelBC95_AT(void )
{
uint8_t ret = 0;
	QuectelBC95_SendCmd(AT_AT);
	ret = GetAckData("OK\r\n",5);         //	
	if (ret == BC95_OK)
		{
	   bc95_device_info.initStep ++;
	   bc95_device_info.errcount =0;
	  }
	else 
	{
		bc95_device_info.err = CONNECT_ERR;
		bc95_device_info.errcount++;
	}
}

/**********************************************************
//BC95����AT+CGSN=1    ��ѯ�豸IMEI��
**********************************************************/
void QuectelBC95_CGSN(void )
{
uint8_t ret = 0;
uint8_t retbuf[20]={0};

QuectelBC95_SendCmd(AT_CGSN);                             //��ѯ�豸IMEI��

ret = ExpectReceData_1("+CGSN:", 10, retbuf);		//500ms
		
	if (ret == BC95_OK)
		{		
		 MyStrCPY(BC95_IMEI, retbuf, IMEI_SIZE);		
		//	UART4Send_Data(CGSNbuff,	IMEI_SIZE);   //������
	   bc95_device_info.initStep ++;
	   bc95_device_info.errcount =0;
	  }
	else 
	{
		bc95_device_info.err = CGSN_ERR;
		bc95_device_info.errcount++;
	}
}

/**********************************************************
//BC95����AT+CIMI    ��ѯUSIM��IMSI��
**********************************************************/
void QuectelBC95_CIMI(void )
{
uint8_t ret = 0;
uint8_t retbuf[20]={0};

QuectelBC95_SendCmd(AT_CIMI);                          //��ѯUSIM��IMSI��

ret = ExpectReceData_1("\r\n", 10, retbuf);
			 	
	if (ret == BC95_OK)
		{

		 MyStrCPY(SIM_IMSI, retbuf, IMSI_SIZE);		
		//	UART4Send_Data(SIM_IMSI,	IMSI_SIZE);   //������
	   bc95_device_info.initStep ++;
	   bc95_device_info.errcount =0;
	  }
	else 
	{
		bc95_device_info.err = CIMI_ERR;
		bc95_device_info.errcount++;
	}
}

/**********************************************************
//BC95����AT+NNMI?    �鿴��������֪ͨ
**********************************************************/
void QuectelBC95_NNMI_C(void )
{
uint8_t ret = 0;

QuectelBC95_SendCmd(AT_NNMI_C);                             //�鿴��������֪ͨ
Write_SOCK_Data_Buffer(0, AT_NNMI_C, sizeof(AT_NNMI_C) );    //������
ret = ExpectReceData("\r\n+NNMI:", 10, &s_stRetData);

	if (ret==BC95_OK && (s_stRetData.ret1==0))        //δ����
		{
		 //��������֪ͨ
	   bc95_device_info.initStep ++;
	   bc95_device_info.errcount =0;
	  }
	else if(ret==BC95_OK && (s_stRetData.ret1==1))     //����
		{
	   //������ѯIP
		 bc95_device_info.initStep  =INITSTEP_NCDP_C;      
	   bc95_device_info.errcount =0;
		}
		
	else 
		{
			bc95_device_info.err = NNMI_C_ERR;
			bc95_device_info.errcount++;
		}
}

/**********************************************************
//BC95����AT+NNMI=1    ������������֪ͨ
**********************************************************/
void QuectelBC95_NNMI(void )
{
uint8_t ret = 0;

QuectelBC95_SendCmd(AT_NNMI);
Write_SOCK_Data_Buffer(0, AT_NNMI, sizeof(AT_NNMI) );    //������
	
ret = GetAckData("\r\nOK",10);       //������������֪ͨ


	if (ret == BC95_OK)
		{
			
     //������ѯ
	   bc95_device_info.initStep ++;
	   bc95_device_info.errcount =0;
	  }
	else 
	{
		bc95_device_info.err = NNMI_ERR;
		bc95_device_info.errcount++;
	}
}

/**********************************************************
//BC95����AT+NCDP?    ��ѯ IOT ƽ̨ IP ��ַ
**********************************************************/
void QuectelBC95_NCDP_C(void )
{
uint8_t ret = 0;
uint8_t retbuf[30]={0};

QuectelBC95_SendCmd(AT_NCDP_C);                             //��ѯ IOT ƽ̨ IP ��ַ

ret = ExpectReceData_1("+NCDP:", 10, retbuf);   

 if (ret == BC95_OK)
		{
		// MyStrCPY(IOT_IPretbuf, retbuf, 19);
			
		 if(MyStrEQ(retbuf, NCDP_HW_17, 19))	   //����ȷ��IP
			 {
				
			   //������ѯ�����Ƿ���
				 bc95_device_info.initStep = INITSTEP_CGATT_C;
	       bc95_device_info.errcount =0;			  
			 }
			else 
			 {
				 //��������IP
				 bc95_device_info.initStep ++;
	       bc95_device_info.errcount =0;	    
			 }
	  }
	else 
	{
		bc95_device_info.err = NCDP_C_ERR;
		bc95_device_info.errcount++;
	}
}

/**********************************************************
//BC95����AT+CFUN=0    ���ùرյ绰����
**********************************************************/
void QuectelBC95_CFUN_N(void )
{
uint8_t ret = 0;

QuectelBC95_SendCmd(AT_CFUN_N);                      //�رյ绰
	
		Write_SOCK_Data_Buffer(0, AT_CFUN_N, sizeof(AT_CFUN_N) );    //������
ret = GetAckData("\r\nOK\r\n",10);                         //500ms

	if (ret == BC95_OK)
		{
	   bc95_device_info.initStep ++;
	   bc95_device_info.errcount =0;
	  }
	else 
	{
		bc95_device_info.err = CFUN_N_ERR;
		bc95_device_info.errcount++;
	}
}

/**********************************************************
//BC95����AT+NCDP=117.60.157.137,5683    ���ý����IP
**********************************************************/
void QuectelBC95_NCDP(void )
{
uint8_t ret = 0;

QuectelBC95_SendCmd(AT_NCDP);                         //���ý����IP

		Write_SOCK_Data_Buffer(0, AT_NCDP, sizeof(AT_NCDP) );    //������	
	
ret = GetAckData("\r\nOK",10);                     //500ms

	if (ret == BC95_OK)
		{
     //
	   bc95_device_info.initStep ++;
	   bc95_device_info.errcount =0;
	  }
	else 
	{
		bc95_device_info.err = NCDP_ERR;
		bc95_device_info.errcount++;
	}
}

/**********************************************************
//BC95����AT+CFUN=1    ���ÿ����绰����
**********************************************************/
void QuectelBC95_CFUN_F(void )
{
uint8_t ret = 0;

QuectelBC95_SendCmd(AT_CFUN_F);                      //�����绰
		Write_SOCK_Data_Buffer(0, AT_CFUN_F, sizeof(AT_CFUN_F) );    //������		
	
ret = GetAckData("\r\nOK",10);                         //500ms

	if (ret == BC95_OK)
		{
			
     //
	   bc95_device_info.initStep ++;
	   bc95_device_info.errcount =0;
	  }
	else 
	{
		bc95_device_info.err = CFUN_F_ERR;
		bc95_device_info.errcount++;
	}
}

/**********************************************************
//BC95����AT+NRB   ����ģ��
**********************************************************/
void QuectelBC95_NRB(void )
{
uint8_t ret = 0;

QuectelBC95_SendCmd(AT_NRB);                      //����ģ��
	
			Write_SOCK_Data_Buffer(0, AT_NRB, sizeof(AT_NRB) );    //������	
ret = GetAckData("OK",10);                         //5000ms

	if (ret == BC95_OK)
		{
     //ģ����Զ����� ������ʼ
	   bc95_device_info.initStep = INITSTEP_START;     
	   bc95_device_info.errcount =0;
	  }
//	else 
//	{
//		
//		bc95_device_info.err = NRB_ERR;
//		bc95_device_info.errcount++;
//	}
}

/**********************************************************
//BC95����AT+CGATT?    �鿴ģ���Ƿ�������ɹ�
**********************************************************/
void QuectelBC95_CGATT_C(void )
{
uint8_t ret = 0;

QuectelBC95_SendCmd(AT_CGATT_C);                             //�鿴ģ���Ƿ�������ɹ�
  
				Write_SOCK_Data_Buffer(0, AT_CGATT_C, sizeof(AT_CGATT_C) );    //������	
	
ret = ExpectReceData("\r\n+CGATT:", 5, &s_stRetData );

	if (ret==BC95_OK && (s_stRetData.ret1==1))            //���ųɹ�
		{
			
     //
	   bc95_device_info.initStep ++;
	   bc95_device_info.errcount =0;
	  }
	else  if (ret==BC95_OK && (s_stRetData.ret1==0))    //����ʧ��
		{
           //���¼��	
			 bc95_device_info.err = CGATT_C_ERR;
			 bc95_device_info.errcount++;
			
		}
	
	else
		{
			 bc95_device_info.err = CGATT_C_ERR;
			 bc95_device_info.errcount++;
		}
}

/**********************************************************
//BC95����AT+CCLK?    ��ȡ����ʱ��
**********************************************************/
void QuectelBC95_CCLK_C(void )
{
uint8_t ret = 0;
uint8_t retbuf[30]={0};

QuectelBC95_SendCmd(AT_CCLK_C);                             //��ȡ����ʱ��


Write_SOCK_Data_Buffer(0, AT_CCLK_C, sizeof(AT_CCLK_C) );    //������	

ret = ExpectReceData_1("\r\n+CCLK:", 10, retbuf );

 if (ret == BC95_OK)
		{
	   MyStrCPY(BC95_CLOCK, retbuf, 20);
     // MyStrCPY(IOT_IPretbuf, retbuf, 19);
			
		 bc95_device_info.netWork =1;                 //�������ӳɹ�
	   bc95_device_info.initStep = INITSTEP_START;
	   bc95_device_info.errcount =0;

		 Nettime_Tran();          //������ʱ��ת����ʱ���
			
     BC95_User_Send_DATA(1, 11 , retbuf , 1);
			
     User_Reports_Message_Send(BC95_USER_buff, 7);			
			
	  }
	else 
	{
		bc95_device_info.err = CCLK_C_ERR;
		bc95_device_info.errcount++;
	}
}


///***************************************************************************************************
// * �� �� ��: QuectelBC95_ConnectNet
// * ��������: ģ����������
// * ����˵��: ��
// * ���ú���: ��
// * ȫ�ֱ���: ��
// * �䡡����: ��
// * ��������: ������
//***************************************************************************************************/

void QuectelBC95_ConnectNet(uint8_t star)
{

	bc95_device_info.err=BC95_OK;
	
	switch(bc95_device_info.initStep)
	{
	  case  INITSTEP_AT:          delay_ms(1000);  QuectelBC95_AT();  	       break;         //�����豸�Ƿ�����
	  case  INITSTEP_CGSN:        delay_ms(1000);  QuectelBC95_CGSN();  	     break;	       //��ѯ�豸IMEI��
	  case  INITSTEP_CIMI:        delay_ms(1000);  QuectelBC95_CIMI();  	     break;	       //��ѯUSIM��IMSI��
	  case  INITSTEP_NNMI_C:      delay_ms(1000);  QuectelBC95_NNMI_C();  	   break;	       //�鿴��������֪ͨ
	  case  INITSTEP_NNMI:        delay_ms(1000);  QuectelBC95_NNMI();  	     break;	       //������������֪ͨ
	  case  INITSTEP_NCDP_C:      delay_ms(1000);  QuectelBC95_NCDP_C();  	   break;	       //��ѯ IOT ƽ̨ IP ��ַ
	  case  INITSTEP_CFUN_N:      delay_ms(1000);  QuectelBC95_CFUN_N();       break;	       //���ùرյ绰����
	  case  INITSTEP_NCDP:        delay_ms(1000);  QuectelBC95_NCDP();         break;	       //���ý����IP
	  case  INITSTEP_CFUN_F:      delay_ms(1000);  QuectelBC95_CFUN_F();       break;	       //���ÿ����绰����
	  case  INITSTEP_NRB:         delay_ms(1000);  QuectelBC95_NRB();          break;	       //����ģ��
	  case  INITSTEP_CGATT_C:     delay_ms(1000);  QuectelBC95_CGATT_C();      break;	       //�鿴ģ���Ƿ�������ɹ�
	  case  INITSTEP_CCLK_C:      delay_ms(1000);  QuectelBC95_CCLK_C();       break;	       //��ȡ����ʱ��

		default:  break;
	}
	
	if((bc95_device_info.errcount>=10)&&((bc95_device_info.err==CONNECT_ERR)||(bc95_device_info.err==CGSN_ERR)||(bc95_device_info.err==CIMI_ERR)||(bc95_device_info.err==NNMI_C_ERR)))
	{		
    bc95_device_info.netWork =0;                 //��������ʧ��
		
		bc95_device_info.initStep =INITSTEP_START;
		
		QuectelBC95_Rest();		    //��λģ��	
		
//	  return;
	}
	
	if((bc95_device_info.errcount>=30)&&(bc95_device_info.err==CGATT_C_ERR))
	{		
    bc95_device_info.netWork =0;                 //��������ʧ��
		
		bc95_device_info.initStep =INITSTEP_AT;
		
		QuectelBC95_Rest();		    //��λģ��	
		
//	  return;
	}
	
	
	
	if((bc95_device_info.err==NRB_ERR)&&(bc95_device_info.errcount>=2))    //���ӷ�����ʧ��
		{
			bc95_device_info.netWork =0;                 //��������ʧ��
			
		// 	bc95_device_info.initStep =INITSTEP_QICLOSE;
		
		  QuectelBC95_Rest();		    //��λģ��	
			
		}
	
//	if((bc95_device_info.err==QUERY_SOCKET_ERR)&&(ec20_device_info.errcount>=3))    //�ر�sokectʧ��
//	{
//		bc95_device_info.netWork =0;                 //��������ʧ��
//		
//		bc95_device_info.initStep =INITSTEP_START;
//		
//		QuectelBC95_Rest();		    //��λģ��	
//	}	
	
}


	//BC95��ջ�����
void cleanBC95_bcrebuff(void)
{
    uint16_t i=0;
	
    i=	255;
	
	g_u8RxIndexW=0;
	while(i)
	{
	RxDataBuff[--i]=0;

	}
}







	/**********************************************************
//��ʼ��BC95����ͨѶ������
**********************************************************/
void InitBC95Combuff(void)
{
	cleanBC95_bcrebuff();
	
	endcount = 0;	//������־~	
	
	g_u8RxIndexW=0;
	
	s_u8RxIndexR=0;
	
	USART1_RX_CRLF=0;
}





#endif

