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
void begin(void);
int main()
{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO ,ENABLE);    
		GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
		SystemInit();
		initialise();
		memset(shelves,0,sizeof(shelves));
			NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);			
			usart1_Init(115200);
			CAN_Mode_Init();
			Ledbeep_init();
			//RC_Init();
			OLED_Init(); 
			las_Init();
			PID_init();
			huiductrlinit();
			infrared_Init();
			KEY_Init();
			OLED_Clear();
			path_Init();	
			TIM5_Int_Init(35, 999); //1000HZ		PID调速
			TIM7_Int_Init(35,999);	//1000HZ,    确定速度		
			LED1=0;
			delay(500);
			LED1=1;
			delay(500);
			LED1=0;
			begin();
			OLED_SHOW_MANU();
			TIM6_Int_Init(35, 999);  //10HZ		路径规划，确定nextx,nexty
			LED1=1;
			
//			
//			position_x=2;
//			position_y=4;
//			orientation=positive_y ;		//测试抓取
//			toFetch();
			
			 
			mode=1;
			while(1)								//开始
			{
				waitingStop();
				if(!stopping&&!IsRemote&&!IsFetch)
					 MOVE(nextx,nexty);
				if(position_x==0&&position_y==3)
					break;
			}
			IsHD=1;
			mode=2;
			 while(1)									//巡视
			 {
					//remoteAction();						//遥控器指令，调试用
				 waitingStop();								//OLED菜单显示、等待上方传送停止指令				
				 patrol(); 										 //巡视场地，找障碍物
				 if(!stopping&&!IsRemote&&!IsFetch)
					 MOVE(nextx,nexty);
				 if(patrolStatus==19)
					 break;
			 }
			 while(1)
			 {
				 OLED_SHOW_MANU();
			 }
			 mode=4;
			 while(1)									//常规
			 {
				 	//remoteAction();						//遥控器指令，调试用
				 waitingStop();								//OLED菜单显示、等待上方传送停止指令				
				 if(!stopping&&!IsRemote&&!IsFetch)
					 MOVE(nextx,nexty);
				 else if(IsFetch&&!stopping&&!IsRemote)
					 toFetch();
			 }
}


