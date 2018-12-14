#ifndef motor_h
#define motor_h
#include "include.h"
#include "pid.h"
void CAN_Mode_Init(void);

void Set_CM_Speed(CAN_TypeDef *CANx, int16_t cm1_iq, int16_t cm2_iq);

void Set_YT_Speed(CAN_TypeDef *CANx, int16_t yt1_iq ,int16_t yt2_iq);
typedef struct
{
	uint16_t now_speed;			//当前转速
	uint16_t output;				//pid输出
	int32_t target_speed;		//目标转速
}Motor;//speed单位RPM

extern Motor motor1;
extern Motor motor2;
extern Motor motor3;
extern Motor motor4;
extern Motor yt_motor1;
extern Motor yt_motor2;
#endif
