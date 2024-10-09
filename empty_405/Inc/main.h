/*
 * main.h
 *
 *  Created on: Sep 28, 2024
 *      Author: AI FARM
 */

#ifndef MAIN_H_
#define MAIN_H_
//#include "stm32f405xx.h"
#include "stm32f4xx_hal.h"
//#include "stm32f4xx_hal_rcc.h"


extern TIM_HandleTypeDef htim3;

extern TIM_HandleTypeDef htim4;

extern UART_HandleTypeDef huart1;

void Error_Handler(void);


#define GYRO_CS_Pin GPIO_PIN_4
#define GYRO_CS_GPIO_Port GPIOA
#define GYRO_INT_Pin GPIO_PIN_4
#define GYRO_INT_GPIO_Port GPIOC


#endif /* MAIN_H_ */
