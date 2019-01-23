#ifndef _pid_h
#define _pid_h
#include "include.h"

typedef struct
{
	float SetSpeed; //定义设定值
	float ActualSpeed;//定义实际值
	float err; //定义偏差值
	float err_last; //定义上一个偏差值
	float Kp,Ki,Kd; //定义比例、积分、微分系数
	float voltage; //定义电压值（控制执行器的变量）
	float integral; //定义积分值
}pid;

struct PID_member
{
	double Kp;
	double Ki;
	double Kd;
	int16_t error_now;
	int16_t error_last;
	int16_t error_inter;
	int16_t error_sum;
	int16_t pid_out;
	int16_t pid_out_last;
	int16_t pid_out_inter;
};

extern struct PID_member s_PIDcm1, s_PIDcm2, huidu_PID;

void PID_init(void);

void HuiduPidCalcuation(void);
void CM2speedPID_Calculation(void);
void CM1speedPID_Calculation(void);
void CMControl(void);
#endif
