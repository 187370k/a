#include "Delay.h"
#include "Stepper.h"

uint8_t STEP;	// ���ڴ洢��������߹����������

/**
  * @brief  ������������GPIO��ʼ������
  * @param  ��
  * @retval ��
  */
void Stepper_GPIOInit(void)
{
  Stepper_CLK;
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;	// �������
	GPIO_InitStruct.Pin = Stepper_LA | Stepper_LB | Stepper_LC | Stepper_LD;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;;
	HAL_GPIO_Init(Stepper_Output_GPIO,&GPIO_InitStruct);
  HAL_GPIO_WritePin(Stepper_Output_GPIO, Stepper_LA | Stepper_LB | Stepper_LC | Stepper_LD, GPIO_PIN_RESET);

}

/**
  * @brief  ���ͣת����
  * @param  ��
  * @retval ��
  */
void Stepper_Stop(void)
{
	HAL_GPIO_WritePin(Stepper_Output_GPIO, Stepper_LA | Stepper_LB | Stepper_LC | Stepper_LD, GPIO_PIN_RESET);
}

/**
  * @brief  4�ĵ���������������
  * @param  StepNum 	������ţ�0~3��ӦA~D
  * @param	Delay_Time_xms 		ÿ����ת����ʱʱ��x ms�����ڿ��Ʋ�������ٶȣ�һ������ڵ���2��
  * @retval ��
  */
void Stepper_SingleStep(uint8_t StepNum, uint16_t Delay_Time_xms)
{
	switch(StepNum)
	{
		case 0:		// A
			HAL_GPIO_WritePin(Stepper_Output_GPIO, Stepper_LA,GPIO_PIN_SET);
			HAL_GPIO_WritePin(Stepper_Output_GPIO, Stepper_LB | Stepper_LC | Stepper_LD,GPIO_PIN_RESET);
		break;
		case 1:		// B
			HAL_GPIO_WritePin(Stepper_Output_GPIO, Stepper_LB,GPIO_PIN_SET);
			HAL_GPIO_WritePin(Stepper_Output_GPIO, Stepper_LA | Stepper_LC | Stepper_LD,GPIO_PIN_RESET);
		break;			
		case 2:		// C
			HAL_GPIO_WritePin(Stepper_Output_GPIO, Stepper_LC,GPIO_PIN_SET);
			HAL_GPIO_WritePin(Stepper_Output_GPIO, Stepper_LA | Stepper_LB | Stepper_LD,GPIO_PIN_RESET);
		break;
		case 3:		// D
			HAL_GPIO_WritePin(Stepper_Output_GPIO, Stepper_LD,GPIO_PIN_SET);
			HAL_GPIO_WritePin(Stepper_Output_GPIO, Stepper_LA | Stepper_LB | Stepper_LC,GPIO_PIN_RESET);
		break;
		default: break;
	}
	  Delay_ms(Delay_Time_xms);	// ��ʱ�����Ƶ���ٶ�
	  Stepper_Stop();				// �ϵ磬��ֹ�������
}

/**
  * @brief  �������������ת
  * @param  direction		�����ת���򣬿�����Forward������������Reversal����ת��
  * @param	step			���ת���Ĳ���
  * @param	Delay_Time_xms	ÿ����ת����ʱʱ��x ms�����ڿ��Ʋ�������ٶȣ�һ������ڵ���2��
  * @retval ��
  */
void Stepper_RotateByStep(RotDirection direction, uint32_t step, uint16_t Delay_Time_xms)
{
	for (uint32_t i = 0; i < step; i ++)
	{
		if (direction == Forward)	// �������
		{
			STEP ++;
			if (STEP > 3)
			{
				STEP = 0;
			}
		}
		else if (direction == Reversal)	// �����ת
		{
			if (STEP < 1)
			{
				STEP = 4;
			}
			STEP --;
		}
		Stepper_SingleStep(STEP, Delay_Time_xms);
	}
}

/**
  * @brief  �������������Ȧ��ת
  * @param  direction		�����ת���򣬿�����Forward������������Reversal����ת��
  * @param  Loop			�����ת��Ȧ��
  * @param  Delay_Time_xms	ÿ����ת����ʱʱ��x ms�����ڿ��Ʋ�������ٶȣ�һ������ڵ���2��
  * @retval 
  */
void Stepper_RotateByLoop(RotDirection direction, uint32_t Loop, uint16_t Delay_Time_xms)
{
	Stepper_RotateByStep(direction, Loop * 2048, Delay_Time_xms+1);
}

