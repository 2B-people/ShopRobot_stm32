#ifndef _plan_h
#define _plan_h
#include "include.h"
void MOVE(uint8_t _target_position_x,uint8_t _target_position_y);
void ROTATE(uint8_t Clockwise);//Clockwise为1顺时针
void move_control(void);
extern uint8_t IsMoveFinsh;
extern uint8_t IsRotate;

#define fast_vel 0.5		//一般情况下车速
#define slow_vel 0.1		//车子还在运行状态的最低车速
#define down_vel 0.0005	//达到最后一格时，每个周期减下的速度

#endif

