

#include <stdio.h>
#include <string.h>	
#include <math.h>

#include "43inchLCD.h"
#include "43inchGUI.h"

//#include "stdio.h"	
#include "delay.h"
#include "43inch_Config.h"

extern uint lcdx,lcdy;			
extern uchar LCDTYPE,TOUCHTYPE;
extern volatile uint Bcolor;
extern volatile uint Fcolor;
extern volatile ulong  count;
extern uchar FONT,FLASHTYPE;
extern u32 Layer0,Layer1,Layer2,Layer3;;
extern volatile uchar MPU_Interface;
//extern const unsigned char logo[153600];
extern const uint Touch_Coordinate[8][6];
extern uint Button_State[4];
extern uchar Touch_State;

 u8  num_43inchlcd[]={"0123456789 :.-"};

/*******************************************************************************
* 函数名  : 设置背光亮度
* 描述    : 设置液晶背光亮度
* 输入          : 设定背光亮度 范围0~100           
* 输出         : None
* 返回         : None
*******************************************************************************/
 void Set_Backlight(uchar bl) //设置背光亮度，范围0~100
{
Set_PWM_Prescaler_1_to_256(1);
Select_PWM0_Clock_Divided_By_1();
Select_PWM0();								
Set_Timer0_Count_Buffer(6000); 
Set_Timer0_Compare_Buffer(bl*60);
Start_PWM0();  							
}

void GUI_CleanScreen(void) //用背景色清屏
{
  Foreground_color_65k(Bcolor);//
	Line_Start_XY(0,0);
	Line_End_XY(lcdx-1,lcdy-1);
	Start_Square_Fill();
	Foreground_color_65k(Fcolor);	
}
/*******************************************************************************
* 函数名  : 设置前景色和背景色
* 描述    : 设置液晶前景色和背景色
* 输入    : 设置前景色BC 背景色FC                  
* 输出    : 前景色Fcolor 背景色Bcolor
* 返回    : None
*******************************************************************************/
void Set_Color(uint bc,uint fc)//设置bc为背景色，fc为前景色
{
Foreground_color_65k(fc);
Background_color_65k(bc);	
Bcolor=bc,Fcolor=fc;
}

/*******************************************************************************
* 函数名  : 以前景色显示一个点
* 描述    : 在液晶屏上显示一个点 ,坐标范围不超液晶分辨率
* 输入    : 设定点的坐标位置X Y                                
* 输出    : None
* 返回    : None
*******************************************************************************/
void GUI_Point(uint x,uint y)//画一点，x、y为坐标值
{
    LCD_SetCursor(x, y);
    LCD_WriteRAM_Prepare(); 
	 	if(MPU_Interface==2)
	{ 
	LCD_DataWrite(Fcolor);
	}
	else
	{
LCD_DataWrite(Fcolor&0x00ff);
LCD_DataWrite(Fcolor>>8);	
 }

	
}
/*******************************************************************************
* 函数名  : 读取一个点颜色数据
* 描述    : 读取液晶屏上一个点的颜色数据 ,坐标范围不超液晶分辨率
* 输入          : 设定读取坐标点的位置X Y 
* 输出         : None
* 返回         :  颜色数据
*******************************************************************************/
uint GUI_ReadPoint(uint x,uint y)//读一点，x、y为坐标值
{	uint readcolor;
	  LCD_SetCursor(x, y);
    LCD_WriteRAM_Prepare(); 
	 	if(MPU_Interface==2)
	{ LCD_DataRead();
	readcolor=LCD_DataRead();
	}
	else
	{
LCD_DataRead();LCD_DataRead();
readcolor= LCD_DataRead();	
readcolor=(readcolor<<8)+LCD_DataRead();
 }

return readcolor;	
}
/*******************************************************************************
* 函数名  : 写入一个点颜色数据
* 描述    : 写入液晶屏上一个点颜色数据 ,坐标范围不超液晶分辨率
* 输入    : 设定写入坐标点的位置X Y 
* 输出    : None
* 返回    : None
*******************************************************************************/
void GUI_WritePoint(uint x,uint y,uint color)
{	
    LCD_SetCursor(x, y);
    LCD_WriteRAM_Prepare(); 
	 	if(MPU_Interface==2)
	{ 
	LCD_DataWrite(color);
	}
	else
	{
LCD_DataWrite(color&0x00ff);
LCD_DataWrite(color>>8);	
 }

}
/*******************************************************************************
* 函数名  : 显示空心圆
* 描述    : 在液晶屏上显示一个空心圆 ,坐标范围不超液晶分辨率
* 输入          : 设定空心圆圆心坐标 X Y 
*                 设定空心圆半径R
*                 
* 输出         : None
* 返回         : None
*******************************************************************************/

