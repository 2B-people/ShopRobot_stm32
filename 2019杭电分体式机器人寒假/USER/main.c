#include "include.h"
#include "math.h"

//////////key_PIN1   	//中
//////////key_PIN2  	//左
//////////key_PIN3  	//下
//////////key_PIN4  	//右
//////////key_PIN5  	//上
//////////key_PIN6  	//独立


double required_vel = 0;
uint8_t IsControlFinsh;			  //是否完成指定任务
uint8_t IsStop=0;					  //是否接到急停状态信号的标志

uint8_t target_position=1;	//目标区域	
uint8_t position_x = 0;			  //当前横坐标
uint8_t position_y = 0;			  //当前纵坐标
uint8_t orientation=positive_y ; //当前车的朝向，默认开始为y正方向。
uint8_t target_position_x = 0;	//目标横坐标
uint8_t target_position_y = 0;	//目标纵坐标
uint8_t IsHD=1;									//是否使用模拟灰度。
uint8_t Obstacle=0;						//障碍物位置
uint16_t Distance=0;					//激光雷达测距结果
void begin(void);
int main()
{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO ,ENABLE);    
		GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
		SystemInit();
		initialise();
	
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);			
		usart1_Init(115200);
		CAN_Mode_Init();
		Ledbeep_init();
		RC_Init();
		OLED_Init(); 
		las_Init();
		PID_init();
		huiductrlinit();
		infrared_Init();
		KEY_Init();
		OLED_Clear();
		path_Init();
			
	
   	TIM5_Int_Init(35, 999); //1000HZ		PID调速
		TIM7_Int_Init(35,9999);	//100HZ,    确定速度		
		begin();
		TIM6_Int_Init(359, 9999);  //10HZ		路径规划，确定nextx,nexty
	 while(1)
	 {
			remoteAction();
			MOVE(nextx,nexty);
			waitingStop();	
	 }
	 
}


void begin(void)
{
	
	required_vel=0.3;
	while(infrared1==BLACK||infrared2==BLACK||infrared3==BLACK||infrared4==BLACK);
	required_vel=0;
	ROTATE(0);
	IsHD=1;
	orientation=positive_y;
	position_x=0;
	position_y=2;
	target_position_x=0;
	target_position_y=3;
	if(target_position_x!=position_x||target_position_y!=position_y)
		path_cal();
	nextx=position_x;
	nexty=position_y;
		
}
