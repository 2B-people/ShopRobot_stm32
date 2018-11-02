#include <stdio.h>
#include "hardwareserial.h"
#include "config.h"
#include "motor.h"
#include "battery.h"
#include "led.h"
#include "PID.h"
#include "Kinematics.h"
#include <riki_msgs/Velocities.h>
#include <geometry_msgs/Twist.h>
#include <riki_msgs/Imu.h>
#include <riki_msgs/Battery.h>
#include <geometry_msgs/Vector3.h>
#include "control.h"
#include "timer.h"
#include "remote.h"
#ifdef __cplusplus
extern "C" {
#include "oled.h"
#endif
#ifdef __cplusplus
}
#endif
double required_angular_vel = 0;
double required_linear_vel_x =0;
double required_linear_vel_y = 0;

extern REMOTE RC_CtrlData;

Battery bat(25, 10.6, 12.6);
Kinematics kinematics(MAX_RPM, WHEEL_DIAMETER,0.165 ,0.12 ,255);
Kinematics::output required_rpm;
HardwareSerial usart(SERIAL1);
Led led;


Motor motor1(0x201);
Motor motor2(0x202);
Motor motor3(0x203);
Motor motor4(0x204);














int main(void)
{
	uint32_t previous_control_time = 0;
	uint32_t publish_vel_time=0;
	uint32_t show_test_time=0;
	uint8_t key;

	SystemInit();
	initialise();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	
	CAN_Mode_Init();
	OLED_Init();		
	TIM5_Int_Init(71,9999);
	RC_Init();
	usart.begin(115200);
	while(1)
	{	
		OLED_ShowNum(10,0,abs(-motor1.Show_Now_Speed()),4,12);
		OLED_ShowNum(40,0,abs(motor2.Show_Now_Speed()),4,12);
		OLED_ShowNum(10,2,abs(motor3.Show_Now_Speed()),4,12);
		OLED_ShowNum(40,2,abs(-motor4.Show_Now_Speed()),4,12);	

	if(RC_CtrlData.ch0>1684||RC_CtrlData.ch1>1684||RC_CtrlData.ch2>1684||RC_CtrlData.ch3>1684||RC_CtrlData.s1>3||RC_CtrlData.s2>3||RC_CtrlData.ch0<364||RC_CtrlData.ch1<364||RC_CtrlData.ch2<364||RC_CtrlData.ch3<364||RC_CtrlData.s1<1||RC_CtrlData.s2<1)
		stop_base();
	}
}




