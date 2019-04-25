#include "Head.h"





//////////////////////////////////////////////////////////////////////////////////////////////////
//					以下为用户要根据硬件和功能改变的部分,可理解为KEY管理系统的移植文件
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "shujuku.h"
#include <stdio.h>
#include <cstring>

u8 Key_Value=21;
u8 Key_Model=0;        //0为小写字母，1为大写字母，2为数字，3为标点
u8 Key_hang;					//显示字符所在行
u8 Key_lie;						//显示字符所在列

u8 usr_key;
char show[3];

u8 i=0;
u8 j=0;

/**************************************************************
**函数名:KeyTransfer
**功能:按键值的转变
**注意事项:按键按下的值,一般为硬件值,一般要从这个硬件值转化为软件值后才能被用户程序利用
			转化方式可以按硬件的情况而定.比较快捷的就是用数组的方式直接转变,某些需要复键的则要自行特别处理
**************************************************************/
u8 KeyTransfer(HALKEY_TYPE key)
{
	if(Key_Model>4)
	{
		Key_Model=0;
	}
	if(key<MAX_KEY_NO+1)
	{
		if(Key_Model==0)   //0为大写字母
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
		else if(Key_Model==1)  //1为大写字母
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
		else if(Key_Model==2)  //2为数字，
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

//最大允许的键值,
#define MAX_KEY_NO		19		//16个按键





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

/*文字的转换库*/


#endif



