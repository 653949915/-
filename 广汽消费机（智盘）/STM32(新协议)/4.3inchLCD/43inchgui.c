

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
* ������  : ���ñ�������
* ����    : ����Һ����������
* ����          : �趨�������� ��Χ0~100           
* ���         : None
* ����         : None
*******************************************************************************/
 void Set_Backlight(uchar bl) //���ñ������ȣ���Χ0~100
{
Set_PWM_Prescaler_1_to_256(1);
Select_PWM0_Clock_Divided_By_1();
Select_PWM0();								
Set_Timer0_Count_Buffer(6000); 
Set_Timer0_Compare_Buffer(bl*60);
Start_PWM0();  							
}

void GUI_CleanScreen(void) //�ñ���ɫ����
{
  Foreground_color_65k(Bcolor);//
	Line_Start_XY(0,0);
	Line_End_XY(lcdx-1,lcdy-1);
	Start_Square_Fill();
	Foreground_color_65k(Fcolor);	
}
/*******************************************************************************
* ������  : ����ǰ��ɫ�ͱ���ɫ
* ����    : ����Һ��ǰ��ɫ�ͱ���ɫ
* ����    : ����ǰ��ɫBC ����ɫFC                  
* ���    : ǰ��ɫFcolor ����ɫBcolor
* ����    : None
*******************************************************************************/
void Set_Color(uint bc,uint fc)//����bcΪ����ɫ��fcΪǰ��ɫ
{
Foreground_color_65k(fc);
Background_color_65k(bc);	
Bcolor=bc,Fcolor=fc;
}

/*******************************************************************************
* ������  : ��ǰ��ɫ��ʾһ����
* ����    : ��Һ��������ʾһ���� ,���귶Χ����Һ���ֱ���
* ����    : �趨�������λ��X Y                                
* ���    : None
* ����    : None
*******************************************************************************/
void GUI_Point(uint x,uint y)//��һ�㣬x��yΪ����ֵ
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
* ������  : ��ȡһ������ɫ����
* ����    : ��ȡҺ������һ�������ɫ���� ,���귶Χ����Һ���ֱ���
* ����          : �趨��ȡ������λ��X Y 
* ���         : None
* ����         :  ��ɫ����
*******************************************************************************/
uint GUI_ReadPoint(uint x,uint y)//��һ�㣬x��yΪ����ֵ
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
* ������  : д��һ������ɫ����
* ����    : д��Һ������һ������ɫ���� ,���귶Χ����Һ���ֱ���
* ����    : �趨д��������λ��X Y 
* ���    : None
* ����    : None
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
* ������  : ��ʾ����Բ
* ����    : ��Һ��������ʾһ������Բ ,���귶Χ����Һ���ֱ���
* ����          : �趨����ԲԲ������ X Y 
*                 �趨����Բ�뾶R
*                 
* ���         : None
* ����         : None
*******************************************************************************/

