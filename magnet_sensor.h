#ifndef __MAGNET_SENSOR_H
#define __MAGNET_SENSOR_H

#include "main.h"

/* 引脚定义 */
#define MAGNET_GPIO_PORT      GPIOA
#define MAGNET_GPIO_PIN       GPIO_PIN_1


/* 函数声明 */
void MagnetSensor_Init(void);
void MagnetSensor_Update(void);
uint8_t MagnetSensor_GetState(void);
void MagnetSensor_Process(void);

#endif /* __MAGNET_SENSOR_H */
