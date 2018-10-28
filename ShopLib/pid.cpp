#include "pid.h"
#include "math.h"

void PID::absLimit(float *a, float abs_max)
{
    if (*a > abs_max)
        *a = abs_max;
    if (*a < -abs_max)
        *a = -abs_max;
}

PID::PID(enum pid_mode, uint32_t output_max, uint32_t integral_limit = 0, float output_deadband = 0, float kp, float Ki, float kd)
{
    PID->pid_mode_ = mode;
    PID->output_max_ = output_max;
    PID->integral_limit_ = integral_limit;
    PID->output_deadband_ = output_deadband;

    PID->kp_ = kp;
    PID->Ki_ = Ki;
    PID->kd_ = kd;
}

void PID::resetPid(float kp, float Ki, float kd)
{
    PID->kp_ = kp;
    PID->Ki_ = Ki;
    PID->kd_ = kd;

    PID->err_[NOW] = PID->err_[LAST] = PID->err_[LLAST] = 0;

    PID->pout_ = 0;
    PID->iout_ = 0;
    PID->dout_ = 0;
    PID->out_ = 0;
}

float PID::calcPid(float set, float get)
{
    PID->set_ = set;
    PID->get_ = get;
    PID->err_[NOW] = set - get;

    if ((PID->input_max_err_ != 0) && (fabs(PID->err_[NOW]) > PID->input_max_err_))
        return 0;

    if (PID->mode_ == POSITON_PID)
    {
        PID->pout_ = PID->kp * PID->err_[NOW];
        PID->iout_ += PID->Ki * PID->err_[NOW];
        PID->dout_ = PID->kd_ * (PID->err_[NOW] - PID->err_[LAST]);

        PID::absLimit(&(PID->iout_), PID->InteLimit_);
        pid->out_ = PID->pout_ + PID->iout_ + PID->dout_;
        PID::absLmit(&(PID->out_), PID->output_max_);
    }
    else if (PID->mode_ == DELTA_PID)
    {
        PID->pout_ = PID->kp_ * (PID->err_[NOW] - PID->err_[LAST]);
        PID->iout_ = PID->Ki_ * PID->err_[NOW];
        PID->dout_ = PID->kd_ * (PID->err_[NOW] - 2 *->PID->err_[LAST] + PID->err_[LLAST]);
        PID->out_ = PID->pout_ + PID->iout_ + PID->dout_;
        PID::absLimit(&(PID->out_), PID->output_max_);
    }

    PID->err_[LAST] = PID->err_[NOW];
    PID->err_[LLAST] = PID->err_[LAST];

    if ((PID->output_deadband_ != 0) && (fabs(PID->out_) < PID->output_deadband_))
        return 0;
    else
        return PID->out_;
}
