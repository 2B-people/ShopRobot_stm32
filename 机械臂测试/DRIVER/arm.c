#include "arm.h"

int16_t up_dowm_1=0;												//角度加减标志					
int16_t up_dowm_3=0;

int16_t now_angle_[3]={7010,6325,6390};			//角度初始化，舵机1~3

int16_t floor_[2]={6410,6890};							//货物1，2层参数

int16_t rid_speed=4;												//舵机速度

int16_t goods[12]={6430,6430,6415,6415,6425,6405,6395,6430,6430,6415,6415,6415}; 				//抓货物
								// 雪花 红牛 网球 爽歪 魔方 娃哈 养乐 乐虎 特仑 方块 方块 方块

int16_t give_goods=6570;										//放货物


					//      7199    199    50hz
void Arm_Init(u16 arr,u16 psc)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);  
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	TIM_TimeBaseStructure.TIM_Period = arr;
	TIM_TimeBaseStructure.TIM_Prescaler =psc; 
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; 
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  
	
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseStructure); 
 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; 
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; 
	TIM_OCInitStructure.TIM_Pulse = 0; 
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	
	TIM_OC1Init(TIM2, &TIM_OCInitStructure);  
	TIM_OC2Init(TIM2, &TIM_OCInitStructure); 
	TIM_OC3Init(TIM2, &TIM_OCInitStructure); 
 

	TIM_CtrlPWMOutputs(TIM2,ENABLE);	
	
	TIM_OC1PreloadConfig(TIM2,TIM_OCPreload_Enable);  
	TIM_OC2PreloadConfig(TIM2,TIM_OCPreload_Enable); 
	TIM_OC3PreloadConfig(TIM2,TIM_OCPreload_Enable); 


	TIM_ARRPreloadConfig(TIM2,ENABLE); 
	
	TIM_Cmd(TIM2,ENABLE);  
	
	TIM_SetCompare1(TIM2,now_angle_[0]);
	TIM_SetCompare2(TIM2,now_angle_[1]);
	TIM_SetCompare3(TIM2,now_angle_[2]);
}


void Give_goods()
{
		if((give_goods-now_angle_[2])>0)
		up_dowm_3=1;
	else
		up_dowm_3=-1;
	
	for(;now_angle_[2]!=give_goods;now_angle_[2]+=up_dowm_3)		
	{
		delay(rid_speed);
		TIM_SetCompare3(TIM2,now_angle_[2]);
	}																																						//放开货物
}


void Get_goods(int16_t goods_num,int16_t floor_num)
{
	
	if((give_goods-now_angle_[2])>0)
		up_dowm_3=1;
	else
		up_dowm_3=-1;
	
	for(;now_angle_[2]!=give_goods;now_angle_[2]+=up_dowm_3)		
	{
		delay(rid_speed);
		TIM_SetCompare3(TIM2,now_angle_[2]);
	}																																						//打开机械爪
	
	
	
	if((floor_[0]-now_angle_[0])>0)
		up_dowm_1=1;

	else
		up_dowm_1=-1;

	for(;now_angle_[0]!=floor_[0];now_angle_[0]+=up_dowm_1,now_angle_[1]-=up_dowm_1)
	{
		delay(rid_speed);
		TIM_SetCompare1(TIM2,now_angle_[0]);
		TIM_SetCompare2(TIM2,now_angle_[1]);
	}																																						//到货物位置
																
	
	
	if((goods[goods_num]-now_angle_[2])>0)
		up_dowm_3=1;
	else
		up_dowm_3=-1;
	
	for(;now_angle_[2]!=goods[goods_num];now_angle_[2]+=up_dowm_3)
	{
		delay(rid_speed);
		TIM_SetCompare3(TIM2,now_angle_[2]);
	}																																						//抓取指定货物
																
	
		
	if((floor_[floor_num]-now_angle_[0])>0)
		up_dowm_1=1;

	else
		up_dowm_1=-1;

	for(;now_angle_[0]!=floor_[floor_num];now_angle_[0]+=up_dowm_1,now_angle_[1]-=up_dowm_1)
	{
		delay(rid_speed);
		TIM_SetCompare1(TIM2,now_angle_[0]);
		TIM_SetCompare2(TIM2,now_angle_[1]);
	}																																						//到达指定层数
}

