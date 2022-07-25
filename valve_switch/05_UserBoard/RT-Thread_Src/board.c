/*
 * Copyright (c) 2006-2019, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-07-24     Tanek        the first version
 * 2018-11-12     Ernest Chen  modify copyright
 */
 
#include <stdint.h>
#include <rthw.h>
#include <rtthread.h>
#include "board.h"
#include "printf.h"

#define _SCB_BASE       (0xE000E010UL)
#define _SYSTICK_CTRL   (*(rt_uint32_t *)(_SCB_BASE + 0x0))
#define _SYSTICK_LOAD   (*(rt_uint32_t *)(_SCB_BASE + 0x4))
#define _SYSTICK_VAL    (*(rt_uint32_t *)(_SCB_BASE + 0x8))
#define _SYSTICK_CALIB  (*(rt_uint32_t *)(_SCB_BASE + 0xC))
#define _SYSTICK_PRI    (*(rt_uint8_t  *)(0xE000ED23UL))

// Updates the variable SystemCoreClock and must be called 
// whenever the core clock is changed during program execution.
extern void SystemCoreClockUpdate(void);

// Holds the system core clock, which is the system clock 
// frequency supplied to the SysTick timer and the processor 
// core clock.
extern uint32_t SystemCoreClock;

static uint32_t _SysTick_Config(rt_uint32_t ticks)
{
    if ((ticks - 1) > 0xFFFFFF)
    {
        return 1;
    }
    
    _SYSTICK_LOAD = ticks - 1; 
    _SYSTICK_PRI = 0xFF;
    _SYSTICK_VAL  = 0;
    _SYSTICK_CTRL = 0x07;  
    
    return 0;
}

#if defined(RT_USING_USER_MAIN) && defined(RT_USING_HEAP)
//#define RT_HEAP_SIZE 1024
#define RT_HEAP_SIZE 3072
static uint32_t rt_heap[RT_HEAP_SIZE];     // heap default size: 4K(1024 * 4)
RT_WEAK void *rt_heap_begin_get(void)
{
    return rt_heap;
}

RT_WEAK void *rt_heap_end_get(void)
{
    return rt_heap + RT_HEAP_SIZE;
}
#endif

/**
 * This function will initial your board.
 */
void rt_hw_board_init()
{
    //(1)��ʼ��ϵͳʱ��
    SystemCoreClockUpdate();
    //��2����ʼ��SysTick��RT_TICK_PER_SECONDΪrtconfig.h���õĵδ�Ƶ�ʣ�Ĭ��1000
    _SysTick_Config(SystemCoreClock / RT_TICK_PER_SECOND);

    //Ӳ��BSP��ʼ��ͳͳ�����������LED�����ڣ�LCD��
#ifdef RT_USING_COMPONENTS_INIT  //���������ʼ������
    rt_components_board_init();
#endif
//���ͬʱ������RT_USING_USER_MAIN�� RT_USING_HEAP�������꣬��ʾRT-Thread���洴���ں˶���ʱʹ�ö�̬�ڴ���䷽����
#if defined(RT_USING_USER_MAIN) && defined(RT_USING_HEAP)
    //��3����ʼ���ѿռ�
    rt_system_heap_init(rt_heap_begin_get(), rt_heap_end_get());
#endif

}

void SysTick_Handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    rt_tick_increase();

    /* leave interrupt */
    rt_interrupt_leave();
}
