/*
 * =============================================================
 *
 *       Filename:  Motor.c
 *
 *    Description:  �������c�ļ�  ͨ��L298N�������
 *
 *        Version:  1.0.1
 *        Created:  2015.5.13
 *       Revision:  first
 *       Compiler:  Keil ��Vision 4
 *
 *         Author:  ���Ӣ������
 *	        Email:  513814330@qq.com
 *	           QQ:  513814330
 *
 * =============================================================
 */
 /*********************************************
                ����ͷ�ļ�
**********************************************/ 
#include	"motor.h"
#include	<reg52.h>
#include    <intrins.h>
/*********************************************
                ����λ����
**********************************************/ 
//---------- L298N ------------//
sbit 	RIGHT_IN1 =	P1^3;	  //�ұߵ�� �ź�1
sbit	RIGHT_EN  =	P1^4;     //�ұߵ�� ʹ��
sbit	RIGHT_IN2 =	P1^5;     //�ұߵ�� �ź�2
						   
sbit 	LEFT_IN1 =	P1^2;     //��ߵ�� �ź�1
sbit	LEFT_EN  =	P1^1;	  //��ߵ�� ʹ��
sbit	LEFT_IN2 =	P1^0;	  //��ߵ�� �ź�2

//---------- ST188 ------------//
sbit 	Sensor1  = P0^0;	  //������1
sbit	Sensor2  = P0^1;	  //������2
sbit	Sensor3  = P0^2;	  //������3
sbit	Sensor4  = P0^3;	  //������4
sbit	Sensor5  = P0^4;	  //������5

/*********************************************
                  �궨��
**********************************************/
#define PWM_PERIOD  100       //PWM�������ֵ PWM_PERIOD*100us
#define STR_FIX 1.2           //ֱ������ ��ʾ��߱��ұ߿���ٱ�����ֱ��ʱ�����Ĵ� �ҹ����С��

/*********************************************
                ��������
**********************************************/
//---------- PWM ------------//
uchar	PWM_COUNTER = 0;      //pwm�������� 100*100us
uchar	LEFT_PWM_DUTY  = 50;  //��ߵ��ռ�ձ�
uchar	RIGHT_PWM_DUTY = 50;  //�ұߵ��ռ�ձ�

/*********************************************
�������ƣ� Delay_10Us
�������ܣ� us��ʱ����
�������룺 us-��ʱʱ����Ʊ���
��������� ��
**********************************************/
void Delay_10Us(uint us)
{
	while( us-- );
}

/*********************************************
�������ƣ� DelayMs
�������ܣ� ms����ʱ��������ʱʱ�䣺ms*ms
�������룺 ms-��ʱʱ����Ʊ���
��������� ��
**********************************************/
void DelayMs(uint ms)
{
	unsigned int i,j;
	for( i = 0; i < ms; i ++ )
		for( j = 115; j > 0; j --);
}

/*********************************************
�������ƣ� Init_Motor
�������ܣ� ��ʼ����Ƭ���Ķ�ʱ0(���ڲ���PWM)
�������룺 ��
��������� ��
**********************************************/
void Init_Motor(void)
{
   TMOD = (TMOD&0xF0)|0x02;       //�趨T0�Ĺ���ģʽΪ2
   //----װ�붨ʱ����ֵ -----//
   TH0 = 0x95;                    //100us��ʱ ����ռ�ձȿ���
   TL0 = 0x95;	

   ET0 = 1;                       // ��ʱ��0�����ж� 
   TR0 = 1;                       // ������ʱ��0 
   EA  = 1;                       // �����ж� 
}

/*********************************************
�������ƣ� Timer0_ISR
�������ܣ� ��ʱ��0�жϷ�����,�������PWM��
�������룺 ��
��������� ��
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
�������ƣ� Stop
�������ܣ� ͣ������
�������룺 speed_left -����ռ�ձ�
           speed_right-����ռ�ձ�
��������� ��
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
�������ƣ� GoHead
�������ܣ� ǰ������������С����һ���ٶ�ֱ��ǰ����Ҳ����
           ����С��ת��
�������룺 speed_left -����ռ�ձ�
           speed_right-����ռ�ձ�
��������� ��
**********************************************/
void GoHead(uchar speed_left,uchar speed_right)
{
	LEFT_IN1  = 0;
	LEFT_IN2  = 1;

	RIGHT_IN1 =	0;
	RIGHT_IN2 =	1;
	LEFT_PWM_DUTY  = (uchar)(speed_left*STR_FIX); //ֱ������
	RIGHT_PWM_DUTY = speed_right;
}

/*********************************************
�������ƣ� GoBack
�������ܣ� ���˺���������С����һ���ٶ�ֱ�ߺ��ˣ�Ҳ����
           С������ת��
�������룺 speed_left -����ռ�ձ�
           speed_right-����ռ�ձ�
��������� ��
**********************************************/
void GoBack(uchar speed_left,uchar speed_right)
{
	LEFT_IN1  = 1;
	LEFT_IN2  =	0;
	RIGHT_IN1 =	1;
	RIGHT_IN2 =	0;
	LEFT_PWM_DUTY  = (uchar)(speed_left*STR_FIX); //ֱ������
	RIGHT_PWM_DUTY = speed_right;
}
/*********************************************
�������ƣ� Goright
�������ܣ� ��ת90�Ⱥ���������С����һ���ٶ���ת90��
�������룺 speed_left -����ռ�ձ�
           speed_right-����ռ�ձ�
��������� ��
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
�������ƣ� Goleft_180
�������ܣ� ת180�Ⱥ���������С����һ���ٶȴ�����ת180��
�������룺 speed_left -����ռ�ձ�
           speed_right-����ռ�ձ�
��������� ��
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
�������ƣ� Sensor
�������ܣ� ������ʶ�𣬸��ݴ������������ݣ�����һ��
		   ѭ������
�������룺 sbit 	 Sensor1  = P0^0	  //������1
           sbit		 Sensor2  = P0^1	  //������2
		   sbit		 Sensor3  = P0^2	  //������3
		   sbit		 Sensor4  = P0^3	  //������4
		   sbit		 Sensor5  = P0^4	  //������5
��������� uchar     road_status		  //ѭ������
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