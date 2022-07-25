#include "includes.h"


void thread_SPThread1()
{

    //（1）======申明局部变量===========================================
    int SPcount;      //记录信号量的个数
    uart_send_string(UART_User,(void *)"第一次进入线程1！\n");
	gpio_init(LIGHT_BLUE,GPIO_OUTPUT,LIGHT_OFF);
    gpio_init(LIGHT_GREEN,GPIO_OUTPUT,LIGHT_OFF);
    gpio_init(LIGHT_RED,GPIO_OUTPUT,LIGHT_OFF);
    //（2）======主循环（开始）==========================================
    while (1)
    {
    	delay_ms(1000);    //延时1秒
    	SPcount=SP->value;  //获取信号量的值
    	//uart_send_string(UART_User,(void *)"当前SP为%d\n",SPcount);
		userprintf("当前SP为%d\n",SPcount);
    	uart_send_string(UART_User,(void *)"线程1请求1个SP\n");
		if(SPcount==0)
		{
			uart_send_string(UART_User,(void *)"SP为0，线程1等待\n");
		}
		//获取一个信号量
		rt_sem_take(SP,RT_WAITING_FOREVER);
		SPcount=SP->value;
		//uart_send_string(UART_User,(void *)"线程1获取1个SP，SP还剩%d\n",SPcount);
		userprintf("线程1获取1个SP，SP还剩%d\n",SPcount);
		delay_ms(5000);
		//释放一个信号量
		rt_sem_release(SP);
        uart_send_string(UART_User,(void *)"线程1成功释放1个SP\n");
	}//（2）======主循环（结束）==========================================
	
}