void GUI_Circle   (uint x,uint y,uint r)	  //显示空心圆
{
	Circle_Center_XY(x,y);		
		Circle_Radius_R(r);			
Start_Circle_or_Ellipse();	

}
/*******************************************************************************
* 函数名  : 显示实心圆
* 描述    : 在液晶屏上显示一个实心圆 ,坐标范围不超液晶分辨率
* 输入          : 设定实心圆圆心坐标 X Y
*                 设定实心圆半径R
*                 
* 输出         : None
* 返回         : None
*******************************************************************************/
void GUI_CircleFill (uint x,uint y,uint r)	  //显示实心圆
{
Circle_Center_XY(x,y);			
Circle_Radius_R(r);					
Start_Circle_or_Ellipse_Fill();	
}
/*******************************************************************************
* 函数名  : 显示空心椭圆
* 描述    : 在液晶屏上显示一个空心椭圆 ,坐标范围不超液晶分辨率
* 输入          : 设定空心椭圆圆心坐标 X Y 
*                 设定空心椭圆半径R1，半径R2
*                 
* 输出         : None
* 返回         : None
*******************************************************************************/
void GUI_Ellipse  (uint x,uint y,uint r1,uint r2)	  //显示空心椭圆
{
Circle_Center_XY(x,y);			
Ellipse_Radius_RxRy(r1, r2);
Start_Circle_or_Ellipse();
}
/*******************************************************************************
* 函数名  : 显示实心椭圆
* 描述    : 在液晶屏上显示一个实心椭圆
* 输入          : 设定实心椭圆圆心坐标 X Y ,坐标范围不超液晶分辨率
*                设置实心椭圆半径R1，半径R2
*                 
* 输出         : None
* 返回         : None
*******************************************************************************/
void GUI_EllipseFill  (uint x,uint y,uint r1,uint r2)	  //显示实心椭圆
{
Circle_Center_XY(x,y);			
Ellipse_Radius_RxRy(r1,r2);	
Start_Circle_or_Ellipse_Fill();	
}
/*******************************************************************************
* 函数名  : 显示空心三角形
* 描述    : 在液晶屏上显示一个实心三角形 ,坐标范围不超液晶分辨率
* 输入          : 设置空心三角形第一个点坐标X1 Y1
*               ：设置空心三角形第二个点坐标X2 Y2
*								：设置空心三角形第二个点坐标X3 Y3
*                 
* 输出         : None
* 返回         : None
*******************************************************************************/
void GUI_Triangle (uint x1,uint y1,uint x2,uint y2,uint x3,uint y3)	 //显示空心三角形
{
Triangle_Point1_XY(x1,y1);	
Triangle_Point2_XY(x2,y2);	
Triangle_Point3_XY(x3,y3);	
Start_Triangle();	
}
/*******************************************************************************
* 函数名  : 显示实心三角形
* 描述    : 在液晶屏上显示一个实心三角形 ,坐标范围不超液晶分辨率
* 输入          : 设置实心三角形第一个点坐标X1 Y1
*               ：设置实心三角形第二个点坐标X2 Y2
*								：设置实心三角形第二个点坐标X3 Y3
*                 
* 输出         : None
* 返回         : None
*******************************************************************************/
void GUI_Fill_Triangle (uint x1,uint y1,uint x2,uint y2,uint x3,uint y3)  //显示实心三角形
{
Triangle_Point1_XY(x1,y1);	
Triangle_Point2_XY(x2,y2);	
Triangle_Point3_XY(x3,y3);	
Start_Triangle_Fill();
}
/*******************************************************************************
* 函数名  : 显示空心矩形
* 描述    : 在液晶屏上显示一个空心矩形 ,坐标范围不超液晶分辨率
* 输入          : 设置空心矩形左上角第一个点坐标
*									设置矩形的长W和宽H
*                 
* 输出         : None
* 返回         : None
*******************************************************************************/
 void GUI_Rectangle (uint xs,uint ys,uint w,uint h)  //显示空心矩形
 {
	Line_Start_XY(xs,ys);
	Line_End_XY(xs+w-1,ys+h-1);
	Start_Square();	
}
/*******************************************************************************
* 函数名  : 显示实心矩形
* 描述    : 在液晶屏上显示一个实心矩形 ,坐标范围不超液晶分辨率
* 输入          : 设置实心矩形左上角第一个点坐标
*									设置矩形的长W和宽H
*                 
* 输出         : None
* 返回         : None
*******************************************************************************/
 void GUI_RectangleFill (uint xs,uint ys,uint w,uint h)   //显示实心矩形
 {
	Line_Start_XY(xs,ys);
	Line_End_XY(xs+w-1,ys+h-1);
	Start_Square_Fill();
}
/*******************************************************************************
* 函数名  : 显示空心圆角矩形
* 描述    : 在液晶屏上显示一个空心圆角矩形 ，坐标范围不超液晶分辨率
* 输入          : 设置显示空心圆角矩形左上角第一个点坐标
*									设置空心圆角矩形的长和宽
*                 设置圆角R ,R圆角不能少于长W或者宽H的一半
* 输出         : None
* 返回         : None
*******************************************************************************/
 void GUI_Rectangle_R (uint xs,uint ys,uint w,uint h,uint r)  //显示空心圆角矩形，r圆角不能少于w或者h的一半
 {
 		Line_Start_XY(xs,ys);
	Line_End_XY(xs+w-1,ys+h-1);
Ellipse_Radius_RxRy(r,r);
Start_Circle_Square();	
}
/*******************************************************************************
* 函数名  : 显示实心圆角矩形
* 描述    : 在液晶屏上显示一个空心圆角矩形 ，坐标范围不超液晶分辨率
* 输入          : 设置显示实心圆角矩形左上角第一个点坐标
*									设置实心圆角矩形的长和宽
*                 设置圆角R ,R圆角不能少于长W或者宽H的一半
* 输出         : None
* 返回         : None
*******************************************************************************/
 void GUI_RectangleFill_R  (uint xs,uint ys,uint w,uint h,uint r)  //显示实心圆角矩形，r圆角不能少于w或者h的一半
 {
 			Line_Start_XY(xs,ys);
Line_End_XY(xs+w-1,ys+h-1);
Ellipse_Radius_RxRy(r,r);
Start_Circle_Square_Fill();	
}
/*******************************************************************************
* 函数名  : 显直线
* 描述    : 在液晶屏上显示一条直线 ，坐标范围不超液晶分辨率
* 输入          : 设置直线的第一个点的坐标X1 Y1
*									设置直线的第二个点的坐标X2 Y2
*                
* 输出         : None
* 返回         : None
*******************************************************************************/
void GUI_Line(uint x1,uint y1,uint x2,uint y2)//显示直线
{
	Line_Start_XY(x1,y1);
	Line_End_XY(x2,y2);
	Start_Line();
}
/*******************************************************************************
* 函数名  : 显示128MB内的图片
* 描述    : 在液晶屏上显示一幅图片 ，坐标范围不超液晶分辨率
* 输入          :picnum为烧录到储存器里面的图片序号，好烧录软件左边列表对应，X,Y为在改位置显示的坐标             
* 输出         : None
* 返回         : None
*******************************************************************************/

 void Dis_Image_Mix_128Mb(uint picnum,uint x,uint y)	//128Mb储存器，显示图片到当前屏幕
 {
    ulong picx=0,picy=0,fadd=0;uchar buf3[12];
    FLASH_Read_128Mb(buf3, picnum*12, 12);
	
	   fadd=(ulong)buf3[0];
	   fadd=(fadd<<8)+buf3[1];
	   fadd=(fadd<<8)+buf3[2];
	   fadd=(fadd<<8)+buf3[3];


	   picx=(ulong)buf3[4];
	   picx=(picx<<8)+buf3[5];
	   picx=(picx<<8)+buf3[6];
	   picx=(picx<<8)+buf3[7];

	   picy=(ulong)buf3[8];
	   picy=(picy<<8)+buf3[9];
	   picy=(picy<<8)+buf3[10];
	   picy=(picy<<8)+buf3[11];

	 if((picx!=0)&(picy!=0)&(picnum<170))
	 {
 	 BTE_Destination_Color_16bpp();  
				Enable_SFlash_SPI();
    Select_SFI_0();
    Select_SFI_DMA_Mode();
    Select_SFI_24bit_Address();
		Select_SFI_Waveform_Mode_3();
		    Select_SFI_Dual_Mode0();
    SPI_Clock_Period(0);
Canvas_Image_Start_address(Layer2);
	
	SFI_DMA_Destination_Start_Address(Layer2);
Memory_XY_Mode(); 
	   SFI_DMA_Source_Width(picx); 
	   SFI_DMA_Transfer_Width_Height(picx,picy);
	   SFI_DMA_Destination_Upper_Left_Corner(x,y); 
	   SFI_DMA_Source_Start_Address(fadd);

 Start_SFI_DMA();
  Check_Busy_SFI_DMA();
 	 BTE_Destination_Color_16bpp();  
     BTE_Destination_Memory_Start_Address(Layer1);
     BTE_Destination_Image_Width(lcdx);
     BTE_Destination_Window_Start_XY(x,y);  
     BTE_Window_Size(picx,picy);

     BTE_S0_Color_16bpp();
     BTE_S0_Memory_Start_Address(Layer2);
     BTE_S0_Image_Width(lcdx);
     BTE_S0_Window_Start_XY(x,y);

	BTE_ROP_Code(12);
    BTE_Operation_Code(2); //BTE move  
	BTE_Enable(); Check_BTE_Busy();
	Canvas_Image_Start_address(Layer1);
}
	
 }
 /*******************************************************************************
* 函数名  : 显示128MB内的图片到制定图层
* 描述    : 在液晶屏上指定图层显示一幅图片， 坐标范围不超液晶分辨率
* 输入          :picnum为烧录到储存器里面的图片序号，好烧录软件左边列表对应，X,Y为在改位置显示的坐标 ，layer为指定的图层
* 输出         : None
* 返回         : None
*******************************************************************************/
void Dis_Image_Mix_128Mb_Layer(uint picnum,uint x,uint y,uint layer)	//128Mb储存器，显示图片到指定图层
 {
     ulong picx=0,picy=0,fadd=0;uchar buf3[12];
     FLASH_Read_128Mb(buf3, picnum*12, 12);
	
	   fadd=(ulong)buf3[0];
	   fadd=(fadd<<8)+buf3[1];
	   fadd=(fadd<<8)+buf3[2];
	   fadd=(fadd<<8)+buf3[3];


	   picx=(ulong)buf3[4];
	   picx=(picx<<8)+buf3[5];
	   picx=(picx<<8)+buf3[6];
	   picx=(picx<<8)+buf3[7];

	   picy=(ulong)buf3[8];
	   picy=(picy<<8)+buf3[9];
	   picy=(picy<<8)+buf3[10];
	   picy=(picy<<8)+buf3[11];

	 if((picx!=0)&(picy!=0)&(picnum<170))
	 {
 	 BTE_Destination_Color_16bpp();  
				Enable_SFlash_SPI();
    Select_SFI_0();
    Select_SFI_DMA_Mode();
    Select_SFI_24bit_Address();
		Select_SFI_Waveform_Mode_3();
		    Select_SFI_Dual_Mode0();
    SPI_Clock_Period(0);
Canvas_Image_Start_address(layer);
	
	SFI_DMA_Destination_Start_Address(layer);
Memory_XY_Mode(); 
	   SFI_DMA_Source_Width(picx); 
	   SFI_DMA_Transfer_Width_Height(picx,picy);
	   SFI_DMA_Destination_Upper_Left_Corner(x,y); 
	   SFI_DMA_Source_Start_Address(fadd);

 Start_SFI_DMA();
  Check_Busy_SFI_DMA();
 
	//Canvas_Image_Start_address(Layer1);
}
	
 }
