#include "includes.h"


void thread_delayGreen(void)
{
    userprintf("------��һ�ν����̵��̣߳�%x��\r\n",thread_self());
    gpio_init(LIGHT_GREEN,GPIO_OUTPUT,LIGHT_OFF);
    while (1)
    {
    	userprintf("2-1.��ǰ���е��߳�=%x���̵���ʱ10�루��ʼ����\r\n",thread_self());
		delay_ms(10000);  //��ʱ
		userprintf("2-2.��ǰ���е��߳�=%x���̵���ʱ10�루���������̵Ʒ�ת��\r\n",thread_self());
		gpio_reverse(LIGHT_GREEN);    //�Ƶ�״̬��ת
    }
}
