#include "rc522_config.h"
#include "rc522_function.h"
#include "stm32f10x.h"
#include "usart.h"
#include "head.h"
// unsigned char cardbuff [ 8 ]; //��Ű�λ�ַ�����ʽ�Ŀ���

void RC522_Init ( void )
{
	RC522_SPI_Config ();
	
	macRC522_Reset_Disable();
	
	macRC522_CS_Disable();
	delay_ms(10);
 	PcdReset ();             //��λRC522 
	M500PcdConfigISOType ( 'A' );//���ù�����ʽ	
	
}


 void RC522_SPI_Config ( void )
{
  /* SPI_InitTypeDef  SPI_InitStructure */
  GPIO_InitTypeDef GPIO_InitStructure;
	/*!< Configure SPI_RC522_SPI pins: CS */
	macRC522_GPIO_CS_CLK_FUN ( macRC522_GPIO_CS_CLK, ENABLE );
  GPIO_InitStructure.GPIO_Pin = macRC522_GPIO_CS_PIN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = macRC522_GPIO_CS_Mode;
  GPIO_Init(macRC522_GPIO_CS_PORT, &GPIO_InitStructure);
	
  /*!< Configure SPI_RC522_SPI pins: SCK */
	macRC522_GPIO_SCK_CLK_FUN ( macRC522_GPIO_SCK_CLK, ENABLE );
  GPIO_InitStructure.GPIO_Pin = macRC522_GPIO_SCK_PIN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = macRC522_GPIO_SCK_Mode;
  GPIO_Init(macRC522_GPIO_SCK_PORT, &GPIO_InitStructure);
	
  /*!< Configure SPI_RC522_SPI pins: MOSI */
	macRC522_GPIO_MOSI_CLK_FUN ( macRC522_GPIO_MOSI_CLK, ENABLE );
  GPIO_InitStructure.GPIO_Pin = macRC522_GPIO_MOSI_PIN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = macRC522_GPIO_MOSI_Mode;
  GPIO_Init(macRC522_GPIO_MOSI_PORT, &GPIO_InitStructure);

  /*!< Configure SPI_RC522_SPI pins: MISO */
	macRC522_GPIO_MISO_CLK_FUN ( macRC522_GPIO_MISO_CLK, ENABLE );
  GPIO_InitStructure.GPIO_Pin = macRC522_GPIO_MISO_PIN;
  GPIO_InitStructure.GPIO_Mode = macRC522_GPIO_MISO_Mode;
  GPIO_Init(macRC522_GPIO_MISO_PORT, &GPIO_InitStructure);	
	
	
  /*!< Configure SPI_RC522_SPI pins: RST */
	macRC522_GPIO_RST_CLK_FUN ( macRC522_GPIO_RST_CLK, ENABLE );
  GPIO_InitStructure.GPIO_Pin = macRC522_GPIO_RST_PIN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = macRC522_GPIO_RST_Mode;
  GPIO_Init(macRC522_GPIO_RST_PORT, &GPIO_InitStructure);
	
}



void IC_test ( void )
{
	
//	char cStr [ 30 ];
  u8 ucArray_ID [ 4 ];  //�Ⱥ���IC�������ͺ�UID(IC�����к�)
	u8 ucStatusReturn;  //����״̬
//  static u8 ucLineCount = 0; 
	
		int t;
		if ( ( ucStatusReturn = PcdRequest ( PICC_REQALL, ucArray_ID ) ) != MI_OK )  //Ѱ��
			ucStatusReturn = PcdRequest ( PICC_REQALL, ucArray_ID );	//��ʧ���ٴ�Ѱ��
     //  printf ( "The Card ID is: %02X", ucArray_ID [ 0 ]);
		if ( ucStatusReturn == MI_OK  )
		{
		//	printf ( "The Card ID is: %02X", ucArray_ID [ 0 ]);
			
			
			if ( PcdAnticoll ( ucArray_ID ) == MI_OK )  //����ײ�����ж��ſ������д��������Χʱ������ͻ���ƻ������ѡ��һ�Ž��в�����
			{
	//			HexToStr(cardbuff,ucArray_ID, 4);//����λ���к�ת��Ϊ8λ�ַ�����ʽ
				
				
				//				USART_SendData(USART1,ucArray_ID[t]);//�򴮿�1��������
//				while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//�ȴ����ͽ���		

				showStandby=0;          //�رմ�����ʾ

				
			for(t=0;t<4;t++)
			{
          
			idbuff[t]	=ucArray_ID[t];
				
			}
				
			
			
				FindCardno();
			
					if (bfindcard)
		{
			
			
		//	return;
		}
			
			
			
			//	printf ( "The Card ID is: %02X%02X%02X%02X", ucArray_ID [ 0 ], ucArray_ID [ 1 ], ucArray_ID [ 2 ], ucArray_ID [ 3 ] );
			
				 
			}
			
		}
		
  }

