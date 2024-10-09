/*
 * dragonll_imu6500.h
 *
 *  Created on: Oct 9, 2024
 *      Author: AI FARM
 */

#ifndef INC_DRAGONLL_IMU6500_H_
#define INC_DRAGONLL_IMU6500_H_
#include "stm32f4xx_hal.h"
//#include "spi.h"
//#include "gpio.h"
#include "main.h"


#define IMU_ADDR					0xD0
#define WHO_AM_I_ADDR				0x75
#define PWR_MGMT_1					0x6B
#define CONFIG_REG					0x1A

#define SMPLRT_DIV_REG				0x19
#define GYRO_CONFIG_REG				0x1B

#define ACCEL_CONFIG_REG			0x1C
#define ACCEL_CONFIG_2_REG			0x1D

#define GYRO_DATA_REG				0x43
#define ACCEL_DATA_REG				0x3B


extern SPI_HandleTypeDef hspi1;


typedef struct {

	int16_t acc[3];
	int16_t gyr[3];
	float accScale[3];
	float gyroScale[3];

} MPU6500_IMU;

uint8_t MPU6500_Init(MPU6500_IMU *imu);

void MPU6500_ReadAcc(MPU6500_IMU *imu);
void MPU6500_ReadGyr(MPU6500_IMU *imu);
void MPU6500_ReadScale(MPU6500_IMU *imu);



#endif /* INC_DRAGONLL_IMU6500_H_ */
