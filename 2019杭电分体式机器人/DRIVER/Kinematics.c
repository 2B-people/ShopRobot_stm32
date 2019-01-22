#include "kinematics.h"
//float speed[4];
double get_RPM(double liner_vel_in)
{
		float circumference_=PI*WHEEL_DIAMETER;
		float liner_vel = liner_vel_in * 60;		//将速度转为m/min
		double retrun_speed=liner_vel*COUNTS_PER_REV/circumference_;//将速度转换为轮子转速
		return retrun_speed;
}

void stop_base()
{
	required_vel=0;
	
}
