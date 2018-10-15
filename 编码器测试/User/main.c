#include "STM32F1.h"

u16	Parameter = 512;																	//输入编码器线数
u16 Count,OldCNT;

int main(void)
{
	delay_init();	    	 																//延时函数初始化	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 	 	//设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	uart_init(115200);	 																//串口初始化为115200
	LCD_Init();			   																	//初始化LCD  
	TIM4_Init();																				//初始化TIM4为编码器借口模式
	POINT_COLOR=BLUE;																		//字体颜色
	LCD_ShowString(75,150,200,16,16,"Count:");

  while(1)
	{
		 u16 NewCNT=0;
        int CNT;
        NewCNT=TIM4->CNT;
        CNT=NewCNT-OldCNT;
      
 
                
        OldCNT=NewCNT;  
			if((int)CNT<=0)
       LCD_ShowNum(125,150,abs((int)CNT),5,16); 
			else
				LCD_ShowNum(125,250,(int)CNT,5,16); 
		}		
}


/*------------End line - Lx ------------*/
