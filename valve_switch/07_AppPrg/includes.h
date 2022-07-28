
#ifndef  INCLUDES_H     //防止重复定义（INCLUDES_H 开头）
#define  INCLUDES_H

//----------------------------------------------------------------------
//（1）包含用到的构件
#include "user.h"
#include "NumToStr.h"
#include "lcd.h"
#include "adc.h"

//----------------------------------------------------------------------
//（2）全局使用的宏常数。


//----------------------------------------------------------------------
//（3）自定义数据类型

//----------------------------------------------------------------------

//（4）声明全局变量。命名规范见注2。
//【不动】宏定义全局变量前缀G_VAR_PREFIX。实现原理见注3。
#ifdef GLOBLE_VAR              //GLOBLE_VAR在main.c文件中有宏定义
  #define G_VAR_PREFIX         //前缀G_VAR_PREFIX定义为空
#else                          //GLOBLE_VAR在非main.c文件中无定义
  #define G_VAR_PREFIX extern  //前缀G_VAR_PREFIX定义为"extern"
#endif
//（在此增加全局变量）

//（系统保留）
G_VAR_PREFIX vuint16_t gcRecvLen;
G_VAR_PREFIX vuint16_t gcRecvDCLen;
G_VAR_PREFIX uint8_t  gcRecvBuf[MCU_SECTORSIZE];
//（用户增加）
G_VAR_PREFIX double acc_R[3];
G_VAR_PREFIX double gyro_R[3];
G_VAR_PREFIX double angle_R[3];

G_VAR_PREFIX int16_t sacc[3];
G_VAR_PREFIX int16_t sgyro[3];
G_VAR_PREFIX int16_t sangle[3];

G_VAR_PREFIX uint8_t sangle_test[6];

G_VAR_PREFIX uint8_t str_acc[3];
G_VAR_PREFIX uint8_t str_gyro[3];
G_VAR_PREFIX uint8_t str_angle[3];


 








//----------------------------------------------------------------------


#endif                  //防止重复定义（INCLUDES_H 结尾）




