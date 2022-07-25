
#ifndef  INCLUDES_H     //防止重复定义（INCLUDES_H 开头）
#define  INCLUDES_H

//----------------------------------------------------------------------
//（1）包含用到的构件
#include "user.h"
#include <OsFunc.h>
#include "NumToStr.h"
#include "lcd.h"
#include "adc.h"

//----------------------------------------------------------------------
//（2）全局使用的宏常数。
#define CMD_CHOOSE_EVENT  (1<<1)      //定义命令选择事件位第1位
#define GREEN_LIGHT_EVENT  (1<<2)      //定义绿灯事件为事件字第2位
#define BLUE_LIGHT_EVENT  (1<<3)      //定义蓝灯事件为事件字第3位
//----------------------------------------------------------------------
//（3）自定义数据类型

//----------------------------------------------------------------------

//（4）声明全局变量。命名规范见注2。
//【不动】宏定义全局变量前缀G_VAR_PREFIX。实现原理见注3。
#ifdef GLOBLE_VAR              //GLOBLE_VAR在main.c文件中有宏定义
  #define G_VAR_PREFIX         //前缀G_VAR_PREFIX定义为空
#else                          //GLOBLE_VAR在非main.c文件中无定义
  #define G_VAR_PREFIX extern  //前缀G_VAR_PREFIX定义为"extern"
#endif
//（在此增加全局变量）

//（系统保留）
G_VAR_PREFIX vuint16_t gcRecvLen;
G_VAR_PREFIX vuint16_t gcRecvDCLen;
G_VAR_PREFIX vuint8_t  gcRecvBuf[MCU_SECTORSIZE];
//（用户增加）
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
//线程函数声明
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


#endif                  //防止重复定义（INCLUDES_H 结尾）




