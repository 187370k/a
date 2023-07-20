#include "esp8266.h"
#include "delay.h"
#include "tim.h"
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{	      
	   HAL_TIM_Base_Stop_IT(&htim4);
	//���жϷ�ʽ������DMAԭ����ͬ���ǽ�IT��ΪDMA����
    //HAL_UART_Transmit_IT(&huart1, buf, 3);	
     if (huart->Instance == USART1)                    /* ����Ǵ���1 */
    {
        if ((g_usart_rx_sta & 0x8000) == 0)             /* ����δ��� */
        {
            if (g_usart_rx_sta & 0x4000)                /* ���յ���0x0d�����س����� */
            {
                if (buf[0]!= 0x0a)             /* ���յ��Ĳ���0x0a�������ǻ��м��� */
                {
                    g_usart_rx_sta = 0;                 /* ���մ���,���¿�ʼ */
                }
                else                                    /* ���յ�����0x0a�������м��� */
                {
                    g_usart_rx_sta |= 0x8000;           /* ��������� */
                }
            }
            else                                        /* ��û�յ�0X0d�����س����� */
            {
                if (buf[0]== 0x0d)
                    g_usart_rx_sta |= 0x4000;
                else
                {
                    g_usart_rx_buf[g_usart_rx_sta & 0X3FFF] = buf[0];
                    g_usart_rx_sta++;

                    if (g_usart_rx_sta > (USART_REC_LEN - 1))
                    {
                        g_usart_rx_sta = 0;             /* �������ݴ���,���¿�ʼ���� */
                    }
                }
            }
        }
    }

	  HAL_UART_Receive_IT(&huart1,(uint8_t *)buf, 1);//�ٴδ�DMA���ܣ�������жϵķ�ʽ�����ٴδ��жϽ���
	  HAL_TIM_Base_Start_IT(&htim4);		
}
void Esp8266_Init()
{	
	 HAL_UART_Receive_IT(&huart1,(uint8_t *)buf, 1);//�ٴδ�DMA���ܣ�������жϵķ�ʽ�����ٴδ��жϽ���
	 //__HAL_UART_ENABLE_IT(&huart1,UART_IT_IDLE);//����UART�����жϼ�UART_IT_IDLE��Ҳ���Կ��������ж�
	 //�����󵱷���������С��3�ֽڵ����ݺ�ͻ��������жϣ�Ҳ����UART1_IRQHandler()����һ���жϴ�����

	   printf("AT+RST\r\n");//��λ
		 Delay_ms(2000);
	
		 printf("AT+CWMODE=1\r\n");//ģʽ
		 Delay_ms(2000);
	
//	 printf("AT\r\n");
//	 Delay_ms(1000);
//		 
//	 printf("AT+GMR\r\n");
//	 Delay_ms(1000);;//��ѯ�汾��

		 printf("AT+CWJAP=\"Redmi K50 kun\",\"11111111\"\r\n");
		 Delay_ms(2000);

		 printf("AT+CIPSNTPCFG=1,8,\"ntp1.aliyun.com\"\r\n");
		 Delay_ms(2000);

		 printf("AT+MQTTUSERCFG=0,1,\"NULL\",\"ESP8266&izskktWOdN1\",\"f6f9358eb1d6bfd345fdce0f585b640da87b5ca2782530e8bcc2fe0f05fb414c\",0,0,\"\"\r\n");
		 Delay_ms(2000);

		 printf("AT+MQTTCLIENTID=0,\"izskktWOdN1.ESP8266|securemode=2\\,signmethod=hmacsha256\\,timestamp=1688383891433|\"\r\n");
		 Delay_ms(2000);
     
		 printf("AT+MQTTCONN=0,\"iot-06z00h24667p6v3.mqtt.iothub.aliyuncs.com\",1883,1\r\n");
		 Delay_ms(2000);//�����������ӵ�������
     
  	 printf("AT+MQTTSUB=0,\"/izskktWOdN1/ESP8266/user/get\",1\r\n");
		 Delay_ms(2000);//����ָ��
		 
  	 printf("AT+MQTTPUB=0,\"/izskktWOdN1/ESP8266/user/update\",\"hello\",1,0\r\n");
		 Delay_ms(2000);//��������	
}
