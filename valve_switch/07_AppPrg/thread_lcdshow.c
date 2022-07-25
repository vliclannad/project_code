#include "includes.h"

void thread_lcdshow()
{
    while(1)
    {
        LCD_ShowString(65,90,BLACK,GRAY,str_acc[0]);
        LCD_ShowString(65,125,BLACK,GRAY,str_acc[1]);
        LCD_ShowString(65,160,BLACK,GRAY,str_acc[2]);
    }
    



}