#ifndef	__SYSCOMM_H__
#define	__SYSCOMM_H__
#include "sys.h"	
/**********************************************************
//外部变量声明
**********************************************************/
#define KEY_SIZE 20            //按键接收长度
#define OpenSPK()		BEEP = 0    //打开蜂鸣器
#define CloseSPK()		BEEP = 1  //关闭蜂鸣器

#define	LONG_BEEP			500 //发长声
#define	SHORT_BEEP			100 //发短声
#define	SHORT_BEEP_UART			50 //发短声


#define ERR_BEEP()			    Beep(3, LONG_BEEP)   //错误声音
#define SUCCESS()		        Beep(2, SHORT_BEEP)  //成功声音
#define UARTSUCCESS()		    Beep(1, SHORT_BEEP_UART)  //成功声音




/**********************************************************
//外部函数声明
**********************************************************/

u32 MyStrEQ(u8 *a, u8 *b, u16 ilen);
void MyStrCPY(uint8_t *d, uint8_t *r, u16 ilen);
u8  GetXOR(uint8_t *ptr, uint32_t len);
u8 MyStrCMP(u8 *a, u8 *b, u8 len);
void Beep(u8 count, u32 idelay);
void LED1_fun(u8 count, u32 idelay);
void LED2_fun(u8 count, u32 idelay);

u8 GetSum(u8 *b, u8 icount);
void HexToStr(unsigned char *pbDest,  unsigned char *pbSrc,  unsigned char nLen);
	
void StrToHex(u8 *pbDest, u8 *pbSrc, int nLen);

unsigned long	BCDtoDec(const unsigned char *bcd, int length);
int DectoHex(int dec, unsigned char *hex, int length);
unsigned long HextoDec(const unsigned char *hex, int length);

u8 HextoBCD( u8 temp );

uint32_t getBCDtoDec(u8 *bcd, u8 length);
void getDectoBCD(u32 Dec, u8 *Bcd, u8 length);

void turn_4_data(u8*a,u8*b);
void turn_2_data(u8*a,u8*b);
	
extern u8 GetASCIIValue(u8 *inValue,int nLen);
void GetBCDValue1(u8 *outValue, u8 *inValue,int nLen);
void StrTodec(u8 *pbDest, u8 *pbSrc, int nLen);

void InitSysvar(void);
void SaveExtvar(u8 * var) ; 
void SaveSysvar(u8 * var);


unsigned long separate_value_2_1(u8*b);
void separate_value_1_4(u32 a,u8*b);

void  GAEI_IC_Conversion(uint8_t *inIC ,uint8_t *OutIC);
#endif











