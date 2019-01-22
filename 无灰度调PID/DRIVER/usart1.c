#include "usart1.h"
void usart1_Init(uint32_t baud)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef  NVIC_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);	

	//USART_TX   
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;        	 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	 //50MHz
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	 	 
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	//USART_RX	 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;           
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 
	GPIO_Init(GPIOA, &GPIO_InitStructure);  

	USART_InitStructure.USART_BaudRate	 = baud;				
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;	
	USART_InitStructure.USART_StopBits 	 = USART_StopBits_1;	
	USART_InitStructure.USART_Parity	 = USART_Parity_No;		
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	

	USART_Init(USART1, &USART_InitStructure); 				

	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;       
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3; 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;		
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			
	NVIC_Init(&NVIC_InitStructure);						   
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);

	USART_Cmd(USART1, ENABLE);
}

uint32_t usart1_write(uint8_t ch)
{
	USART_SendData(USART1, ch);
	while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET); 
	return 1; 
}
void usart1_print(const char *format, ...)
{
		va_list args;
	char buf[256];
	va_start (args, format);
	vsprintf (buf, format, args);       
	va_end (args);    
	usart1_putstr(buf);
}

void usart1_putstr(const char *str)
{
		int i;
	for(i = 0; i < strlen(str); i++){	
		usart1_write(str[i]);
	}
}
