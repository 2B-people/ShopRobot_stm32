#ifndef _pid_h
#define _pid_h
#include "include.h"

typedef struct 
{
	float Kp;
	float Ki;
	float Kd;
	int16_t error_now;
	int16_t error_last;
	int16_t error_inter;
	int16_t error_sum;
	int16_t pid_out;
	int16_t pid_out_last;
	int16_t pid_out_inter;
}PID_member;

extern PID_member* s_PIDcm1;
extern PID_member* s_PIDcm2;
extern PID_member* huidu_PID;
void PID_init(void);

void HuiduPidCalcuation(void);
void CM2speedPID_Calculation(void);
void CM1speedPID_Calculation(void);
void CMControl(void);
#endif
