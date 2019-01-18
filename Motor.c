/*
 * =============================================================
 *
 *       Filename:  Motor.c
 *
 *    Description:  电机驱动c文件  通过L298N驱动电机
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
 /*********************************************
                包含头文件
**********************************************/ 
#include	"motor.h"
#include	<reg52.h>
#include    <intrins.h>
/*********************************************
                引脚位定义
**********************************************/ 
//---------- L298N ------------//
sbit 	RIGHT_IN1 =	P1^3;	  //右边电机 信号1
sbit	RIGHT_EN  =	P1^4;     //右边电机 使能
sbit	RIGHT_IN2 =	P1^5;     //右边电机 信号2
						   
sbit 	LEFT_IN1 =	P1^2;     //左边电机 信号1
sbit	LEFT_EN  =	P1^1;	  //左边电机 使能
sbit	LEFT_IN2 =	P1^0;	  //左边电机 信号2

//---------- ST188 ------------//
sbit 	Sensor1  = P0^0;	  //传感器1
sbit	Sensor2  = P0^1;	  //传感器2
sbit	Sensor3  = P0^2;	  //传感器3
sbit	Sensor4  = P0^3;	  //传感器4
sbit	Sensor5  = P0^4;	  //传感器5

/*********************************************
                  宏定义
**********************************************/
#define PWM_PERIOD  100       //PWM周期最大值 PWM_PERIOD*100us
#define STR_FIX 1.2           //直线修正 表示左边比右边快多少倍（走直线时左拐则改大 右拐则改小）

/*********************************************
                变量定义
**********************************************/
//---------- PWM ------------//
uchar	PWM_COUNTER = 0;      //pwm产生周期 100*100us
uchar	LEFT_PWM_DUTY  = 50;  //左边电机占空比
uchar	RIGHT_PWM_DUTY = 50;  //右边电机占空比

/*********************************************
函数名称： Delay_10Us
函数功能： us延时函数
函数输入： us-延时时间控制变量
函数输出： 无
**********************************************/
void Delay_10Us(uint us)
{
	while( us-- );
}

/*********************************************
函数名称： DelayMs
函数功能： ms级延时函数，延时时间：ms*ms
函数输入： ms-延时时间控制变量
函数输出： 无
**********************************************/
void DelayMs(uint ms)
{
	unsigned int i,j;
	for( i = 0; i < ms; i ++ )
		for( j = 115; j > 0; j --);
}

/*********************************************
函数名称： Init_Motor
函数功能： 初始化单片机的定时0(用于产生PWM)
函数输入： 无
函数输出： 无
**********************************************/
void Init_Motor(void)
{
   TMOD = (TMOD&0xF0)|0x02;       //设定T0的工作模式为2
   //----装入定时器初值 -----//
   TH0 = 0x95;                    //100us定时 用于占空比控制
   TL0 = 0x95;	

   ET0 = 1;                       // 定时器0允许中断 
   TR0 = 1;                       // 启动定时器0 
   EA  = 1;                       // 开总中断 
}

/*********************************************
函数名称： Timer0_ISR
函数功能： 定时器0中断服务函数,用于输出PWM波
函数输入： 无
函数输出： 无
**********************************************/
void Timer0_ISR(void) interrupt	1 using 1
{
	PWM_COUNTER ++;
	if(PWM_COUNTER < PWM_PERIOD)
	{
		if(PWM_COUNTER > LEFT_PWM_DUTY)	 LEFT_EN  = 0;
		if(PWM_COUNTER > RIGHT_PWM_DUTY) RIGHT_EN = 0;
	}
	else 
	{
		PWM_COUNTER = 0;	
		LEFT_EN  = 1;
		RIGHT_EN = 1;
	}
}

/*********************************************
函数名称： Stop
函数功能： 停车函数
函数输入： speed_left -左轮占空比
           speed_right-右轮占空比
函数输出： 无
**********************************************/
void Stop(uchar speed_left,uchar speed_right)
{
	LEFT_IN1  = 0;
	LEFT_IN2  = 0;

	RIGHT_IN1 =	0;
	RIGHT_IN2 =	0;
	LEFT_PWM_DUTY  = speed_left;
	RIGHT_PWM_DUTY = speed_right;
}

/*********************************************
函数名称： GoHead
函数功能： 前进函数：控制小车以一定速度直线前进，也可以
           控制小车转弯
函数输入： speed_left -左轮占空比
           speed_right-右轮占空比
函数输出： 无
**********************************************/
void GoHead(uchar speed_left,uchar speed_right)
{
	LEFT_IN1  = 0;
	LEFT_IN2  = 1;

	RIGHT_IN1 =	0;
	RIGHT_IN2 =	1;
	LEFT_PWM_DUTY  = (uchar)(speed_left*STR_FIX); //直线修正
	RIGHT_PWM_DUTY = speed_right;
}

