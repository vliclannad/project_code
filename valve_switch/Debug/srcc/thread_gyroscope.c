#include "includes.h"
#include "valueType.h"

void thread_gyroscope()
{
    int i;
    while(1)
    {
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
        for(i=0;i<3;i++)
        {
            *DoubleConvertToStr(acc_R[i],2,str_acc[i]);
        }
         for(i=0;i<3;i++)
        {
            *DoubleConvertToStr(gyro_R[i],2,str_gyro[i]);
        }
         for(i=0;i<3;i++)
        {
            *DoubleConvertToStr(angle_R[i],2,str_angle[i]);
        }
    }

}