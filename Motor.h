/*
 * =============================================================
 *
 *       Filename:  Motor.c
 *
 *    Description:  电机驱动h文件   通过L298N驱动电机
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
#ifndef __MOTOR_H__            //头文件防重载定义
#define __MOTOR_H__

#define uchar	unsigned char  //数据类型定义
#define	uint	unsigned int

void      Delay_10Us(uint us);      //us级延时
void      DelayMs(uint ms);		    //毫秒级延时
void      Init_Motor(void);	        //电机计时器（T0）初始化函数
void      Timer0_ISR(void);         //PWM波中断函数
void      Stop(uchar speed_left,uchar speed_right);
void      GoHead(uchar speed_left,uchar speed_right);
void      GoBack(uchar speed_left,uchar speed_right);
void      Goright_90(int delaytime);
																		    
uchar Sensor(Sensor1,Sensor2,Sensor3,Sensor4,Sensor5);	//传感器识别函数***

#endif