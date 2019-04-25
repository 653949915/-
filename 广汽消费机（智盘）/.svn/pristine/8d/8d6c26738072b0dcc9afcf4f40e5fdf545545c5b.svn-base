
#include  "sys.h"

#define Dis_X_MAX		320-1
#define Dis_Y_MAX		240-1

//Define the MCU Register
#define LCD_Ctrl_GPIO()		//PINSEL1 &= ~(0x00003cfc)
#define LCD_Ctrl_Out()		//IODIR0 |= (SPI_SS+SPI_SDA+SPI_SCK+SPI_RES)
#define LCD_Ctrl_In()		//IODIR0 &= ~(SPI_BUSY)
#define LCD_Ctrl_Set(n)		GPIOB->BSRR = n
#define LCD_Ctrl_Clr(n)		GPIOB->BSRR = ((n)<<16)

//#define	LCD_RST				(unsigned int)(0x01<<10)
//#define	LCD_RST_SET()	GPIOB->BSRR = LCD_RST
//#define	LCD_RST_CLR()	GPIOB->BSRR = (LCD_RST<<16)

//#define	LCD_PS				(unsigned int)(0x01<<11)
//#define	LCD_PS_SET()	GPIOE->BSRR = LCD_PS
//#define	LCD_PS_CLR()	GPIOE->BSRR = (LCD_PS<<16)

//#define SPI_SS				(unsigned int)(0x01<<12)
//#define SPI_SS_SET()		GPIOB->BSRR = SPI_SS
//#define SPI_SS_CLR()		GPIOB->BSRR = (SPI_SS<<16)

//#define SPI_SDA				(unsigned int)(0x01<<13)
//#define SPI_SDA_SET()		GPIOB->BSRR = SPI_SDA
//#define SPI_SDA_CLR()		GPIOB->BSRR = (SPI_SDA<<16)

//#define SPI_SCK				(unsigned int)(0x01<<14)
//#define SPI_SCK_SET()		GPIOB->BSRR = SPI_SCK
//#define SPI_SCK_CLR()		GPIOB->BSRR = (SPI_SCK<<16)


#define SPI_SDA_SET()   GPIOE->BSRR=GPIO_Pin_8
#define SPI_SDA_CLR()   GPIOE->BRR=GPIO_Pin_8 

#define SPI_SS_SET()    GPIOE->BSRR=GPIO_Pin_7
#define SPI_SS_CLR()    GPIOE->BRR=GPIO_Pin_7

#define SPI_SCK_SET()  GPIOE->BSRR=GPIO_Pin_9
#define SPI_SCK_CLR()  GPIOE->BRR=GPIO_Pin_9

#define SPI_BLK_SET()  GPIOE->BSRR=GPIO_Pin_11
#define SPI_BLK_CLR()  GPIOE->BRR=GPIO_Pin_11

#define LCD_RST_SET()  GPIOE->BSRR=GPIO_Pin_10
#define LCD_RST_CLR()  GPIOE->BRR=GPIO_Pin_10


#define LCD_ASC8_FONT						  1
#define LCD_ASC12_FONT						2
#define LCD_ASC16_FONT						3

#define LCD_HZK16_FONT						4
#define LCD_HZK24_FONT						5
#define LCD_HZK32_FONT						6

#define CMD_CLEAR_SCREEN				0x01
#define CMD_SET_BG_COLOR				0x02
#define CMD_SET_FG_COLOR				0x04
#define CMD_SET_DISPLAY_ON			0x08
#define CMD_SET_DISPLAY_OFF			0x10
#define CMD_SET_DISPLAY_INVERT		0x11
#define CMD_SET_DISPLAY_NO_INVERT		0x12
#define CMD_SET_WINDOW				0x14
#define CMD_WR_MEMSTART				0x18
#define CMD_ASC_DISPLAY				0x20
#define CMD_HZ_DISPLAY					0x21
#define CMD_END_ASC_DISPLAY			0x22
#define CMD_END_HZ_DISPLAY			0x24
#define CMD_SET_FONT_TYPE				0x28

#define CMD_DRAW_POINT				0x31
#define CMD_DRAW_LINE					0x32
#define CMD_DRAW_RECT					0x34
#define CMD_DRAW_ICON					0x35
#define CMD_DRAW_TRAN_ICON		0x37
#define CMD_DRAW_QRCODE				0x39

#define 	SYN_BYTE					0xaa

#define LCD_RED   0xF800      //红色
#define LCD_GREEN 0x07e0      //绿色
#define LCD_BLUE  0x001F      //蓝色
#define LCD_LIGHT_BLUE 0x075F  //亮蓝色
#define LCD_DARK 0x0000        //黑色
#define LCD_WHITE 0xFFFF	     //白色
#define LCD_MIDDLE_BLE	0x74F9
#define LCD_DEEP_BLUE	0x10AF   //深蓝色



extern uint8_t  MenuShowBuf[14][20];

void LCD_Standby(void)	;

void LCD_ShowPlay_Card(uint8_t type)  ;

void LCD_ShowKeyValue(void);

void LCD_Show_Consump_Pattern(void);

void LCD_Disp_Function(void);

void LCD_Disp_MenuPassword(void);

void LCD_Disp_Query_Money(void);

void ShowKeyValue_Plus(void);







