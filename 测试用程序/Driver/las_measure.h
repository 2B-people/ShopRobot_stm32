#ifndef _las_measure
#define _las_measure
#include "config.h"
typedef enum
{
	forward=1,
	back=2,
	left=3,
	right=4
}direction;
void changeDirection(direction dir);//选择读取距离的方向
void las_Init();
void las_measure();
uint16_t las_data(direction dir);
#endif