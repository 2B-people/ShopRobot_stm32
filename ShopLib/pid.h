#ifndef __PID_H_
#define __PID_H_

#include "stm32f103.h"

class PID
{
public:
  enum
  {
    LLAST = 0,
    LAST,
    NOW,
    POSITON_PID,
    DELTA_PID,
  };
  
  PID(enum pid_mode, uint32_t output_max = 0, uint32_t integral_limit = 0, float output_deadband = 0, float kp, float ki, float kd);
  void resetPid(float kp, float ki, float kd);
  float calcPid(float set, float get);

private:
  enum mode_;

  uint32_t output_max_;
  uint32_t integral_limit_;

  float kp_;
  float ki_;
  float kd_;

  float set_;
  float get_;
  float err_[3] = {0, 0, 0};

  float pout_ = 0;
  float iout_ = 0;
  float dout_ = 0;
  float out_ = 0;

  float input_max_err_;   //input max err;
  float output_deadband_; //output deadband;

  void adsLimit(float *a, float abs_max);
};

#endif // __PID_H_
