/*
 * =============================================================
 *
 *       Filename:  Buzzer.h
 *
 *    Description:  ������h�ļ�  ͨ������������
 *
 *        Version:  1.0.1
 *        Created:  2015.5.13
 *       Revision:  frist
 *       Compiler:  Keil ��Vision 4
 *
 *         Author:  ���Ӣ������
 *	        Email:  513814330@qq.com
 *	           QQ:  513814330
 *
 * =============================================================
 */
#ifndef __BUZZER_H__           //ͷ�ļ������ض���
#define __BUZZER_H__

#define  uchar	unsigned char  //�������Ͷ���
#define	 uint	unsigned int
 //---------- ���������� ------------//
sbit  BUZZER = P3^0;           //����������δ�ã�

void  Buzzer(uchar delay_x);   //�������������͵�ƽ������

#endif 