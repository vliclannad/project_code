#include <OsFunc.h>
#include "board.h"
//======================================================================
//函数名称：OS_start
//函数返回：无
//参数说明：
//功能概要：启动RTOS并执行主线程app_init
//======================================================================
void OS_start(void (*func)(void))
{
	rtthread_startup((void *)func);  //启动RTOS并执行主线程app_init
}


//=========================================================================
//函数名称：rtthread_startup
//函数返回：无
//参数说明：无
//功能概要：设置堆栈区，初始化Systick、定时器、调度器，创建主线程、空闲线程，启动调度器
//=========================================================================
int rtthread_startup(void (*func)(void))
{
    rt_hw_interrupt_disable(); //关中断
    //（1）板级硬件初始化，注意: 在板级硬件初始化函数中把要堆初始化好(前提是使用动态内存)
    rt_hw_board_init();
    //打印 RT-Thread 版本号，未用到
    //rt_show_version();
    //（2）定时器初始化
    rt_system_timer_init();
    //（3）调度器初始化
    rt_system_scheduler_init();
#ifdef RT_USING_SIGNALS
    //信号量初始化
    rt_system_signal_init();
#endif
    //（4）创建初始线程（主线程）
    rt_application_init((void *)func);
    //定时器线程初始化，未用到
    //rt_system_timer_thread_init();
    //（5）创建空闲线程
    rt_thread_idle_init();
    //（6）启动调度器
    rt_system_scheduler_start();
    //绝对不会到这里
    return 0;
}

//=========================================================================
//函数名称：rt_application_init
//函数返回：无
//参数说明：无
//功能概要：创建主线程，并将其加入线程就绪列表，等待调度器启动后调度主线程运行
//=========================================================================
void rt_application_init(void (*func)(void))
{
    rt_thread_t tid;

#ifdef RT_USING_HEAP
    //（1）创建主线程，并为其分配运行所需资源
    tid = rt_thread_create("main", (void *)func, RT_NULL,
                           RT_MAIN_THREAD_STACK_SIZE, RT_MAIN_THREAD_PRIORITY, 20);
    // RT_ASSERT为保留函数，内容为空
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
    //（2）将主线程加入线程就绪列表，等待调度器启动后运行
    rt_thread_startup(tid);
}
