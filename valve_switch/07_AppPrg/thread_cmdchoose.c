#include "includes.h"



void thread_cmdchoose()
{
        uint32_t recvedstate;
        uint8_t recvData[9];
    while(1)
    {
        uart_send_string(UART_User,(void *)"��������ѡ���̣߳��ȴ��¼��ź�\n");
        rt_event_recv(EventWord,CMD_CHOOSE_EVENT,RT_EVENT_FLAG_OR|RT_EVENT_FLAG_CLEAR,RT_WAITING_FOREVER,&recvedstate);//�ȴ�����ѡ���̵߳��¼��źţ����ڽ��������ݺ�ᴥ��
        uart_send_string(UART_User,(void *)"���յ��¼��ź�\n");
        if(recvedstate==CMD_CHOOSE_EVENT)  //��������������ȷ
    	{
            if(gcRecvBuf[7]==CONNECT_CODE)//������Ϊ66������Pc������mcuȡ������
            {
                uart_send_string(UART_User,(void*) "I can see you");//�ط�����ȷ��
                LCD_ShowString(96,50,BLUE,GRAY,(char *)" ������");
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

    		if(gcRecvBuf[7]==EVENT_CODE) //������Ϊ90�������¼����ܡ�
            {
                if(gcRecvBuf[8]==0x01)//�������Ϊ01�����������ù��ܣ������¼��źŰ�С���̴߳����������Ƶ���������
                {  
                    //�����ù����߳�ǰ�ȹر����������߳�
                    uart_send_string(UART_User,(void *)"���յ��¼����ܿ�����������¼�����");
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
                    LCD_ShowString(6,125,BLACK,GRAY,(char *)"��ǰ״̬:ִ���¼���ʾ      ");

                }
                if(gcRecvBuf[8]==0x00)//�������Ϊ00������رոù��ܣ���������С���̣߳���С���߳�������������
                {
                    uart_send_string(UART_User,(void *)"���յ��¼����ܽ�������¼�����ģ�����");
                    rt_thread_detach(thd_eventBlue);
                    rt_thread_detach(thd_eventGreen);
                    gpio_init(LIGHT_BLUE,GPIO_OUTPUT,LIGHT_OFF);
                    gpio_init(LIGHT_GREEN,GPIO_OUTPUT,LIGHT_OFF);
                    gpio_init(LIGHT_RED,GPIO_OUTPUT,LIGHT_OFF);
                    LCD_ShowString(6,125,BLACK,GRAY,(char *)"��ǰ״̬:�ȴ�����      ");
                }
                

            }

            if(gcRecvBuf[7]==MESSAGE_CODE) //������Ϊ91��������Ϣ���й��ܡ�
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


                rt_thread_startup(thd_messagerecv);//������Ϣ�����߳�
                //ȡ���յ���������Ϊһ����Ϣ
			    for(int i=0;i<8;i++)
                {
                    recvData[i] = gcRecvBuf[i+9];

                }
				
		        //������Ϣ��ŵ���Ϣ����
			    rt_mq_send(mq,recvData,sizeof(recvData));
		    }

            

            if(gcRecvBuf[7]==SEM_CODE) //������Ϊ92�������ź������ܡ�
            {
                if(gcRecvBuf[8]==0x01)//�������Ϊ01�����������ù���
                {
                    uart_send_string(UART_User,(void *)"���յ��ź������ܿ�������ź�������ģ�鿪��\n");
                    rt_thread_detach(thd_eventBlue);
                    rt_thread_detach(thd_eventGreen);
                    rt_thread_detach(thd_messagerecv);
                    rt_thread_detach(thd_mutexRed);
                    rt_thread_detach(thd_mutexGreen);
                    rt_thread_detach(thd_mutexBlue);
                    rt_thread_detach(thd_delayBlue);
                    rt_thread_detach(thd_delayGreen);
                    rt_thread_detach(thd_delayRed);



	                rt_thread_startup(thd_SPThread1);//�����ź����߳�1
	                rt_thread_startup(thd_SPThread2);//�����ź����߳�2
	                rt_thread_startup(thd_SPThread3);//�����ź����߳�
                    LCD_ShowString(6,125,BLACK,GRAY,(char *)"��ǰ״̬:ִ���ź�����ʾ      ");


                }
                if(gcRecvBuf[8]==0x00)//�������Ϊ00������رոù���
                {
                    uart_send_string(UART_User,(void *)"���յ��ź������ܽ�������ź�������ģ�����");
                    rt_thread_detach(thd_SPThread1);	
                    rt_thread_detach(thd_SPThread2);
                    rt_thread_detach(thd_SPThread3);
                    gpio_init(LIGHT_BLUE,GPIO_OUTPUT,LIGHT_OFF);
                    gpio_init(LIGHT_GREEN,GPIO_OUTPUT,LIGHT_OFF);
                    gpio_init(LIGHT_RED,GPIO_OUTPUT,LIGHT_OFF);
                    LCD_ShowString(6,125,BLACK,GRAY,(char *)"��ǰ״̬:�ȴ�����      ");

                }

            }

            if(gcRecvBuf[7]==MUTEX_CODE) //������Ϊ93���������ܡ�
            {
                if(gcRecvBuf[8]==0x01)
                {
                    uart_send_string(UART_User,(void *)"���յ����������ܿ����������ģ�鿪��\n");
                    rt_thread_detach(thd_eventBlue);
                    rt_thread_detach(thd_eventGreen);
                    rt_thread_detach(thd_messagerecv);
                    rt_thread_detach(thd_SPThread1);	
                    rt_thread_detach(thd_SPThread2);
                    rt_thread_detach(thd_SPThread3);
                    rt_thread_detach(thd_delayBlue);
                    rt_thread_detach(thd_delayGreen);
                    rt_thread_detach(thd_delayRed);

                    rt_thread_startup(thd_mutexRed);//�����������߳�
	                rt_thread_startup(thd_mutexGreen);//�����������߳�
	                rt_thread_startup(thd_mutexBlue);//�����������߳�
                    LCD_ShowString(6,125,BLACK,GRAY,(char *)"��ǰ״̬:ִ�л�������ʾ      ");
                }
                if(gcRecvBuf[8]==0x00)
                {
                    uart_send_string(UART_User,(void *)"���յ����������ܹر��������ģ��ر�\n");
                    rt_thread_detach(thd_mutexRed);
                    rt_thread_detach(thd_mutexGreen);
                    rt_thread_detach(thd_mutexBlue);
                    gpio_init(LIGHT_BLUE,GPIO_OUTPUT,LIGHT_OFF);
                    gpio_init(LIGHT_GREEN,GPIO_OUTPUT,LIGHT_OFF);
                    gpio_init(LIGHT_RED,GPIO_OUTPUT,LIGHT_OFF);
                    LCD_ShowString(6,125,BLACK,GRAY,(char *)"��ǰ״̬:�ȴ�����      ");
                }

            }

                if(gcRecvBuf[7]==DELAY_CODE) //������Ϊ94������"��ʱ���ܡ�
            {
                if(gcRecvBuf[8]==0x01)
                {
                    uart_send_string(UART_User,(void *)"���յ���ʱ���ܿ����������ģ�鿪��\n");
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
                    LCD_ShowString(6,125,BLACK,GRAY,(char *)"��ǰ״̬:ִ����ʱ��ʾ      ");
                }
                if(gcRecvBuf[8]==0x00)
                {
                    uart_send_string(UART_User,(void *)"���յ���ʱ���ܹر��������ģ��ر�\n");
                    rt_thread_detach(thd_delayBlue);
                    rt_thread_detach(thd_delayGreen);
                    rt_thread_detach(thd_delayRed);
                    gpio_init(LIGHT_BLUE,GPIO_OUTPUT,LIGHT_OFF);
                    gpio_init(LIGHT_GREEN,GPIO_OUTPUT,LIGHT_OFF);
                    gpio_init(LIGHT_RED,GPIO_OUTPUT,LIGHT_OFF);
                    LCD_ShowString(6,125,BLACK,GRAY,(char *)"��ǰ״̬:�ȴ�����      ");
                }

            }

    	}
    }
}