void GUI_Circle   (uint x,uint y,uint r)	  //��ʾ����Բ
{
	Circle_Center_XY(x,y);		
		Circle_Radius_R(r);			
Start_Circle_or_Ellipse();	

}
/*******************************************************************************
* ������  : ��ʾʵ��Բ
* ����    : ��Һ��������ʾһ��ʵ��Բ ,���귶Χ����Һ���ֱ���
* ����          : �趨ʵ��ԲԲ������ X Y
*                 �趨ʵ��Բ�뾶R
*                 
* ���         : None
* ����         : None
*******************************************************************************/
void GUI_CircleFill (uint x,uint y,uint r)	  //��ʾʵ��Բ
{
Circle_Center_XY(x,y);			
Circle_Radius_R(r);					
Start_Circle_or_Ellipse_Fill();	
}
/*******************************************************************************
* ������  : ��ʾ������Բ
* ����    : ��Һ��������ʾһ��������Բ ,���귶Χ����Һ���ֱ���
* ����          : �趨������ԲԲ������ X Y 
*                 �趨������Բ�뾶R1���뾶R2
*                 
* ���         : None
* ����         : None
*******************************************************************************/
void GUI_Ellipse  (uint x,uint y,uint r1,uint r2)	  //��ʾ������Բ
{
Circle_Center_XY(x,y);			
Ellipse_Radius_RxRy(r1, r2);
Start_Circle_or_Ellipse();
}
/*******************************************************************************
* ������  : ��ʾʵ����Բ
* ����    : ��Һ��������ʾһ��ʵ����Բ
* ����          : �趨ʵ����ԲԲ������ X Y ,���귶Χ����Һ���ֱ���
*                ����ʵ����Բ�뾶R1���뾶R2
*                 
* ���         : None
* ����         : None
*******************************************************************************/
void GUI_EllipseFill  (uint x,uint y,uint r1,uint r2)	  //��ʾʵ����Բ
{
Circle_Center_XY(x,y);			
Ellipse_Radius_RxRy(r1,r2);	
Start_Circle_or_Ellipse_Fill();	
}
/*******************************************************************************
* ������  : ��ʾ����������
* ����    : ��Һ��������ʾһ��ʵ�������� ,���귶Χ����Һ���ֱ���
* ����          : ���ÿ��������ε�һ��������X1 Y1
*               �����ÿ��������εڶ���������X2 Y2
*								�����ÿ��������εڶ���������X3 Y3
*                 
* ���         : None
* ����         : None
*******************************************************************************/
void GUI_Triangle (uint x1,uint y1,uint x2,uint y2,uint x3,uint y3)	 //��ʾ����������
{
Triangle_Point1_XY(x1,y1);	
Triangle_Point2_XY(x2,y2);	
Triangle_Point3_XY(x3,y3);	
Start_Triangle();	
}
/*******************************************************************************
* ������  : ��ʾʵ��������
* ����    : ��Һ��������ʾһ��ʵ�������� ,���귶Χ����Һ���ֱ���
* ����          : ����ʵ�������ε�һ��������X1 Y1
*               ������ʵ�������εڶ���������X2 Y2
*								������ʵ�������εڶ���������X3 Y3
*                 
* ���         : None
* ����         : None
*******************************************************************************/
void GUI_Fill_Triangle (uint x1,uint y1,uint x2,uint y2,uint x3,uint y3)  //��ʾʵ��������
{
Triangle_Point1_XY(x1,y1);	
Triangle_Point2_XY(x2,y2);	
Triangle_Point3_XY(x3,y3);	
Start_Triangle_Fill();
}
/*******************************************************************************
* ������  : ��ʾ���ľ���
* ����    : ��Һ��������ʾһ�����ľ��� ,���귶Χ����Һ���ֱ���
* ����          : ���ÿ��ľ������Ͻǵ�һ��������
*									���þ��εĳ�W�Ϳ�H
*                 
* ���         : None
* ����         : None
*******************************************************************************/
 void GUI_Rectangle (uint xs,uint ys,uint w,uint h)  //��ʾ���ľ���
 {
	Line_Start_XY(xs,ys);
	Line_End_XY(xs+w-1,ys+h-1);
	Start_Square();	
}
/*******************************************************************************
* ������  : ��ʾʵ�ľ���
* ����    : ��Һ��������ʾһ��ʵ�ľ��� ,���귶Χ����Һ���ֱ���
* ����          : ����ʵ�ľ������Ͻǵ�һ��������
*									���þ��εĳ�W�Ϳ�H
*                 
* ���         : None
* ����         : None
*******************************************************************************/
 void GUI_RectangleFill (uint xs,uint ys,uint w,uint h)   //��ʾʵ�ľ���
 {
	Line_Start_XY(xs,ys);
	Line_End_XY(xs+w-1,ys+h-1);
	Start_Square_Fill();
}
/*******************************************************************************
* ������  : ��ʾ����Բ�Ǿ���
* ����    : ��Һ��������ʾһ������Բ�Ǿ��� �����귶Χ����Һ���ֱ���
* ����          : ������ʾ����Բ�Ǿ������Ͻǵ�һ��������
*									���ÿ���Բ�Ǿ��εĳ��Ϳ�
*                 ����Բ��R ,RԲ�ǲ������ڳ�W���߿�H��һ��
* ���         : None
* ����         : None
*******************************************************************************/
 void GUI_Rectangle_R (uint xs,uint ys,uint w,uint h,uint r)  //��ʾ����Բ�Ǿ��Σ�rԲ�ǲ�������w����h��һ��
 {
 		Line_Start_XY(xs,ys);
	Line_End_XY(xs+w-1,ys+h-1);
Ellipse_Radius_RxRy(r,r);
Start_Circle_Square();	
}
/*******************************************************************************
* ������  : ��ʾʵ��Բ�Ǿ���
* ����    : ��Һ��������ʾһ������Բ�Ǿ��� �����귶Χ����Һ���ֱ���
* ����          : ������ʾʵ��Բ�Ǿ������Ͻǵ�һ��������
*									����ʵ��Բ�Ǿ��εĳ��Ϳ�
*                 ����Բ��R ,RԲ�ǲ������ڳ�W���߿�H��һ��
* ���         : None
* ����         : None
*******************************************************************************/
 void GUI_RectangleFill_R  (uint xs,uint ys,uint w,uint h,uint r)  //��ʾʵ��Բ�Ǿ��Σ�rԲ�ǲ�������w����h��һ��
 {
 			Line_Start_XY(xs,ys);
Line_End_XY(xs+w-1,ys+h-1);
Ellipse_Radius_RxRy(r,r);
Start_Circle_Square_Fill();	
}
/*******************************************************************************
* ������  : ��ֱ��
* ����    : ��Һ��������ʾһ��ֱ�� �����귶Χ����Һ���ֱ���
* ����          : ����ֱ�ߵĵ�һ���������X1 Y1
*									����ֱ�ߵĵڶ����������X2 Y2
*                
* ���         : None
* ����         : None
*******************************************************************************/
void GUI_Line(uint x1,uint y1,uint x2,uint y2)//��ʾֱ��
{
	Line_Start_XY(x1,y1);
	Line_End_XY(x2,y2);
	Start_Line();
}
/*******************************************************************************
* ������  : ��ʾ128MB�ڵ�ͼƬ
* ����    : ��Һ��������ʾһ��ͼƬ �����귶Χ����Һ���ֱ���
* ����          :picnumΪ��¼�������������ͼƬ��ţ�����¼�������б��Ӧ��X,YΪ�ڸ�λ����ʾ������             
* ���         : None
* ����         : None
*******************************************************************************/

 void Dis_Image_Mix_128Mb(uint picnum,uint x,uint y)	//128Mb����������ʾͼƬ����ǰ��Ļ
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
* ������  : ��ʾ128MB�ڵ�ͼƬ���ƶ�ͼ��
* ����    : ��Һ������ָ��ͼ����ʾһ��ͼƬ�� ���귶Χ����Һ���ֱ���
* ����          :picnumΪ��¼�������������ͼƬ��ţ�����¼�������б��Ӧ��X,YΪ�ڸ�λ����ʾ������ ��layerΪָ����ͼ��
* ���         : None
* ����         : None
*******************************************************************************/
void Dis_Image_Mix_128Mb_Layer(uint picnum,uint x,uint y,uint layer)	//128Mb����������ʾͼƬ��ָ��ͼ��
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
* ������  : ��ʾ1024MB�ڵ�ͼƬ
* ����    : ��Һ��������ʾһ��ͼƬ
 * ����          :picnumΪ��¼�������������ͼƬ��ţ�����¼�������б��Ӧ��X,YΪ�ڸ�λ����ʾ������
