#include "plan.h"

#define rotate_vel 0.5 //旋转速度
//一开始以线性关系减速，在最后一刻急停。
uint8_t IsMoveFinsh;
uint8_t IsRotate;



/*

the position division

postive_y
-----------------
|                |
|  3  4     5    | 
|                |
|    ----        |
|  2|    |  6    |
|   |----|       |
|                |
|  1  8     7    |
|----------------     postive_x

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
					if(_target_position_x-position_x>1)
						required_vel=-fast_vel;
					else
					{
						required_vel+=down_vel;
						if(required_vel>=(-slow_vel)) 
							required_vel=(-slow_vel);
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
				if(position_x-_target_position_x>1)
					required_vel=-fast_vel;
				else
				{
						required_vel+=down_vel;
						if(required_vel>=(-slow_vel)) 
							required_vel=(-slow_vel);
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
				if(_target_position_y-position_y>1)
					required_vel=-fast_vel;
				else
				{
						required_vel+=down_vel;
						if(required_vel>=(-slow_vel)) 
							required_vel=(-slow_vel);
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

				if(position_y-_target_position_y>1)
					required_vel=-fast_vel;
				else
				{
						required_vel+=down_vel;
						if(required_vel>=(-slow_vel)) 
							required_vel=(-slow_vel);
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
			motor1.target_speed=-COUNTS_PER_REV*(rotate_vel*60/(PI*WHEEL_DIAMETER));
			motor2.target_speed=COUNTS_PER_REV*rotate_vel*60/(PI*WHEEL_DIAMETER);
			delay(30);
			while(infrared1==0&&infrared2==0&&infrared3==0&&infrared4==0);
			break;
		case 1:
			motor1.target_speed=COUNTS_PER_REV*rotate_vel*60/(PI*WHEEL_DIAMETER);
			motor2.target_speed=-COUNTS_PER_REV*(rotate_vel*60/(PI*WHEEL_DIAMETER));
			delay(30);
			while(infrared1==0&&infrared2==0&&infrared3==0&&infrared4==0);
			break;
	}
	IsRotate=0;
}

void move_control(void)//路径规划
{
	if(position_x<=3&&position_y<=3)
		position=1;
	else if(position_x<=2&&position_y>=4&&position_y<=6)
		position=2;
	else if(position_x<=3&&position_y>=7)
		position=3;
	else if(position_x>=4&&position_x<=6&&position_y>=7)
		position=4;
	else if(position_x>=7&&position_y>=7)
		position=5;
	else if(position_x>=7&&position_y>=4&&position_y<=6)
		position=6;
	else if(position_x>=7&&position_y<=3)
		position=7;
	else if(position_x>=4&&position_x<=6&&position_y<=2)
		position=8;
	
	
	if(target_position_x<=3&&target_position_y<=3)
		target_position=1;
	else if(target_position_x<=2&&target_position_y>=4&&target_position_y<=6)
		target_position=2;
	else if(target_position_x<=3&&target_position_y>=7)
		target_position=3;
	else if(target_position_x>=4&&target_position_x<=6&&target_position_y>=7)
		target_position=4;
	else if(target_position_x>=7&&target_position_y>=7)
		target_position=5;
	else if(target_position_x>=7&&target_position_y>=4&&target_position_y<=6)
		target_position=6;
	else if(target_position_x>=7&&target_position_y<=3)
		target_position=7;
	else if(target_position_x>=4&&target_position_x<=6&&target_position_y<=2)
		target_position=8;
	
	switch(position)
	{
		case 1:
		{
			if(position_y==3)
			{
				switch(target_position)
				{
					case 6:MOVE(position_x,2);MOVE(target_position_x,target_position_y);break;
					default:MOVE(position_x,target_position_y);MOVE(target_position_x,target_position_y);break;
				}
			}
			else if(position_x==3)
			{
				switch(target_position)
				{
					case 4:MOVE(2,position_y);MOVE(position_x,target_position_y);MOVE(target_position_x,target_position_y);break;
					default:MOVE(target_position_x,target_position_y);break;
				}
			}
			else
			{
				switch(target_position)
				{
					case 1:MOVE(target_position_x,target_position_y);break;
					case 2:MOVE(target_position_x,target_position_y);break;
					case 3:MOVE(target_position_x,target_position_y);break;
					case 4:MOVE(position_x,target_position_y);MOVE(target_position_x,target_position_y);break;
					case 5:MOVE(position_x,target_position_y);MOVE(target_position_x,target_position_y);break;
					case 6:MOVE(target_position_x,target_position_y);break;
					case 7:MOVE(target_position_x,target_position_y);break;
					case 8:MOVE(target_position_x,target_position_y);break;
				}
			}
			break;
		}
		case 2:
		{
			switch(target_position)
			{
				case 1:MOVE(target_position_x,target_position_y);break;
				case 2:MOVE(target_position_x,target_position_y);break;
				case 3:MOVE(target_position_x,target_position_y);break;
				case 4:MOVE(position_x,target_position_y);MOVE(target_position_x,target_position_y);break;
				case 5:MOVE(position_x,target_position_y);MOVE(target_position_x,target_position_y);break;
				case 6:MOVE(position_x,7);MOVE(target_position_x,target_position_y);break;
				case 7:MOVE(position_x,target_position_y);MOVE(target_position_x,target_position_y);break;
				case 8:MOVE(position_x,target_position_y);MOVE(target_position_x,target_position_y);break;
			}
			break;
		}
		case 3:
		{
			if(position_x==3)
			{
				switch(target_position)
				{
					case 8:MOVE(2,position_y);MOVE(position_x,target_position_y);MOVE(target_position_x,target_position_y);break;
					default:MOVE(target_position_x,target_position_y);break;
				}
			}
			switch(target_position)
			{
				case 1:MOVE(target_position_x,target_position_y);break;
				case 2:MOVE(target_position_x,target_position_y);break;
				case 3:MOVE(target_position_x,target_position_y);break;
				case 4:MOVE(target_position_x,target_position_y);break;
				case 5:MOVE(target_position_x,target_position_y);break;
				case 6:MOVE(target_position_x,target_position_y);break;
				case 7:MOVE(target_position_x,target_position_y);break;
				case 8:MOVE(position_x,target_position_y);MOVE(target_position_x,target_position_y);break;
			}
			break;
		}
		case 4:
		{
			switch(target_position)
			{
				case 1:MOVE(target_position_x,target_position_y);break;
				case 2:MOVE(target_position_x,target_position_y);break;
				case 3:MOVE(target_position_x,target_position_y);break;
				case 4:MOVE(target_position_x,target_position_y);break;
				case 5:MOVE(target_position_x,target_position_y);break;
				case 6:MOVE(target_position_x,target_position_y);break;
				case 7:MOVE(target_position_x,target_position_y);break;
				case 8:MOVE(7,position_y);MOVE(position_x,target_position_y);MOVE(target_position_x,target_position_y);break;
			}
			break;
		}
		case 5:
		{
			switch(target_position)
			{
				case 1:MOVE(target_position_x,target_position_y);break;
				case 2:MOVE(target_position_x,target_position_y);break;
				case 3:MOVE(target_position_x,target_position_y);break;
				case 4:MOVE(target_position_x,target_position_y);break;
				case 5:MOVE(target_position_x,target_position_y);break;
				case 6:MOVE(target_position_x,target_position_y);break;
				case 7:MOVE(target_position_x,target_position_y);break;
				case 8:MOVE(position_x,target_position_y);MOVE(target_position_x,target_position_y);break;
			}
			break;
		}
		case 6:
		{
			if(position_y==3)
			{
				switch(target_position)				
				{
					case 2:MOVE(position_x,2);MOVE(target_position_x,target_position_y);break;
					default:MOVE(position_x,target_position_y);MOVE(target_position_x,target_position_y);break;
				}
			}
			switch(target_position)
			{
				case 1:MOVE(position_x,target_position_y);MOVE(target_position_x,target_position_y);break;
				case 2:MOVE(position_x,7);MOVE(target_position_x,target_position_y);break;
				case 3:MOVE(position_x,target_position_y);MOVE(target_position_x,target_position_y);break;
				case 4:MOVE(position_x,target_position_y);MOVE(target_position_x,target_position_y);break;
				case 5:MOVE(target_position_x,target_position_y);break;
				case 6:MOVE(target_position_x,target_position_y);break;
				case 7:MOVE(target_position_x,target_position_y);break;
				case 8:MOVE(position_x,target_position_y);MOVE(target_position_x,target_position_y);break;
			}
			break;
		}
		case 7:
		{
			switch(target_position)
			{
				case 1:MOVE(target_position_x,target_position_y);break;
				case 2:MOVE(target_position_x,target_position_y);break;
				case 3:MOVE(target_position_x,target_position_y);break;
				case 4:MOVE(position_x,target_position_y);MOVE(target_position_x,target_position_y);break;
				case 5:MOVE(target_position_x,target_position_y);break;
				case 6:MOVE(target_position_x,target_position_y);break;
				case 7:MOVE(target_position_x,target_position_y);break;
				case 8:MOVE(target_position_x,target_position_y);break;
			}
			break;
		}
		case 8:
		{
			switch(target_position)
			{
				case 1:MOVE(target_position_x,target_position_y);break;
				case 2:MOVE(target_position_x,target_position_y);break;
				case 3:MOVE(target_position_x,target_position_y);break;
				case 4:MOVE(target_position_x,target_position_y);break;
				case 5:MOVE(target_position_x,target_position_y);break;
				case 6:MOVE(target_position_x,target_position_y);break;
				case 7:MOVE(target_position_x,target_position_y);break;
				case 8:MOVE(7,position_y);MOVE(position_x,target_position_y);MOVE(target_position_x,target_position_y);break;
			}
			break;
		}
	}
	


	IsMoveFinsh=0;
	if(position_x==target_position_x&&position_y==target_position_y)
	{
		required_vel=0;
		IsMoveFinsh=1;
	}
}
