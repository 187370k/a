#ifndef __DHT11_H__
#define __DHT11_H__

#include "main.h"

#define DHT11_DQ_OUT_HIGH HAL_GPIO_WritePin(GPIOC,GPIO_PIN_11,GPIO_PIN_SET)
#define DHT11_DQ_OUT_LOW 	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_11,GPIO_PIN_RESET)

#define DHT11_DQ_IN	 HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_11)

//IO方向设置
void DS18B20_IO_IN(void);
void DS18B20_IO_OUT(void);

		
uint8_t DHT11_Init(void);//初始化DHT11
uint8_t DHT11_Read_Data(uint16_t *temp,uint16_t *humi);//读取温湿度
uint8_t DHT11_Read_Byte(void);//读出一个字节
uint8_t DHT11_Read_Bit(void);//读出一个位
uint8_t DHT11_Check(void);//检测是否存在DHT11
void DHT11_Rst(void);//复位DHT11  
extern   uint16_t temperature;
extern	 uint16_t humidity;
extern   uint8_t  Tem_Flag;
extern   uint8_t  Hum_Flag;
#endif
