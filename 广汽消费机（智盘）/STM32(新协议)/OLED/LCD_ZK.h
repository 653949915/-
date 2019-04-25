//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;

//
//  �� �� ��   : LCD_ZK.H
//  �� �� ��   : v2.0
//  ��    ��   :
//  ��������   : 2014-0101
//  ����޸�   : 
//  ��������   : �ֿ�� OLED SPI�ӿ���ʾ����(STM32ϵ��)
//              ˵��: 
//              ------------------------����ΪOLED��ʾ���õ��Ľӿ----------------------------------------
//              GND    ��Դ��
//              VCC  ��5V��3.3v��Դ
//              D0   PA2��CLK��
//              D1   PA3��DIN��
//              RES  PA4
//              DC   PA5
//              CS   PA1                
//              --------------------------����ΪOLED��ʾ���õ��Ľӿ�--------------------------------------
//              ------------------------����ΪOLED�ֿⲿ�����õ��Ľӿ----------------------------------------
//              OUT   PB10	SPI	
//              IN  	PB11
//              SCK   PB9
//              CS2   PB7                
//              --------------------------����ΪOLED�ֿⲿ�����õ��Ľӿ�--------------------------------------
// �޸���ʷ   :
// ��    ��   : 


//******************************************************************************/
//#include "sys.h"
#define _LCD_ZK_H_
#ifdef _LCD_ZK_H_




/*LCD 12864*/
#define RS_H GPIO_SetBits(GPIOE,GPIO_Pin_9) //RS=1   4PIN
#define RS_L GPIO_ResetBits(GPIOE,GPIO_Pin_9) //RS=0

#define RW_H GPIO_SetBits(GPIOE,GPIO_Pin_8) //RW=1    5PIN
#define RW_L GPIO_ResetBits(GPIOE,GPIO_Pin_8);  //RW = 0

#define EN_H GPIO_SetBits(GPIOE,GPIO_Pin_7);    //EN = 1   6PIN
#define EN_L GPIO_ResetBits(GPIOE,GPIO_Pin_7);  //EN = 0

//#define RST_H GPIO_SetBits(GPIOE,GPIO_Pin_10);    //EN = 1   6PIN
//#define RST_L GPIO_ResetBits(GPIOE,GPIO_Pin_10);  //EN = 0




/* the macro definition to trigger the led on or off 
 * 1 - off
 - 0 - on
 */
//#define ON  0
//#define OFF 1

//���κ꣬��������������һ��ʹ��
#define lcd_cs1(a)	if (a)	\
					GPIO_SetBits(GPIOE,GPIO_Pin_7);\
					else		\
					GPIO_ResetBits(GPIOE,GPIO_Pin_7)

#define lcd_rs(a)	if (a)	\
					GPIO_SetBits(GPIOE,GPIO_Pin_8);\
					else		\
					GPIO_ResetBits(GPIOE,GPIO_Pin_8)

#define lcd_reset(a)	if (a)	\
					GPIO_SetBits(GPIOE,GPIO_Pin_9);\
					else		\
					GPIO_ResetBits(GPIOE,GPIO_Pin_9)

#define lcd_sid(a)	if (a)	\
					GPIO_SetBits(GPIOE,GPIO_Pin_10);\
					else		\
					GPIO_ResetBits(GPIOE,GPIO_Pin_10)

#define lcd_sclk(a)	if (a)	\
					GPIO_SetBits(GPIOE,GPIO_Pin_11);\
					else		\
					GPIO_ResetBits(GPIOE,GPIO_Pin_11)
					
			/************ �ֿ�   *************/		
					
#define Rom_CS(a)	if (a)	\
					GPIO_SetBits(GPIOE,GPIO_Pin_13);\
					else		\
					GPIO_ResetBits(GPIOE,GPIO_Pin_13)

#define Rom_SCK(a)	if (a)	\
					GPIO_SetBits(GPIOE,GPIO_Pin_12);\
					else		\
					GPIO_ResetBits(GPIOE,GPIO_Pin_12)

#define Rom_OUT(a)	if (a)	\
					GPIO_SetBits(GPIOE,GPIO_Pin_15);\
					else		\
					GPIO_ResetBits(GPIOE,GPIO_Pin_15)

#define Rom_IN(a)	if (a)	\
					GPIO_SetBits(GPIOE,GPIO_Pin_14);\
					else		\
					GPIO_ResetBits(GPIOE,GPIO_Pin_14)

#define ROM_OUT    GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_15)

extern unsigned char const bmp1[];
extern unsigned char const jiong1[];
extern unsigned char const lei1[];
extern unsigned char  NUMBER[11][16];
extern unsigned char  SMALLNUMBER[12][12];
void display_graphic_12x12(unsigned int page,unsigned char column,unsigned char *dp);			
					
/*дָ�LCDģ��*/
void transfer_command_lcd(int data1);   
/*д���ݵ�LCDģ��*/
void transfer_data_lcd(int data1);
/*��ʱ*/
void delay(int n_ms);               
/*LCDģ���ʼ��*/
void OLED_Init(void);
void lcd_address(unsigned char page,unsigned char column);
/*ȫ������*/
void clear_screen(void);
/*��ʾ128x64����ͼ��*/
void display_128x64(const unsigned char *dp);
/*��ʾ132x64����ͼ��*/
//void display_132x64(unsigned char *dp);
/*��ʾ16x16����ͼ�񡢺��֡���Ƨ�ֻ�16x16���������ͼ��*/
void display_graphic_16x16(unsigned int page,unsigned int column,const unsigned char *dp);
/*��ʾ8x16����ͼ��ASCII, ��8x16����������ַ�������ͼ��*/
void display_graphic_8x16(unsigned int page,unsigned char column,unsigned char *dp);
/*��ʾ5*7����ͼ��ASCII, ��5x7����������ַ�������ͼ��*/
void display_graphic_5x7(unsigned int page,unsigned char column,unsigned char *dp);
/****��ָ�����Ѷ�ֿ�IC***/
void send_command_to_ROM( unsigned char datu );
/****�Ӿ���Ѷ�ֿ�IC��ȡ���ֻ��ַ����ݣ�1���ֽڣ�***/
static unsigned char get_data_from_ROM(void);
/*����ص�ַ��addrHigh����ַ���ֽ�,addrMid����ַ���ֽ�,addrLow����ַ���ֽڣ�����������DataLen���ֽڵ����ݵ� pBuff�ĵ�ַ*/
/*������ȡ*/
void get_n_bytes_data_from_ROM(unsigned char addrHigh,unsigned char addrMid,unsigned char addrLow,unsigned char *pBuff,unsigned char DataLen );
/******************************************************************/
void display_GB2312_string(unsigned char y,unsigned char x,unsigned char *text);
void display_string_5x7(unsigned char y,unsigned char x,unsigned char *text);


void OLED_GPIO_Config(void);

#endif