/*******************************************************************************
* 函数名  : 显示1024MB内的图片
* 描述    : 在液晶屏上显示一幅图片
 * 输入          :picnum为烧录到储存器里面的图片序号，好烧录软件左边列表对应，X,Y为在改位置显示的坐标
* 输出         : None
* 返回         : None
*******************************************************************************/
  void Dis_Image_mix_1024Mb(uint picnum,uint x,uint y)	//1024Mb储存器，显示图片到当前屏幕
 {  uchar buf3[12]; 
ulong picx=0,picy=0,fadd=0;
FLASH_Read_1024GMb(buf3, picnum*12);
  
	   fadd=(ulong)buf3[0];
	   fadd=(fadd<<8)+buf3[1];
	   fadd=(fadd<<8)+buf3[2];
	   fadd=(fadd<<8)+buf3[3];


	   picx=(ulong)buf3[4];
	   picx=(picx<<8)+buf3[5];
	   picx=(picx<<8)+buf3[6];
	   picx=(picx<<8)+buf3[7];

	   picy=(ulong)buf3[8];
	   picy=(picy<<8)+buf3[9];
	   picy=(picy<<8)+buf3[10];
	   picy=(picy<<8)+buf3[11];

	   
		
 	 Select_SFI_0();
   	Enable_SFlash_SPI();
    
    Select_SFI_DMA_Mode();
    Select_SFI_24bit_Address();
Select_SFI_8_DummyRead();
 Memory_Linear_Mode();
Select_SFI_Waveform_Mode_3();
   Select_SFI_Dual_Mode0();

   SPI_Clock_Period(0);
   nSS_Active();
  SPI_Master_FIFO_Data_Put(0x13);
  SPI_Master_FIFO_Data_Put(0xff);
  SPI_Master_FIFO_Data_Put((fadd/2048)>>8);
  SPI_Master_FIFO_Data_Put(fadd/2048);
  nSS_Inactive();
  delay_ms(10);
SPI_Clock_Period(0);	 
	 
  SFI_DMA_Transfer_Number(picx*picy*2); 
SFI_DMA_Destination_Start_Address(lcdx*lcdy*2*4);

	  Start_SFI_DMA();
      Check_Busy_SFI_DMA();
 
	 BTE_Destination_Color_16bpp();  
     BTE_Destination_Memory_Start_Address(0);
     BTE_Destination_Image_Width(lcdx);
     BTE_Destination_Window_Start_XY(x,y);//x,y  
     BTE_Window_Size(picx,picy);

     BTE_S0_Color_16bpp();
     BTE_S0_Memory_Start_Address(lcdx*lcdy*2*4);
     BTE_S0_Image_Width(picx);
     BTE_S0_Window_Start_XY(0,0);//x,y

	BTE_ROP_Code(12);
    BTE_Operation_Code(2); //BTE move  
	BTE_Enable(); Check_BTE_Busy();
	Canvas_Image_Start_address(0);
    nSS_Inactive();
 }
  /*******************************************************************************
* 函数名  : 显示1024MB内的图片到制定图层
* 描述    : 在液晶屏上指定图层显示一幅图片
* 输入          :picnum为烧录到储存器里面的图片序号，好烧录软件左边列表对应，X,Y为在改位置显示的坐标 ，layer为指定的图层
* 输出         : None
* 返回         : None
*******************************************************************************/
   void Dis_Image_mix_1024Mb_Layer(uint picnum,uint x,uint y,uint layer)  	//1024Mb储存器，显示图片到指定图层
 {  uchar buf3[12]; 
ulong picx=0,picy=0,fadd=0;//uchar buf3[12];
FLASH_Read_1024GMb(buf3, picnum*12);
  
	   fadd=(ulong)buf3[0];
	   fadd=(fadd<<8)+buf3[1];
	   fadd=(fadd<<8)+buf3[2];
	   fadd=(fadd<<8)+buf3[3];


	   picx=(ulong)buf3[4];
	   picx=(picx<<8)+buf3[5];
	   picx=(picx<<8)+buf3[6];
	   picx=(picx<<8)+buf3[7];

	   picy=(ulong)buf3[8];
	   picy=(picy<<8)+buf3[9];
	   picy=(picy<<8)+buf3[10];
	   picy=(picy<<8)+buf3[11];

	   
		
 	 Select_SFI_0();
   	Enable_SFlash_SPI();
    
    Select_SFI_DMA_Mode();
    Select_SFI_24bit_Address();
Select_SFI_8_DummyRead();
 Memory_Linear_Mode();
Select_SFI_Waveform_Mode_3();
   Select_SFI_Dual_Mode0();

   SPI_Clock_Period(0);
   nSS_Active();
  SPI_Master_FIFO_Data_Put(0x13);
  SPI_Master_FIFO_Data_Put(0xff);
  SPI_Master_FIFO_Data_Put((fadd/2048)>>8);
  SPI_Master_FIFO_Data_Put(fadd/2048);
  nSS_Inactive();
  delay_ms(10);
SPI_Clock_Period(0);	 
	 
  SFI_DMA_Transfer_Number(picx*picy*2); 
SFI_DMA_Destination_Start_Address(layer);

	  Start_SFI_DMA();
      Check_Busy_SFI_DMA();
 
	Canvas_Image_Start_address(0);
 }
  /*******************************************************************************
* 函数名  : 根据不同的储存器容量，选择不同的显示图片函数
* 描述    : 在液晶屏上显示一幅图片 ,坐标范围不超液晶分辨率
**输入          :picnum为烧录到储存器里面的图片序号，好烧录软件左边列表对应，X,Y为在改位置显示的坐标 
* 输出         : None
* 返回         : None
*******************************************************************************/
 void Dis_Image_Mix(uint picnum,uint x,uint y)
 {
  if(FLASHTYPE==0)//容量为128Mb的液晶，显示液晶储存器内部的图片	
     Dis_Image_Mix_128Mb(picnum,x,y);	
	else if(FLASHTYPE==1)//容量为1024Mb的液晶，显示液晶储存器内部的图片		
     Dis_Image_mix_1024Mb(picnum,x,y);
 }
 
 /*******************************************************************************
* 函数名  : 显示1024MB内的图片到指定图层
* 描述    : 在液晶屏上指定图层显示一幅图片 ,坐标范围不超液晶分辨率
* 输入    ：picnum为烧录到储存器里面的图片序号，好烧录软件左边列表对应，X,Y为在改位置显示的坐标 ，layer为指定的图层出位置XY
* 输出         : None
* 返回         : None
*******************************************************************************/
    void Dis_Image_Mix_Layer(uint picnum,uint x,uint y,uint layer)
 {
  	if(FLASHTYPE==0)//容量为128Mb的液晶，显示液晶储存器内部的图片	
Dis_Image_Mix_128Mb_Layer(picnum,x,y,layer);	
	if(FLASHTYPE==1)//容量为1024Mb的液晶，显示液晶储存器内部的图片		
Dis_Image_mix_1024Mb_Layer(picnum,x,y,layer);
 }