* ���         : None
* ����         : None
*******************************************************************************/
  void Dis_Image_mix_1024Mb(uint picnum,uint x,uint y)	//1024Mb����������ʾͼƬ����ǰ��Ļ
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
* ������  : ��ʾ1024MB�ڵ�ͼƬ���ƶ�ͼ��
* ����    : ��Һ������ָ��ͼ����ʾһ��ͼƬ
* ����          :picnumΪ��¼�������������ͼƬ��ţ�����¼�������б��Ӧ��X,YΪ�ڸ�λ����ʾ������ ��layerΪָ����ͼ��
* ���         : None
* ����         : None
*******************************************************************************/
   void Dis_Image_mix_1024Mb_Layer(uint picnum,uint x,uint y,uint layer)  	//1024Mb����������ʾͼƬ��ָ��ͼ��
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
* ������  : ���ݲ�ͬ�Ĵ�����������ѡ��ͬ����ʾͼƬ����
* ����    : ��Һ��������ʾһ��ͼƬ ,���귶Χ����Һ���ֱ���
**����          :picnumΪ��¼�������������ͼƬ��ţ�����¼�������б��Ӧ��X,YΪ�ڸ�λ����ʾ������ 
* ���         : None
* ����         : None
*******************************************************************************/
 void Dis_Image_Mix(uint picnum,uint x,uint y)
 {
  if(FLASHTYPE==0)//����Ϊ128Mb��Һ������ʾҺ���������ڲ���ͼƬ	
     Dis_Image_Mix_128Mb(picnum,x,y);	
	else if(FLASHTYPE==1)//����Ϊ1024Mb��Һ������ʾҺ���������ڲ���ͼƬ		
     Dis_Image_mix_1024Mb(picnum,x,y);
 }
 
 /*******************************************************************************
* ������  : ��ʾ1024MB�ڵ�ͼƬ��ָ��ͼ��
* ����    : ��Һ������ָ��ͼ����ʾһ��ͼƬ ,���귶Χ����Һ���ֱ���
* ����    ��picnumΪ��¼�������������ͼƬ��ţ�����¼�������б��Ӧ��X,YΪ�ڸ�λ����ʾ������ ��layerΪָ����ͼ���λ��X�YY
* ���         : None
* ����         : None
*******************************************************************************/
    void Dis_Image_Mix_Layer(uint picnum,uint x,uint y,uint layer)
 {
  	if(FLASHTYPE==0)//����Ϊ128Mb��Һ������ʾҺ���������ڲ���ͼƬ	
Dis_Image_Mix_128Mb_Layer(picnum,x,y,layer);	
	if(FLASHTYPE==1)//����Ϊ1024Mb��Һ������ʾҺ���������ڲ���ͼƬ		
Dis_Image_mix_1024Mb_Layer(picnum,x,y,layer);
 }
