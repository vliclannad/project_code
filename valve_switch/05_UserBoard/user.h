//======================================================================
//�ļ����ƣ�user.h��userͷ�ļ���
//������λ��SD-Arm(sumcu.suda.edu.cn)
//���¼�¼��20181201-20200830
//��Ҫ˵������1�������õ���ͷ�ļ���Ϊ�ﵽӦ�ó���Ŀ���ֲ�ԣ�����Ӳ��Ҫ��
//              оƬ�ĸ����ţ���Ҫ������궨�壬Ŀ����ʵ�ֶԾ���Ӳ������
//              ��̣������Ƕ�оƬ�����ű��
//          ��2���жϴ�����������ڴ˺궨�壬�Ա�isr.c����ֲ
//======================================================================
#ifndef USER_H   //��ֹ�ظ����壨USER_H ��ͷ��
#define USER_H

//��1�����̶����ļ�����
#include "printf.h"
#include "gpio.h"
#include "flash.h"
#include "emuart.h"
#include "gec.h"
#include "Os_United_API.h"

//��2�����䶯��ָʾ�ƶ˿ڼ����Ŷ��塪����ʵ��ʹ�õ����ŸĶ�
//ָʾ�ƶ˿ڼ����Ŷ���
#define  LIGHT_RED    (PTB_NUM|7)  //��ƣ���GEC_56��
#define  LIGHT_GREEN  (PTB_NUM|8)  //�̵ƣ���GEC_55��
#define  LIGHT_BLUE   (PTB_NUM|9)  //���ƣ���GEC_54��

//��״̬�궨�壨�������ư���Ӧ�������ƽ��Ӳ���ӷ�������
#define  LIGHT_ON       0    //����
#define  LIGHT_OFF      1    //�ư�

//��3�����䶯��UART����ģ�鶨��
#define UART_Debug   UART_3   //���ڳ�����£��޷���ʹ��
#define UART_User    UART_2   //�û����ڣ���-GND;��-TX;��-RX��

//��4�����䶯���жϷ������궨��
#define UART_User_Handler   USART2_IRQHandler  //�û������жϺ���

// (5)����궨��
#define EVENT_CODE  0x90    //�¼������û�ָ��
#define MESSAGE_CODE 0x91   //��Ϣ���й����û�ָ��
#define SEM_CODE 0x92       //�ź��������û�ָ��
#define MUTEX_CODE 0x93     //�����������û�ָ��
#define DELAY_CODE 0x94     //��ʱ�����û�ָ��
#define CONNECT_CODE 0x66   //pc������mcu������
#define RESULT_CODE 0x77    //mcu����������

#endif    //��ֹ�ظ����壨USER_H ��β��
