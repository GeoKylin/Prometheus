/*
 * =============================================================
 *
 *       Filename:  Motor.c
 *
 *    Description:  �������h�ļ�   ͨ��L298N�������
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
#ifndef __MOTOR_H__            //ͷ�ļ������ض���
#define __MOTOR_H__

#define uchar	unsigned char  //�������Ͷ���
#define	uint	unsigned int

void      Delay_10Us(uint us);      //us����ʱ
void      DelayMs(uint ms);		    //���뼶��ʱ
void      Init_Motor(void);	        //�����ʱ����T0����ʼ������
void      Timer0_ISR(void);         //PWM���жϺ���
void      Stop(uchar speed_left,uchar speed_right);
void      GoHead(uchar speed_left,uchar speed_right);
void      GoBack(uchar speed_left,uchar speed_right);
void      Goright_90(int delaytime);
																		    
uchar Sensor(Sensor1,Sensor2,Sensor3,Sensor4,Sensor5);	//������ʶ����***

#endif