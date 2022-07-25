/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2012-09-20     Bernard      Change the name to components.c
 *                             And all components related header files.
 * 2012-12-23     Bernard      fix the pthread initialization issue.
 * 2013-06-23     Bernard      Add the init_call for components initialization.
 * 2013-07-05     Bernard      Remove initialization feature for MS VC++ compiler
 * 2015-02-06     Bernard      Remove the MS VC++ support and move to the kernel
 * 2015-05-04     Bernard      Rename it to components.c because compiling issue
 *                             in some IDEs.
 * 2015-07-29     Arda.Fu      Add support to use RT_USING_USER_MAIN with IAR
 */

#include <rthw.h>
#include <rtthread.h>

#ifdef RT_USING_USER_MAIN
#ifndef RT_MAIN_THREAD_STACK_SIZE
#define RT_MAIN_THREAD_STACK_SIZE     2048
#endif
#ifndef RT_MAIN_THREAD_PRIORITY
#define RT_MAIN_THREAD_PRIORITY       (RT_THREAD_PRIORITY_MAX / 3)
#endif
#endif

#ifdef RT_USING_COMPONENTS_INIT
/*
 * Components Initialization will initialize some driver and components as following
 * order:
 * rti_start         --> 0
 * BOARD_EXPORT      --> 1
 * rti_board_end     --> 1.end
 *
 * DEVICE_EXPORT     --> 2
 * COMPONENT_EXPORT  --> 3
 * FS_EXPORT         --> 4
 * ENV_EXPORT        --> 5
 * APP_EXPORT        --> 6
 *
 * rti_end           --> 6.end
 *
 * These automatically initialization, the driver or component initial function must
 * be defined with:
 * INIT_BOARD_EXPORT(fn);
 * INIT_DEVICE_EXPORT(fn);
 * ...
 * INIT_APP_EXPORT(fn);
 * etc.
 */
static int rti_start(void)
{
    return 0;
}
INIT_EXPORT(rti_start, "0");

static int rti_board_start(void)
{
    return 0;
}
INIT_EXPORT(rti_board_start, "0.end");

static int rti_board_end(void)
{
    return 0;
}
INIT_EXPORT(rti_board_end, "1.end");

static int rti_end(void)
{
    return 0;
}
INIT_EXPORT(rti_end, "6.end");

/**
 * RT-Thread Components Initialization for board
 */
void rt_components_board_init(void)
{
#if RT_DEBUG_INIT
    int result;
    const struct rt_init_desc *desc;
    for (desc = &__rt_init_desc_rti_board_start; desc < &__rt_init_desc_rti_board_end; desc ++)
    {
        rt_kprintf("initialize %s", desc->fn_name);
        result = desc->fn();
        rt_kprintf(":%d done\n", result);
    }
#else
    const init_fn_t *fn_ptr;

    for (fn_ptr = &__rt_init_rti_board_start; fn_ptr < &__rt_init_rti_board_end; fn_ptr++)
    {
        (*fn_ptr)();
    }
#endif
}

/**
 * RT-Thread Components Initialization
 */
void rt_components_init(void)
{
#if RT_DEBUG_INIT
    int result;
    const struct rt_init_desc *desc;

    rt_kprintf("do components initialization.\n");
    for (desc = &__rt_init_desc_rti_board_end; desc < &__rt_init_desc_rti_end; desc ++)
    {
        rt_kprintf("initialize %s", desc->fn_name);
        result = desc->fn();
        rt_kprintf(":%d done\n", result);
    }
#else
    const init_fn_t *fn_ptr;

    for (fn_ptr = &__rt_init_rti_board_end; fn_ptr < &__rt_init_rti_end; fn_ptr ++)
    {
        (*fn_ptr)();
    }
#endif
}

#ifdef RT_USING_USER_MAIN

void rt_application_init(void);
void rt_hw_board_init(void);
int rtthread_startup(void);

