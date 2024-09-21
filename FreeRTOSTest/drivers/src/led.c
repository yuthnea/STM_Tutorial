/*
 * led.c
 *
 *  Created on: Aug 28, 2024
 *      Author: Admin
 */

/**
 *    ||          ____  _ __
 * +------+      / __ )(_) /_______________ _____  ___
 * | 0xBC |     / __  / / __/ ___/ ___/ __ `/_  / / _ \
 * +------+    / /_/ / / /_/ /__/ /  / /_/ / / /_/  __/
 *  ||  ||    /_____/_/\__/\___/_/   \__,_/ /___/\___/
 *
 * Crazyflie control firmware
 *
 * Copyright (C) 2011-2012 Bitcraze AB
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, in version 3.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 * led.c - LED handing functions
 */
#include <stdbool.h>

#include "stm32f4xx_hal.h"


#include "led.h"


static bool isInit;


void ledInit()
{

	if (isInit)
		return;
	GPIO_InitTypeDef GPIO_InitStruct = { 0 };

	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOC_CLK_ENABLE();

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(LED_PORT, LED_PIN, GPIO_PIN_RESET);

	/*Configure GPIO pin : PtPin */
	GPIO_InitStruct.Pin = LED_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(LED_PORT, &GPIO_InitStruct);

	isInit = true;
}


void ledSet(bool value)
{
	if ( value == 0 ) HAL_GPIO_WritePin(LED_PORT, LED_PIN, 0);
	else HAL_GPIO_WritePin(LED_PORT, LED_PIN, 1);

}





