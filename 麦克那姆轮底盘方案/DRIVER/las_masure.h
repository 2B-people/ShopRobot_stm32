#ifndef las_masure
#define las_masure
#include "include.h"
typedef enum
{
	FORWARD=1,
	BACK=2,
	LEFT=3,
	RIGHT=4
}direction;

void changeDirection(direction dir);//选择读取距离的方向
void las_Init(void);
void las_measure(direction dir);
void las_data(direction dir);
extern uint16_t Distance_F;
extern uint16_t Distance_B;
extern uint16_t Distance_L;
extern uint16_t Distance_R;

#endif
