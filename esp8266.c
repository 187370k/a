#include "esp8266.h"
#include "delay.h"
#include "tim.h"
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{	      
	   HAL_TIM_Base_Stop_IT(&htim4);
	//用中断方式接受与DMA原理相同就是将IT改为DMA即可
    //HAL_UART_Transmit_IT(&huart1, buf, 3);	
     if (huart->Instance == USART1)                    /* 如果是串口1 */
    {
        if ((g_usart_rx_sta & 0x8000) == 0)             /* 接收未完成 */
        {
            if (g_usart_rx_sta & 0x4000)                /* 接收到了0x0d（即回车键） */
            {
                if (buf[0]!= 0x0a)             /* 接收到的不是0x0a（即不是换行键） */
                {
                    g_usart_rx_sta = 0;                 /* 接收错误,重新开始 */
                }
                else                                    /* 接收到的是0x0a（即换行键） */
                {
                    g_usart_rx_sta |= 0x8000;           /* 接收完成了 */
                }
            }
            else                                        /* 还没收到0X0d（即回车键） */
            {
                if (buf[0]== 0x0d)
                    g_usart_rx_sta |= 0x4000;
                else
                {
                    g_usart_rx_buf[g_usart_rx_sta & 0X3FFF] = buf[0];
                    g_usart_rx_sta++;

                    if (g_usart_rx_sta > (USART_REC_LEN - 1))
                    {
                        g_usart_rx_sta = 0;             /* 接收数据错误,重新开始接收 */
                    }
                }
            }
        }
    }

	  HAL_UART_Receive_IT(&huart1,(uint8_t *)buf, 1);//再次打开DMA接受，如果是中断的方式就是再次打开中断接受
	  HAL_TIM_Base_Start_IT(&htim4);		
}
void Esp8266_Init()
{	
	 HAL_UART_Receive_IT(&huart1,(uint8_t *)buf, 1);//再次打开DMA接受，如果是中断的方式就是再次打开中断接受
	 //__HAL_UART_ENABLE_IT(&huart1,UART_IT_IDLE);//开启UART空闲中断即UART_IT_IDLE，也可以开启其他中断
	 //开启后当发送完任意小于3字节的数据后就会进入空闲中断，也就是UART1_IRQHandler()串口一的中断处理函数

	   printf("AT+RST\r\n");//复位
		 Delay_ms(2000);
	
		 printf("AT+CWMODE=1\r\n");//模式
		 Delay_ms(2000);
	
//	 printf("AT\r\n");
//	 Delay_ms(1000);
//		 
//	 printf("AT+GMR\r\n");
//	 Delay_ms(1000);;//查询版本号

		 printf("AT+CWJAP=\"Redmi K50 kun\",\"11111111\"\r\n");
		 Delay_ms(2000);

		 printf("AT+CIPSNTPCFG=1,8,\"ntp1.aliyun.com\"\r\n");
		 Delay_ms(2000);

		 printf("AT+MQTTUSERCFG=0,1,\"NULL\",\"ESP8266&izskktWOdN1\",\"f6f9358eb1d6bfd345fdce0f585b640da87b5ca2782530e8bcc2fe0f05fb414c\",0,0,\"\"\r\n");
		 Delay_ms(2000);

		 printf("AT+MQTTCLIENTID=0,\"izskktWOdN1.ESP8266|securemode=2\\,signmethod=hmacsha256\\,timestamp=1688383891433|\"\r\n");
		 Delay_ms(2000);
     
		 printf("AT+MQTTCONN=0,\"iot-06z00h24667p6v3.mqtt.iothub.aliyuncs.com\",1883,1\r\n");
		 Delay_ms(2000);//到这里是连接到阿里云
     
  	 printf("AT+MQTTSUB=0,\"/izskktWOdN1/ESP8266/user/get\",1\r\n");
		 Delay_ms(2000);//订阅指令
		 
  	 printf("AT+MQTTPUB=0,\"/izskktWOdN1/ESP8266/user/update\",\"hello\",1,0\r\n");
		 Delay_ms(2000);//发送数据	
}
