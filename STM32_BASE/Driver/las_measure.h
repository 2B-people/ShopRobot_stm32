#ifndef _las_measure
#define _las_measure
#include "config.h"

void changeDirection(direction dir);//选择读取距离的方向
void las_Init();
void las_measure();
uint16_t las_data(direction dir);
#endif