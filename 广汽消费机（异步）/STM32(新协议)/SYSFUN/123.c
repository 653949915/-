#include "Head.h"





//////////////////////////////////////////////////////////////////////////////////////////////////
//					����Ϊ�û�Ҫ����Ӳ���͹��ܸı�Ĳ���,�����ΪKEY����ϵͳ����ֲ�ļ�
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "shujuku.h"
#include <stdio.h>
#include <cstring>

u8 Key_Value=21;
u8 Key_Model=0;        //0ΪСд��ĸ��1Ϊ��д��ĸ��2Ϊ���֣�3Ϊ���
u8 Key_hang;					//��ʾ�ַ�������
u8 Key_lie;						//��ʾ�ַ�������

u8 usr_key;
char show[3];

u8 i=0;
u8 j=0;

/**************************************************************
**������:KeyTransfer
**����:����ֵ��ת��
**ע������:�������µ�ֵ,һ��ΪӲ��ֵ,һ��Ҫ�����Ӳ��ֵת��Ϊ���ֵ����ܱ��û���������
			ת����ʽ���԰�Ӳ�����������.�ȽϿ�ݵľ���������ķ�ʽֱ��ת��,ĳЩ��Ҫ��������Ҫ�����ر���
**************************************************************/
u8 KeyTransfer(HALKEY_TYPE key)
{
	if(Key_Model>4)
	{
		Key_Model=0;
	}
	if(key<MAX_KEY_NO+1)
	{
		if(Key_Model==0)   //0Ϊ��д��ĸ
		{
			if(Key_Mark&KEY_FIRST)
			{
				Key_Value=Key_Model0_FIRST[key];
			}
			else if(Key_Mark&KEY_SECOND)
			{
				Key_Value=Key_Model0_SECOND[key];
			}
			else if(Key_Mark&KEY_THIRD)
			{
				Key_Value=Key_Model0_THIRD[key];
			}
			else
			{
				Key_Value=21;
			}		
		}
		else if(Key_Model==1)  //1Ϊ��д��ĸ
		{
			if(Key_Mark&KEY_FIRST)
			{
				Key_Value=Key_Model1_FIRST[key];
			}
			else if(Key_Mark&KEY_SECOND)
			{
				Key_Value=Key_Model1_SECOND[key];
			}
			else if(Key_Mark&KEY_THIRD)
			{
				Key_Value=Key_Model1_THIRD[key];
			}
			else
			{
				Key_Value=21;
			}		
		}
		else if(Key_Model==2)  //2Ϊ���֣�
		{
			Key_Value=Key_Model2[key];	
		}

		else if(Key_Model==4)   //
		{
			Key_Value=Key_Model4;	  //18
		}
		else
			Key_Value=21;
	}
	return Key_Value;
} 



#ifndef SHUJUKU_H
#define SHUJUKU_H

//�������ļ�ֵ,
#define MAX_KEY_NO		19		//16������





u8 Key_Model0_FIRST[]=
{
	KEY_NONE,
	's',    'a',    'd',       KEY_BACK,
	'g',      'j',    'm',       KEY_SPACE,
	'p',      't',    'w',       KEY_ESC,
	KEY_STAR, KEY_0,  KEY_POUND, KEY_ENTER
};  

u8 Key_Model0_SECOND[]=
{
	KEY_NONE,
	'z',    'b',    'e',       KEY_BACK,
	'h',      'k',    'n',       KEY_SPACE,
	'q',      'u',    'x',       KEY_ESC,
	KEY_STAR, KEY_0,  KEY_POUND, KEY_ENTER
}; 

u8 Key_Model0_THIRD[]=
{
	KEY_NONE,
	KEY_1,    'c',    'f',       KEY_BACK,
	'i',      'l',    'o',       KEY_SPACE,
	'r',      'v',    'y',       KEY_ESC,
	KEY_STAR, KEY_0,  KEY_POUND, KEY_ENTER
}; 

u8 Key_Model1_FIRST[]=
{
	KEY_NONE,
	'S',    'A',    'D',       KEY_BACK,
	'G',      'J',    'M',       KEY_SPACE,
	'P',      'T',    'W',       KEY_ESC,
	KEY_STAR, KEY_0,  KEY_POUND, KEY_ENTER
};

u8 Key_Model1_SECOND[]=
{
	KEY_NONE,
	'Z',     'B',   'E',       KEY_BACK,
	'H',       'K',   'N',       KEY_SPACE,
	'Q',       'U',   'X',       KEY_ESC,
	KEY_STAR,  KEY_0, KEY_POUND, KEY_ENTER
}; 

u8 Key_Model1_THIRD[]=
{
	KEY_NONE,
	KEY_1,     'C',   'F',       KEY_BACK,
	'I',       'L',   'O',       KEY_SPACE,
	'R',       'V',   'Y',       KEY_ESC,
	KEY_STAR,  KEY_0, KEY_POUND, KEY_ENTER
};

u8 Key_Model2[]=
{
	KEY_NONE,
	KEY_1,    KEY_2,  KEY_3,     KEY_BACK,
	KEY_4,    KEY_5,  KEY_6,     KEY_SPACE,
	KEY_7,    KEY_8,  KEY_9,     KEY_ESC,
	KEY_STAR, KEY_0,  KEY_POUND, KEY_ENTER
}; 

/*���ֵ�ת����*/


#endif



