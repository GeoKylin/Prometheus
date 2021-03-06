/*
 * =============================================================
 *
 *       Filename:  Timer.c
 *
 *    Description:  计时器c文件  通过51自带计时器T1记录运行时间
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
#include	"Timer.h"
#include	<reg52.h>
#include    <intrins.h>

uchar SecondL = 0;         //时间秒低位
uchar SecondH = 0;         //时间秒高位
uchar MinuteL = 0;         //时间分低位
uchar MinuteH = 0;         //时间分高位
/*********************************************
函数名称： Init_Timer
函数功能： 初始化单片机的定时1(用于记录运行时间)
函数输入： 无
函数输出： 无
**********************************************/
void Init_Timer(void)
{
   TMOD = (TMOD&0x0F)|0x10;        //设定T1的工作模式为1
   //----装入定时器初值 -----//
   TH1 = (65536-50000)/256;        //50ms定时 用于运行计时         
   TL1 = (65536-50000)%256;

   IP  = IP&0x08;                  //计时器享有中断优先
   ET1 = 1;                        // 定时器1允许中断
   TR1 = 1;                        // 启动定时器1 
   EA  = 1;                        // 开总中断 
}

/*********************************************
函数名称： Timer1_ISR
函数功能： 定时器1中断服务函数,用于产生时钟
函数输入： 无
函数输出： 无
**********************************************/
void Timer1_ISR() interrupt 3       
{
	uchar cnt;
	TH1 = (65536-50000)/256;              
	TL1 = (65536-50000)%256;
	cnt++;
	if(cnt >= 20)
	{
	   cnt = 0;
	   ++SecondL;
	   if(SecondL == 10)
	   {
		  SecondL = 0;
		  ++SecondH;
		  if(SecondH == 6)
		  {
			 SecondH = 0;
			 ++MinuteL;
			 if(MinuteL == 10)
			 {
				MinuteL = 0;
				++MinuteH;
			  }
		   }
		 }
	 }
}