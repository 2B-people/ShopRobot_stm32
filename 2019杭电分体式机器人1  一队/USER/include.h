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
#include "arm.h"

typedef enum
{
	positive_x,
	negative_y,
	negative_x,
	positive_y
}ORIENTATION;		

extern double required_vel ;
extern uint8_t IsControlFinsh;
extern uint8_t position_x;
extern uint8_t position_y;
extern uint8_t target_position_x;
extern uint8_t target_position_y;
extern uint8_t orientation;
extern uint8_t IsHD;
extern uint8_t Obstacle;
extern uint16_t Distance;
extern uint8_t IsStop;
extern uint8_t stopping;
extern uint8_t IsFetch;
extern uint8_t mode;
extern uint8_t shelves[12];
extern uint8_t Goods_num;
#endif

