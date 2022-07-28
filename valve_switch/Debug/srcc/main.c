#define GLOBLE_VAR
#include "includes.h"
#include "valueType.h"

void main_Dly_ms(uint32_t ms);
int main(void)
{ 
	printf("进入main函数");
	DISABLE_INTERRUPTS;

	int i;
	char mstring[1024];
    gpio_init(LIGHT_GREEN,GPIO_OUTPUT,LIGHT_OFF);
	gpio_init(LIGHT_BLUE,GPIO_OUTPUT,LIGHT_OFF);
	gpio_init(LIGHT_RED,GPIO_OUTPUT,LIGHT_OFF);
	uart_init(UART_User,9600); 
	uart_enable_re_int(UART_User);
	    //LCD初始化、初始界面绘制
	ENABLE_INTERRUPTS;
    LCD_Init();
    LCD_aotu(2,2,238,318,0);
    LCD_ShowString(35,20,BLACK,GRAY,(char *)"test1");
    
    LCD_ShowString(6,90,BLACK,GRAY,(char *)"X angle:");
    LCD_aotu(4,110,236,120,1);
    LCD_ShowString(6,125,BLACK,GRAY,(char *)"Y angle:");
    LCD_aotu(4,145,236,155,1);
    LCD_ShowString(6,160,BLACK,GRAY,(char *)"Z angle:");
    printf("LCD面板初始化化完毕");
    LCD_aotu(4,180,236,190,1);
	printf("串口中断开启");

    printf("准备进入循环");
	while(1)
	{
	    main_Dly_ms(5000);
        for(i=0;i<3;i++)
        {
            angle_R[i]=(sangle[i])/32768*180;
        }
        if(sangle[1]>40)
        {
        gpio_reverse(LIGHT_BLUE);
        }
         LCD_ShowString(65,90,BLACK,GRAY,(uint8_t *)DoubleConvertToStr((double)sangle[0]/32768*180,3,mstring));
   		 LCD_ShowString(65,125,BLACK,GRAY,(uint8_t *)DoubleConvertToStr((double)sangle[1]/32768*180,3,mstring));
  		 LCD_ShowString(65,160,BLACK,GRAY,(uint8_t *)DoubleConvertToStr((double)sangle[2]/32768*180,3,mstring));
            
        printf("x轴角度为：%.3f,y轴角度为%.3f，Z轴角度为%.3f\n",(double)sangle[0]/32768*180,(double)sangle[1]/32768*180,(double)sangle[2]/32768*180);
     }


}
void main_Dly_ms(uint32_t ms)
{
	for(uint32_t i= 0; i < (4800*ms); i++) __asm("nop");
}


