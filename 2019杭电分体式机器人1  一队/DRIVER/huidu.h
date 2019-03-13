#ifndef  __HUIDU_H
#define  __HUIDU_H

#include "sys.h"
//左右计次


                       
//函数
void adcjihe1(void);
void classtime(void);




//函数
void  ADC_GPIO_Init(void);
void  ADCx_Mode_Init(void);
void  huiductrlinit(void);
void  adcjihe(void);

//需要一个全局变量ADC_ConvertedValue[],
//还有一个main函数里的ADC_ConvertedValueLocal[]
extern u16  ADC_JIHE[NOFCHANEL]; //0为左边，1为右路；

extern u16 ADC_ConvertedValue[NOFCHANEL];
#endif


