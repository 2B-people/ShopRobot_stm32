#include "bottom_sensor.h"
#define NOLINETIME 600
uint8_t LsRotate=0;
double dis;
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
	
		 RCC_APB2PeriphClockCmd(infrared_CLK5,ENABLE);//使能PORTA,PORTE时钟
	GPIO_InitStructure.GPIO_Pin  = infrared_PIN5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置成上拉输入
 	GPIO_Init(infrared_PORT5, &GPIO_InitStructure);
}
void ChangeCoordinate()
{
	static uint8_t flag=0;
	
	if(!IsRotate&&!IsFetch)
	{
		dis+=(required_vel/20);			//确定行走距离
	}
	if(required_vel<=slow_vel)
	{
		if(dis>=460)								//如果走了一段较长距离还未检测到白线，则认为已经记到白线，减小计数模块出错带来的负面影响
		{
			switch(orientation)
					{
						case positive_x:if(required_vel>0) position_x+=1;else if(required_vel<0)position_x-=1;break;
						case positive_y:if(required_vel>0) position_y+=1;else if(required_vel<0)position_y-=1;break;
						case negative_x:if(required_vel>0) position_x-=1;else if(required_vel<0)position_x+=1;break;
						case negative_y:if(required_vel>0) position_y-=1;else if(required_vel<0)position_y+=1;break;
					}		
			dis=0;
			flag=0;
			LED2=!LED2;
		}
		else if(dis>=300)						//必须在经过上一条白线之后走过一段距离才能开始检测下一条白线，避免多次计数
		{
			if(IsRotate)
				flag=0;
			else if(!IsRotate&&!IsFetch)
			{
				if(flag==0&&infrared1==BLACK&&infrared2==BLACK&&infrared3==BLACK&&infrared4==BLACK)
				{
					if(infrared1==BLACK&&infrared2==BLACK&&infrared3==BLACK&&infrared4==BLACK)
					{
						if(infrared1==BLACK&&infrared2==BLACK&&infrared3==BLACK&&infrared4==BLACK)
						{
							Beep_On_Off(False);
							flag=1;
						}
					}
				}
				if(flag==1&&((infrared1==WHITE&&infrared3==WHITE)||(infrared2==WHITE&&infrared4==WHITE)))
				{
					Beep_On_Off(True);
					switch(orientation)
					{
						case positive_x:if(required_vel>0) position_x+=1;else if(required_vel<0)position_x-=1;break;
						case positive_y:if(required_vel>0) position_y+=1;else if(required_vel<0)position_y-=1;break;
						case negative_x:if(required_vel>0) position_x-=1;else if(required_vel<0)position_x+=1;break;
						case negative_y:if(required_vel>0) position_y-=1;else if(required_vel<0)position_y+=1;break;
					}		
					dis=0;
					flag=0;
					LED2=!LED2;
				}
			}
		}
		
	}



	else if(required_vel==fast_vel)				//高速状态下不用考虑每一次走的是否到达确切位置，因此直接使用计算的距离当作真实距离
	{
		if(dis >= 400)
		{
			dis=0;
			switch(orientation)
				{
					case positive_x:if(required_vel>0) position_x+=1;else if(required_vel<0)position_x-=1;break;
					case positive_y:if(required_vel>0) position_y+=1;else if(required_vel<0)position_y-=1;break;
					case negative_x:if(required_vel>0) position_x-=1;else if(required_vel<0)position_x+=1;break;
					case negative_y:if(required_vel>0) position_y-=1;else if(required_vel<0)position_y+=1;break;
				}
		}
	}
	
	
//	else
//	{
//		TIM6_counter++;
//		if(TIM6_counter>=597)
//		{
//			TIM6_counter=0;
//			switch(orientation)
//			{
//				case positive_x:if(required_vel>0) position_x+=1;else if(required_vel<0)position_x-=1;break;
//				case positive_y:if(required_vel>0) position_y+=1;else if(required_vel<0)position_y-=1;break;
//				case negative_x:if(required_vel>0) position_x-=1;else if(required_vel<0)position_x+=1;break;
//				case negative_y:if(required_vel>0) position_y-=1;else if(required_vel<0)position_y+=1;break;
//			}
//		}
//	}
	
}


