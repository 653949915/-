//******************************************************************************
//*File name:           bsp_SST25VF016.c                                       *
//*Descriptions:        SPI下的SST25VF016B操作函数库                           *
//*Created date:        2011-03-29                                             *
//*Modified date:       2011-03-29                                             *
//*Version:             1.0                                                    *
//*note:                SST25VFXX 写操作必须先使能写状态，同时被写的数据位置需要
//*                     在擦除状态，而擦除是4K,32K,64K方式擦除，所以写数据需将要
//*                     该地址所在的4K数据读出，存放到一个数组，修改数组对应的数
//*                     据，然后擦除存储器内的该4K数据，将数组重新写入存储器       
//******************************************************************************
#include "bsp_SST25VF016.h"


// u8 SST25V_ByteRead(u32 ReadAddr);
// void SST25V_BufferRead(u8* pBuffer, u32 ReadAddr, u16 NumByteToRead);

u8 SST25V_HighSpeedRead(u32 ReadAddr);
void SST25V_HighSpeedBufferRead(u8* pBuffer, u32 ReadAddr, u16 NumByteToRead);

u8 SPI_Flash_SendByte(u8 byte);
u8 SPI_Flash_ReceiveByte(void);
void SST25V_ByteWrite(u8 Byte, u32 WriteAddr);
void AutoAddressIncrement_WordProgramA(u8 Byte1, u8 Byte2, u32 Addr);
void AutoAddressIncrement_WordProgramB(u8 state,u8 Byte1, u8 Byte2) ;

void SST25V_Wait_Busy_AAI(void);
void SST25V_SectorErase_4KByte(u32 Addr);
void SST25V_BlockErase_32KByte(u32 Addr);
void SST25V_BlockErase_64KByte(u32 Addr);
void SST25V_ChipErase(void);

u8 SST25V_ReadStatusRegister(void);
void SST25V_WriteEnable(void);
void SST25V_WriteDisable(void);

void SST25V_EnableWriteStatusRegister(void);
void SST25V_WriteStatusRegister(u8 Byte);
void SST25V_WaitForWriteEnd(void);

u32 SST25V_ReadJedecID(void);

u16 SST25V_ReadManuID_DeviceID(u32 ReadManu_DeviceID_Addr);

void SST25V_EBSY(void);
void SST25V_DBSY(void);

/******************************************************************************
** 函数名称: SST25V_Init(void)						
** 函数功能: SST25 初始化
** 入口参数: 无		
** 出口参数: 无		
** 备    注: 无 
*******************************************************************************/
void SST25V_Init(void)
{
    SPI_FLASH_Init();
    SST25_CS_HIGH();
    SST25V_EnableWriteStatusRegister();
    SST25V_WriteStatusRegister(0x02);
    SST25V_DBSY();
}
/******************************************************************************
** 函数名称: SPI_FLASH_Init(void)						
** 函数功能: 初始化SPI端口			
** 入口参数: 无		
** 出口参数: 无		
** 备    注: 无 
*******************************************************************************/
void SPI_FLASH_Init(void)
{
    /*****端口配置*****/
  SPI_InitTypeDef  SPI_InitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;
  
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
  // SCLK  MISO  MOSI
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;  
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;          //CS
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  SPI_FLASH_CS_HIGH();
	
    /**********SPI配置******************/
	
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
  SPI_InitStructure.SPI_Mode = SPI_Mode_Master;                      //主机模式
  SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;                  //8位数据
  SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;                        //模式3
  SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
  SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;                          //软件控制CS
  SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2; //时钟分频 
  SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;                 //高位在前
  SPI_InitStructure.SPI_CRCPolynomial = 7;                           //CRC校验
  SPI_Init(SPI1, &SPI_InitStructure);                                //配置
  SPI_Cmd(SPI1, ENABLE);                                             //使能SPI1
	
	
}

