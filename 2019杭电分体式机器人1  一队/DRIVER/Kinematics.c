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
				switch(orientation)
				{
					case positive_x:
						target_position_x=position_x+1;
						target_position_y=position_y;
						path_cal();
						break;
					case negative_x:
						target_position_x=position_x-1;
						target_position_y=position_y;
						path_cal();
						break;
					case negative_y:
						target_position_x=position_x;
						target_position_y=position_y-1;
						path_cal();
						break;
					case positive_y:
						target_position_x=position_x;
						target_position_y=position_y+1;
						path_cal();
						break;
				}
				stopping = 1;
			}
			else if(stopping)								//接收到开始信号
			{
					stopping = 0;									
			}						
}
void decideSpeed(void)
{
static uint8_t lsx;
	static uint8_t lsy;
	

	
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
	if(required_vel>=fast_vel)
	{
		huidu_PID.Kd=hK_P;
		huidu_PID.Ki=hK_I;
		huidu_PID.Kd=hK_D;
	}
	else
	{
		huidu_PID.Kp=0.65;
		huidu_PID.Ki=0;
		huidu_PID.Kd=0.02;
	}
	if(IsRotate==0)		//旋转结束
	{
		
		if(LsRotate&&position_x==lsx&&position_y==lsy&&!IsFetch&&position_x&&position_x!=target_position_x&&position_y!=target_position_y)//如果是旋转结束后走的第一格
		{
			required_vel=slow_vel;	
		}
		else if(LsRotate)//旋转结束后走完第一格					
			LsRotate=0;
		lsx=position_x;		//检查有无走完旋转后的第一格
		lsy=position_y;
		
		motor1.target_speed = get_RPM(required_vel);	
		motor2.target_speed = get_RPM(required_vel);
	}
	
	
}
