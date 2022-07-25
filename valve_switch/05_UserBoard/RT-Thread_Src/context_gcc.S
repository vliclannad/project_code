/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2009-10-11     Bernard      first version
 * 2012-01-01     aozima       support context switch load/store FPU register.
 * 2013-06-18     aozima       add restore MSP feature.
 * 2013-06-23     aozima       support lazy stack optimized.
 * 2018-07-24     aozima       enhancement hard fault exception handler.
 */

/**
 * @addtogroup cortex-m4
 */
/*@{*/

.cpu cortex-m4
.syntax unified
.thumb
.text

.equ    SCB_VTOR,           0xE000ED08              //向量表偏移寄存器
.equ    NVIC_INT_CTRL,      0xE000ED04              //中断控制状态寄存器
.equ    NVIC_SYSPRI2,       0xE000ED20              //系统优先级寄存器(2)
.equ    NVIC_PENDSV_PRI,    0x00FF0000              // PendSV 优先级值 (lowest)
.equ    NVIC_PENDSVSET,     0x10000000              //触发PendSV exception的值


/*
 * rt_base_t rt_hw_interrupt_disable();
 */

.global rt_hw_interrupt_disable
.type rt_hw_interrupt_disable, %function
//关中断
rt_hw_interrupt_disable:
    MRS     r0, PRIMASK
    CPSID   I
    BX      LR

/*
 * void rt_hw_interrupt_enable(rt_base_t level);
 */
.global rt_hw_interrupt_enable
.type rt_hw_interrupt_enable, %function
//开中断
rt_hw_interrupt_enable:
    MSR     PRIMASK, r0
    BX      LR

/*
 * void rt_hw_context_switch(rt_uint32 from, rt_uint32 to);
 * r0 --> from
 * r1 --> to
 */
.global rt_hw_context_switch_interrupt
.type rt_hw_context_switch_interrupt, %function
.global rt_hw_context_switch
.type rt_hw_context_switch, %function
//上下文切换函数
rt_hw_context_switch_interrupt:
rt_hw_context_switch:
    //设置中断标志位rt_thread_switch_interrupt_flag为1
    LDR     r2, =rt_thread_switch_interrupt_flag   //加载rt_thread_switch_interrupt_flag的地址到r2
    LDR     r3, [r2]                         //加载rt_thread_switch_interrupt_flag的值到r3
    CMP     r3, #1                         //r3与1比较，相等则执行BEQ指令，否则不执行
    BEQ     _reswitch
    MOV     r3, #1                       //设置r3的值为1
    STR     r3, [r2]                       //将r3的值存储到rt_thread_switch_interrupt_flag，即置1
    //设置rt_interrupt_from_thread的值
    LDR     r2, =rt_interrupt_from_thread   //加载rt_interrupt_from_thread的地址到r2
    STR     r0, [r2]          //存储r0的值到rt_interrupt_from_thread，即上一个线程栈指针sp的指针

_reswitch:
    //设置rt_interrupt_to_thread的值
    LDR     r2, =rt_interrupt_to_thread     //加载rt_interrupt_to_thread的地址到r2
    STR     r1, [r2]      //存储r1的值到rt_interrupt_to_thread，即下一个线程栈指针sp的指针
    //触发PendSV异常，实现上下文切换
LDR r0, =NVIC_INT_CTRL
    LDR r1, =NVIC_PENDSVSET
    STR r1, [r0]
    //子程序返回
    BX  LR

/* r0 --> switch from thread stack
 * r1 --> switch to thread stack
 * psr, pc, lr, r12, r3, r2, r1, r0 are pushed into [from] stack
 */
