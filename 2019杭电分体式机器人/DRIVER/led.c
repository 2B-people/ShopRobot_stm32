#include "led.h"
void Led_init()		
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RIKI_LED_GPIO_CLK, ENABLE);

	GPIO_InitStructure.GPIO_Pin     = RIKI_LED_PIN;
	GPIO_InitStructure.GPIO_Mode    = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed   = GPIO_Speed_50MHz;
	GPIO_Init(RIKI_LED_GPIO_PORT, &GPIO_InitStructure);
}

void LED_On_Off(char status)				
{
	if(status == True){
		GPIO_SetBits(RIKI_LED_GPIO_PORT, RIKI_LED_PIN);					//�ߵ�ƽ����
	}else{
		GPIO_ResetBits(RIKI_LED_GPIO_PORT, RIKI_LED_PIN);
	}
}
