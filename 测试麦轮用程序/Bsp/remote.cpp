<<<<<<< HEAD
#include "remote.h"
#include "stdio.h"
volatile uint8_t sbus_rx_buffer[2][RC_FRAME_LENGTH]; //double sbus rx buffer to save data
REMOTE RC_CtrlData;

void RC_Init(void)
{
	

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1 ,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA ,ENABLE);
	DMA_InitTypeDef DMA_InitStructure;
	/*CONFIG GPIO*/
	GPIO_InitTypeDef gpio;
	USART_InitTypeDef usart2;
	
	gpio.GPIO_Pin = GPIO_Pin_3 ;
	gpio.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &gpio);

	USART_DeInit(USART2);
	usart2.USART_BaudRate = 100000;
	usart2.USART_WordLength = USART_WordLength_8b;
	usart2.USART_StopBits = USART_StopBits_1;
	usart2.USART_Parity = USART_Parity_Even;
	usart2.USART_Mode = USART_Mode_Rx;
	usart2.USART_HardwareFlowControl = USART_HardwareFlowControl_None;USART_Init(USART2,&usart2);
	USART_Cmd(USART2,ENABLE);
	USART_DMACmd(USART2,USART_DMAReq_Rx,ENABLE);

/*CONFIG NVIC*/
	
	NVIC_InitTypeDef nvic;
	nvic.NVIC_IRQChannel = DMA1_Channel5_IRQn;
	nvic.NVIC_IRQChannelPreemptionPriority = 1;
	nvic.NVIC_IRQChannelSubPriority = 1;
	nvic.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&nvic);
	
	
	  /* DMA1 Channel6 (triggered by USART2 Rx event) Config */

  DMA_DeInit(DMA1_Channel6);
  DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&(USART2->DR);// 初始化外设地址，相当于“哪家快递”  
  DMA_InitStructure.DMA_MemoryBaseAddr =(uint32_t)&sbus_rx_buffer[0][0];// 内存地址，相当于几号柜
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;//外设作为数据来源，即为收快递
  DMA_InitStructure.DMA_BufferSize = RC_FRAME_LENGTH ;// 缓存容量，即柜子大小
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable; // 外设地址不递增，即柜子对应的快递不变
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;// 内存递增
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte; //外设字节宽度，即快递运输快件大小度量（按重量算，还是按体积算） 
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;// 内存字节宽度，即店主封装快递的度量(按重量，还是按体质进行封装)
  DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;//循环存储
  DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;// 优先级很高，对应快递就是加急
  DMA_InitStructure.DMA_M2M = DMA_M2M_Disable; // 内存与外设通信，而非内存到内存 
  DMA_Init(DMA1_Channel6, &DMA_InitStructure);// 把参数初始化，即拟好与快递公司的协议
	USART_ITConfig(USART2, USART_IT_IDLE, ENABLE);
  DMA_Cmd(DMA1_Channel6, ENABLE);// 启动DMA，即与快递公司签订合同，正式生效	
  USART_DMACmd(USART2, USART_DMAReq_Rx, ENABLE);// 使能DMA串口接受请求
}

/******************************************************************************
* @fn RemoteDataProcess
** @brief resolution rc protocol data.
* @pData a point to rc receive buffer.
* @return None.
* @note RC_CtrlData is a global variable.you can deal with it in other place.
*/
void RemoteDataProcess(volatile uint8_t *pData)
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
	
	
		


	
}



