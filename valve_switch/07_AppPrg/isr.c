
#include "includes.h"


/*-------------------------------------------------------------------------
JY60����֡�ṹ��֡ͷ0x55+��������0x51,0x52,0x53�����ٶȣ����ٶȣ��Ƕȣ�+���ݵͰ�λ��X�ᣩ+���ݸ߰�λ��X�ᣩ+���ݵͰ�λ��Y�ᣩ+���ݸ߰�λ��Y�ᣩ+���ݵͰ�λ��Z�ᣩ+���ݸ߰�λ��Z�ᣩ+���ݵͰ�λ��������
+���ݸ߰�λ��������+CRCУ�飨���ֽڣ�
-------------------------------------------------------------------------*/

void UART_User_Handler(void)
{
	 //��1����������
    uint8_t flag,ch;
	gcRecvLen=0;
    DISABLE_INTERRUPTS;      //�����ж�
    //��2��δ�������ڽ����жϣ��˳�
    if(!uart_get_re_int(UART_User)) goto UART_User_Handler_EXIT;
    //��3���յ�һ���ֽڣ��������ֽ�����
    gcRecvBuf[gcRecvLen++] = uart_re1(UART_User,&flag);        //���ý���һ���ֽڵĺ���
	if (gcRecvBuf[0]!=0x55)
	{
		gcRecvLen=0;
		return;
	}
	if(gcRecvDCLen<11)
	{
		return;
	}
	else 
	{
		switch (gcRecvBuf[1])
		{
		case 0x51:memcpy(&sacc,&gcRecvBuf[2],8);//���X,Y,Z������ٶ�
			break;
		case 0x52:memcpy(&sgyro,&gcRecvBuf[2],8);//���X,Y,Z������ٶ�
			break;
		case 0x53:memcpy(&sangle,&gcRecvBuf[2],8);//���X,Y,Z������ٶ�
			break;
		default:
			break;
		}
		gcRecvLen=0;
	}
	ENABLE_INTERRUPTS;

	UART_User_Handler_EXIT:{
    ENABLE_INTERRUPTS;
    }

	
}