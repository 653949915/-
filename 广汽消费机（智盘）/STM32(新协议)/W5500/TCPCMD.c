#include "Head.h"






















/**********************************************************
//初始化串口通讯缓冲区
**********************************************************/
void InitRj45buff(void)
{
 memset(rj45buff,0,sizeof(rj45buff));
	
	InitCombuff();
	
}


/**********************************************************
//通讯数据检验
**********************************************************/
u32 CheckRJ45Data(void)
{
	u8   DEF_MACHNO[] = {0X51,0X05,0X07,0X01};

  u8	 ch;
		

	if (rj45buff[0] != '*') { return 0; }

	
	if (!MyStrEQ(rj45buff + 1, machno, 4) && 
		!MyStrEQ(rj45buff + 1, DEF_MACHNO, 4)) { return 0; }

	Data_length=separate_value_2_1(rj45buff+7);         	//2字节地址合并	
		
	ch = GetXOR(rj45buff + 1, Data_length + 8);
		
	if (ch != rj45buff[Data_length + 9]) { return 0; }//异或检验

	return 1;

}

/**********************************************************
//处理485通讯
**********************************************************/
void ProcessRJ45(void)
{	

	if (!CheckRJ45Data()) { goto com_end; } //检查数据 
			
	 memcpy( combuff, rj45buff,sizeof(rj45buff));
	
	switch (combuff[6]) //处理命令
	{
		           
	//	 case 0x30: BeginOutput(); break;
				              
        case 0x01: GetMachType();             break;     //读取机器型号
    		case 0x02: GetVersion();              break;     //读取版本信息
  		  case 0x03: SetMachno();               break;     //设置机号
	    	case 0x04: GetMachno();               break;     //读取机号		
			  case 0x05: SetTime();                 break;     //设置时间
		    case 0x06: GetTime();                 break;     //读取时间
    	  case 0x07: SetSectionAndPassword();   break;     //设置读写扇区与密码	
    	  case 0x08: GetSectionAndPassword();   break;     //读取读写扇区与密码		
			  case 0x09: Set_Clock_delay();		      break;     //设置打卡延时			
			  case 0x0A: Set_Output_delay();		    break;     //设置开门延时				
				case 0x0B: Set_list_enabled();		    break;     //设置白名单是否开启		
				case 0x0C: Get_sysvar();		          break;     //读取机器基本参数		
				case 0x0D: Set_Restore_factory();		  break;     //恢复出厂设置		
				case 0x0E: Get_ChipInfo_Com();		    break;     //读取芯片信息			

		    case 0x11: Set_TCP_Mode();            break;     //设置TCP模式(服务器or客户端)		
		    case 0x12: Set_TCP_Local_IPandPort(); break;     //设置本地IP地址和端口号			
		    case 0x13: Get_TCP_Local_IPandPort(); break;     //读取本地IP地址和端口号			
		    case 0x14: Set_TCP_Remote_IPandPort();break;     //设置远端IP地址和端口号		
		    case 0x15: Get_TCP_Remote_IPandPort();break;     //读取远端IP地址和端口号					
		    case 0x16: SetWhiteGroupName();       break;     //下发全部白名单
			  case 0x17: GetWhiteGroupName();			  break;     //读取全部白名单
        case 0x18: ClearWhiteName();				  break;     //清除所有白名单
		    case 0x19: TEST_GQ();                 break;     //追加单条白名单
		    case 0x1A: TEST_GQ();                 break;     //删除单条白名单
  	  	case 0x1B: SetBackGroupName();        break;     //下发全部黑名单		
  	  	case 0x1C: GetBackGroupName();        break;     //读取全部黑名单
  	  	case 0x1D: ClearBackName();           break;     //清除全部黑名单
  	  	case 0x1E: TEST_GQ();                 break;     //追加一条黑名单		 
  	  	case 0x1F: DelOneBackGroupName();     break;     //删除一条黑名单				
					
		    case 0x21: GetMaxRecordCount_GQ();    break;     //读取刷卡记录数量
  			case 0x22: GetRecord_GQ();  				  break;     //读取新增刷卡记录
				case 0x23: GetRecord_GQ_1();  				break;     //读取全部刷卡记录
			  case 0x24: ClearRecord();             break;     //清除所有刷卡记录



				case 0x31: Set_ReadorWriteICData_Mode();break;     //设置是否读写卡扇区数据
			  case 0x32: Set_Check_Sector_Password_Mode();  break;     //设置是否检测密码
			  case 0x33: Get_Extvar();  break;     //获取扩展参数



  			case 0x25: TEST_GQ();  				       break;     //测试
 	
		    default:  goto com_end;
	}

	com_end:
	  InitRj45buff();

  
}









