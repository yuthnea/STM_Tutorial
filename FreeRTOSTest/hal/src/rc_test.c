/*
 * rc_test.c
 *
 *  Created on: Oct 7, 2024
 *      Author: AI FARM
 */
#include "rc_test.h"
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
#include "dragonll_ibus.h"

uint32_t rc_cournter = 0;
//uint16_t ibus_data[IBUS_USER_CHANNELS];

static void rc_task_test(void *param) {

	for (;;) {
		rc_cournter += 1;
//		hal_ibus_read(ibus_data);
		vTaskDelay(1);
	}

}

void rc_test(){
	xTaskCreate(rc_task_test, RC_TASK_NAME_TEST, RC_TASK_STACKSIZE, NULL, RC_TASK_PRI_TEST, NULL);
}