#if defined(__CC_ARM) || defined(__CLANG_ARM)
extern int $Super$$main(void);
/* re-define main function */
int $Sub$$main(void)
{
    rtthread_startup();
    return 0;
}
#elif defined(__ICCARM__)
extern int main(void);
/* __low_level_init will auto called by IAR cstartup */
extern void __iar_data_init3(void);
int __low_level_init(void)
{
    // call IAR table copy function.
    __iar_data_init3();
    rtthread_startup();
    return 0;
}
#elif defined(__GNUC__)
extern int main(void);
/* Add -eentry to arm-none-eabi-gcc argument */
//int entry(void)
//{
//    rtthread_startup();
//    return 0;
//}
#endif

#ifndef RT_USING_HEAP
/* if there is not enable heap, we should use static thread and stack. */
ALIGN(8)
static rt_uint8_t main_stack[RT_MAIN_THREAD_STACK_SIZE];
struct rt_thread main_thread;
#endif

/* the system main thread */
void main_thread_entry(void *parameter)
{
    extern int main(void);
    extern int $Super$$main(void);

    /* RT-Thread components initialization */
    rt_components_init();

    /* invoke system main function */
#if defined(__CC_ARM) || defined(__CLANG_ARM)
    $Super$$main(); /* for ARMCC. */
#elif defined(__ICCARM__) || defined(__GNUC__)
    main();
#endif
}

//=========================================================================
//�������ƣ�rt_application_init
//�������أ���
//����˵������
//���ܸ�Ҫ���������̣߳�����������߳̾������У��ȴ�������������������߳�����
//=========================================================================
//void rt_application_init(void)
//{
//    rt_thread_t tid;
//
//#ifdef RT_USING_HEAP
//    //��1���������̣߳���Ϊ���������������Դ
//    tid = rt_thread_create("main", main_thread_entry, RT_NULL,
//                           RT_MAIN_THREAD_STACK_SIZE, RT_MAIN_THREAD_PRIORITY, 20);
//    // RT_ASSERTΪ��������������Ϊ��
//    RT_ASSERT(tid != RT_NULL);
//#else
//    rt_err_t result;
//
//    tid = &main_thread;
//    result = rt_thread_init(tid, "main", main_thread_entry, RT_NULL,
//                            main_stack, sizeof(main_stack), RT_MAIN_THREAD_PRIORITY, 20);
//    RT_ASSERT(result == RT_EOK);
//
//    /* if not define RT_USING_HEAP, using to eliminate the warning */
//    (void)result;
//#endif
//    //��2�������̼߳����߳̾������У��ȴ�����������������
//    rt_thread_startup(tid);
//}

//=========================================================================
//�������ƣ�rtthread_startup
//�������أ���
//����˵������
//���ܸ�Ҫ�����ö�ջ������ʼ��Systick����ʱ�������������������̡߳������̣߳�����������
//=========================================================================
//int rtthread_startup(void)
//{
//    rt_hw_interrupt_disable(); //���ж�
//    //��1���弶Ӳ����ʼ����ע��: �ڰ弶Ӳ����ʼ�������а�Ҫ�ѳ�ʼ����(ǰ����ʹ�ö�̬�ڴ�)
//    rt_hw_board_init();
//    //��ӡ RT-Thread �汾�ţ�δ�õ�
//    //rt_show_version();
//    //��2����ʱ����ʼ��
//    rt_system_timer_init();
//    //��3����������ʼ��
//    rt_system_scheduler_init();
//#ifdef RT_USING_SIGNALS
//    //�ź�����ʼ��
//    rt_system_signal_init();
//#endif
//    //��4��������ʼ�̣߳����̣߳�
//    rt_application_init();
//    //��ʱ���̳߳�ʼ����δ�õ�
//    //rt_system_timer_thread_init();
//    //��5�����������߳�
//    rt_thread_idle_init();
//    //��6������������
//    rt_system_scheduler_start();
//    //���Բ��ᵽ����
//    return 0;
//}
#endif
#endif