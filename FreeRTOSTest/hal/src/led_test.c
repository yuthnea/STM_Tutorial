/*
 * led_test.c
 *
 *  Created on: Sep 20, 2024
 *      Author: AI FARM
 */

#include <led_test.h>
#include <FreeRTOS.h>
#include <task.h>

#include "stm32f4xx_hal.h"
#include "led.h" //when we use LED_PORT, LED_PIN

#include "system.h"
#include "stabilizer_types.h"
#include "estimator.h"

#include "cf_math.h"

#include "usec_time.h"
#include <stdlib.h>

uint32_t counter_led_task = 0;


static void led_task_test(void *param){
//	systemWaitStart();
//	uint64_t lastTime  = usecTimestamp();
// Open made code belove not work

	while(1){
		HAL_GPIO_TogglePin(LED_PORT, LED_PIN);
		vTaskDelay(100);
	}
}
void ledblink_test(){
	xTaskCreate(led_task_test, LED_TASK_NAME, LED_TASK_STACKSIZE, NULL, LED_TASK_PRI_TEST, NULL);
}


