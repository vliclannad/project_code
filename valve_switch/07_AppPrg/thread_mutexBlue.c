#include "includes.h"


void thread_mutexBlue()
{
    //��1��======�����ֲ�����==========================================
    gpio_init(LIGHT_BLUE,GPIO_OUTPUT,LIGHT_OFF);
    uart_send_string(UART_User,(void *)"��һ�ν��������̣߳�\r\n");
    //��2��======��ѭ������ʼ��==========================================
    while (1)
    {
    	//1.��ס��ɫ�ƻ�����
    	rt_mutex_take(mutex,RT_WAITING_FOREVER);
		uart_send_string(UART_User,(void *)"\r\n������ɫ�������ɹ������Ʒ�ת����ʱ20��\r\n");
		//2.���Ʊ���
		gpio_reverse(LIGHT_BLUE);
		//3.��ʱ20��
		delay_ms(20000);
		//4.���Ʊ䰵
		gpio_reverse(LIGHT_BLUE);
		//5.������ɫ�ƻ�����
		rt_mutex_release(mutex);
    }//��2��======��ѭ����������==========================================
}