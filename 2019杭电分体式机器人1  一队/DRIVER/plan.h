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
void begin1(void);
void begin2(void);
void begin3(void);
void begin4(void);
void patrol1(void);
void patrol2(void);
void patrol3(void);
void toCoordinate(uint8_t x,uint8_t y);
extern uint8_t nextx;
extern uint8_t nexty;
extern uint8_t patrolStatus;
extern int8_t next_x[11];
extern int8_t next_y[11];
extern uint8_t IsPathCalFinish;
#endif

