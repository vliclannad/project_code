#include "includes.h"



void thread_delayRed(void)
{   
    userprintf("------��һ�ν������̣߳�%x��\r\n",thread_self());
    gpio_init(LIGHT_RED,GPIO_OUTPUT,LIGHT_OFF);
    while (1)
    {
    	userprintf("��ǰ���е��߳�=%x�������ʱ5�루��ʼ����\r\n",thread_self());
		delay_ms(5000);  //��ʱ5��
		userprintf("��ǰ���е��߳�=%x�������ʱ5�루����������Ʒ�ת��\r\n",thread_self());
		gpio_reverse(LIGHT_RED);    //�Ƶ�״̬��ת
    }
}

