#include "STM32F1.h"

static void TIM4_Mode_Config(void)
{
		GPIO_InitTypeDef GPIO_InitStructure; 
		TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
		TIM_ICInitTypeDef TIM_ICInitStructure;

		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOB, &GPIO_InitStructure);

		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
		TIM_DeInit(TIM4);  
		TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); 

		TIM_TimeBaseStructure.TIM_Period = 0XFFFF; 
		TIM_TimeBaseStructure.TIM_Prescaler = 0;     //设置预分频：  
		TIM_TimeBaseStructure.TIM_ClockDivision =TIM_CKD_DIV1;  //设置时钟分频系数：不分频 
		TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //向上计数模式   

		TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
	////////////////////////////////////////////////////////////////////////////////////////////////

		
			TIM_EncoderInterfaceConfig(TIM4, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Falling);

			
		
	/////////////////////////////////////////////////////////////////////////////////////////////////////
		TIM_ICStructInit(&TIM_ICInitStructure); 
		TIM_ICInitStructure.TIM_ICFilter = 6; 
		TIM_ICInit(TIM4, &TIM_ICInitStructure);
		
		TIM_ClearFlag(TIM4, TIM_FLAG_Update); 
		TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE); 

		TIM_SetCounter(TIM4, 0);

		TIM_Cmd(TIM4, ENABLE); 
}

void TIM4_Init(void)
{
  TIM4_Mode_Config();
}

/*------------End line - Lx ------------*/
