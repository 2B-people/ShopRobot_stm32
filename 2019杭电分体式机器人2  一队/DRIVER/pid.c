#include "pid.h"
#define c 1
#define MaxPid 1500



struct PID_member s_PIDcm1, s_PIDcm2, huidu_PID;

void PID_init()
{
	s_PIDcm1.Kp = K_P;
	s_PIDcm1.Ki = K_I;
	s_PIDcm1.Kd = K_D;

	s_PIDcm2.Kp = K_P;
	s_PIDcm2.Ki = K_I;
	s_PIDcm2.Kd = K_D;

	huidu_PID.Kp = hK_P;
	huidu_PID.Ki = hK_I;
	huidu_PID.Kd = hK_D;
}

void HuiduPidCalcuation()
{
	int16_t derror, error_sum_out;
	huidu_PID.error_now = ADC_JIHE[0] - ADC_JIHE[1];
	huidu_PID.error_sum += huidu_PID.error_now;
	error_sum_out = huidu_PID.error_sum;


	derror = huidu_PID.error_last - huidu_PID.error_inter;
	huidu_PID.error_inter = huidu_PID.error_last;
	huidu_PID.error_last = huidu_PID.error_now;
	huidu_PID.pid_out = (int16_t) ((double)huidu_PID.error_now * huidu_PID.Kp + error_sum_out * huidu_PID.Ki + derror * huidu_PID.Kd);
	if (huidu_PID.pid_out < -1200)
		huidu_PID.pid_out = -1200;
	if (huidu_PID.pid_out > 1200)
		huidu_PID.pid_out = 1200;

}

void CM1speedPID_Calculation()
{
	int16_t derror, error_sum_out;
	s_PIDcm1.error_now = motor1.target_speed * c - motor1.now_speed;
	s_PIDcm1.error_sum += s_PIDcm1.error_now;
	error_sum_out = s_PIDcm1.error_sum;
	derror = s_PIDcm1.error_last - s_PIDcm1.error_inter;
	s_PIDcm1.error_inter = s_PIDcm1.error_last;
	s_PIDcm1.error_last = s_PIDcm1.error_now;
	s_PIDcm1.pid_out = (int16_t) ((double)s_PIDcm1.error_now * s_PIDcm1.Kp + error_sum_out * s_PIDcm1.Ki + derror * s_PIDcm1.Kd);
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

	derror = s_PIDcm2.error_last - s_PIDcm2.error_inter;
	s_PIDcm2.error_inter = s_PIDcm2.error_last;
	s_PIDcm2.error_last = s_PIDcm2.error_now;
	s_PIDcm2.pid_out = (int16_t) ((double)s_PIDcm2.error_now * s_PIDcm2.Kp + error_sum_out * s_PIDcm2.Ki + derror * s_PIDcm2.Kd);

	if (s_PIDcm2.pid_out < -MaxPid)
		s_PIDcm2.pid_out = -MaxPid;
	if (s_PIDcm2.pid_out > MaxPid)
		s_PIDcm2.pid_out = MaxPid;
}

void CMControl()
{
		CM1speedPID_Calculation();
		CM2speedPID_Calculation();
		Set_CM_Speed(CAN1, s_PIDcm1.pid_out, s_PIDcm2.pid_out);
}
