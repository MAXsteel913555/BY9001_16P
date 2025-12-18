/*
 * key.c
 *
 *  Created on: Dec 17, 2025
 *      Author: LL
 */
#include "key.h"
#include "usart.h"


uint8_t myData1[7] = {0x7E, 0x05, 0x41, 0x00, 0x01, 0x45, 0xEF};  //曲目1
uint8_t myData2[7] = {0x7E, 0x05, 0x41, 0x00, 0x02, 0x46, 0xEF};  //曲目2
uint8_t myData3[7] = {0x7E, 0x05, 0x41, 0x00, 0x03, 0x47, 0xEF};  //曲目3

uint8_t myData4[5] = {0x7E, 0x03, 0x05, 0x06, 0xEF};//音量加
uint8_t myData5[5] = {0x7E, 0x03, 0x06, 0x05, 0xEF};//音量减


static uint32_t start_time = 0;//按下的时刻
static uint32_t last_send_time = 0;//上次发送的时刻

static uint8_t long_pressing_flag = 0;//长按标志位

uint8_t longPressData[5] = {0x7E, 0x03, 0x05, 0x06, 0xEF};  // 长按pa0 音量加

void Key_process()
{
	 uint32_t current_time = HAL_GetTick();//获取时间

	    //按键1(PA0)
	    if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == 0)  // 按键按下
	    {
	        HAL_Delay(20);  // 消抖

	        if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == 0)  // 确认按下
	        {
	            // 记录按下开始时间
	            start_time = current_time;//按键按下的时刻
	            last_send_time = current_time;  // 上次发送的时刻

	            long_pressing_flag = 0;  // 标志位为0

	            // 等待按键松开，同时检查长按
	            while (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == 0)
	            {
	                current_time = HAL_GetTick();
	                uint32_t press_duration = current_time - start_time;

	                // 如果按下超过1秒，进入长按状态
	                if (press_duration >= 1000)
	                {
	                	long_pressing_flag = 1;  // 标记为长按状态

	                    //判断按下时间是否大于1s
	                    if (current_time - last_send_time >= 1000)
	                    {
	                        // 发送长按数据
	                        HAL_UART_Transmit_IT(&huart1, longPressData, 5);
	                        last_send_time = current_time;  // 更新上次发送时间

	                        // 这里可以加个LED闪烁提示
	                        // HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
	                    }
	                }

	                HAL_Delay(10);  // 小延时，降低CPU使用
	            }

	            // 按键松开后的处理
	            if (!long_pressing_flag)  // 如果是短按
	            {
	                // 发送短按数据
	                HAL_UART_Transmit_IT(&huart1, myData1, 7);
	            }

	            // 重置状态
	            long_pressing_flag = 0;
	        }
	    }


	  //按键2pa2
	  if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_2) == 0)  // 按键按下
				  {
					  HAL_Delay(100);

					  // 使用中断发送数据
					  HAL_UART_Transmit_IT(&huart1, myData3, 7);


					  while (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_2) == 0);
				  }

				  HAL_Delay(10);

	  //按键4 pb12
	  if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_12) == 0)  // 按键按下
				  {
					  HAL_Delay(100);

					  // 使用中断发送数据
					  HAL_UART_Transmit_IT(&huart1, myData4, 5);


					  while (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_12) == 0);
				  }

				  HAL_Delay(10);

	  //按键5 pb13
	  if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_13) == 0)  // 按键按下
				  {
					  HAL_Delay(100);

					  // 使用中断发送数据
					  HAL_UART_Transmit_IT(&huart1, myData5, 5);


					  while (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_13) == 0);
				  }

				  HAL_Delay(10);
}
