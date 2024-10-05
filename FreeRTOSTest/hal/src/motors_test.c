/*
 * motors_test.c
 *
 *  Created on: Sep 27, 2024
 *      Author: AI FARM
 */
#include "motors_test.h"
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

//#include "dshot.h"

uint32_t motors_value = 0;
uint16_t my_motor_value[4] = {0, 0, 0, 0};
uint8_t next_state = 0;


static void motors_task_test(void *param) {
//	hal_dshot_init(DSHOT600);
//	vTaskDelay(100);
	//JH
	while(1){
		motors_value += 1;
		hal_dshot_write(my_motor_value);
		//JH only a round
//		next_state = 1;
		vTaskDelay(1);
	}
}
void motors_test(){
	xTaskCreate(motors_task_test, MOTORS_TASK_NAME_TEST, MOTORS_TASK_STACKSIZE_TEST, NULL, MOTORS_TASK_PRI_TEST, NULL);
}
