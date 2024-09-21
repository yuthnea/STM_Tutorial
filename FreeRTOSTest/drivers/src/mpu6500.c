/*
 * mpu6500.c
 *
 *  Created on: Sep 13, 2024
 *      Author: AI FARM
 */

#include <FreeRTOS.h>
#include <task.h>

#include "stm32f4xx_hal.h"
#include "spi_drv.h"
#include "mpu6500.h"
#include "i2c_drv.h"

uint8_t walk = 0;

bool mpu6500TestConnection() {
	uint8_t mpuID;
//	walk = 1;//JH
	HAL_I2C_Mem_Read(&hi2c1, MPU6500_ADDRESS, WHO_AM_I_REG, 1, &mpuID, 1, 100);
//	walk =1;//NJH
	if (mpuID != 0x75)
		return false;
//	walk = 1;//NJH
	return true;
}

static bool mpu6500EvaluateSelfTest(float low, float high, float value,
		char *string) {
	if (value < low || value > high) {
		//    DEBUG_PRINT("Self test %s [FAIL]. low: %0.2f, high: %0.2f, measured: %0.2f\n",
		//                string, (double)low, (double)high, (double)value);
		return false;
	}
	return true;
}
bool mpu6500SelfTest() {
	return true;
}
void mpu6500Init(void) {
	uint8_t data;
	data = 0x00;
	HAL_I2C_Mem_Write(&hi2c1, MPU6500_ADDRESS, PWR_MGMT_1_REG, 1, &data, 1,
			100);
	vTaskDelay(500);
	// Set ACCEL to +-16g, GYRO to +-2000dps
	data = 0x18;
	HAL_I2C_Mem_Write(&hi2c1, MPU6500_ADDRESS, GYRO_CONFIG_REG, 1, &data, 1,
			100);
	vTaskDelay(10);
	HAL_I2C_Mem_Write(&hi2c1, MPU6500_ADDRESS, ACCEL_CONFIG_REG, 1, &data, 1,
			100);
	vTaskDelay(10);
	// Set sampling rate to 1khz
	data = 0x07;
	HAL_I2C_Mem_Write(&hi2c1, MPU6500_ADDRESS, SMPLRT_DIV_REG, 1, &data, 1,
			100);

	vTaskDelay(10);
	// Set GYRO to 41hz bandwidth
	data = 0x03;
	HAL_I2C_Mem_Write(&hi2c1, MPU6500_ADDRESS, CONFIG_REG, 1, &data, 1, 100);

	// Enable data ready interrupt to propagate to interrupt pin
	vTaskDelay(10);
	data = 0x01;
	HAL_I2C_Mem_Write(&hi2c1, MPU6500_ADDRESS, INT_ENABLE_REG, 1, &data, 1,
			100);
}

void mpu6500SetAccelDLPF(uint8_t range) {
	HAL_I2C_Mem_Write(&hi2c1, MPU6500_ADDRESS, ACCEL_CONFIG_2_REG, 1, &range, 1,
			100);
}
void mpu6500GetAccelGyroData(mpu6500_t *mpu6500TypeDef) {
	HAL_I2C_Mem_Read(&hi2c1, MPU6500_ADDRESS, ACCEL_XOUT_H_REG, 1,
			mpu6500TypeDef->buf, sizeof(mpu6500_t), 100);
}
void mpu6500GetMotion6(int16_t *ax, int16_t *ay, int16_t *az, int16_t *gx,
		int16_t *gy, int16_t *gz) {
	uint8_t buf[14];
	HAL_I2C_Mem_Read(&hi2c1, MPU6500_ADDRESS, ACCEL_XOUT_H_REG, 1, buf, 14,
			100);
	*ax = (((int16_t) buf[0]) << 8) | buf[1];
	*ay = (((int16_t) buf[2]) << 8) | buf[3];
	*az = (((int16_t) buf[4]) << 8) | buf[5];
	*gx = (((int16_t) buf[8]) << 8) | buf[9];
	*gy = (((int16_t) buf[10]) << 8) | buf[11];
	*gz = (((int16_t) buf[12]) << 8) | buf[13];
}
//void MPU_CS(MPU6500_SPI_t *pMPU6500, uint8_t stat){
//	HAL_GPIO_WritePin(pMPU6500->settings.CS_Pin, pMPU6500->settings.CS_Port, stat);
//}
