
#ifndef  INCLUDES_H     //��ֹ�ظ����壨INCLUDES_H ��ͷ��
#define  INCLUDES_H

//----------------------------------------------------------------------
//��1�������õ��Ĺ���
#include "user.h"
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
G_VAR_PREFIX uint8_t  gcRecvBuf[MCU_SECTORSIZE];
//���û����ӣ�
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


#endif                  //��ֹ�ظ����壨INCLUDES_H ��β��




