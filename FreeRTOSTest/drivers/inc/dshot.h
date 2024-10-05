/*
 * dshot.h
 *
 *  Created on: Sep 17, 2024
 *      Author: AI FARM
 */

#ifndef INC_DSHOT_H_
#define INC_DSHOT_H_
//#include "tim.h"
#include "stdbool.h"
#include <math.h>
#include "timer_drv.h"
#include "nvic.h"

// Configuration Timer
#define TIMER_CLOCK		84000000

// Motor 1
#define MOTOR_1_TIM		(&htim3)
#define MOTOR_1_TIM_CHANNEL		TIM_CHANNEL_1

// Motor 2
#define MOTOR_2_TIM		(&htim3)
#define MOTOR_2_TIM_CHANNEL		TIM_CHANNEL_2

// Motor 3
#define MOTOR_3_TIM		(&htim3)
#define MOTOR_3_TIM_CHANNEL		TIM_CHANNEL_3

// Motor 4
#define MOTOR_4_TIM		(&htim3)
#define MOTOR_4_TIM_CHANNEL		TIM_CHANNEL_4


#define MHZ_TO_HZ(x)		((x) * 1000000)

#define dshot150_hz		MHZ_TO_HZ(3)
#define dshot300_hz		MHZ_TO_HZ(6)
#define dshot600_hz		MHZ_TO_HZ(12)

#define MOTOR_BIT_0		7
#define MOTOR_BIT_1		14
#define MOTOR_BITLENGTH	20

#define DSHOT_FRAME_SIZE	16
#define DSHOT_DMA_BUFFER_SIZE	18

#define DSHOT_MIN_THROTTLE		48
#define DSHOT_MAX_THROTTLE		2047
#define DSHOT_RANGE		(DSHOT_MAX_THROTTLE - DSHOT_MIN_THROTTLE)

typedef enum{
	DSHOT150,
	DSHOT300,
	DSHOT600
}dshot_type;

// Init Dshot
void hal_dshot_init(dshot_type dshot_type);

// Basic Function Dshot
void hal_dshot_write(uint16_t* motor_value);


#endif /* INC_DSHOT_H_ */
