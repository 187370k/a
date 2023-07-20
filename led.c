#include "led.h"
void LED_Brightness_Contorl(uint16_t Brightness )//设置LED亮度 低亮度666， 中亮度1332，高亮度1999
{		
		  HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_3);	//开启定时器3的通道3的PWM输出
		__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3,Brightness);
}