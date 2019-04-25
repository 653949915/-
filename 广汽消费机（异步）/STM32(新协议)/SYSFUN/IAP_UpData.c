#include "Head.h"

#include "stdlib.h"	 
//#include "IAP_UpData.h"


uint8_t __attribute__ ((aligned (4))) Receiapbuf[IAP_SIZE];	 //用于缓存数据的数组
uint16_t iapcnt = 0;	    							                 //当前iapbuffer中已经填充的数据长度,一次填充满了之后写入flash并清零
uint32_t iapaddr = FLASH_APP2_ADDR;						         //当前系统写入地址,每次写入之后地址增加1024

uint16_t iappackcnt = 0;	                             //升级固件包的包数

uint16_t iapreceivepackcnt = 0;	                       //升级固件包实际接收的数量

uint32_t iapallcnt = 0;	                              //升级固件总字节





////////////////////////////////伪随机数产生办法////////////////////////////////
u32 random_seed=1;
void app_srand(u32 seed)
{
	random_seed=seed;
}
//获取伪随机数
//可以产生0~RANDOM_MAX-1的随机数
//seed:种子
//max:最大值	  		  
//返回值:0~(max-1)中的一个值 	
/*
公式：   X(n+1) = (a * X(n) + c) % m

模m, m > 0
系数a, 0 < a < m
增量c, 0 <= c < m
原始值(种子) 0 <= X(0) < m
*/

u32 app_get_rand(u32 max)
{			    	    
	random_seed=random_seed*22695477+1;
	return (random_seed)%max; 
}  




//产生伪随机数
u32 False_Random_number(void)
{
	u32 seed;
	
	union  EightByte  i8 ={0};
	
	seed=time_buf[6];

	app_srand(seed);
	
	i8.i = app_get_rand(90000);

	return i8.i;
	
//  RS485_Send_Data(i8.c, 8);
}






/******************************************************************************
//写Flash
******************************************************************************/
uint32_t write_flash(void)
{
//	uint8_t *ptr;
//	uint8_t status;
	
	iap_write_appbin(iapaddr,Receiapbuf,IAP_SIZE);  //将接收到的代码写入FLASH 
	iapcnt = 0;
	iapaddr += IAP_SIZE;
	
	return 1;
}







//固件开始更新前的检查
//传入值：固件数据个数（4字节） + 发送固件包包数（2字节）


uint8_t  Check_IAP_Start_Updata(uint8_t *data ,uint16_t len)
{
	
	union  TwoByte   ic2={0};       //固件数据包个数
  union  FourByte  ic4={0};       //固件包字节数
  
	
  MyStrCPY(ic4.c, data , 4);
  
  MyStrCPY(ic2.c, data +4 , 2);

  if(ic4.i > FLASH_APP_SIZE)    //固件大小不能大于预定义的固件大小
	{
		return 0;
	}

	iapallcnt  = ic4.i;
	
	iappackcnt = ic2.i;         //
	
	iapaddr = FLASH_APP2_ADDR;	//存储位置初始化
	
	iapreceivepackcnt = 0;
	
	iapcnt = 0;		
	
  return 1;
}


//固件内容检测
//传入值：固件包内容（512字节） + crc校验（2字节）

uint8_t  Handle_IAP_Data(uint8_t *data ,uint16_t len)
{
	
	CalculateCRC(data, len - 2);
	
	if ((data[len-2] == crchigh) && (data[len-1] == crclow))
	{	
		MyStrCPY(Receiapbuf+iapcnt, data, len-2);
		
		iapcnt += (len - 2); 
		
		 iapreceivepackcnt ++ ;     //实际接收的包数量+1
		
		if (iapcnt == IAP_SIZE)
		{
       	iap_write_appbin(iapaddr,Receiapbuf,IAP_SIZE);  //将接收到的代码写入FLASH 
	      iapcnt = 0;
	      iapaddr += IAP_SIZE;  
			
		}
		
   else if((len-2)<  512)
		 {		 
			  iap_write_appbin(iapaddr,Receiapbuf,iapcnt);  //将接收到的代码写入FLASH 

	      iapaddr += (iapcnt);		

			 	iapcnt = 0;			 
		 }
		return 1;
	}
	
	return 0;
}



//固件结束检测
//
uint8_t  Check_IAP_END_Updata(void)
{
//	  union  FourByte  ic4={0};       //固件包字节数
		
		uint32_t   iapaddr_size =0;
		
		iapaddr_size = iapaddr- FLASH_APP2_ADDR;
				
	 if ( iapallcnt!= iapaddr_size)	    //接收到的固件数量和真实的固件数量对比 
			{				
//				ic4.i =	iapallcnt;
//				
//				RS485_Send_Data(ic4.c, 4);
//				
//				ic4.i =	iapaddr_size;
//				
//				RS485_Send_Data(ic4.c, 4);				
				
				return 0;
			}
		
	return 1;
	
}


//读取固件内容
//
void  IAP_Read_Data(void)
{


}



//固件发送完毕，系统重启更新
//
void  IAP_OK_System_Boot(void)
{
	
	 union    TwoByte  ic2 = {0};
	
	 uint8_t  databuf[4]={0x55 ,0x55};
	
	 iap_write_appbin(FLASH_DATA_ADDR,databuf,2);      //写入固件更新标志
	
	 ic2.i = iapreceivepackcnt ;
	 
	 iap_write_appbin(FLASH_DATA_ADDR+8,ic2.c,2);      //写入实际接收到的包数量	 
	 
	 ic2.i = iappackcnt ;
	 
	 iap_write_appbin(FLASH_DATA_ADDR+16,ic2.c,2);      //写入上位机计算的包数量 	 
	 
}


//清除固件更新标志
//
void  Clear_IAP_OK_System_Boot(void)
{
	
	 uint8_t  databuf[6]={0x00};
	 
	 uint8_t  databuf_def[6]={0x01, 0X02, 0X03, 0X04, 0X05, 0X06};	 
	 
	
	 iap_write_appbin(FLASH_DATA_ADDR,databuf,2);      //写入固件更新标志
	
	 STMFLASH_Read(FLASH_DATA_ADDR  , (u16*)(databuf) , 1);      //   从STM32内部Flash中读取 更新标志
	 
//	 STMFLASH_Read(FLASH_DATA_ADDR +8 , (u16*)(databuf+2) , 1);      //   从STM32内部Flash中读取 实际接收到的包数量

//	 STMFLASH_Read(FLASH_DATA_ADDR +16 , (u16*)(databuf+4) , 1);      //   从STM32内部Flash中读取 上位机计算的包数量 
	 
  if((databuf[0]==0x55)&&(databuf[1]==0x55))     //有更新固件标志
		{
					
			iap_write_appbin(FLASH_DATA_ADDR,databuf_def,2);      //写入固件更新标志
			
	    iap_write_appbin(FLASH_DATA_ADDR+8,databuf_def+2,2);      //写入实际接收到的包数量	
			
	    iap_write_appbin(FLASH_DATA_ADDR+16,databuf_def+4,2);      //写入上位机计算的包数量  			
			
//      if(MyStrEQ(databuf+2, databuf+4, 2))  //两个值相等
//			{
//			  if((databuf[2]==0xFF)&&(databuf[3]==0xFF)) 
//			  {
//				  
//				
//				}
//			}				
		}
 
}






//软件复位方式；
void SoftReset(void)
{
  __set_FAULTMASK(1);      // 关闭所有中端
	
  NVIC_SystemReset();// 复位
}











