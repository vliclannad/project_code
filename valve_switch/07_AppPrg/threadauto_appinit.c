#include "includes.h"


void app_init(void)
{

	rt_thread_t thd_cmdchoose;


	

	DISABLE_INTERRUPTS;


	printf("  调用gpio_init函数，分别初始化红灯、绿灯、蓝灯\r\n");
	gpio_init(LIGHT_GREEN,GPIO_OUTPUT,LIGHT_OFF);
	gpio_init(LIGHT_BLUE,GPIO_OUTPUT,LIGHT_OFF);
	gpio_init(LIGHT_RED,GPIO_OUTPUT,LIGHT_OFF);
	uart_init(UART_User,115200); 
	    //LCD初始化、初始界面绘制
    LCD_Init();
    LCD_aotu(2,2,238,318,0);
    LCD_ShowString(35,20,BLACK,GRAY,(char *)"RT-Thread实验演示系统");
    LCD_ShowString(96,50,RED,GRAY,(char *)" 未连接");
    
    LCD_ShowString(6,90,BLACK,GRAY,(char *)"程序版本:1.01");
    LCD_aotu(4,110,236,120,1);
    LCD_ShowString(6,125,BLACK,GRAY,(char *)"当前状态:等待命令");
    LCD_aotu(4,145,236,155,1);
    LCD_ShowString(6,160,BLACK,GRAY,(char *)"小灯状态:关");
    LCD_aotu(4,180,236,190,1);
	uart_enable_re_int(UART_User);
	ENABLE_INTERRUPTS;
	
	//创建事件字
	EventWord=rt_event_create("EventWord",RT_IPC_FLAG_PRIO);
	//创建消息队列
	mq=rt_mq_create("mq",9,4,RT_IPC_FLAG_FIFO);
	//创建信号量
	SP=rt_sem_create("SP",2,RT_IPC_FLAG_FIFO);
	//创建互斥量
	mutex=rt_mutex_create("mutex",RT_IPC_FLAG_PRIO);


	//创建命令选择线程
	thd_cmdchoose=rt_thread_create("cmdchoose", (void *)thread_cmdchoose, 0, 512, 9, 10);
	//创建事件线程
	thd_eventGreen = rt_thread_create("eventGreen", (void *)thread_eventGreen, 0, 512, 10, 10);
	thd_eventBlue = rt_thread_create("eventBlue", (void *)thread_eventBlue, 0, 512, 10, 10);
	//创建消息队列线程
	thd_messagerecv = rt_thread_create("messagerecv", (void *)thread_messagerecv, 0, 512, 10, 10);
	//创建三个信号量线程
	thd_SPThread1 = rt_thread_create("SPThread1", (void *)thread_SPThread1, 0, 512, 10, 10);
	thd_SPThread2 = rt_thread_create("SPThread2", (void *)thread_SPThread2, 0, 512, 10, 10);
	thd_SPThread3 = rt_thread_create("SPThread3", (void *)thread_SPThread3, 0, 512, 10, 10);
	//创建三个互斥量线程
	thd_mutexBlue = rt_thread_create("mutexBlue", (void *)thread_mutexBlue, 0, 512, 10, 10);
	thd_mutexGreen = rt_thread_create("mutexGreen", (void *)thread_mutexGreen, 0, 512, 10, 10);
	thd_mutexRed = rt_thread_create("mutexRed", (void *)thread_mutexRed, 0, 512, 10, 10);
	//创建三个延时线程
	thd_delayRed=rt_thread_create("delayRed", (void *)thread_delayRed, 0, 512, 10, 10);
	thd_delayGreen=rt_thread_create("delayGreen", (void *)thread_delayGreen, 0, 512, 10, 10);
	thd_delayBlue=rt_thread_create("delayBlue", (void *)thread_delayBlue, 0, 512, 10, 10);

	thd_lcdshow=rt_thread_create("lcdshow", (void *)thread_lcdshow, 0, 512, 10, 10);




	   



    rt_thread_startup(thd_cmdchoose);//启动命令选择线程
	rt_thread_startup(thd_lcdshow);//启动LCD屏自动更新线程
}
