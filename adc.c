/**
  ******************************************************************************
  * @file    adc.c
  * @brief   This file provides code for the configuration
  *          of the ADC instances.
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

/* Includes ------------------------------------------------------------------*/
#include "adc.h"

/* USER CODE BEGIN 0 */
#include "delay.h"
//#define CAL_PPM  10  // 校准环境中PPM值
//#define RL	     10  // RL阻值
//#define R0	     26  // R0阻值
uint16_t   MQ_2_Date;
uint16_t   Light_Date;
uint8_t   MQ_2_Flag=0;
uint8_t   Light_Flag;

/* USER CODE END 0 */

ADC_HandleTypeDef hadc1;

/* ADC1 init function */
void MX_ADC1_Init(void)
{

  /* USER CODE BEGIN ADC1_Init 0 */

  /* USER CODE END ADC1_Init 0 */

  ADC_MultiModeTypeDef multimode = {0};
  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC1_Init 1 */

  /* USER CODE END ADC1_Init 1 */
  /** Common config
  */
  hadc1.Instance = ADC1;
  hadc1.Init.ClockPrescaler = ADC_CLOCK_ASYNC_DIV2;
  hadc1.Init.Resolution = ADC_RESOLUTION_16B;
  hadc1.Init.ScanConvMode = ADC_SCAN_DISABLE;
  hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  hadc1.Init.LowPowerAutoWait = DISABLE;
  hadc1.Init.ContinuousConvMode = DISABLE;
  hadc1.Init.NbrOfConversion = 1;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc1.Init.ConversionDataManagement = ADC_CONVERSIONDATA_DR;
  hadc1.Init.Overrun = ADC_OVR_DATA_PRESERVED;
  hadc1.Init.LeftBitShift = ADC_LEFTBITSHIFT_NONE;
  hadc1.Init.OversamplingMode = DISABLE;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure the ADC multi-mode
  */
  multimode.Mode = ADC_MODE_INDEPENDENT;
  if (HAL_ADCEx_MultiModeConfigChannel(&hadc1, &multimode) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_3;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SamplingTime = ADC_SAMPLETIME_1CYCLE_5;
  sConfig.SingleDiff = ADC_SINGLE_ENDED;
  sConfig.OffsetNumber = ADC_OFFSET_NONE;
  sConfig.Offset = 0;
  sConfig.OffsetSignedSaturation = DISABLE;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC1_Init 2 */

  /* USER CODE END ADC1_Init 2 */

}

void HAL_ADC_MspInit(ADC_HandleTypeDef* adcHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};
  if(adcHandle->Instance==ADC1)
  {
  /* USER CODE BEGIN ADC1_MspInit 0 */

  /* USER CODE END ADC1_MspInit 0 */
  /** Initializes the peripherals clock
  */
    PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_ADC;
    PeriphClkInitStruct.PLL2.PLL2M = 32;
    PeriphClkInitStruct.PLL2.PLL2N = 180;
    PeriphClkInitStruct.PLL2.PLL2P = 5;
    PeriphClkInitStruct.PLL2.PLL2Q = 2;
    PeriphClkInitStruct.PLL2.PLL2R = 2;
    PeriphClkInitStruct.PLL2.PLL2RGE = RCC_PLL2VCIRANGE_1;
    PeriphClkInitStruct.PLL2.PLL2VCOSEL = RCC_PLL2VCOWIDE;
    PeriphClkInitStruct.PLL2.PLL2FRACN = 0;
    PeriphClkInitStruct.AdcClockSelection = RCC_ADCCLKSOURCE_PLL2;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
    {
      Error_Handler();
    }

    /* ADC1 clock enable */
    __HAL_RCC_ADC12_CLK_ENABLE();

    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();
    /**ADC1 GPIO Configuration
    PA6     ------> ADC1_INP3
    PC4     ------> ADC1_INP4
    */
    GPIO_InitStruct.Pin = GPIO_PIN_6;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_4;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /* USER CODE BEGIN ADC1_MspInit 1 */

  /* USER CODE END ADC1_MspInit 1 */
  }
}

