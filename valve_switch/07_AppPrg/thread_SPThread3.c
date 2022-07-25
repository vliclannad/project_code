#include "includes.h"

void thread_SPThread3()
{
    //（1）======申明局部变量===========================================
    int SPcount;      //记录信号量的个数
    uart_send_string(UART_User,(void *)"第一次进入线程3！\n");
	gpio_init(LIGHT_RED,GPIO_OUTPUT,LIGHT_OFF);
    //（2）======主循环（开始）==========================================
    while (1)
    {
		gpio_init(LIGHT_BLUE,GPIO_OUTPUT,LIGHT_OFF);
    	delay_ms(1000);    //延时1秒
    	SPcount=SP->value; //获取信号量的值
    	//uart_send_string(UART_User,(void *)"当前SP个数为%d\n",SPcount);
		userprintf("当前SP个数为%d\n",SPcount);
    	uart_send_string(UART_User,(void *)"线程3请求1个SP\n");
		if(SPcount==0)
		{
			uart_send_string(UART_User,(void *)"SP个数为0，线程3等待\n");

		}
		rt_sem_take(SP,RT_WAITING_FOREVER); //获取一个信号量
		SPcount=SP->value;                 //获取信号量的值
		//uart_send_string(UART_User,(void *)"线程3获取1个SP，SP还剩%d\n",SPcount);
		userprintf("线程3获取1个SP，SP还剩%d\n",SPcount);
		delay_ms(3000);
	    uart_send_string(UART_User,(void *)"转换红灯状态\n");
		gpio_reverse(LIGHT_RED);
		rt_sem_release(SP);   //释放一个信号量
		uart_send_string(UART_User,(void *)"线程3成功释放1个SP\n");
    }//（2）======主循环（结束）==========================================  
}