/*******************************************************************************
* 函数名  : 初始化文字功能
* 描述    : 初始化文字功能
* 输入          : NONE

* 输出         : None
* 返回         : None
*******************************************************************************/
void cnconfig(void)
{
			Enable_SFlash_SPI();
    Select_SFI_1();
   
    Select_SFI_24bit_Address();
		Select_SFI_Waveform_Mode_3();
		    Select_SFI_Dual_Mode1();
    SPI_Clock_Period(0);	
	 }
/*******************************************************************************
* 函数名  : 显示文字
* 描述    : 在液晶屏上显示文字
* 输入          : 设置文字显示坐标位置X Y
*				 tongtou:设置文字字体是否通透
                 *str:显示的文字数据 
* 输出         : None
* 返回         : None
*******************************************************************************/
void Display_Text(uint x,uint y,uchar tongtou ,uchar *str)
{
	  Select_SFI_1();
      Select_SFI_Font_Mode();

      Select_SFI_Waveform_Mode_0();
      Select_SFI_0_DummyRead();
      Select_SFI_Single_Mode();
      SPI_Clock_Period(4);	 // Freq must setting <=20MHZ
	 GTFont_Select_GT23L32S4W_GT23H32S4W();
	Set_GTFont_Decoder(1);//有三种字符字体，请参考说明书
	  Enable_SFlash_SPI();
 Memory_XY_Mode(); 

	if(tongtou==0)
	Font_Background_select_Color();
	if(tongtou==1)
	Font_Background_select_Transparency();
	
	Goto_Text_XY(x,y);
	
  Show_String(str);	

}


