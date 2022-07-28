
#include "includes.h"
#include "string.h"

uint16_t useremuart_frame(uint8_t ch, uint8_t *data);
/*-------------------------------------------------------------------------
JY60����֡�ṹ��֡ͷ0x55+��������0x51,0x52,0x53�����ٶȣ����ٶȣ��Ƕȣ�+���ݵͰ�λ��X�ᣩ+���ݸ߰�λ��X�ᣩ+���ݵͰ�λ��Y�ᣩ+���ݸ߰�λ��Y�ᣩ+���ݵͰ�λ��Z�ᣩ+���ݸ߰�λ��Z�ᣩ+���ݵͰ�λ��������
+���ݸ߰�λ��������+CRCУ�飨���ֽڣ�
-------------------------------------------------------------------------*/

void UART_User_Handler(void)
{
	 //��1����������
    uint8_t flag,ch;
    DISABLE_INTERRUPTS;//�����ж�
	gcRecvLen=0;     
    //��2��δ�������ڽ����жϣ��˳�
    if(!uart_get_re_int(UART_User)) goto UART_User_Handler_EXIT;
    //��3���յ�һ���ֽڣ��������ֽ�����
    ch = uart_re1(UART_User,&flag);  
	gpio_reverse(LIGHT_RED);
	if(!flag) goto UART_User_Handler_EXIT; //ʵ��δ�յ����ݣ��˳�
	gcRecvLen =useremuart_frame(ch,(uint8_t*)gcRecvBuf);
	if (gcRecvLen == 0) goto UART_User_Handler_EXIT; 
	printf("%d",gcRecvLen);
    /*gcRecvBuf[gcRecvLen++] = uart_re1(UART_User,&flag);     
	printf("Ŀǰ���ճ���Ϊ%d",gcRecvLen);   //���ý���һ���ֽڵĺ���
	if (gcRecvBuf[0]!=0x55)
	{
		gcRecvLen=0;
		return;
	}
	if(gcRecvLen<11)
	{
		return;
	}*/
	/*switch (gcRecvBuf[1])
	{
		case 0x51: memcpy(&sacc,&gcRecvBuf[2],6);//���X,Y,Z������ٶ�
			break;
		case 0x52: memcpy(&sgyro,&gcRecvBuf[2],6);//���X,Y,Z������ٶ�
			break;
		case 0x53: memcpy(&sangle,&gcRecvBuf[2],6);//���X,Y,Z������ٶ�
			break;
		default:
			break;
	}*/
	memcpy(&sangle,&gcRecvBuf[2],6);//���X,Y,Z������ٶ�
	gcRecvLen=0;


	UART_User_Handler_EXIT:{
    ENABLE_INTERRUPTS;
    }

	
}
uint16_t useremuart_frame(uint8_t ch, uint8_t *data)
{
	//printf("���뵽emuart_frame�п�ʼ��֡\n");
	static uint16_t index = 1;
	static uint16_t length = 1;
	uint16_t ret_val;
	
	
	//��1����δ���յ����ݻ���δ����֡ͷ�����˳�������0  ֡ͷ����Ϊ�����ֽ�
	if(((index-1) == 0 && ch != 0x55))
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
	//�ж������Ƿ������ϣ���������˳���֡
	if(index==11)
	{
		index = 1;
		ret_val = 11; //������Ч���ݳ���
		length=1;
		//data[(length-1)] = 0; //�����鳤��Ϊ0
		goto uecom_recv_exit;
	}
	ret_val = 0;
	goto uecom_recv_exit;
uecom_recv_exit:
    return ret_val;
}