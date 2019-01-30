#include "bottom_sensor.h"
void infrared_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
 
 	RCC_APB2PeriphClockCmd(infrared_CLK1,ENABLE);//使能PORTA,PORTE时钟
	GPIO_InitStructure.GPIO_Pin  = infrared_PIN1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置成上拉输入
 	GPIO_Init(infrared_PORT1, &GPIO_InitStructure);

	RCC_APB2PeriphClockCmd(infrared_CLK2,ENABLE);//使能PORTA,PORTE时钟
	GPIO_InitStructure.GPIO_Pin  = infrared_PIN2;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置成上拉输入
 	GPIO_Init(infrared_PORT2, &GPIO_InitStructure);

	 	RCC_APB2PeriphClockCmd(infrared_CLK3,ENABLE);//使能PORTA,PORTE时钟
	GPIO_InitStructure.GPIO_Pin  = infrared_PIN3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置成上拉输入
 	GPIO_Init(infrared_PORT3, &GPIO_InitStructure);

	 RCC_APB2PeriphClockCmd(infrared_CLK4,ENABLE);//使能PORTA,PORTE时钟
	GPIO_InitStructure.GPIO_Pin  = infrared_PIN4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置成上拉输入
 	GPIO_Init(infrared_PORT4, &GPIO_InitStructure);
}
void ChangeCoordinate()
{
	static uint8_t flag=0;
	if(flag==0&&infrared1==BLACK&&infrared2==BLACK&&infrared3==BLACK&&infrared4==BLACK)
	{
		Beep_On_Off(False);
		flag=1;
	}
	if(flag==1&&((infrared1==WHITE&&infrared2==WHITE)||(infrared3==WHITE&&infrared4==WHITE)))
	{
		Beep_On_Off(True);
		switch(orientation)
		{
			case positive_x:if(required_vel>0) position_x+=1;else position_x-=1;break;
			case positive_y:if(required_vel>0) position_y+=1;else position_y-=1;break;
			case negative_x:if(required_vel>0) position_x-=1;else position_x+=1;break;
			case negative_y:if(required_vel>0) position_y-=1;else position_y+=1;break;
		}
		flag=0;
	}
}

void ROTATE(uint8_t Clockwise)//旋转车  ,1 是顺时针
{
	required_vel=0;
	
	IsRotate=1;	//停止pid调速，先进行旋转
	motor1.target_speed = get_RPM(required_vel);
	motor2.target_speed = get_RPM(required_vel);
	switch(Clockwise)
	{
		case 0:
			motor1.target_speed=-get_RPM(0.2);
			motor2.target_speed=get_RPM(0.2);
		if(orientation!=0)
			orientation--;
		else
			orientation=3;
			break;
		case 1:
			motor1.target_speed=get_RPM(0.2);
			motor2.target_speed=-get_RPM(0.2);
		if(orientation!=3)
			orientation++;
		else
			orientation=0;
			break;
	}
	delay(610);
	IsRotate=0;
	
}