/*******************************************************************************
* ������  : ��ʼ�����ֹ���
* ����    : ��ʼ�����ֹ���
* ����          : NONE

* ���         : None
* ����         : None
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
* ������  : ��ʾ����
* ����    : ��Һ��������ʾ����
* ����          : ����������ʾ����λ��X Y
*				 tongtou:�������������Ƿ�ͨ͸
                 *str:��ʾ���������� 
* ���         : None
* ����         : None
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
	Set_GTFont_Decoder(1);//�������ַ����壬��ο�˵����
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
* ������  : ��ʾ����
* ����    : ��Һ��������ʾ����
* ����          : ����������ʾ����λ��X Y
*				 tongtou:�������������Ƿ�ͨ͸
                 *str:��ʾ���������� 
* ���         : None
* ����         : None
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
	Set_GTFont_Decoder(1);//�������ַ����壬��ο�˵����
	  Enable_SFlash_SPI();
 Memory_XY_Mode(); 

	if(tongtou==0)
	Font_Background_select_Color();
	if(tongtou==1)
	Font_Background_select_Transparency();
	
	Goto_Text_XY(x,y);
		
  Show_String(strt);	

	memset(strt, 0, len);   //��0	
		
}



//��ʾ����
void Write_Number_43inchLCD(uint x,uint y,uchar tongtou ,uint8_t s )// ������ʾ����
{ 
		
   Display_Text_Str( x, y, tongtou ,num_43inchlcd+s,1 );	

}









/*******************************************************************************
* ������  : ��������
* ����    : ��������
* ����          : 1����16����2����24����3����32����
*        				
* ���         : None
* ����         : None
*******************************************************************************/
void Set_Font(uchar font) //��������
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
* ������  : �������ּ��
* ����    : �������ּ�ļ��
* ����          : �������ּ����Ҽ��X
*									�������ּ����¼��Y
*        				
* ���         : None
* ����         : None
*******************************************************************************/
void Set_Font_Distance(uint x,uint y)//�������ּ��
{
Font_Line_Distance(x);	
Set_Font_to_Font_Width(y);	

}
/*******************************************************************************
* ������  : ָ����Ļλ�÷�ɫ��ʾ
* ����    : ��Һ��ָ��λ�÷�ɫ��ʾ
* ����          : �������Ͻ�����X1 Y1
*									�������½�����X2 Y2
*        				
* ���         : None
* ����         : None
*******************************************************************************/
 void inverse(uint xs,uint ys,uint xe,uint ye)//��Ļ������	
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
* ������  : ����Һ���ӿ����ͺ�Һ���ͺ�
* ����    : ������ʾҺ���ӿں�Һ���ͺ�
* ����          : ����Һ���ӿ�SPI 8BIT FSMC
*									����Һ���ͺ�
*        				
* ���         : None
* ����         : None
*******************************************************************************/
void selectlcd_mode(void)//����Һ���ӿ����ͺ�Һ���ͺ�
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
��ʾ�Զ���ͼƬ
x:X�����ַ
x:Y�����ַ
w:��ʾͼƬ�Ŀ��
h:��ʾͼƬ�ĸ߶�
numbers:��ʾͼƬ���ֽ���
*datap��ͼƬ�����ָ��
ע�⣺�Ƽ��á�image2lcd���������ͼƬ���飬�����ʽ�Ǹ�λ��ǰ��RGB565��ʽ
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
// Check_Mem_WR_FIFO_not_Full(); //���MCU�ٶȱȽϿ죬Ҫ�����������������һ��72M��STM32��������ʲô�ӿڣ�������Ҫ����Ρ� 
   i=i+2;
   }
   Active_Window_WH(lcdx,lcdy);Active_Window_XY(0,0);
}