.global PendSV_Handler
.type PendSV_Handler, %function
PendSV_Handler:
    //关中断，保护上下文切换不被中断，MRS加载特殊功能寄存器的值到通用寄存器
    //中断屏蔽寄存器（PRIMASK）D31~D1位保留，只有D0位有意义，CPSID  i将D0位置1（关总中断）
    MRS r2, PRIMASK
    CPSID   I
    //获取中断标志位判断是否为0
    LDR r0, =rt_thread_switch_interrupt_flag    //加载rt_thread_switch_interrupt_flag的地址到r0
    LDR r1, [r0]                           //加载rt_thread_switch_interrupt_flag的值到r1
    CBZ r1, pendsv_exit                    //判断r1是否为0，为0则跳转到pendsv_exit

    MOV r1, #0x00                       //r1不为0则清0
    STR r1, [r0]                        //将r1的值存储到rt_thread_switch_interrupt_flag，即清0
    //判断rt_interrupt_from_thread的值是否为0
    LDR r0, =rt_interrupt_from_thread    //加载rt_interrupt_from_thread的地址到r0
    LDR r1, [r0]                      //加载rt_interrupt_from_thread的值到r1
    CBZ r1, switch_to_thread          //第一次线程切换时rt_interrupt_from_thread肯定为0，
                                      //则跳转到switch_to_thread

    //上文保存
    //当进入PendSVC Handler时，上一个线程运行的环境即xPSR，PC（线程入口地址），R14，R12，
    //R3，R2，R1，R0（线程的形参），这些CPU寄存器的值会自动保存到线程的栈中，剩下的r4~r11需
    //要手动保存。
    MRS r1, psp                 //获取线程栈指针到r1
    
#if defined (__VFP_FP__) && !defined(__SOFTFP__)
    TST     lr, #0x10         //if(!EXC_RETURN[4])
                              //检查扩展堆栈帧（通过检查该位来表示是否需要FPU寄存器组）
    VSTMDBEQ r1!, {d8 - d15}     //保存FPU寄存器s16~s31
#endif
    
    STMFD   r1!, {r4 - r11}      //将CPU寄存器r4~r11的值存储到r1指向的地址
                                  //(每操作一次地址将递减一次)

#if defined (__VFP_FP__) && !defined(__SOFTFP__)
    MOV     r4, #0x00           /* flag = 0 */
    TST     lr, #0x10           /* if(!EXC_RETURN[4]) */
    MOVEQ   r4, #0x01           /* flag = 1 */
    STMFD   r1!, {r4}           /* push flag */
#endif

    LDR r0, [r0]               //加载r0指向值到r0，即r0=rt_interrupt_from_thread
    STR r1, [r0]                //将r1的值存储到r0，即更新线程栈sp

//上下文切换
switch_to_thread:
    LDR r1, =rt_interrupt_to_thread  //加载rt_interrupt_to_thread的地址到r1
                                     // rt_interrupt_to_thread是一个全局变量，里面存的是线程栈指针SP的指针
    LDR r1, [r1]                  //加载rt_interrupt_to_thread的值到r1，即sp的指针
    LDR r1, [r1]                //加载sp到r1
#if defined (__VFP_FP__) && !defined(__SOFTFP__)
    LDMFD   r1!, {r3}           /* pop flag */
#endif

    LDMFD   r1!, {r4 - r11}          //将线程栈指针r1(操作之前先递减)指向的内容
                                      //加载到CPU寄存器r4~r11

#if defined (__VFP_FP__) && !defined(__SOFTFP__)
    CMP     r3,  #0             /* if(flag_r3 != 0) */
    VLDMIANE  r1!, {d8 - d15}   /* pop FPU register s16~s31 */
#endif

    MSR psp, r1                 //线程栈指针更新到PSP

#if defined (__VFP_FP__) && !defined(__SOFTFP__)
    ORR     lr, lr, #0x10       /* lr |=  (1 << 4), clean FPCA. */
    CMP     r3,  #0             /* if(flag_r3 != 0) */
    BICNE   lr, lr, #0x10       /* lr &= ~(1 << 4), set FPCA. */
#endif

pendsv_exit:
    MSR PRIMASK, r2             //恢复中断
    ORR lr, lr, #0x04       //确保异常返回使用的栈指针是PSP，即LR寄存器的位2要为1
                           //异常返回，这个时候栈中的剩下内容将会自动加载到CPU寄存器：xPSR，PC（线程入口地址），
                          //R14，R12，R3，R2，R1，R0（线程的形参），同时PSP的值也将更新，即指向线程栈的栈顶
    BX  lr


/*
 * void rt_hw_context_switch_to(rt_uint32 to);
 * r0 --> to
 */
