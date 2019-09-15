#include "motor.h"

GPIO_TypeDef* MOTOR_PORT[MOTORn] = {RIKI_MOTOR1_GPIO_PORT, RIKI_MOTOR2_GPIO_PORT, RIKI_MOTOR3_GPIO_PORT, RIKI_MOTOR4_GPIO_PORT};
GPIO_TypeDef* MOTOR_PWM_PORT[MOTORn] = {RIKI_MOTOR1_PWM_PORT, RIKI_MOTOR2_PWM_PORT,RIKI_MOTOR3_PWM_PORT, RIKI_MOTOR4_PWM_PORT};
TIM_TypeDef*  MOTOR_PWM_TIM[MOTORn] = {RIKI_MOTOR1_PWM_TIM, RIKI_MOTOR2_PWM_TIM,RIKI_MOTOR3_PWM_TIM, RIKI_MOTOR4_PWM_TIM};
const uint32_t  MOTOR_PORT_CLK[MOTORn] = {RIKI_MOTOR1_GPIO_CLK, RIKI_MOTOR2_GPIO_CLK,RIKI_MOTOR3_GPIO_CLK, RIKI_MOTOR4_GPIO_CLK};
const uint32_t  MOTOR_PWM_PORT_CLK[MOTORn] = {RIKI_MOTOR1_PWM_CLK, RIKI_MOTOR2_PWM_CLK,RIKI_MOTOR3_PWM_CLK, RIKI_MOTOR4_PWM_CLK};
const uint32_t  MOTOR_PWM_TIM_CLK[MOTORn] = {RIKI_MOTOR1_PWM_TIM_CLK, RIKI_MOTOR2_PWM_TIM_CLK,RIKI_MOTOR3_PWM_TIM_CLK, RIKI_MOTOR4_PWM_TIM_CLK};
const uint16_t  MOTOR_A_PIN[MOTORn] = {RIKI_MOTOR1_A_PIN, RIKI_MOTOR2_A_PIN,RIKI_MOTOR3_A_PIN, RIKI_MOTOR4_A_PIN};
const uint16_t  MOTOR_B_PIN[MOTORn] = {RIKI_MOTOR1_B_PIN, RIKI_MOTOR2_B_PIN,RIKI_MOTOR3_B_PIN, RIKI_MOTOR4_B_PIN};
const uint16_t  MOTOR_PWM_PIN[MOTORn] = {RIKI_MOTOR1_PWM_PIN, RIKI_MOTOR2_PWM_PIN,RIKI_MOTOR3_PWM_PIN, RIKI_MOTOR4_PWM_PIN};


Motor::Motor(Motor_TypeDef _motor, uint32_t _arr, uint32_t _psc)
{
	motor = _motor;
	arr = _arr;
	psc = _psc;
}

void Motor::init()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(MOTOR_PORT_CLK[this->motor] , ENABLE);
	 /** init motor gpio **/
	GPIO_InitStructure.GPIO_Pin     = MOTOR_A_PIN[this->motor] | MOTOR_B_PIN[this->motor];
	GPIO_InitStructure.GPIO_Mode    = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed   = GPIO_Speed_50MHz;
	GPIO_Init(MOTOR_PORT[this->motor], &GPIO_InitStructure);

	/** init motor pwm gpio **/
	GPIO_InitStructure.GPIO_Pin     = MOTOR_PWM_PIN[this->motor];
	GPIO_InitStructure.GPIO_Mode    = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed   = GPIO_Speed_50MHz;
	GPIO_Init(MOTOR_PWM_PORT[this->motor], &GPIO_InitStructure);

	motor_pwm_init();
}

