#include "remote.h"
uint8_t sbus_rx_buffer[RC_FRAME_LENGTH]; //double sbus rx buffer to save data
REMOTE RC_CtrlData;
DMA_InitTypeDef DMA_InitStructure;
extern double required_vel;
void RC_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	//使能USART1，GPIOA时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
 	USART_DeInit(USART2);  //复位串口1

    //USART1_RX	  PA.3
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
    GPIO_Init(GPIOA, &GPIO_InitStructure);  //初始化PA10

  
   //USART 初始化设置

	USART_InitStructure.USART_BaudRate = 100000;//一般设置为9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_Even;//偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式

    USART_Init(USART2, &USART_InitStructure); //初始化串口
    //l USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//开启中断
	//USART_ITConfig(USART1, USART_IT_IDLE, ENABLE); 
    USART_Cmd(USART2, ENABLE);                    //使能串口 
		
		
		RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);	//使能DMA传输
		USART_DMACmd(USART2,USART_DMAReq_Rx,DISABLE);
		DMA_DeInit(DMA1_Channel6);   //将DMA的通道1寄存器重设为缺省值
		DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)&USART2->DR;  //DMA外设ADC基地址
		DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)sbus_rx_buffer;  //DMA内存基地址
		DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;  //数据传输方向
		DMA_InitStructure.DMA_BufferSize = 18;  //DMA通道的DMA缓存的大小
		DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;  //外设地址寄存器不变
		DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;  //内存地址寄存器递增
		DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;  //数据宽度为8位
		DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte; //数据宽度为8位
		
		DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;//工作在循环模式下
		DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh; //DMA通道 x拥有中优先级 
		DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;  //DMA通道x没有设置为内存到内存传输
		DMA_Init(DMA1_Channel6, &DMA_InitStructure);  //根据DMA_InitStruct中指定的参数初始化DMA的通道USART1_Tx_DMA_Channel所标识的寄存器
		DMA_ClearFlag(DMA1_FLAG_TC6); //清除DMA接收完成标志
		DMA_ITConfig(DMA1_Channel6, DMA_IT_TC, ENABLE);//DMA5传输完成中断
		USART_DMACmd(USART2,USART_DMAReq_Rx,ENABLE);//使能USART2的接收DMA请求
		

	NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel6_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	DMA_Cmd(DMA1_Channel6, ENABLE);         	
		
		
		
		
		
		
		
		
		
		
}

/******************************************************************************
* @fn RemoteDataProcess
** @brief resolution rc protocol data.
* @pData a point to rc receive buffer.
* @return None.
* @note RC_CtrlData is a global variable.you can deal with it in other place.
*/
void RemoteDataProcess(uint8_t *pData)
{
	if(pData == NULL)
	{
		return;
	}
	RC_CtrlData.ch0 = ((int16_t)pData[0] | ((int16_t)pData[1] << 8)) & 0x07FF;
	RC_CtrlData.ch1 = (((int16_t)pData[1] >> 3) | ((int16_t)pData[2] << 5))& 0x07FF;
	RC_CtrlData.ch2 = (((int16_t)pData[2] >> 6) | ((int16_t)pData[3] << 2) |((int16_t)pData[4] << 10)) & 0x07FF;
	RC_CtrlData.ch3 = (((int16_t)pData[4] >> 1) | ((int16_t)pData[5]<<7)) &0x07FF;
	RC_CtrlData.s1 = ((pData[5] >> 4) & 0x000C) >> 2;
	RC_CtrlData.s2 = ((pData[5] >> 4) & 0x0003);
//	if(RC_CtrlData.ch0<1400&&RC_CtrlData.ch0>600)
//		required_vel=(double)(RC_CtrlData.ch0 -1024)*0.0025;	

}


void DMA1_Channel6_IRQHandler(void)
{
    if(DMA_GetITStatus(DMA1_IT_TC6)) //通道5传输完成中断TC 还有传输 过半中断HT 错误中断TE 全局中断GL
     {
        DMA_ClearITPendingBit(DMA1_IT_GL6);    //清除全部中断标志
				RemoteDataProcess(sbus_rx_buffer);
     }
}
