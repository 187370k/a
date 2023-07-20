#ifndef __DC_motor_H_
#define __DC_motor_H_
#include "main.h"
#include "tim.h"
// PC6     ------> TIM3_CH1
void DC_motor_GPIO_Init(void);//控制直流电机正反转默认为正转,打开PWM
void DC_motor_Contorl(uint16_t Pulse);//设置电机转速0~1999，一档500，二档1000，三档1500
#endif