/*
 * dragonll_imu6500.c
 *
 *  Created on: Oct 9, 2024
 *      Author: AI FARM
 */
#include "dragonll_imu6500.h"

#include "system.h"
#include "sleepus.h"

static void MPU_CS(uint8_t state) {
	if (!state)
		HAL_GPIO_WritePin(GYRO_CS_GPIO_Port, GYRO_CS_Pin, 0);
	else
		HAL_GPIO_WritePin(GYRO_CS_GPIO_Port, GYRO_CS_Pin, 1);
}
static void MPU_Wirte_Register(uint8_t reg, uint8_t value) {
	uint8_t buf[2];
	buf[0] = reg;
	buf[0] &= ~(0x80);
	buf[1] = value;
	MPU_CS(0);
	HAL_SPI_Transmit(&hspi1, buf, 2, 100);
	MPU_CS(1);
}
static void MPU_Read_Register(uint8_t reg, uint8_t *buffer, uint8_t len) {
	uint8_t buf = reg | 0x80;
	MPU_CS(0);
	HAL_SPI_Transmit(&hspi1, &buf, 1, 100);
	HAL_SPI_Receive(&hspi1, buffer, len, 100);
	MPU_CS(1);
}
uint8_t MPU6500_Init(MPU6500_IMU *imu) {

	imu->acc[0] = 0.0f;
	imu->acc[1] = 0.0f;
	imu->acc[2] = 0.0f;
	imu->gyr[0] = 0.0f;
	imu->gyr[1] = 0.0f;
	imu->gyr[2] = 0.0f;

//	HAL_Delay(10);
//	vTaskDelay(10);
	sleepus(10000);
	//use internal 100Mhz
	uint8_t imuID;
	MPU_Read_Register(WHO_AM_I_ADDR, &imuID, 1);
	if (imuID != 0x70)
		return 0;

//	HAL_Delay(50);
//	vTaskDelay(50);
	// 1 % 0.05 = 20
	sleepus(50000);
	// use 20Mhz internal
	uint8_t imuMode = 0x00;
	MPU_Wirte_Register(PWR_MGMT_1, imuMode);

	//Configure sample rate to 1KHz
	uint8_t sampleRateConfig = 0x00;
	MPU_Wirte_Register(SMPLRT_DIV_REG, sampleRateConfig);
	/* GYRO Configure */

	// Configure digital low-pass filter bandwidth to 184Hz with 1KHz
//	HAL_Delay(10);
//	vTaskDelay(10);
	sleepus(10000);
	uint8_t gyroDLPFConfig = 0x01;
	MPU_Wirte_Register(CONFIG_REG, gyroDLPFConfig);

	// Configure GYRO range to +-500dps
//	HAL_Delay(10);
//	vTaskDelay(10);
	sleepus(10000);
	uint8_t gyroRange = 0x0B;
	MPU_Wirte_Register(GYRO_CONFIG_REG, gyroRange);

	/* Accel configure */

	// Configure digital low-pass filter bandwidth to 184Hz with 1KHz
//	HAL_Delay(10);
//	vTaskDelay(10);
	sleepus(10000);
	uint8_t accelDLPFConfig = 0x01;
	MPU_Wirte_Register(ACCEL_CONFIG_2_REG, accelDLPFConfig);

	// Configure ACCEL range to +-8g
//	HAL_Delay(10);
//	vTaskDelay(10);
	sleepus(10000);
	uint8_t accelRange = 0x10;
	MPU_Wirte_Register(ACCEL_CONFIG_REG, accelRange);

	return 1;
}

void MPU6500_ReadAcc(MPU6500_IMU *imu) {
	uint8_t rxBuf[6];

	MPU_Read_Register(ACCEL_DATA_REG, rxBuf, 6);

	int16_t accelX = rxBuf[0] << 8 | rxBuf[1];
	int16_t accelY = rxBuf[2] << 8 | rxBuf[3];
	int16_t accelZ = rxBuf[4] << 8 | rxBuf[5];

	// +-8g
	imu->acc[0] = accelX;
	imu->acc[1] = accelY;
	imu->acc[2] = accelZ;



}
void MPU6500_ReadGyr(MPU6500_IMU *imu) {

	uint8_t rxBuf[6];

	MPU_Read_Register(GYRO_DATA_REG, rxBuf, 6);

	int16_t gyroX = rxBuf[0] << 8 | rxBuf[1];
	int16_t gyroY = rxBuf[2] << 8 | rxBuf[3];
	int16_t gyroZ = rxBuf[4] << 8 | rxBuf[5];

	imu->gyr[0] = gyroX;
	imu->gyr[1] = gyroY;
	imu->gyr[2] = gyroZ;

}
void MPU6500_ReadScale(MPU6500_IMU *imu){

	MPU6500_ReadAcc(imu);
	MPU6500_ReadGyr(imu);

	for ( uint8_t i=0; i<3; i++ ){
		imu->accScale[i] = (float) imu->acc[i] * 0.00239501953125f;
		imu->gyroScale[i] = (float) imu->gyr[i] * 0.00026632423f;
	}


}


