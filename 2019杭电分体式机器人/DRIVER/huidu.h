#ifndef  __HUIDU_H
#define  __HUIDU_H

#include "sys.h"
//左右计次


//计次灰度引脚定义
#define      huidu1                          PEin(2)
#define      huidu2                          PEin(3)                         
//函数
void huidu_init(void);
void adcjihe1(void);
void classtime(void);



//ADC宏定义
#define       ADCx                         ADC1
#define       ADCx_CLK                     RCC_APB2Periph_ADC1

#define       ADC_GPIO_CLK                 RCC_APB2Periph_GPIOC
#define       ADC_PORT                     GPIOB

//转化通道个数
#define       NOFCHANEL                    2

#define       ADC_PIN1                     GPIO_Pin_0
#define       ADC_CHANNEL1                 ADC_Channel_10
#define       ADC_PIN2                     GPIO_Pin_1
#define       ADC_CHANNEL2                 ADC_Channel_11

//ADC1对应DMA1通道1，ADC3对应DMA2通道5，ADC2没有DMA功能
#define       ADC_DMA_CHANNEL              DMA1_Channel1

//转换用,将(0~4096)的模拟量变成0到3.3V的实际电压
#define       CONVERT a                    (float)a/4096*3.3

//函数
void  ADC_GPIO_Init(void);
void  ADCx_Mode_Init(void);
void  huiductrlinit(void);
void  adcjihe(void);

//需要一个全局变量ADC_ConvertedValue[],
//还有一个main函数里的ADC_ConvertedValueLocal[]
extern u16  ADC_JIHE[2]; //0为左边，1为右路；


#endif


