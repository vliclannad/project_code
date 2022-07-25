
#include "includes.h"


/*-------------------------------------------------------------------------
JY60数据帧结构：帧头0x55+数据类型0x51,0x52,0x53（加速度，角速度，角度）+数据低八位（X轴）+数据高八位（X轴）+数据低八位（Y轴）+数据高八位（Y轴）+数据低八位（Z轴）+数据高八位（Z轴）+数据低八位（其他）
+数据高八位（其他）+CRC校验（两字节）
-------------------------------------------------------------------------*/

void UART_User_Handler(void)
{
	 //（1）变量声明
    uint8_t flag,ch;
	gcRecvLen=0;
    DISABLE_INTERRUPTS;      //关总中断
    //（2）未触发串口接收中断，退出
    if(!uart_get_re_int(UART_User)) goto UART_User_Handler_EXIT;
    //（3）收到一个字节，读出该字节数据
    gcRecvBuf[gcRecvLen++] = uart_re1(UART_User,&flag);        //调用接收一个字节的函数
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
		case 0x51:memcpy(&sacc,&gcRecvBuf[2],8);//存放X,Y,Z三轴加速度
			break;
		case 0x52:memcpy(&sgyro,&gcRecvBuf[2],8);//存放X,Y,Z三轴角速度
			break;
		case 0x53:memcpy(&sangle,&gcRecvBuf[2],8);//存放X,Y,Z三轴角速度
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