void ROTATE(uint8_t Clockwise)//旋转车  ,1 是顺时针
{
	LED2=0;
	required_vel=0;
	IsRotate=1;	
	switch(Clockwise)
	{
		case 0:
			motor1->target_speed=-get_RPM(0.2);
			motor2->target_speed=get_RPM(0.2);
			delay(625);
		break;
		case 1:
			motor1->target_speed=get_RPM(0.2);
			motor2->target_speed=-get_RPM(0.2);
			delay(525);
		break;
	}
	switch(Clockwise)					//旋转完之后，改变车的朝向
	{
		case 0:
		if(orientation!=0)
			orientation--;
		else
			orientation=3;
		break;
		case 1:
		if(orientation!=3)
			orientation++;
		else
			orientation=0;	
		break;
	}
	required_vel=0;						
	delay(100);
	IsRotate=0;								//旋转标志置0
	LED2=1;
	LsRotate=1;								//直到旋转后走完第一格，该标志才置0
	dis=0;
}
void toFetch(uint8_t IsGet,uint8_t Floor)			//抓取程序
{
	uint8_t IsInline=1;
	IsHD=1;
	IsFetch=1;
	target_position_x=position_x;
	target_position_y=position_y;
	if(position_x==0&&position_y>=4)
	{
		while(orientation!=negative_x)
		{
			switch(orientation)
				{
					case positive_y:ROTATE(0);break;
					default:ROTATE(1);
				}
		}
	}
	else if(position_x==9&&position_y<=5)
	{
		while(orientation!=positive_x)
		{
			switch(orientation)
				{
					case negative_y:ROTATE(0);break;
					default:ROTATE(1);
				}
		}
	}	
	else if(position_y==9&&position_x>=4)
	{
		while(orientation!=positive_y)
		{
			switch(orientation)
				{
					case positive_x:ROTATE(0);break;
					default:ROTATE(1);
				}
		}
	}	
	else if(position_y==0&&position_x<=5)
	{
		while(orientation!=negative_y)
		{
			switch(orientation)
				{
					case negative_x:ROTATE(0);break;
					default:ROTATE(1);
				}
		}
	}
	else
	{
		if(position_x==2&&position_y==4)
		{
			while(orientation!=positive_y)
			{
				switch(orientation)
				{
					case negative_x:ROTATE(0);break;
					default:ROTATE(1);
				}
			}
			required_vel=slow_vel;
			delay(NOLINETIME);
			required_vel=0;
			ROTATE(1);
			IsInline=0;
		}
		else if(position_x==2&&position_y==5)
		{
			while(orientation!=positive_x)
			{
				switch(orientation)
				{
					case negative_y:ROTATE(0);break;
					default:ROTATE(1);
				}
			}
		}
		else if(position_x==2&&position_y==6)
		{
			while(orientation!=negative_y)
			{
				switch(orientation)
				{
					case negative_x:ROTATE(0);break;
					default:ROTATE(1);
				}
			}
			required_vel=slow_vel;
			delay(NOLINETIME);
			required_vel=0;
			ROTATE(0);
			IsInline=0;
		}
		else if(position_x==7&&position_y==3)
		{
			while(orientation!=positive_y)
			{
				switch(orientation)
				{
					case positive_x:ROTATE(0);break;
					default:ROTATE(1);
				}
			}
			required_vel=slow_vel;
			delay(NOLINETIME);
			required_vel=0;
			ROTATE(0);
			IsInline=0;
		}
		else if(position_x==7&&position_y==4)
		{
			while(orientation!=negative_x)
			{
				switch(orientation)
				{
					case positive_y:ROTATE(0);break;
					default:ROTATE(1);
				}
			}
		}
		else if(position_x==7&&position_y==5)
		{
			while(orientation!=negative_y)
			{
				switch(orientation)
				{
					case negative_x:ROTATE(0);break;
					default:ROTATE(1);
				}
			}
			required_vel=slow_vel;
			delay(NOLINETIME);
			required_vel=0;
			ROTATE(1);
			IsInline=0;
		}
		else if(position_y==2&&position_x==3)
		{
			while(orientation!=positive_x)
			{
				switch(orientation)
				{
					case negative_y:ROTATE(0);break;
					default:ROTATE(1);
				}
			}
			required_vel=slow_vel;
			delay(NOLINETIME);
			required_vel=0;
			ROTATE(0);
			IsInline=0;
		}
		else if(position_y==2&&position_x==4)
		{
			while(orientation!=positive_y)
			{
				switch(orientation)
				{
					case positive_x:ROTATE(0);break;
					default:ROTATE(1);
				}
			}
		}
		else if(position_y==2&&position_x==5)
		{
			while(orientation!=negative_x)
			{
				switch(orientation)
				{
					case positive_y:ROTATE(0);break;
					default:ROTATE(1);
				}
			}
			required_vel=slow_vel;
			delay(NOLINETIME);
			required_vel=0;
			ROTATE(1);
			IsInline=0;
		}
		else if(position_y==7&&position_x==4)
		{
			while(orientation!=positive_x)
			{
				switch(orientation)
				{
					case negative_y:ROTATE(0);break;
					default:ROTATE(1);
				}
			}
			required_vel=slow_vel;
			delay(NOLINETIME);
			required_vel=0;
			ROTATE(1);
			IsInline=0;
		}
		else if(position_y==7&&position_x==5)
		{
			while(orientation!=negative_y)
			{
				switch(orientation)
				{
					case negative_x:ROTATE(0);break;
					default:ROTATE(1);
				}
			}
		}
		else if(position_y==7&&position_x==6)
		{
			while(orientation!=negative_x)
			{
				switch(orientation)
				{
					case positive_y:ROTATE(0);break;
					default:ROTATE(1);
				}
			}
			required_vel=slow_vel;
			delay(NOLINETIME);
			required_vel=0;
			ROTATE(0);
			IsInline=0;
		}
	}
	
	
	if(!IsInline)
	{
		IsHD=0;
	}
	
	required_vel=0;
	
	switch(Floor)
	{
		case 0:Goods_floor(0);break;
		case 1:Goods_floor(1);break;
	}
	delay(1000);
	required_vel=slow_vel;
	
	delay(1700);
	OLED_SHOW_MANU();
	required_vel=0;
	OLED_SHOW_MANU();
	delay(1000);
	OLED_SHOW_MANU();
	
	
	switch(IsGet)
	{
		case 100:	Give_goods();break;
		default:Get_goods(IsGet);break;
	}
	
	
	
	
	required_vel=-slow_vel;
	OLED_SHOW_MANU();
	delay(300);
	OLED_SHOW_MANU();
	while(infrared2==BLACK||infrared4==BLACK)
	{
		OLED_SHOW_MANU();
	}
	required_vel=0;
	
	IsHD=1;
	IsFetch=0;
	
	if(!IsInline)			//回到整点位置
	{
		if(position_x==2&&position_y==4)
		{
			ROTATE(1);
			required_vel=slow_vel;
			while(infrared2==BLACK||infrared4==BLACK)
			{
				OLED_SHOW_MANU();
			}
			required_vel=0;
			position_x=2;
			position_y=4;			
		}
		else if(position_x==2&&position_y==6)
		{
			ROTATE(0);
			position_x=2;
			position_y=6;		
		}
		else if(position_x==7&&position_y==3)
		{
			ROTATE(0);
			required_vel=slow_vel;
			while(infrared2==BLACK||infrared4==BLACK)
			{
				OLED_SHOW_MANU();
			}
			required_vel=0;
			position_x=7;
			position_y=3;	
		}
		else if(position_x==7&&position_y==5)
		{
			ROTATE(1);
			required_vel=slow_vel;
			while(infrared2==BLACK||infrared4==BLACK)
			{
				OLED_SHOW_MANU();
			}
			required_vel=0;
			position_x=7;
			position_y=5;	
		}
		else if(position_y==2&&position_x==3)
		{
			ROTATE(0);
			required_vel=slow_vel;
			while(infrared2==BLACK||infrared4==BLACK)
			{
				OLED_SHOW_MANU();
			}
			required_vel=0;
			position_x=3;
			position_y=2;	
		}
		else if(position_y==2&&position_x==5)
		{
			ROTATE(1);
			required_vel=slow_vel;
			while(infrared2==BLACK||infrared4==BLACK)
			{
				OLED_SHOW_MANU();
			}
			required_vel=0;
			position_x=5;
			position_y=2;	
		}
		else if(position_y==7&&position_x==4)
		{
			ROTATE(1);
			required_vel=slow_vel;
			while(infrared2==BLACK||infrared4==BLACK)
			{
				OLED_SHOW_MANU();
			}
			required_vel=0;
			position_x=4;
			position_y=7;	
		}
		else if(position_y==7&&position_x==6)
		{
			ROTATE(0);
			required_vel=slow_vel;
			while(infrared2==BLACK||infrared4==BLACK)
			{
				OLED_SHOW_MANU();
			}
			required_vel=0;
			position_x=6;
			position_y=7;	
		}
	}
	dis=0;
	
	
}

