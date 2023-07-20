#include "buzzer.h"
void Buzzer_Init()
{	
	 GPIO_InitTypeDef GPIO_InitStruct = {0};
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();	 
  GPIO_InitStruct.Pin = GPIO_PIN_6;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);
	 
	GPIO_InitStruct.Pin = GPIO_PIN_13|GPIO_PIN_12;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
	HAL_GPIO_WritePin(GPIOD,GPIO_PIN_13,GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOD,GPIO_PIN_12,GPIO_PIN_RESET);	 
}

