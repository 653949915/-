#include "Head.h"

#include "speak.h"




void TX_L(void)
{
    GPIO_ResetBits(GPIOD, GPIO_Pin_14);
}

void TX_H(void)
{
    GPIO_SetBits(GPIOD, GPIO_Pin_14);
}


/*!
 * @brief 	模拟串口1 TX IO口配置
 * @param	none
 * @return	none
 * @note	Tx(PA10)
 */
void SPEAK_USART_TX_init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);	             //使能PB端口时钟	
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_14;		 
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOD, &GPIO_InitStructure); 
    GPIO_SetBits(GPIOD, GPIO_Pin_14);
}



uint32_t delayTime =104;	//!<9600，理论值为104但实际测下来99时效果最好
/*!
 * @brief 	模拟串口1发送一个字节
 * @param	
 * @return	none
 * @note	数据低位在前高位在后
 */
void MUSART1_SendData(uint8_t data)
{
	uint8_t i = 0;
	TX_L();		//!<起始位
	delay_us(delayTime);
	for(i = 0; i < 8; i++){
		if(data & 0x01)
			TX_H();
		else
			TX_L();
		delay_us(delayTime);
		data >>= 1;
	}
	TX_H();		//!<停止位
	delay_us(delayTime);
}

/*!
 * @brief 	模拟串口1发送字符串
 * @param	
 * @return	none
 * @note	数据低位在前高位在后
 */
void SPEAKUART_SendString(uint8_t *speakcombuff ,uint16_t len)
{
	uint16_t t;
	for(t=0;t<len;t++)
	 {
		  MUSART1_SendData(speakcombuff[t]);//向串口1发送数据
	
	
   }
}



/*!
 * @brief 	向SYN6288发送数据
 * @param	  function  需要执行的功能
            Cmdparam  命令参数
            data      需要发送的数据 
            len       数据长度

 * @return	none
 * @note	
 */
void  SYN6288_Send(uint8_t function ,uint8_t Cmdparam , uint8_t *data ,uint8_t len)
{
  uint8_t  syn6288databuf[200]={0xFD};


    syn6288databuf[1] = 0x00;
    syn6288databuf[2] = len + 3;
    syn6288databuf[3] = function;
    syn6288databuf[4] = Cmdparam;	
	  memcpy(syn6288databuf + 5, data, len );	
    syn6288databuf[len+5] = GetXOR(syn6288databuf, len+6);	

    SPEAKUART_SendString(syn6288databuf ,len+6);
}



void SC50X0_SDA(unsigned char data)
{    
    unsigned char i;
	
	   delay_ms(200);
	
     SPEAK_SDA = 0;

     delay_ms(5);    

     for(i=0;i < 8;i++)

     {  
        SPEAK_SDA = 1; 

        if(data & 0x01)

        {
           delay_us(1200);  

           SPEAK_SDA = 0;

           delay_us(400);  
        }
        else

        { 
           delay_us(400);  

           SPEAK_SDA = 0;

           delay_us(1200);  
        } 

        data >>= 1;
     } 
      SPEAK_SDA = 1;  

      delay_us(100); 
} 











