#if !defined(KINEMATIVS_H)
#define KINEMATIVS_H

#define PI 3.1415926

class Kinematics
{
  private:
    /* data */
    float circumference_;
    int max_rpm_;
    float base_a_;
    float base_b_;
    int pwm_max_;
    int reduction_ratio_;
    float speed[4];
    int rpmTopwm(int rpm);

  public:
    struct output
    {
        int motor1;
        int motor2;
        int motor3;
        int motor4;
    };
    struct velocities
    {
        float linear_x;
        float linear_y;
        float angular_z;
    };

    Kinematics(int motor_max_rpm, float wheel_diameter, float base_a, float base_b, int reduction_ratio);

    velocities getVelocities(int rpm_motor1, int rpm_motor2, int rpm_motor3, int rpm_motor4);
    output getRPM(float linear_x, float linear_y, float angular_z);
    output getPWM(float linear_x, float linear_y, float angular_z);
    
};

#endif // KINEMATIVS_H
