/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32h7xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
/* USER CODE BEGIN Private defines */
extern     uint8_t WS_Flag;//��������ģʽ��־λ
extern     uint8_t LS_Flag;//�ƹ�����ģʽ��־λ
extern     uint8_t CS_Flag;//��������ģʽ��־λ
extern     uint8_t FS_Flag;//��������ģʽ��־λ
extern      uint8_t Show_Flag; //��������λ����������
		 
extern 		 uint8_t Curtain_Flag; //�����жϴ��������	    0Ϊ�رգ�1Ϊ�뿪��2Ϊȫ��
extern 		 uint8_t Fan_Flag;     // �����жϷ��ȵ������ 	0Ϊ�رգ�1Ϊ1����2Ϊ2����3Ϊ3��
extern 		 uint8_t Lignt_Flag;    //�����жϼ���������	     0Ϊ�أ�1Ϊ����2Ϊ�ϰ���3Ϊ����
extern     uint8_t Windows_Flag;  //�����жϴ��������	   0Ϊ�أ�1Ϊ�뿪��2Ϊȫ��
extern		 uint8_t Curtain_Work_Flag;		 //�����жϲ�������Ƿ�����ת����תʱΪ1��ֹͣʱΪ0
extern		 uint8_t DC_motor_Work_Flag;		 //�����жϲ�������Ƿ�����ת����תʱΪ1��ֹͣʱΪ0

extern      char* Lignt;
extern      char* Air;		 
extern      char* Curtain;		 
extern      char* Windows;		 

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
