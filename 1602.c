/*
 * =============================================================
 *
 *       Filename:  1602.c
 *
 *    Description:  Һ����ʾc�ļ�
 *
 *        Version:  1.0.1
 *        Created:  2015.5.13
 *       Revision:  first
 *       Compiler:  Keil ��Vision 4
 *
 *         Author:  ���Ӣ������
 *	        Email:  513814330@qq.com
 *	           QQ:  513814330
 * =============================================================
 */
 #include	"1602.h"
 #include	"Timer.h"
 #include	<reg52.h>
/*********************************************
                  �궨��
**********************************************/
#define DataPort P2	 //8λ���ݿڣ�Ӳ����
#define Busy 0x80    //æ���DB7
/*********************************************
                ����λ����
**********************************************/
sbit RS=P0^5;        //�Ĵ���ѡ������ˣ�Ӳ����
sbit RW=P0^6;        //��д��������ˣ�Ӳ����
sbit E =P0^7;        //ʹ���ź�����ˣ�Ӳ����

/*********************************************
         �ڲ��������壨���ɱ��ⲿ�ļ����ã�
**********************************************/
void  Lcd_delay(uint t);
uchar Wait_for_busy(void);
void  Lcd_write_CMD(uchar cmd);
void  Lcd_write_DAT(uchar dat);
void  Set_X_Y(uchar x,uchar y);

/*********************************************
�������ƣ� Lcd_delay
�������ܣ� LCDר����ʱ��������ʱʱ�䣺t����
�������룺 t-��ʱʱ����Ʊ���
��������� ��
**********************************************/
void Lcd_delay(uint t)
{
	unsigned int i,j;
	for( i = 0; i < t; i ++ )
		for( j = 115; j > 0; j --);
}

/*********************************************
�������ƣ� Lcd_write_CMD
�������ܣ� 1602д����
�������룺 �������
��������� ��
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
�������ƣ� Lcd_write_DAT
�������ܣ� 1602д����
�������룺 ��ʾ����
��������� ��
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
�������ƣ� Wait_for_busy
�������ܣ� �ȴ�1602æ��
�������룺 ��
��������� 0��ʾ�ɹ� 1��ʾ��ʱ
**********************************************/
uchar Wait_for_busy(void)
{
	uchar times=10;//��ೢ��10��
	DataPort=0xFF;//��ȫ������ �ȴ�����
	RS=0;
	RW=1;
	do
	{
	E=1;
	Lcd_delay(3);	
	E=0;
	Lcd_delay(3);
	times--;
	}while((times>0)&&(DataPort&Busy==0x80));//�������λΪ1 ��ʾæ
	if (times) return 0;
	else return 1;
}
/*********************************************
�������ƣ� Init_1602
�������ܣ� LCD1602��ʼ��
�������룺 ��
��������� ��
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
�������ƣ� Set_X_Y
�������ܣ� ���ù��X Y��ֵ
�������룺 �����x�� y��
��������� ��
**********************************************/
void Set_X_Y(uchar x,uchar y)
{
	uchar temp;												  
	if(x>1)x=1;     //����ֻ����0��1
	if(y>15)y=15;   //����ֻ����0~15
	temp=x*0x40+y;
	Lcd_write_CMD(temp|0x80);
}
/*********************************************
�������ƣ� Write_char
�������ܣ� ��X Y�����һ���̶��ַ�
�������룺 �����x�� y�� ����ַ�c
��������� ��
**********************************************/
void Write_char(uchar x,uchar y,uchar c)
{
	Set_X_Y(x,y);
	Lcd_write_DAT(c);
}
/*********************************************
�������ƣ� Write_str
�������ܣ� ��X Y�����һ���ַ���
�������룺 �����x�� y�� ����ַ���ָ��c �ַ������� l 
��������� ��
**********************************************/
void Write_str(uchar x,uchar y,char *c,uchar l)
{
	uchar i;
	Set_X_Y(x,y);
	for(i=0;i<l;i++)
	Lcd_write_DAT(c[i]);
}
/*********************************************
�������ƣ� Display_Time
�������ܣ� ��ʾʱ��
�������룺 �����x�� 0��
��������� ��
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
