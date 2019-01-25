#include "include.h"
#include "math.h"
double required_vel = -0.1;
uint8_t IsControlFinsh;			  //是否完成指定任务
uint8_t IsStop=0;					  //是否接到急停状态信号的标志
uint8_t position=1;				  //当前区域，分为八块
uint8_t target_position=1;	//目标区域	
uint8_t position_x = 0;			  //当前横坐标
uint8_t position_y = 2;			  //当前纵坐标
uint8_t orientation = positive_x; //当前车的朝向，默认开始为x正方向
uint8_t target_position_x = 0;	//目标横坐标
uint8_t target_position_y = 2;	//目标纵坐标
uint8_t stopping=0;				  //车身是否仍然处于急停状态的标志
uint8_t key;

void begin(void);
int main()
{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);
		GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE); //要先开时钟，再重映射；关闭jtag，保留swd。

		SystemInit();
		initialise();
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
		usart1_Init(115200);
		CAN_Mode_Init();
		//Ledbeep_init();
		//RC_Init();
		OLED_Init(); 
		//las_Init();
		//usart1_Init(115200);
		PID_init();
		huiductrlinit();
		//infrared_Init();
		KEY_Init();
		OLED_Clear();
		TIM5_Int_Init(35, 999); //1000HZ		PID调速		
		//begin();		//将车开到初始位置
	//	TIM6_Int_Init(359, 9999);  //10HZ		路径
 while (1)
 {
	 if(!(stopping&&required_vel!=0))
	 {
		 usart1_print("%d\n",huidu_PID.pid_out);
			OLED_ShowString(0, 0, "X", 16);
			OLED_ShowNum(16,0,position_x,3,16);		//X坐标
			OLED_ShowString(0, 2, "Y", 16);
			OLED_ShowNum(16,2,position_y,3,16);		//Y坐标
			OLED_ShowString(0, 4, "P", 16);	
			OLED_ShowNum(16,4,position,3,16);			//分块区
			OLED_ShowString(0, 6, "V", 16);	
			OLED_ShowNum(16,6,(abs)(required_vel*100),3,16);		//车辆速度	 
			OLED_ShowString(50, 0, "M1", 16);
			OLED_ShowNum(76,0,(abs)(motor1.target_speed),4,16);//电机1速度
			OLED_ShowString(50, 2, "M2", 16);
			OLED_ShowNum(76,2,(abs)(motor2.target_speed),4,16);//电机2速度
			OLED_ShowString(50, 4, "H1", 16);
			OLED_ShowNum(76,4, ADC_JIHE[0],4,16);			//灰度1值
			OLED_ShowString(50, 6, "H2", 16);
			OLED_ShowNum(76,6, ADC_JIHE[1],4,16);			//灰度2值
			key=KEY_Scan(0);
			if(key==KEY1_PRES)
				required_vel=0;
			else if(key==KEY2_PRES)
				required_vel+=0.1;
			else if(key==KEY3_PRES)
				required_vel-=0.1;
	 }
//		if (IsStop)
//		{
//			TIM_Cmd(TIM6, DISABLE);
//			if(required_vel>0)
//				required_vel -= down_vel;
//			else if(required_vel<0)
//				required_vel += down_vel;
//			stopping = 1;
//		}
//		else
//		{
//			if (stopping)
//			{
//				TIM_Cmd(TIM6, ENABLE);
//				stopping = 0;
//			}
//		}
 }
}


void begin(void)
{
	
}
