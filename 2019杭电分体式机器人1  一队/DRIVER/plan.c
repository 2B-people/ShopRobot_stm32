#include "plan.h"
		//地图计算完成标志
//一开始以线性关系减速，在最后一刻急停。
uint8_t IsMoveFinsh=1;
uint8_t IsRotate=0;
uint8_t patrolStatus=1;
uint8_t IsPathCalFinish=0;
char graph[11][11];
int8_t prex[11][11];
int8_t prey[11][11];
int8_t n=10, m=10;
int8_t sx, sy, tx, ty;
queue qx;
queue qy;
queue lujinx;
queue lujiny;
int8_t next_x[11];
int8_t next_y[11];

uint8_t nextx;
uint8_t nexty;

int8_t dirx[] = { 0,0,1,-1 };
int8_t diry[] = { 1,-1,0,0 };
int8_t vis[11][11];


enum
{
	go_forward,
	go_back,
	go_left,
	go_right
};


void MOVE(uint8_t _target_position_x,uint8_t _target_position_y)//移动车到指定坐标
{
	if(_target_position_x>position_x)
	{
			switch(orientation)
			{
				case positive_x:
					if(_target_position_x-position_x>1)
					{
						if(required_vel<fast_vel)
							required_vel+=down_vel;
						else
							required_vel=fast_vel;
					}
					else if(_target_position_x-position_x==1)
					{
						if(required_vel>slow_vel)
							required_vel-=down_vel;
						else
							required_vel=slow_vel;
					}
					break;
				case negative_x:
					ROTATE(1);
					ROTATE(1);
					if(_target_position_x-position_x>1)
					{
						if(required_vel<fast_vel)
							required_vel+=down_vel;
						else
							required_vel=fast_vel;
					}
					else if(_target_position_x-position_x==1)
					{
						if(required_vel>slow_vel)
							required_vel-=down_vel;
						else
							required_vel=slow_vel;
					}
					break;
				case positive_y:
					ROTATE(1);
					if(_target_position_x-position_x>1)
					{
						if(required_vel<fast_vel)
							required_vel+=down_vel;
						else
							required_vel=fast_vel;
					}
					else if(_target_position_x-position_x==1)
					{
						if(required_vel>slow_vel)
							required_vel-=down_vel;
						else
							required_vel=slow_vel;
					}
					break;
				case negative_y:
					ROTATE(0);
					if(_target_position_x-position_x>1)
					{
						if(required_vel<fast_vel)
							required_vel+=down_vel;
						else
							required_vel=fast_vel;
					}
					else if(_target_position_x-position_x==1)
					{
						if(required_vel>slow_vel)
							required_vel-=down_vel;
						else
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
				ROTATE(1);
				ROTATE(1);
				if(position_x-_target_position_x>1)
				{
					if(required_vel<fast_vel)
						required_vel+=down_vel;
					else
						required_vel=fast_vel;
				}
				else if(_target_position_x-position_x==-1)
				{
						if(required_vel>slow_vel)
							required_vel-=down_vel;
						else
							required_vel=slow_vel;
				}
				break;
			case negative_x:
				if(position_x-_target_position_x>1)
				{
					if(required_vel<fast_vel)
						required_vel+=down_vel;
					else
						required_vel=fast_vel;
				}
				else if(_target_position_x-position_x==-1)
				{
					if(required_vel>slow_vel)
							required_vel-=down_vel;
						else
							required_vel=slow_vel;
				}
				break;
			case positive_y:
				ROTATE(0);
				if(position_x-_target_position_x>1)
				{
					if(required_vel<fast_vel)
						required_vel+=down_vel;
					else
						required_vel=fast_vel;
				}
				else if(_target_position_x-position_x==-1)
				{
					if(required_vel>slow_vel)
							required_vel-=down_vel;
						else
							required_vel=slow_vel;
				}
				break;
			case negative_y:
				ROTATE(1);
				if(position_x-_target_position_x>1)
				{
					if(required_vel<fast_vel)
						required_vel+=down_vel;
					else
						required_vel=fast_vel;
				}
				else if(_target_position_x-position_x==-1)
				{
					if(required_vel>slow_vel)
							required_vel-=down_vel;
						else
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
				{
					if(required_vel<fast_vel)
						required_vel+=down_vel;
					else
						required_vel=fast_vel;
				}
				else if(_target_position_y-position_y==1)
				{
					if(required_vel>slow_vel)
							required_vel-=down_vel;
						else
							required_vel=slow_vel;
				}
				break;
			case negative_x:
				ROTATE(1);
				if(_target_position_y-position_y>1)
				{
					if(required_vel<fast_vel)
						required_vel+=down_vel;
					else
						required_vel=fast_vel;
				}
				else if(_target_position_y-position_y==1)
				{
						if(required_vel>slow_vel)
							required_vel-=down_vel;
						else
							required_vel=slow_vel;
				}
				break;
			case positive_y:
				if(_target_position_y-position_y>1)
				{
					if(required_vel<fast_vel)
						required_vel+=down_vel;
					else
						required_vel=fast_vel;
				}
				else if(_target_position_y-position_y==1)
				{
						if(required_vel>slow_vel)
							required_vel-=down_vel;
						else
							required_vel=slow_vel;
				}
				break;
			case negative_y:
				ROTATE(1);
				ROTATE(1);
				if(_target_position_y-position_y>1)
				{
					if(required_vel<fast_vel)
						required_vel+=down_vel;
					else
						required_vel=fast_vel;
				}
				else if(_target_position_y-position_y==1)
				{
							if(required_vel>slow_vel)
							required_vel-=down_vel;
						else
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
				{
					if(required_vel<fast_vel)
						required_vel+=down_vel;
					else
						required_vel=fast_vel;
				}
				else if(_target_position_y-position_y==-1)
				{
						if(required_vel>slow_vel)
							required_vel-=down_vel;
						else
							required_vel=slow_vel;
				}
				break;
			case negative_x:
				ROTATE(0);
				if(position_y-_target_position_y>1)
				{
					if(required_vel<fast_vel)
						required_vel+=down_vel;
					else
						required_vel=fast_vel;
				}
				else if(_target_position_y-position_y==-1)
				{
						if(required_vel>slow_vel)
							required_vel-=down_vel;
						else
							required_vel=slow_vel;
				}
				break;
			case positive_y:
				ROTATE(1);
				ROTATE(1);
				if(position_y-_target_position_y>1)
				{
					if(required_vel<fast_vel)
						required_vel+=down_vel;
					else
						required_vel=fast_vel;
				}
				else if(_target_position_y-position_y==-1)
				{
						if(required_vel>slow_vel)
							required_vel-=down_vel;
						else
							required_vel=slow_vel;
				}
				break;
			case negative_y:
				if(position_y-_target_position_y>1)
				{
					if(required_vel<fast_vel)
						required_vel+=down_vel;
					else
						required_vel=fast_vel;
				}
				else if(_target_position_y-position_y==-1)
				{
						if(required_vel>slow_vel)
							required_vel-=down_vel;
						else
							required_vel=slow_vel;
				}
				break;
		}
	}
	else
		required_vel=0;
	if(position_x==target_position_x&&position_y==target_position_y)
	{
		required_vel=0;
	}
}


/************************************************************************路径规划***************************************************************************/

int8_t check(int x, int y)
{
	return (x >= 0 && x < n&&y >= 0 && y < m && !vis[x][y] && (graph[x][y] == '*' || graph[x][y] == 'T'));//注意不要把'T'这个目的地给滤掉
}

void bfs()
{
	int8_t i=0;
	enQueue(&qx, sx);
	enQueue(&qy, sy);
	while (qx.front != qx.endline&&qy.front != qy.endline)
	{
		int x = qx.data[qx.front];
		int y = qy.data[qy.front];
		deQueue(&qx);
		deQueue(&qy);
		for (i = 0; i < 4; i++)
		{
			int nx = x + dirx[i];
			int ny = y + diry[i];
			if (check(nx, ny))
			{
				vis[nx][ny] = 1;
				prex[nx][ny] = x;
				prey[nx][ny] = y;
				if (graph[nx][ny] == 'T')
				{
					return;
				}
				else
				{
					enQueue(&qx, nx);
					enQueue(&qy, ny);
				}
			}
		}
	}
}
void show(int8_t x, int8_t y)
{
	if (x == -1)
	{
		return;
	}
	show(prex[x][y], prey[x][y]);
	enQueue(&lujinx, x);
	enQueue(&lujiny, y);	
}


void path_Init(void)
{
	memset(vis, 0, sizeof(vis));
	memset(prex, -1, sizeof(prex));
	memset(prey, -1, sizeof(prey));
	memset(next_x, -1, sizeof(next_x));
	memset(next_y, -1, sizeof(next_y));
	nextx=position_x;
	nexty=position_y;
	initQueue(&qx);
	initQueue(&qy);
	initQueue(&lujinx);
	initQueue(&lujiny);
	strcpy(graph[0], "**********");						//      ‘*’代表通路，‘#’表示障碍物，‘S’表示开始位置，‘T’表示终点位置。
	strcpy(graph[1], "**********");
	strcpy(graph[2], "**********");
	strcpy(graph[3], "***####***");
	strcpy(graph[4], "***####***");
	strcpy(graph[5], "***####***");
	strcpy(graph[6], "***####***");
	strcpy(graph[7], "**********");
	strcpy(graph[8], "**********");
	strcpy(graph[9], "**********");
	switch(Obstacle)
	{
		case 1:graph[8][1]='#';break;
		case 2:graph[8][4]='#';break;
		case 3:graph[8][8]='#';break;
		case 4:graph[5][8]='#';break;
		case 5:graph[1][8]='#';break;
		case 6:graph[1][5]='#';break;
	}
	
	
	
}


void path_cal(void)
{
	int state=-1;
	int lstate = -1;
	int i=0;
	int loop=0;
	IsPathCalFinish=0;
	nextx=position_x;
	nexty=position_y;
	path_Init();
	graph[position_x][position_y] = 'S';
	graph[target_position_x][target_position_y] = 'T';
	sx=position_x;sy=position_y;tx=target_position_x;ty=target_position_y;
	if(position_x!=target_position_x||position_y!=target_position_y)
	{
		bfs();
		show(prex[tx][ty], prey[tx][ty]);
		enQueue(&lujinx, tx);
		enQueue(&lujiny, ty);
		for (i = lujinx.front; i<lujinx.endline; i++)
		{
			lstate = state;
			switch (lujinx.data[i+1]- lujinx.data[i])
			{
			case 0:	
				switch (lujiny.data[i + 1] - lujiny.data[i])
				{
				case 1:state = go_forward; break;
				case -1:state = go_back; break;
				}
				break;
			case 1:
				state = go_right; break;
			case -1:
				state = go_left; break;
			}
			if(lstate!=state)
			{
				next_x[loop]=lujinx.data[i];
				next_y[loop]=lujiny.data[i];
				loop++;
			}
		}
		next_x[loop]=-1;
		next_y[loop]=-1;	
		graph[position_x][position_y]='*';
		graph[target_position_x][target_position_y] = '*';
		IsMoveFinsh=0;
	}
	IsPathCalFinish=1;
}


void move_base()
{
	if(next_x[0]!=-1&&next_y[0]!=-1)
	{
		if(position_x==next_x[0]&&position_y==next_y[0])
		{
			next_x[0]=-1;
			next_y[0]=-1;
		}
		if(next_x[0]!=-1&&next_y[0]!=-1)
		{
			nextx=next_x[0];
			nexty=next_y[0];
		}
	}
	else if(next_x[1]!=-1&&next_y[1]!=-1)
	{
		if(position_x==next_x[1]&&position_y==next_y[1])
		{
			next_x[1]=-1;
			next_y[1]=-1;
		}
		if(next_x[1]!=-1&&next_y[1]!=-1)
		{
			nextx=next_x[1];
			nexty=next_y[1];
		}
	}
	else if(next_x[2]!=-1&&next_y[2]!=-1)
	{
		if(position_x==next_x[2]&&position_y==next_y[2])
		{
			next_x[2]=-1;
			next_y[2]=-1;
		}
		if(next_x[2]!=-1&&next_y[2]!=-1)
		{
			nextx=next_x[2];
			nexty=next_y[2];
		}
	}
	else if(next_x[3]!=-1&&next_y[3]!=-1)
	{
		if(position_x==next_x[3]&&position_y==next_y[3])
		{
			next_x[3]=-1;
			next_y[3]=-1;
		}
		if(next_x[3]!=-1&&next_y[3]!=-1)
		{
			nextx=next_x[3];
			nexty=next_y[3];
		}
	}
	else if(next_x[4]!=-1&&next_y[4]!=-1)
	{
		if(position_x==next_x[4]&&position_y==next_y[4])
		{
			next_x[4]=-1;
			next_y[4]=-1;
		}
		if(next_x[4]!=-1&&next_y[4]!=-1)
		{
			nextx=next_x[4];
			nexty=next_y[4];
		}
	}
	else if(next_x[5]!=-1&&next_y[5]!=-1)
	{
		if(position_x==next_x[5]&&position_y==next_y[5])
		{
			next_x[5]=-1;
			next_y[5]=-1;
		}
		if(next_x[5]!=-1&&next_y[5]!=-1)
		{
			nextx=next_x[5];
			nexty=next_y[5];
		}
	}
	else if(next_x[6]!=-1&&next_y[6]!=-1)
	{
		if(position_x==next_x[6]&&position_y==next_y[6])
		{
			next_x[6]=-1;
			next_y[6]=-1;
		}
		if(next_x[6]!=-1&&next_y[6]!=-1)
		{
			nextx=next_x[6];
			nexty=next_y[6];
		}
	}
	else if(next_x[7]!=-1&&next_y[7]!=-1)
	{
		if(position_x==next_x[7]&&position_y==next_y[7])
		{
			next_x[7]=-1;
			next_y[7]=-1;
		}
		if(next_x[7]!=-1&&next_y[7]!=-1)
		{
			nextx=next_x[7];
			nexty=next_y[7];
		}
	}
	else if(next_x[8]!=-1&&next_y[8]!=-1)
	{
		if(position_x==next_x[8]&&position_y==next_y[8])
		{
			next_x[8]=-1;
			next_y[8]=-1;
		}
		if(next_x[8]!=-1&&next_y[8]!=-1)
		{
			nextx=next_x[8];
			nexty=next_y[8];
		}
	}
	else if(next_x[9]!=-1&&next_y[9]!=-1)
	{
		if(position_x==next_x[9]&&position_y==next_y[9])
		{
			next_x[9]=-1;
			next_y[9]=-1;
		}
		if(next_x[9]!=-1&&next_y[9]!=-1)
		{
			nextx=next_x[9];
			nexty=next_y[9];
		}
	}
	else if(next_x[10]!=-1&&next_y[10]!=-1)
	{
		if(position_x==next_x[10]&&position_y==next_y[10])
		{
			next_x[10]=-1;
			next_y[10]=-1;
		}
		if(next_x[10]!=-1&&next_y[10]!=-1)
		{
			nextx=next_x[10];
			nexty=next_y[10];
		}
	}
	else if((position_x!=target_position_x||position_y!=target_position_y)&&IsPathCalFinish)
	{
		nextx=target_position_x;
		nexty=target_position_y;
		
	}
	else 
	{
		nextx=position_x;
		nexty=position_y;
	}
	
	
	if(position_x==target_position_x&&position_y==target_position_y)
	{
		IsMoveFinsh=1;
		nextx=position_x;
		nexty=position_y;
	}
	else
		IsMoveFinsh=0;

}

void begin1(void)
{
	while(required_vel<slow_vel)
		required_vel+=down_vel;
	required_vel=slow_vel;
	while(1)
	{
		if((infrared2==WHITE&&infrared4==WHITE)||(infrared1==WHITE&&infrared3==WHITE))
			break;
		OLED_SHOW_MANU();
	}
	required_vel=0;
	Arm_run();
	while(required_vel<slow_vel)
		required_vel+=down_vel;
	required_vel=slow_vel;
	delay(800);
	while(1)
	{
		if((infrared2==WHITE&&infrared4==WHITE)||(infrared1==WHITE&&infrared3==WHITE))
			break;
		OLED_SHOW_MANU();
	}
	required_vel=0;
	ROTATE(0);
	IsHD=1;
	while(required_vel<slow_vel)
		required_vel+=down_vel;
	required_vel=slow_vel;
	delay(800);
	while(1)
	{
		if((infrared2==WHITE&&infrared4==WHITE)||(infrared1==WHITE&&infrared3==WHITE))
			break;
		OLED_SHOW_MANU();
	}
	required_vel=0;
	
	orientation=positive_y;
	position_x=1;
	position_y=3;
	target_position_x=1;
	target_position_y=3;
	nextx=1;
	nexty=3;
	IsMoveFinsh=1;
}
void begin2(void)
{
	while(required_vel<slow_vel)
		required_vel+=down_vel;
	required_vel=slow_vel;
	while(1)
	{
		if((infrared2==WHITE&&infrared4==WHITE)||(infrared1==WHITE&&infrared3==WHITE))
			break;
		OLED_SHOW_MANU();
	}
	required_vel=0;
	Arm_run();
	ROTATE(1);
	IsHD=1;
	while(required_vel<slow_vel)
		required_vel+=down_vel;
	required_vel=slow_vel;
	delay(800);
	while(1)
	{
		if((infrared2==WHITE&&infrared4==WHITE)||(infrared1==WHITE&&infrared3==WHITE))
			break;
		OLED_SHOW_MANU();
	}
	required_vel=0;
	
	orientation=negative_y;
	position_x=0;
	position_y=1;
	target_position_x=0;
	target_position_y=1;
	nextx=0;
	nexty=1;
	IsMoveFinsh=1;
}

void begin3(void)
{
	while(required_vel<slow_vel)
		required_vel+=down_vel;
	required_vel=slow_vel;
	while(1)
	{
		if((infrared2==WHITE&&infrared4==WHITE)||(infrared1==WHITE&&infrared3==WHITE))
			break;
		OLED_SHOW_MANU();
	}
	required_vel=0;
	Arm_run();
	ROTATE(0);
	IsHD=1;
	while(required_vel<slow_vel)
		required_vel+=down_vel;
	required_vel=slow_vel;
	delay(800);
	while(1)
	{
		if((infrared2==WHITE&&infrared4==WHITE)||(infrared1==WHITE&&infrared3==WHITE))
			break;
		OLED_SHOW_MANU();
	}
	required_vel=0;
	
	orientation=negative_y;
	position_x=0;
	position_y=3;
	target_position_x=0;
	target_position_y=3;
	nextx=0;
	nexty=3;
	IsMoveFinsh=1;
}



void patrol1(void)			//巡视1代码
{
	switch(patrolStatus)
	{
		case 1:	
		patrolStatus=2;			
			break;
		case 2:
			if(IsMoveFinsh&&orientation!=positive_y)
			{
				switch(orientation)
				{
					case positive_x:ROTATE(0);break;
					default:ROTATE(1);
				}
			}
			else if(Distance<=100&&IsMoveFinsh)
			{
				Obstacle=6;
				nextx=position_x;
				nexty=position_y;
				path_Init();
				patrolStatus=3;
			}
			else if(Distance<=220&&IsMoveFinsh)
			{
				Obstacle=5;
				nextx=position_x;
				nexty=position_y;
				path_Init();
				patrolStatus=3;
			}
			else if(IsMoveFinsh)
			{
				LED3=0;
				nextx=position_x;
				nexty=position_y;
				patrolStatus=3;
			}
			break;
		case 3:
			toCoordinate(3,8);
			patrolStatus=4;
			break;
		case 4:
			if(IsMoveFinsh&&orientation!=positive_x)
			{
				switch(orientation)
				{
					case negative_y:ROTATE(0);break;
					default:ROTATE(1);
				}
			}
			else if(Distance<=100&&IsMoveFinsh&&orientation==positive_x)
			{
				Obstacle=4;
				nextx=position_x;
				nexty=position_y;
				path_Init();
				patrolStatus=5;
			}
			else if(Distance<=220&&IsMoveFinsh&&orientation==positive_x)
			{
				Obstacle=3;
				nextx=position_x;
				nexty=position_y;
				path_Init();
				patrolStatus=5;
			}
			else if(IsMoveFinsh)
			{
				nextx=position_x;
				nexty=position_y;
				patrolStatus=5;
			}
			break;
		case 5:
			toCoordinate(3,9);
			patrolStatus=6;
			break;
		case 6:
			if(IsMoveFinsh)
				patrolStatus=7;
			break;
		case 7:
			toCoordinate(4,9);
			patrolStatus=8;
			break;
		case 8:
			if(IsMoveFinsh&&orientation!=positive_x)
				switch(orientation)
				{
					case negative_y:ROTATE(0);break;
					default:ROTATE(1);
				}
			else if(IsMoveFinsh)
			{
				/***********补充货架障碍物程序**********/
				if(ADC_ConvertedValue[2]>Dis_Vel)
					shelves[0]=1;
				if(ADC_ConvertedValue[3]>Dis_Vel)
					shelves[1]=1;
				patrolStatus=9;
			}
			break;
		case 9:
			toCoordinate(5,9);
			patrolStatus=10;
			break;
		case 10:
			if(IsMoveFinsh)
			{
				/***********补充货架障碍物程序**********/
				if(ADC_ConvertedValue[2]>Dis_Vel)
					shelves[2]=1;
				if(ADC_ConvertedValue[3]>Dis_Vel)
					shelves[3]=1;
				patrolStatus=11;
			}
			break;
		case 11:
			toCoordinate(6,9);
			patrolStatus=12;
			break;
		case 12:
			if(IsMoveFinsh)
			{
				/***********补充货架障碍物程序**********/
				patrolStatus=13;
				if(ADC_ConvertedValue[2]>Dis_Vel)
					shelves[4]=1;
				if(ADC_ConvertedValue[3]>Dis_Vel)
					shelves[5]=1;
			}
			break;
		case 13:
			toCoordinate(7,9);
			patrolStatus=14;
			break;
		case 14:
			if(IsMoveFinsh)
			{
				/***********补充货架障碍物程序**********/
				patrolStatus=15;
				if(ADC_ConvertedValue[2]>Dis_Vel)
					shelves[6]=1;
				if(ADC_ConvertedValue[3]>Dis_Vel)
					shelves[7]=1;
			}
			break;
		case 15:
			toCoordinate(8,9);
			patrolStatus=16;
			break;
		case 16:
			if(IsMoveFinsh)
			{
				/***********补充货架障碍物程序**********/
				if(ADC_ConvertedValue[2]>Dis_Vel)
					shelves[8]=1;
				if(ADC_ConvertedValue[3]>Dis_Vel)
					shelves[9]=1;
				patrolStatus=17;
			}
		break;
		case 17:
			toCoordinate(9,9);
			patrolStatus=18;
			break;
		case 18:
			if(IsMoveFinsh)
			{
				/***********补充货架障碍物程序**********/
				if(ADC_ConvertedValue[2]>Dis_Vel)
					shelves[10]=1;
				if(ADC_ConvertedValue[3]>Dis_Vel)
					shelves[11]=1;
				patrolStatus=100;
			}
		break;
	}	
}

void patrol2(void)			//巡视2代码
{
	switch(patrolStatus)
	{
		case 1:
			toCoordinate(6,1);
			patrolStatus=2;
			break;
		case 2:
			if(IsMoveFinsh&&orientation!=positive_x)
			{
				switch(orientation)
				{
					case negative_y:ROTATE(0);break;
					default:ROTATE(1);
				}
			}
			else if(Distance<=100&&IsMoveFinsh&&orientation==positive_x)
			{
				Obstacle=1;
				nextx=position_x;
				nexty=position_y;
				path_Init();
				patrolStatus=3;
			}
			else if(IsMoveFinsh)
			{
				nextx=position_x;
				nexty=position_y;
				patrolStatus=3;
			}
			break;	
		case 3:
			toCoordinate(9,0);
			patrolStatus=4;
			break;
		case 4:
			if(IsMoveFinsh&&orientation!=positive_y)
				switch(orientation)
				{
					case negative_x:ROTATE(0);break;
					default:ROTATE(1);
				}
			else if(IsMoveFinsh)
			{
				/***********补充货架障碍物程序**********/
				if(ADC_ConvertedValue[2]>Dis_Vel)
					shelves[0]=1;
				if(ADC_ConvertedValue[3]>Dis_Vel)
					shelves[1]=1;
				patrolStatus=5;
			}
			break;
		case 5:
			toCoordinate(9,1);
			patrolStatus=6;
			break;
		case 6:
			if(IsMoveFinsh&&orientation!=positive_y)
				switch(orientation)
				{
					case negative_x:ROTATE(0);break;
					default:ROTATE(1);
				}
			else if(IsMoveFinsh)
			{
				/***********补充货架障碍物程序**********/
				if(ADC_ConvertedValue[2]>Dis_Vel)
					shelves[2]=1;
				if(ADC_ConvertedValue[3]>Dis_Vel)
					shelves[3]=1;
				patrolStatus=7;
			}
			break;
		case 7:
			toCoordinate(9,2);
			patrolStatus=8;
			break;
		case 8:
			if(IsMoveFinsh&&orientation!=positive_y)
				switch(orientation)
				{
					case negative_x:ROTATE(0);break;
					default:ROTATE(1);
				}
			else if(IsMoveFinsh)
			{
				/***********补充货架障碍物程序**********/
				if(ADC_ConvertedValue[2]>Dis_Vel)
					shelves[4]=1;
				if(ADC_ConvertedValue[3]>Dis_Vel)
					shelves[5]=1;
				patrolStatus=9;
			}
			break;
		case 9:
			toCoordinate(9,3);
			patrolStatus=10;
			break;
		case 10:
			if(IsMoveFinsh&&orientation!=positive_y)
				switch(orientation)
				{
					case negative_x:ROTATE(0);break;
					default:ROTATE(1);
				}
			else if(IsMoveFinsh)
			{
				/***********补充货架障碍物程序**********/
				if(ADC_ConvertedValue[2]>Dis_Vel)
					shelves[6]=1;
				if(ADC_ConvertedValue[3]>Dis_Vel)
					shelves[7]=1;
				patrolStatus=11;
			}
			break;
		case 11:
			toCoordinate(9,4);
			patrolStatus=12;
			break;
		case 12:
			if(IsMoveFinsh&&orientation!=positive_y)
				switch(orientation)
				{
					case negative_x:ROTATE(0);break;
					default:ROTATE(1);
				}
			else if(IsMoveFinsh)
			{
				/***********补充货架障碍物程序**********/
				if(ADC_ConvertedValue[2]>Dis_Vel)
					shelves[8]=1;
				if(ADC_ConvertedValue[3]>Dis_Vel)
					shelves[9]=1;
				patrolStatus=13;
			}
			break;
		case 13:
			toCoordinate(9,5);
			patrolStatus=14;
			break;
		case 14:
			if(IsMoveFinsh&&orientation!=positive_y)
				switch(orientation)
				{
					case negative_x:ROTATE(0);break;
					default:ROTATE(1);
				}
			else if(IsMoveFinsh)
			{
				/***********补充货架障碍物程序**********/
				if(ADC_ConvertedValue[2]>Dis_Vel)
					shelves[10]=1;
				if(ADC_ConvertedValue[3]>Dis_Vel)
					shelves[11]=1;
				patrolStatus=100;
			}
			break;
	}
}

void patrol3(void)			//巡视3代码
{
	switch(patrolStatus)
	{
		case 1:
			toCoordinate(0,4);
			patrolStatus=2;
			break;
		case 2:
			if(IsMoveFinsh&&orientation!=positive_y)
				switch(orientation)
				{
					case negative_x:ROTATE(0);break;
					default:ROTATE(1);
				}
			else if(IsMoveFinsh)
			{
				/***********补充货架障碍物程序**********/
				if(ADC_ConvertedValue[2]>Dis_Vel)
					shelves[0]=1;
				if(ADC_ConvertedValue[3]>Dis_Vel)
					shelves[1]=1;
				patrolStatus=3;
			}
			break;
		case 3:
			toCoordinate(0,5);
			patrolStatus=4;
			break;
		case 4:
			if(IsMoveFinsh&&orientation!=positive_y)
				switch(orientation)
				{
					case negative_x:ROTATE(0);break;
					default:ROTATE(1);
				}
			else if(IsMoveFinsh)
			{
				/***********补充货架障碍物程序**********/
				if(ADC_ConvertedValue[2]>Dis_Vel)
					shelves[2]=1;
				if(ADC_ConvertedValue[3]>Dis_Vel)
					shelves[3]=1;
				patrolStatus=5;
			}
			break;
		case 5:
			toCoordinate(0,6);
			patrolStatus=6;
			break;
		case 6:
			if(IsMoveFinsh&&orientation!=positive_y)
				switch(orientation)
				{
					case negative_x:ROTATE(0);break;
					default:ROTATE(1);
				}
			else if(IsMoveFinsh)
			{
				/***********补充货架障碍物程序**********/
				if(ADC_ConvertedValue[2]>Dis_Vel)
					shelves[4]=1;
				if(ADC_ConvertedValue[3]>Dis_Vel)
					shelves[5]=1;
				patrolStatus=7;
			}
			break;
		case 7:
			toCoordinate(0,7);
			patrolStatus=8;
			break;
		case 8:
			if(IsMoveFinsh&&orientation!=positive_y)
				switch(orientation)
				{
					case negative_x:ROTATE(0);break;
					default:ROTATE(1);
				}
			else if(IsMoveFinsh)
			{
				/***********补充货架障碍物程序**********/
				if(ADC_ConvertedValue[2]>Dis_Vel)
					shelves[6]=1;
				if(ADC_ConvertedValue[3]>Dis_Vel)
					shelves[7]=1;
				patrolStatus=9;
			}
			break;
		case 9:
			toCoordinate(0,8);
			patrolStatus=10;
			break;
		case 10:
			if(IsMoveFinsh&&orientation!=positive_y)
				switch(orientation)
				{
					case negative_x:ROTATE(0);break;
					default:ROTATE(1);
				}
			else if(IsMoveFinsh)
			{
				/***********补充货架障碍物程序**********/
				if(ADC_ConvertedValue[2]>Dis_Vel)
					shelves[8]=1;
				if(ADC_ConvertedValue[3]>Dis_Vel)
					shelves[9]=1;
				patrolStatus=11;
			}
			break;
		case 11:
			toCoordinate(0,9);
			patrolStatus=12;
			break;
		case 12:
			if(IsMoveFinsh&&orientation!=positive_y)
				switch(orientation)
				{
					case negative_x:ROTATE(0);break;
					default:ROTATE(1);
				}
			else if(IsMoveFinsh)
			{
				/***********补充货架障碍物程序**********/
				if(ADC_ConvertedValue[2]>Dis_Vel)
					shelves[10]=1;
				if(ADC_ConvertedValue[3]>Dis_Vel)
					shelves[11]=1;
				patrolStatus=100;
			}
			break;
	}
}



void toCoordinate(uint8_t x,uint8_t y)
{
	target_position_x=x;
	target_position_y=y;
	IsPathCalFinish=0;	
	path_cal();
}
