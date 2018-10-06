#include <stdio.h>
#include "hardwareserial.h"
#include "gy85.h"
#include "battery.h"
#include "led.h"
#include "Kinematics.h"
#include <ros.h>
#include <riki_msgs/Velocities.h>
#include <geometry_msgs/Twist.h>
#include <riki_msgs/PID.h>
#include <riki_msgs/Imu.h>
#include <riki_msgs/Battery.h>
#include <geometry_msgs/Vector3.h>
#include <ros/time.h>
#include "motor.h"

Motor motor1(0x201);
Motor motor2(0x202);
Motor motor3(0x203);
Motor motor4(0x204);



double required_angular_vel = 0;
double required_linear_vel_x = 0;
double required_liner_vel_y=0;
uint32_t previous_command_time = 0;

bool is_first = true;
bool accel, gyro, mag;


Battery bat(25, 10.6, 12.6);
Kinematics kinematics( 500 , 0.50 , 0.30 , 0.30  );


Gy85 imu;
Led led;

void pid_callback(const riki_msgs::PID &pid);
void command_callback(const geometry_msgs::Twist &cmd_msg);

ros::NodeHandle nh;

riki_msgs::Imu raw_imu_msg;
riki_msgs::Velocities raw_vel_msg;
riki_msgs::Battery raw_battery_msg;

ros::Subscriber<geometry_msgs::Twist> cmd_sub("cmd_vel", command_callback);
ros::Subscriber<riki_msgs::PID> pid_sub("pid", pid_callback);
ros::Publisher raw_vel_pub("raw_vel", &raw_vel_msg);
ros::Publisher raw_imu_pub("raw_imu", &raw_imu_msg);
ros::Publisher raw_battery_pub("battery", &raw_battery_msg);

void pid_callback(const riki_msgs::PID &pid)
{
    // TODO using our PID function
		motor1.motor_PID.Set_PID(pid.p1, pid.i1, pid.d1,pid.max,pid.min);
		motor2.motor_PID.Set_PID(pid.p2, pid.i2, pid.d2,pid.max,pid.min);
		motor3.motor_PID.Set_PID(pid.p3, pid.i3, pid.d3,pid.max,pid.min);
		motor4.motor_PID.Set_PID(pid.p4, pid.i4, pid.d4,pid.max,pid.min);
}

void command_callback(const geometry_msgs::Twist &cmd_msg)
{
    // TODO using our /cmd_msg
     required_linear_vel_x = cmd_msg.linear.x;
		 required_linear_vel_y = cmd_msg.linear.y;
     required_angular_vel = cmd_msg.angular.z;
		
			previous_command_time = millis();
}

void move_base()		//运动学解析
{
    Kinematics::output req_rpm;		
		req_rpm=getRPM(required_linear_vel_x,  required_linear_vel_y,  required_angular_vel);
		motor1.Set_Speed(req_rpm.motor1);
		motor2.Set_Speed(req_rpm.motor1);
		motor3.Set_Speed(req_rpm.motor1);
		motor4.Set_Speed(req_rpm.motor1);
		Set_CM_Speed(CAN1,
		motor1.motor_PID.PID_calculate(motor1.Show_Target_Speed(),motor1.Show_Now_Speed()),
		motor2.motor_PID.PID_calculate(motor2.Show_Target_Speed(),motor2.Show_Now_Speed()),
		motor3.motor_PID.PID_calculate(motor3.Show_Target_Speed(),motor3.Show_Now_Speed()),
		motor4.motor_PID.PID_calculate(motor4.Show_Target_Speed(),motor4.Show_Now_Speed()));
	
}

//berif: publish the linear msg to ROS 
void publish_linear_velocity()
{
    // TODO using kinematics to get 
    // motor1.updateSpeed(encoder1.read());
    // motor2.updateSpeed(encoder2.read());

    // Kinematics::velocities vel;
    // vel = kinematics.getVelocities(motor1.rpm, motor2.rpm);

    // //fill in the object
    // raw_vel_msg.linear_x = vel.linear_x;
    // raw_vel_msg.linear_y = 0.0;
    // raw_vel_msg.angular_z = vel.angular_z;

    //publish raw_vel_msg object to ROS
    raw_vel_pub.publish(&raw_vel_msg);
}