/*********************************************
函数名称： GoBack
函数功能： 后退函数：控制小车以一定速度直线后退，也可以
           小车后退转弯
函数输入： speed_left -左轮占空比
           speed_right-右轮占空比
函数输出： 无
**********************************************/
void GoBack(uchar speed_left,uchar speed_right)
{
	LEFT_IN1  = 1;
	LEFT_IN2  =	0;
	RIGHT_IN1 =	1;
	RIGHT_IN2 =	0;
	LEFT_PWM_DUTY  = (uchar)(speed_left*STR_FIX); //直线修正
	RIGHT_PWM_DUTY = speed_right;
}
/*********************************************
函数名称： Goright
函数功能： 右转90度函数：控制小车以一定速度旋转90度
函数输入： speed_left -左轮占空比
           speed_right-右轮占空比
函数输出： 无
**********************************************/
void Goright_90(int delaytime)
{
	LEFT_IN1  = 0;
	LEFT_IN2  = 1;

	RIGHT_IN1 =	1;
	RIGHT_IN2 =	0;
	LEFT_PWM_DUTY  = 26*2;
	RIGHT_PWM_DUTY = 26;
	DelayMs(delaytime);
}
/*********************************************
函数名称： Goleft_180
函数功能： 转180度函数：控制小车以一定速度从左旋转180度
函数输入： speed_left -左轮占空比
           speed_right-右轮占空比
函数输出： 无
**********************************************/
void Goleft_180(int delaytime)
{
	LEFT_IN1  = 1;
	LEFT_IN2  = 0;
	RIGHT_IN1 =	0;
	RIGHT_IN2 =	1;
	LEFT_PWM_DUTY  = 26-20;
	RIGHT_PWM_DUTY = 26;
	DelayMs(delaytime);
}
/**********************************************
函数名称： Sensor
函数功能： 传感器识别，根据传感器传入数据，返回一个
		   循迹变量
函数输入： sbit 	 Sensor1  = P0^0	  //传感器1
           sbit		 Sensor2  = P0^1	  //传感器2
		   sbit		 Sensor3  = P0^2	  //传感器3
		   sbit		 Sensor4  = P0^3	  //传感器4
		   sbit		 Sensor5  = P0^4	  //传感器5
函数输出： uchar     road_status		  //循迹变量
**********************************************/
uchar Sensor(Sensor1,Sensor2,Sensor3,Sensor4,Sensor5)
{
	if((Sensor1==0 && Sensor2==0 && Sensor3==1 && Sensor4==0 && Sensor5==0)||(Sensor1==0 && Sensor2==1 && Sensor3==1 && Sensor4==1 && Sensor5==0)||(Sensor1==1 && Sensor2==1 && Sensor3==1 && Sensor4==1 && Sensor5==1)) return 0x04;
	if( Sensor1==0 && Sensor2==0 && Sensor3==0 && Sensor4==0 && Sensor5==0) return 0x00;

	if((Sensor1==0 && Sensor2==1 && Sensor3==1 && Sensor4==0 && Sensor5==0)||(Sensor1==1 && Sensor2==1 && Sensor3==1 && Sensor4==1 && Sensor5==0)) return 0x06;
	if((Sensor1==0 && Sensor2==1 && Sensor3==0 && Sensor4==0 && Sensor5==0)||(Sensor1==1 && Sensor2==1 && Sensor3==1 && Sensor4==0 && Sensor5==0)) return 0x02;
	if( Sensor1==1 && Sensor2==1 && Sensor3==0 && Sensor4==0 && Sensor5==0) return 0x03;
	if( Sensor1==1 && Sensor2==0 && Sensor3==0 && Sensor4==0 && Sensor5==0) return 0x01;

	if((Sensor1==0 && Sensor2==0 && Sensor3==1 && Sensor4==1 && Sensor5==0)) return 0x0C;
	if((Sensor1==0 && Sensor2==0 && Sensor3==0 && Sensor4==1 && Sensor5==0)) return 0x08;
	if( Sensor1==0 && Sensor2==0 && Sensor3==0 && Sensor4==1 && Sensor5==1) return 0x18;
	if( Sensor1==0 && Sensor2==0 && Sensor3==0 && Sensor4==0 && Sensor5==1) return 0x10;

	if((Sensor1==0 && Sensor2==0 && Sensor3==1 && Sensor4==1 && Sensor5==1)||(Sensor1==0 && Sensor2==1 && Sensor3==1 && Sensor4==1 && Sensor5==1)) return 0x05;
}