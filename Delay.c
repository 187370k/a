#include "gpio.h"
#include "stm32h7xx.h"                  // Device header
#include "tim.h"
 
//void Delay_us(uint16_t nus)
//{
//	__HAL_TIM_SET_COUNTER(&htim2, 0); //�Ѽ�������ֵ����Ϊ0
//	__HAL_TIM_ENABLE(&htim2); //��������
//	while (__HAL_TIM_GET_COUNTER(&htim2) < nus); //ÿ����һ�Σ�����1us��ֱ��������ֵ����������Ҫ��ʱ��
//	__HAL_TIM_DISABLE(&htim2); //�رռ���
//}
///* USER CODE END 0 */
void Delay_us(uint16_t us)
{     
	uint16_t differ = 0xffff-us-5;				
	__HAL_TIM_SET_COUNTER(&htim2,differ);	//�趨TIM2��������ʼֵ
	HAL_TIM_Base_Start(&htim2);		//������ʱ��	
	
	while(differ < 0xffff-5)//�ж�
	{	
		differ = __HAL_TIM_GET_COUNTER(&htim2);		//��ѯ�������ļ���ֵ
	}
	HAL_TIM_Base_Stop(&htim2);//�رն�ʱ��
}

void Delay_ms(unsigned int xms)
{
	for(; xms>0; xms--)
	{
		Delay_us(1000);
	}
}
//΢����ʱ