/******************************************************************************
* @fn USART2_IRQHandler
*
* @brief USART2 irq, we are care of ilde interrupt that means receiving the
one frame datas is finished.
*
* @return None.
*
* @note This code is fully tested on STM32F405RGT6 Platform, You can port
it
* to the other platform.
*/
extern "C" void USART2_IRQHandler (void)
{
	if(USART_GetITStatus(USART2, USART_IT_IDLE) != RESET)
	{//clear the idle pending flag
		(void)USART2->SR;
		(void)USART2->DR;
		//Target is Memory0
		if(DMA_GetCurrDataCounter(DMA1_Channel6) == 0)
		{
			DMA_Cmd(DMA1_Channel6, DISABLE);
			DMA1_Channel6->CNDTR = (uint16_t)RC_FRAME_LENGTH; //relocate thedma memory pointer to the beginning position
			//DMA1_Channel6->CCR |= (uint32_t)(DMA_SxCR_CT); //enable the current selected memory is Memory 1
			DMA_SetCurrDataCounter(DMA1_Channel6,1);
			DMA_Cmd(DMA1_Channel6, ENABLE);
			if(DMA_GetCurrDataCounter(DMA1_Channel6) == 0) //ensure received complete frame data.
			{
				RemoteDataProcess(sbus_rx_buffer[0]);
			}
		}
	//Target is Memory1
		else
		{
			DMA_Cmd(DMA1_Channel6, DISABLE);
			DMA1_Channel6->CNDTR = (uint16_t)RC_FRAME_LENGTH; //relocate the dma memory pointer to the beginning position
			//DMA1_Channel6->CCR &= ~(uint32_t)(DMA_SxCR_CT); //enable the current selected memory is Memory 0
			DMA_SetCurrDataCounter(DMA1_Channel6,0);
			DMA_Cmd(DMA1_Channel6, ENABLE);
			if(DMA_GetCurrDataCounter(DMA1_Channel6) == 0)
			{
				RemoteDataProcess(sbus_rx_buffer[1]);
			}
		}
	}
}
=======
#include "remote.h"
extern "C"{
#include "stdio.h"
}
#include "control.h"
uint8_t sbus_rx_buffer[RC_FRAME_LENGTH]; //double sbus rx buffer to save data
REMOTE RC_CtrlData;
DMA_InitTypeDef DMA_InitStructure;
extern double required_angular_vel;
extern double required_linear_vel_x ;
extern double required_linear_vel_y ;
void RC_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	//使能USART1，GPIOA时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
 	USART_DeInit(USART2);  //复位串口1

    //USART2_RX	  PA.3
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
		DMA_ClearFlag(DMA1_FLAG_TC5); //清除DMA接收完成标志
		DMA_ITConfig(DMA1_Channel6, DMA_IT_TC, ENABLE);//DMA5传输完成中断
		USART_DMACmd(USART2,USART_DMAReq_Rx,ENABLE);//使能USART1的接收DMA请求
		
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel6_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
			//DMA_Cmd(DMA1_Channel5, ENABLE); //正式允许DMA
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
	
	
	if(RC_CtrlData.ch0<1500||RC_CtrlData.ch0>500)
		required_linear_vel_x =	(double)(RC_CtrlData.ch0 -1024)*0.0025;
	else
		required_linear_vel_x =	(double)(RC_CtrlData.ch0 -1024)*0.0045;
	if(RC_CtrlData.ch1<1400||RC_CtrlData.ch1>500)
		required_linear_vel_y =	(double)(RC_CtrlData.ch1 -1024)*0.0025;
	else
		required_linear_vel_y =	(double)(RC_CtrlData.ch1 -1024)*0.0045;
	
	if(RC_CtrlData.ch2<1400||RC_CtrlData.ch2>500)
		required_angular_vel =	-(double)(RC_CtrlData.ch2 -1024)*0.0025;
	else
		required_angular_vel =	-(double)(RC_CtrlData.ch2 -1024)*0.0045;
	
	
	
	
	if(RC_CtrlData.ch0>1684||RC_CtrlData.ch1>1684||RC_CtrlData.ch2>1684||RC_CtrlData.ch3>1684||RC_CtrlData.s1>3||RC_CtrlData.s2>3||RC_CtrlData.ch0<364||RC_CtrlData.ch1<364||RC_CtrlData.ch2<364||RC_CtrlData.ch3<364||RC_CtrlData.s1<1||RC_CtrlData.s2<1)
		stop_base();
	
	if(required_linear_vel_x>=1)
		required_linear_vel_x=1;
	if(required_linear_vel_y>=1)
		required_linear_vel_y=1;
	if(required_angular_vel>=3)
		required_angular_vel=3;
}


extern "C" void DMA1_Channel6_IRQHandler(void)
{
    if(DMA_GetITStatus(DMA1_IT_TC6)) //通道5传输完成中断TC 还有传输 过半中断HT 错误中断TE 全局中断GL
     {
//       MYDMA_Disable(DMA1_Channel5);
        DMA_ClearITPendingBit(DMA1_IT_GL6);    //清除全部中断标志
//			DMA_InitStructure.DMA_BufferSize = 18u; 
//		       

//			DMA_InitStructure.DMA_MemoryBaseAddr = (u32)&sbus_rx_buffer[0];
//			DMA_Init(DMA1_Channel5, &DMA_InitStructure);
				RemoteDataProcess(sbus_rx_buffer);
		

     }
}
>>>>>>> d13f5f0ab27e128bee545c36e70a70630e8c91e1
