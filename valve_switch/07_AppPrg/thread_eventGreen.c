#include "includes.h"


void thread_eventGreen()
{
	//（1）======申请局部变量=========================================
    uint32_t recvedstate;
    printf("第一次进入绿灯线程!\r\n");
	gpio_init(LIGHT_GREEN,GPIO_OUTPUT,LIGHT_OFF);
	//（2）======主循环（开始）==========================================
    while (1)
    {
    	uart_send_string(UART_User,(void *)"在绿灯线程中，等待绿灯事件被触发\r\n");
    	//一直等待GREEN_LIGHT_EVENT事件字
        rt_event_recv(EventWord,GREEN_LIGHT_EVENT,RT_EVENT_FLAG_OR|RT_EVENT_FLAG_CLEAR,RT_WAITING_FOREVER,&recvedstate);
    	if(recvedstate==GREEN_LIGHT_EVENT)  //如果接收完成且正确
    	{
			uart_send_string(UART_User,(void *)"在绿灯线程中，收到绿灯事件，绿灯反转\r\n");
            gpio_reverse(LIGHT_GREEN);     //转换绿灯状态
			rt_event_send(EventWord,BLUE_LIGHT_EVENT);
    	}
    }//（2）======主循环（结束）==========================================
}