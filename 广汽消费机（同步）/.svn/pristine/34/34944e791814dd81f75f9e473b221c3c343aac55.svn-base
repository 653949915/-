//////////////////////////////////////////////////////////////////////////////////	 
//±¾³ÌĞòÖ»¹©Ñ§Ï°Ê¹ÓÃ£¬Î´¾­×÷ÕßĞí¿É£¬²»µÃÓÃÓÚÆäËüÈÎºÎÓÃÍ¾

//
//  ÎÄ ¼ş Ãû   : LCD_ZK.H
//  °æ ±¾ ºÅ   : v2.0
//  ×÷    Õß   :
//  Éú³ÉÈÕÆÚ   : 2014-0101
//  ×î½üĞŞ¸Ä   : 
//  ¹¦ÄÜÃèÊö   : ×Ö¿â°æ OLED SPI½Ó¿ÚÑİÊ¾Àı³Ì(STM32ÏµÁĞ)
//              ËµÃ÷: 
//              ------------------------ÒÔÏÂÎªOLEDÏÔÊ¾ËùÓÃµ½µÄ½Ó¿----------------------------------------
//              GND    µçÔ´µØ
//              VCC  ½Ó5V»ò3.3vµçÔ´
//              D0   PA2£¨CLK£©
//              D1   PA3£¨DIN£©
//              RES  PA4
//              DC   PA5
//              CS   PA1                
//              --------------------------ÒÔÉÏÎªOLEDÏÔÊ¾ËùÓÃµ½µÄ½Ó¿Ú--------------------------------------
//              ------------------------ÒÔÏÂÎªOLED×Ö¿â²¿·ÖËùÓÃµ½µÄ½Ó¿----------------------------------------
//              OUT   PB10	SPI	
//              IN  	PB11
//              SCK   PB9
//              CS2   PB7                
//              --------------------------ÒÔÉÏÎªOLED×Ö¿â²¿·ÖËùÓÃµ½µÄ½Ó¿Ú--------------------------------------
// ĞŞ¸ÄÀúÊ·   :
// ÈÕ    ÆÚ   : 


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

//´ø²Îºê£¬¿ÉÒÔÏñÄÚÁªº¯ÊıÒ»ÑùÊ¹ÓÃ
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
					
			/************ ×Ö¿â   *************/		
					
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
					
/*Ğ´Ö¸Áîµ½LCDÄ£¿é*/
void transfer_command_lcd(int data1);   
/*Ğ´Êı¾İµ½LCDÄ£¿é*/
void transfer_data_lcd(int data1);
/*ÑÓÊ±*/
void delay(int n_ms);               
/*LCDÄ£¿é³õÊ¼»¯*/
void OLED_Init(void);
void lcd_address(unsigned char page,unsigned char column);
/*È«ÆÁÇåÆÁ*/
void clear_screen(void);
/*ÏÔÊ¾128x64µãÕóÍ¼Ïñ*/
void display_128x64(const unsigned char *dp);
/*ÏÔÊ¾132x64µãÕóÍ¼Ïñ*/
//void display_132x64(unsigned char *dp);
/*ÏÔÊ¾16x16µãÕóÍ¼Ïñ¡¢ºº×Ö¡¢ÉúÆ§×Ö»ò16x16µãÕóµÄÆäËûÍ¼±ê*/
void display_graphic_16x16(unsigned int page,unsigned int column,const unsigned char *dp);
/*ÏÔÊ¾8x16µãÕóÍ¼Ïñ¡¢ASCII, »ò8x16µãÕóµÄ×ÔÔì×Ö·û¡¢ÆäËûÍ¼±ê*/
void display_graphic_8x16(unsigned int page,unsigned char column,unsigned char *dp);
/*ÏÔÊ¾5*7µãÕóÍ¼Ïñ¡¢ASCII, »ò5x7µãÕóµÄ×ÔÔì×Ö·û¡¢ÆäËûÍ¼±ê*/
void display_graphic_5x7(unsigned int page,unsigned char column,unsigned char *dp);
/****ËÍÖ¸Áîµ½¾§ÁªÑ¶×Ö¿âIC***/
void send_command_to_ROM( unsigned char datu );
/****´Ó¾§ÁªÑ¶×Ö¿âICÖĞÈ¡ºº×Ö»ò×Ö·ûÊı¾İ£¨1¸ö×Ö½Ú£©***/
static unsigned char get_data_from_ROM(void);
/*´ÓÏà¹ØµØÖ·£¨addrHigh£ºµØÖ·¸ß×Ö½Ú,addrMid£ºµØÖ·ÖĞ×Ö½Ú,addrLow£ºµØÖ·µÍ×Ö½Ú£©ÖĞÁ¬Ğø¶Á³öDataLen¸ö×Ö½ÚµÄÊı¾İµ½ pBuffµÄµØÖ·*/
/*Á¬Ğø¶ÁÈ¡*/
void get_n_bytes_data_from_ROM(unsigned char addrHigh,unsigned char addrMid,unsigned char addrLow,unsigned char *pBuff,unsigned char DataLen );
/******************************************************************/
void display_GB2312_string(unsigned char y,unsigned char x,unsigned char *text);
void display_string_5x7(unsigned char y,unsigned char x,unsigned char *text);


void OLED_GPIO_Config(void);

#endif
