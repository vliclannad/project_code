#include "includes.h"


void thread_delayBlue(void)
{
    userprintf("------第一次进入蓝灯线程：%x\r\n",thread_self());
    gpio_init(LIGHT_BLUE,GPIO_OUTPUT,LIGHT_OFF);
    while (1)
    {
    	userprintf("1-1.当前运行的线程=%x，蓝灯延时20秒（开始）；\r\n",thread_self());
		delay_ms(20000);  //延时
		userprintf("1-2.当前运行的线程=%x，蓝灯延时20秒（结束），蓝灯反转。\r\n",thread_self());
		gpio_reverse(LIGHT_BLUE);    //灯的状态反转
    }
}