.global rt_hw_context_switch_to
.type rt_hw_context_switch_to, %function
rt_hw_context_switch_to:
    //（1）将下一个将要运行的线程的栈的sp的指针存放到rt_interrupt_to_thread
    LDR r1, =rt_interrupt_to_thread   //将rt_interrupt_to_thread的地址加载到r1
    STR r0, [r1]                    //将r0的值存储到rt_interrupt_to_thread
#if defined (__VFP_FP__) && !defined(__SOFTFP__)
    //第一次线程启动，不需要FPU寄存器保存，强制清除CONTROL[2]标志。此时为堆栈是MSP，也就是复位后进入第一个线程之前的状态
    MRS     r2, CONTROL         /* read */
    BIC     r2, #0x04           /* modify */
    MSR     CONTROL, r2         /* write-back */
#endif
    //（2）设置rt_interrupt_from_thread的值为0，表示启动第一次线程切换
    LDR r1, =rt_interrupt_from_thread  //将rt_interrupt_from_thread的地址加载到r1
    MOV r0, #0x0                   //配置r0等于0
    STR r0, [r1]                     //将r0的值存储到rt_interrupt_from_thread
    //（3）设置中断标志位rt_thread_switch_interrupt_flag的值为1
    LDR     r1, =rt_thread_switch_interrupt_flag   //将rt_thread_switch_interrupt_flag的地址加载到r1
    MOV     r0, #1                            //配置r0等于1
    STR     r0, [r1]                           //将r0的值存储到rt_thread_switch_interrupt_flag
    //（4）设置 PendSV 异常的优先级
    LDR r0, =NVIC_SYSPRI2     //将系统优先级寄存器2地址加载到r0
    LDR r1, =NVIC_PENDSV_PRI   //将PendSV优先级值 (lowest)加载到r1
    LDR.W   r2, [r0,#0x00]       //读，（LDR.W始终生成32位指令），将r0保存的系统优先级寄存器2地址加载到r2
    ORR     r1,r1,r2             //改，将r1与r2进行“或”运算并将值返回到r1
    STR     r1, [r0]             //写，将r1值存储到系统优先级寄存器2，即更新设置PendSV优先级值为最低
    //（5）触发 PendSV异常 (产生上下文切换)
    LDR r0, =NVIC_INT_CTRL    //将中断控制状态寄存器地址加载到r0
    LDR r1, =NVIC_PENDSVSET   //将能触发PendSV异常的值加载到r1
    STR r1, [r0]              //更新中断控制状态寄存器，触发PendSV异常
    //（6）恢复主堆栈指针MSP
    LDR     r0, =SCB_VTOR   //将中断向量表偏移寄存器地址加载到r0，实际通过中断向量表定位堆栈地址
    LDR     r0, [r0]
    LDR     r0, [r0]
    NOP
    MSR     msp, r0        //恢复主堆栈指针MSP，将堆栈地址保存到MSP中
    //（7）使能中断，pendSV中断开始执行，完成首个线程切换
    CPSIE   F
    CPSIE   I





    /* never reach here! */

/* compatible with old version */
.global rt_hw_interrupt_thread_switch
.type rt_hw_interrupt_thread_switch, %function
rt_hw_interrupt_thread_switch:
    BX  lr
    NOP

.global HardFault_Handler
.type HardFault_Handler, %function
HardFault_Handler:
    /* get current context */
    MRS     r0, msp                 /* get fault context from handler. */
    TST     lr, #0x04               /* if(!EXC_RETURN[2]) */
    BEQ     _get_sp_done
    MRS     r0, psp                 /* get fault context from thread. */
_get_sp_done:

    STMFD   r0!, {r4 - r11}         /* push r4 - r11 register */
#if defined (__VFP_FP__) && !defined(__SOFTFP__)
    STMFD   r0!, {lr}               /* push dummy for flag */
#endif
    STMFD   r0!, {lr}               /* push exec_return register */

    TST     lr, #0x04               /* if(!EXC_RETURN[2]) */
    BEQ     _update_msp
    MSR     psp, r0                 /* update stack pointer to PSP. */
    B       _update_done
_update_msp:
    MSR     msp, r0                 /* update stack pointer to MSP. */
_update_done:

    PUSH    {LR}
    BL      rt_hw_hard_fault_exception
    POP     {LR}

    ORR     lr, lr, #0x04
    BX      lr
