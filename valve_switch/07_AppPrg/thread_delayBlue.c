#include "includes.h"


void thread_delayBlue(void)
{
    userprintf("------��һ�ν��������̣߳�%x\r\n",thread_self());
    gpio_init(LIGHT_BLUE,GPIO_OUTPUT,LIGHT_OFF);
    while (1)
    {
    	userprintf("1-1.��ǰ���е��߳�=%x��������ʱ20�루��ʼ����\r\n",thread_self());
		delay_ms(20000);  //��ʱ
		userprintf("1-2.��ǰ���е��߳�=%x��������ʱ20�루�����������Ʒ�ת��\r\n",thread_self());
		gpio_reverse(LIGHT_BLUE);    //�Ƶ�״̬��ת
    }
}

