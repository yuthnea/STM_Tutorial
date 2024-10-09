/*
 * dgll_imu.c
 *
 *  Created on: Oct 9, 2024
 *      Author: AI FARM
 */
#include "dgll_imu.h"
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

MPU6500_IMU imu;

//uint16_t imu_flage = 0;

static void imu_task_test(void *param){
//	imu_flage = 1;
	//JH
	if(MPU6500_Init(&imu) == 0){
//		imu_flage = 1;
		//NJH
		for(;;);
	}
//	imu_flage = 1;
	//JH
	for(;;){
		MPU6500_ReadAcc(&imu);
		MPU6500_ReadGyr(&imu);
		vTaskDelay(10);
	}
}

void imu_test(){
	xTaskCreate(imu_task_test, IMU_TASK_NAME_TEST, IMU_TASK_STACKSIZE, NULL, IMU_TASK_PRI_TEST, NULL);
}

