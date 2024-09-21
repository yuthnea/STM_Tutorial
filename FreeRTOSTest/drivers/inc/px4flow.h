/*
 * px4flow.h
 *
 *  Created on: Sep 2, 2024
 *      Author: Admin
 */

#ifndef INC_PX4FLOW_H_
#define INC_PX4FLOW_H_
#include <stdbool.h>
#include "main.h"
#include "i2c_drv.h"

#define PX4FLOW_ADDRESS 0x42 << 1
#define PX4FLOW_TIMEOUT 10


typedef struct
{
    uint16_t frame_count;// counts created I2C frames
    int16_t pixel_flow_x_sum;// accumulated x flow in pixels*10 since last I2C frame
    int16_t pixel_flow_y_sum;// accumulated y flow in pixels*10 since last I2C frame
    int16_t flow_comp_m_x;// x velocity*1000 in meters / timestep
    int16_t flow_comp_m_y;// y velocity*1000 in meters / timestep
    int16_t qual;// Optical flow quality / confidence 0: bad, 255: maximum quality
    int16_t gyro_x_rate; //gyro x rate
    int16_t gyro_y_rate; //gyro y rate
    int16_t gyro_z_rate; //gyro z rate
    uint8_t gyro_range; // gyro range
    uint8_t sonar_timestamp;// timestep in milliseconds between I2C frames
    int16_t ground_distance;// Ground distance in meters*1000. Positive value: distance known. Negative value: Unknown distance
} px4flowData_t;


void px4flowInit(px4flowData_t *flow);
bool px4flowTestConnection();
void px4flowUpdate(px4flowData_t *flow);

#endif /* INC_PX4FLOW_H_ */
