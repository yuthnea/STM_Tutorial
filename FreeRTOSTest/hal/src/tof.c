/*
 * tof.c
 *
 *  Created on: Sep 2, 2024
 *      Author: Admin
 */
#include <FreeRTOS.h>
#include <task.h>

#include "tof.h"
#include "px4flow.h"

#include "system.h"
#include "stabilizer_types.h"
#include "estimator.h"

#include "cf_math.h"
#include "usec_time.h"
#include <stdlib.h>

#include "led.h"

#define RANGE_OUTLIER_LIMIT 3000
// Measurement noise model
static const float expPointA = 2.5f;
static const float expStdA = 0.0025f; // STD at elevation expPointA [m]
static const float expPointB = 4.0f;
static const float expStdB = 0.2f;    // STD at elevation expPointB [m]
static float expCoeff;

static px4flowData_t px4;
int16_t dis;

int tofCounter;

void zRangerTask(void* arg)
{
	TickType_t lastWakeTime;

	systemWaitStart();
	lastWakeTime = xTaskGetTickCount();
	expCoeff = logf(expStdB / expStdA) / (expPointB - expPointA);
	while(1){
		ledSet(1);
		vTaskDelayUntil(&lastWakeTime, M2T(25));
		tofCounter++;
		px4flowUpdate(&px4);
		dis = px4.ground_distance;
		if (px4.ground_distance < RANGE_OUTLIER_LIMIT) {
			float distance = (float) px4.ground_distance * 0.001f; // Scale from [mm] to [m]
			float stdDev = expStdA * (1.0f + expf(expCoeff * (distance - expPointA)));
			tofMeasurement_t tofData;
			tofData.timestamp = xTaskGetTickCount();
			tofData.distance = distance;
			tofData.stdDev = stdDev;
			estimatorEnqueueTOF(&tofData);
		}
		ledSet(0);
		vTaskDelayUntil(&lastWakeTime, M2T(25));
	}
}

void tofInit()
{
	px4flowInit(&px4);

	if (px4flowTestConnection() == false){
		while(1);
	}

	  xTaskCreate(zRangerTask, ZRANGER2_TASK_NAME, ZRANGER2_TASK_STACKSIZE, NULL, ZRANGER2_TASK_PRI, NULL);

}






