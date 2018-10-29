#include "PID.h"
PID::PID(float Kp,float Ki,float Kd,int16_t out_Max,int16_t out_Min)
{
	this->Kp=Kp;
	this->Ki=Ki;
	this->Kd=Kd;
	this->out_Max=out_Max;
	this->out_Min=out_Min;
}

void PID::Set_PID(float Kp,float Ki,float Kd,int16_t out_Max,int16_t out_Min)
{
	this->Kp=Kp;
	this->Ki=Ki;
	this->Kd=Kd;
}

int16_t PID::PID_calculate(int16_t target_speed,int16_t now_speed)
{
	int16_t derror;
	error_now=target_speed*1-now_speed;
	error_sum+=error_now;
	
	derror=error_last-error_inter;
	error_inter=error_last;
	error_last=error_now;
	pid_out=int32_t(error_now*Kp+error_sum*Ki+derror*Kd);
	
	if(pid_out<out_Min) pid_out=out_Min;
	if(pid_out>out_Max) pid_out=out_Max;
	return pid_out;
}
