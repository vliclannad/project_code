//======================================================================
//�ļ����ƣ�adc.c
//����ṩ�����ݴ�ѧ������Ƕ��ʽ����(sumcu.suda.edu.cn)
//�汾���£�2019-9-20 V1.1
//�����������������̵�<01_Doc>�ļ�����Readme.txt�ļ�
//======================================================================
#include "adc.h"

//======================================================================
//�������ƣ�adc_init
//���ܸ�Ҫ����ʼ��һ��ADͨ������ɼ�ģʽ
//����˵����Channel��ͨ���ţ���ѡ��Χ��ADC_CHANNEL_VREFINT��
//         ADC_CHANNEL_TEMPSENSOR��ADC_CHANNEL_x(1=<x<=16)��ADC_CHANNEL_VBAT
//         diff�����ѡ��=1(AD_DIFF 1)����֣�=0(AD_SINGLE);
//         ���ˣ�ADC_CHANNEL_VREFINT��ADC_CHANNEL_TEMPSENSOR��ADC_CHANNEL_VBAT
//         ǿ��Ϊ���ˣ�ADC_CHANNEL_x(1=<x<=16)��ѡ���˻��߲��ģʽ
//======================================================================

void adc_init(uint16_t Channel,uint8_t Diff)
{
    //��1������ADCʱ�ӣ�Ƶ��=����ʱ��/4,48MHz��ADCʱ�Ӳ�����14MHz
    RCC->AHB2ENR |= RCC_AHB2ENR_ADCEN;
    ADC1_COMMON->CCR |= ADC_CCR_CKMODE;
    //��2���˳�����״̬��ʹ����ѹ��,ADCĬ�ϴ��ڵ���״̬�Խ��͹���
    ADC1->CR &= ~ADC_CR_DEEPPWD;
    ADC1->CR |= ADC_CR_ADVREGEN;
    //��3��ʹ��ADC����ڲ��ɼ�����
    if(Channel == 0)
    {
        ADC1_COMMON->CCR |= ADC_CCR_VREFEN;  //ʹ�ܲο���ѹ�ɼ�����
    }
    else if(Channel == 17)
    {
        ADC1_COMMON->CCR |= ADC_CCR_TSEN;    //ʹ���¶Ȳɼ�����
    }
    else if(Channel == 18)
    {
        ADC1_COMMON->CCR |= ADC_CCR_VBATEN;  //ʹ�ܻ�׼��ѹ�ɼ�����
    }
    
    //��4����ʼ��ADC���ƼĴ���,�����������λ
    ADC1->CR &= 0x3fffffc0;
    //��5�����˲��ѡ��
    if (Diff)
    {
        BSET(Channel,ADC1->DIFSEL);  
    }
    else
    {
        BCLR(Channel,ADC1->DIFSEL);	
    }
    
    //��6������ADC
    ADC1->CR |= ADC_CR_ADEN;
    //��7�����ò���ʱ��Ϊ12.5��ʱ������
    if((int)Channel >= 0 && (int)Channel <= 9 )
    {
        BCLR(Channel*3,ADC1->SMPR1);
        BSET(Channel*3+1,ADC1->SMPR1);
        BCLR(Channel*3+2,ADC1->SMPR1);
    }
    if((int)Channel >= 10 && (int)Channel <= 18 )
    {
        BCLR((Channel%10)*3,ADC1->SMPR2);
        BSET((Channel%10)*3+1,ADC1->SMPR2);
        BCLR((Channel%10)*3+2,ADC1->SMPR2);
    }
    //��8�����üĴ���CFGR������12λ���Ҷ��롢���ε�ͨ��ת��
    ADC1->CFGR &= 0xffffffe7;         //��������Ϊ12λ
    ADC1->CFGR &= 0xffffffdf;         //���ݶ��뷽ʽ�Ҷ���
    ADC1->CFGR |= ADC_CFGR_DISCEN;    //������ת��ģʽ
    ADC1->CFGR &= ~ADC_CFGR_CONT;     //����ת��ģʽ
    ADC1->CFGR &= ~ADC_CFGR_DISCNUM;  //һ��ͨ��
    ADC1->CFGR &= ~ADC_CFGR_EXTEN;    //��ֹӲ���������
    //��11������ͨ�����г���Ϊ1
    ADC1->SQR1 &= ~ADC_SQR1_L;	   
}

//============================================================================
//�������ƣ�adc_read
//���ܸ�Ҫ����ʼ��һ��ADͨ�������Ųɼ�ģʽ
//����˵����diff�����ѡ��=1(AD_DIFF 1)����֣�=0(AD_SINGLE);
//         ���ˣ�DC_CHANNEL_VREFINT��ADC_CHANNEL_TEMPSENSOR��ADC_CHANNEL_VBAT
//         ǿ��Ϊ���ˣ�ADC_CHANNEL_x(1=<x<=16)��ѡ���˻��߲��ģʽ
//============================================================================
uint16_t adc_read(uint8_t Channel)
{
    uint16_t ADCResult;   //���ڴ��ADֵ
    int i,t;
    ADCResult=0;
    //��1������ADC,ʹ����ѹ��
    ADC1->CR |= ADC_CR_ADEN;
    ADC1->CR |= ADC_CR_ADVREGEN;
    //��2����յ�һ��ת������
    ADC1->SQR1 &= 0xFFFFF83F; 
    //��3����ѡͨ�������һ��ת��������
    ADC1->SQR1 |=((uint32_t)Channel<<6);
    //��4����ʼת��
    ADC1->CR |= ADC_CR_ADSTART;
    //��5���ȴ�ת����ɣ���ȡת�����
    for (i=0;i<=50;i++) __asm("nop");
    for (t = 0; t < 0xFBBB; t++)//��ѯָ������
    {
        //�ж�ת���Ƿ����
        if (BGET(2,ADC1->ISR)==1)  //ת�����
        {
            ADCResult = ADC1->DR;   //��ȡ����,��ת����ɱ�־λ
            break;
        }
    } 
    return ADCResult;
}




////============================================================================
////�������ƣ�TempRegression
////���ܸ�Ҫ���������Ļ����¶�ADֵת��Ϊʵ���¶�
////����˵����tmpAD��ͨ��adc_read�����õ���ADֵ
////�������أ�ʵ���¶�ֵ
////============================================================================
//float TempRegression(uint16_t tmpAD)
//{
//    float v1,v2,S,T;
//    v1 = ((float)tmpAD*3300)/4096;   //ADֵ��Ϊ�������ѹ(mV)
//    v2=3300 - v1;                    //��ѹ�������˵�ѹ(mV)
//    S = v1/v2;                       //��ѹ��
//    T = (1/(log(S)/3950.0 + (1/(273.15 + 25)))) - 273.15 + 0.5;
//    return T;
//}


//============================================================================
//�������ƣ�TempTrans
//���ܸ�Ҫ����������mcu�¶�ADֵת��Ϊʵ���¶�
//����˵����mcu_temp_AD��ͨ��adc_read�����õ���ADֵ
//�������أ�ʵ���¶�ֵ
//============================================================================
float TempTrans(uint16_t mcu_temp_AD)
{
	float mcu_temp_result;
	mcu_temp_result=(float)(55+(100*((float)(mcu_temp_AD) - AD_CAL1))/(AD_CAL2 - AD_CAL1));
	return mcu_temp_result;
}
