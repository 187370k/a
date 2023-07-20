#ifndef __STEPPER_H_
#define __STEPPER_H_
#include "main.h"

// �������ת����
typedef enum 
{
	Forward = 0,
	Reversal = 1
} RotDirection;

// ��Ҫʹ�������˿�ʱ��ֻ��Ҫ�������µĺ궨�弴��
// ������Ҫ��֤�ĸ�����˿�ͬ��һ��GPIO
// �������������һ�㣬��Ҫ����Stepper.c�г�ʼ������Stepper_Init��Stepper_RotateByStep�е�һЩ��������
// ����ĺ궨����Ϊ����߳���Ŀɶ��ԺͿ���ֲ�ԣ���ʹ��stm32f10x.h�ж����ԭʼ����Ҳδ������
//#define		Stepper_CLK				RCC_APB2Periph_GPIOA
#define		Stepper_CLK	       __HAL_RCC_GPIOE_CLK_ENABLE();

#define		Stepper_Output_GPIO		GPIOE
#define 	Stepper_LA				GPIO_PIN_2
#define 	Stepper_LB				GPIO_PIN_3
#define 	Stepper_LC				GPIO_PIN_4
#define 	Stepper_LD				GPIO_PIN_5

void Stepper_GPIOInit(void);
void Stepper_Stop(void);
void Stepper_SingleStep(uint8_t StepNum, uint16_t Delay_Time_xms);
void Stepper_RotateByStep(RotDirection direction, uint32_t step, uint16_t Delay_Time_xms);
void Stepper_RotateByLoop(RotDirection direction, uint32_t Loop, uint16_t Delay_Time_xms);

#endif

