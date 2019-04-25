#ifndef __RC522_CONFIG_H
#define	__RC522_CONFIG_H


//CS(SDA)---PC5;
//SCK---PA5;
//MOSI---PA7;
//MISO---PA6;
//RST--PC4;

/*********************************** RC522 引脚定义 *********************************************/
#define               macRC522_GPIO_CS_CLK_FUN                  RCC_APB2PeriphClockCmd
#define               macRC522_GPIO_CS_CLK                      RCC_APB2Periph_GPIOC
#define               macRC522_GPIO_CS_PORT    	                GPIOC			   
#define               macRC522_GPIO_CS_PIN		                  GPIO_Pin_12
#define               macRC522_GPIO_CS_Mode		                  GPIO_Mode_Out_PP

#define               macRC522_GPIO_SCK_CLK_FUN                 RCC_APB2PeriphClockCmd
#define               macRC522_GPIO_SCK_CLK                     RCC_APB2Periph_GPIOB
#define               macRC522_GPIO_SCK_PORT    	              GPIOB			   
#define               macRC522_GPIO_SCK_PIN		                  GPIO_Pin_5
#define               macRC522_GPIO_SCK_Mode		                GPIO_Mode_Out_PP

#define               macRC522_GPIO_MOSI_CLK_FUN                RCC_APB2PeriphClockCmd
#define               macRC522_GPIO_MOSI_CLK                    RCC_APB2Periph_GPIOD
#define               macRC522_GPIO_MOSI_PORT    	              GPIOD			   
#define               macRC522_GPIO_MOSI_PIN		                GPIO_Pin_2
#define               macRC522_GPIO_MOSI_Mode		                GPIO_Mode_Out_PP

#define               macRC522_GPIO_MISO_CLK_FUN                RCC_APB2PeriphClockCmd
#define               macRC522_GPIO_MISO_CLK                    RCC_APB2Periph_GPIOB
#define               macRC522_GPIO_MISO_PORT    	              GPIOB			   
#define               macRC522_GPIO_MISO_PIN		                GPIO_Pin_4
#define               macRC522_GPIO_MISO_Mode		                GPIO_Mode_IN_FLOATING

#define               macRC522_GPIO_RST_CLK_FUN                 RCC_APB2PeriphClockCmd
#define               macRC522_GPIO_RST_CLK                     RCC_APB2Periph_GPIOB
#define               macRC522_GPIO_RST_PORT    	              GPIOB		   
#define               macRC522_GPIO_RST_PIN		                  GPIO_Pin_3
#define               macRC522_GPIO_RST_Mode		                GPIO_Mode_Out_PP



/*********************************** RC522 函数宏定义*********************************************/
#define          macRC522_CS_Enable()         GPIO_ResetBits ( macRC522_GPIO_CS_PORT, macRC522_GPIO_CS_PIN )
#define          macRC522_CS_Disable()        GPIO_SetBits ( macRC522_GPIO_CS_PORT, macRC522_GPIO_CS_PIN )

#define          macRC522_Reset_Enable()      GPIO_ResetBits( macRC522_GPIO_RST_PORT, macRC522_GPIO_RST_PIN )
#define          macRC522_Reset_Disable()     GPIO_SetBits ( macRC522_GPIO_RST_PORT, macRC522_GPIO_RST_PIN )

#define          macRC522_SCK_0()             GPIO_ResetBits( macRC522_GPIO_SCK_PORT, macRC522_GPIO_SCK_PIN )
#define          macRC522_SCK_1()             GPIO_SetBits ( macRC522_GPIO_SCK_PORT, macRC522_GPIO_SCK_PIN )

#define          macRC522_MOSI_0()            GPIO_ResetBits( macRC522_GPIO_MOSI_PORT, macRC522_GPIO_MOSI_PIN )
#define          macRC522_MOSI_1()            GPIO_SetBits ( macRC522_GPIO_MOSI_PORT, macRC522_GPIO_MOSI_PIN )

#define          macRC522_MISO_GET()          GPIO_ReadInputDataBit ( macRC522_GPIO_MISO_PORT, macRC522_GPIO_MISO_PIN )



/*********************************** 函数 *********************************************/


static void  RC522_SPI_Config( void );
void             RC522_Init                   ( void );

void             IC_test                      ( void );

// extern  unsigned char cardbuff [  ]; 


 //  u8 ucArray_ID [ 4 ];  //先后存放IC卡的类型和UID(IC卡序列号)
#endif /* __RC522_CONFIG_H */

