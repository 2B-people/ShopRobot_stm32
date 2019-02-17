#include "kinematics.h"
double get_RPM(double liner_vel_in)
{
		float circumference_=PI*WHEEL_DIAMETER;
		float liner_vel = liner_vel_in * 60;		//将速度转为m/min
		double retrun_speed=liner_vel*COUNTS_PER_REV/circumference_;//将速度转换为轮子转速
		return retrun_speed;
}

void waitingStop()
{

	if((!stopping)||required_vel==0)
			{
				OLED_SHOW_MANU();
			}		 		
			if (IsStop)											//接收到停止信号
			{
				required_vel=0;
				stopping = 1;
			}
			else if(stopping)								//接收到开始信号
			{
					stopping = 0;									
			}						
}
void decideSpeed(void)
{
	if(required_vel==0)
	{
		s_PIDcm1.error_sum=0;							//速度为0时将积分置零
		s_PIDcm2.error_sum=0;							
	}
	if(required_vel>=MaxVel)
	{
		required_vel=MaxVel;							
	}
	else if(required_vel<=-MaxVel)
	{
		required_vel=-MaxVel;
	}	
	if(IsRotate==0)
	{
		motor1.target_speed = get_RPM(required_vel);
		motor2.target_speed = get_RPM(required_vel);
	}
	if(IsHD&&IsRotate==0)
	{
			adcjihe();											//adc采样量化
			HuiduPidCalcuation();						//根据adc数值
			if(required_vel!=0)
			{
				motor1.target_speed += huidu_PID.pid_out;
				motor2.target_speed -= huidu_PID.pid_out;				
			}
	}
	
	
}
