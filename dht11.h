#ifndef __DHT11_H__
#define __DHT11_H__

#include "main.h"

#define DHT11_DQ_OUT_HIGH HAL_GPIO_WritePin(GPIOC,GPIO_PIN_11,GPIO_PIN_SET)
#define DHT11_DQ_OUT_LOW 	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_11,GPIO_PIN_RESET)

#define DHT11_DQ_IN	 HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_11)

//IO��������
void DS18B20_IO_IN(void);
void DS18B20_IO_OUT(void);

		
uint8_t DHT11_Init(void);//��ʼ��DHT11
uint8_t DHT11_Read_Data(uint16_t *temp,uint16_t *humi);//��ȡ��ʪ��
uint8_t DHT11_Read_Byte(void);//����һ���ֽ�
uint8_t DHT11_Read_Bit(void);//����һ��λ
uint8_t DHT11_Check(void);//����Ƿ����DHT11
void DHT11_Rst(void);//��λDHT11  
extern   uint16_t temperature;
extern	 uint16_t humidity;
extern   uint8_t  Tem_Flag;
extern   uint8_t  Hum_Flag;
#endif