/*
 * =============================================================
 *
 *       Filename:  1602.h
 *
 *    Description:  Һ����ʾh�ļ�
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
#ifndef __1602_H__             //ͷ�ļ������ض���
#define __1602_H__

#define uchar	unsigned char  //�������Ͷ���
#define	uint	unsigned int

void Init_1602(void);
void Set_X_Y(uchar x,uchar y);
void Write_char(uchar x,uchar y,uchar c);
void Write_str(uchar x,uchar y,char *c,uchar l);
void Display_Time(uchar x);

#endif