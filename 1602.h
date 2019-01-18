/*
 * =============================================================
 *
 *       Filename:  1602.h
 *
 *    Description:  液晶显示h文件
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
#ifndef __1602_H__             //头文件防重载定义
#define __1602_H__

#define uchar	unsigned char  //数据类型定义
#define	uint	unsigned int

void Init_1602(void);
void Set_X_Y(uchar x,uchar y);
void Write_char(uchar x,uchar y,uchar c);
void Write_str(uchar x,uchar y,char *c,uchar l);
void Display_Time(uchar x);

#endif