#include <stdio.h>
#include "millisecondtimer.h"
#include "hardwareserial.h"
#include "config.h"
#include "gy85.h"
#include "led.h"
#include "motor.h"
#include "Kinematics.h"
#include <ros.h>
#include <ros/time.h>
#include <riki_msgs/Velocities.h>
#include <geometry_msgs/Twist.h>
#include <riki_msgs/PID.h>
#include <riki_msgs/Imu.h>
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

void move_base()
{
    //    Kinematics::output req_rpm;
    //		req_rpm=kinematics.getRPM(required_linear_vel_x,  required_linear_vel_y,  required_angular_vel);
    //		motor1.Set_Speed(req_rpm.motor1);
    //		motor2.Set_Speed(req_rpm.motor1);
    //		motor3.Set_Speed(req_rpm.motor1);
    //		motor4.Set_Speed(req_rpm.motor1);
    //		Set_CM_Speed(CAN1,
    //		motor1.motor_PID.PID_calculate(motor1.Show_Target_Speed(),motor1.Show_Now_Speed()),
    //		motor2.motor_PID.PID_calculate(motor2.Show_Target_Speed(),motor2.Show_Now_Speed()),
    //		motor3.motor_PID.PID_calculate(motor3.Show_Target_Speed(),motor3.Show_Now_Speed()),
    //		motor4.motor_PID.PID_calculate(motor4.Show_Target_Speed(),motor4.Show_Now_Speed()));

    Set_CM_Speed(CAN1, 1000, 1000, 1000, 1000);
}

void stop_base()
{
    // TODO repair we control funtion and variable

    required_linear_vel_x = 0;
    required_linear_vel_y = 0;
    required_angular_vel = 0;
}

int main(void)
{

    uint32_t previous_control_time = 0;
    uint32_t publish_vel_time = 0;

    SystemInit();
    initialise();
    CAN_Mode_Init(); //初始化CAN总线

    while (1)
    {
        if ((millis() - previous_control_time) >= (1000 / COMMAND_RATE))
        {
            move_base();
            previous_control_time = millis();
        }

        if ((millis() - publish_vel_time) >= (1000 / VEL_PUBLISH_RATE))
        {
            publish_vel_time = millis();
        }
    }
}
