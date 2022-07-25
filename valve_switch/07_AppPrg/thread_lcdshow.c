#include "includes.h"

void thread_lcdshow()
{
    while(1)
    {
        int i;
        int r=55;//»­Ô²µÄ°ë¾¶
        delay_ms(1000);
        if(gpio_get(LIGHT_BLUE)==0&&gpio_get(LIGHT_GREEN)==1&&gpio_get(LIGHT_RED)==1)
        {
            LCD_ShowString(6,160,BLACK,GRAY,(char *)"Ð¡µÆ×´Ì¬:À¶µÆ¿ª");
            for(i=1;i<=r;i++)
            {
                LCD_DrawCircle(120,255,i,BLUE);
            }
            LCD_DrawCircle(120,255,55,BLUE);
        }
        if(gpio_get(LIGHT_BLUE)==1&&gpio_get(LIGHT_GREEN)==0&&gpio_get(LIGHT_RED)==1)
        {
            LCD_ShowString(6,160,BLACK,GRAY,(char *)"Ð¡µÆ×´Ì¬:ÂÌµÆ¿ª");
            for(i=1;i<=r;i++)
            {
                LCD_DrawCircle(120,255,i,GREEN);
            }
        }
        if(gpio_get(LIGHT_BLUE)==1&&gpio_get(LIGHT_GREEN)==1&&gpio_get(LIGHT_RED)==0)
        {
            LCD_ShowString(6,160,BLACK,GRAY,(char *)"Ð¡µÆ×´Ì¬:ºìµÆ¿ª");
            for(i=1;i<=r;i++)
            {
                LCD_DrawCircle(120,255,i,RED);
            }
        }
        if(gpio_get(LIGHT_BLUE)==1&&gpio_get(LIGHT_GREEN)==1&&gpio_get(LIGHT_RED)==1)
        {
            LCD_ShowString(6,160,BLACK,GRAY,(char *)"Ð¡µÆ×´Ì¬:¹Ø      ");
            for(i=1;i<=r;i++)
            {
                LCD_DrawCircle(120,255,i,BLACK);
            }
        }

    }
    



}