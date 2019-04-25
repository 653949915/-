#include "Head.h"






















/**********************************************************
//��ʼ������ͨѶ������
**********************************************************/
void InitRj45buff(void)
{
 memset(rj45buff,0,sizeof(rj45buff));
	
	InitCombuff();
	
}


/**********************************************************
//ͨѶ���ݼ���
**********************************************************/
u32 CheckRJ45Data(void)
{
	u8   DEF_MACHNO[] = {0X51,0X05,0X07,0X01};

  u8	 ch;
		

	if (rj45buff[0] != '*') { return 0; }

	
	if (!MyStrEQ(rj45buff + 1, machno, 4) && 
		!MyStrEQ(rj45buff + 1, DEF_MACHNO, 4)) { return 0; }

	Data_length=separate_value_2_1(rj45buff+7);         	//2�ֽڵ�ַ�ϲ�	
		
	ch = GetXOR(rj45buff + 1, Data_length + 8);
		
	if (ch != rj45buff[Data_length + 9]) { return 0; }//������

	return 1;

}

/**********************************************************
//����485ͨѶ
**********************************************************/
void ProcessRJ45(void)
{	

	if (!CheckRJ45Data()) { goto com_end; } //������� 
			
	 memcpy( combuff, rj45buff,sizeof(rj45buff));
	
	switch (combuff[6]) //��������
	{
		           
	//	 case 0x30: BeginOutput(); break;
				              
        case 0x01: GetMachType();             break;     //��ȡ�����ͺ�
    		case 0x02: GetVersion();              break;     //��ȡ�汾��Ϣ
  		  case 0x03: SetMachno();               break;     //���û���
	    	case 0x04: GetMachno();               break;     //��ȡ����		
			  case 0x05: SetTime();                 break;     //����ʱ��
		    case 0x06: GetTime();                 break;     //��ȡʱ��
    	  case 0x07: SetSectionAndPassword();   break;     //���ö�д����������	
    	  case 0x08: GetSectionAndPassword();   break;     //��ȡ��д����������		
			  case 0x09: Set_Clock_delay();		      break;     //���ô���ʱ			
			  case 0x0A: Set_Output_delay();		    break;     //���ÿ�����ʱ				
				case 0x0B: Set_list_enabled();		    break;     //���ð������Ƿ���		
				case 0x0C: Get_sysvar();		          break;     //��ȡ������������		
				case 0x0D: Set_Restore_factory();		  break;     //�ָ���������		
				case 0x0E: Get_ChipInfo_Com();		    break;     //��ȡоƬ��Ϣ			

		    case 0x11: Set_TCP_Mode();            break;     //����TCPģʽ(������or�ͻ���)		
		    case 0x12: Set_TCP_Local_IPandPort(); break;     //���ñ���IP��ַ�Ͷ˿ں�			
		    case 0x13: Get_TCP_Local_IPandPort(); break;     //��ȡ����IP��ַ�Ͷ˿ں�			
		    case 0x14: Set_TCP_Remote_IPandPort();break;     //����Զ��IP��ַ�Ͷ˿ں�		
		    case 0x15: Get_TCP_Remote_IPandPort();break;     //��ȡԶ��IP��ַ�Ͷ˿ں�					
		    case 0x16: SetWhiteGroupName();       break;     //�·�ȫ��������
			  case 0x17: GetWhiteGroupName();			  break;     //��ȡȫ��������
        case 0x18: ClearWhiteName();				  break;     //������а�����
		    case 0x19: TEST_GQ();                 break;     //׷�ӵ���������
		    case 0x1A: TEST_GQ();                 break;     //ɾ������������
  	  	case 0x1B: SetBackGroupName();        break;     //�·�ȫ��������		
  	  	case 0x1C: GetBackGroupName();        break;     //��ȡȫ��������
  	  	case 0x1D: ClearBackName();           break;     //���ȫ��������
  	  	case 0x1E: TEST_GQ();                 break;     //׷��һ��������		 
  	  	case 0x1F: DelOneBackGroupName();     break;     //ɾ��һ��������				
					
		    case 0x21: GetMaxRecordCount_GQ();    break;     //��ȡˢ����¼����
  			case 0x22: GetRecord_GQ();  				  break;     //��ȡ����ˢ����¼
				case 0x23: GetRecord_GQ_1();  				break;     //��ȡȫ��ˢ����¼
			  case 0x24: ClearRecord();             break;     //�������ˢ����¼



				case 0x31: Set_ReadorWriteICData_Mode();break;     //�����Ƿ��д����������
			  case 0x32: Set_Check_Sector_Password_Mode();  break;     //�����Ƿ�������
			  case 0x33: Get_Extvar();  break;     //��ȡ��չ����



  			case 0x25: TEST_GQ();  				       break;     //����
 	
		    default:  goto com_end;
	}

	com_end:
	  InitRj45buff();

  
}









