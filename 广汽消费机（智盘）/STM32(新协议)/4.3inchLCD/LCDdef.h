

//#include "43inchgui.h"
//#include "43inchLCD.h"
//#include "FT5308.h"
//#include "gt9xx.h"




#define Low_Speed  0	 //����fsmc�ٶȣ�����Һ��δ����PLL��Ƶ֮ǰ
#define High_Speed  1	 //������fsmc�ٶȣ�����Һ��δ����PLL��Ƶ֮��
#define High_Speed_ReadRam  2	 //������fsmc�ٶȣ�����Һ��δ����PLL��Ƶ֮�󣬵�Ҫ����RAM��ȡ������ĳ������Ҫ�������ã�����Ҫ��RD������10k�������裬CS������100p�Եص���

#define VS32240M35_2  1	 //320*240�ֱ���
#define VS48272M43_2  2	  //480*270�ֱ���
#define VS482720M50_2  3  //480*270�ֱ���
#define VS80480M50HD_2  4 //800*480�ֱ���
#define VS64480M56_2  5		//640*480�ֱ���
#define VS80480M70_2  6		//800*480�ֱ���
#define VS10600M70HD 7		//1024*600�ֱ���
#define VS80600M80  8	    //800*600�ֱ���
#define VS106000M101  9		//1024*600�ֱ���

#define LCD_SPI	  0 //spi�ӿ�
#define LCD_8BIT 1	   //8λ�ӿ�
#define LCD_FSMC   2	   //FSMC�ӿڡ���ע��ֻ��ĳЩstm32оƬ����fsmc�ӿ�

#define Flash_128Mb	  0 //ͼƬ����������
#define Flash_1024Mb	 1	 //ͼƬ����������


#define NC	  0 //����������
#define RTP	  1 //���败����
#define CTP	 2	 //���ݴ�����



#define uchar      unsigned char
#define uint       unsigned int
#define ulong      unsigned long
//#define u8      unsigned char
//#define u16       unsigned int
//#define u32     unsigned long
/*
			 	   #ifdef RA8873

#define	Layer0  0	
#define	Layer1  0x180000//786432					 
#define Layer2  0x380000//1835008		 
#define Layer3  0x580000//2883584		//2883584		
#endif
			 	   #ifdef M43
#define	Layer0  0	
#define	Layer1  786432					 
#define Layer2  1835008		 
#define Layer3  2883584		 
#endif
*/
#define PicAdd  0x220000
#define PicPage 34//PicAdd/65536

#define PageSector 32747//һ��32768��SECTOR�����20����ҳ��

#define BufferNumber 15

#define SPI_CS0()	GPIOE->BRR = GPIO_Pin_12
#define SPI_CS1()	GPIOE->BSRR = GPIO_Pin_12
#define SPI0_FLASH_CS1_LOW()    GPIOA->BRR = GPIO_Pin_4
#define SPI0_FLASH_CS1_HIGH()    GPIOA->BSRR = GPIO_Pin_4



#define BUSY1    GPIOB->BRR = GPIO_Pin_8
#define BUSY0     GPIOB->BSRR = GPIO_Pin_8




#define LcdType_43
 #define SKIP_DIF 30
#define SAMPLES 10
#define CALSIZE  20//����У׼�������Ļ�ߵľ������ص�
#define busysize 10
#define flashtime 20
#define bdradd 0x0800f400
#define picadd 0x0800f800

#define  TOUCH_NC    0
#define  TOUCH_DOWN	 1
#define  TOUCH_UP    2
#define Menu_Num  8
