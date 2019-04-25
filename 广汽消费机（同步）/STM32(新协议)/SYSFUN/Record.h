#ifndef	__RECORD_H__
#define	__RECORD_H__
#include "sys.h"	
///**********************************************************
//SST25VF32��¼�洢 1MB
//**********************************************************/
//#define	RECORD_SIZE		14L   //��¼���ȣ���L�ܹؼ��� 
//#define	SECTOR_SIZE		4096L //ҳ�ֽ�
//#define	MAX_PAGE		  256L  //ҳ��
//#define RECORD_ST		  0L
//#define MAX_RECORD		((MAX_PAGE * SECTOR_SIZE - RECORD_ST) / RECORD_SIZE)  //(256*4096-0)/14=74898.285...  


///**********************************************************
////SST25VF32��¼�洢 3MB
//**********************************************************/
//#define	RECORD_SIZE		16L   //��¼���ȣ���L�ܹؼ��� 
//#define	SECTOR_SIZE		4096L //ҳ�ֽ�
//#define	MAX_PAGE		  512L  //ҳ��
//#define RECORD_ST		  0L
//#define MAX_RECORD		((MAX_PAGE * SECTOR_SIZE - RECORD_ST) / RECORD_SIZE)  //(768*4096-0)/16=196608  



/**********************************************************
W25Q64 ��¼�洢  8MB   8388608
**********************************************************/
#define W25X_PAGE_SIZE      1920L//                       //256L         /* ����ҳ��С          */  
#define W25X_PAGE_NUM       3215L//20w��   ���4369Lҳ    //32768L       /* ����ҳ�ĸ���        */ 

#define	RECORD_SIZE		30L    //��¼���ȣ���L�ܹؼ��� 
#define	SECTOR_SIZE		4096L  //�����ֽ���
#define	MAX_PAGE		  2048L  //������ 256*8=2048
#define RECORD_ST		  0L

#define MAX_RECORD		205760L //((W25X_PAGE_SIZE *W25X_PAGE_NUM)/RECORD_SIZE)  /*(1920*3215)/30 = 205760*/        //((MAX_PAGE * SECTOR_SIZE - RECORD_ST) / RECORD_SIZE)  //(2048*4096-0)/30=279620 


#define UPDATA_POS    W25X_PAGE_NUM*W25X_PAGE_SIZE         //ʵʱ�ϴ��洢λ��

#define UPDATA_MAX_RECORD      75008L                       //ʵʱ�ϴ��������1172ҳ     ʵ�����79616

#define W25X_UPDATAPAGE_NUM       1000L //       /* ����ҳ�ĸ���        */ 

#define W25X_PAGE_MAXNUM        4369L     //���ҳ�� 

/**********************************************************
//�ⲿ��������
**********************************************************/
extern  uint32_t  recordcount;//��¼����	

extern  uint32_t stopdate_addr;               // ��������ĩ�˵�ַ
extern	uint8_t  recorddata[];            //flash�洢�����ݣ�16�ֽڣ�
extern	uint8_t  recorddataup[];            //flash�洢�����ݣ�16�ֽڣ�
	
extern uint8_t   rdtemporary_count;         //������¼��ʱ�洢���� eeprom
extern uint32_t  rdrealtime_up_count;       //������¼ʵʱ�ϴ����� flash	
extern uint16_t  uploadflash_cycle ;         //ʵʱ�ϴ����浽flashʱ�����

extern uint8_t  temporarydata[];            //������¼��ʱ�洢  //ʵʱ�ϴ���

extern uint32_t  Flow_number ;                //��ˮ��

extern  uint32_t  Actual_Card_number ;                //ʵ����������
 
extern  uint32_t  Err_Card_number ;                   //������������
 
extern  uint32_t  Operation_Comm_number ;             //������������

extern  uint8_t  maxrecordcount_err ;             //�����������

extern  uint8_t  recordcount_err ;                //�洢�������

extern u8  def_Consum_Amount[] ;	               //Ĭ�����ѽ��

/**********************************************************
//�ⲿ��������
**********************************************************/
void InitRecord(void);
void DelRecord(void);//ɾ����¼
void AddRecord(u8 cnt ,uint8_t type);//���Ӽ�¼

void Init_UpdataRecord(void);         //��ʼ��ʵʱ�ϴ���¼�洢���� 
void Save_UpdataRecordCount(void);    //����ʵʱ�ϴ���¼����
void Del_UpdataRecord(void);          //ɾ������ʵʱ�ϴ���¼

void Add_UpdataRecord(uint8_t typ);    //����ʵʱ�ϴ���¼

void UPloadRecord(u8 stype);

void  Arrange_Record(u8 cnt ,uint8_t type);

void DelUPloadRecord(u8 *rd);    //ɾ��ʵʱ�ϴ�ˢ����¼


void InitOperation_CommCount(void);   //��ʼ������������

void InitActual_CardCount(void);   //��ʼ��ʵ����������

void InitErr_CardCount(void);      //��ʼ��������������

void SaveActual_CardCount(void);   //����ʵ����������

void SaveOperation_CommCount(void);  //�����������

void SaveErr_CardCount(void);    //���������������

void InitRecordcount_Err(void);  //��ʼ�洢����

void SaveRecordcount_Err(void); //����洢����


#endif


