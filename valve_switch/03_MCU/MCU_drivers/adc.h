//======================================================================
//�ļ����ƣ�adc.h
//����ṩ��SD-Arm(sumcu.suda.edu.cn)
//�汾���£�20190920-20200420
//����������STM32L431оƬADת��ͷ�ļ�
//�ɼ�����12λ
//======================================================================
#ifndef _ADC_H     //��ֹ�ظ����壨��ͷ��
#define _ADC_H
#include "string.h"
#include "mcu.h"

//ͨ��ת������0-18


//ͨ���Ŷ���
#define ADC_CHANNEL_VREFINT 0     //�ڲ��ο���ѹ��� ��Ҫʹ��VREFINT����  
#define ADC_CHANNEL_1 1      	  //ͨ��1
#define ADC_CHANNEL_2 2           //ͨ��2
#define ADC_CHANNEL_3 3           //ͨ��3 
#define ADC_CHANNEL_4 4           //ͨ��4  
#define ADC_CHANNEL_5 5           //ͨ��5     
#define ADC_CHANNEL_6 6           //ͨ��6    
#define ADC_CHANNEL_7 7           //ͨ��7     
#define ADC_CHANNEL_8 8           //ͨ��8    
#define ADC_CHANNEL_9 9           //ͨ��9     
#define ADC_CHANNEL_10 10         //ͨ��10    
#define ADC_CHANNEL_11 11         //ͨ��11    
#define ADC_CHANNEL_12 12         //ͨ��12   
#define ADC_CHANNEL_13 13         //ͨ��13  
#define ADC_CHANNEL_14 14         //ͨ��14   
#define ADC_CHANNEL_15 15         //ͨ��15   
#define ADC_CHANNEL_16 16         //ͨ��16   
#define ADC_CHANNEL_TEMPSENSOR 17 //�ڲ��¶ȼ�� ��Ҫʹ��TEMPSENSOR
#define ADC_CHANNEL_VBAT 18       //��Դ��� x��Ҫʹ��VBAT 
//���ŵ��˻���ѡ��    
#define AD_DIFF 1                 //�������
#define AD_SINGLE 0               //��������
//�¶Ȳɼ�����AD_CAL2��AD_CAL1
#define AD_CAL2 (*(uint16_t*) 0x1FFF75CA)
#define AD_CAL1 (*(uint16_t*) 0x1FFF75A8)
//======================================================================
//�������ƣ�adc_init
//���ܸ�Ҫ����ʼ��һ��ADͨ������ɼ�ģʽ
//����˵����Channel��ͨ���ţ���ѡ��Χ��ADC_CHANNEL_VREFINT��
//         ADC_CHANNEL_TEMPSENSOR��ADC_CHANNEL_x(1=<x<=16)��ADC_CHANNEL_VBAT
//         diff�����ѡ��=1(AD_DIFF 1)����֣�=0(AD_SINGLE);
//         ���ˣ�ADC_CHANNEL_VREFINT��ADC_CHANNEL_TEMPSENSOR��ADC_CHANNEL_VBAT
//         ǿ��Ϊ���ˣ�ADC_CHANNEL_x(1=<x<=16)��ѡ���˻��߲��ģʽ
//======================================================================
void adc_init(uint16_t Channel,uint8_t Diff);


//============================================================================
//�������ƣ�adc_read
//���ܸ�Ҫ����ʼ��һ��ADͨ�������Ųɼ�ģʽ
//����˵����diff�����ѡ��=1(AD_DIFF 1)����֣�=0(AD_SINGLE);
//         ���ˣ�ADC_CHANNEL_VREFINT��ADC_CHANNEL_TEMPSENSOR��ADC_CHANNEL_VBAT
//         ǿ��Ϊ���ˣ�ADC_CHANNEL_x(1=<x<=16)��ѡ���˻��߲��ģʽ
//============================================================================
uint16_t adc_read(uint8_t Channel);




//============================================================================
//�������ƣ�TempRegression
//���ܸ�Ҫ���������Ļ����¶�ADֵת��Ϊʵ���¶�
//����˵����tmpAD��ͨ��adc_read�����õ���ADֵ
//�������أ�ʵ���¶�ֵ
//============================================================================
float TempRegression(uint16_t tmpAD);


//============================================================================
//�������ƣ�TempTrans
//���ܸ�Ҫ����������mcu�¶�ADֵת��Ϊʵ���¶�
//����˵����mcu_temp_AD��ͨ��adc_read�����õ���ADֵ
//�������أ�ʵ���¶�ֵ
//============================================================================
float TempTrans(uint16_t mcu_temp_AD);



#endif

