/*
 * =============================================================
 *
 *       Filename:  Timer.h
 *
 *    Description:  ��ʱ��h�ļ�  ͨ��51�Դ���ʱ��T1��¼����ʱ��
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
#ifndef __TIMER_H__            //ͷ�ļ������ض���
#define __TIMER_H__

#define uchar	unsigned char  //�������Ͷ���
#define	uint	unsigned int
 //---------- ʱ�ӱ��� ------------//
 extern uchar SecondL;         //ʱ�����λ
 extern uchar SecondH;         //ʱ�����λ
 extern uchar MinuteL;         //ʱ��ֵ�λ
 extern uchar MinuteH;         //ʱ��ָ�λ

 void Init_Timer(void);        //��ʱ����ʼ��
 void Timer1_ISR();            //��ʱ���ж���Ӧ

#endif