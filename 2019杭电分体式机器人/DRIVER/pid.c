#include "pid.h"
#define c 1
#define MaxPid 1500
//#define IsHD



struct PID_member
{
	float Kp;
	float Ki;
	float Kd;
	int16_t error_now;
	int16_t error_last;
	int16_t error_inter;
	int16_t error_sum;
	int16_t pid_out;
	int32_t pid_out_last;
	int32_t pid_out_inter;
} s_PIDcm1, s_PIDcm2, huidu_PID;

void PID_init()
{
	s_PIDcm1.Kp = K_P;
	s_PIDcm1.Ki = K_I;
	s_PIDcm1.Kd = K_D;

	s_PIDcm2.Kp = K_P;
	s_PIDcm2.Ki = K_I;
	s_PIDcm2.Kd = K_D;

	huidu_PID.Kp = K_P;
	huidu_PID.Ki = K_I;
	huidu_PID.Kd = K_D;
}

void HuiduPidCalcuation()
{
	int16_t derror, error_sum_out;
	if(required_vel>0)
		huidu_PID.error_now = ADC_JIHE[0] - ADC_JIHE[1];
	else
		huidu_PID.error_now = ADC_JIHE[2] - ADC_JIHE[3];
	huidu_PID.error_sum += huidu_PID.error_now;
	error_sum_out = huidu_PID.error_sum;


	derror = huidu_PID.error_last - huidu_PID.error_inter;
	huidu_PID.error_inter = huidu_PID.error_last;
	huidu_PID.error_last = huidu_PID.error_now;
	huidu_PID.pid_out = huidu_PID.error_now * huidu_PID.Kp + error_sum_out * huidu_PID.Ki + derror * huidu_PID.Kd;
	if (huidu_PID.pid_out < -1000)
		huidu_PID.pid_out = -1000;
	if (huidu_PID.pid_out > 1000)
		huidu_PID.pid_out = 1000;
}

void CM1speedPID_Calculation()
{
	int16_t derror, error_sum_out;
	s_PIDcm1.error_now = motor1.target_speed * c - motor1.now_speed;
	s_PIDcm1.error_sum += s_PIDcm1.error_now;
	error_sum_out = s_PIDcm1.error_sum;

	//        if(error_sum_out>12500)
	//          error_sum_out=12500;
	//        if(error_sum_out<-12500)
	//          error_sum_out=-12500;

	derror = s_PIDcm1.error_last - s_PIDcm1.error_inter;
	s_PIDcm1.error_inter = s_PIDcm1.error_last;
	s_PIDcm1.error_last = s_PIDcm1.error_now;
	s_PIDcm1.pid_out = s_PIDcm1.error_now * s_PIDcm1.Kp + error_sum_out * s_PIDcm1.Ki + derror * s_PIDcm1.Kd;
	if (s_PIDcm1.pid_out < -MaxPid)
		s_PIDcm1.pid_out = -MaxPid;
	if (s_PIDcm1.pid_out > MaxPid)
		s_PIDcm1.pid_out = MaxPid;
}

void CM2speedPID_Calculation()
{
	int16_t derror, error_sum_out;

	s_PIDcm2.error_now = motor2.target_speed * c - motor2.now_speed;

	s_PIDcm2.error_sum += s_PIDcm2.error_now;
	error_sum_out = s_PIDcm2.error_sum;

	//        if(error_sum_out>12500)
	//          error_sum_out=12500;
	//        if(error_sum_out<-12500)
	//          error_sum_out=-12500;

	derror = s_PIDcm2.error_last - s_PIDcm2.error_inter;
	s_PIDcm2.error_inter = s_PIDcm2.error_last;
	s_PIDcm2.error_last = s_PIDcm2.error_now;
	s_PIDcm2.pid_out = s_PIDcm2.error_now * s_PIDcm2.Kp + error_sum_out * s_PIDcm2.Ki + derror * s_PIDcm2.Kd;

	if (s_PIDcm2.pid_out < -MaxPid)
		s_PIDcm2.pid_out = -MaxPid;
	if (s_PIDcm2.pid_out > MaxPid)
		s_PIDcm2.pid_out = MaxPid;
}

void CMControl()
{
	if(required_vel==0)
	{
		s_PIDcm1.error_sum=0;
		s_PIDcm2.error_sum=0;
	}
	else if(required_vel>MaxVel)
	{
		required_vel=MaxVel;
	}
	else if(required_vel<=MaxVel)
	{
		required_vel=-MaxVel;
	}
	
	if(!IsRotate)
	{
			motor1.target_speed = get_RPM(required_vel);
			motor2.target_speed = get_RPM(required_vel);
#ifdef IsHD
			adcjihe();
			HuiduPidCalcuation();
			motor1.target_speed += huidu_PID.pid_out;
			motor2.target_speed -= huidu_PID.pid_out;
#endif
	}
		CM1speedPID_Calculation();
		CM2speedPID_Calculation();
		Set_CM_Speed(CAN1, s_PIDcm1.pid_out, s_PIDcm2.pid_out);

}
