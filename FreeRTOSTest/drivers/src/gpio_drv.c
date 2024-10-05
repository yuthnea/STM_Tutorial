/*
 * gpio_drv.c
 *
 *  Created on: Sep 27, 2024
 *      Author: AI FARM
 */

#include "gpio_drv.h"

void GPIO_Init(void){
	  /* GPIO Ports Clock Enable */
	  __HAL_RCC_GPIOH_CLK_ENABLE();
	  __HAL_RCC_GPIOC_CLK_ENABLE();
	  __HAL_RCC_GPIOA_CLK_ENABLE();
}
