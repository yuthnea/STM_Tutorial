/*
 * gpio_drv.c
 *
 *  Created on: Sep 27, 2024
 *      Author: AI FARM
 */

#include "gpio_drv.h"

void GPIO_Init(void){
	  /* GPIO Ports Clock Enable */
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	  __HAL_RCC_GPIOH_CLK_ENABLE();
	  __HAL_RCC_GPIOC_CLK_ENABLE();
	  __HAL_RCC_GPIOA_CLK_ENABLE();

	  HAL_GPIO_WritePin(GYRO_CS_GPIO_Port, GYRO_CS_Pin, GPIO_PIN_RESET);
	  /*Configure GPIO pin : GYRO_CS_Pin */
	  GPIO_InitStruct.Pin = GYRO_CS_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	  HAL_GPIO_Init(GYRO_CS_GPIO_Port, &GPIO_InitStruct);

	  /*Configure GPIO pin : GYRO_INT_Pin */
	  GPIO_InitStruct.Pin = GYRO_INT_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  HAL_GPIO_Init(GYRO_INT_GPIO_Port, &GPIO_InitStruct);



}
