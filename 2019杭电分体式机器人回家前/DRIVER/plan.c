#include "plan.h"

//一开始以线性关系减速，在最后一刻急停。
uint8_t IsMoveFinsh=0;
uint8_t IsRotate=0;


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

int8_t nextx;
int8_t nexty;

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
						required_vel=fast_vel;
					else if(_target_position_x-position_x==1)
					{
						required_vel-=down_vel;
						if(required_vel<=slow_vel)
							required_vel=slow_vel;
					}
					break;
				case negative_x:
					if(_target_position_x-position_x>1)
						required_vel=-fast_vel;
					else if(_target_position_x-position_x==1)
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
					else if(_target_position_x-position_x==1)
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
					else if(_target_position_x-position_x==1)
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
				else if(_target_position_x-position_x==-1)
				{
						required_vel+=down_vel;
						if(required_vel>=(-slow_vel)) 
							required_vel=(-slow_vel);
				}
				break;
			case negative_x:
				if(position_x-_target_position_x>1)
					required_vel=fast_vel;
				else if(_target_position_x-position_x==-1)
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
				else if(_target_position_x-position_x==-1)
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
				else if(_target_position_x-position_x==-1)
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
				else if(_target_position_y-position_y==1)
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
				else if(_target_position_y-position_y==1)
				{
					required_vel-=down_vel;
					if(required_vel<=slow_vel)
						required_vel=slow_vel;
				}
				break;
			case positive_y:
				if(_target_position_y-position_y>1)
					required_vel=fast_vel;
				else if(_target_position_y-position_y==1)
				{
					required_vel-=down_vel;
					if(required_vel<=slow_vel)
						required_vel=slow_vel;
				}
				break;
			case negative_y:
				if(_target_position_y-position_y>1)
					required_vel=-fast_vel;
				else if(_target_position_y-position_y==1)
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
				else if(_target_position_y-position_y==-1)
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
				else if(_target_position_y-position_y==-1)
				{
					required_vel-=down_vel;
					if(required_vel<=slow_vel)
						required_vel=slow_vel;
				}
				break;
			case positive_y:

				if(position_y-_target_position_y>1)
					required_vel=-fast_vel;
				else if(_target_position_y-position_y==-1)
				{
						required_vel+=down_vel;
						if(required_vel>=(-slow_vel)) 
							required_vel=(-slow_vel);
				}
				break;
			case negative_y:
				if(position_y-_target_position_y>1)
					required_vel=fast_vel;
				else if(_target_position_y-position_y==-1)
				{
					required_vel-=down_vel;
					if(required_vel<=slow_vel)
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
	memset(prex, -1, sizeof(prex));
	memset(prey, -1, sizeof(prey));
	memset(next_x, -1, sizeof(next_x));
	memset(next_y, -1, sizeof(next_y));

	initQueue(&qx);
	initQueue(&qy);
	initQueue(&lujinx);
	initQueue(&lujiny);
	strcpy(graph[0], "**********");
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
	path_Init();
	graph[position_x][position_y] = 'S';
	graph[target_position_x][target_position_y] = 'T';
	sx=position_x;sy=position_y;tx=target_position_x;ty=target_position_y;
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
	
}


void move_base()
{
	
	if(next_x[0]!=-1&&next_y[0]!=-1)
	{
			nextx=next_x[0];
			nexty=next_y[0];
		if(position_x==next_x[0]&&position_y==next_y[0])
		{
			next_x[0]=-1;
			next_y[0]=-1;
		}
	}
	else if(next_x[1]!=-1&&next_y[1]!=-1)
	{
			nextx=next_x[1];
			nexty=next_y[1];
		if(position_x==next_x[1]&&position_y==next_y[1])
		{
			next_x[1]=-1;
			next_y[1]=-1;
		}
	}
	else if(next_x[2]!=-1&&next_y[2]!=-1)
	{
			nextx=next_x[2];
			nexty=next_y[2];
		if(position_x==next_x[2]&&position_y==next_y[2])
		{
			next_x[2]=-1;
			next_y[2]=-1;
		}
	}
	else if(next_x[3]!=-1&&next_y[3]!=-1)
	{
		nextx=next_x[3];
			nexty=next_y[3];
		if(position_x==next_x[3]&&position_y==next_y[3])
		{
			next_x[3]=-1;
			next_y[3]=-1;
		}
	}
	else if(next_x[4]!=-1&&next_y[4]!=-1)
	{
		nextx=next_x[4];
			nexty=next_y[4];
		if(position_x==next_x[4]&&position_y==next_y[4])
		{
			next_x[4]=-1;
			next_y[4]=-1;
		}
	}
	else if(next_x[5]!=-1&&next_y[5]!=-1)
	{
		nextx=next_x[5];
			nexty=next_y[5];
		if(position_x==next_x[5]&&position_y==next_y[5])
		{
			next_x[5]=-1;
			next_y[5]=-1;
		}
	}
	else if(next_x[6]!=-1&&next_y[6]!=-1)
	{
		nextx=next_x[6];
			nexty=next_y[6];
		if(position_x==next_x[6]&&position_y==next_y[6])
		{
			next_x[6]=-1;
			next_y[6]=-1;
		}
	}
	else if(next_x[7]!=-1&&next_y[7]!=-1)
	{
		nextx=next_x[7];
			nexty=next_y[7];
		if(position_x==next_x[7]&&position_y==next_y[7])
		{
			next_x[7]=-1;
			next_y[7]=-1;
		}
	}
	else if(next_x[8]!=-1&&next_y[8]!=-1)
	{
		nextx=next_x[8];
			nexty=next_y[8];
		if(position_x==next_x[8]&&position_y==next_y[8])
		{
			next_x[8]=-1;
			next_y[8]=-1;
		}
	}
	else if(next_x[9]!=-1&&next_y[9]!=-1)
	{
		nextx=next_x[9];
			nexty=next_y[9];
		if(position_x==next_x[9]&&position_y==next_y[9])
		{
			next_x[9]=-1;
			next_y[9]=-1;
		}
	}
	else if(next_x[10]!=-1&&next_y[10]!=-1)
	{
		nextx=next_x[10];
			nexty=next_y[10];
		if(position_x==next_x[10]&&position_y==next_y[10])
		{
			next_x[10]=-1;
			next_y[10]=-1;
		}
	}
	else
	{
		nextx=target_position_x;
		nexty=target_position_y;
	}

	
	
	if(position_x==target_position_x&&position_y==target_position_y)
	{
		IsMoveFinsh=1;
		nextx=target_position_x;
		nexty=target_position_y;
		required_vel=0;
	}
	else
		IsMoveFinsh=0;

	MOVE(nextx,nexty);
}


