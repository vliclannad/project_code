#include <OsFunc.h>
#include "board.h"
//======================================================================
//�������ƣ�OS_start
//�������أ���
//����˵����
//���ܸ�Ҫ������RTOS��ִ�����߳�app_init
//======================================================================
void OS_start(void (*func)(void))
{
	rtthread_startup((void *)func);  //����RTOS��ִ�����߳�app_init
}


//=========================================================================
//�������ƣ�rtthread_startup
//�������أ���
//����˵������
//���ܸ�Ҫ�����ö�ջ������ʼ��Systick����ʱ�������������������̡߳������̣߳�����������
//=========================================================================
int rtthread_startup(void (*func)(void))
{
    rt_hw_interrupt_disable(); //���ж�
    //��1���弶Ӳ����ʼ����ע��: �ڰ弶Ӳ����ʼ�������а�Ҫ�ѳ�ʼ����(ǰ����ʹ�ö�̬�ڴ�)
    rt_hw_board_init();
    //��ӡ RT-Thread �汾�ţ�δ�õ�
    //rt_show_version();
    //��2����ʱ����ʼ��
    rt_system_timer_init();
    //��3����������ʼ��
    rt_system_scheduler_init();
#ifdef RT_USING_SIGNALS
    //�ź�����ʼ��
    rt_system_signal_init();
#endif
    //��4��������ʼ�̣߳����̣߳�
    rt_application_init((void *)func);
    //��ʱ���̳߳�ʼ����δ�õ�
    //rt_system_timer_thread_init();
    //��5�����������߳�
    rt_thread_idle_init();
    //��6������������
    rt_system_scheduler_start();
    //���Բ��ᵽ����
    return 0;
}

//=========================================================================
//�������ƣ�rt_application_init
//�������أ���
//����˵������
//���ܸ�Ҫ���������̣߳�����������߳̾����б��ȴ�������������������߳�����
//=========================================================================
void rt_application_init(void (*func)(void))
{
    rt_thread_t tid;

#ifdef RT_USING_HEAP
    //��1���������̣߳���Ϊ���������������Դ
    tid = rt_thread_create("main", (void *)func, RT_NULL,
                           RT_MAIN_THREAD_STACK_SIZE, RT_MAIN_THREAD_PRIORITY, 20);
    // RT_ASSERTΪ��������������Ϊ��
    RT_ASSERT(tid != RT_NULL);
#else
    rt_err_t result;

    tid = &main_thread;
    result = rt_thread_init(tid, "main", main_thread_entry, RT_NULL,
                            main_stack, sizeof(main_stack), RT_MAIN_THREAD_PRIORITY, 20);
    RT_ASSERT(result == RT_EOK);

    /* if not define RT_USING_HEAP, using to eliminate the warning */
    (void)result;
#endif
    //��2�������̼߳����߳̾����б��ȴ�����������������
    rt_thread_startup(tid);
}
