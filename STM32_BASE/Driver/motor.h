#ifndef _MOTOR_H_
#define _MOTOR_H_

#include "pid.h"
#include "stm32f10x.h"


void CAN_Mode_Init(void);
void Set_CM_Speed(CAN_TypeDef *CANx, int16_t cm1_iq, int16_t cm2_iq, int16_t cm3_iq, int16_t cm4_iq);

void Set_YT_Speed(CAN_TypeDef *CANx, int16_t yt1_iq ,int16_t yt2_iq);

class Motor:public PID {
	
	public:
		Motor(int32_t id);	
		void Set_Output(int16_t output);
		void Get_Speed(int16_t now_speed);
		int16_t Show_Now_Speed(void);
		int16_t Show_Output(void);
		
	
	private:
		uint32_t id;
		uint16_t now_speed;
		uint16_t output;
};

#endif //_MOTOR_H_
