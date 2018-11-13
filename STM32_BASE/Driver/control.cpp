#include "control.h"
#include "config.h"
extern Kinematics kinematics;
extern double required_angular_vel;
extern double required_linear_vel_x;
extern double required_linear_vel_y;
extern double required_pitch ;
extern double required_yaw ;
extern Motor motor1;
extern Motor motor2;
extern Motor motor3;
extern Motor motor4;
extern Motor yt_motor1;
extern Motor yt_motor2;

void move_base()
{
	Kinematics::output required_rpm;
	required_rpm = kinematics.getRPM(required_linear_vel_x, required_linear_vel_y, required_angular_vel);

	Set_CM_Speed(CAN1,
				 motor1.calcPid(required_rpm.motor1 , motor1.Show_Now_Speed()),
				 motor2.calcPid(required_rpm.motor2 , motor2.Show_Now_Speed()),
				 motor3.calcPid(required_rpm.motor3 , motor3.Show_Now_Speed()),
				 motor4.calcPid(required_rpm.motor4 , motor4.Show_Now_Speed())); //PID????
}

void stop_base()
{
	required_linear_vel_x = 0;
	required_linear_vel_y = 0;
	required_angular_vel = 0;
}
void 	yt_move_base()
{
	double required_pitch_s=required_pitch*60;
	double required_yaw_s=required_yaw*60;
	int _yt_motor1=required_yaw_s/(YT_WHELL_DIAMETER*PI);
	int _yt_motor2=required_pitch_s/(YT_WHELL_DIAMETER*PI);
	
	if(_yt_motor1>=YT_MAX_RPM)
		_yt_motor1=0;
	if(_yt_motor2>=YT_MAX_RPM)
		_yt_motor2=0;
	
	Set_YT_Speed(CAN1,
	yt_motor1.calcPid(_yt_motor1,yt_motor1.Show_Now_Speed()),
	yt_motor2.calcPid(_yt_motor2,yt_motor2.Show_Now_Speed()));
}
