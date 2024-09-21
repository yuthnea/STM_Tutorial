/*
 * flow_tof.c
 *
 *  Created on: Sep 2, 2024
 *      Author: Admin
 */

#include <flow.h>
#include <FreeRTOS.h>
#include <task.h>

#include "px4flow.h"

#include "system.h"
#include "stabilizer_types.h"
#include "estimator.h"

#include "cf_math.h"

#include "usec_time.h"
#include <stdlib.h>

#define OULIER_LIMIT 100

static float stdFlow = 0.01f;

px4flowData_t px4;


int16_t fx,fy;


static void flowdeckTask(void *param)
{
	systemWaitStart();
	uint64_t lastTime  = usecTimestamp();


	while(1){

		vTaskDelay(10);
		px4flowUpdate(&px4);

		float accpx = (float) -px4.pixel_flow_x_sum / 10.0f;
		float accpy = (float) -px4.pixel_flow_y_sum / 10.0f;

	    // Outlier removal
	    if (abs(accpx) < OULIER_LIMIT && abs(accpy) < OULIER_LIMIT) {

	    	flowMeasurement_t flowData;
			flowData.stdDevX = stdFlow;
			flowData.stdDevY = stdFlow;
			flowData.dt = (float)(usecTimestamp()-lastTime)/1000000.0f;
			lastTime = usecTimestamp();
			flowData.dpixelx = accpx;
			flowData.dpixely = accpy;
			fx = (float) accpx * 1.0f;
			fy = (float) accpy * 1.0f;

			if ( px4.qual != 0 ){
				estimatorEnqueueFlow(&flowData);
			}

	    }

	}
}

void flowTofInit()
{
	px4flowInit(&px4);

	if (px4flowTestConnection() == false){
		while(1);
	}

	xTaskCreate(flowdeckTask, FLOW_TASK_NAME, FLOW_TASK_STACKSIZE, NULL, FLOW_TASK_PRI, NULL);
}


