#ifndef arm_h
#define arm_h
#include "include.h"

void Arm_Init(u16 arr,u16 psc);								//	初始化

void Arm_run(void);														//	初始化

void Get_goods(int16_t goods_num);						//	抓货物（参数为货物编号）

void Goods_floor(int16_t floor_num);					//	放置层数

void Give_goods(void);												//	放货物

void Com_run(void);														//  平时跑


#endif

