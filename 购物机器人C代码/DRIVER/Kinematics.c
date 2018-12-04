#include "kinematics.h"
float speed[4];
void get_RPM()
{
		float circumference_=PI*WHEEL_DIAMETER;
	
		float linear_x_mins = required_linear_vel_x * 60;
    float linear_y_mins = required_linear_vel_y * 60;
    float angular_z_mins = required_angular_vel * 60;

    speed[0] = linear_y_mins - linear_x_mins + angular_z_mins * (LENGTH_A + LENGTH_B);
    speed[1] = linear_y_mins + linear_x_mins - angular_z_mins * (LENGTH_A + LENGTH_B);
    speed[2] = linear_y_mins - linear_x_mins - angular_z_mins * (LENGTH_A + LENGTH_B);
    speed[3]= linear_y_mins + linear_x_mins + angular_z_mins * (LENGTH_A + LENGTH_B);

 

		motor1.target_speed = -(int)(speed[0] / circumference_);//	�ٶ�/�ܳ�
    motor2.target_speed = (int)(speed[1] / circumference_);
    motor3.target_speed = (int)(speed[2] / circumference_);
    motor4.target_speed = -(int)(speed[3] / circumference_);

    motor1.target_speed*=COUNTS_PER_REV;
    motor2.target_speed*=COUNTS_PER_REV;
		motor3.target_speed*=COUNTS_PER_REV;
		motor4.target_speed*=COUNTS_PER_REV;

//    if (motor1.target_speed >= MAX_RPM ||
//        motor2.target_speed >= MAX_RPM ||
//        motor3.target_speed >= MAX_RPM ||
//        motor4.target_speed >= MAX_RPM)
//    {
//      motor1.target_speed=  0;
//			motor2.target_speed=  0;
//			motor3.target_speed=  0;
//			motor4.target_speed=  0;
//    }
}

void stop_base()
{
	required_linear_vel_x = 0;
	required_linear_vel_y = 0;
	required_angular_vel = 0;
}
