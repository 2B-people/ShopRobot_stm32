#ifndef __PID_H_
#define __PID_H_

#include "config.h"

enum PidTpyeDef
{
  LLAST = 0,
  LAST,
  NOW,
  POSITON_PID,
  DELTA_PID,
};

class PID
{
public:
  PID(PidTpyeDef pid_mode, float kp, float ki, float kd, uint32_t output_max, uint32_t integral_limit, float output_deadband);
  void resetPid(float kp, float ki, float kd);
  float calcPid(float set, float get);

private:
  PidTpyeDef pid_mode_;

  uint32_t output_max_;
  uint32_t integral_limit_;

  float kp_;
  float ki_;
  float kd_;

  float set_;
  float get_;
  float err_[3];

  float pout_;
  float iout_;
  float dout_;
  float out_;

  float input_max_err_;   //input max err;
  float output_deadband_; //output deadband;

  void adsLimit(float *a, float abs_max);
};

#endif // __PID_H_
