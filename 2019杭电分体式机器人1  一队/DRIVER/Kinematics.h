#ifndef _Kinematics_h
#define _Kinematics_h
#include "include.h"
float get_RPM(float liner_vel_in);
void waitingStop(void);
void decideSpeed(void);
extern uint8_t lsx;
extern uint8_t lsy;
#endif

