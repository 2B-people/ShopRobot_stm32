#include "led.h"
#include "sys.h"
void Led_init()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(LED_GPIO_CLK, ENABLE);
	GPIO_InitStructure.GPIO_Pin = LED_PIN1|LED_PIN2|LED_PIN3 ;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(LED_GPIO_PORT, &GPIO_InitStructure);
}

void LED_On_Off(char status, uint16_t LED_Pin)
{
	if (status == True)
	{
		GPIO_SetBits(GPIOC,LED_Pin); //高电平点亮
	}
	else
	{
		GPIO_ResetBits(GPIOC, LED_Pin);
	}
}
void SW_LED(char led_nemberx, char status)
{
	switch (led_nemberx)
	{
	case 1:
		LED_On_Off(status,GPIO_Pin_0);
		 break;
	case 2:
		LED_On_Off(status,GPIO_Pin_1);
		 break;	
	case 3:
		LED_On_Off(status,GPIO_Pin_3);
		break;
	default:
		printf("error!");
		break;
	}
}

