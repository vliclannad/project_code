//================================================================================
//�ļ����ƣ�OS_start.h��RTOS���������ӿ�ͷ�ļ���
//������λ���մ�arm��������(sumcu.suda.edu.cn)
//���¼�¼��
//20210126��1����"..src/components.c"�ļ��н�ȡrtthread_startup��rt_application_init
//================================================================================
#ifndef OSFUNC_H   //��ֹ�ظ����壨OSFUNC_H ��ͷ��
#define OSFUNC_H


#include <rthw.h>
#include <rtthread.h>

#define RTThread_Start 1 //��User����

//���߳����ȼ���С
#define RT_MAIN_THREAD_PRIORITY       (RT_THREAD_PRIORITY_MAX / 3)

//RTOS������ں���
void OS_start(void (*func)(void));
//RT_Thread��������
int rtthread_startup(void (*func)(void));
//�������̣߳����̣߳���������
void rt_application_init(void (*func)(void));

#endif