void Motor::motor_pwm_init()
{
	//pwm value ((1 + psc)/72M)*(1+arr)
	//eg: ((1+143)/72M)*(1+9999) = 0.02s --10000 count use 0.02s
	//set arduino pwm value 490hz 255 count 
	//((1 + 575)/72M)(1 + 254) = (1 / 490)
	TIM_TimeBaseInitTypeDef TIM_BaseInitStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;

	RCC_APB2PeriphClockCmd(MOTOR_PWM_TIM_CLK[this->motor], ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);//�˿���ӳ��
	GPIO_PinRemapConfig(GPIO_FullRemap_TIM1,ENABLE);  
	
	TIM_BaseInitStructure.TIM_Period                = this->arr;
	TIM_BaseInitStructure.TIM_Prescaler             = this->psc;
	TIM_BaseInitStructure.TIM_ClockDivision         = TIM_CKD_DIV1;
	TIM_BaseInitStructure.TIM_CounterMode           = TIM_CounterMode_Up;
	TIM_BaseInitStructure.TIM_RepetitionCounter     = 0;

	TIM_TimeBaseInit(MOTOR_PWM_TIM[this->motor], &TIM_BaseInitStructure);

	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; 
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 0; 
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; 

	if(this->motor == MOTOR1){
		TIM_OC1Init(MOTOR_PWM_TIM[this->motor], &TIM_OCInitStructure);
		TIM_OC1PreloadConfig(MOTOR_PWM_TIM[this->motor], TIM_OCPreload_Enable);
	}

	if(this->motor == MOTOR2) {
		TIM_OC2Init(MOTOR_PWM_TIM[this->motor], &TIM_OCInitStructure);
		TIM_OC2PreloadConfig(MOTOR_PWM_TIM[this->motor], TIM_OCPreload_Enable);
	}
	if(this->motor == MOTOR3) {
		TIM_OC3Init(MOTOR_PWM_TIM[this->motor], &TIM_OCInitStructure);
		TIM_OC3PreloadConfig(MOTOR_PWM_TIM[this->motor], TIM_OCPreload_Enable);
	}
	if(this->motor == MOTOR4) {
		TIM_OC4Init(MOTOR_PWM_TIM[this->motor], &TIM_OCInitStructure);
		TIM_OC4PreloadConfig(MOTOR_PWM_TIM[this->motor], TIM_OCPreload_Enable);
	}
	TIM_ARRPreloadConfig(MOTOR_PWM_TIM[this->motor], ENABLE);

	TIM_CtrlPWMOutputs(MOTOR_PWM_TIM[this->motor], ENABLE);
	TIM_Cmd(MOTOR_PWM_TIM[this->motor], ENABLE);
}

void Motor::spin(int pwm)
{
<<<<<<< HEAD:测试麦轮用程序/Driver/motor.cpp
	if(pwm > 0)
	{
		switch(this->motor)
		{
			case MOTOR1:
				TIM_SetCompare1(MOTOR_PWM1_TIM[this->motor], abs(pwm));
				TIM_SetCompare1(MOTOR_PWM2_TIM[this->motor], 0);	
			break;
			case MOTOR2:
				TIM_SetCompare2(MOTOR_PWM1_TIM[this->motor], abs(pwm));
				TIM_SetCompare2(MOTOR_PWM2_TIM[this->motor], 0);	
			case MOTOR3:
				TIM_SetCompare3(MOTOR_PWM1_TIM[this->motor], abs(pwm));
				TIM_SetCompare3(MOTOR_PWM2_TIM[this->motor], 0);	
			case MOTOR4:
				TIM_SetCompare4(MOTOR_PWM1_TIM[this->motor], abs(pwm));
				TIM_SetCompare4(MOTOR_PWM2_TIM[this->motor], 0);	
		}
	}
	else if(pwm < 0) 
	{
		switch(this->motor)
		{
			case MOTOR1:
				TIM_SetCompare1(MOTOR_PWM2_TIM[this->motor], abs(pwm));
				TIM_SetCompare1(MOTOR_PWM1_TIM[this->motor], 0);	
			break;
			case MOTOR2:
				TIM_SetCompare2(MOTOR_PWM2_TIM[this->motor], abs(pwm));
				TIM_SetCompare2(MOTOR_PWM1_TIM[this->motor], 0);	
			case MOTOR3:
				TIM_SetCompare3(MOTOR_PWM2_TIM[this->motor], abs(pwm));
				TIM_SetCompare3(MOTOR_PWM1_TIM[this->motor], 0);	
			case MOTOR4:
				TIM_SetCompare4(MOTOR_PWM2_TIM[this->motor], abs(pwm));
				TIM_SetCompare4(MOTOR_PWM1_TIM[this->motor], 0);	
		}
=======
	if(pwm > 0){
		GPIO_SetBits(MOTOR_PORT[this->motor], MOTOR_A_PIN[this->motor]);
		GPIO_ResetBits(MOTOR_PORT[this->motor], MOTOR_B_PIN[this->motor]);
	}else if(pwm < 0) {
		GPIO_SetBits(MOTOR_PORT[this->motor], MOTOR_B_PIN[this->motor]);
		GPIO_ResetBits(MOTOR_PORT[this->motor], MOTOR_A_PIN[this->motor]);
	}
	if(this->motor == MOTOR1){
		TIM_SetCompare1(MOTOR_PWM_TIM[this->motor], abs(pwm));
	}
	if(this->motor == MOTOR2){
		TIM_SetCompare2(MOTOR_PWM_TIM[this->motor], abs(pwm));
>>>>>>> parent of cff8acb... 编码器与电机修改:编码器版/Driver/motor.cpp
	}
}


void Motor::updateSpeed(long encoder_ticks)
{
	//this function calculates the motor's RPM based on encoder ticks and delta time
	unsigned long current_time = millis();
	unsigned long dt = current_time - prev_update_time_;

	//convert the time from milliseconds to minutes
	double dtm = (double)dt / 60000;
	double delta_ticks = encoder_ticks - prev_encoder_ticks_;

	//calculate wheel's speed (RPM)
	rpm = (delta_ticks / counts_per_rev_) / dtm;

	prev_update_time_ = current_time;
	prev_encoder_ticks_ = encoder_ticks;
}

