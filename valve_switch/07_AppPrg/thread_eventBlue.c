#include "includes.h"


void thread_eventBlue()
{
    //��1��======�����ֲ�����==========================================
    uint32_t recvedstate;

    printf("---��һ�ν������������߳�!\r\n");
    gpio_init(LIGHT_BLUE,GPIO_OUTPUT,LIGHT_ON);
    gpio_init(LIGHT_GREEN,GPIO_OUTPUT,LIGHT_OFF);
    gpio_init(LIGHT_RED,GPIO_OUTPUT,LIGHT_OFF);

    

    //��2��======��ѭ������ʼ��==========================================
    while (1)   //��ѭ��
    {
      rt_event_recv(EventWord,BLUE_LIGHT_EVENT,RT_EVENT_FLAG_OR|RT_EVENT_FLAG_CLEAR,RT_WAITING_FOREVER,&recvedstate);//�ȴ����������¼��ź�
      if(recvedstate==BLUE_LIGHT_EVENT)
     {  //��������������ȷ
    	uart_send_string(UART_User,(void *)"----���������߳�-----\r\n");
    	uart_send_string(UART_User,(void *)"�������߳��У������̵��¼�\r\n");
       // useruart_send_string(UART_User,(void *)"----�������߳��У������̵��¼�-----\r\n");
    	//����GREEN_LIGHT_EVENT�¼�λ
        rt_event_send(EventWord,GREEN_LIGHT_EVENT);
        uart_send_string(UART_User,(void *)"------������˸------\r\n");
       // useruart_send_string(UART_User,(void *)"----������˸-----\r\n");
	  	gpio_reverse(LIGHT_BLUE);
        delay_ms(10000);

     }
    }//��2��======��ѭ����������==========================================
}
