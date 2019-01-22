#include "include.h"

double required_vel = 0.0;
uint8_t IsControlFinsh;			  //是否完成指定任务
uint8_t IsStop;					  //是否接到急停状态信号的标志
uint8_t position;				  //当前区域，分为八块
uint8_t position_x = 0;			  //当前横坐标
uint8_t position_y = 2;			  //当前纵坐标
uint8_t orientation = positive_x; //当前车的朝向，默认开始为x正方向
uint8_t target_position_x = 0;	//目标横坐标
uint8_t target_position_y = 3;	//目标纵坐标
uint8_t stopping;				  //车身是否仍然处于急停状态的标志


void begin(void);
int main()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE); //要先开时钟，再重映射；关闭jtag，保留swd。

	SystemInit();
	initialise();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	
	CAN_Mode_Init();
	Ledbeep_init();
	RC_Init();
	OLED_Init(); 
	las_Init();
	usart1_Init(115200);
	PID_init();
	huiductrlinit();
	infrared_Init();
	KEY_Init();
	OLED_Clear();
	TIM5_Int_Init(71, 9999); //100HZ		PID调速
	TIM6_Int_Init(71, 999);  //10HZ		路径规划
	begin();		//将车开到初始位置

 while (1)
 {
	 if(!(stopping&&required_vel!=0))
	 {
			OLED_ShowString(0, 0, "X", 16);
			OLED_ShowNum(16,0,position_x,3,16);
			OLED_ShowString(0, 2, "Y", 16);
			OLED_ShowNum(16,2,position_y,3,16);
			OLED_ShowString(0, 4, "P", 16);
			OLED_ShowNum(16,4,position,3,16);
			OLED_ShowString(50, 0, "M1", 16);
			OLED_ShowNum(76,0,motor1.now_speed,4,16);
			OLED_ShowString(50, 2, "M2", 16);
			OLED_ShowNum(76,2,motor2.now_speed,4,16);
			OLED_ShowString(50, 4, "T1", 16);
			OLED_ShowNum(76,4,motor1.target_speed,4,16);
			OLED_ShowString(50, 6, "T2", 16);
			OLED_ShowNum(76,6,motor2.target_speed,4,16);
	 }
		if (IsStop)
		{
			TIM_Cmd(TIM6, DISABLE);
			if(required_vel>0)
				required_vel -= down_vel;
			else if(required_vel<0)
				required_vel += down_vel;
			stopping = 1;
		}
		else
		{
			if (stopping)
			{
				TIM_Cmd(TIM6, ENABLE);
				stopping = 0;
			}
		}
 }
}


void begin(void)
{
	
}