/******************************************************************************
** 函数名称: SPI_FLASH_SendByte(u8 byte)					
** 函数功能: 发送1个字节数据，返回接收到的数据		
** 入口参数: byte	
** 出口参数: byte	
** 备    注: 无 
*******************************************************************************/
static u8 SPI_FLASH_SendByte(u8 byte)
{
    while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
    SPI_I2S_SendData(SPI1, byte);
    while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);
    return SPI_I2S_ReceiveData(SPI1);
}
/******************************************************************************
** 函数名称: SPI_FLASH_ReadByte(void)					
** 函数功能: 接收SPI数据	
** 入口参数: 无		
** 出口参数: byte 返回接收的数据
** 备    注: 无 
*******************************************************************************/
static u8 SPI_FLASH_ReadByte(void)
{
  return (SPI_FLASH_SendByte(SST25_Dummy_Byte));
}
/************************************************************************
** 函数名称: SST25V_ReadStatusRegister(void)	
** 函数功能: SST25VF016B 读取状态寄存器
** 入口参数: 无
** 出口参数: 状态寄存器数据
** 注	 意: 
************************************************************************/
u8 SST25V_ReadStatusRegister(void)
{
  u8 StatusRegister = 0;
  SST25_CS_LOW();
  SPI_FLASH_SendByte(SST25_ReadStatusReg);
  StatusRegister = SPI_FLASH_ReadByte();
  SST25_CS_HIGH();
  return StatusRegister;
}
/************************************************************************
** 函数名称: SST25V_WriteEnable(void)
** 函数功能: SST25VF016B 写使能
** 入口参数: 无
** 出口参数: 无
** 注	 意: 
************************************************************************/
void SST25V_WriteEnable(void)
{
  SST25_CS_LOW();
  SPI_FLASH_SendByte(SST25_WriteEnable);
  SST25_CS_HIGH();
}
/************************************************************************
** 函数名称: SST25V_WriteDisable(void)
** 函数功能: SST25VF016B 禁止写使能
** 入口参数: 无
** 出口参数: 无
** 注	 意: 
************************************************************************/
void SST25V_WriteDisable(void)
{
  SST25_CS_LOW();
  SPI_FLASH_SendByte(SST25_WriteDisable);
  SST25_CS_HIGH();
}
/************************************************************************
** 函数名称: SST25V_EnableWriteStatusRegister(void)
** 函数功能: SST25VF016B 使能写状态寄存器
** 入口参数: 无
** 出口参数: 无
** 注	 意: 
************************************************************************/
void SST25V_EnableWriteStatusRegister(void)
{
  SST25_CS_LOW();
  SPI_FLASH_SendByte(SST25_EnableWriteStatusReg);
  SST25_CS_HIGH();
}
/************************************************************************
** 函数名称: SST25V_WriteStatusRegister(u8 Byte)
** 函数功能: SST25VF016B 写状态寄存器指令
** 入口参数: u8 Byte :指令
** 出口参数: 无
** 注	 意: 
************************************************************************/
void SST25V_WriteStatusRegister(u8 Byte)
{
  SST25V_EnableWriteStatusRegister();
  SST25_CS_LOW();
  SPI_FLASH_SendByte(SST25_WriteStatusReg);
  SPI_FLASH_SendByte(Byte);
  SST25_CS_HIGH();
}
/************************************************************************
** 函数名称: SST25V_WaitForWriteEnd(void)
** 函数功能: SST25VF016B 等待数据写完
** 入口参数: 无
** 出口参数: 无
** 注	 意: 
************************************************************************/
void SST25V_WaitForWriteEnd(void)
{
  u8 FLASH_Status = 0;
  SST25_CS_LOW();
  SPI_FLASH_SendByte(SST25_ReadStatusReg);
  do
  {
    FLASH_Status = SPI_FLASH_SendByte(SST25_Dummy_Byte);

  } while((FLASH_Status & SST25_WriteStatusReg) == SET);

  SST25_CS_HIGH();
}
/************************************************************************
** 函数名称: SST25V_ByteRead		
** 函数功能: SST25VF016B的读取1个字节数据(低速)			
** 入口参数:
**			 u32 ReadAddr：目标地址,
             范围 0x0 - SST25_MAX_ADDR（SST25_MAX_ADDR = 0x1FFFFF）		
** 出口参数: 返回读取的数据	
** 备    注: 
************************************************************************/
u8 SST25V_ByteRead(u32 ReadAddr)
{
  u8 Temp = 0;
  SST25_CS_LOW();
  SPI_FLASH_SendByte(SST25_ReadData);
  SPI_FLASH_SendByte((ReadAddr & 0xFF0000) >> 16);
  SPI_FLASH_SendByte((ReadAddr& 0xFF00) >> 8);
  SPI_FLASH_SendByte(ReadAddr & 0xFF);  
  Temp = SPI_FLASH_ReadByte();
  SST25_CS_HIGH();
  return Temp;
}
/************************************************************************
** 函数名称: SST25V_BufferRead		
** 函数功能: SST25VF016B的读取N个字节数据(低速)			
** 入口参数:
**			 u32 ReadAddr：目标地址,
             范围 0x0 - SST25_MAX_ADDR（SST25_MAX_ADDR = 0x1FFFFF）
**           pBuffer:  存放数据的数组
**           NumByteToRead : 数据个数
** 出口参数: 返回读取的数据	
** 备    注: 
************************************************************************/
void SST25V_BufferRead(u8* pBuffer, u32 ReadAddr, u16 NumByteToRead)
{
  SST25_CS_LOW();
  SPI_FLASH_SendByte(SST25_ReadData);
  SPI_FLASH_SendByte((ReadAddr & 0xFF0000) >> 16);
  SPI_FLASH_SendByte((ReadAddr& 0xFF00) >> 8);
  SPI_FLASH_SendByte(ReadAddr & 0xFF);

  while(NumByteToRead--)
  {
    *pBuffer = SPI_FLASH_ReadByte();
    pBuffer++;
  }
  SST25_CS_HIGH();
}
/************************************************************************
** 函数名称: SST25V_HighSpeedRead	
** 函数功能: SST25VF016B的读函数，高速读取1字节		
** 入口参数:
**			 u32 ReadAddr：目标地址,
**			 u8* pBuffer:接收缓存的指针			
** 出口参数: 	
** 备    注: 
************************************************************************/
u8 SST25V_HighSpeedRead(u32 ReadAddr)
{
  u32 Temp = 0;
  SST25_CS_LOW();
  SPI_FLASH_SendByte(SST25_FastReadData);
  SPI_FLASH_SendByte((ReadAddr & 0xFF0000) >> 16);
  SPI_FLASH_SendByte((ReadAddr& 0xFF00) >> 8);
  SPI_FLASH_SendByte(ReadAddr & 0xFF);
  SPI_FLASH_SendByte(SST25_Dummy_Byte);
  Temp = SPI_FLASH_ReadByte();
  SST25_CS_HIGH();
  return Temp;
}
/************************************************************************
** 函数名称: SST25V_HighSpeedBufferRead		
** 函数功能: SST25VF016B的读函数，高速读取N字节		
** 入口参数:
**			 u32 ReadAddr：目标地址,
             范围 0x0 - SST25_MAX_ADDR（SST25_MAX_ADDR = 0x1FFFFF）
**      	 u16 NumByteToRead:	要读取的数据字节数
**			 u8* pBuffer:接收缓存的指针			
** 出口参数: 	
** 备    注: 
************************************************************************/
void SST25V_HighSpeedBufferRead(u8* pBuffer, u32 ReadAddr, u16 NumByteToRead)
{
  SST25_CS_LOW();
  SPI_FLASH_SendByte(SST25_FastReadData);
  SPI_FLASH_SendByte((ReadAddr & 0xFF0000) >> 16);
  SPI_FLASH_SendByte((ReadAddr& 0xFF00) >> 8);
  SPI_FLASH_SendByte(ReadAddr & 0xFF);
  SPI_FLASH_SendByte(SST25_Dummy_Byte);

  while(NumByteToRead--)
  {
    *pBuffer = SPI_FLASH_ReadByte();
    pBuffer++;
  }
  SST25_CS_HIGH();
}
/************************************************************************
** 函数名称: SST25V_Wait_Busy_AAI(void) 				
** 函数功能: SST25VF016B 查询AAI忙？
** 入口参数: 无
** 出口参数: 无	
** 注	 意: 
************************************************************************/
void SST25V_Wait_Busy_AAI(void) 
{ 
  while (SST25V_ReadStatusRegister() == 0x43) /* ???? */
  SST25V_ReadStatusRegister(); 
}
/************************************************************************
** 函数名称: SST25V_ByteWrite				
** 函数功能: SST25VF016B的写函数，可写1个数据到指定地址	
** 入口参数:
**			 u32 WriteAddr：目标地址,范围 0x0 - SST25_MAX_ADDR（SST25_MAX_ADDR = 0x1FFFFF）
**			 u8 Byte:发送数据
** 出口参数: 	
** 注	 意: 
************************************************************************/
void SST25V_ByteWrite(u8 Byte, u32 WriteAddr)
{
  SST25V_WriteEnable();
  SST25_CS_LOW();
  SPI_FLASH_SendByte(SST25_ByteProgram);
  SPI_FLASH_SendByte((WriteAddr & 0xFF0000) >> 16);
  SPI_FLASH_SendByte((WriteAddr & 0xFF00) >> 8);
  SPI_FLASH_SendByte(WriteAddr & 0xFF);
  
  SPI_FLASH_SendByte(Byte);
  SST25_CS_HIGH();
  SST25V_WaitForWriteEnd();
}




