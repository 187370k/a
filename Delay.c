#include "gpio.h"
#include "stm32h7xx.h"                  // Device header
#include "tim.h"
 
//void Delay_us(uint16_t nus)
//{
//	__HAL_TIM_SET_COUNTER(&htim2, 0); //把计数器的值设置为0
//	__HAL_TIM_ENABLE(&htim2); //开启计数
//	while (__HAL_TIM_GET_COUNTER(&htim2) < nus); //每计数一次，就是1us，直到计数器值等于我们需要的时间
//	__HAL_TIM_DISABLE(&htim2); //关闭计数
//}
///* USER CODE END 0 */
void Delay_us(uint16_t us)
{     
	uint16_t differ = 0xffff-us-5;				
	__HAL_TIM_SET_COUNTER(&htim2,differ);	//设定TIM2计数器起始值
	HAL_TIM_Base_Start(&htim2);		//启动定时器	
	
	while(differ < 0xffff-5)//判断
	{	
		differ = __HAL_TIM_GET_COUNTER(&htim2);		//查询计数器的计数值
	}
	HAL_TIM_Base_Stop(&htim2);//关闭定时器
}

void Delay_ms(unsigned int xms)
{
	for(; xms>0; xms--)
	{
		Delay_us(1000);
	}
}
//微秒延时
