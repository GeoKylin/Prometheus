/*
 * =============================================================
 *
 *       Filename:  Buzzer.h
 *
 *    Description:  蜂鸣器h文件  通过蜂鸣器发声
 *
 *        Version:  1.0.1
 *        Created:  2015.5.13
 *       Revision:  frist
 *       Compiler:  Keil μVision 4
 *
 *         Author:  杨君英、王锴
 *	        Email:  513814330@qq.com
 *	           QQ:  513814330
 *
 * =============================================================
 */
#ifndef __BUZZER_H__           //头文件防重载定义
#define __BUZZER_H__

#define  uchar	unsigned char  //数据类型定义
#define	 uint	unsigned int
 //---------- 蜂鸣器变量 ------------//
sbit  BUZZER = P3^0;           //蜂鸣器（暂未用）

void  Buzzer(uchar delay_x);   //蜂鸣器函数（低电平发声）

#endif 