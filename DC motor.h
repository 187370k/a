#ifndef __DC_motor_H_
#define __DC_motor_H_
#include "main.h"
#include "tim.h"
// PC6     ------> TIM3_CH1
void DC_motor_GPIO_Init(void);//����ֱ���������תĬ��Ϊ��ת,��PWM
void DC_motor_Contorl(uint16_t Pulse);//���õ��ת��0~1999��һ��500������1000������1500
#endif