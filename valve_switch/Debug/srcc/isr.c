
#include "includes.h"
#include "string.h"

uint16_t useremuart_frame(uint8_t ch, uint8_t *data);
/*-------------------------------------------------------------------------
JY60数据帧结构：帧头0x55+数据类型0x51,0x52,0x53（加速度，角速度，角度）+数据低八位（X轴）+数据高八位（X轴）+数据低八位（Y轴）+数据高八位（Y轴）+数据低八位（Z轴）+数据高八位（Z轴）+数据低八位（其他）
+数据高八位（其他）+CRC校验（两字节）
-------------------------------------------------------------------------*/

void UART_User_Handler(void)
{
	 //（1）变量声明
    uint8_t flag,ch;
    DISABLE_INTERRUPTS;//关总中断
	gcRecvLen=0;     
    //（2）未触发串口接收中断，退出
    if(!uart_get_re_int(UART_User)) goto UART_User_Handler_EXIT;
    //（3）收到一个字节，读出该字节数据
    ch = uart_re1(UART_User,&flag);  
	gpio_reverse(LIGHT_RED);
	if(!flag) goto UART_User_Handler_EXIT; //实际未收到数据，退出
	gcRecvLen =useremuart_frame(ch,(uint8_t*)gcRecvBuf);
	if (gcRecvLen == 0) goto UART_User_Handler_EXIT; 
	printf("%d",gcRecvLen);
    /*gcRecvBuf[gcRecvLen++] = uart_re1(UART_User,&flag);     
	printf("目前接收长度为%d",gcRecvLen);   //调用接收一个字节的函数
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
		case 0x51: memcpy(&sacc,&gcRecvBuf[2],6);//存放X,Y,Z三轴加速度
			break;
		case 0x52: memcpy(&sgyro,&gcRecvBuf[2],6);//存放X,Y,Z三轴角速度
			break;
		case 0x53: memcpy(&sangle,&gcRecvBuf[2],6);//存放X,Y,Z三轴角速度
			break;
		default:
			break;
	}*/
	memcpy(&sangle,&gcRecvBuf[2],6);//存放X,Y,Z三轴角速度
	gcRecvLen=0;


	UART_User_Handler_EXIT:{
    ENABLE_INTERRUPTS;
    }

	
}
uint16_t useremuart_frame(uint8_t ch, uint8_t *data)
{
	//printf("进入到emuart_frame中开始组帧\n");
	static uint16_t index = 1;
	static uint16_t length = 1;
	uint16_t ret_val;
	
	
	//（1）若未接收到数据或者未遇到帧头，则退出并返回0  帧头长度为两个字节
	if(((index-1) == 0 && ch != 0x55))
	{
		index = 1;
		length = 1;
		ret_val = 0;     //接收数据错误
		goto uecom_recv_exit;
	}
	//（2）正确接收到了帧头，继续执行，将数据存入data数组
	data[(index++)-1] = ch;
	//printf("%d",index);
	//（3）当获取到第四个数据时，求出有效数据长度
	//判断数据是否接收完毕，接收完毕退出组帧
	if(index==11)
	{
		index = 1;
		ret_val = 11; //返回有效数据长度
		length=1;
		//data[(length-1)] = 0; //令数组长度为0
		goto uecom_recv_exit;
	}
	ret_val = 0;
	goto uecom_recv_exit;
uecom_recv_exit:
    return ret_val;
}