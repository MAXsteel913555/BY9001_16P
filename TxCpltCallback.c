#include "TxCpltCallback.h"

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
	HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
}
