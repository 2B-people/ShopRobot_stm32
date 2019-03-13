#include "include.h"

u16 localnum = 0;
u16 ADC_ConvertedValue[NOFCHANEL];
u16 ADC_JIHE[NOFCHANEL]; //0为左边，1为右路；
u16 ADC_jihe[NOFCHANEL][20] = {0};

//ADC采集用

void ADC_GPIO_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    //打开ADC_IO端口时钟
    RCC_APB2PeriphClockCmd(ADC_GPIO_CLK, ENABLE);

    //配置ADC_IO引脚模式
    GPIO_InitStructure.GPIO_Pin = ADC_PIN1 | ADC_PIN2| ADC_PIN3| ADC_PIN4;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;

    //初始化ADC IO
    GPIO_Init(ADC_PORT, &GPIO_InitStructure);
}

void ADCx_Mode_Init(void)
{
    DMA_InitTypeDef DMA_InitStructure;
    ADC_InitTypeDef ADC_InitStructure;

    //打开DMA时钟
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
    //打开ADC时钟
    RCC_APB2PeriphClockCmd(ADCx_CLK, ENABLE);

    /*------------------DMA模式配置--------------------*/
    //复位DMA控制器
    DMA_DeInit(ADC_DMA_CHANNEL);
    //配置DMA初始化结构体
    //外设基址为：ADC数据寄存器地址
    DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)(&(ADCx->DR));
    //储存器地址
    DMA_InitStructure.DMA_MemoryBaseAddr = (u32)ADC_ConvertedValue;
    //数据来自外设
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
    //缓冲区大小，应该等于数据目的地的大小
    DMA_InitStructure.DMA_BufferSize = NOFCHANEL;
    //外部寄存器只有一个，地址不用递增
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    //储存器地址递增
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    //外设数据大小为半字，2字节
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
    //内存数据大小也为半字
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
    //循环传输模式
    DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
    //DMA传输通道优先级为高，当使用一个DMA通道时，优先级设置不受影响
    DMA_InitStructure.DMA_Priority = DMA_Priority_High;
    //禁止存储器到存储器模式，而用从外设到存储器
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
    //初始化DMA
    DMA_Init(ADC_DMA_CHANNEL, &DMA_InitStructure);
    //使能DMA通道
    DMA_Cmd(ADC_DMA_CHANNEL, ENABLE);
    /*-------------ADC模式配置---------------------*/
    //只使用了一个ADC，属于单模式
    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
    //扫描模式
    ADC_InitStructure.ADC_ScanConvMode = ENABLE;
    //连续转换模式
    ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
    //不用外部触发，软件开启
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
    //转换结果右对齐
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
    //转换通道个数
    ADC_InitStructure.ADC_NbrOfChannel = NOFCHANEL;
    //初始化ADC
    ADC_Init(ADCx, &ADC_InitStructure);
    //配置ADC通道的转换顺序和采样时间
    ADC_RegularChannelConfig(ADCx, ADC_CHANNEL1, 1,
                             ADC_SampleTime_71Cycles5);
    ADC_RegularChannelConfig(ADCx, ADC_CHANNEL2, 2,
                             ADC_SampleTime_71Cycles5);
	  ADC_RegularChannelConfig(ADCx, ADC_CHANNEL3, 3,
                             ADC_SampleTime_71Cycles5);
    ADC_RegularChannelConfig(ADCx, ADC_CHANNEL4, 4,
                             ADC_SampleTime_71Cycles5);
    //使能ADC DMA请求
    ADC_DMACmd(ADCx, ENABLE);
    //开启ADC，并开始转换
    ADC_Cmd(ADCx, ENABLE);
    //初始化ADC校准寄存器
    ADC_ResetCalibration(ADCx);
    //等待
    while (ADC_GetResetCalibrationStatus(ADCx))
        ;
    //ADC开始校准
    ADC_StartCalibration(ADCx);
    //等待校准完成
    while (ADC_GetCalibrationStatus(ADCx))
        ;
    //软件触发adc转换
    ADC_SoftwareStartConvCmd(ADCx, ENABLE);
}

void adcjihe(void) //ADC集合
{
    char i;
    u32 sum1 = 0, sum2 = 0 ,sum3=0 ,sum4=0;
    //if (pidjud)
    {
        for (i = 19; i > 0; i--)
        {
            if (i == 1)
            {
                ADC_jihe[0][i] = ADC_ConvertedValue[0];
                ADC_jihe[1][i] = ADC_ConvertedValue[1];
								ADC_jihe[2][i] = ADC_ConvertedValue[2];
                ADC_jihe[3][i] = ADC_ConvertedValue[3];
            }
            else
            {
                ADC_jihe[0][i] = ADC_jihe[0][i - 1];
                ADC_jihe[1][i] = ADC_jihe[1][i - 1];
								ADC_jihe[2][i] = ADC_jihe[2][i - 1];
                ADC_jihe[3][i] = ADC_jihe[3][i - 1];
            }
        }
        for (i = 1; i < 20; i++)
        {
            sum1 += ADC_jihe[0][i];
            sum2 += ADC_jihe[1][i];
						sum3 += ADC_jihe[2][i];
            sum4 += ADC_jihe[3][i];
        }
        ADC_JIHE[0] = (u16)(sum1 / 19.0);
        ADC_JIHE[1] = (u16)(sum2 / 19.0);
				ADC_JIHE[2] = (u16)(sum3 / 19.0);
        ADC_JIHE[3] = (u16)(sum4 / 19.0);
    }
}




void huiductrlinit(void)
{
    ADC_GPIO_Init();
    ADCx_Mode_Init();
}
