#include "pid.h"
#include "math.h"

void absLimit(float *a, float abs_max)
{
    if (*a > abs_max)
        *a = abs_max;
    if (*a < -abs_max)
        *a = -abs_max;
}

PID::PID(uint8_t pid_mode, float kp, float ki, float kd,uint32_t output_max, uint32_t integral_limit, float output_deadband)
{
   if(pid_mode == 1)
	 {
		 	pid_mode_ = POSITON_PID;
	 }
else{
			 	pid_mode_ = DELTA_PID;
}

		input_max_err_ = 0;
    output_max_ = output_max;
    integral_limit_ = integral_limit;
    output_deadband_ = output_deadband;

    kp_ = kp;
    ki_ = ki;
    kd_ = kd;
}

void PID::resetPid(float kp, float ki, float kd)
{
    kp_ = kp;
    ki_ = ki;
    kd_ = kd;

    err_[NOW] = err_[LAST] = err_[LLAST] = 0;

    pout_ = 0.0;
    iout_ = 0.0;
    dout_ = 0.0;
    out_ = 0.0;
}

float PID::calcPid(float set, float get)
{
    set_ = set;
    get_ = get;
    err_[NOW] = set - get;

    if ((input_max_err_ != 0) && (fabs(err_[NOW]) > input_max_err_))
        return 0;

    if (pid_mode_ == POSITON_PID)
    {
        pout_ = kp_ * err_[NOW];
        iout_ += ki_ * err_[NOW];
        dout_ = kd_ * (err_[NOW] - err_[LAST]);

        absLimit(&(iout_), integral_limit_);
        out_ = pout_ + iout_ + dout_;
        absLimit(&(out_), output_max_);
    }
    else if (pid_mode_ == DELTA_PID)
    {
        pout_ = kp_ * (err_[NOW] - err_[LAST]);
        iout_ = ki_ * err_[NOW];
        dout_ = kd_ * (err_[NOW] - 2 * err_[LAST] + err_[LLAST]);
        out_ = pout_ + iout_ + dout_;
        absLimit(&(out_), output_max_);
    }

    err_[LAST] = err_[NOW];
    err_[LLAST] = err_[LAST];

    if ((output_deadband_ != 0) && (fabs(out_) < output_deadband_))
        return 0;
    else
        return out_;
}
