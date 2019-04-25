#include "key.h"
#include "delay.h"
#include "rs485.h"	

 u8 keymode;


void KEY_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD,ENABLE);     //使能PORTA,PORTC时钟
	//GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE); //关闭jtag，使能SWD，可以用SWD模式调试
	GPIO_InitStructure.GPIO_Pin  = KEY_ROW;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;            //行 设置成上拉输入（k4-k7）
 	GPIO_Init(GPIOD, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin =KEY_LINE;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 	     //列 推挽输出  (k0-k3)
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
  GPIO_Init(GPIOD, &GPIO_InitStructure);					 //根据设定参数初始化GPIOA.8
  GPIO_SetBits(GPIOD,KEY_LINE);						     //PA.8 输出高
} 
u8 Read_Gpio(void)     //读数据
{       
    u8 DATAS;
    BYTE_T R_BUFF;
    R_BUFF.BITS.B0=GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_8);//读取按键0KEY0;
    R_BUFF.BITS.B1=GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_9);//读取按键1KEY1 ;  
    R_BUFF.BITS.B2=GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_10);//读取按键2KEY2 ; 
    R_BUFF.BITS.B3=GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_11);//读取按键3KEY3 ; 
    R_BUFF.BITS.B4=GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_12);//读取按键4KEY4 ;
    R_BUFF.BITS.B5=GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_13);//读取按键5KEY5 ;
    R_BUFF.BITS.B6=GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_14);//读取按键6KEY6 ;
    R_BUFF.BITS.B7=GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_15);//读取按键7KEY7 ; 
	DATAS=R_BUFF.byte;
    return DATAS; 
}  
void  Write_Gpio(u8 DATAS)     //写数据
{      
  BYTE_T W_BUFF; 
  W_BUFF.byte=DATAS;
  GPIO_WriteBit(GPIOD, GPIO_Pin_8, (BitAction)W_BUFF.BITS.B0);   
  GPIO_WriteBit(GPIOD, GPIO_Pin_9, (BitAction)W_BUFF.BITS.B1);
	GPIO_WriteBit(GPIOD, GPIO_Pin_10,(BitAction)W_BUFF.BITS.B2);
	GPIO_WriteBit(GPIOD, GPIO_Pin_11,(BitAction)W_BUFF.BITS.B3);
	GPIO_WriteBit(GPIOD, GPIO_Pin_12,(BitAction)W_BUFF.BITS.B4);
	GPIO_WriteBit(GPIOD, GPIO_Pin_13,(BitAction)W_BUFF.BITS.B5);
	GPIO_WriteBit(GPIOD, GPIO_Pin_14,(BitAction)W_BUFF.BITS.B6);
	GPIO_WriteBit(GPIOD, GPIO_Pin_15,(BitAction)W_BUFF.BITS.B7);
}

u16 count=0;

u8 long_click()
{
  if(++count>LONG_TIME) 
  {
    count=0;
	return 1;
  }
  else return 0;
}




u8  Keyscan(void)
{   
  static u8 key_now=1;
	static u8 temp;
  static u8 key_state;
  u8 key_val;	
	u8 key_past;
	u8 key_dect;
  u8 key_temp;
 	u8 key_row,key_line;
	
  KEY_LINEOUT_ROWIN();    
	
 	Write_Gpio(0xf0);
 	key_row=Read_Gpio()&(0xf0); 
 	
  KEY_LINEIN_ROWOUT(); 
	
 	Write_Gpio(0x0f);
	
 	key_line=Read_Gpio()&(0x0f); 
	
	key_temp=key_row|key_line; 
	
  key_past=key_now;
	
	if(key_temp!=0xff)         
     {
       key_now=0;

       temp=key_temp;
			 
      }
	else if(key_temp==0xff)            key_now=1; 
	if(key_past&&(!key_now))           key_dect=1;
	else if(!key_past&&key_now)        key_dect=2;

   switch(key_state) 
		{			
  		case 0:	count=0;		
	   		if(key_dect==1)	key_state=1;	
	   		break;
  		case 1:	
			   if(key_dect==2)	     //短按处理
                {
									
						//		RS485_Send_One_Data(temp);//集中发送		
									
               switch(temp)    
	    		      {
									case 0xe7: key_val=1;  break;  // 1
									case 0xd7: key_val=2;  break;  // 2
									case 0xb7: key_val=3;  break;  // 3
									case 0x77: key_val=13; break;  // 设置						

									case 0xeb: key_val=4;  break;  // 4
									case 0xdb: key_val=5;  break;  // 5
									case 0xbb: key_val=6;  break;  // 6
									case 0x7b: key_val=14; break;  // 功能

									case 0xed: key_val=7;  break;  // 7
									case 0xdd: key_val=8;  break;  //  8
									case 0xbd: key_val=9;  break;  // 9
									case 0x7d: key_val=15; break;  // 查询
										
									case 0xee: key_val=11; break;  // *
									case 0xde: key_val=10; break;  // 0
									case 0xbe: key_val=12; break;  // #
									case 0x7e: key_val=16; break;  // 确认
														
									default:   key_val=0; break;
									
		    	      }
               key_state=0;
              }
            if(long_click())       //长按按处理
			        {
                switch(key_temp)       
	    		      {
//				        case 0xee: key_val=33;break;  //  21
//				        case 0xde: key_val=29;break;  //  22
//				        case 0xbe: key_val=25;break;  //  23
//				        case 0x7e: key_val=21;break;  //  24
//					
//				        case 0xed: key_val=34;break;  //  25
//				        case 0xdd: key_val=30;break;  //  26
//				        case 0xbd: key_val=26;break;  //  27
//				        case 0x7d: key_val=22;break;  //  28
//					
//				        case 0xeb: key_val=35;break;  //  29
//				        case 0xdb: key_val=31;break;  //  30
//				        case 0xbb: key_val=27;break;  //  34
//				        case 0x7b: key_val=23;break;  //  32
//					
//				        case 0xe7: key_val=36;break;  //  33
//				        case 0xd7: key_val=32;break;  //  34
//				        case 0xb7: key_val=28;break;  //  35
//				        case 0x77: key_val=24;break;  //  36
//					    default:   key_val=0;break;
									
									
							  case 0xe7: key_val=1;  break;  // 1
				        case 0xd7: key_val=2;  break;  // 2
				        case 0xb7: key_val=3;  break;  // 3
				        case 0x77: key_val=13; break;  // 设置						

					      case 0xeb: key_val=4;  break;  // 4
				        case 0xdb: key_val=5;  break;  // 5
				        case 0xbb: key_val=6;  break;  // 6
				        case 0x7b: key_val=14; break;  // 功能

				        case 0xed: key_val=7;  break;  // 7
				        case 0xdd: key_val=8;  break;  //  8
				        case 0xbd: key_val=9;  break;  // 9
				        case 0x7d: key_val=15; break;  // 查询
									
				        case 0xee: key_val=11; break;  // *
				        case 0xde: key_val=10; break;  // 0
				        case 0xbe: key_val=12; break;  // #
				        case 0x7e: key_val=16; break;  // 确认
								default:   key_val=0; break;	
		    	      }
               key_state=2;
             }
	   		 break; 
  	  case 2: count=0;					
	   	       if(key_dect==2)	
                {
                  key_state=0;
                  temp=0;
                }
	   	      break;    
 	}
	return key_val;
}

