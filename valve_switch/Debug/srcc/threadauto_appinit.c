#include "includes.h"


void app_init(void)
{


	

	DISABLE_INTERRUPTS;


	printf("  ����gpio_init�������ֱ��ʼ����ơ��̵ơ�����\r\n");
	gpio_init(LIGHT_GREEN,GPIO_OUTPUT,LIGHT_OFF);
	gpio_init(LIGHT_BLUE,GPIO_OUTPUT,LIGHT_OFF);
	gpio_init(LIGHT_RED,GPIO_OUTPUT,LIGHT_OFF);
	uart_init(UART_User,9600); 
	    //LCD��ʼ������ʼ�������
    LCD_Init();
    LCD_aotu(2,2,238,318,0);
    LCD_ShowString(35,20,BLACK,GRAY,(char *)"�����ǽǶȲ鿴");
    
    LCD_ShowString(6,90,BLACK,GRAY,(char *)"X��Ƕ�:");
    LCD_aotu(4,110,236,120,1);
    LCD_ShowString(6,125,BLACK,GRAY,(char *)"Y��Ƕ�:");
    LCD_aotu(4,145,236,155,1);
    LCD_ShowString(6,160,BLACK,GRAY,(char *)"Z��Ƕ�:");
    LCD_aotu(4,180,236,190,1);
	uart_enable_re_int(UART_User);



	thd_gyroscope=rt_thread_create("gyroscope", (void *)thread_gyroscope, 0, 512, 10, 10);
	thd_lcdshow=rt_thread_create("lcdshow", (void *)thread_lcdshow, 0, 512, 10, 10);

	ENABLE_INTERRUPTS;




	   



	rt_thread_startup(thd_lcdshow);//����LCD���Զ������߳�
	rt_thread_startup(thd_gyroscope);
}
