/*
 * mpu9250.c
 *
 *  Created on: Aug 30, 2024
 *      Author: Admin
 */
#include <FreeRTOS.h>
#include <task.h>

#include "stm32f4xx_hal.h"
#include "i2c_drv.h"
#include "mpu9250.h"


bool mpu9250TestConnection()
{
	uint8_t mpuID;
	HAL_I2C_Mem_Read(&hi2c1, MPU9250_ADDRESS, WHO_AM_I_REG, 1, &mpuID, 1, 100);
	if (mpuID != 0x75) return false;

	return true;
}
static bool mpu9250EvaluateSelfTest(float low, float high, float value, char* string)
{
  if (value < low || value > high)
  {
//    DEBUG_PRINT("Self test %s [FAIL]. low: %0.2f, high: %0.2f, measured: %0.2f\n",
//                string, (double)low, (double)high, (double)value);
    return false;
  }
  return true;
}
bool mpu9250SelfTest()
{
	uint8_t rawData[6] = { 0, 0, 0, 0, 0, 0 };
	uint8_t saveReg[5];
	uint8_t selfTest[6];
	int32_t gAvg[3] = { 0 }, aAvg[3] = { 0 }, aSTAvg[3] = { 0 }, gSTAvg[3] = { 0 };
	int32_t factoryTrim[6];
	float aDiff[3], gDiff[3];
	uint8_t FS = 0;
	int i;

	HAL_I2C_Mem_Read(&hi2c1, MPU9250_ADDRESS, SMPLRT_DIV_REG, 1, &saveReg[0], 1, 100);
	HAL_I2C_Mem_Read(&hi2c1, MPU9250_ADDRESS, CONFIG_REG, 1, &saveReg[1], 1, 100);
	HAL_I2C_Mem_Read(&hi2c1, MPU9250_ADDRESS, GYRO_CONFIG_REG, 1, &saveReg[2], 1, 100);
	HAL_I2C_Mem_Read(&hi2c1, MPU9250_ADDRESS, ACCEL_CONFIG_REG, 1, &saveReg[3], 1, 100);
	HAL_I2C_Mem_Read(&hi2c1, MPU9250_ADDRESS, ACCEL_CONFIG_2_REG, 1, &saveReg[4], 1, 100);

	HAL_I2C_Mem_Write(&hi2c1, MPU9250_ADDRESS, SMPLRT_DIV_REG, 1, (uint8_t*) 0x00, 1, 100);
	HAL_I2C_Mem_Write(&hi2c1, MPU9250_ADDRESS, CONFIG_REG, 1, (uint8_t*) 0x02, 1, 100);
	HAL_I2C_Mem_Write(&hi2c1, MPU9250_ADDRESS, GYRO_CONFIG_REG, 1, (uint8_t*) (1<<FS), 1, 100);
	HAL_I2C_Mem_Write(&hi2c1, MPU9250_ADDRESS, ACCEL_CONFIG_2_REG, 1, (uint8_t*) 0x02, 1, 100);
	HAL_I2C_Mem_Write(&hi2c1, MPU9250_ADDRESS, ACCEL_CONFIG_REG, 1, (uint8_t*) (1<<FS), 1, 100);

	for (i = 0; i < 200; i++) {
		// get average current values of gyro and acclerometer
		HAL_I2C_Mem_Read(&hi2c1, MPU9250_ADDRESS, ACCEL_XOUT_H_REG, 1, rawData, 6, 100);
		aAvg[0] += (int16_t) (((int16_t) rawData[0] << 8) | rawData[1]); // Turn the MSB and LSB into a signed 16-bit value
		aAvg[1] += (int16_t) (((int16_t) rawData[2] << 8) | rawData[3]);
		aAvg[2] += (int16_t) (((int16_t) rawData[4] << 8) | rawData[5]);

		HAL_I2C_Mem_Read(&hi2c1, MPU9250_ADDRESS, GYRO_XOUT_H_REG, 1, rawData, 6, 100);
		gAvg[0] += (int16_t) ((int16_t) rawData[0] << 8) | rawData[1]; // Turn the MSB and LSB into a signed 16-bit value
		gAvg[1] += (int16_t) ((int16_t) rawData[2] << 8) | rawData[3];
		gAvg[2] += (int16_t) ((int16_t) rawData[4] << 8) | rawData[5];
	}

	for (i = 0; i < 3; i++) { // Get average of 200 values and store as average current readings
		aAvg[i] /= 200;
		gAvg[i] /= 200;
	}

	// Configure the accelerometer for self-test
	HAL_I2C_Mem_Write(&hi2c1, MPU9250_ADDRESS, ACCEL_CONFIG_REG, 1, (uint8_t*) 0xE0, 1, 100);
	HAL_I2C_Mem_Write(&hi2c1, MPU9250_ADDRESS, GYRO_CONFIG_REG, 1, (uint8_t*) 0xE0, 1, 100);
	vTaskDelay(M2T(25)); // Delay a while to let the device stabilize

	for (i = 0; i < 200; i++) {
		// get average self-test values of gyro and acclerometer
		HAL_I2C_Mem_Read(&hi2c1, MPU9250_ADDRESS, ACCEL_XOUT_H_REG, 1, rawData, 6, 100);
		aSTAvg[0] += (int16_t) (((int16_t) rawData[0] << 8) | rawData[1]); // Turn the MSB and LSB into a signed 16-bit value
		aSTAvg[1] += (int16_t) (((int16_t) rawData[2] << 8) | rawData[3]);
		aSTAvg[2] += (int16_t) (((int16_t) rawData[4] << 8) | rawData[5]);

		HAL_I2C_Mem_Read(&hi2c1, MPU9250_ADDRESS, GYRO_XOUT_H_REG, 1, rawData, 6, 100);
		gSTAvg[0] += (int16_t) (((int16_t) rawData[0] << 8) | rawData[1]); // Turn the MSB and LSB into a signed 16-bit value
		gSTAvg[1] += (int16_t) (((int16_t) rawData[2] << 8) | rawData[3]);
		gSTAvg[2] += (int16_t) (((int16_t) rawData[4] << 8) | rawData[5]);
	}

	for (i = 0; i < 3; i++) { // Get average of 200 values and store as average self-test readings
		aSTAvg[i] /= 200;
		gSTAvg[i] /= 200;
	}

	// Configure the gyro and accelerometer for normal operation
	// Configure the accelerometer for self-test
	HAL_I2C_Mem_Write(&hi2c1, MPU9250_ADDRESS, ACCEL_CONFIG_REG, 1, (uint8_t*) 0x00, 1, 100);
	HAL_I2C_Mem_Write(&hi2c1, MPU9250_ADDRESS, GYRO_CONFIG_REG, 1, (uint8_t*) 0x00, 1, 100);
	vTaskDelay(M2T(25)); // Delay a while to let the device stabilize

	// Retrieve accelerometer and gyro factory Self-Test Code from USR_Reg
	HAL_I2C_Mem_Read(&hi2c1, MPU9250_ADDRESS, MPU9250_RA_ST_X_ACCEL, 1, &selfTest[0], 1, 100);
	HAL_I2C_Mem_Read(&hi2c1, MPU9250_ADDRESS, MPU9250_RA_ST_Y_ACCEL, 1, &selfTest[1], 1, 100);
	HAL_I2C_Mem_Read(&hi2c1, MPU9250_ADDRESS, MPU9250_RA_ST_Z_ACCEL, 1, &selfTest[2], 1, 100);
	HAL_I2C_Mem_Read(&hi2c1, MPU9250_ADDRESS, MPU9250_RA_ST_X_GYRO, 1, &selfTest[3], 1, 100);
	HAL_I2C_Mem_Read(&hi2c1, MPU9250_ADDRESS, MPU9250_RA_ST_Y_GYRO, 1, &selfTest[4], 1, 100);
	HAL_I2C_Mem_Read(&hi2c1, MPU9250_ADDRESS, MPU9250_RA_ST_Z_GYRO, 1, &selfTest[5], 1, 100);
	for (i = 0; i < 6; i++) {
		if (selfTest[i] != 0) {
			factoryTrim[i] = mpu6500StTb[selfTest[i] - 1];
		} else {
			factoryTrim[i] = 0;
		}
	}

	// Report results as a ratio of (STR - FT)/FT; the change from Factory Trim of the Self-Test Response
	// To get percent, must multiply by 100
	for (i = 0; i < 3; i++) {
		aDiff[i] = 100.0f * ((float) ((aSTAvg[i] - aAvg[i]) - factoryTrim[i])) / factoryTrim[i]; // Report percent differences
		gDiff[i] = 100.0f * ((float) ((gSTAvg[i] - gAvg[i]) - factoryTrim[i + 3])) / factoryTrim[i + 3]; // Report percent differences
	}

	// Restore old configuration
	HAL_I2C_Mem_Write(&hi2c1, MPU9250_ADDRESS, SMPLRT_DIV_REG, 1, &saveReg[0], 1, 100);
	HAL_I2C_Mem_Write(&hi2c1, MPU9250_ADDRESS, CONFIG_REG, 1, &saveReg[1], 1, 100);
	HAL_I2C_Mem_Write(&hi2c1, MPU9250_ADDRESS, GYRO_CONFIG_REG, 1, &saveReg[2], 1, 100);
	HAL_I2C_Mem_Write(&hi2c1, MPU9250_ADDRESS, ACCEL_CONFIG_2_REG, 1, &saveReg[3], 1, 100);
	HAL_I2C_Mem_Write(&hi2c1, MPU9250_ADDRESS, ACCEL_CONFIG_REG, 1, &saveReg[4], 1, 100);

	// Check result
	if (mpu9250EvaluateSelfTest(
			MPU9250_ST_GYRO_LOW, MPU9250_ST_GYRO_HIGH, gDiff[0], "gyro X")
			&& mpu9250EvaluateSelfTest(MPU9250_ST_GYRO_LOW,
					MPU9250_ST_GYRO_HIGH, gDiff[1], "gyro Y")
			&& mpu9250EvaluateSelfTest(MPU9250_ST_GYRO_LOW,
					MPU9250_ST_GYRO_HIGH, gDiff[2], "gyro Z")
			&& mpu9250EvaluateSelfTest(MPU9250_ST_ACCEL_LOW,
					MPU9250_ST_ACCEL_HIGH, aDiff[0], "acc X")
			&& mpu9250EvaluateSelfTest(MPU9250_ST_ACCEL_LOW,
					MPU9250_ST_ACCEL_HIGH, aDiff[1], "acc Y")
			&& mpu9250EvaluateSelfTest(MPU9250_ST_ACCEL_LOW,
					MPU9250_ST_ACCEL_HIGH, aDiff[2], "acc Z")) {
		return true;
	} else {
		return false;
	}

}
void mpu9250Init(void)
{
	uint8_t data;

    data = 0x00;
    HAL_I2C_Mem_Write(&hi2c1, MPU9250_ADDRESS, PWR_MGMT_1_REG, 1, &data, 1, 100);
    vTaskDelay(500);

    // Set ACCEL to +-16g, GYRO to +-2000dps
    data = 0x18;
    HAL_I2C_Mem_Write(&hi2c1, MPU9250_ADDRESS, GYRO_CONFIG_REG, 1, &data, 1, 100);
    vTaskDelay(10);
    HAL_I2C_Mem_Write(&hi2c1, MPU9250_ADDRESS, ACCEL_CONFIG_REG, 1, &data, 1, 100);
    vTaskDelay(10);

    // Set sampling rate to 1Khz
    data = 0x07;
    HAL_I2C_Mem_Write(&hi2c1, MPU9250_ADDRESS, SMPLRT_DIV_REG, 1, &data, 1, 100);

    vTaskDelay(10);
    // Set GYRO to 41Hz bandwidth
    data = 0x03;
    HAL_I2C_Mem_Write(&hi2c1, MPU9250_ADDRESS, CONFIG_REG, 1, &data, 1, 100);

    // Enable data ready interrupt to propagate to interrupt pin
    vTaskDelay(10);
    data = 0x01;
    HAL_I2C_Mem_Write(&hi2c1, MPU9250_ADDRESS, INT_ENABLE_REG, 1, &data, 1, 100);

}

