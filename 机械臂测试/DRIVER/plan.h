#ifndef _plan_h
#define _plan_h
#include "include.h"
void MOVE(uint8_t _target_position_x,uint8_t _target_position_y);
int8_t check(int x, int y);
void bfs(void);
extern uint8_t IsMoveFinsh;
extern uint8_t IsRotate;
void show(int8_t x, int8_t y);
void path_cal(void);
void path_Init(void);
void move_base(void);
#endif

