#include "DC motor.h"
void DC_motor_GPIO_Init(void)//控制直流电机正反转默认为正转
{
	HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_4);	//开启定时器3的通道4的PWM输出
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  __HAL_RCC_GPIOE_CLK_ENABLE();
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);
  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_0, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_1, GPIO_PIN_RESET);
	
}
void DC_motor_Contorl(uint16_t Pulse)//设置电机转速0~1999，一档666，二档1332，三档1999
{	
		HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_4);	//开启定时器3的通道4的PWM输出
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4,Pulse);
}