#include "includes.h"


void thread_SPThread1()
{

    //��1��======�����ֲ�����===========================================
    int SPcount;      //��¼�ź����ĸ���
    uart_send_string(UART_User,(void *)"��һ�ν����߳�1��\n");
	gpio_init(LIGHT_BLUE,GPIO_OUTPUT,LIGHT_OFF);
    gpio_init(LIGHT_GREEN,GPIO_OUTPUT,LIGHT_OFF);
    gpio_init(LIGHT_RED,GPIO_OUTPUT,LIGHT_OFF);
    //��2��======��ѭ������ʼ��==========================================
    while (1)
    {
    	delay_ms(1000);    //��ʱ1��
    	SPcount=SP->value;  //��ȡ�ź�����ֵ
    	//uart_send_string(UART_User,(void *)"��ǰSPΪ%d\n",SPcount);
		userprintf("��ǰSPΪ%d\n",SPcount);
    	uart_send_string(UART_User,(void *)"�߳�1����1��SP\n");
		if(SPcount==0)
		{
			uart_send_string(UART_User,(void *)"SPΪ0���߳�1�ȴ�\n");
		}
		//��ȡһ���ź���
		rt_sem_take(SP,RT_WAITING_FOREVER);
		SPcount=SP->value;
		//uart_send_string(UART_User,(void *)"�߳�1��ȡ1��SP��SP��ʣ%d\n",SPcount);
		userprintf("�߳�1��ȡ1��SP��SP��ʣ%d\n",SPcount);
		delay_ms(5000);
		//�ͷ�һ���ź���
		rt_sem_release(SP);
        uart_send_string(UART_User,(void *)"�߳�1�ɹ��ͷ�1��SP\n");
	}//��2��======��ѭ����������==========================================
	
}
