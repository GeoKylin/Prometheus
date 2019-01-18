/*
 * =============================================================
 *
 *       Filename:  main.c
 *
 *    Description:  �����˴�������-��������˹
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

#define X 1

/*********************************************
                  ͷ�ļ�
**********************************************/
#include	<reg52.h>
#include    <intrins.h>
#include	"Motor.h"	//���
#include	"1602.h"	//��ʾ��
#include	"Timer.h"	//��ʱ��
#include    "Buzzer.h"	//������
/*********************************************
                  �궨��
**********************************************/
#define uchar	unsigned char
#define	uint	unsigned int
/*********************************************
                ����λ����
**********************************************/
//---------- ST188 ------------//
sbit 	Sensor1  = P0^0;	  //������1
sbit	Sensor2  = P0^1;	  //������2
sbit	Sensor3  = P0^2;	  //������3
sbit	Sensor4  = P0^3;	  //������4
sbit	Sensor5  = P0^4;	  //������5

/*********************************************
                ��������
**********************************************/
uchar   road_status;             //ѭ����������·���״̬��

void    RoadTrack(road_status);	 //ѭ������
void  RoadTrack_1(road_status);
void    Init_main(void);	     //��ʼ������

/*********************************************
�������ƣ� Init_main
�������ܣ� ��ʼ������
�������룺 �� 
��������� ��
**********************************************/
void  Init_main(void)
{
	Init_1602();
	Init_Timer();
	Init_Motor();
}

/*********************************************
�������ƣ� RoadTrack
�������ܣ� ��·���ѭ��
�������룺 road_status-��·���״̬ 
��������� ��
**********************************************/
void  RoadTrack(road_status)
{
	switch (road_status)
	{
		case 0x04:	GoHead(44*X,44*X);	break;	            //ǰ��
		case 0x00:  GoBack(30*X,30*X);  DelayMs(20);break;  //ֱ�ߺ���

		case 0x06:	GoHead(25*X,40*X);	break;	            //С��ת1
		case 0x02:	GoHead(17*X,40*X);	break;	            //С��ת2
		case 0x03:	GoHead(35*X,55*X);	break;	            //����ת1
		case 0x01:	GoHead(17*X,55*X);	break;	            //����ת2
		
		case 0x0C:	GoHead(39*X,25*X);	break;              //С��ת1
		case 0x08:	GoHead(39*X,17*X);	break;              //С��ת2
		case 0x18:	GoHead(56*X,25*X);	break;              //����ת1	
		case 0x10:	GoHead(56*X,17*X);	break;              //����ת2
		
		case 0x05:  Goright_90(300); break;				
		default:break; 
	}
}

/*********************************************
�������ƣ� RoadTrack_1
�������ܣ� ��·���ѭ��
�������룺 road_status-��·���״̬ 
��������� ��
**********************************************/
void  RoadTrack_1(road_status)
{
	switch (road_status)
	{
		case 0x04:	GoBack(44*X,44*X);	break;	            //ǰ��
		case 0x00:  GoHead(30*X,30*X);  DelayMs(20);break;  //ֱ�ߺ���

		case 0x06:	GoBack(40*X,25*X);	break;	            //С��ת1
		case 0x02:	GoBack(40*X,17*X);	break;	            //С��ת2
		case 0x03:	GoBack(55*X,35*X);	break;	            //����ת1
		case 0x01:	GoBack(55*X,17*X);	break;	            //����ת2
		
		case 0x0C:	GoBack(25*X,39*X);	break;              //С��ת1
		case 0x08:	GoBack(17*X,39*X);	break;              //С��ת2
		case 0x18:	GoBack(25*X,56*X);	break;              //����ת1	
		case 0x10:	GoBack(17*X,56*X);	break;              //����ת2
		
		case 0x05:  GoBack(44*X,44*X);  break;				
		default:break; 
	}
}

/********************************************
�������ƣ� main
�������ܣ� ������������
�������룺 ��
��������� ��
**********************************************/
void main(void)
{ 
	int Black_FLAG;     //ȫ�ڼ�����־
	Black_FLAG=0;       //ȫ�ڱ�־����
	Init_main();
	Stop(30,30);
	Write_str(0,3,"Prometheus",10);	  //��ʾ����
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