/************************************************************************
** 函数名称: SST25V_ByteWrite				
** 函数功能: SST25VF016B的写函数，可写2个数据到指定地址 (AAI写) 带地址的写
**           即 第一次需写地址，以后就是2个2个数据的持续写
** 入口参数:
**			 u32 WriteAddr：目标地址,范围 0x0 - SST25_MAX_ADDR（SST25_MAX_ADDR = 0x1FFFFF）
**			 u8 Byte1, u8 Byte2:发送的2个数据
** 出口参数: 	
** 注	 意: 
************************************************************************/
void AutoAddressIncrement_WordProgramA(u8 Byte1, u8 Byte2, u32 Addr)
{
  SST25V_WriteEnable();
  SST25_CS_LOW();
  SPI_FLASH_SendByte(SST25_AAI_WordProgram);
  SPI_FLASH_SendByte((Addr & 0xFF0000) >> 16);
  SPI_FLASH_SendByte((Addr & 0xFF00) >> 8);
  SPI_FLASH_SendByte(Addr & 0xFF);

  SPI_FLASH_SendByte(Byte1);
  SPI_FLASH_SendByte(Byte2);

  SST25_CS_HIGH();
  SST25V_Wait_Busy_AAI();
  //SPI_FLASH_WaitForWriteEnd();
}
/************************************************************************
** 函数名称: SST25V_ByteWrite				
** 函数功能: SST25VF016B的写函数，可写2个数据到指定地址 (AAI写) 不带地址的写
**           即 第一次需写地址，以后就是2个2个数据的持续写
** 入口参数:
**			 u32 WriteAddr：目标地址,范围 0x0 - SST25_MAX_ADDR（SST25_MAX_ADDR = 0x1FFFFF）
**			 u8 Byte1, u8 Byte2:发送的2个数据
**           u8 state :模式选择，AAI发送数据的最后2个数据之后需要发送一次WRDI
** 出口参数: 	
** 注	 意: 
************************************************************************/
void AutoAddressIncrement_WordProgramB(u8 state,u8 Byte1, u8 Byte2) 
{ 
  SST25V_WriteEnable();
  SST25_CS_LOW();
  SPI_FLASH_SendByte(SST25_AAI_WordProgram);

  SPI_FLASH_SendByte(Byte1);
  SPI_FLASH_SendByte(Byte2);

  SST25_CS_HIGH();
  SST25V_Wait_Busy_AAI();
  
  if(state==1)
  {
    SST25V_WriteDisable();
  }
  SST25V_Wait_Busy_AAI();
}
/************************************************************************
** 函数名称: SST25V_SectorErase_4KByte				
** 函数功能: SST25VF016B 擦除该地址所在的4K存储器的数据
** 入口参数: u32 Addr : 地址
** 出口参数: 无	
** 注	 意: 
************************************************************************/
void SST25V_SectorErase_4KByte(u32 Addr)
{
  SST25V_WriteEnable();
  SST25_CS_LOW();
  SPI_FLASH_SendByte(SST25_4KByte_BlockERASE);
  SPI_FLASH_SendByte((Addr & 0xFF0000) >> 16);
  SPI_FLASH_SendByte((Addr & 0xFF00) >> 8);
  SPI_FLASH_SendByte(Addr & 0xFF);
  
  SST25_CS_HIGH();
  SST25V_WaitForWriteEnd();
}
/************************************************************************
** 函数名称: SST25V_BlockErase_32KByte(u32 Addr)			
** 函数功能: SST25VF016B 擦除该地址所在的32K存储器的数据
** 入口参数: u32 Addr : 地址
** 出口参数: 无	
** 注	 意: 
************************************************************************/
void SST25V_BlockErase_32KByte(u32 Addr)
{
  SST25V_WriteEnable();
  SST25_CS_LOW();
  SPI_FLASH_SendByte(SST25_32KByte_BlockErase);
  SPI_FLASH_SendByte((Addr & 0xFF0000) >> 16);
  SPI_FLASH_SendByte((Addr & 0xFF00) >> 8);
  SPI_FLASH_SendByte(Addr & 0xFF);
  
  SST25_CS_HIGH();
  SST25V_WaitForWriteEnd();
}
/************************************************************************
** 函数名称: SST25V_BlockErase_64KByte(u32 Addr)			
** 函数功能: SST25VF016B 擦除该地址所在的64K存储器的数据
** 入口参数: u32 Addr : 地址
** 出口参数: 无	
** 注	 意: 
************************************************************************/
void SST25V_BlockErase_64KByte(u32 Addr)
{
  SST25V_WriteEnable();
  SST25_CS_LOW();
  SPI_FLASH_SendByte(SST25_64KByte_BlockErase);
  SPI_FLASH_SendByte((Addr & 0xFF0000) >> 16);
  SPI_FLASH_SendByte((Addr & 0xFF00) >> 8);
  SPI_FLASH_SendByte(Addr & 0xFF);
  
  SST25_CS_HIGH();
  SST25V_WaitForWriteEnd();
}
/************************************************************************
** 函数名称: SST25V_ChipErase(void)		
** 函数功能: SST25VF016B 擦除存储器的全部数据
** 入口参数: 无
** 出口参数: 无	
** 注	 意: 
************************************************************************/
void SST25V_ChipErase(void)
{
  SST25V_WriteEnable();
  SST25_CS_LOW();
  SPI_FLASH_SendByte(SST25_ChipErase);
  SST25_CS_HIGH();
  SST25V_WaitForWriteEnd();
}
/************************************************************************
** 函数名称: SST25V_ReadJedecID(void)
** 函数功能: SST25VF016B 读取制造商和器件信息
** 入口参数: 无
** 出口参数: 信息数据
** 注	 意: 
************************************************************************/
u32 SST25V_ReadJedecID(void)
{
  u32 JEDECID = 0, Temp0 = 0, Temp1 = 0, Temp2 = 0;
  SST25_CS_LOW();
  SPI_FLASH_SendByte(SST25_JedecDeviceID);
  Temp0 = SPI_FLASH_ReadByte();
  Temp1 = SPI_FLASH_ReadByte();
  Temp2 = SPI_FLASH_ReadByte();
  SST25_CS_HIGH();  
  JEDECID = (Temp0 << 16) | (Temp1 << 8) | Temp2;
  return JEDECID;
}
/************************************************************************
** 函数名称: SST25V_ReadManuID_DeviceID(u32 ReadManu_DeviceID_Addr)
** 函数功能: SST25VF016B 读取器件信息
** 入口参数: u32 ReadManu_DeviceID_Addr 器件地址
** 出口参数: u16  器件ID
** 注	 意: 
************************************************************************/
u16 SST25V_ReadManuID_DeviceID(u32 ReadManu_DeviceID_Addr)
{
  u16 ManuID_DeviceID = 0;
  u8 ManufacturerID = 0,  DeviceID = 0;
  SST25_CS_LOW();
  SPI_FLASH_SendByte(SST25_ManufactDeviceID);
  
  SPI_FLASH_SendByte((ReadManu_DeviceID_Addr & 0xFF0000) >> 16);
  SPI_FLASH_SendByte((ReadManu_DeviceID_Addr & 0xFF00) >> 8);
  SPI_FLASH_SendByte(ReadManu_DeviceID_Addr & 0xFF);
  
  if(ReadManu_DeviceID_Addr==1)
  {
    DeviceID = SPI_FLASH_ReadByte();
    ManufacturerID = SPI_FLASH_ReadByte();
  }
  else
  {
    ManufacturerID = SPI_FLASH_ReadByte();
    DeviceID = SPI_FLASH_ReadByte();
  }
  
  ManuID_DeviceID = ((ManufacturerID<<8) | DeviceID);
  SST25_CS_HIGH();
  
  return ManuID_DeviceID;
}
/************************************************************************
** 函数名称: SST25V_EBSY()
** 函数功能: SST25VF016B 发送EBSY
** 入口参数: 无
** 出口参数: 无
** 注	 意: 
************************************************************************/
void SST25V_EBSY()
{ 
  SST25_CS_LOW();
  SPI_FLASH_SendByte(SST25_EBSY);
  SST25_CS_HIGH();
} 
/************************************************************************
** 函数名称: SST25V_EBSY()
** 函数功能: SST25VF016B 发送DBSY
** 入口参数: 无
** 出口参数: 无
** 注	 意: 
************************************************************************/
void SST25V_DBSY()
{ 
  SST25_CS_LOW();
  SPI_FLASH_SendByte(SST25_DBSY);
  SST25_CS_HIGH();
}
/************************************************************************
** 函数名称: SSTF016B_WriteSingleBlock		
** 函数功能: 在1个扇区内写多个数据
** 入口参数:
**			 unsigned long W_address：目标地址,
**                范围 0x0 - SST25_MAX_ADDR（SST25_MAX_ADDR = 0x1FFFFF）
**			 unsigned char* SndbufPt:要发送的数组
**           unsigned int Count:发送数据个数
** 出口参数: 	
** 注	 意: 
************************************************************************/
void SSTF016B_WriteOneByte(unsigned long W_address, unsigned char byte)
{
    unsigned long Dst;
    unsigned long i;
    unsigned char SST25VFTemp[4096]={0,0,0,0,0,0,0,0,0,};
    Dst = W_address / 4096;    //计算数据所在的扇区的起始地址
    Dst = Dst * 4096;
    SST25V_BufferRead(SST25VFTemp,Dst,4096); //先将改扇区内的数据读出
    SST25V_SectorErase_4KByte(Dst);          //擦除改扇区
    SST25VFTemp[W_address % 4096] = byte;   
//     for(i = 0;i < 4096;i ++)      //赋值数组
// 	{
//         SST25V_ByteWrite(SST25VFTemp[i],Dst + i);
// 	}	
    AutoAddressIncrement_WordProgramA(SST25VFTemp[0],SST25VFTemp[1], Dst);    
    for(i = 2;i < 4094;i += 2)      //赋值数组
	{
        AutoAddressIncrement_WordProgramB(0,SST25VFTemp[i],SST25VFTemp[i + 1]);
	}	
    AutoAddressIncrement_WordProgramB(1,SST25VFTemp[4094],SST25VFTemp[4095]);	
}




