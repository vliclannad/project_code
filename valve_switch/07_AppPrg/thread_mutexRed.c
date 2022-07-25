#include "includes.h"


void thread_mutexRed()
{
    //��1��======�����ֲ�����==========================================
    gpio_init(LIGHT_RED,GPIO_OUTPUT,LIGHT_OFF);
    uart_send_string(UART_User,(void *)"��һ�ν������̣߳�\r\n");
    //��2��======��ѭ������ʼ��==========================================
    while (1)
    {
    	//1.��ס��ɫ�ƻ�����
    	rt_mutex_take(mutex,RT_WAITING_FOREVER);
        uart_send_string(UART_User,(void *)"\r\n������ɫ�������ɹ�����Ʒ�ת����ʱ5��\r\n");
        //2.��Ʊ���
        gpio_reverse(LIGHT_RED);
        //3.��ʱ5��
        delay_ms(5000);
    	//4.��Ʊ䰵
    	gpio_reverse(LIGHT_RED);
        //5.������ɫ�ƻ�����
		rt_mutex_release(mutex);
     }//��2��======��ѭ����������==========================================
}