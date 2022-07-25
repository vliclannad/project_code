#include "includes.h"


void thread_mutexRed()
{
    //（1）======申明局部变量==========================================
    gpio_init(LIGHT_RED,GPIO_OUTPUT,LIGHT_OFF);
    uart_send_string(UART_User,(void *)"第一次进入红灯线程！\r\n");
    //（2）======主循环（开始）==========================================
    while (1)
    {
    	//1.锁住单色灯互斥量
    	rt_mutex_take(mutex,RT_WAITING_FOREVER);
        uart_send_string(UART_User,(void *)"\r\n锁定单色互斥量成功！红灯反转，延时5秒\r\n");
        //2.红灯变亮
        gpio_reverse(LIGHT_RED);
        //3.延时5秒
        delay_ms(5000);
    	//4.红灯变暗
    	gpio_reverse(LIGHT_RED);
        //5.解锁单色灯互斥量
		rt_mutex_release(mutex);
     }//（2）======主循环（结束）==========================================
}