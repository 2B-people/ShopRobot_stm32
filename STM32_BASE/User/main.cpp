#include <stdio.h>
#include "hardwareserial.h"
#include "gy85.h"
#include "led.h"
#include "motor.h"
#include "timer.h"
#include "control.h"
#include "Kinematics.h"

#include <ros.h>

#include <shop_msgs/Imu.h>
#include <shop_msgs/LaserScan.h>
#include <shop_msgs/Pid.h>
#include <shop_msgs/Velocities.h>

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

Kinematics kinematics(MAX_RPM, WHEEL_DIAMETER, 0.165, 0.12,COUNTS_PER_REV);

Led led;

void pid_callback(const shop_msgs::Pid &pid);
void command_callback(const geometry_msgs::Twist &cmd_msg);

ros::NodeHandle nh;

shop_msgs::Imu raw_imu_msg;
shop_msgs::Velocities raw_vel_msg;
shop_msgs::LaserScan raw_scan_msg;

ros::Subscriber<geometry_msgs::Twist> cmd_sub("cmd_vel", command_callback);
ros::Subscriber<shop_msgs::Pid> pid_sub("pid", pid_callback);
ros::Publisher raw_vel_pub("raw_vel", &raw_vel_msg);
ros::Publisher raw_imu_pub("raw_imu", &raw_imu_msg);
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
    Kinematics::velocities vel;
    vel = kinematics.getVelocities(motor1.Show_Now_Speed(), motor2.Show_Now_Speed(),
                                   motor3.Show_Now_Speed(), motor4.Show_Now_Speed());

    raw_vel_msg.linear_x = vel.linear_x;
    raw_vel_msg.linear_y = vel.linear_y;
    raw_vel_msg.angular_z = vel.angular_z;

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

void publisher_debug()
{
    char buffer[50];
    sprintf(buffer, "motor1 speed :%d ,pidout:%lf", motor1.Show_Now_Speed(), err1);
    nh.loginfo(buffer);
    sprintf(buffer, "motor2 speed :%d ,pidout:%lf", motor2.Show_Now_Speed(), err2);
    nh.loginfo(buffer);
    sprintf(buffer, "motor3 speed :%d ,pidout:%lf", motor3.Show_Now_Speed(), err3);
    nh.loginfo(buffer);
    sprintf(buffer, "motor4 speed :%d ,pidout:%lf", motor4.Show_Now_Speed(), err4);
    nh.loginfo(buffer);
    sprintf(buffer, "x:%lf y:%lf z:%lf", required_linear_vel_x, required_linear_vel_y, required_angular_vel);
    nh.loginfo(buffer);
    sprintf(buffer, "time:%d", millis());
    nh.loginfo(buffer);
}

int main(void)
{
    uint32_t publish_vel_time = 0;
    uint32_t publish_scan_time = 0;
    uint32_t previous_debug_time = 0;

    SystemInit();
    initialise();
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    TIM5_Int_Init(71, 9999);
    CAN_Mode_Init();

    nh.initNode();
    nh.advertise(raw_vel_pub);
    nh.advertise(raw_imu_pub);
    nh.advertise(raw_larscan_pub);
    nh.subscribe(pid_sub);
    nh.subscribe(cmd_sub);

    while (!nh.connected())
    {
        nh.spinOnce();
    }
    nh.loginfo("Shopbase Connected!");
    led.on_off(true);

    while (1)
    {
        if ((millis() - publish_vel_time) >= (1000 / VEL_PUBLISH_RATE))
        {
            publisher_linear_velocities();
            publish_vel_time = millis();
        }
        if ((millis() - previous_command_time) >= 400)
        {
            stop_base();
        }
        if ((millis() - publish_scan_time) >= (1000 / VEL_PUBLISH_RATE))
        {
            publisher_laser_scan();
            publish_scan_time = millis();
        }
        if (DEBUG)
        {
            if ((millis() - previous_debug_time) >= (1000 / DEBUG_RATE))
            {
                publisher_debug();
                previous_debug_time = millis();
            }
        }
        nh.spinOnce();
    }
}
