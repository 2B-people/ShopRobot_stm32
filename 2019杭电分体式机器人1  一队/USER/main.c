#include "include.h"
#include "math.h"
#define car1
//////////key_PIN1   	//中
//////////key_PIN2  	//左
//////////key_PIN3  	//下
//////////key_PIN4  	//右
//////////key_PIN5  	//上
//////////key_PIN6  	//独立

float required_vel = 0;
uint8_t IsControlFinsh; //是否完成指定任务
uint8_t IsStop = 0;		//是否接到急停状态信号的标志
uint8_t IsFetch = 0;
uint8_t position_x = 0;			  //当前横坐标
uint8_t position_y = 0;			  //当前纵坐标
uint8_t orientation = positive_x; //当前车的朝向，默认开始为y正方向。
uint8_t target_position_x = 0;	//目标横坐标
uint8_t target_position_y = 0;	//目标纵坐标
uint8_t target_orientation = positive_x;
uint8_t IsHD = 0;
;
;					   //是否使用模拟灰度。
uint8_t Obstacle = 0;  //障碍物位置
uint16_t Distance = 0; //激光雷达测距结果
uint8_t stopping = 0;  //车身是否停止
uint8_t mode = 0;
uint8_t shelves[12]; //C货架
uint8_t Goods_num;
float pitch,roll,yaw; 		//欧拉角
void begin(void);

int main()
{
	mainCAMERA(); //摄像头车  初始坐标(1,2) 初始方向+y
 //mainNOCAMERA(); //非摄像头车
	
}

void mainNOCAMERA(void)
{
	u8 success = 0;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
	SystemInit();
	//initialise();
	delay_init();
	memset(shelves, 0, sizeof(shelves));
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	usart1_Init(115200);
	Arm_Init(7199, 199);
	CAN_Mode_Init(); //初始化CAN总线
	Ledbeep_init();  //初始化LED灯、蜂鸣器
	//RC_Init();
	OLED_Init();			//初始化OLED
	las_Init();				//初始化测距模块
	PID_init();				//初始化PID参数
	huiductrlinit();		//初始化模拟灰度
	infrared_Init();		//初始化底层红外传感器
	KEY_Init();				//初始化按键
	OLED_Clear();			//清空OLED屏
	path_Init();			//初始化路径规划函数
	TIM5_Int_Init(35, 999); //1000HZ		PID调速
	TIM7_Int_Init(35, 999); //1000HZ,    确定速度
	M8266HostIf_Init();
	success = M8266WIFI_Module_Init_Via_SPI();
	LED1 = 0;
	delay(500);
	LED1 = 1;
	delay(500);
	LED1 = 0;
	wifi_wait_begin();
	
	begin1(); //将车从红色框区开出
//	MPU_Init();					//初始化MPU6050
//	while(mpu_dmp_init());
	OLED_SHOW_MANU();
	TIM6_Int_Init(71, 99); //1000HZ		路径规划，确定nextx,nexty 72m
	LED1 = 1;

	mode = 1;
	IsHD = 1;
	
	
	/*********************************************/
//	Arm_run();
//	orientation=positive_y;
//	position_x=7;
//	position_y=3;
//	toFetch(0,2);
//	toCoordinate(9,0);
//	while(1)
//	{
//		MOVE(nextx,nexty);
//		OLED_SHOW_MANU();
//		if(IsMoveFinsh==1)
//			break;
//	}
//	toFetch(100,0);
//	
	/************************************************/
	
	
	
	
	
	
	
	while (1) //巡视
	{
		waitingStop(); //OLED菜单显示、等待上方传送停止指令
		patrol1();	 //巡视场地，找障碍物
		if (!stopping && !IsFetch && !IsMoveFinsh)
		{
			MOVE(nextx, nexty);
		}
		if (patrolStatus == 100)
			break;
	}
	
	
	success = wifi_finish();

	mode = 3;
	

	
	/******************************************/
//				toCoordinate(2,4);
//				while(1)
//			 {
//				 waitingStop();								//OLED菜单显示、等待上方传送停止指令
//				 if(!stopping&&!IsFetch)
//				 {
//					 MOVE(nextx,nexty);
//						OLED_SHOW_MANU();
//				 }
//				 if(position_x==2&&position_y==4)
//				 {
//					 LED3=0;
//					 break;
//				 }
//			 }
//			 toFetch(0,2);
//			 toCoordinate(0,0);
//			 while(1)
//			 {
//				 waitingStop();								//OLED菜单显示、等待上方传送停止指令
//				 if(!stopping&&!IsFetch)
//				 {
//					 MOVE(nextx,nexty);
//						OLED_SHOW_MANU();
//				 }
//				 if(position_x==0&&position_y==0)
//					 break;
//			 }
//			 toFetch(100,1);
	/*******************************/
	while (1) //常规
	{
		wifi_connect();
		waitingStop(); //OLED菜单显示、等待上方传送停止指令
		if (!stopping && !IsFetch)
		{
			MOVE(nextx, nexty);
			sifi_send();
		}
		else if (IsFetch && !stopping)
		{
			toFetch(Goods_num, 1); //抓取
			wifi_finish();
		}
		if (IsMoveFinsh)
		{
			if (target_orientation != orientation)
			{
				switch (target_orientation)
				{
				case positive_x:
					while (orientation != positive_x)
					{
						if (orientation == negative_y)
							ROTATE(0);
						else
							ROTATE(1);
					}
					break;
				case positive_y:
					while (orientation != positive_y)
					{
						if (orientation == positive_x)
							ROTATE(0);
						else
							ROTATE(1);
					}
					break;
				case negative_x:
					while (orientation != negative_x)
					{
						if (orientation == positive_y)
							ROTATE(0);
						else
							ROTATE(1);
					}
					break;
				case negative_y:
					while (orientation != negative_y)
					{
						if (orientation == negative_x)
							ROTATE(0);
						else
							ROTATE(1);
					}
					break;
				}
			}
		}
	}
}

