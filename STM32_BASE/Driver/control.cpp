#include "control.h"

extern Kinematics kinematics;
extern double required_angular_vel;
extern double required_linear_vel_x;
extern double required_linear_vel_y;
extern Motor motor1;
extern Motor motor2;
extern Motor motor3;
extern Motor motor4;

void move_base()
{
	Kinematics::output required_rpm;
	required_rpm = kinematics.getRPM(required_linear_vel_x, required_linear_vel_y, required_angular_vel);

	Set_CM_Speed(CAN1,
				 motor1.calcPid(required_rpm.motor1 , motor1.Show_Now_Speed()),
				 motor2.calcPid(required_rpm.motor2 , motor2.Show_Now_Speed()),
				 motor3.calcPid(required_rpm.motor3 , motor3.Show_Now_Speed()),
				 motor4.calcPid(required_rpm.motor4 , motor4.Show_Now_Speed())); //PID????
}

void stop_base()
{
	required_linear_vel_x = 0;
	required_linear_vel_y = 0;
	required_angular_vel = 0;
}
