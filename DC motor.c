#include "DC motor.h"
void DC_motor_GPIO_Init(void)//����ֱ���������תĬ��Ϊ��ת
{
	HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_4);	//������ʱ��3��ͨ��4��PWM���
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
void DC_motor_Contorl(uint16_t Pulse)//���õ��ת��0~1999��һ��666������1332������1999
{	
		HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_4);	//������ʱ��3��ͨ��4��PWM���
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4,Pulse);
}