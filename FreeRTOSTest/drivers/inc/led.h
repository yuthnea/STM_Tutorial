/*
 * led.h
 *
 *  Created on: Aug 28, 2024
 *      Author: Admin
 */

#ifndef INC_LED_H_
#define INC_LED_H_

#include <stdbool.h>

#define LED_PIN 	GPIO_PIN_13
#define LED_PORT	GPIOC

void ledInit();
void ledSet(bool value);

#endif /* INC_LED_H_ */
