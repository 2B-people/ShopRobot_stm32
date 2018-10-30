#include <stdio.h>
#include "millisecondtimer.h"
#include "hardwareserial.h"
#include "config.h"
#include "gy85.h"
#include "led.h"
#include "motor.h"
#include "Kinematics.h"

#include <shop_msgs/Imu.h>
#include <shop_msgs/LaserScan.h>
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

void pid_callback(const shop_msgs::Pid &pid);
void command_callback(const geometry_msgs::Twist &cmd_msg);

ros::NodeHandle nh;

//shop_msgs::Imu raw_vel_msg;
shop_msgs::Velocities raw_vel_msg;
shop_msgs::LaserScan raw_scan_msg;

ros::Subscriber<geometry_msgs::Twist> cmd_sub("cmd_vel", command_callback);
ros::Subscriber<shop_msgs::Pid> pid_sub("pid", pid_callback);
ros::Publisher raw_vel_pub("raw_vel", &raw_vel_msg);
//ros::Publisher raw_imu_pub("raw_imu", &raw_imu_msg);
ros::Publisher raw_larscan_pub("raw_larscan_msg", &raw_scan_msg);

void pid_callback(const shop_msgs::Pid &pid)
{
    motor1.resetPid(pid.p, pid.i, pid.d);
    motor2.resetPid(pid.p, pid.i, pid.d);
    motor3.resetPid(pid.p, pid.i, pid.d);
    motor4.resetPid(pid.p, pid.i, pid.d);
}

void command_callback(const geometry_msgs::Twist &cmd_msg)
{
    required_linear_vel_x = cmd_msg.linear.x;
    required_linear_vel_y = cmd_msg.linear.y;
    required_angular_vel = cmd_msg.angular.z;

    previous_command_time = millis();
}

void publisher_linear_velocities()
{
    raw_vel_msg.linear_x = 1.0;
    raw_vel_msg.linear_y = 1.0;
    raw_vel_msg.angular_z = 1.0;

    raw_vel_pub.publish(&raw_vel_msg);
}

void publisher_laser_scan()
{
    raw_scan_msg.scan1_ranges = 2.0;
    raw_scan_msg.scan2_ranges = 2.0;
    raw_scan_msg.scan3_ranges = 2.0;
    raw_scan_msg.scan4_ranges = 2.0;
    raw_scan_msg.scan_time = 11.0;

    raw_larscan_pub.publish(&raw_scan_msg);
}

int main(void)
{
    uint32_t publish_vel_time = 0;
    uint32_t publish_scan_time = 0;

    SystemInit();
    initialise();

    nh.initNode();
    nh.advertise(raw_vel_pub);
    //nh.advertise(raw_imu_pub);
    nh.advertise(raw_larscan_pub);
    nh.subscribe(pid_sub);
    nh.subscribe(cmd_sub);

    while (!nh.connected())
    {
        nh.spinOnce();
    }
    nh.loginfo("Rikibase Connected!");


    while (1)
    {
        if ((millis() - publish_vel_time) >= (1000 / VEL_PUBLISH_RATE))
        {
            publisher_linear_velocities();
            publish_vel_time = millis();
        }
        if ((millis() - publish_scan_time) >= (1000 / VEL_PUBLISH_RATE))
        {
            publisher_laser_scan();
            publish_scan_time = millis();
        }
				        nh.spinOnce();
    }
}
