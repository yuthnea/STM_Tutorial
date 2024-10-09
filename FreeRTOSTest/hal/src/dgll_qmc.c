/*
 * dgll_qmc.c
 *
 *  Created on: Oct 9, 2024
 *      Author: AI FARM
 */
#include "dgll_qmc.h"
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

//uint32_t qmc_flage = 0;
qmc_typedef qmc;

static void qmc_task_test(void *param){
//	qmc_flage = 1;
	qmc5883p_init();

	for(;;){
		qmc5883p_read(&qmc);
		vTaskDelay(10);
//		qmc_flage = 1;
	}
}

void qmc_test(){
	xTaskCreate(qmc_task_test, QMC_TASK_NAME_TEST, QMC_TASK_STACKSIZE, NULL, QMC_TASK_PRI_TEST, NULL);
}
