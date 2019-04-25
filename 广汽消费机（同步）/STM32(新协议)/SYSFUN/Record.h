#ifndef	__RECORD_H__
#define	__RECORD_H__
#include "sys.h"	
///**********************************************************
//SST25VF32记录存储 1MB
//**********************************************************/
//#define	RECORD_SIZE		14L   //记录长度，带L很关键！ 
//#define	SECTOR_SIZE		4096L //页字节
//#define	MAX_PAGE		  256L  //页数
//#define RECORD_ST		  0L
//#define MAX_RECORD		((MAX_PAGE * SECTOR_SIZE - RECORD_ST) / RECORD_SIZE)  //(256*4096-0)/14=74898.285...  


///**********************************************************
////SST25VF32记录存储 3MB
//**********************************************************/
//#define	RECORD_SIZE		16L   //记录长度，带L很关键！ 
//#define	SECTOR_SIZE		4096L //页字节
//#define	MAX_PAGE		  512L  //页数
//#define RECORD_ST		  0L
//#define MAX_RECORD		((MAX_PAGE * SECTOR_SIZE - RECORD_ST) / RECORD_SIZE)  //(768*4096-0)/16=196608  



/**********************************************************
W25Q64 记录存储  8MB   8388608
**********************************************************/
#define W25X_PAGE_SIZE      1920L//                       //256L         /* 定义页大小          */  
#define W25X_PAGE_NUM       3215L//20w条   最大4369L页    //32768L       /* 定义页的个数        */ 

#define	RECORD_SIZE		30L    //记录长度，带L很关键！ 
#define	SECTOR_SIZE		4096L  //扇区字节数
#define	MAX_PAGE		  2048L  //扇区数 256*8=2048
#define RECORD_ST		  0L

#define MAX_RECORD		205760L //((W25X_PAGE_SIZE *W25X_PAGE_NUM)/RECORD_SIZE)  /*(1920*3215)/30 = 205760*/        //((MAX_PAGE * SECTOR_SIZE - RECORD_ST) / RECORD_SIZE)  //(2048*4096-0)/30=279620 


#define UPDATA_POS    W25X_PAGE_NUM*W25X_PAGE_SIZE         //实时上传存储位置

#define UPDATA_MAX_RECORD      75008L                       //实时上传最大数量1172页     实际最大79616

#define W25X_UPDATAPAGE_NUM       1000L //       /* 定义页的个数        */ 

#define W25X_PAGE_MAXNUM        4369L     //最大页数 

/**********************************************************
//外部变量声明
**********************************************************/
extern  uint32_t  recordcount;//记录数量	

extern  uint32_t stopdate_addr;               // 新增数据末端地址
extern	uint8_t  recorddata[];            //flash存储的数据（16字节）
extern	uint8_t  recorddataup[];            //flash存储的数据（16字节）
	
extern uint8_t   rdtemporary_count;         //数卡记录临时存储计数 eeprom
extern uint32_t  rdrealtime_up_count;       //数卡记录实时上传数量 flash	
extern uint16_t  uploadflash_cycle ;         //实时上传保存到flash时间计数

extern uint8_t  temporarydata[];            //数卡记录临时存储  //实时上传用

extern uint32_t  Flow_number ;                //流水号

extern  uint32_t  Actual_Card_number ;                //实际数卡数量
 
extern  uint32_t  Err_Card_number ;                   //错误数卡数量
 
extern  uint32_t  Operation_Comm_number ;             //操作命令数量

extern  uint8_t  maxrecordcount_err ;             //超出最大容量

extern  uint8_t  recordcount_err ;                //存储错误计数

extern u8  def_Consum_Amount[] ;	               //默认消费金额

/**********************************************************
//外部函数声明
**********************************************************/
void InitRecord(void);
void DelRecord(void);//删除记录
void AddRecord(u8 cnt ,uint8_t type);//增加记录

void Init_UpdataRecord(void);         //初始化实时上传记录存储个数 
void Save_UpdataRecordCount(void);    //保存实时上传记录数量
void Del_UpdataRecord(void);          //删除所有实时上传记录

void Add_UpdataRecord(uint8_t typ);    //保存实时上传记录

void UPloadRecord(u8 stype);

void  Arrange_Record(u8 cnt ,uint8_t type);

void DelUPloadRecord(u8 *rd);    //删除实时上传刷卡记录


void InitOperation_CommCount(void);   //初始操作命令数量

void InitActual_CardCount(void);   //初始化实际数卡数量

void InitErr_CardCount(void);      //初始化错误数卡数量

void SaveActual_CardCount(void);   //保存实际数卡数量

void SaveOperation_CommCount(void);  //保存操作命令

void SaveErr_CardCount(void);    //保存错误数卡数量

void InitRecordcount_Err(void);  //初始存储错误

void SaveRecordcount_Err(void); //保存存储错误


#endif


