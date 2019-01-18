/*
 * =============================================================
 *
 *       Filename:  main.c
 *
 *    Description:  机器人大赛调试-普罗米修斯
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

#define X 1

/*********************************************
                  头文件
**********************************************/
#include	<reg52.h>
#include    <intrins.h>
#include	"Motor.h"	//电机
#include	"1602.h"	//显示器
#include	"Timer.h"	//计时器
#include    "Buzzer.h"	//蜂鸣器
/*********************************************
                  宏定义
**********************************************/
#define uchar	unsigned char
#define	uint	unsigned int
/*********************************************
                引脚位定义
**********************************************/
//---------- ST188 ------------//
sbit 	Sensor1  = P0^0;	  //传感器1
sbit	Sensor2  = P0^1;	  //传感器2
sbit	Sensor3  = P0^2;	  //传感器3
sbit	Sensor4  = P0^3;	  //传感器4
sbit	Sensor5  = P0^4;	  //传感器5

/*********************************************
                变量定义
**********************************************/
uchar   road_status;             //循迹变量（道路检测状态）

void    RoadTrack(road_status);	 //循迹函数
void  RoadTrack_1(road_status);
void    Init_main(void);	     //初始化函数

/*********************************************
函数名称： Init_main
函数功能： 初始化汇总
函数输入： 无 
函数输出： 无
**********************************************/
void  Init_main(void)
{
	Init_1602();
	Init_Timer();
	Init_Motor();
}

/*********************************************
函数名称： RoadTrack
函数功能： 道路检测循迹
函数输入： road_status-道路检测状态 
函数输出： 无
**********************************************/
void  RoadTrack(road_status)
{
	switch (road_status)
	{
		case 0x04:	GoHead(44*X,44*X);	break;	            //前进
		case 0x00:  GoBack(30*X,30*X);  DelayMs(20);break;  //直线后退

		case 0x06:	GoHead(25*X,40*X);	break;	            //小左转1
		case 0x02:	GoHead(17*X,40*X);	break;	            //小左转2
		case 0x03:	GoHead(35*X,55*X);	break;	            //大左转1
		case 0x01:	GoHead(17*X,55*X);	break;	            //大左转2
		
		case 0x0C:	GoHead(39*X,25*X);	break;              //小右转1
		case 0x08:	GoHead(39*X,17*X);	break;              //小右转2
		case 0x18:	GoHead(56*X,25*X);	break;              //大右转1	
		case 0x10:	GoHead(56*X,17*X);	break;              //大右转2
		
		case 0x05:  Goright_90(300); break;				
		default:break; 
	}
}

/*********************************************
函数名称： RoadTrack_1
函数功能： 道路检测循迹
函数输入： road_status-道路检测状态 
函数输出： 无
**********************************************/
void  RoadTrack_1(road_status)
{
	switch (road_status)
	{
		case 0x04:	GoBack(44*X,44*X);	break;	            //前进
		case 0x00:  GoHead(30*X,30*X);  DelayMs(20);break;  //直线后退

		case 0x06:	GoBack(40*X,25*X);	break;	            //小左转1
		case 0x02:	GoBack(40*X,17*X);	break;	            //小左转2
		case 0x03:	GoBack(55*X,35*X);	break;	            //大左转1
		case 0x01:	GoBack(55*X,17*X);	break;	            //大左转2
		
		case 0x0C:	GoBack(25*X,39*X);	break;              //小右转1
		case 0x08:	GoBack(17*X,39*X);	break;              //小右转2
		case 0x18:	GoBack(25*X,56*X);	break;              //大右转1	
		case 0x10:	GoBack(17*X,56*X);	break;              //大右转2
		
		case 0x05:  GoBack(44*X,44*X);  break;				
		default:break; 
	}
}

/********************************************
函数名称： main
函数功能： 整个程序的入口
函数输入： 无
函数输出： 无
**********************************************/
void main(void)
{ 
	int Black_FLAG;     //全黑计数标志
	Black_FLAG=0;       //全黑标志清零
	Init_main();
	Stop(30,30);
	Write_str(0,3,"Prometheus",10);	  //显示组名
	while(1)
	{
		if (Sensor1==1 && Sensor2==1 && Sensor3==1 && Sensor4==1 && Sensor5==1) Black_FLAG++;
		if (Black_FLAG==5) break;
		road_status = Sensor(Sensor1,Sensor2,Sensor3,Sensor4,Sensor5);
		RoadTrack(road_status);
	    DelayMs(100);
		Display_Time(1);
	}
	while(1)
	{
		if (Sensor1==1 && Sensor2==1 && Sensor3==1 && Sensor4==1 && Sensor5==1) Black_FLAG++;
		if (Black_FLAG==7) break;
		road_status = Sensor(Sensor1,Sensor2,Sensor3,Sensor4,Sensor5);
		RoadTrack_1(road_status);
	    DelayMs(100);
		Display_Time(1);
	}
	while(1)
	{
		if (Sensor1==1 && Sensor2==1 && Sensor3==1 && Sensor4==1 && Sensor5==1) Black_FLAG++;
		if (Black_FLAG==9) break;
		road_status = Sensor(Sensor1,Sensor2,Sensor3,Sensor4,Sensor5);
		RoadTrack(road_status);
	    DelayMs(100);
		Display_Time(1);
	}
	Display_Time(1);
	while(1)
	{
		GoHead(0,0);
		DelayMs(300);
	}
}