/*******************************************************************************
* 函数名  : 显示文字
* 描述    : 在液晶屏上显示文字
* 输入          : 设置文字显示坐标位置X Y
*				 tongtou:设置文字字体是否通透
                 *str:显示的文字数据 
* 输出         : None
* 返回         : None
*******************************************************************************/
void Display_Text_Str(uint x,uint y,uchar tongtou ,uchar *str ,uint8_t len)
{

	uint8_t  *strt;
	
	 memcpy(strt, str, len /*sizeof(RxDataBuff)*/);	
	
	  Select_SFI_1();
      Select_SFI_Font_Mode();

      Select_SFI_Waveform_Mode_0();
      Select_SFI_0_DummyRead();
      Select_SFI_Single_Mode();
      SPI_Clock_Period(4);	 // Freq must setting <=20MHZ
	 GTFont_Select_GT23L32S4W_GT23H32S4W();
	Set_GTFont_Decoder(1);//有三种字符字体，请参考说明书
	  Enable_SFlash_SPI();
 Memory_XY_Mode(); 

	if(tongtou==0)
	Font_Background_select_Color();
	if(tongtou==1)
	Font_Background_select_Transparency();
	
	Goto_Text_XY(x,y);
		
  Show_String(strt);	

	memset(strt, 0, len);   //清0	
		
}



//显示数字
void Write_Number_43inchLCD(uint x,uint y,uchar tongtou ,uint8_t s )// 数字显示函数
{ 
		
   Display_Text_Str( x, y, tongtou ,num_43inchlcd+s,1 );	

}









/*******************************************************************************
* 函数名  : 设置字体
* 描述    : 设置字体
* 输入          : 1代表16点阵，2代表24点阵，3代表32点阵
*        				
* 输出         : None
* 返回         : None
*******************************************************************************/
void Set_Font(uchar font) //设置字体
{
switch (font)
 {
	 case 0x01:	 
       {
	   Font_Select_8x16_16x16();FONT=1;
       }
       break;
	 case 0x02:	 
       {
	   Font_Select_12x24_24x24();	FONT=2;
       }
       break;
	 case 0x03:	 
       {
	   Font_Select_16x32_32x32();FONT=3;
       }
       break;

}
}
/*******************************************************************************
* 函数名  : 设置文字间距
* 描述    : 设置文字间的间距
* 输入          : 设置文字间左右间距X
*									设置文字间上下间距Y
*        				
* 输出         : None
* 返回         : None
*******************************************************************************/
void Set_Font_Distance(uint x,uint y)//设置文字间距
{
Font_Line_Distance(x);	
Set_Font_to_Font_Width(y);	

}
/*******************************************************************************
* 函数名  : 指定屏幕位置反色显示
* 描述    : 在液晶指定位置反色显示
* 输入          : 设置左上角坐标X1 Y1
*									设置右下角坐标X2 Y2
*        				
* 输出         : None
* 返回         : None
*******************************************************************************/
 void inverse(uint xs,uint ys,uint xe,uint ye)//屏幕区域反显	
 {
   Memory_XY_Mode();
  	 BTE_Destination_Color_16bpp();  
     BTE_Destination_Memory_Start_Address(Layer1);
     BTE_Destination_Image_Width(lcdx);
     BTE_Destination_Window_Start_XY(xs,ys);  
     BTE_Window_Size(xe-xs,ye-ys);

     BTE_S0_Color_16bpp();
     BTE_S0_Memory_Start_Address(Layer1);
     BTE_S0_Image_Width(lcdx);
     BTE_S0_Window_Start_XY(xs,ys);

	   BTE_ROP_Code(3);
     BTE_Operation_Code(2); //BTE move  
	   BTE_Enable(); Check_BTE_Busy();
 }


