/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "dma.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "string.h"
#include "stdio.h"
#include "delay.h"
#include "Stepper.h"
#include "esp8266.h"
#include "DC motor.h"
#include "OLED.h"
#include "DHT11.h"
#include "led.h"
#include "servos.h"
#include "buzzer.h"
//int jiaodu;
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
int fputc(int ch, FILE *f){
 uint8_t temp[1] = {ch};
 HAL_UART_Transmit(&huart1, temp, 1, 0xffff);
return ch;
}
int fgetc(FILE * f)
{
  uint8_t ch = 0;
  HAL_UART_Receive(&huart1,&ch, 1, 0xffff);
  return ch;
}
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
//uint8_t u_buf[256];//
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
     uint8_t WS_Flag=1;//��������ģʽ��־λ
     uint8_t LS_Flag=1;//�ƹ�����ģʽ��־λ
     uint8_t CS_Flag=1;//��������ģʽ��־λ
     uint8_t FS_Flag=1;//��������ģʽ��־λ
		 
     uint8_t Show_Flag=0 ; //��������λ����������
		 
		 uint8_t Curtain_Flag=0; //�����жϴ��������	    0Ϊ�رգ�1Ϊ�뿪��2Ϊȫ��
		 uint8_t Fan_Flag=0;     // �����жϷ��ȵ������ 	0Ϊ�رգ�1Ϊ1����2Ϊ2����3Ϊ3��
		 uint8_t Lignt_Flag=0;    //�����жϼ���������	     0Ϊ�أ�1Ϊ����2Ϊ�ϰ���3Ϊ����
   	 uint8_t Windows_Flag=0;  //�����жϴ��������	   0Ϊ�أ�1Ϊ�뿪��2Ϊȫ��
		 uint8_t Curtain_Work_Flag=0;		 //�����жϲ�������Ƿ�����ת����תʱΪ1��ֹͣʱΪ0
		 uint8_t DC_motor_Work_Flag=0;		 //�����жϲ�������Ƿ�����ת����תʱΪ1��ֹͣʱΪ0
		 
     char* Lignt;
     char* Air;
     char* Curtain;
     char* Windows;		 
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
	MX_DMA_Init();
  MX_USART1_UART_Init();
  MX_TIM2_Init();
  MX_ADC1_Init();
  MX_TIM3_Init();
  MX_TIM4_Init();
  MX_TIM5_Init();
  MX_TIM1_Init();
  /* USER CODE BEGIN 2 */
  //*************	MX_DMA_Init()����Ҫ��MX_USART1_UART_Init()����ǰ�߷��߲�����*************
   HAL_TIM_Base_Stop_IT(&htim4);
	 Stepper_GPIOInit();
	 DC_motor_GPIO_Init();
	 Esp8266_Init();
	 Buzzer_Init();
	 DHT11_Init();
	 OLED_Init();
	 HAL_TIM_Base_Start_IT(&htim4);
	// Servos_Control(63);
 //**********ÿ����cubemx�������ļ������Ҫ��printf��scanf��Ҫ��ħ������TarGet�ﹴѡuse microlib************//  
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {	  
	 	//**********ÿ����cubemx�������ļ������Ҫ��printf��scanf��Ҫ��ħ������TarGet�ﹴѡuse microlib************
			OLED_Show();
 			if(strstr((const char*)g_usart_rx_buf,"WSON"))
		 {     
			 	   HAL_GPIO_WritePin(GPIOC,GPIO_PIN_1,GPIO_PIN_RESET);
					 WS_Flag=1;
		 }
		 	if(strstr((const char*)g_usart_rx_buf,"LSON"))
		 {		 HAL_GPIO_WritePin(GPIOC,GPIO_PIN_0,GPIO_PIN_SET);
					 LS_Flag=1;				 
		 }
			if(strstr((const char*)g_usart_rx_buf,"CSON"))
		 { 
			 		HAL_GPIO_WritePin(GPIOC,GPIO_PIN_1,GPIO_PIN_SET);
					 CS_Flag=1;					
	   }
	    if(strstr((const char*)g_usart_rx_buf,"FSON"))
		 {			
					 FS_Flag=1;
	   }
		  if(WS_Flag==1)
			{		
							/*����ش�*/
					if(MQ_2_Flag==0)//����Ȼ����й¶Ϊǰ��
					{				
							if(Hum_Flag==1)
							{	
							 /*�������ش�*/
								Servos_Control(160);
                 Windows_Flag=0;								
							}
								if(Hum_Flag==0)
							{	
							 /*��߲����꿪��*/
								Servos_Control(63);
                Windows_Flag=2;								
							}
					}
						if(MQ_2_Flag==1)/*��Ȼ��й¶����*/
						{	
							 	Servos_Control(63);
                 Windows_Flag=2;							
						}							
			}
		 if(LS_Flag==1)
		 {	
			 		 if(Light_Flag==1)
					 {							 
						 LED_Brightness_Contorl(1300);
              Lignt_Flag=2;						 
					 }
					 if(Light_Flag==2)
					 {							 
						  LED_Brightness_Contorl(2000);
              Lignt_Flag=3;						 
						 
					 }
					 if(Light_Flag==0)
					 {	
             LED_Brightness_Contorl(0);
             Lignt_Flag=0;						 
						 
					 }

		 }
		 if(CS_Flag==1)
		 {	
					 /*��Ȼ��й¶������ȫ��*/
					if(MQ_2_Flag==1)
					{	
						if(Curtain_Flag==0)//�жϴ���״̬
						{
							if(Curtain_Work_Flag==0)
							{
								 Stepper_RotateByLoop(Forward, 2, 2);
								 Curtain_Work_Flag=1;
								 Curtain_Flag=2;//�����жϴ����򿪳̶�
							}
						}
						if(Curtain_Flag==1)
						{  
							if(Curtain_Work_Flag==0)
							{
							 Stepper_RotateByLoop(Forward, 1, 2);
							 Curtain_Flag=2;//�����жϴ����򿪳̶�
							 Curtain_Work_Flag=1;
              }
						}							            				
					}
					 /*���߽ϰ���һ�봰��*/
					if(MQ_2_Flag==0)
					{
						if(Light_Flag==1)
						{	
									if(Curtain_Flag==0)
								{  
									if(Curtain_Work_Flag==0)
									{
										 Stepper_RotateByLoop(Forward, 1, 2);
										 Curtain_Flag=1;//�����жϴ����򿪳̶�
										 Curtain_Work_Flag=1;
									}
								}	
									if(Curtain_Flag==2)
								{ 
									if( Curtain_Work_Flag==0)
									{
										 Stepper_RotateByLoop(Reversal, 1, 2);
										 Curtain_Flag=1;//�����жϴ����򿪳̶�
										 Curtain_Work_Flag=1;
									}

								}	

						}
					if(Light_Flag==2)
					{	
							if(Curtain_Flag==0)
						{  
							if(Curtain_Work_Flag==0)
							{
								 Stepper_RotateByLoop(Forward, 2, 2);
								 Curtain_Flag=2;//�����жϴ����򿪳̶�
								 Curtain_Work_Flag=1;
								
							}
						}	
							if(Curtain_Flag==1)
						{  
							if( Curtain_Work_Flag==0)
							{
								 Stepper_RotateByLoop(Forward, 1, 2);
								 Curtain_Flag=2;//�����жϴ����򿪳̶�
								 Curtain_Work_Flag=1;
							}
						}	
					}	
					 /*���߳���رմ���*/
					if(Light_Flag==0)
					{	
							if(Curtain_Flag==1)
						{ 
							if(Curtain_Work_Flag==0)
							{
								 Stepper_RotateByLoop(Reversal, 1, 2);
								 Curtain_Flag=0;//�����жϴ����򿪳̶�
								 Curtain_Work_Flag=1;
							}

						}	
							if(Curtain_Flag==2)
						{  
							if(Curtain_Work_Flag==0)
							{
									Stepper_RotateByLoop(Reversal, 2, 2); //���������ת�������ر�
									Curtain_Flag=0;//�����жϴ����򿪳̶�
									Curtain_Work_Flag=1;
							}
						}							
					}	
						
				}
					 /*���ߺܰ���ȫ������*/
 					
		 }
		 if(FS_Flag==1)
		 {	
					 if(MQ_2_Flag==1)//ú��й¶������
					{	
						 DC_motor_Contorl(1800);//���õ��ת��0~1999���͵�600���е�1300	���ߵ�1800
              Fan_Flag=3;
             DC_motor_Work_Flag=1;						
					}					
					if(MQ_2_Flag==0)
					{
							 DC_motor_Contorl(0);//���õ��ת��0~1999���͵�600���е�1300	���ߵ�1800
							 Fan_Flag=0;
               DC_motor_Work_Flag=0;						
						
							 if(Tem_Flag==1)
						{	
								DC_motor_Contorl(1300);//���õ��ת��0~1999���͵�600���е�1300	���ߵ�1800
								Fan_Flag=2;						
                DC_motor_Work_Flag=1;						
							
						}
							 if(Tem_Flag==2)
							{	
								 DC_motor_Contorl(1800);//���õ��ת��0~1999���͵�600���е�1300	���ߵ�1800
								 Fan_Flag=3;
                 DC_motor_Work_Flag=1;														
							}			 			 		 
				}
		 }
		   if(strstr((const char*)g_usart_rx_buf,"WSOFF"))
			 {
				   	WS_Flag=0;
			 }
		 	 if(strstr((const char*)g_usart_rx_buf,"LSOFF"))
			 {
				   	LS_Flag=0;

			 }
		 	 if(strstr((const char*)g_usart_rx_buf,"CSOFF"))
			{
						CS_Flag=0;
			}
		 	if(strstr((const char*)g_usart_rx_buf, "FSOFF"))
			{					
						FS_Flag=0;
			}			 
			 if(WS_Flag==0)
			 {	
				  if(strstr((const char*)g_usart_rx_buf,"WindowsOpenBig"))
				  {	
					  /*�����������ȫ��*/
							 	Servos_Control(63);
                 Windows_Flag=2;						
						  											
					}
					if(strstr((const char*)g_usart_rx_buf,"WindowsOpenHalf"))
				  {	
					  /*�����������һ��*/
							Servos_Control(100);
              Windows_Flag=1;						
						  											
					}
				  if(strstr((const char*)g_usart_rx_buf,"WindowsClose"))
				  {	
					  /*����������ر�*/
							 	Servos_Control(163);
                Windows_Flag=0;						
						  											
					}				 				 
			 }
			 if(LS_Flag==0)
			 {	
				  if(strstr((const char*)g_usart_rx_buf,"LightMiddle"))
				  {	
					  /*���ƹ��Ϊ����*/
						LED_Brightness_Contorl(1322);
             Lignt_Flag=2;						 
							
					}
					if(strstr((const char*)g_usart_rx_buf,"LightBig"))
				  {	
					  /*���ƹ��Ϊ����*/
						LED_Brightness_Contorl(1999);
            Lignt_Flag=3;						 
						
					}
				  if(strstr((const char*)g_usart_rx_buf,"LightSmall"))
				  {	
					  /*���ƹ��Ϊ����*/
						LED_Brightness_Contorl(666);
             Lignt_Flag=1;						 
						
					}
					if(strstr((const char*)g_usart_rx_buf,"LightClose"))
				  {	
					  /*���ƹ�ر�*/
						LED_Brightness_Contorl(0);
            Lignt_Flag=0;						 
						
					}
				 
			 }
				if(CS_Flag==0)
				{	
				  if(strstr((const char*)g_usart_rx_buf,"CurtainMiddle"))
				  {	
					  /*�������뿪*/
							if(Curtain_Flag==0)
						{
							 Stepper_RotateByLoop(Forward, 1, 2);
							 Curtain_Flag=1;//�����жϴ����򿪳̶�
						}	
							if(Curtain_Flag==2)
						{
							 Stepper_RotateByLoop(Reversal, 1, 2);
							 Curtain_Flag=1;//�����жϴ����򿪳̶�
						}	
						
					}
					if(strstr((const char*)g_usart_rx_buf,"CurtainBig"))
				  {	
					  /*������ȫ��*/
						if(Curtain_Flag==0)//�жϴ���״̬
						{
							 Stepper_RotateByLoop(Forward, 2, 2);
							 Curtain_Flag=2;//�����жϴ����򿪳̶�
						}
						if(Curtain_Flag==1)
						{
							 Stepper_RotateByLoop(Forward, 1, 2);
							 Curtain_Flag=2;//�����жϴ����򿪳̶�
						}							            				
						
					}
					if(strstr((const char*)g_usart_rx_buf,"CurtainClose"))
				  {	
					  /*�������ر�*/
							if(Curtain_Flag==1)
						{
							 Stepper_RotateByLoop(Reversal, 1, 2);
							 Curtain_Flag=0;//�����жϴ����򿪳̶�
						}	
							if(Curtain_Flag==2)
						{
						  Stepper_RotateByLoop(Reversal, 2, 2); //���������ת�������ر�
              Curtain_Flag=0;//�����жϴ����򿪳̶�             												
						}							
					}
					
				}
        if(FS_Flag==0)
				{	
				  if(strstr((const char*)g_usart_rx_buf,"FanMiddle"))
				  {	
					  /*�����е�*/
						DC_motor_Contorl(1322);
             Fan_Flag=2;						
						
					}
					if(strstr((const char*)g_usart_rx_buf,"FanBig"))
				  {	
					  /*���ȸߵ�*/
						DC_motor_Contorl(1800);
             Fan_Flag=3;						
						
					}
					if(strstr((const char*)g_usart_rx_buf,"FanSmall"))
				  {	
					  /*���ȵ͵�*/
						DC_motor_Contorl(600);
             Fan_Flag=1;						
						
					}

					if(strstr((const char*)g_usart_rx_buf,"FanClose"))
				  {	
					  /*���ȹر�*/
						DC_motor_Contorl(0);
             Fan_Flag=0;												
					}
					
				}
		   if(strstr((const char*)g_usart_rx_buf,"SHOW"))//������ʪ�ȣ�����������������������ȵ����������봰�������
			 {
		  	    HAL_GPIO_WritePin(GPIOC,GPIO_PIN_1,GPIO_PIN_SET);				 
				   	Show_Flag=1;
			 }
				
		   if (g_usart_rx_sta & 0x8000)  //����������ݱ�־λΪ�´ν��ܰ�������Ϣ��׼��
     {
					 g_usart_rx_sta = 0;					
     }
		 	 if(Light_Flag==0)
		{
			    Lignt="normal";
		}

		 if(Light_Flag==1)
		{	
			    Lignt="poor";
		}

	  if(Light_Flag==2)
		{	
			    Lignt="bad";
		}
		
		 	if(Curtain_Flag==0)
		{
			    Curtain="off";
		}
		 	if(Curtain_Flag==1)
		{
			    Curtain="half";
		}
		 	if(Curtain_Flag==2)
		{
			    Curtain="full";
		}
		
		 	if(Windows_Flag==0)
		{
			    Windows="off";
		}
		 	if(Windows_Flag==1)
		{
			    Windows="half";
		}
		 	if(Windows_Flag==2)
		{
			   Windows="full";
		}
     if(MQ_2_Flag==1)
	 {			
		  Air="dinnerous";		
	 }
     if(MQ_2_Flag==0)
	 {			
		   Air="normal";		
	 }
       if(MQ_2_Flag==1)/*��Ȼ��й¶����*/
			{	
						Servos_Control(63);
            Windows_Flag=2;	
            DC_motor_Contorl(1800);
				    Fan_Flag=3;						
			}							

    		 
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	}
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Supply configuration update enable
  */
  HAL_PWREx_ConfigSupply(PWR_LDO_SUPPLY);
  /** Configure the main internal regulator output voltage
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE0);

  while(!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY)) {}
  /** Macro to configure the PLL clock source
  */
  __HAL_RCC_PLL_PLLSOURCE_CONFIG(RCC_PLLSOURCE_HSI);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_DIV1;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 35;
  RCC_OscInitStruct.PLL.PLLP = 2;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
  RCC_OscInitStruct.PLL.PLLRGE = RCC_PLL1VCIRANGE_3;
  RCC_OscInitStruct.PLL.PLLVCOSEL = RCC_PLL1VCOWIDE;
  RCC_OscInitStruct.PLL.PLLFRACN = 0;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2
                              |RCC_CLOCKTYPE_D3PCLK1|RCC_CLOCKTYPE_D1PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.SYSCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB3CLKDivider = RCC_APB3_DIV2;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_APB1_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_APB2_DIV2;
  RCC_ClkInitStruct.APB4CLKDivider = RCC_APB4_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_7) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
