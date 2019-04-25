#ifndef	__SPEAK_H__
#define	__SPEAK_H__
#include  "sys.h"




/*SYN6288 ����*/

#define  SYN6288CMD_VOICE_PLAY            0X01              //�ϳɲ�������
#define  SYN6288CMD_STOP_SYNTHES          0X02              //ֹͣ�ϳ�
#define  SYN6288CMD_PAUSE_SYNTHES         0X03              //��ͣ�ϳ�
#define  SYN6288CMD_RECOVERY_SYNTHES      0X04              //�ָ��ϳ�
#define  SYN6288CMD_STATE_QUERY           0X21              //״̬��ѯ
#define  SYN6288CMD_POWER_DOWN            0X88              //оƬ����
#define  SYN6288CMD_SET_BPS               0X32              //���ò�����



/*SYN6288 �������*/


#define  SYN6288CMDPARAM_PLAY_MUSIC0     0X00              //���������� GB2312��ʽ
#define  SYN6288CMDPARAM_PLAY_MUSIC1     0X08              //��������1 GB2312��ʽ       
#define  SYN6288CMDPARAM_PLAY_MUSIC2     0X10              //��������2 GB2312��ʽ
#define  SYN6288CMDPARAM_PLAY_MUSIC3     0X18              //��������3 GB2312��ʽ
#define  SYN6288CMDPARAM_PLAY_MUSIC4     0X20              //��������4 GB2312��ʽ
#define  SYN6288CMDPARAM_PLAY_MUSIC5     0X28              //��������5 GB2312��ʽ

//#define KEY_SIZE 20Voice playback

/**********************************************************
//�ⲿ��������
**********************************************************/


	
//extern u8  showStandby;//��ʾ����
//extern u32 Standbycount;//����ʾ����ʱ��ʱ����

//extern u8 showtime;//��ʾʱ��
//extern u32 timecount;//����ʾʱ��ʱ��ʱ����

//extern u32 keyidx;//�ַ����ո���
//extern u8 keybuff[];//���յ��ַ�



//extern u32 key;      //����ֵ



/**********************************************************
//�ⲿ��������
**********************************************************/

#define SPEAK_SDA    PBout(7)// PB7

#define SC8002_SHDN  PBout(6)// PB6


void SC50X0_SDA(unsigned char data);


void SPEAK_USART_TX_init(void);

void MUSART1_SendData(uint8_t data);
void SPEAKUART_SendString(uint8_t *speakcombuff ,uint16_t len);

void  SYN6288_Send(uint8_t function ,uint8_t Cmdparam , uint8_t *data ,uint8_t len);
#endif
