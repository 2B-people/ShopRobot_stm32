#include "plan.h"
#define fast_vel 2.0		//一般情况下车速
#define slow_vel 0.5		//车子还在运行状态的最低车速
#define down_vel 0.005	//达到最后一格时，每个周期减下的速度
#define rotate_vel 0.5 //旋转速度
//一开始以线性关系减速，在最后一刻急停。
uint8_t IsMoveFinsh;
uint8_t IsRotate;



/*

the position division


-----------------
|                |
|  3  4     5    | 
|                |
|    ----        |
|  2|    |  6    |
|   |----|       |
|                |
|  1  8     7    |
|----------------

*/
void MOVE(uint8_t _target_position_x,uint8_t _target_position_y)//移动车到指定坐标
{
	if(_target_position_x>position_x)
	{
			switch(orientation)
			{
				case positive_x:
					if(_target_position_x-position_x>1)
						required_vel=fast_vel;
					else
					{
						required_vel-=down_vel;
						if(required_vel<=slow_vel)
							required_vel=slow_vel;
					}
					break;
				case negative_x:
					ROTATE(1);
					ROTATE(1);
					if(_target_position_x-position_x>1)
						required_vel=fast_vel;
					else
					{
						required_vel-=down_vel;
						if(required_vel<=slow_vel) 
							required_vel=slow_vel;
					}
					break;
				case positive_y:
					ROTATE(1);
					if(_target_position_x-position_x>1)
						required_vel=fast_vel;
					else
					{
						required_vel-=down_vel;
						if(required_vel<=slow_vel)
							required_vel=slow_vel;
					}
					break;
				case negative_y:
					ROTATE(0);
					if(_target_position_x-position_x>1)
						required_vel=fast_vel;
					else
					{
						required_vel-=down_vel;
						if(required_vel<=slow_vel)
							required_vel=slow_vel;
					}
					break;
			}
	}
	else if(_target_position_x<position_x)
	{
		switch(orientation)
		{
			case positive_x:
				ROTATE(0);
				ROTATE(0);
				if(position_x-_target_position_x>1)
					required_vel=fast_vel;
				else
				{
					required_vel-=down_vel;
					if(required_vel<=slow_vel)
						required_vel=slow_vel;
				}
				break;
			case negative_x:
				if(position_x-_target_position_x>1)
					required_vel=fast_vel;
				else
				{
					required_vel-=down_vel;
					if(required_vel<=slow_vel)
						required_vel=slow_vel;
				}
				break;
			case positive_y:
				ROTATE(0);
				if(position_x-_target_position_x>1)
					required_vel=fast_vel;
				else
				{
					required_vel-=down_vel;
					if(required_vel<=slow_vel)
						required_vel=slow_vel;
				}
				break;
			case negative_y:
				ROTATE(1);
				if(position_x-_target_position_x>1)
					required_vel=fast_vel;
				else
				{
					required_vel-=down_vel;
					if(required_vel<=slow_vel)
						required_vel=slow_vel;
				}
				break;
		}
	}
	else if(_target_position_y>position_y)
	{
		switch(orientation)
		{
			case positive_x:
				ROTATE(0);
				if(_target_position_y-position_y>1)
					required_vel=fast_vel;
				else
				{
					required_vel-=down_vel;
					if(required_vel<=slow_vel)
						required_vel=slow_vel;
				}
				break;
			case negative_x:
				ROTATE(1);
				if(_target_position_y-position_y>1)
					required_vel=fast_vel;
				else
				{
					required_vel-=down_vel;
					if(required_vel<=slow_vel)
						required_vel=slow_vel;
				}
				break;
			case positive_y:
				if(_target_position_y-position_y>1)
					required_vel=fast_vel;
				else
				{
					required_vel-=down_vel;
					if(required_vel<=slow_vel)
						required_vel=slow_vel;
				}
				break;
			case negative_y:
				ROTATE(1);
				ROTATE(1);
				if(_target_position_y-position_y>1)
					required_vel=fast_vel;
				else
				{
					required_vel-=down_vel;
					if(required_vel<=slow_vel)
						required_vel=slow_vel;
				}
				break;
		}
	}
	else if(_target_position_y<position_y)
	{
		switch(orientation)
		{
			case positive_x:
				ROTATE(1);
				if(position_y-_target_position_y>1)
					required_vel=fast_vel;
				else
				{
					required_vel-=down_vel;
					if(required_vel<=slow_vel)
						required_vel=slow_vel;
				}
				break;
			case negative_x:
				ROTATE(0);
				if(position_y-_target_position_y>1)
					required_vel=fast_vel;
				else
				{
					required_vel-=down_vel;
					if(required_vel<=slow_vel)
						required_vel=slow_vel;
				}
				break;
			case positive_y:
				ROTATE(0);
				ROTATE(0);
				if(position_y-_target_position_y>1)
					required_vel=fast_vel;
				else
				{
					required_vel-=down_vel;
					if(required_vel<=slow_vel)
						required_vel=slow_vel;
				}
				break;
			case negative_y:
				if(position_y-_target_position_y>1)
					required_vel=fast_vel;
				else
				{
					required_vel-=down_vel;
					if(required_vel<=slow_vel)
						required_vel=slow_vel;
				}
				break;
		}
	}
	else if(position_x==target_position_x&&position_y==target_position_y)
	{
		required_vel=0;
	}
}


