#include "led.h"
void LED_Brightness_Contorl(uint16_t Brightness )//����LED���� ������666�� ������1332��������1999
{		
		  HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_3);	//������ʱ��3��ͨ��3��PWM���
		__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3,Brightness);
}