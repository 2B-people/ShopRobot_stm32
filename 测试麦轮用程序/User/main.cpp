#include <stdio.h>
#include "hardwareserial.h"
#include "config.h"
#include "motor.h"
#include "encoder.h"
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


int Motor::counts_per_rev_ = COUNTS_PER_REV;

double required_angular_vel = 1.0;
double required_linear_vel_x = 0;
double required_linear_vel_y = 0;
uint32_t previous_command_time = 0;


PID motor1_pid(-255, 255, K_P, K_I, K_D);
PID motor2_pid(-255, 255, K_P, K_I, K_D);
PID motor3_pid(-255, 255, K_P, K_I, K_D);
PID motor4_pid(-255, 255, K_P, K_I, K_D);

Motor motor1(MOTOR1, 254, 575);
Motor motor2(MOTOR2, 254, 575);
Motor motor3(MOTOR3, 254, 575);
Motor motor4(MOTOR4, 254, 575);

Encoder encoder1(ENCODER1, 0xffff, 0);
Encoder encoder2(ENCODER2, 0xffff, 0);
Encoder encoder3(ENCODER3, 0xffff, 0);
Encoder encoder4(ENCODER4, 0xffff, 0);
Battery bat(25, 10.6, 12.6);
Kinematics kinematics(MAX_RPM, WHEEL_DIAMETER,0.6 ,0.6 ,899);

Led led;





riki_msgs::Imu raw_imu_msg;
riki_msgs::Velocities raw_vel_msg;
riki_msgs::Battery raw_battery_msg;


void move_base()
{

    Kinematics::output pwm;
    pwm=kinematics.getRPM(required_linear_vel_x, required_linear_vel_y,required_angular_vel);
		

	
    motor1.spin(motor1_pid.compute(constrain(pwm.motor1, -MAX_RPM, MAX_RPM), motor1.rpm));
    motor2.spin(motor2_pid.compute(constrain(pwm.motor2, -MAX_RPM, MAX_RPM), motor2.rpm));
    motor3.spin(motor3_pid.compute(constrain(pwm.motor3, -MAX_RPM, MAX_RPM), motor3.rpm));
    motor4.spin(motor4_pid.compute(constrain(pwm.motor4, -MAX_RPM, MAX_RPM), motor4.rpm));
}






void stop_base()
{
    required_linear_vel_x = 0;
    required_linear_vel_y = 0;
    required_angular_vel = 0;
	
}




int main(void)
{
	uint32_t previous_control_time = 0;
	uint32_t publish_vel_time=0;


	SystemInit();
	initialise();
	
  motor1.init();
  motor2.init();
	motor3.init();
  motor4.init();
	encoder1.init();
  encoder2.init();
	encoder3.init();
  encoder4.init();
/////////////////////////////////////////////////////////////这一部分放到类中就会卡死，属实玄学。/////////////////////////////////////
	TIM_OCInitTypeDef  TIM_OCInitStructure;		
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; 
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 0; 
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; 
	TIM_OC1Init(TIM1, &TIM_OCInitStructure);
	TIM_OC1Init(TIM8, &TIM_OCInitStructure);
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




	while(1)
	{
		if ((millis() - previous_control_time) >= (1000 / COMMAND_RATE))
		{
			 move_base();
       previous_control_time = millis();
    }
		
		if ((millis() - publish_vel_time) >= (1000 / VEL_PUBLISH_RATE))
		{
			motor1.updateSpeed(encoder1.read());
			motor2.updateSpeed(encoder2.read());
			motor3.updateSpeed(encoder3.read());
			motor4.updateSpeed(encoder4.read());
			publish_vel_time = millis();
		}
	}
}
