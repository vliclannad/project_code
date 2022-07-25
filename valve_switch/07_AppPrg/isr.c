
#include "includes.h"

static uint8_t emuartFrameHead[2] = {0xA5,0x5A};  //֡ͷ
uint16_t useremuart_frame(uint8_t ch, uint8_t *data);


void UART_User_Handler(void)
{
	 //��1����������
    uint8_t flag,ch;
    DISABLE_INTERRUPTS;      //�����ж�
    //��2��δ�������ڽ����жϣ��˳�
    if(!uart_get_re_int(UART_User)) goto UART_User_Handler_EXIT;
    //��3���յ�һ���ֽڣ��������ֽ�����
    ch = uart_re1(UART_User,&flag);        //���ý���һ���ֽڵĺ���
    if(!flag) goto UART_User_Handler_EXIT; //ʵ��δ�յ����ݣ��˳�

    
       gcRecvLen =useremuart_frame(ch,(uint8_t*)gcRecvBuf);//�Խ���������֡������0��֡δ�ɹ������س�����֡�ɹ���
       if (gcRecvLen == 0) goto UART_User_Handler_EXIT; 
       rt_event_send(EventWord,CMD_CHOOSE_EVENT);//���ݽ�����ɣ�������ѡ���¼���λ
        gcRecvLen = 0;   //֡�Ѿ�ʹ����ϣ��´����յ�һ���ֽڣ����Լ�����֡
        //��ʹ��ģ���ṩ��User����ͨ��֡�ṹ������)��
     
    //��5���������˳�����
UART_User_Handler_EXIT:{
	//printf("goto----1\n");
    ENABLE_INTERRUPTS;
    }
    //main_Dly_ms(10);//�����ж�
}


uint16_t useremuart_frame(uint8_t ch, uint8_t *data)
{
	//printf("���뵽emuart_frame�п�ʼ��֡\n");
	static uint16_t index = 1;
	static uint16_t length = 1;
	uint16_t ret_val;
	
	
	//��1����δ���յ����ݻ���δ����֡ͷ�����˳�������0  ֡ͷ����Ϊ�����ֽ�
	if(((index-1) == 0 && ch != emuartFrameHead[0]) ||
			((index-1) == 1 && ch != emuartFrameHead[1]))
	{
		index = 1;
		length = 1;
		ret_val = 0;     //�������ݴ���
		goto uecom_recv_exit;
	}
	//��2����ȷ���յ���֡ͷ������ִ�У������ݴ���data����
	data[(index++)-1] = ch;
	//printf("%d",index);
	//��3������ȡ�����ĸ�����ʱ�������Ч���ݳ���


	if((index-1) == 3)
	{
		//printf("������ȷ����\n");
		length = data[2];
	}
	//�ж������Ƿ������ϣ���������˳���֡
	if(index==data[2]+4)
	{
		index = 1;
		ret_val = (length+3); //������Ч���ݳ���
		length=1;
		//data[(length-1)] = 0; //�����鳤��Ϊ0
		goto uecom_recv_exit;
	}
	ret_val = 0;
	goto uecom_recv_exit;
uecom_recv_exit:
    return ret_val;
}