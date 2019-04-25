#ifndef __BC95_H
#define __BC95_H
#include "sys.h"

#define   IMEI_SIZE            15                //IMEI�� ����
#define   IMSI_SIZE            15                //IMSI�� ����

/*************************************************************
��ʼ������
**************************************************************/

#define         INITSTEP_START             0                             //����
#define         INITSTEP_AT                1                             // 
#define         INITSTEP_CGSN              2                             // 
#define         INITSTEP_CIMI              3                             // 
#define         INITSTEP_NNMI_C            4                             // 
#define         INITSTEP_NNMI              5                             // 
#define         INITSTEP_NCDP_C            6                             // 
#define         INITSTEP_CFUN_N            7                             // 
#define         INITSTEP_NCDP              8                             // 
#define         INITSTEP_CFUN_F            9                             // 
#define         INITSTEP_NRB               10                             // 
#define         INITSTEP_CGATT_C           11                             // 
#define         INITSTEP_CCLK_C            12                             // 
                           // 
/*************************************************************
���ش�����
**************************************************************/
#define         BC95_OK                 0                               //OK
#define         STRING_ERR              1                               //��Ԥ�ڷ����ַ���
#define         CONNECT_ERR             2                               //��ģ�����Ӵ���
#define         QUERY_BAUD_ERR          3                               //�����ʴ���
#define         CLOSE_SOCKET_ERR        4
#define         CLOSE_CONTEXT_ERR       5
#define         SQ_ERR                  6                               //�źŲ�ѯ����
#define         REG_ERR                 7                               //����ע��ʧ��
#define         GREG_ERR                8                               //GPRS����ʧ��
#define         SET_CONTEXT_ERR         9
#define         ACT_CONTEXT_ERR         10

#define         CGSN_ERR                11
#define         CIMI_ERR                12
#define         NNMI_C_ERR              13
#define         NNMI_ERR                14
#define         NCDP_C_ERR              15
#define         CFUN_N_ERR              16
#define         NCDP_ERR                17
#define         CFUN_F_ERR              18
#define         NRB_ERR                 19
#define         CGATT_C_ERR             20
#define         CCLK_C_ERR              21

#define         QUERY_PIN_ERR           50                              //��SIM������SIM����PIN��
#define         BACK_TO_TRAN_ACCESS_MODE_ERR    51
#define         OVER_TIME               52


#define  BC95_UART		USART1	//����EC20�Ĵ���.

#define  RX_BUFF_LEN        COM_SIZE                          //���ջ������鳤��

#define  BC95REST  PAout(8)                                  // PA8	 EC20��λ����

extern u16 g_u16OverTimeCnt;                                //�뵹��ʱ��������Ҫ��ÿ���Լ�1

extern u16 g_u8RxIndexW;                                    //���ڽ��ռ�����д�������� ����ΪRxDataBuff���鳤�� RX_BUFF_LEN

extern u8  RxDataBuff[];                                    //���ڽ���BUFF

//extern uint16_t g_u16OverTimeCnt;                                      //�뵹��ʱ��������Ҫ��ÿ���Լ�1
extern    uint8_t  BC95_IMEI[]  ;             //BC95��IMEI��
extern    uint8_t  SIM_IMSI []  ;             //BC95��IMEI��
extern  	uint8_t  BC95_CLOCK[];              //BC95����ʱ��

extern    uint8_t  BC95_USER_buff[];      //BC95�û�����
void InitBC95Combuff(void);  //��ʼ��BC95����ͨѶ������


void QuectelBC95_ConnectNet(uint8_t star);

void BC95_SendString(uint8_t *combuff ,uint16_t len);
#endif


