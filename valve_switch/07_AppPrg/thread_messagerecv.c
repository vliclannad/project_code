#include "includes.h"


void thread_messagerecv()
{
	//��1��======�����ֲ�����==========================================
    uint8_t temp[8];
	char *cnt;
	uint8_t recvState;
	printf("��һ�ν�����Ϣ�����߳�!\r\n");
	gpio_init(LIGHT_BLUE,GPIO_OUTPUT,LIGHT_OFF);
    gpio_init(LIGHT_GREEN,GPIO_OUTPUT,LIGHT_OFF);
    gpio_init(LIGHT_RED,GPIO_OUTPUT,LIGHT_OFF);
	 //��2��======��ѭ������ʼ��==========================================
    while (1)
    {
	    //�ȴ���Ϣ
		recvState=mq_recv(mq,&temp,sizeof(temp),RT_WAITING_FOREVER);

		if(recvState==0)  //�������Ϣ
       	{
			cnt = rt_malloc(1);//�����ڴ�  
    	   	rt_sprintf(cnt,"%d",mq->entry);//entry�����е���Ϣ����
    	   	uart_send_string(UART_User,(void*)"��Ϣ��������Ϣ��=");
    	   	uart_send_string(UART_User,(uint8_t *)cnt);
    	   	uart_send_string(UART_User,(void *) "\r\n");
    	   	uart_send_string(UART_User,(void*) "��ǰȡ������Ϣ=");
    	   	uart_sendN(UART_User,8,temp);
    	   	uart_send_string(UART_User,(void *) "\r\n");
    	   	delay_ms(1000);                //�ӳ٣�Ϊ����ʾ��Ϣ�ѻ������


			//useruart_send_string(UART_User,(void*)"��Ϣ��Ϣ��Ϣ��Ϣ��Ϣ��Ϣ��Ϣ��Ϣ");
    	 }
    }//��2��======��ѭ����������==========================================
}