void check_imu()
{
    gyro = imu.check_gyroscope();
    accel = imu.check_accelerometer();
    mag = imu.check_magnetometer();

    if (!accel)
    {
        nh.logerror("Accelerometer NOT FOUND!");
    }

    if (!gyro)
    {
        nh.logerror("Gyroscope NOT FOUND!");
    }

    if (!mag)
    {
        nh.logerror("Magnetometer NOT FOUND!");
    }
    is_first = false;
}

void publish_imu()
{
    //geometry_msgs::Vector3 acceler, gyro, mag;
    //this function publishes raw IMU reading
    //measure accelerometer
    if (accel)
    {
        imu.measure_acceleration();
        raw_imu_msg.linear_acceleration = imu.raw_acceleration;
    }

    //measure gyroscope
    if (gyro)
    {
        imu.measure_gyroscope();
        raw_imu_msg.angular_velocity = imu.raw_rotation;
    }

    //measure magnetometer
    if (mag)
    {
        imu.measure_magnetometer();
        raw_imu_msg.magnetic_field = imu.raw_magnetic_field;
    }

    //publish raw_imu_msg object to ROS
    raw_imu_pub.publish(&raw_imu_msg);
}

void stop_base()
{
    // TODO repair we control funtion and variable
    required_linear_vel = 0;
    required_angular_vel = 0;
}

void publishBAT()
{
    raw_battery_msg.battery = bat.get_volt();
    raw_battery_pub.publish(&raw_battery_msg);
}

void print_debug()
{
    // TODO using we debug function
    char buffer[50];
    //order milemeter msg when debug 
    //sprintf(buffer, "Encoder Left: %ld", encoder1.read());
    nh.loginfo(buffer);
    //sprintf(buffer, "Encoder Right: %ld", encoder2.read());
    nh.loginfo(buffer);
    //sprintf (buffer, "get line speed : %f, pwm: %d", required_linear_vel, pwm);
    //nh->loginfo(buffer);
}

int main(void)
{
    bool OnOff = true;
    uint32_t previous_battery_debug_time = 0;
    uint32_t previous_debug_time = 0;
    uint32_t previous_imu_time = 0;
    uint32_t previous_control_time = 0;
    uint32_t publish_vel_time = 0;
    char battery_buffer[] = "The voltage is lower than 11.3V,Please charge! ";

    SystemInit();
    initialise();

    //motor1.init();
    //motor2.init();
    //encoder1.init();
    //encoder2.init();
    led.init();
    imu.init();
    bat.init();

    nh.initNode();
    nh.advertise(raw_vel_pub);
    nh.advertise(raw_imu_pub);
    nh.advertise(raw_battery_pub);
    nh.subscribe(pid_sub);
    nh.subscribe(cmd_sub);

    while (!nh.connected())
    {
        nh.spinOnce();
    }
    nh.loginfo("Shopbase Connected!");

    led.on_off(OnOff);

    while (1)
    {
        if ((millis() - previous_control_time) >= (1000 / COMMAND_RATE))
        {
            move_base();
            previous_control_time = millis();
        }

        if ((millis() - previous_command_time) >= 400)
        {
            stop_base();
        }

        if ((millis() - publish_vel_time) >= (1000 / VEL_PUBLISH_RATE))
        {
            publish_linear_velocity();
            publish_vel_time = millis();
        }

        if ((millis() - previous_imu_time) >= (1000 / IMU_PUBLISH_RATE))
        {
            if (is_first)
            {
                //sanity check if the IMU exits
                check_imu();
            }
            else
            {
                //publish the IMU data
                publish_imu();
            }
            previous_imu_time = millis();
        }

        if ((millis() - previous_battery_debug_time) >= (1000 / BAT_PUBLISH_RATE))
        {
            if (bat.get_volt() < 11.300000)
            {
                OnOff = !OnOff;
                led.on_off(OnOff);
                nh.logwarn(battery_buffer);
            }
            publishBAT();
            previous_battery_debug_time = millis();
        }

        if (DEBUG)
        {
            if ((millis() - previous_debug_time) >= (1000 / DEBUG_RATE))
            {
                print_debug();
                previous_debug_time = millis();
            }
        }

        nh.spinOnce();
    }
}
