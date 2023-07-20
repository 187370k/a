/**
  ******************************************************************************
  * @file    adc.h
  * @brief   This file contains all the function prototypes for
  *          the adc.c file
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __ADC_H__
#define __ADC_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

extern ADC_HandleTypeDef hadc1;

/* USER CODE BEGIN Private defines */
#define SMOG_READ_TIMES	3			//��������������ȡ����,����ô���,Ȼ��ȡƽ��ֵ
/* USER CODE END Private defines */
void MX_ADC1_Init(void);
/* USER CODE BEGIN Prototypes */
//uint32_t adc_get_result(void);
//float Smog_Get_Vol(void);	//��ȡMQ7�������ĵ�ѹֵ
//float Smog_GetPPM(void);
//uint32_t MQ2_ADC_Read(void);//��ȡ��������һ��ADCת��ֵ
//uint16_t ADC1_Average_Data(void);//��ȡ��������ADCת��ֵƽ��ֵ
//uint32_t Photoresistor_module_ADC_Read(void);
uint16_t Board_Get_ADCChannelValue(ADC_HandleTypeDef* hadc,uint32_t channel);//��ȡadc1,����ͨ��������
extern uint16_t   MQ_2_Date;
extern uint16_t   Light_Date;
extern uint8_t   MQ_2_Flag;
extern uint8_t   Light_Flag;
uint16_t MQ_2_Average_Data(void);
uint16_t Light_Average_Data(void);
//��ͨ��3 PA6     ------> ADC1_INP3Ϊ��������ֵΪС��7000�����ֵΪ11000��
//ͨ��4   PC4     ------> ADC1_INP4 //����Ϊ11000���ϰ�ʱΪ30000��ȫ��60000
//extern ADC_ChannelConfTypeDef sConfig;
extern uint16_t ADC_Average_Value(void);//ADCת��ֵƽ��ֵ
/*****************����ֵΪС��7000�����ֵΪ11000��
/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __ADC_H__ */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
