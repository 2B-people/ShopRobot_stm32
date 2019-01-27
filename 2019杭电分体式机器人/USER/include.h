#ifndef _include_h
#define _include_h

#include<stdio.h>
#include<stdlib.h>


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
#include "plan.h"
#include "oled.h"
#include "bottom_sensor.h"
#include "huidu.h"
#include "key.h"
#include "queue.h"
typedef enum
{
	positive_x,
	positive_y,
	negative_x,
	negative_y
}ORIENTATION;		

extern double required_vel ;
extern uint8_t IsControlFinsh;
extern uint8_t target_position;
extern uint8_t position_x;
extern uint8_t position_y;
extern uint8_t target_position_x;
extern uint8_t target_position_y;
extern uint8_t orientation;
extern uint8_t IsHD;
extern uint8_t Obstacle;
#endif

