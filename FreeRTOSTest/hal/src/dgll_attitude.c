/*
 * dgll_attitude.c
 *
 *  Created on: Oct 14, 2024
 *      Author: AI FARM
 */
#include "dgll_attitude.h"
#include "dgll_imu.h"
#include "dgll_qmc.h"
#include "MadgwickAHRS.h"

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

uint8_t att_flage = 0;
typedef struct {
	float gyro_x;
	float gyro_y;
	float gyro_z;
	float acc_x;
	float acc_y;
	float acc_z;
} Scale_senor;
typedef struct{
	float roll;
	float pitch;
	float yaw;
}angle_;

Scale_senor scale_;
angle_ angle__;

extern MPU6500_IMU imu;
extern qmc_typedef qmc;




static void attitude_task_test(void *param){


//	att_flage = 1;
	for(;;){
//		att_flage += 1;

		/*
		 * Scale for IMU
		 */

		scale_.acc_x = imu.acc[0] * 0.00239501953125f;
		scale_.acc_y = imu.acc[1] * 0.00239501953125f;
		scale_.acc_z = imu.acc[2] * 0.00239501953125f;

		scale_.gyro_x = imu.gyr[0] * 0.00026632423f;
		scale_.gyro_y = imu.gyr[1] * 0.00026632423f;
		scale_.gyro_z = imu.gyr[2] * 0.00026632423f;

		MadgwickAHRSupdate(scale_.gyro_x, scale_.gyro_y, scale_.gyro_z,
						scale_.acc_x, scale_.acc_y, scale_.acc_y,
						qmc.qmc_x, qmc.qmc_y,qmc.qmc_z);
		angle__.roll = asin(2 * ((q0 * q2) - (q1 * q3)))* 57.29577951f;
		angle__.pitch = -atan2( 2 * ( (q0 * q1) + (q2 * q3)), 1 - (2 * ((q1 * q1) + (q2 * q2)))) * 57.29577951f; //degrees
		angle__.yaw = atan2(2 * ((q0 * q3) + (q1 * q2)), 1 - (2 * ((q2 * q2) + (q3 * q3)))) * 57.29577951f; //degrees
		vTaskDelay(1);
	}
}


void attitude_test(){
	xTaskCreate(attitude_task_test, ATT_TASK_NAME_TEST, ATT_TASK_STACKSIZE, NULL, ATT_TASK_PRI_TEST, NULL);
}