/************************************************************************
** 函数名称: SSTF016B_WriteSingleBlock		
** 函数功能: 在1个扇区内写多个数据
** 入口参数:
**			 unsigned long W_address：目标地址,
**                范围 0x0 - SST25_MAX_ADDR（SST25_MAX_ADDR = 0x1FFFFF）
**			 unsigned char* SndbufPt:要发送的数组
**           unsigned int Count:发送数据个数
** 出口参数: 	
** 注	 意: 
************************************************************************/
void SSTF016B_WriteSingleBlock(unsigned long W_address, unsigned char* SndbufPt, unsigned int Count)
{
    unsigned long Sector ;
    unsigned long i = 0;
    unsigned long Dst = 0;
    unsigned char SST25VFTemp[4096]={0,0,0,0,0,0,0,0,0,};
    unsigned int  m;   // 数据在该扇区内剩余的数据
        
    m      = W_address % 4096;
    Sector = W_address / 4096;    //  除以512,扇区数
    Dst = Sector * 4096;//计算芯片扇区地址
    SST25V_BufferRead(SST25VFTemp,Dst,4096); //先将改扇区内的数据读出
    SST25V_SectorErase_4KByte(Dst);          //擦除改扇区
    for(i = 0;i < Count;i ++)      //赋值数组
	{
        SST25VFTemp[i + m] = SndbufPt[i];
	}
    AutoAddressIncrement_WordProgramA(SST25VFTemp[0],SST25VFTemp[1], Dst);    
    for(i = 2;i < 4094;i += 2)      //赋值数组
	{
        AutoAddressIncrement_WordProgramB(0,SST25VFTemp[i],SST25VFTemp[i + 1]);
	}	
    AutoAddressIncrement_WordProgramB(1,SST25VFTemp[4094],SST25VFTemp[4095]); 		
}
/************************************************************************
** 函数名称: SSTF016B_WriteMultiBlock	
** 函数功能: 在相邻的2个扇区内写多个数据
** 入口参数:
**			 unsigned long W_address：目标地址,
**                范围 0x0 - SST25_MAX_ADDR（SST25_MAX_ADDR = 0x1FFFFF）
**			 unsigned char* SndbufPt:要发送的数组
**           unsigned int Count:发送数据个数
** 出口参数: 	
** 注	 意:   有bug 使用此函数时，刷卡延时值会变成0xff
************************************************************************/
void SSTF016B_WriteMultiBlock(unsigned long pW_address, unsigned char* pSndbufPt,unsigned int pCount)
{
    unsigned long Sector ;
    unsigned long Dst = 0;
    unsigned int  m;   // 数据在该扇区内剩余的数据
        
    m      = pW_address % 4096;
    Sector = pW_address / 4096;    //  除以512,扇区数
    
    if( (4096 - m) >= pCount)
    {
        SSTF016B_WriteSingleBlock(pW_address,pSndbufPt, pCount);
    }
    else
    {
        SSTF016B_WriteSingleBlock(pW_address,pSndbufPt, 4096 - m);
        Dst = Sector * 4096 + 4096;            
        SSTF016B_WriteSingleBlock(Dst,&pSndbufPt[4096 - m], pCount - ( 4096 - m));
	
    }	
}

 //结合AB构成的地址自动增加的连续数据的写入  