void mpu9250SetAccelDLPF(uint8_t range)
{
    HAL_I2C_Mem_Write(&hi2c1, MPU9250_ADDRESS, ACCEL_CONFIG_2_REG, 1, &range, 1, 100);
}
void mpu9250GetAccelGyroData(mpu9250_t *mpu9250TypeDef)
{
	HAL_I2C_Mem_Read(&hi2c1, MPU9250_ADDRESS, ACCEL_XOUT_H_REG, 1, mpu9250TypeDef->buf, sizeof(mpu9250_t), 100);

}
void mpu9250GetMotion6(int16_t* ax, int16_t* ay, int16_t* az, int16_t* gx, int16_t* gy, int16_t* gz)
{
	uint8_t buf[14];
	HAL_I2C_Mem_Read(&hi2c1, MPU9250_ADDRESS, ACCEL_XOUT_H_REG, 1, buf, 14, 100);
	*ax = (((int16_t) buf[0]) << 8) | buf[1];
	*ay = (((int16_t) buf[2]) << 8) | buf[3];
	*az = (((int16_t) buf[4]) << 8) | buf[5];
	*gx = (((int16_t) buf[8]) << 8) | buf[9];
	*gy = (((int16_t) buf[10]) << 8) | buf[11];
	*gz = (((int16_t) buf[12]) << 8) | buf[13];
}
