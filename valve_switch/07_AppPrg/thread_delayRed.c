#include "includes.h"



void thread_delayRed(void)
{   
    userprintf("------第一次进入红灯线程：%x，\r\n",thread_self());
    gpio_init(LIGHT_RED,GPIO_OUTPUT,LIGHT_OFF);
    while (1)
    {
    	userprintf("当前运行的线程=%x，红灯延时5秒（开始）；\r\n",thread_self());
		delay_ms(5000);  //延时5秒
		userprintf("当前运行的线程=%x，红灯延时5秒（结束），红灯反转。\r\n",thread_self());
		gpio_reverse(LIGHT_RED);    //灯的状态反转
    }
}

