#include "includes.h"


void thread_eventGreen()
{
	//��1��======����ֲ�����=========================================
    uint32_t recvedstate;
    printf("��һ�ν����̵��߳�!\r\n");
	gpio_init(LIGHT_GREEN,GPIO_OUTPUT,LIGHT_OFF);
	//��2��======��ѭ������ʼ��==========================================
    while (1)
    {
    	uart_send_string(UART_User,(void *)"���̵��߳��У��ȴ��̵��¼�������\r\n");
    	//һֱ�ȴ�GREEN_LIGHT_EVENT�¼���
        rt_event_recv(EventWord,GREEN_LIGHT_EVENT,RT_EVENT_FLAG_OR|RT_EVENT_FLAG_CLEAR,RT_WAITING_FOREVER,&recvedstate);
    	if(recvedstate==GREEN_LIGHT_EVENT)  //��������������ȷ
    	{
			uart_send_string(UART_User,(void *)"���̵��߳��У��յ��̵��¼����̵Ʒ�ת\r\n");
            gpio_reverse(LIGHT_GREEN);     //ת���̵�״̬
			rt_event_send(EventWord,BLUE_LIGHT_EVENT);
    	}
    }//��2��======��ѭ����������==========================================
}