#include "plan.h"
uint8_t IsMoveFinsh;
void MOVE(uint8_t _target_position_x,uint8_t _target_position_y)//移动车到指定坐标
{
	if(_target_position_x>position_x)
	{
		if(position_y>=3&&position_y<=6&&((_target_position_x<=3&&position_x>=6)||(_target_position_x>=6&&position_x<=3)));
		else
		{
			switch(orientation)
			{
				case positive_x:
					if(_target_position_x-position_x>1)
						required_vel=2.0;
					else
					{
						required_vel-=0.005;
						if(required_vel<=0.5)
							required_vel=0.5;
					}
					break;
				case negative_x:
					ROTATE(1);
					ROTATE(1);
					if(_target_position_x-position_x>1)
						required_vel=2.0;
					else
					{
						required_vel-=0.005;
						if(required_vel<=0.5)
							required_vel=0.5;
					}
					break;
				case positive_y:
					ROTATE(1);
					if(_target_position_x-position_x>1)
						required_vel=2.0;
					else
					{
						required_vel-=0.005;
						if(required_vel<=0.5)
							required_vel=0.5;
					}
					break;
				case negative_y:
					ROTATE(0);
					if(_target_position_x-position_x>1)
						required_vel=2.0;
					else
					{
						required_vel-=0.005;
						if(required_vel<=0.5)
							required_vel=0.5;
					}
					break;
			}
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
					required_vel=2.0;
				else
				{
					required_vel-=0.005;
					if(required_vel<=0.5)
						required_vel=0.5;
				}
				break;
			case negative_x:
				if(position_x-_target_position_x>1)
					required_vel=2.0;
				else
				{
					required_vel-=0.005;
					if(required_vel<=0.5)
						required_vel=0.5;
				}
				break;
			case positive_y:
				ROTATE(0);
				if(position_x-_target_position_x>1)
					required_vel=2.0;
				else
				{
					required_vel-=0.005;
					if(required_vel<=0.5)
						required_vel=0.5;
				}
				break;
			case negative_y:
				ROTATE(1);
				if(position_x-_target_position_x>1)
					required_vel=2.0;
				else
				{
					required_vel-=0.005;
					if(required_vel<=0.5)
						required_vel=0.5;
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
					required_vel=2.0;
				else
				{
					required_vel-=0.005;
					if(required_vel<=0.5)
						required_vel=0.5;
				}
				break;
			case negative_x:
				ROTATE(1);
				if(_target_position_y-position_y>1)
					required_vel=2.0;
				else
				{
					required_vel-=0.005;
					if(required_vel<=0.5)
						required_vel=0.5;
				}
				break;
			case positive_y:
				if(_target_position_y-position_y>1)
					required_vel=2.0;
				else
				{
					required_vel-=0.005;
					if(required_vel<=0.5)
						required_vel=0.5;
				}
				break;
			case negative_y:
				ROTATE(1);
				ROTATE(1);
				if(_target_position_y-position_y>1)
					required_vel=2.0;
				else
				{
					required_vel-=0.005;
					if(required_vel<=0.5)
						required_vel=0.5;
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
					required_vel=2.0;
				else
				{
					required_vel-=0.005;
					if(required_vel<=0.5)
						required_vel=0.5;
				}
				break;
			case negative_x:
				ROTATE(0);
				if(position_y-_target_position_y>1)
					required_vel=2.0;
				else
				{
					required_vel-=0.005;
					if(required_vel<=0.5)
						required_vel=0.5;
				}
				break;
			case positive_y:
				ROTATE(0);
				ROTATE(0);
				if(position_y-_target_position_y>1)
					required_vel=2.0;
				else
				{
					required_vel-=0.005;
					if(required_vel<=0.5)
						required_vel=0.5;
				}
				break;
			case negative_y:
				if(position_y-_target_position_y>1)
					required_vel=2.0;
				else
				{
					required_vel-=0.005;
					if(required_vel<=0.5)
						required_vel=0.5;
				}
				break;
		}
	}
}


void ROTATE(uint8_t Clockwise)//旋转车
{
	switch(Clockwise)
	{
		case 0:
			break;
		case 1:
			break;
	}
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
			MOVE(2,target_position_y);
		else
			MOVE(7,target_position_y);
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
		MOVE(target_position_x,target_position_y);
	IsMoveFinsh=0;
	if(position_x==target_position_x&&position_y==target_position_y)
		IsMoveFinsh=1;
}