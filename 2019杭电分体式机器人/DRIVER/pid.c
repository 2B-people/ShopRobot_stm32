#include "pid.h"
#define c 1
extern Motor motor1;
extern Motor motor2;
extern Motor motor3;
extern Motor motor4;
extern Motor yt_motor1;
extern Motor yt_motor2;
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
}s_PIDcm1,s_PIDcm2,s_PIDcm3,s_PIDcm4,ytPID1,ytPID2;

void PID_init()
{
	s_PIDcm1.Kp=K_P;

	s_PIDcm1.Ki=K_I;
	s_PIDcm1.Kd=K_D;
	
	s_PIDcm2.Kp=K_P;
	s_PIDcm2.Ki=K_I;
	s_PIDcm2.Kd=K_D;

	s_PIDcm3.Kp=K_P;
	s_PIDcm3.Ki=K_I;
	s_PIDcm3.Kd=K_D;
	
	s_PIDcm4.Kp=K_P;
	s_PIDcm4.Ki=K_I;
	s_PIDcm4.Kd=K_D;	
	
	ytPID1.Kp=YT_KP;
	ytPID1.Ki=YT_KI;
	ytPID1.Kd=YT_KD;
	
	ytPID2.Kp=YT_KP;
	ytPID2.Ki=YT_KI;
	ytPID2.Kd=YT_KD;	
}

void CM1speedPID_Calculation()
{	
	int16_t derror,error_sum_out;
	s_PIDcm1.error_now=motor1.target_speed*c-motor1.now_speed;
	s_PIDcm1.error_sum+=s_PIDcm1.error_now;
        error_sum_out=s_PIDcm1.error_sum;

//        if(error_sum_out>12500)
//          error_sum_out=12500;
//        if(error_sum_out<-12500)
//          error_sum_out=-12500;
        

	derror=s_PIDcm1.error_last-s_PIDcm1.error_inter;
	s_PIDcm1.error_inter=s_PIDcm1.error_last;
	s_PIDcm1.error_last=s_PIDcm1.error_now;
	s_PIDcm1.pid_out=s_PIDcm1.error_now*s_PIDcm1.Kp+error_sum_out*s_PIDcm1.Ki+derror*s_PIDcm1.Kd;
	if(s_PIDcm1.pid_out<-8000) s_PIDcm1.pid_out=-8000;
	if(s_PIDcm1.pid_out>8000) s_PIDcm1.pid_out=8000;

}

void CM2speedPID_Calculation()
{	
	int16_t derror,error_sum_out;
		
	s_PIDcm2.error_now=motor2.target_speed*c-motor2.now_speed;

	s_PIDcm2.error_sum+=s_PIDcm2.error_now;
        error_sum_out=s_PIDcm2.error_sum;

//        if(error_sum_out>12500)
//          error_sum_out=12500;
//        if(error_sum_out<-12500)
//          error_sum_out=-12500;
        

	derror=s_PIDcm2.error_last-s_PIDcm2.error_inter;
	s_PIDcm2.error_inter=s_PIDcm2.error_last;
	s_PIDcm2.error_last=s_PIDcm2.error_now;
	s_PIDcm2.pid_out=s_PIDcm2.error_now*s_PIDcm2.Kp+error_sum_out*s_PIDcm2.Ki+derror*s_PIDcm2.Kd;

	if(s_PIDcm2.pid_out<-8000) s_PIDcm2.pid_out=-8000;
	if(s_PIDcm2.pid_out>8000) s_PIDcm2.pid_out=8000;

}

void CM3speedPID_Calculation()
{	
	int32_t derror,error_sum_out;
	s_PIDcm3.error_now=motor3.target_speed*c-motor3.now_speed;
	s_PIDcm3.error_sum+=s_PIDcm3.error_now;
        error_sum_out=s_PIDcm3.error_sum;

//        if(error_sum_out>12500)
//          error_sum_out=12500;
//        if(error_sum_out<-12500)
//          error_sum_out=-12500;

	derror=s_PIDcm3.error_last-s_PIDcm3.error_inter;
	s_PIDcm3.error_inter=s_PIDcm3.error_last;
	s_PIDcm3.error_last=s_PIDcm3.error_now;
	s_PIDcm3.pid_out=s_PIDcm3.error_now*s_PIDcm3.Kp+error_sum_out*s_PIDcm3.Ki+derror*s_PIDcm3.Kd;
	if(s_PIDcm3.pid_out<-8000) s_PIDcm3.pid_out=-8000;
	if(s_PIDcm3.pid_out>8000) s_PIDcm3.pid_out=8000;
	

}

void CM4speedPID_Calculation()
{	
	int32_t derror,error_sum_out;
	s_PIDcm4.error_now=motor4.target_speed*c-motor4.now_speed;
	s_PIDcm4.error_sum+=s_PIDcm4.error_now;
        error_sum_out=s_PIDcm4.error_sum;

//        if(error_sum_out>12500)
//          error_sum_out=12500;
//        if(error_sum_out<-12500)
//          error_sum_out=-12500;

	derror=s_PIDcm4.error_last-s_PIDcm4.error_inter;
	s_PIDcm4.error_inter=s_PIDcm4.error_last;
	s_PIDcm4.error_last=s_PIDcm4.error_now;
	s_PIDcm4.pid_out=s_PIDcm4.error_now*s_PIDcm4.Kp+error_sum_out*s_PIDcm4.Ki+derror*s_PIDcm4.Kd;
	if(s_PIDcm4.pid_out<-8000) s_PIDcm4.pid_out=-8000;
	if(s_PIDcm4.pid_out>8000) s_PIDcm4.pid_out=8000;
	

}

void CMControl()
{
	if(!IsRotate)//Î´ÔÚÐý×ªÊ±
		get_RPM();
  CM2speedPID_Calculation();
//  CM4speedPID_Calculation();
  CM1speedPID_Calculation();
//  CM3speedPID_Calculation();
  Set_CM_Speed(CAN1,s_PIDcm1.pid_out,s_PIDcm2.pid_out);
	// Set_CM_Speed(CAN1,500,500,500,500);
}
