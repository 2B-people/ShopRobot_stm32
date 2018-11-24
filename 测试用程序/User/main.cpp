#include <stdio.h>
#include "hardwareserial.h"
#include "config.h"
#include "motor.h"
#include "led.h"
#include "PID.h"
#include "Kinematics.h"
#include <riki_msgs/Velocities.h>
#include <geometry_msgs/Twist.h>
#include <riki_msgs/Imu.h>
#include <riki_msgs/Battery.h>
#include <geometry_msgs/Vector3.h>
#include "control.h"
#include "timer.h"
#include "remote.h"
#include "las_measure.h"

#ifdef __cplusplus
extern "C" {
#include "oled.h"
#endif
#ifdef __cplusplus
}
#endif

double required_angular_vel = 0;
double required_linear_vel_x =0;
double required_linear_vel_y = 0;
double required_pitch ;
double required_yaw ;
extern REMOTE RC_CtrlData;
extern uint16_t USART_RX_STA;

Kinematics kinematics(MAX_RPM, WHEEL_DIAMETER,LENGTH_A ,LENGTH_B ,COUNTS_PER_REV);
Kinematics::output required_rpm;

Led led;
HardwareSerial usart1(SERIAL1);

Motor motor1(0x201);
Motor motor2(0x202);
Motor motor3(0x203);
Motor motor4(0x204);
Motor yt_motor1(0x205);
Motor yt_motor2(0x206);














int main(void)
{
	SystemInit();
	initialise();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	
	CAN_Mode_Init();
	OLED_Init();		
	TIM5_Int_Init(71,9999);//100HZ
	TIM6_Int_Init(719,9999);//10HZ
	RC_Init();
	las_Init();
	usart1.begin(115200);
	yt_motor1.resetPid(YT_KP,YT_KI,YT_KD);
	while(1)
	{	

		usart1.print("Running...\n");
		usart1.print("F:%d\n",las_data(FORWARD));
		usart1.print("B:%d\n",las_data(BACK));
		usart1.print("L:%d\n",las_data(LEFT));
		usart1.print("R:%d",las_data(RIGHT));
		usart1.print("RX_STA:%d\n\n\n\n",USART_RX_STA);
		delay(1);
	}
}




