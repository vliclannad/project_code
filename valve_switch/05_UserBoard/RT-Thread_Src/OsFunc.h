//================================================================================
//文件名称：OS_start.h（RTOS启动函数接口头文件）
//制作单位：苏大arm技术中心(sumcu.suda.edu.cn)
//更新记录：
//20210126（1）从"..src/components.c"文件中截取rtthread_startup与rt_application_init
//================================================================================
#ifndef OSFUNC_H   //防止重复定义（OSFUNC_H 开头）
#define OSFUNC_H


#include <rthw.h>
#include <rtthread.h>

#define RTThread_Start 1 //从User启动

//主线程优先级大小
#define RT_MAIN_THREAD_PRIORITY       (RT_THREAD_PRIORITY_MAX / 3)

//RTOS启动入口函数
void OS_start(void (*func)(void));
//RT_Thread启动函数
int rtthread_startup(void (*func)(void));
//自启动线程（主线程）创建函数
void rt_application_init(void (*func)(void));

#endif
