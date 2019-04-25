#include "LCDdef.h"
#include "sys.h"


void Set_Backlight(uchar bl);//设置背光亮度
void GUI_CleanScreen(void);//用颜色清屏
void Set_Color(uint bc,uint fc);  //设置颜色
void GUI_Point(uint x,uint y);  //显示一个点
void GUI_Circle   (uint x,uint y,uint r);	  //显示空心圆
void GUI_CircleFill (uint x,uint y,uint r);	  //显示实心圆
void GUI_Ellipse  (uint x,uint y,uint r1,uint r2);	  //显示空心椭圆
void GUI_EllipseFill  (uint x,uint y,uint r1,uint r2);	  //显示实心椭圆，功能07
void GUI_Triangle (uint x1,uint y1,uint x2,uint y2,uint x3,uint y3);	 //显示空心三角形，功能08
void GUI_Fill_Triangle (uint x1,uint y1,uint x2,uint y2,uint x3,uint y3);  //显示实心三角形，功能09
void GUI_Rectangle (uint xs,uint ys,uint w,uint h);  //显示空心矩形，功能10
void GUI_RectangleFill (uint xs,uint ys,uint w,uint h) ;  //显示实心矩形，功能11
void GUI_Rectangle_R (uint xs,uint ys,uint w,uint h,uint r);  //显示空心圆角矩形，功能12
void GUI_RectangleFill_R  (uint xs,uint ys,uint w,uint h,uint r);  //显示实心圆角矩形
void GUI_Line(uint x1,uint y1,uint x2,uint y2);//显示直线	 
void Dis_Image_Mix_1024Mb(uint picnum,uint x,uint y);	
void Dis_Image_Mix_128Mb(uint picnum,uint x,uint y);	
void Dis_Image_Mix(uint picnum,uint x,uint y);	
void Draw_Picture(uint x,uint y,uint w,uint h,unsigned long numbers,const unsigned char *datap);
void Disp_FloatNum(u8 mode,u32 x,u32 y,u8 fontsize,u8 w,double value,uchar *format,uint B_color,uint F_color ); //显示浮点数，客户可以根据自己的需求修改程序

void selectlcd_mode(void);
void Set_Backlight(uchar bl);
void Set_Color(uint bc,uint fc);
void cnconfig(void);
void Display_Text(uint x,uint y,uchar tongtou ,uchar *str);
void GUI_Point(uint x,uint y);
void Set_Font_Distance(uint x,uint y);


void Set_Font(uchar font);
void sentvalue(uchar tm);
void inverse(uint xs,uint ys,uint xe,uint ye);

void  Nandflash_Config(void);


void STMFLASH_Read(u32 ReadAddr,u16 *pBuffer,u16 NumToRead);
void STMFLASH_Write_NoCheck(u32 WriteAddr,u16 *pBuffer,u16 NumToWrite) ;  
void Geometric_Drawing(void);
void W25N01_Set_BUF(void);
void W25N01_Reset(void);
void W25N01_Clear_BUF(void);
void GUI_WritePoint(uint x,uint y,uint color);
uint GUI_ReadPoint(uint x,uint y);



void Display_Text_Str(uint x,uint y,uchar tongtou ,uchar *str ,uint8_t len);

void Write_Number_43inchLCD(uint x,uint y,uchar tongtou ,uint8_t s );// 数字显示函数

extern u8  num_43inchlcd[];
