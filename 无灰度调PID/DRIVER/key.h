#ifndef KEY_H
#define KEY_H

#include "include.h"

#define KEY1_PRES 	1	//KEY1按下
#define KEY2_PRES  	2	//KEY2按下
#define KEY3_PRES 	3	//KEY3按下
#define KEY4_PRES   4	//KEY4按下
#define KEY5_PRES   5	//KEY5按下
#define KEY6_PRES	  6	//KEY6按下

#define KEY1  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)//读取按键1
#define KEY2  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_5)//读取按键2
#define KEY3  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_6)//读取按键3 
#define KEY4  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_7)//读取按键4
#define KEY5  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_8)//读取按键5
#define KEY6  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_9)//读取按键6 

u8 KEY_Scan(u8 mode);
void KEY_Init(void); //IO初始化
	
#endif
