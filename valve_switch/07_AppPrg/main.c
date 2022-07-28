#define GLOBLE_VAR
#include "includes.h"

void main_Dly_ms(uint32_t ms);
int main(void)
{
	printf("进入main函数");
	DISABLE_INTERRUPTS;

	int i;
    gpio_init(LIGHT_GREEN,GPIO_OUTPUT,LIGHT_OFF);
	gpio_init(LIGHT_BLUE,GPIO_OUTPUT,LIGHT_OFF);
	gpio_init(LIGHT_RED,GPIO_OUTPUT,LIGHT_OFF);
	uart_init(UART_User,9600); 
	    //LCD初始化、初始界面绘制
    /*LCD_Init();
    LCD_aotu(2,2,238,318,0);
    LCD_ShowString(35,20,BLACK,GRAY,(char *)"test1");
    
    LCD_ShowString(6,90,BLACK,GRAY,(char *)"X angle:");
    LCD_aotu(4,110,236,120,1);
    LCD_ShowString(6,125,BLACK,GRAY,(char *)"Y angle:");
    LCD_aotu(4,145,236,155,1);
    LCD_ShowString(6,160,BLACK,GRAY,(char *)"Z angle:");
    LCD_aotu(4,180,236,190,1);*/
	uart_enable_re_int(UART_User);
    ENABLE_INTERRUPTS;
	while(1)
	{
	    main_Dly_ms(5000);
		for(i=0;i<3;i++)//X,Y,Z三轴加速度处理
        {
            acc_R[i]=sacc[i]/32768*16;
        }
        for(i=0;i<3;i++)//X,Y,Z三轴角速度处理
        {
            gyro_R[i]=sgyro[i]/32768*2000;
        }
        for(i=0;i<3;i++)//X,Y,Z三轴角度处理
        {
            angle_R[i]=sangle[i]/32768*180;
        }
        printf("%d",gcRecvBuf[0]);
        printf("x轴角度为：%f,y轴角度为%f，Z轴角度为%f\n",angle_R[0],angle_R[1],angle_R[2]);
     }
    //LCD_ShowString(65,90,BLACK,GRAY,(uint8_t *)DoubleConvertToStr(acc_R[0],2,mString));
    //LCD_ShowString(65,125,BLACK,GRAY,(uint8_t *)DoubleConvertToStr(acc_R[1],2,mString));
   // LCD_ShowString(65,160,BLACK,GRAY,(uint8_t *)DoubleConvertToStr(acc_R[2],2,mString));
    main_Dly_ms(100);

}
void main_Dly_ms(uint32_t ms)
{
	for(uint32_t i= 0; i < (4800*ms); i++) __asm("nop");
}


