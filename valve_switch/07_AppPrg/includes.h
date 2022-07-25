
#ifndef  INCLUDES_H     //��ֹ�ظ����壨INCLUDES_H ��ͷ��
#define  INCLUDES_H

//----------------------------------------------------------------------
//��1�������õ��Ĺ���
#include "user.h"
#include <OsFunc.h>
#include "NumToStr.h"
#include "lcd.h"
#include "adc.h"

//----------------------------------------------------------------------
//��2��ȫ��ʹ�õĺ곣����


//----------------------------------------------------------------------
//��3���Զ�����������

//----------------------------------------------------------------------

//��4������ȫ�ֱ����������淶��ע2��
//���������궨��ȫ�ֱ���ǰ׺G_VAR_PREFIX��ʵ��ԭ���ע3��
#ifdef GLOBLE_VAR              //GLOBLE_VAR��main.c�ļ����к궨��
  #define G_VAR_PREFIX         //ǰ׺G_VAR_PREFIX����Ϊ��
#else                          //GLOBLE_VAR�ڷ�main.c�ļ����޶���
  #define G_VAR_PREFIX extern  //ǰ׺G_VAR_PREFIX����Ϊ"extern"
#endif
//���ڴ�����ȫ�ֱ�����

//��ϵͳ������
G_VAR_PREFIX vuint16_t gcRecvLen;
G_VAR_PREFIX vuint16_t gcRecvDCLen;
G_VAR_PREFIX vuint8_t  gcRecvBuf[MCU_SECTORSIZE];
//���û����ӣ�
G_VAR_PREFIX float acc_R[3];
G_VAR_PREFIX float gyro_R[3];
G_VAR_PREFIX float angle_R[3];

G_VAR_PREFIX uint8_t str_acc[3];
G_VAR_PREFIX uint8_t str_gyro[3];
G_VAR_PREFIX uint8_t str_angle[3];




// JY60�ṹ��
typedef struct SAcc
{
	short a[3];
	short T;
};
typedef struct SGyro
{
	short w[3];
	short T;
};
typedef struct SAngle
{
	short Angle[3];
	short T;
};


 
char YAWCMD[3] = {0XFF,0XAA,0X52};
char ACCCMD[3] = {0XFF,0XAA,0X67};
char SLEEPCMD[3] = {0XFF,0XAA,0X60};
char UARTMODECMD[3] = {0XFF,0XAA,0X61};
char IICMODECMD[3] = {0XFF,0XAA,0X62};



G_VAR_PREFIX  rt_thread_t thd_lcdshow;
G_VAR_PREFIX  rt_thread_t thd_gyroscope;
//�̺߳�������
void app_init(void);
void thread_lcdshow();
void thread_gyroscope();


#define delay_ms(x)  rt_thread_delay(x)
//----------------------------------------------------------------------


#endif                  //��ֹ�ظ����壨INCLUDES_H ��β��




