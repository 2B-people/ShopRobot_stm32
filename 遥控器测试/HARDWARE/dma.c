#include "dma.h"
void MDMA_Init()
{
	// DMA Rx
	USART_DMACmd(USART1,USART_DMAReq_Rx,ENABLE);  
	DMA_Cmd(DMA1_Channel5,DISABLE);
	DMA_InitStruct.DMA_PeripheralBaseAddr = (u32)(&USART1->DR);
	DMA_InitStruct.DMA_MemoryBaseAddr = (u32)RxBuf0;
	DMA_InitStruct.DMA_DIR = DMA_DIR_PeripheralSRC;
	DMA_InitStruct.DMA_BufferSize = 10;
	DMA_InitStruct.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStruct.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStruct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	DMA_InitStruct.DMA_MemoryDataSize = DMA_PeripheralDataSize_Byte;
	DMA_InitStruct.DMA_Mode = DMA_Mode_Circular;
	DMA_InitStruct.DMA_Priority = DMA_Priority_High;
	DMA_InitStruct.DMA_M2M = DMA_M2M_Disable;
	DMA_Init(DMA1_Channel5,&DMA_InitStruct);
	DMA_Cmd(DMA1_Channel5,ENABLE);
	DMA_ITConfig(DMA1_Channel5,DMA_IT_TC,ENABLE);
    NVIC_InitStruct.NVIC_IRQChannel = DMA1_Channel5_IRQn;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStruct);

    //ENABLE DMA TX ISR
    DMA_ITConfig(DMA1_Channel4,DMA_IT_TC,ENABLE);
    NVIC_InitStruct.NVIC_IRQChannel = DMA1_Channel4_IRQn;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 2;
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStruct);
}