//具有先擦除待写区域的功能  
//pBuffer：为待写数据组  
//WriteAddr：所写数据的起始地址  
//NumByteToWrite：所要写的数据的长度  
//void SPI_Flash_Write_sst(u8* pBuffer,u32 WriteAddr,u16 NumByteToWrite)  
// {  
// u16 i,temp;  
// u32 secpos;  
// u16 secoff;  
// u16 secremain;       
// //以下代码为擦除待写区域的代码  
//secpos=WriteAddr/4096;                                           //扇区（4K）地址0~511 for     SST25VF016  
//secoff=WriteAddr%4096;                                                             //在扇区内的偏移  
//secremain=4096-secoff;                                                           //扇区剩余空间大小  
//if(NumByteToWrite<secremain)                                                  //剩余空间大于所存数据  
//{  
//   temp=1;  
// }  
// else                                                                 //剩余空间小于所存数据  
//{  
//   i=NumByteToWrite-secremain;                           //判断还占了几个扇区  
//if(i%4096==0)  
//        temp=i/4096+1;  
// else  
//        temp=i/4096+2;  
// }  
// for(i=0;i<temp;i++)  
// {  
//   SST25V_SectorErase_4KByte((secpos+i)*4096);                   //擦除将要写入数据的扇区     
// }  
//   //以下代码为将数据写入指定地址的代码  
//if(NumByteToWrite%2==0)  
// {  
//   temp=NumByteToWrite/2-1;  
// }  
// else  
// {  
//   temp=NumByteToWrite/2;  
// }  
// AutoAddressIncrement_WordProgramA(pBuffer[0], pBuffer[1],WriteAddr );                                        //开始写数据  
//for(i=1;i<temp;i++)  
// {  
//   AutoAddressIncrement_WordProgramB(0,pBuffer[2*i], pBuffer[2*i+1]);  
// }  
// if(NumByteToWrite%2==0)  
// {  
//   AutoAddressIncrement_WordProgramB(1,pBuffer[NumByteToWrite-2], pBuffer[NumByteToWrite-1]);   //结束写数据  
//}  
//else  
// {  
//   AutoAddressIncrement_WordProgramB(1,pBuffer[NumByteToWrite-1],0);                                         //结束写数据  
//}  
// } 


























