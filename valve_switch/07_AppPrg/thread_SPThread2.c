#include "includes.h"

void thread_SPThread2()
{
    //（1）======申明局部变量===========================================
    int SPcount;      //记录信号量的个数
    uart_send_string(UART_User,(void *)"第一次进入线程2！\n");
    //（2）======主循环（开始）==========================================
    while (1)
	{
		delay_ms(1000);
    	SPcount=SP->value;   //获取信号量的值
    	//uart_send_string(UART_User,(void *)"当前SP为%d\n");
		userprintf("当前SP为%d\n",SPcount);
		uart_send_string(UART_User,(void *)"线程2请求1个SP\n");
		if(SPcount==0)
		{
			uart_send_string(UART_User,(void *)"SP个数为0，线程2等待\n");

		}
		rt_sem_take(SP,RT_WAITING_FOREVER); //获取一个信号量
		SPcount=SP->value;
		//uart_send_string(UART_User,(void *)"线程2获取1个SP，SP还剩%d\n");
		userprintf("线程2获取1个SP，SP还剩%d\n",SPcount);
		delay_ms(2000);
		rt_sem_release(SP);   //释放一个信号量
        uart_send_string(UART_User,(void *)"线程2成功释放1个SP\n");
	}//（2）======主循环（结束）==========================================  
}
