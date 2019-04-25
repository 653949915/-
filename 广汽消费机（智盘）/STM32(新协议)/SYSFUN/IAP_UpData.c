#include "Head.h"

#include "stdlib.h"	 
//#include "IAP_UpData.h"


uint8_t __attribute__ ((aligned (4))) Receiapbuf[IAP_SIZE];	 //���ڻ������ݵ�����
uint16_t iapcnt = 0;	    							                 //��ǰiapbuffer���Ѿ��������ݳ���,һ���������֮��д��flash������
uint32_t iapaddr = FLASH_APP2_ADDR;						         //��ǰϵͳд���ַ,ÿ��д��֮���ַ����1024

uint16_t iappackcnt = 0;	                             //�����̼����İ���

uint16_t iapreceivepackcnt = 0;	                       //�����̼���ʵ�ʽ��յ�����

uint32_t iapallcnt = 0;	                              //�����̼����ֽ�





////////////////////////////////α����������취////////////////////////////////
u32 random_seed=1;
void app_srand(u32 seed)
{
	random_seed=seed;
}
//��ȡα�����
//���Բ���0~RANDOM_MAX-1�������
//seed:����
//max:���ֵ	  		  
//����ֵ:0~(max-1)�е�һ��ֵ 	
/*
��ʽ��   X(n+1) = (a * X(n) + c) % m

ģm, m > 0
ϵ��a, 0 < a < m
����c, 0 <= c < m
ԭʼֵ(����) 0 <= X(0) < m
*/

u32 app_get_rand(u32 max)
{			    	    
	random_seed=random_seed*22695477+1;
	return (random_seed)%max; 
}  




//����α�����
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
//дFlash
******************************************************************************/
uint32_t write_flash(void)
{
//	uint8_t *ptr;
//	uint8_t status;
	
	iap_write_appbin(iapaddr,Receiapbuf,IAP_SIZE);  //�����յ��Ĵ���д��FLASH 
	iapcnt = 0;
	iapaddr += IAP_SIZE;
	
	return 1;
}







//�̼���ʼ����ǰ�ļ��
//����ֵ���̼����ݸ�����4�ֽڣ� + ���͹̼���������2�ֽڣ�


uint8_t  Check_IAP_Start_Updata(uint8_t *data ,uint16_t len)
{
	
	union  TwoByte   ic2={0};       //�̼����ݰ�����
  union  FourByte  ic4={0};       //�̼����ֽ���
  
	
  MyStrCPY(ic4.c, data , 4);
  
  MyStrCPY(ic2.c, data +4 , 2);

  if(ic4.i > FLASH_APP_SIZE)    //�̼���С���ܴ���Ԥ����Ĺ̼���С
	{
		return 0;
	}

	iapallcnt  = ic4.i;
	
	iappackcnt = ic2.i;         //
	
	iapaddr = FLASH_APP2_ADDR;	//�洢λ�ó�ʼ��
	
	iapreceivepackcnt = 0;
	
	iapcnt = 0;		
	
  return 1;
}


//�̼����ݼ��
//����ֵ���̼������ݣ�512�ֽڣ� + crcУ�飨2�ֽڣ�

uint8_t  Handle_IAP_Data(uint8_t *data ,uint16_t len)
{
	
	CalculateCRC(data, len - 2);
	
	if ((data[len-2] == crchigh) && (data[len-1] == crclow))
	{	
		MyStrCPY(Receiapbuf+iapcnt, data, len-2);
		
		iapcnt += (len - 2); 
		
		 iapreceivepackcnt ++ ;     //ʵ�ʽ��յİ�����+1
		
		if (iapcnt == IAP_SIZE)
		{
       	iap_write_appbin(iapaddr,Receiapbuf,IAP_SIZE);  //�����յ��Ĵ���д��FLASH 
	      iapcnt = 0;
	      iapaddr += IAP_SIZE;  
			
		}
		
   else if((len-2)<  512)
		 {		 
			  iap_write_appbin(iapaddr,Receiapbuf,iapcnt);  //�����յ��Ĵ���д��FLASH 

	      iapaddr += (iapcnt);		

			 	iapcnt = 0;			 
		 }
		return 1;
	}
	
	return 0;
}



//�̼��������
//
uint8_t  Check_IAP_END_Updata(void)
{
//	  union  FourByte  ic4={0};       //�̼����ֽ���
		
		uint32_t   iapaddr_size =0;
		
		iapaddr_size = iapaddr- FLASH_APP2_ADDR;
				
	 if ( iapallcnt!= iapaddr_size)	    //���յ��Ĺ̼���������ʵ�Ĺ̼������Ա� 
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


//��ȡ�̼�����
//
void  IAP_Read_Data(void)
{


}



//�̼�������ϣ�ϵͳ��������
//
void  IAP_OK_System_Boot(void)
{
	
	 union    TwoByte  ic2 = {0};
	
	 uint8_t  databuf[4]={0x55 ,0x55};
	
	 iap_write_appbin(FLASH_DATA_ADDR,databuf,2);      //д��̼����±�־
	
	 ic2.i = iapreceivepackcnt ;
	 
	 iap_write_appbin(FLASH_DATA_ADDR+8,ic2.c,2);      //д��ʵ�ʽ��յ��İ�����	 
	 
	 ic2.i = iappackcnt ;
	 
	 iap_write_appbin(FLASH_DATA_ADDR+16,ic2.c,2);      //д����λ������İ����� 	 
	 
}


//����̼����±�־
//
void  Clear_IAP_OK_System_Boot(void)
{
	
	 uint8_t  databuf[6]={0x00};
	 
	 uint8_t  databuf_def[6]={0x01, 0X02, 0X03, 0X04, 0X05, 0X06};	 
	 
	
	 iap_write_appbin(FLASH_DATA_ADDR,databuf,2);      //д��̼����±�־
	
	 STMFLASH_Read(FLASH_DATA_ADDR  , (u16*)(databuf) , 1);      //   ��STM32�ڲ�Flash�ж�ȡ ���±�־
	 
//	 STMFLASH_Read(FLASH_DATA_ADDR +8 , (u16*)(databuf+2) , 1);      //   ��STM32�ڲ�Flash�ж�ȡ ʵ�ʽ��յ��İ�����

//	 STMFLASH_Read(FLASH_DATA_ADDR +16 , (u16*)(databuf+4) , 1);      //   ��STM32�ڲ�Flash�ж�ȡ ��λ������İ����� 
	 
  if((databuf[0]==0x55)&&(databuf[1]==0x55))     //�и��¹̼���־
		{
					
			iap_write_appbin(FLASH_DATA_ADDR,databuf_def,2);      //д��̼����±�־
			
	    iap_write_appbin(FLASH_DATA_ADDR+8,databuf_def+2,2);      //д��ʵ�ʽ��յ��İ�����	
			
	    iap_write_appbin(FLASH_DATA_ADDR+16,databuf_def+4,2);      //д����λ������İ�����  			
			
//      if(MyStrEQ(databuf+2, databuf+4, 2))  //����ֵ���
//			{
//			  if((databuf[2]==0xFF)&&(databuf[3]==0xFF)) 
//			  {
//				  
//				
//				}
//			}				
		}
 
}






//�����λ��ʽ��
void SoftReset(void)
{
  __set_FAULTMASK(1);      // �ر������ж�
	
  NVIC_SystemReset();// ��λ
}











