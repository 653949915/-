#ifndef	__EC20FUN_H__
#define	__EC20FUN_H__
#include  "sys.h"

typedef struct
{
	
	unsigned char err ; 		  //错误类型
	unsigned char errcount ; 	//错误计数
	unsigned char initStep ;	//初始化步骤
	unsigned char dataType ;	//设定数据返回类型--16种
	unsigned char reboot ;		//死机重启标志
	unsigned char netWork ;		//网络访问OK
	unsigned char send_ok ;		//网络设备层的发送成功
	unsigned char reverse ;		//预留
	unsigned char reverse2;		//预留2

} KT_DEVICE_INFO;


extern KT_DEVICE_INFO   ec20_device_info;

extern uint8_t  ec20_remoteipbuf[];        //远端IP端口

void Process4G_Commu(void);                 //处理4G通讯

void Init_EC20_Remote_IP(void);

void   ec20sufatest(void );


#endif	

