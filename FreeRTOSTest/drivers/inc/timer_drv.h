/*
 * timer_drv.h
 *
 *  Created on: Sep 18, 2024
 *      Author: AI FARM
 */

#ifndef INC_TIMER_DRV_H_
#define INC_TIMER_DRV_H_
#include "main.h"
//#include "stm32f4xx.h"
//#include "stm32f4xx_hal_tim.h"


extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;

void TIM3_Init(void);
void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);
void TIM3_DMA_Init(void);

void TIM4_Init(void);

#endif /* INC_TIMER_DRV_H_ */