/*******************************************************************************
* 函数名  : 设置液晶接口类型和液晶型号
* 描述    : 设置显示液晶接口和液晶型号
* 输入          : 设置液晶接口SPI 8BIT FSMC
*									设置液晶型号
*        				
* 输出         : None
* 返回         : None
*******************************************************************************/
void selectlcd_mode(void)//设置液晶接口类型和液晶型号
{
	LCDTYPE=VS48272M43_2;      //VS106000M101;//VS80480M70_2 ; //VS48272M43_2;
  MPU_Interface=LCD_SPI;
  FLASHTYPE=Flash_128Mb;     //Flash_1024Mb;	     Flash_128Mb
  
  LCD43inch_Init();
		
  LCD_Select(LCDTYPE);
		
	Boot_Display_43inch();

//	LCDTEST();
	
}
/*
显示自定义图片
x:X坐标地址
x:Y坐标地址
w:显示图片的宽度
h:显示图片的高度
numbers:显示图片的字节数
*datap：图片数组的指针
注意：推荐用“image2lcd”软件生成图片数组，数组格式是高位在前，RGB565格式
*/
void Draw_Picture(uint x,uint y,uint w,uint h,unsigned long numbers,const unsigned char *datap)
{	unsigned long i;   uint temp;
Graphic_Mode_8876();
	
	Active_Window_WH(w,h);
	Active_Window_XY(x,y);
	LCD_SetCursor(x, y);
LCD_WriteRAM_Prepare();

  for(i=0;i<numbers;)
   {
   if(MPU_Interface==2)
   {
   temp=(uint)datap[i];
   	temp=(temp<<8)+datap[i+1];
   
   LCD_DataWrite(temp);
   }
   else
   {
	LCD_DataWrite(datap[i+1]);
	LCD_DataWrite(datap[i]);
   }
// Check_Mem_WR_FIFO_not_Full(); //如果MCU速度比较快，要加上这个测满函数，一般72M的STM32，无论用什么接口，都不需要加这段。 
   i=i+2;
   }
   Active_Window_WH(lcdx,lcdy);Active_Window_XY(0,0);
}


