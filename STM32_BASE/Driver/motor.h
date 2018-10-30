#ifndef _MOTOR_H_
#define _MOTOR_H_

#include "pid.h"
#include "config.h"

void CAN_Mode_Init(void);
void Set_CM_Speed(CAN_TypeDef *CANx, int16_t cm1_iq, int16_t cm2_iq, int16_t cm3_iq, int16_t cm4_iq);

class Motor:public PID {
	public:
		Motor(uint32_t id);	
		void Set_Speed(uint16_t target_speed);
		void Get_Speed(uint16_t now_speed);
		uint16_t Show_Now_Speed(void);
		uint16_t Show_Target_Speed(void);
	
	private:
		uint32_t id;
		uint16_t now_speed;
		uint16_t target_speed;
};

#endif //_MOTOR_H_
