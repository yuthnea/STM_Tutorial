/*
 * flowdeck.c
 *
 *  Created on: Sep 6, 2024
 *      Author: Admin
 */

#include "FreeRTOS.h"
#include "task.h"

#include "deck_spi.h"
#include "system.h"
#include "pmw3901.h"
#include "sleepus.h"

#include "stabilizer_types.h"
#include "estimator.h"

#include "cf_math.h"

#include "usec_time.h"
#include <stdlib.h>

#define AVERAGE_HISTORY_LENGTH 4
#define OULIER_LIMIT 100
#define LP_CONSTANT 0.8f

#if defined(USE_MA_SMOOTHING)
static struct {
  float32_t averageX[AVERAGE_HISTORY_LENGTH];
  float32_t averageY[AVERAGE_HISTORY_LENGTH];
  size_t ptr;
} pixelAverages;
#endif

extern uint8_t flage = 0;

float dpixelx_previous = 0;
float dpixely_previous = 0;

static uint8_t outlierCount = 0;
static float stdFlow = 2.0f;

static bool isInit = false;

motionBurst_t currentMotion;

// Disables pushing the flow measurement in the EKF
static bool useFlowDisabled = false;

// Turn on adaptive standard deviation for the kalman filter
static bool useAdaptiveStd = false;

// Set standard deviation flow
// (will not work if useAdaptiveStd is on)
static float flowStdFixed = 2.0f;

static void flowdeckTask(void *param)
{
//	flage = 1; // nan JUMP HERE
	systemWaitStart();

	uint64_t lastTime = usecTimestamp();
	flage = 1;
	while(1) {
		vTaskDelay(10);

	    pmw3901ReadMotion(&currentMotion);
	    // Flip motion information to comply with sensor mounting
	    // (might need to be changed if mounted differently)
	    int16_t accpx = -currentMotion.deltaY;
	    int16_t accpy = -currentMotion.deltaX;

		// Outlier removal
		if (abs(accpx) < OULIER_LIMIT && abs(accpy) < OULIER_LIMIT) {

			if (useAdaptiveStd) {
				// The standard deviation is fitted by measurements flying over low and high texture
				//   and looking at the shutter time
				float shutter_f = (float) currentMotion.shutter;
				stdFlow = 0.0007984f * shutter_f + 0.4335f;

				// The formula with the amount of features instead
				/*float squal_f = (float)currentMotion.squal;
				 stdFlow =  -0.01257f * squal_f + 4.406f; */
				if (stdFlow < 0.1f)
					stdFlow = 0.1f;
			} else {
				stdFlow = flowStdFixed;
			}

			// Form flow measurement struct and push into the EKF
			flowMeasurement_t flowData;
			flowData.stdDevX = stdFlow;
			flowData.stdDevY = stdFlow;
			flowData.dt = (float) (usecTimestamp() - lastTime) / 1000000.0f;
			// we do want to update dt every measurement and not only in the ones with detected motion,
			// as we work with instantaneous gyro and velocity values in the update function
			// (meaning assuming the current measurements over all of dt)
			lastTime = usecTimestamp();

#if defined(USE_MA_SMOOTHING)
	      // Use MA Smoothing
	      pixelAverages.averageX[pixelAverages.ptr] = (float32_t)accpx;
	      pixelAverages.averageY[pixelAverages.ptr] = (float32_t)accpy;

	      float32_t meanX;
	      float32_t meanY;

	      arm_mean_f32(pixelAverages.averageX, AVERAGE_HISTORY_LENGTH, &meanX);
	      arm_mean_f32(pixelAverages.averageY, AVERAGE_HISTORY_LENGTH, &meanY);

	      pixelAverages.ptr = (pixelAverages.ptr + 1) % AVERAGE_HISTORY_LENGTH;

	      flowData.dpixelx = (float)meanX;   // [pixels]
	      flowData.dpixely = (float)meanY;   // [pixels]
	#elif defined(USE_LP_FILTER)
	      // Use LP filter measurements
	      flowData.dpixelx = LP_CONSTANT * dpixelx_previous + (1.0f - LP_CONSTANT) * (float)accpx;
	      flowData.dpixely = LP_CONSTANT * dpixely_previous + (1.0f - LP_CONSTANT) * (float)accpy;
	      dpixelx_previous = flowData.dpixelx;
	      dpixely_previous = flowData.dpixely;
	#else
			// Use raw measurements
			flowData.dpixelx = (float) accpx;
			flowData.dpixely = (float) accpy;
#endif
			// Push measurements into the estimator if flow is not disabled
			//    and the PMW flow sensor indicates motion detection
			if (!useFlowDisabled && currentMotion.motion == 0xB0) {
				estimatorEnqueueFlow(&flowData);
			}
		} else {
			outlierCount++;
		}

	}

}

void flowdeck1Init()
{
  if (isInit) {
    return;
  }
//  flage = 1;// JUMP HERE
  if (pmw3901Init())
  {
    xTaskCreate(flowdeckTask, FLOW_TASK_NAME, FLOW_TASK_STACKSIZE, NULL,FLOW_TASK_PRI, NULL);
//    flage = 1; //Nan JUMP HERE
    isInit = true;
  }
}