void Disp_FloatNum(u8 mode,u32 x,u32 y,u8 fontsize,u8 w,double value,uchar *format,uint B_color,uint F_color ) //显示浮点数，客户可以根据自己的需求修改程序
{

	 uchar temp[10];
	  uint tempb,tempf;
	 tempf=Read_Foreground_color_65k();
	tempb= Read_Background_color_65k();
	 	  Select_SFI_1();
      Select_SFI_Font_Mode();

      Select_SFI_Waveform_Mode_0();
      Select_SFI_0_DummyRead();
      Select_SFI_Single_Mode();
      SPI_Clock_Period(4);	 // Freq must setting <=20MHZ
	 GTFont_Select_GT23L32S4W_GT23H32S4W();
	
	  Enable_SFlash_SPI();
 Memory_XY_Mode(); 	 
	Background_color_65k(B_color);
	if(mode==0)
	Font_Background_select_Color();
	if(mode==1)
	Font_Background_select_Transparency();
	
	if(fontsize==16)
 Font_Select_8x16_16x16();
	if(fontsize==24)
 Font_Select_12x24_24x24();
	if(fontsize==32)
 Font_Select_16x32_32x32();
 	

//printf((char*)temp,format,value);
Foreground_color_65k(B_color);
 GUI_RectangleFill(x,y,w,fontsize); 
Foreground_color_65k(F_color);
 Goto_Text_XY(x,y);
Show_String(temp);	
 Foreground_color_65k(tempf);
 Foreground_color_65k(tempb);




} 

 /*******************************************************************************
* 函数名  : 显示128MB储存器的图片
* 描述    : 以过滤色的方式在液晶屏上显示一幅图片 ，坐标范围不超液晶分辨率，改功能可以用于显示图标，按键等图片，显示非方形的图片
* 输入          :picnum为烧录到储存器里面的图片序号，好烧录软件左边列表对应，X,Y为在改位置显示的坐标 ，Filter_Color为过滤色            
* 输出         : None
* 返回         : None
*******************************************************************************/
void Dis_PicButton_128Mb(uint picnum,uint x,uint y,uint Filter_Color)	
 {
ulong picx=0,picy=0,fadd=0;uchar buf3[12];
uint temp_color=0x0000;
temp_color=Read_Background_color_65k();//保存目前背景色
FLASH_Read_128Mb(buf3, picnum*12, 12);
	
	   fadd=(ulong)buf3[0];
	   fadd=(fadd<<8)+buf3[1];
	   fadd=(fadd<<8)+buf3[2];
	   fadd=(fadd<<8)+buf3[3];


	   picx=(ulong)buf3[4];
	   picx=(picx<<8)+buf3[5];
	   picx=(picx<<8)+buf3[6];
	   picx=(picx<<8)+buf3[7];

	   picy=(ulong)buf3[8];
	   picy=(picy<<8)+buf3[9];
	   picy=(picy<<8)+buf3[10];
	   picy=(picy<<8)+buf3[11];

	 if((picx!=0)&(picy!=0)&(picnum<170))
	 {
 	 BTE_Destination_Color_16bpp();  
				Enable_SFlash_SPI();
    Select_SFI_0();
    Select_SFI_DMA_Mode();
    Select_SFI_24bit_Address();
		Select_SFI_Waveform_Mode_3();
		    Select_SFI_Dual_Mode0();
    SPI_Clock_Period(0);
Canvas_Image_Start_address(Layer2);
	
	SFI_DMA_Destination_Start_Address(Layer2);
Memory_XY_Mode(); 
	   SFI_DMA_Source_Width(picx); 
	   SFI_DMA_Transfer_Width_Height(picx,picy);
	   SFI_DMA_Destination_Upper_Left_Corner(x,y); 
	   SFI_DMA_Source_Start_Address(fadd);

 Start_SFI_DMA();
  Check_Busy_SFI_DMA();
 	 BTE_Destination_Color_16bpp();  
     BTE_Destination_Memory_Start_Address(Layer1);
     BTE_Destination_Image_Width(lcdx);
     BTE_Destination_Window_Start_XY(x,y);  
     BTE_Window_Size(picx,picy);

     BTE_S0_Color_16bpp();
     BTE_S0_Memory_Start_Address(Layer2);
     BTE_S0_Image_Width(lcdx);
     BTE_S0_Window_Start_XY(x,y);

	 BTE_S1_Color_16bpp();
     BTE_S1_Memory_Start_Address(Layer1);
     BTE_S1_Image_Width(lcdx);
     BTE_S1_Window_Start_XY(x,y);

    Background_color_65k(Filter_Color);
	BTE_ROP_Code(14);
    BTE_Operation_Code(5); //BTE move  
	BTE_Enable(); Check_BTE_Busy();
	Canvas_Image_Start_address(Layer1);
    Background_color_65k(temp_color);//将之前保存的背景色重新写进背景色寄存器
}
	
 }
 //选择不同的图层进行操作
 void Sel_Layer(unsigned long layer)
{

Canvas_Image_Start_address(layer);
}
  /*******************************************************************************
* 函数名  : 复制图层
* 描述    : 复制图层
* 输入          :slayer为源图层，dlayer为目标图层，sx,sy为源图层的左上角坐标，dx,dy为目标图层的左上角坐标，w,h为要复制区域的宽和高度           
* 输出         : None
* 返回         : None
*******************************************************************************/
  void Layer_Copy(unsigned long slayer,unsigned long dlayer,uint sx,uint sy,uint dx,uint dy,uint w,uint h)
 {


 	 BTE_Destination_Color_16bpp();  
     BTE_Destination_Memory_Start_Address(dlayer);
     BTE_Destination_Image_Width(lcdx);
     BTE_Destination_Window_Start_XY(dx,dy);  
     BTE_Window_Size(w,h);

     BTE_S0_Color_16bpp();
     BTE_S0_Memory_Start_Address(slayer);
     BTE_S0_Image_Width(lcdx);
     BTE_S0_Window_Start_XY(sx,sy);

	BTE_ROP_Code(12);
    BTE_Operation_Code(2); //BTE move  
	BTE_Enable(); Check_BTE_Busy();
	Canvas_Image_Start_address(Layer1);

	
 }
   /*******************************************************************************
* 函数名  : 画中画窗口1
* 描述    : 显示画中画窗口1
* 输入          :sx,sy为源图层的左上角坐标，dx,dy为目标图层的左上角坐标，w,h为要画中画的宽和高度           
* 输出         : None
* 返回         : None
*******************************************************************************/
void PIP1(unsigned long layer,uint dx,uint dy,uint sx,uint sy,uint w,uint h)
{ 
Select_PIP1_Parameter();
PIP_Image_Start_Address(layer);
PIP_Image_Width(lcdx);
PIP_Window_Image_Start_XY(sx,sy);
PIP_Window_Width_Height(w,h);
PIP_Display_Start_XY(dx,dy);
Enable_PIP1();
}
   /*******************************************************************************
* 函数名  : 画中画窗口2
* 描述    : 显示画中画窗口2
* 输入          :sx,sy为源图层的左上角坐标，dx,dy为目标图层的左上角坐标，w,h为要画中画的宽和高度           
* 输出         : None
* 返回         : None
*******************************************************************************/
void PIP2(unsigned long layer,uint dx,uint dy,uint sx,uint sy,uint w,uint h)
{ 
Select_PIP2_Parameter();
PIP_Image_Start_Address(layer);
PIP_Image_Width(lcdx);
PIP_Window_Image_Start_XY(sx,sy);
PIP_Window_Width_Height(w,h);
PIP_Display_Start_XY(dx,dy);
Enable_PIP2();
}



















