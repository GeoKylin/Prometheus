/*
 * =============================================================
 *
 *       Filename:  Timer.h
 *
 *    Description:  计时器h文件  通过51自带计时器T1记录运行时间
 *
 *        Version:  1.0.1
 *        Created:  2015.5.13
 *       Revision:  first
 *       Compiler:  Keil μVision 4
 *
 *         Author:  杨君英、王锴
 *	        Email:  513814330@qq.com
 *	           QQ:  513814330
 *
 * =============================================================
 */
#ifndef __TIMER_H__            //头文件防重载定义
#define __TIMER_H__

#define uchar	unsigned char  //数据类型定义
#define	uint	unsigned int
 //---------- 时钟变量 ------------//
 extern uchar SecondL;         //时间秒低位
 extern uchar SecondH;         //时间秒高位
 extern uchar MinuteL;         //时间分低位
 extern uchar MinuteH;         //时间分高位

 void Init_Timer(void);        //计时器初始化
 void Timer1_ISR();            //计时器中断响应

#endif