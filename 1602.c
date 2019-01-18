/*
 * =============================================================
 *
 *       Filename:  1602.c
 *
 *    Description:  液晶显示c文件
 *
 *        Version:  1.0.1
 *        Created:  2015.5.13
 *       Revision:  first
 *       Compiler:  Keil μVision 4
 *
 *         Author:  杨君英、王锴
 *	        Email:  513814330@qq.com
 *	           QQ:  513814330
 * =============================================================
 */
 #include	"1602.h"
 #include	"Timer.h"
 #include	<reg52.h>
/*********************************************
                  宏定义
**********************************************/
#define DataPort P2	 //8位数据口（硬件）
#define Busy 0x80    //忙检测DB7
/*********************************************
                引脚位定义
**********************************************/
sbit RS=P0^5;        //寄存器选择输入端（硬件）
sbit RW=P0^6;        //读写控制输入端（硬件）
sbit E =P0^7;        //使能信号输入端（硬件）

/*********************************************
         内部函数定义（不可被外部文件引用）
**********************************************/
void  Lcd_delay(uint t);
uchar Wait_for_busy(void);
void  Lcd_write_CMD(uchar cmd);
void  Lcd_write_DAT(uchar dat);
void  Set_X_Y(uchar x,uchar y);

/*********************************************
函数名称： Lcd_delay
函数功能： LCD专用延时函数，延时时间：t毫秒
函数输入： t-延时时间控制变量
函数输出： 无
**********************************************/
void Lcd_delay(uint t)
{
	unsigned int i,j;
	for( i = 0; i < t; i ++ )
		for( j = 115; j > 0; j --);
}

/*********************************************
函数名称： Lcd_write_CMD
函数功能： 1602写命令
函数输入： 命令代码
函数输出： 无
**********************************************/
void Lcd_write_CMD(uchar cmd)
{
	RS=0;
	RW=0;
	E=1;
	DataPort=cmd;
	Lcd_delay(1);
	E=0;
}
/*********************************************
函数名称： Lcd_write_DAT
函数功能： 1602写数据
函数输入： 显示数据
函数输出： 无
**********************************************/
void Lcd_write_DAT(uchar dat)
{
	RS=1;
	RW=0;
	E=1;
	DataPort=dat;
	Lcd_delay(1);
	E=0;
}
/*********************************************
函数名称： Wait_for_busy
函数功能： 等待1602忙完
函数输入： 无
函数输出： 0表示成功 1表示超时
**********************************************/
uchar Wait_for_busy(void)
{
	uchar times=10;//最多尝试10次
	DataPort=0xFF;//先全部拉低 等待数据
	RS=0;
	RW=1;
	do
	{
	E=1;
	Lcd_delay(3);	
	E=0;
	Lcd_delay(3);
	times--;
	}while((times>0)&&(DataPort&Busy==0x80));//数据最高位为1 表示忙
	if (times) return 0;
	else return 1;
}
/*********************************************
函数名称： Init_1602
函数功能： LCD1602初始化
函数输入： 无
函数输出： 无
**********************************************/
void Init_1602(void)
{
	Lcd_delay(15);
	Wait_for_busy();
	Lcd_write_CMD(0x38);
	Lcd_delay(5);
	Wait_for_busy();
	Lcd_write_CMD(0x38);
	Lcd_delay(1);
	Wait_for_busy();
	Lcd_write_CMD(0x38);
	Wait_for_busy();
	Lcd_write_CMD(0x08);
	Lcd_delay(10);
	Wait_for_busy();
	Lcd_write_CMD(0x01);
	Lcd_delay(10);
	Wait_for_busy();
	Lcd_write_CMD(0x06);
	Lcd_delay(10);
	Wait_for_busy();
	Lcd_write_CMD(0x0c);
	Lcd_delay(10);
}
/*********************************************
函数名称： Set_X_Y
函数功能： 设置光标X Y的值
函数输入： 光标在x行 y列
函数输出： 无
**********************************************/
void Set_X_Y(uchar x,uchar y)
{
	uchar temp;												  
	if(x>1)x=1;     //行数只能是0或1
	if(y>15)y=15;   //列数只能是0~15
	temp=x*0x40+y;
	Lcd_write_CMD(temp|0x80);
}
/*********************************************
函数名称： Write_char
函数功能： 在X Y处输出一个固定字符
函数输入： 光标在x行 y列 输出字符c
函数输出： 无
**********************************************/
void Write_char(uchar x,uchar y,uchar c)
{
	Set_X_Y(x,y);
	Lcd_write_DAT(c);
}
/*********************************************
函数名称： Write_str
函数功能： 在X Y处输出一个字符串
函数输入： 光标在x行 y列 输出字符串指针c 字符串长度 l 
函数输出： 无
**********************************************/
void Write_str(uchar x,uchar y,char *c,uchar l)
{
	uchar i;
	Set_X_Y(x,y);
	for(i=0;i<l;i++)
	Lcd_write_DAT(c[i]);
}
/*********************************************
函数名称： Display_Time
函数功能： 显示时间
函数输入： 光标在x行 0列
函数输出： 无
**********************************************/
void Display_Time(uchar x)
{
	Set_X_Y(x,0);
	Lcd_write_DAT('T');
	Lcd_write_DAT('i');
	Lcd_write_DAT('m');
	Lcd_write_DAT('e');
	Lcd_write_DAT(' ');
	Lcd_write_DAT(MinuteH+0x30);
	Lcd_write_DAT(MinuteL+0x30);
	Lcd_write_DAT(':');
	Lcd_write_DAT(SecondH+0x30);
	Lcd_write_DAT(SecondL+0x30);
}