void LCDTEST(void)//液晶复位
{
	
//uint i,j;double k;

Dis_Image_Mix(0,0,0);//显示液晶内部储存器的第1幅图片	
	
Display_ON();  //
	
delay_ms(100);//延时100ms后再开背光，能有效避免开机闪屏
	
Set_Backlight(100);	//开背光，100%亮度	
	
//Dis_PicButton_128Mb(1,50,50,0xffff);//以过滤色的方式显示图片，一般用于显示非长方形按钮，可过滤按钮边上的颜色，从而显示椭圆形或者不规则形状的按钮图片或图形

//delay_ms(1000);

//delay_ms(1000);
//GUI_CleanScreen();//清屏

//Dis_Image_Mix(2,0,0);//显示液晶内部储存器的第1幅图片	
//	
//delay_ms(1000);	
//delay_ms(1000);	
//GUI_CleanScreen();//清屏
//Dis_Image_Mix(3,0,0);//显示液晶内部储存器的第1幅图片	
//delay_ms(1000);
//delay_ms(1000);
//GUI_CleanScreen();//清屏
//Dis_Image_Mix(4,0,0);//显示液晶内部储存器的第1幅图片	
//delay_ms(1000);
//delay_ms(1000);

//GUI_CleanScreen();//清屏
//Dis_Image_Mix(0,0,0);//显示液晶内部储存器的第1幅图片	
//delay_ms(1000);
//delay_ms(1000);
	
//显示动画

//for(i=15;i>6;i--)
//{

//	Dis_Image_Mix(i,0,0);
//		
//	delay_ms(80);	

//}



//Set_Color(color_white,color_red);  //设置前景色和背景色

////Foreground_color_65k(color_red);	

//Set_Font(3);   //设置字体  1代表16点阵，2代表24点阵，3代表32点阵

//Display_Text(10,10,0,"广州科坦电子技术有限公司");

//Set_Font(2);	//设置字体

////Foreground_color_65k(color_black);	

//Display_Text(0,160,0,"广州科坦电子技术有限公司");

////Foreground_color_65k(color_cyan);

//Set_Font(1);//设置字体

//Display_Text(0,190,0,"广州科坦电子技术有限公司");




////显示进度条
//Dis_Image_Mix(1,0,0);

//for(i=0;i<380;)
//{ 
//	
// delay_ms(6);
// Dis_Image_Mix_128Mb_Layer(5,10,230,Layer2);    //将图片写在第二层显存
// Dis_Image_Mix_128Mb_Layer(6,10+i,230,Layer2);  //将图片写在第二层显存
// Layer_Copy(Layer2,Layer1,10,230,10,230,400,40);//将第二层显存复制到第一图层，避免闪动
// i=i+5;
//	
//}

////显示动画
//for(i=16;i<26;i++)
//{
//Dis_Image_Mix(i,500,0);delay_ms(80);	
//}
//for(i=25;i>15;i--)
//{
//Dis_Image_Mix(i,500,0);delay_ms(80);	
//}
////读取显存测试，用fsmc16位接口速度会比spi快很多
//for(i=0;i<240;i++)
//{
//for(j=0;j<136;j++)
//{	 
//   GUI_WritePoint(i+100,j+300,GUI_ReadPoint(i,j));
//	}
//}

//Sel_Layer(Layer2);//切换图层2

////Draw_Picture(470,200,320,240,153600,logo) ;	//显示自定义图片，图片的分辨率为320*240，每个点占用2个字节，图片数组大小为：320*240*2 
//Layer_Copy(Layer2,Layer1,470,200,470,200,320,240);//将图层2复制到图层1
//Sel_Layer(Layer1);//切换图层1

// delay_ms(1000);


////测试背光亮度
//Set_Backlight(10);	
//delay_ms(400);
//Set_Backlight(50);	
//delay_ms(400);
//Set_Backlight(100);	
//delay_ms(400);




////在多图层下测试RGB颜色
//Sel_Layer(Layer2); //切换图层2，写数据
//for(i=0;i<32;i++)
//{
//Set_Color(color_yellow,(uint)i<<11);
//GUI_RectangleFill (i*(lcdx/32),0,lcdx/32,lcdy/3);	
//Set_Color(color_yellow,(uint)i<<5);	
//GUI_RectangleFill (i*(lcdx/32),lcdy/3,lcdx/32,lcdy/3);
//Set_Color(color_yellow,i);	
//GUI_RectangleFill (i*(lcdx/32),lcdy/3*2,lcdx/32,lcdy-lcdy/3*2); 
//}
//Layer_Copy(Layer2,Layer1,0,0,0,0,lcdx,lcdy);//将图层2复制到图层1
//Sel_Layer(Layer1);//切换图层1显示
//delay_ms(1000);
////测试多边形显示速度
//Geometric_Drawing();
////测试画中画，多图层，图层复制功能
//Set_Font(1);
//Sel_Layer(Layer3);	
// Active_Window_XY(0,0);//write/draw
//Active_Window_WH(300,150);Set_Color(0x3333,color_white);	
//GUI_CleanScreen();	

//Display_Text(0,0,0,"                      画中画（PIP）功能简介                 该功能演示的是画中画功能(PIP),利用控制器强大的显存操作和多图层显示功能，可以实现出画中画。显示画面分开上下层，下层图像可以随时更新，该功能适用于多种菜单、提示等操作。");

//Sel_Layer(Layer1);	
//for(i=0;i<6;i++)
//{
//PIP1(Layer3,500-i*50,i*50,0,0,300,150);
//delay_ms(500);
//Disable_PIP1();
//}
// Active_Window_XY(0,0);	//恢复参数
//Active_Window_WH(lcdx,lcdy);
////测试显示浮点数值
//Set_GTFont_Decoder(1);//设置数字字体


//k=-23.56;		
//Disp_FloatNum(0,100,200,32,100,k, "%3.2f",0xffff,0xf800 );DelayMS_sys(500);
//k=78.12;
//Disp_FloatNum(0,100,200,32,100,k ,"%3.2f",0xffff,0xf800);DelayMS_sys(500);
//k=2.7;
//Disp_FloatNum(0,100,200,32,100,k ,"%3.2f",0xffff,0xf800);	DelayMS_sys(500);
//k=-52.7;
//Disp_FloatNum(0,100,200,32,100,k ,"%3.2f",0xffff,0xf800);DelayMS_sys(500);
//k=5.98;
//Disp_FloatNum(0,100,200,32,100,k ,"%3.2f",0xffff,0xf800);	DelayMS_sys(500);


}





















