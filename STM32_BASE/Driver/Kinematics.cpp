#include "Kinematics.h"

Kinematics::Kinematics(int motor_max_rpm, float wheel_diameter, float base_a, float base_b)
{
    this->max_rpm_ = motor_max_rpm;
    this->circumference_ = PI * wheel_diameter;
    this->base_a_ = base_a;
    this->base_b_ = base_b;
}

Kinematics::output Kinematics::getRPM(float linear_x, float linear_y, float angular_z)
{
    // convert m/s to m/min
    float linear_x_mins = linear_x * 60;
    float linear_y_mins = linear_y * 60;

    // convert rad/s to rad/min
    float angular_z_mins = angular_z * 60;

    this->speed[0] = linear_y_mins - linear_x_mins + angular_z_mins * (base_a_ + base_b_);
    this->speed[1] = linear_y_mins + linear_x_mins - angular_z_mins * (base_a_ + base_b_);
    this->speed[2] = linear_y_mins - linear_x_mins - angular_z_mins * (base_a_ + base_b_);
    this->speed[3] = linear_y_mins + linear_x_mins + angular_z_mins * (base_a_ + base_b_);

    Kinematics::output rpm;

    rpm.motor1 = (int)(speed[0] / circumference_);
    rpm.motor2 = (int)(speed[1] / circumference_);
    rpm.motor3 = (int)(speed[2] / circumference_);
    rpm.motor4 = (int)(speed[3] / circumference_);

    if (rpm.motor1 <= max_rpm_ &&
        rpm.motor2 <= max_rpm_ &&
        rpm.motor3 <= max_rpm_ &&
        rpm.motor4 <= max_rpm_)
    {
        return rpm;
    }
    else
    {
        return;
    }
}

Kinematics::velocities Kinematics::getVelocities(int rpm_motor1, int rpm_motor2, int rpm_motor3, int rpm_motor4)
{
    Kinematics::velocities vel;
    float motor_speed[4];

    motor_speed[0] = rpm_motor1 * circumference_;
    motor_speed[1] = rpm_motor2 * circumference_;
    motor_speed[2] = rpm_motor3 * circumference_;
    motor_speed[3] = rpm_motor4 * circumference_;

    // get x,y linear ,m/s
    vel.linear_y = (motor_speed[0] + motor_speed[1]) / 2 / 60;
    vel.linear_x = (motor_speed[1] - motor_speed[2]) / 2 / 60;

    // get angular_z ,rad/s
    vel.angular_z = (motor_speed[0] - motor_speed[2]) / 2 / 60 / (base_a_ + base_b_);

    return vel;
}