#include "includes.h"

void thread_SPThread2()
{
    //��1��======�����ֲ�����===========================================
    int SPcount;      //��¼�ź����ĸ���
    uart_send_string(UART_User,(void *)"��һ�ν����߳�2��\n");
    //��2��======��ѭ������ʼ��==========================================
    while (1)
	{
		delay_ms(1000);
    	SPcount=SP->value;   //��ȡ�ź�����ֵ
    	//uart_send_string(UART_User,(void *)"��ǰSPΪ%d\n");
		userprintf("��ǰSPΪ%d\n",SPcount);
		uart_send_string(UART_User,(void *)"�߳�2����1��SP\n");
		if(SPcount==0)
		{
			uart_send_string(UART_User,(void *)"SP����Ϊ0���߳�2�ȴ�\n");

		}
		rt_sem_take(SP,RT_WAITING_FOREVER); //��ȡһ���ź���
		SPcount=SP->value;
		//uart_send_string(UART_User,(void *)"�߳�2��ȡ1��SP��SP��ʣ%d\n");
		userprintf("�߳�2��ȡ1��SP��SP��ʣ%d\n",SPcount);
		delay_ms(2000);
		rt_sem_release(SP);   //�ͷ�һ���ź���
        uart_send_string(UART_User,(void *)"�߳�2�ɹ��ͷ�1��SP\n");
	}//��2��======��ѭ����������==========================================  
}
