#include "includes.h"



void thread_cmdchoose()
{
        uint32_t recvedstate;
        uint8_t recvData[9];
    while(1)
    {
        uart_send_string(UART_User,(void *)"进入命令选择线程，等待事件信号\n");
        rt_event_recv(EventWord,CMD_CHOOSE_EVENT,RT_EVENT_FLAG_OR|RT_EVENT_FLAG_CLEAR,RT_WAITING_FOREVER,&recvedstate);//等待命令选择线程的事件信号，串口接收完数据后会触发
        uart_send_string(UART_User,(void *)"接收到事件信号\n");
        if(recvedstate==CMD_CHOOSE_EVENT)  //如果接收完成且正确
    	{
            if(gcRecvBuf[7]==CONNECT_CODE)//命令字为66，代表Pc端正和mcu取得连接
            {
                uart_send_string(UART_User,(void*) "I can see you");//回发连接确认
                LCD_ShowString(96,50,BLUE,GRAY,(char *)" 已连接");
            }
            if(gcRecvBuf[7]==RESULT_CODE)
            {

                rt_thread_delete(thd_eventBlue);
                rt_thread_delete(thd_eventGreen);
                rt_thread_delete(thd_messagerecv);
                rt_thread_delete(thd_SPThread1);	
                rt_thread_delete(thd_SPThread2);
                rt_thread_delete(thd_SPThread3);
                rt_thread_delete(thd_mutexRed);
                rt_thread_delete(thd_mutexGreen);
                rt_thread_delete(thd_mutexBlue);
                rt_thread_delete(thd_delayBlue);
                rt_thread_delete(thd_delayGreen);
                rt_thread_delete(thd_delayRed);

            }

    		if(gcRecvBuf[7]==EVENT_CODE) //命令字为90，代表“事件功能”
            {
                if(gcRecvBuf[8]==0x01)//命令参数为01，代表启动该功能，传递事件信号把小灯线程从阻塞队列移到就绪队列
                {  
                    //启动该功能线程前先关闭其他功能线程
                    uart_send_string(UART_User,(void *)"接收到事件功能开启命令，开启事件功能");
                    rt_thread_detach(thd_messagerecv);
                    rt_thread_detach(thd_SPThread1);	
                    rt_thread_detach(thd_SPThread2);
                    rt_thread_detach(thd_SPThread3);
                    rt_thread_detach(thd_mutexRed);
                    rt_thread_detach(thd_mutexGreen);
                    rt_thread_detach(thd_mutexBlue);
                    rt_thread_detach(thd_delayBlue);
                    rt_thread_detach(thd_delayGreen);
                    rt_thread_detach(thd_delayRed);


                    rt_thread_startup(thd_eventBlue);
                    rt_thread_startup(thd_eventGreen);
                    rt_event_send(EventWord,BLUE_LIGHT_EVENT);
                    LCD_ShowString(6,125,BLACK,GRAY,(char *)"当前状态:执行事件演示      ");

                }
                if(gcRecvBuf[8]==0x00)//命令参数为00，代表关闭该功能，重新启动小灯线程，把小灯线程移入阻塞队列
                {
                    uart_send_string(UART_User,(void *)"接收到事件功能结束命令，事件功能模块结束");
                    rt_thread_detach(thd_eventBlue);
                    rt_thread_detach(thd_eventGreen);
                    gpio_init(LIGHT_BLUE,GPIO_OUTPUT,LIGHT_OFF);
                    gpio_init(LIGHT_GREEN,GPIO_OUTPUT,LIGHT_OFF);
                    gpio_init(LIGHT_RED,GPIO_OUTPUT,LIGHT_OFF);
                    LCD_ShowString(6,125,BLACK,GRAY,(char *)"当前状态:等待命令      ");
                }
                

            }

            if(gcRecvBuf[7]==MESSAGE_CODE) //命令字为91，代表“消息队列功能”
            {
                rt_thread_detach(thd_eventBlue);
                rt_thread_detach(thd_eventGreen);
                rt_thread_detach(thd_SPThread1);	
                rt_thread_detach(thd_SPThread2);
                rt_thread_detach(thd_SPThread3);
                rt_thread_detach(thd_mutexRed);
                rt_thread_detach(thd_mutexGreen);
                rt_thread_detach(thd_mutexBlue);
                rt_thread_detach(thd_delayBlue);
                rt_thread_detach(thd_delayGreen);
                rt_thread_detach(thd_delayRed);


                rt_thread_startup(thd_messagerecv);//启动消息队列线程
                //取出收到的数据作为一个消息
			    for(int i=0;i<8;i++)
                {
                    recvData[i] = gcRecvBuf[i+9];

                }
				
		        //将该消息存放到消息队列
			    rt_mq_send(mq,recvData,sizeof(recvData));
		    }

            

            if(gcRecvBuf[7]==SEM_CODE) //命令字为92，代表“信号量功能”
            {
                if(gcRecvBuf[8]==0x01)//命令参数为01，代表启动该功能
                {
                    uart_send_string(UART_User,(void *)"接收到信号量功能开启命令，信号量功能模块开启\n");
                    rt_thread_detach(thd_eventBlue);
                    rt_thread_detach(thd_eventGreen);
                    rt_thread_detach(thd_messagerecv);
                    rt_thread_detach(thd_mutexRed);
                    rt_thread_detach(thd_mutexGreen);
                    rt_thread_detach(thd_mutexBlue);
                    rt_thread_detach(thd_delayBlue);
                    rt_thread_detach(thd_delayGreen);
                    rt_thread_detach(thd_delayRed);



	                rt_thread_startup(thd_SPThread1);//启动信号量线程1
	                rt_thread_startup(thd_SPThread2);//启动信号量线程2
	                rt_thread_startup(thd_SPThread3);//启动信号量线程
                    LCD_ShowString(6,125,BLACK,GRAY,(char *)"当前状态:执行信号量演示      ");


                }
                if(gcRecvBuf[8]==0x00)//命令参数为00，代表关闭该功能
                {
                    uart_send_string(UART_User,(void *)"接收到信号量功能结束命令，信号量功能模块结束");
                    rt_thread_detach(thd_SPThread1);	
                    rt_thread_detach(thd_SPThread2);
                    rt_thread_detach(thd_SPThread3);
                    gpio_init(LIGHT_BLUE,GPIO_OUTPUT,LIGHT_OFF);
                    gpio_init(LIGHT_GREEN,GPIO_OUTPUT,LIGHT_OFF);
                    gpio_init(LIGHT_RED,GPIO_OUTPUT,LIGHT_OFF);
                    LCD_ShowString(6,125,BLACK,GRAY,(char *)"当前状态:等待命令      ");

                }

            }

            if(gcRecvBuf[7]==MUTEX_CODE) //命令字为93，代表“功能”
            {
                if(gcRecvBuf[8]==0x01)
                {
                    uart_send_string(UART_User,(void *)"接收到互斥量功能开启命令，功能模块开启\n");
                    rt_thread_detach(thd_eventBlue);
                    rt_thread_detach(thd_eventGreen);
                    rt_thread_detach(thd_messagerecv);
                    rt_thread_detach(thd_SPThread1);	
                    rt_thread_detach(thd_SPThread2);
                    rt_thread_detach(thd_SPThread3);
                    rt_thread_detach(thd_delayBlue);
                    rt_thread_detach(thd_delayGreen);
                    rt_thread_detach(thd_delayRed);

                    rt_thread_startup(thd_mutexRed);//启动互斥量线程
	                rt_thread_startup(thd_mutexGreen);//启动互斥量线程
	                rt_thread_startup(thd_mutexBlue);//启动互斥量线程
                    LCD_ShowString(6,125,BLACK,GRAY,(char *)"当前状态:执行互斥量演示      ");
                }
                if(gcRecvBuf[8]==0x00)
                {
                    uart_send_string(UART_User,(void *)"接收到互斥量功能关闭命令，功能模块关闭\n");
                    rt_thread_detach(thd_mutexRed);
                    rt_thread_detach(thd_mutexGreen);
                    rt_thread_detach(thd_mutexBlue);
                    gpio_init(LIGHT_BLUE,GPIO_OUTPUT,LIGHT_OFF);
                    gpio_init(LIGHT_GREEN,GPIO_OUTPUT,LIGHT_OFF);
                    gpio_init(LIGHT_RED,GPIO_OUTPUT,LIGHT_OFF);
                    LCD_ShowString(6,125,BLACK,GRAY,(char *)"当前状态:等待命令      ");
                }

            }

                if(gcRecvBuf[7]==DELAY_CODE) //命令字为94，代表"延时功能”
            {
                if(gcRecvBuf[8]==0x01)
                {
                    uart_send_string(UART_User,(void *)"接收到延时功能开启命令，功能模块开启\n");
                    rt_thread_detach(thd_eventBlue);
                    rt_thread_detach(thd_eventGreen);
                    rt_thread_detach(thd_messagerecv);
                    rt_thread_detach(thd_SPThread1);	
                    rt_thread_detach(thd_SPThread2);
                    rt_thread_detach(thd_SPThread3);
                    rt_thread_detach(thd_mutexRed);
	                rt_thread_detach(thd_mutexGreen);
	                rt_thread_detach(thd_mutexBlue);

                    rt_thread_startup(thd_delayBlue);
                    rt_thread_startup(thd_delayGreen);
                    rt_thread_startup(thd_delayRed);
                    LCD_ShowString(6,125,BLACK,GRAY,(char *)"当前状态:执行延时演示      ");
                }
                if(gcRecvBuf[8]==0x00)
                {
                    uart_send_string(UART_User,(void *)"接收到延时功能关闭命令，功能模块关闭\n");
                    rt_thread_detach(thd_delayBlue);
                    rt_thread_detach(thd_delayGreen);
                    rt_thread_detach(thd_delayRed);
                    gpio_init(LIGHT_BLUE,GPIO_OUTPUT,LIGHT_OFF);
                    gpio_init(LIGHT_GREEN,GPIO_OUTPUT,LIGHT_OFF);
                    gpio_init(LIGHT_RED,GPIO_OUTPUT,LIGHT_OFF);
                    LCD_ShowString(6,125,BLACK,GRAY,(char *)"当前状态:等待命令      ");
                }

            }

    	}
    }
}
