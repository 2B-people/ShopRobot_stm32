#include "las_masure.h"
uint16_t USART_RX_STA=0;
uint16_t USART_RX_NUM=0;
uint8_t MEASURE_BUF[5];
uint8_t Distance_data[5];
uint8_t USART3_BUFF[8];
uint8_t las_mode;

void las_Init()
{
		USART_InitTypeDef USART_InitStructure;  
    NVIC_InitTypeDef NVIC_InitStructure;   
    GPIO_InitTypeDef GPIO_InitStructure;    //声明一个结构体变量，用来初始化GPIO  
		DMA_InitTypeDef DMA_InitStructure;	
		
    //使能串口的RCC时钟  
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB , ENABLE); //使能UART3所在GPIOB的时钟  
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);  
		USART_DeInit(USART3);
    //串口使用的GPIO口配置  
    // Configure USART3 Rx (PB.11) as input floating    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;  
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;  
    GPIO_Init(GPIOB, &GPIO_InitStructure);  

    // Configure USART3 Tx (PB.10) as alternate function push-pull  
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;  
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  
    GPIO_Init(GPIOB, &GPIO_InitStructure);  
	
		    //配置串口  
    USART_InitStructure.USART_BaudRate = 115200;  
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;  
    USART_InitStructure.USART_StopBits = USART_StopBits_1;  
    USART_InitStructure.USART_Parity = USART_Parity_No;  
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;  
    USART_InitStructure.USART_Mode = USART_Mode_Rx ;//只需要接受，不需要发送  
		
		

    USART_Init(USART3, &USART_InitStructure);//配置串口3 
   
    USART_Cmd(USART3, ENABLE);//使能串口3  
		
		
		
		RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);                      //使能DMA1时钟  
		USART_DMACmd(USART3, USART_DMAReq_Rx, DISABLE);  //使能串口3 DMA功能

		DMA_DeInit(DMA1_Channel3);                                              //初始化DMA1通道3  串口3接收通道
		DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)&USART3->DR;                  //串口3接收数据的地址
		DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)USART3_BUFF;      //数据存放的复制
		DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;                      //数据传送方向  串口3作为数据源
		DMA_InitStructure.DMA_BufferSize = 8;                    //接收数据个数       
		DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;        //外围设备 串口3 地址不递增
		DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;                 // DMA存储地址递增
		DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte; //外围设备 串口3 数据宽度 8bits
		DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;         //DMA存储 数据宽度 8bits
		DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;                         //循环获取数据
		DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;                   //串口3通道优先为中等
		DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;                            //关闭内存到内存
		DMA_Init(DMA1_Channel3, &DMA_InitStructure);
		DMA_ClearFlag(DMA1_FLAG_TC3); //清除DMA接收完成标志
		DMA_ITConfig(DMA1_Channel3, DMA_IT_TC, ENABLE);//DMA5传输完成中断
		USART_DMACmd(USART3,USART_DMAReq_Rx,ENABLE);//使能USART2的接收DMA请求
		 		
		NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel3_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x03;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);
		DMA_Cmd(DMA1_Channel3, ENABLE);         	
}


void las_measure(uint8_t *Distance_data)
{
	static uint16_t distance;
	static uint16_t strength;
	distance&=0X0000;
	distance|=(((int16_t)Distance_data[2])&0x00FF);
	distance|=((((int16_t)Distance_data[3])<<8)&0xFF00);
	strength&=0X0000;
	strength|=(((int16_t)Distance_data[4])&0x00FF);
	strength|=((((int16_t)Distance_data[5])<<8)&0xFF00);
	
	
	if(strength>20&&strength<2000&&distance>=30&&distance<=1200)		//只有当信号在一定强度内，数据才是可信的
	{
		Distance=distance;
	}
}
	

//void USART3_IRQHandler(void)                    //串口3中断服务程序
//{
//    static uint8_t Res;
//    if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)  //接收中断
//		{
//			
//			Res=USART_ReceiveData(USART3);
//			if((USART_RX_STA&0x2000)!=0)		//接受距离数据
//			{
//				MEASURE_BUF[USART_RX_NUM++]=Res;
//				if(USART_RX_NUM==5)
//				{
//					Distance_data[0]=MEASURE_BUF[0];
//					Distance_data[1]=MEASURE_BUF[1];
//					Distance_data[2]=MEASURE_BUF[2];
//					Distance_data[3]=MEASURE_BUF[3];
//					Distance_data[4]=MEASURE_BUF[4];
//					USART_RX_NUM=0;
//					USART_RX_STA=0;
//				}
//			}
//			else if((USART_RX_STA&0x1000)!=0)//第二个开始位
//			{
//				if(Res==0x59)USART_RX_STA|=0x2000;
//				else USART_RX_STA=0;
//			}
//			else if(Res==0x59)USART_RX_STA|=0x1000;//第一个开始位
//		}
//		USART_ClearITPendingBit(USART3, USART_IT_RXNE);

//}
void DMA1_Channel3_IRQHandler(void)
{
		  if(DMA_GetITStatus(DMA1_IT_TC3)) //通道5传输完成中断TC 还有传输 过半中断HT 错误中断TE 全局中断GL
     {
        DMA_ClearITPendingBit(DMA1_IT_GL3);    //清除全部中断标志
				las_measure(USART3_BUFF);
     }
}

