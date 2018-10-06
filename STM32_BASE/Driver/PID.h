#ifndef PID_H
#define PID_H
#include <stdint.h>

class PID
{
public:
  PID(float Kp=0.4,float Ki=0,float Kd=0,int16_t out_Max=1500,int16_t out_Min=-1500);
	void Set_PID(float Kp=0.4,float Ki=0,float Kd=0,int16_t out_Max=1500,int16_t out_Min=-1500);
	int16_t PID_calculate(int16_t target_speed,int16_t now_speed);	
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
	int16_t out_Max;
	int16_t out_Min;
};

#endif