void mainCAMERA(void)
{
	u8 success = 0;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
	SystemInit();
	//initialise();
	delay_init();
	memset(shelves, 0, sizeof(shelves));
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	usart1_Init(115200);
	Arm_Init(7199, 199);
	CAN_Mode_Init(); //初始化CAN总线
	Ledbeep_init();  //初始化LED灯、蜂鸣器
	//RC_Init();
	OLED_Init();			//初始化OLED
	las_Init();				//初始化测距模块
	PID_init();				//初始化PID参数
	huiductrlinit();		//初始化模拟灰度
	infrared_Init();		//初始化底层红外传感器
	KEY_Init();				//初始化按键
	OLED_Clear();			//清空OLED屏
	path_Init();			//初始化路径规划函数
	TIM5_Int_Init(35, 999); //1000HZ		PID调速
	TIM7_Int_Init(35, 999); //1000HZ,    确定速度
	M8266HostIf_Init();
	success = M8266WIFI_Module_Init_Via_SPI();
	LED1 = 0;
	delay(500);
	LED1 = 1;
	delay(500);
	LED1 = 0;

	//开车指令
	wifi_wait_begin();
	begin1(); //将车从红色框区开出
	position_x = 1;
	position_y = 2;
	target_position_x = 1;
	target_position_y = 2;
	nextx = 1;
	nexty = 2;
	TIM6_Int_Init(71, 99); //1000HZ		路径规划，确定nextx,nexty 72m
	sifi_send();
	delay(10);
	success = wifi_finish();
	LED1 = 1;
	mode = 1;
	IsHD = 1;

	while (1) //常规
	{
		wifi_connect();
		waitingStop(); //OLED菜单显示、等待上方传送停止指令
		if (!IsFetch)
		{
			MOVE(nextx, nexty);
			sifi_send();
		}
//		else if (IsFetch && !stopping)
//		{
//			toFetch(Goods_num, 1); //抓取
//			wifi_finish();
//		}
		if (IsMoveFinsh)
		{
			if (target_orientation != orientation)
			{
				switch (target_orientation)
				{
				case positive_x:
					while (orientation != positive_x)
					{
						if (orientation == negative_y)
							ROTATE(0);
						else
							ROTATE(1);
					}
					break;
				case positive_y:
					while (orientation != positive_y)
					{
						if (orientation == positive_x)
							ROTATE(0);
						else
							ROTATE(1);
					}
					break;
				case negative_x:
					while (orientation != negative_x)
					{
						if (orientation == positive_y)
							ROTATE(0);
						else
							ROTATE(1);
					}
					break;
				case negative_y:
					while (orientation != negative_y)
					{
						if (orientation == negative_x)
							ROTATE(0);
						else
							ROTATE(1);
					}
					break;
				}
			}
		}
	}
}
