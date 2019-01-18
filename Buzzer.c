 /*
 * =============================================================
 *
 *       Filename:  Buzzer.c
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

/*********************************************
                  头文件
**********************************************/
#include  <reg52.h>
#include  <intrins.h>
#include  "Buzzer.h"
#include  "motor.h"
/********************************************
函数名称： Buzzer
函数功能： 蜂鸣器发声delay_x*Ms，低电平发声
函数输入： delay_x-蜂鸣器发声周期控制变量
函数输出： 无
**********************************************/
void Buzzer(uchar delay_x)
{
    Stop(0,0);
	BUZZER = 0;
	DelayMs(delay_x);
	BUZZER = 1;
	GoHead(20,21);
}
