#include <stdio.h>
#include "millisecondtimer.h"
#include "hardwareserial.h"
#include "config.h"
#include "gy85.h"
#include "led.h"
#include "motor.h"
#include "Kinematics.h"

#include <shop_msgs/Imu.h>
#include <shop_msgs/LaserDistance.h>
#include <shop_msgs/Pid.h>
#include <shop_msgs/Velocities.h>

#include <ros.h>
#include <ros/time.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/Vector3.h>


Motor motor1(0x201);
Motor motor2(0x202);
Motor motor3(0x203);
Motor motor4(0x204);

double required_angular_vel = 0;
double required_linear_vel_x = 0;
double required_linear_vel_y = 0;
uint32_t previous_command_time = 0;

Kinematics kinematics(500, 0.50, 0.30, 0.30);

Led led;



int main(void)
{

	
}
