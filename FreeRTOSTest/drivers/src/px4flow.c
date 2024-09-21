/*
 * px4flow.c
 *
 *  Created on: Sep 2, 2024
 *      Author: Admin
 */
#include "px4flow.h"
#include "i2c_drv.h"

static bool isInit = false;
void px4flowInit(px4flowData_t *flow)
{

	flow->flow_comp_m_x = 0;
	flow->flow_comp_m_y = 0;
	flow->frame_count = 0;
	flow->ground_distance = 0;
	flow->gyro_range = 0;
	flow->gyro_x_rate = 0;
	flow->gyro_y_rate = 0;
	flow->gyro_z_rate = 0;
	flow->pixel_flow_x_sum = 0;
	flow->pixel_flow_y_sum = 0;
	flow->qual = 0;
	flow->sonar_timestamp = 0;

	isInit = true;
}
bool px4flowTestConnection()
{
	if (!isInit){
		return false;
	}
	return true;
}
void px4flowUpdate(px4flowData_t *flow)
{
	uint8_t px4flow_buffer[22];
    uint16_t frameCount;
    int16_t pixFlowXSum;
    int16_t pixFlowYSum;
    int16_t flowCompX;
    int16_t flowCompY;
    int16_t qual;
    int16_t gyroXRate;
    int16_t gyroYRate;
    int16_t gyroZRate;
    uint8_t gyroRange;
    uint8_t sonarTimestamp;
    int16_t groundDistance;

	HAL_I2C_Mem_Read(&hi2c2, PX4FLOW_ADDRESS, 0x00, 1, px4flow_buffer, 22, 100);

	frameCount = px4flow_buffer[1] << 8 | px4flow_buffer[0];
	pixFlowXSum = px4flow_buffer[3] << 8 | px4flow_buffer[2];
	pixFlowYSum = px4flow_buffer[5] << 8 | px4flow_buffer[4];
	flowCompX = px4flow_buffer[7] << 8 | px4flow_buffer[6];
	flowCompY = px4flow_buffer[9] << 8 | px4flow_buffer[8];
	qual = px4flow_buffer[11] << 8 | px4flow_buffer[10];
	gyroXRate = px4flow_buffer[13] << 8 | px4flow_buffer[12];
	gyroYRate = px4flow_buffer[15] << 8 | px4flow_buffer[14];
	gyroZRate = px4flow_buffer[17] << 8 | px4flow_buffer[16];
	gyroRange = px4flow_buffer[18];
	sonarTimestamp = px4flow_buffer[19];
	groundDistance = px4flow_buffer[21] << 8 | px4flow_buffer[20];

	flow->frame_count = frameCount;
	flow->pixel_flow_x_sum = pixFlowXSum;
	flow->pixel_flow_y_sum = pixFlowYSum;
	flow->flow_comp_m_x = flowCompX;
	flow->flow_comp_m_y = flowCompY;
	flow->qual = qual;
	flow->gyro_x_rate = gyroXRate;
	flow->gyro_y_rate = gyroYRate;
	flow->gyro_z_rate = gyroZRate;
	flow->gyro_range = gyroRange;
	flow->sonar_timestamp = sonarTimestamp;
	flow->ground_distance = groundDistance;

}