void HAL_ADC_MspDeInit(ADC_HandleTypeDef* adcHandle)
{

  if(adcHandle->Instance==ADC1)
  {
  /* USER CODE BEGIN ADC1_MspDeInit 0 */

  /* USER CODE END ADC1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_ADC12_CLK_DISABLE();

    /**ADC1 GPIO Configuration
    PA6     ------> ADC1_INP3
    PC4     ------> ADC1_INP4
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_6);

    HAL_GPIO_DeInit(GPIOC, GPIO_PIN_4);

  /* USER CODE BEGIN ADC1_MspDeInit 1 */

  /* USER CODE END ADC1_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */
/* 获得ADC转换后的结果函数 */
//uint32_t adc_get_result(void)
//{
//    HAL_ADC_Start(&hadc1);
//    HAL_ADC_PollForConversion(&hadc1, 10);
//    return (uint16_t)HAL_ADC_GetValue(&hadc1);
//}
uint16_t Board_Get_ADCChannelValue(ADC_HandleTypeDef* hadc,uint32_t channel)
{
    ADC_ChannelConfTypeDef ADC_ChanConf;
    
    ADC_ChanConf.Channel = channel;
    ADC_ChanConf.Rank = ADC_REGULAR_RANK_1;
    ADC_ChanConf.SamplingTime = ADC_SAMPLETIME_1CYCLE_5;
    ADC_ChanConf.SingleDiff = ADC_SINGLE_ENDED;
    ADC_ChanConf.OffsetNumber = ADC_OFFSET_NONE;
    ADC_ChanConf.Offset = 0;

    HAL_ADC_ConfigChannel(hadc, &ADC_ChanConf);

    HAL_ADC_Start(hadc);
    HAL_ADC_PollForConversion(hadc,10); //轮询转换
	
    return (uint16_t)HAL_ADC_GetValue(hadc);
}

//uint32_t MQ2_ADC_Read(void)
//{                      
//	HAL_ADC_Start(&hadc1);/* 启动软件触发检测 */ 
//	HAL_ADC_PollForConversion(&hadc1, 10);	//等待转换结束
//	return (uint16_t)HAL_ADC_GetValue(&hadc1);

//}
uint16_t MQ_2_Average_Data(void)
{
   uint16_t temp_val=0;
//	if(MQ_2_Continue==)
	//{
		temp_val=Board_Get_ADCChannelValue(&hadc1,ADC_CHANNEL_3);	//读取ADC值
		return (uint16_t)temp_val;
	//}
}
//uint16_t Light_Average_Data(void)
//{
//	if(MQ_2_Continue==0)
//	{
//		uint16_t temp=0;
//		uint8_t t;
//		for(t=0;t<SMOG_READ_TIMES;t++)	//定义烟雾传感器读取次数,读这么多次,然后取平均值
//		{
//			 temp+=Board_Get_ADCChannelValue(&hadc1,ADC_CHANNEL_4);	//读取ADC值
//			 Delay_ms(5);
//		}
//		temp/=SMOG_READ_TIMES;//得到平均值
//		return (uint16_t)temp;//返回算出的ADC平均值
//	}
//}
//uint32_t Photoresistor_module_ADC_Read(void)
//{                      
//	HAL_ADC_Start(&hadc1);/* 启动软件触发检测 */ 
//	HAL_ADC_PollForConversion(&hadc1, 10);	//等待转换结束
//	return (uint16_t)HAL_ADC_GetValue(&hadc1);

//}

//float Smog_Get_Vol(void)
//{
//	uint16_t adc_value = 0;//这是从MQ-2传感器模块电压输出的ADC转换中获得的原始数字值，该值的范围为0到4095，将模拟电压表示为数字值
//	float voltage = 0;//MQ-7传感器模块的电压输出，与一氧化碳的浓度成正比
//	
//	adc_value = ADC1_Average_Data(ADC_CHANNEL_3);
//	Delay_ms(5);	
//  voltage  = (3.3/4096.0)*(adc_value);	
//	return voltage;
// }
// float Smog_GetPPM()
//{
//	float RS = (3.3f - Smog_Get_Vol()) / Smog_Get_Vol() * RL;
//	float ppm = 98.322f * pow(RS/R0, -1.458f);
//	return  ppm;
//}

/* USER CODE END 1 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
