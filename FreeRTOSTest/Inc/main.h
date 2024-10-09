/*
 * main.h
 *
 *  Created on: Aug 29, 2024
 *      Author: Admin
 */

#ifndef MAIN_H_
#define MAIN_H_

#include "stm32f4xx_hal.h"

void Error_Handler(void);

#define GYRO_CS_Pin GPIO_PIN_4
#define GYRO_CS_GPIO_Port GPIOA
#define GYRO_INT_Pin GPIO_PIN_4
#define GYRO_INT_GPIO_Port GPIOC

#endif /* MAIN_H_ */
