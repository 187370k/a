#include "tim.h"
#include "servos.h"
void Servos_Control(uint16_t  jiaodu)
	{     
		 HAL_TIM_PWM_Start(&htim5,TIM_CHANNEL_2);	//开启定时器5的通道2的PWM输出
		__HAL_TIM_SET_COMPARE(&htim5, TIM_CHANNEL_2,jiaodu*200/180+50);		
	}
