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
#include <riki_msgs/PID.h>
#include <riki_msgs/Imu.h>
#include <riki_msgs/Battery.h>
#include <geometry_msgs/Vector3.h>
#include "key.h"

double required_angular_vel = 5;
double required_linear_vel_x = 0;
double required_linear_vel_y = 0;
uint32_t previous_command_time = 0;


Battery bat(25, 10.6, 12.6);
Kinematics kinematics(MAX_RPM, WHEEL_DIAMETER,0.165 ,0.12 ,255);
Kinematics::output required_rpm;
HardwareSerial usart(SERIAL1);
Led led;


Motor motor1(0x201);
Motor motor2(0x202);
Motor motor3(0x203);
Motor motor4(0x204);





void move_base();
void stop_base();








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
	while(1)
	{
			
		if ((millis() - previous_control_time) >= (1000 / COMMAND_RATE))
		{
			 move_base();
			 previous_control_time = millis();
    }
		
		
		if ((millis() - show_test_time) >= (1000 / SHOW_TEST_RATE))
		{
			
		}
		
	}
}



void move_base()
{

    
    required_rpm=kinematics.getRPM(required_linear_vel_x, required_linear_vel_y,required_angular_vel);

		Set_CM_Speed(CAN1,
		motor1.motor_PID.PID_calculate(required_rpm.motor1*COUNTS_PER_REV,motor1.Show_Now_Speed()),
		motor2.motor_PID.PID_calculate(required_rpm.motor2*COUNTS_PER_REV,motor2.Show_Now_Speed()),
		motor3.motor_PID.PID_calculate(required_rpm.motor3*COUNTS_PER_REV,motor3.Show_Now_Speed()),
		motor4.motor_PID.PID_calculate(required_rpm.motor4*COUNTS_PER_REV,motor4.Show_Now_Speed()));//PID����
	

		
}






void stop_base()
{
    required_linear_vel_x = 0;
    required_linear_vel_y = 0;
    required_angular_vel = 0;
	
}