void ROTATE(uint8_t Clockwise)//旋转车  ,1 是顺时针
{
	required_vel=0;
	IsRotate=1;	//停止pid调速，先进行旋转
	switch(Clockwise)
	{
		case 0:
			motor1.target_speed=-(rotate_vel*60/(PI*WHEEL_DIAMETER));
			motor2.target_speed=rotate_vel*60/(PI*WHEEL_DIAMETER);
			delay(30);
			while(infrared1==0&&infrared2==0);
			break;
		case 1:
			motor1.target_speed=rotate_vel*60/(PI*WHEEL_DIAMETER);
			motor2.target_speed=-(rotate_vel*60/(PI*WHEEL_DIAMETER));
			delay(30);
			while(infrared1==0&&infrared2==0);
			break;
	}
	IsRotate=0;
}

void move_control(void)//路径规划
{
	if(position_x<=3&&position_y<=3&&target_position_x>=3&&target_position_y>=6)
	{
		MOVE(position_x,target_position_y);
		position=1;
	}
	else if(position_x<=3&&position_y<=6&&(position_y>=6||position_y<=3))
	{
		MOVE(position_x,target_position_y);
		position=2;
	}
	else if(position_x<=3&&position_y<=6&&position_y>=3&&target_position_x>=6&&target_position_y>=3&&target_position_y<=6)
	{
		if(position_y==3||position_y==4)
			MOVE(position_x,2);
		else
			MOVE(position_x,7);
		position=2;
	}
	if(position_x<=3&&position_y>=6&&target_position_x>=3&&target_position_y<=3)
	{
		MOVE(position_x,target_position_y);
		position=3;
	}
	else if(position_x<=6&&position_x>=3&&position_y>=6&&target_position_x>=3&&target_position_x<=6&&target_position_y<=3)
	{
		if(position_x==3||position_x==4)
			MOVE(2,position_y);
		else
			MOVE(7,position_y);
		position=4;
	}
	else if(position_x>=6&&position_y>=6&&target_position_x>=3&&target_position_x<=6&&target_position_y<=3)
	{
		MOVE(position_x,target_position_y);
		position=5;
	}
	else if(position_x>=6&&position_y<=3&&target_position_x>=3&&target_position_x<=6&&target_position_y>=6)
	{
		MOVE(position_x,target_position_y);
		position=7;
	}
	else if(position_x>=6&&position_y>=3&&position_y<=6&&target_position_x<=3&&target_position_y>=3&&target_position_y<=6)
	{
		if(position_y==3||position_y==4)
			MOVE(position_x,2);
		else
			MOVE(position_x,7);
		position=6;
	}
	else if(position_x>=6&&position_y>=3&&position_y<=6&&(target_position_y>=6||target_position_y<=3))
	{
		MOVE(position_x,target_position_y);
		position=6;
	}
	else if(position_x>=3&&position_x<=6&&position_y<=3&&target_position_y>=6&&target_position_x<=6&&target_position_x>=3)
	{
		if(position_x==3||position_y==4)
			MOVE(2,position_y);
		else
			MOVE(7,position_y);
		position=8;
	}
	else
	{
		MOVE(target_position_x,position_y);
		MOVE(position_x,target_position_y);
	}
	IsMoveFinsh=0;
	if(position_x==target_position_x&&position_y==target_position_y)
	{
		required_vel=0;
		IsMoveFinsh=1;
	}
}