void Disp_FloatNum(u8 mode,u32 x,u32 y,u8 fontsize,u8 w,double value,uchar *format,uint B_color,uint F_color ) //��ʾ���������ͻ����Ը����Լ��������޸ĳ���
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
* ������  : ��ʾ128MB��������ͼƬ
* ����    : �Թ���ɫ�ķ�ʽ��Һ��������ʾһ��ͼƬ �����귶Χ����Һ���ֱ��ʣ��Ĺ��ܿ���������ʾͼ�꣬������ͼƬ����ʾ�Ƿ��ε�ͼƬ
* ����          :picnumΪ��¼�������������ͼƬ��ţ�����¼�������б��Ӧ��X,YΪ�ڸ�λ����ʾ������ ��Filter_ColorΪ����ɫ            
* ���         : None
* ����         : None
*******************************************************************************/
void Dis_PicButton_128Mb(uint picnum,uint x,uint y,uint Filter_Color)	
 {
ulong picx=0,picy=0,fadd=0;uchar buf3[12];
uint temp_color=0x0000;
temp_color=Read_Background_color_65k();//����Ŀǰ����ɫ
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
    Background_color_65k(temp_color);//��֮ǰ����ı���ɫ����д������ɫ�Ĵ���
}
	
 }
 //ѡ��ͬ��ͼ����в���
 void Sel_Layer(unsigned long layer)
{

Canvas_Image_Start_address(layer);
}
  /*******************************************************************************
* ������  : ����ͼ��
* ����    : ����ͼ��
* ����          :slayerΪԴͼ�㣬dlayerΪĿ��ͼ�㣬sx,syΪԴͼ������Ͻ����꣬dx,dyΪĿ��ͼ������Ͻ����꣬w,hΪҪ��������Ŀ�͸߶�           
* ���         : None
* ����         : None
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
* ������  : ���л�����1
* ����    : ��ʾ���л�����1
* ����          :sx,syΪԴͼ������Ͻ����꣬dx,dyΪĿ��ͼ������Ͻ����꣬w,hΪҪ���л��Ŀ�͸߶�           
* ���         : None
* ����         : None
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
* ������  : ���л�����2
* ����    : ��ʾ���л�����2
* ����          :sx,syΪԴͼ������Ͻ����꣬dx,dyΪĿ��ͼ������Ͻ����꣬w,hΪҪ���л��Ŀ�͸߶�           
* ���         : None
* ����         : None
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



















void LCDTEST(void)//Һ����λ
{
	
//uint i,j;double k;

Dis_Image_Mix(0,0,0);//��ʾҺ���ڲ��������ĵ�1��ͼƬ	
	
Display_ON();  //
	
delay_ms(100);//��ʱ100ms���ٿ����⣬����Ч���⿪������
	
Set_Backlight(100);	//�����⣬100%����	
	
//Dis_PicButton_128Mb(1,50,50,0xffff);//�Թ���ɫ�ķ�ʽ��ʾͼƬ��һ��������ʾ�ǳ����ΰ�ť���ɹ��˰�ť���ϵ���ɫ���Ӷ���ʾ��Բ�λ��߲�������״�İ�ťͼƬ��ͼ��

//delay_ms(1000);

//delay_ms(1000);
//GUI_CleanScreen();//����

//Dis_Image_Mix(2,0,0);//��ʾҺ���ڲ��������ĵ�1��ͼƬ	
//	
//delay_ms(1000);	
//delay_ms(1000);	
//GUI_CleanScreen();//����
//Dis_Image_Mix(3,0,0);//��ʾҺ���ڲ��������ĵ�1��ͼƬ	
//delay_ms(1000);
//delay_ms(1000);
//GUI_CleanScreen();//����
//Dis_Image_Mix(4,0,0);//��ʾҺ���ڲ��������ĵ�1��ͼƬ	
//delay_ms(1000);
//delay_ms(1000);

//GUI_CleanScreen();//����
//Dis_Image_Mix(0,0,0);//��ʾҺ���ڲ��������ĵ�1��ͼƬ	
//delay_ms(1000);
//delay_ms(1000);
	
//��ʾ����

//for(i=15;i>6;i--)
//{

//	Dis_Image_Mix(i,0,0);
//		
//	delay_ms(80);	

//}



//Set_Color(color_white,color_red);  //����ǰ��ɫ�ͱ���ɫ

////Foreground_color_65k(color_red);	

//Set_Font(3);   //��������  1����16����2����24����3����32����

//Display_Text(10,10,0,"���ݿ�̹���Ӽ������޹�˾");

//Set_Font(2);	//��������

////Foreground_color_65k(color_black);	

//Display_Text(0,160,0,"���ݿ�̹���Ӽ������޹�˾");

////Foreground_color_65k(color_cyan);

//Set_Font(1);//��������

//Display_Text(0,190,0,"���ݿ�̹���Ӽ������޹�˾");




////��ʾ������
//Dis_Image_Mix(1,0,0);

//for(i=0;i<380;)
//{ 
//	
// delay_ms(6);
// Dis_Image_Mix_128Mb_Layer(5,10,230,Layer2);    //��ͼƬд�ڵڶ����Դ�
// Dis_Image_Mix_128Mb_Layer(6,10+i,230,Layer2);  //��ͼƬд�ڵڶ����Դ�
// Layer_Copy(Layer2,Layer1,10,230,10,230,400,40);//���ڶ����Դ渴�Ƶ���һͼ�㣬��������
// i=i+5;
//	
//}

////��ʾ����
//for(i=16;i<26;i++)
//{
//Dis_Image_Mix(i,500,0);delay_ms(80);	
//}
//for(i=25;i>15;i--)
//{
//Dis_Image_Mix(i,500,0);delay_ms(80);	
//}
////��ȡ�Դ���ԣ���fsmc16λ�ӿ��ٶȻ��spi��ܶ�
//for(i=0;i<240;i++)
//{
//for(j=0;j<136;j++)
//{	 
//   GUI_WritePoint(i+100,j+300,GUI_ReadPoint(i,j));
//	}
//}

//Sel_Layer(Layer2);//�л�ͼ��2

////Draw_Picture(470,200,320,240,153600,logo) ;	//��ʾ�Զ���ͼƬ��ͼƬ�ķֱ���Ϊ320*240��ÿ����ռ��2���ֽڣ�ͼƬ�����СΪ��320*240*2 
//Layer_Copy(Layer2,Layer1,470,200,470,200,320,240);//��ͼ��2���Ƶ�ͼ��1
//Sel_Layer(Layer1);//�л�ͼ��1

// delay_ms(1000);


////���Ա�������
//Set_Backlight(10);	
//delay_ms(400);
//Set_Backlight(50);	
//delay_ms(400);
//Set_Backlight(100);	
//delay_ms(400);




////�ڶ�ͼ���²���RGB��ɫ
//Sel_Layer(Layer2); //�л�ͼ��2��д����
//for(i=0;i<32;i++)
//{
//Set_Color(color_yellow,(uint)i<<11);
//GUI_RectangleFill (i*(lcdx/32),0,lcdx/32,lcdy/3);	
//Set_Color(color_yellow,(uint)i<<5);	
//GUI_RectangleFill (i*(lcdx/32),lcdy/3,lcdx/32,lcdy/3);
//Set_Color(color_yellow,i);	
//GUI_RectangleFill (i*(lcdx/32),lcdy/3*2,lcdx/32,lcdy-lcdy/3*2); 
//}
//Layer_Copy(Layer2,Layer1,0,0,0,0,lcdx,lcdy);//��ͼ��2���Ƶ�ͼ��1
//Sel_Layer(Layer1);//�л�ͼ��1��ʾ
//delay_ms(1000);
////���Զ������ʾ�ٶ�
//Geometric_Drawing();
////���Ի��л�����ͼ�㣬ͼ�㸴�ƹ���
//Set_Font(1);
//Sel_Layer(Layer3);	
// Active_Window_XY(0,0);//write/draw
//Active_Window_WH(300,150);Set_Color(0x3333,color_white);	
//GUI_CleanScreen();	

//Display_Text(0,0,0,"                      ���л���PIP�����ܼ��                 �ù�����ʾ���ǻ��л�����(PIP),���ÿ�����ǿ����Դ�����Ͷ�ͼ����ʾ���ܣ�����ʵ�ֳ����л�����ʾ����ֿ����²㣬�²�ͼ�������ʱ���£��ù��������ڶ��ֲ˵�����ʾ�Ȳ�����");

//Sel_Layer(Layer1);	
//for(i=0;i<6;i++)
//{
//PIP1(Layer3,500-i*50,i*50,0,0,300,150);
//delay_ms(500);
//Disable_PIP1();
//}
// Active_Window_XY(0,0);	//�ָ�����
//Active_Window_WH(lcdx,lcdy);
////������ʾ������ֵ
//Set_GTFont_Decoder(1);//������������


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





















