#include "include.h"

double required_angular_vel = 0;
double required_linear_vel_x =1;
double required_linear_vel_y = 0;
double required_pitch ;
double required_yaw ;
uint8_t IsFinsh;
uint32_t publish_las_time = 0;
uint32_t publish_vel_time = 0;
uint32_t publish_remote_time = 0;
int main()
{
	SystemInit();
	initialise();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	
	CAN_Mode_Init();
	TIM5_Int_Init(71,9999);//100HZ
	RC_Init();
	las_Init();
	usart1_Init(115200);
	PID_init();
	while(1)
	{	
//		if ((millis() - publish_vel_time) >= (1000 / VEL_PUBLISH_RATE))
//		{
//			publish_vel();
//			publish_vel_time=millis();
//		}
//		
//		if ((millis() - publish_las_time) >= (1000 / LAS_PUBLISH_RATE))
//		{
//			publish_las();
//			publish_las_time=millis();
//		}
//		if ((millis() - publish_remote_time) >= (1000 / REMOTE_PUBLISH_RATE))
//		{
//			publish_remote();
//			publish_remote_time=millis();
//		}
	}
}
