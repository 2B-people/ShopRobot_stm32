#include "include.h"
#include "math.h"

//////////key_PIN1   	//中
//////////key_PIN2  	//左
//////////key_PIN3  	//下
//////////key_PIN4  	//右
//////////key_PIN5  	//上
//////////key_PIN6  	//独立


double required_vel = 0;
uint8_t IsControlFinsh;			  //是否完成指定任务
uint8_t IsStop=0;					  //是否接到急停状态信号的标志
uint8_t IsFetch=0;
uint8_t position_x = 0;			  //当前横坐标
uint8_t position_y = 0;			  //当前纵坐标
uint8_t orientation=positive_y ; //当前车的朝向，默认开始为y正方向。
uint8_t target_position_x = 0;	//目标横坐标
uint8_t target_position_y = 0;	//目标纵坐标
uint8_t IsHD=0;                                               ;                                                                                                                                                                                                                                                                                                                                                                                                 ;									//是否使用模拟灰度。
uint8_t Obstacle=0;						//障碍物位置
uint16_t Distance=0;					//激光雷达测距结果
uint8_t stopping=0;				  //车身是否停止
uint8_t mode=0;
uint8_t shelves[12];				//C货架
uint8_t Goods_num;
void begin(void);
int main()
{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO ,ENABLE);    
		GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
		SystemInit();
		initialise();
		delay(1000);
		memset(shelves,0,sizeof(shelves));
			NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);			
			usart1_Init(115200);
			Arm_Init(7199,199);
			CAN_Mode_Init();			//初始化CAN总线
			Ledbeep_init();				//初始化LED灯、蜂鸣器
			//RC_Init();	
			OLED_Init(); 					//初始化OLED
			las_Init();						//初始化测距模块
			PID_init();						//初始化PID参数
			huiductrlinit();			//初始化模拟灰度
			infrared_Init();			//初始化底层红外传感器
			KEY_Init();						//初始化按键
			OLED_Clear();					//清空OLED屏
			path_Init();					//初始化路径规划函数
			TIM5_Int_Init(35, 999); //1000HZ		PID调速
			TIM7_Int_Init(35,999);	//1000HZ,    确定速度		
			LED1=0;
			delay(500);
			LED1=1;
			delay(500);
			LED1=0;

			
			begin();								//将车从红色框区开出
			OLED_SHOW_MANU();
			TIM6_Int_Init(71, 999);  //1000HZ		路径规划，确定nextx,nexty 72m
			LED1=1;

			mode=1;	
			IsHD=1;
			 while(1)									//巡视
			 {				
				 waitingStop();								//OLED菜单显示、等待上方传送停止指令				
				 patrol(); 										 //巡视场地，找障碍物
				 if(!stopping&&!IsRemote&&!IsFetch)
					 MOVE(nextx,nexty);
				 if(patrolStatus==19)
					 break;
			 }
			 mode=3;		

/********************************************************/			 
			 toFetch(100,1);
			 target_position_x=5;
			 target_position_y=7;
			 path_cal();			 
			 while(1)									//常规
			 {					
				 waitingStop();								//OLED菜单显示、等待上方传送停止指令				
				 if(!stopping&&!IsRemote&&!IsFetch)
					 MOVE(nextx,nexty);
				 if(position_x==5&&position_y==7)
					 break;
			 }
			 toFetch(0,0);
			 while(1)
			 {
				 OLED_SHOW_MANU();
			 }
			 
/**********************************************************/	 
			 while(1)									//常规
			 {					
				 waitingStop();								//OLED菜单显示、等待上方传送停止指令				
				 if(!stopping&&!IsRemote&&!IsFetch)
					 MOVE(nextx,nexty);
				 else if(IsFetch&&!stopping&&!IsRemote)
					 toFetch(Goods_num,1);									//抓取
			 }
}


