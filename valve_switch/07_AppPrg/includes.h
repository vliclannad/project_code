
#ifndef  INCLUDES_H     //��ֹ�ظ����壨INCLUDES_H ��ͷ��
#define  INCLUDES_H

//----------------------------------------------------------------------
//��1�������õ��Ĺ���
#include "user.h"
#include <OsFunc.h>
#include "NumToStr.h"
#include "lcd.h"
#include "adc.h"

//----------------------------------------------------------------------
//��2��ȫ��ʹ�õĺ곣����
#define CMD_CHOOSE_EVENT  (1<<1)      //��������ѡ���¼�λ��1λ
#define GREEN_LIGHT_EVENT  (1<<2)      //�����̵��¼�Ϊ�¼��ֵ�2λ
#define BLUE_LIGHT_EVENT  (1<<3)      //���������¼�Ϊ�¼��ֵ�3λ
//----------------------------------------------------------------------
//��3���Զ�����������

//----------------------------------------------------------------------

//��4������ȫ�ֱ����������淶��ע2��
//���������궨��ȫ�ֱ���ǰ׺G_VAR_PREFIX��ʵ��ԭ���ע3��
#ifdef GLOBLE_VAR              //GLOBLE_VAR��main.c�ļ����к궨��
  #define G_VAR_PREFIX         //ǰ׺G_VAR_PREFIX����Ϊ��
#else                          //GLOBLE_VAR�ڷ�main.c�ļ����޶���
  #define G_VAR_PREFIX extern  //ǰ׺G_VAR_PREFIX����Ϊ"extern"
#endif
//���ڴ�����ȫ�ֱ�����

//��ϵͳ������
G_VAR_PREFIX vuint16_t gcRecvLen;
G_VAR_PREFIX vuint16_t gcRecvDCLen;
G_VAR_PREFIX vuint8_t  gcRecvBuf[MCU_SECTORSIZE];
//���û����ӣ�
G_VAR_PREFIX rt_event_t EventWord;
G_VAR_PREFIX rt_mq_t mq;
G_VAR_PREFIX rt_sem_t SP;
G_VAR_PREFIX rt_mutex_t mutex;


G_VAR_PREFIX	rt_thread_t thd_eventGreen;
G_VAR_PREFIX 	rt_thread_t thd_eventBlue;
G_VAR_PREFIX 	rt_thread_t thd_messagerecv;
G_VAR_PREFIX 	rt_thread_t thd_SPThread1;
G_VAR_PREFIX 	rt_thread_t thd_SPThread2;
G_VAR_PREFIX 	rt_thread_t thd_SPThread3;
G_VAR_PREFIX 	rt_thread_t thd_mutexBlue;
G_VAR_PREFIX 	rt_thread_t thd_mutexGreen;
G_VAR_PREFIX 	rt_thread_t thd_mutexRed;
G_VAR_PREFIX  rt_thread_t thd_delayGreen;
G_VAR_PREFIX  rt_thread_t thd_delayBlue;
G_VAR_PREFIX  rt_thread_t thd_delayRed;
G_VAR_PREFIX  rt_thread_t thd_lcdshow;
//�̺߳�������
void app_init(void);
void thread_cmdchoose();
void thread_eventGreen();
void thread_eventBlue();
void thread_messagerecv();
void thread_SPThread1();
void thread_SPThread2();
void thread_SPThread3();
void thread_mutexBlue();
void thread_mutexGreen();
void thread_mutexRed();
void thread_delayBlue();
void thread_delayGreen();
void thread_delayRed();
void thread_lcdshow();
//void thread_cloose(uint16_t thread_number);
#define delay_ms(x)  rt_thread_delay(x)
//----------------------------------------------------------------------


#endif                  //��ֹ�ظ����壨INCLUDES_H ��β��




