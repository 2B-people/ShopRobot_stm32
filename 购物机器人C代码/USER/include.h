#ifndef _include_h
#define _include_h


#include "stm32f10x.h"
#include "millisecondtimer.h"
#include "config.h"
#include "motor.h"
#include "led.h"
#include "pid.h"
#include "Kinematics.h"
#include "timer.h"
#include "remote.h"
#include "las_masure.h"
#include "usart1.h"
#include "connect.h"
extern double required_angular_vel ;
extern double required_linear_vel_x ;
extern double required_linear_vel_y ;
extern double required_pitch ;
extern double required_yaw ;
extern uint8_t IsFinsh;
#endif

