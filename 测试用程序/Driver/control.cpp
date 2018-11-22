#include "control.h"
#include "Kinematics.h"
#include "motor.h"
extern Kinematics::output required_rpm;
extern double required_angular_vel ;
extern double required_linear_vel_x ;
extern double required_linear_vel_y ;
extern Motor motor1;
extern Motor motor2;
extern Motor motor3;
extern Motor motor4;
extern Kinematics kinematics;
void move_base()
{

    
    required_rpm=kinematics.getRPM(required_linear_vel_x, required_linear_vel_y,required_angular_vel);

		Set_CM_Speed(CAN1,
		motor1.calcPid(required_rpm.motor1*COUNTS_PER_REV,motor1.Show_Now_Speed()),
		motor2.calcPid(required_rpm.motor2*COUNTS_PER_REV,motor2.Show_Now_Speed()),
		motor3.calcPid(required_rpm.motor3*COUNTS_PER_REV,motor3.Show_Now_Speed()),
		motor4.calcPid(required_rpm.motor4*COUNTS_PER_REV,motor4.Show_Now_Speed()));
	
		Set_YT_Speed(CAN1,0,1000);
	//	Set_CM_Speed(CAN1,1000,1000,1000,1000,500,500);//PID????
}






void stop_base()
{
    required_linear_vel_x = 0;
    required_linear_vel_y = 0;
    required_angular_vel = 0;
	
}
