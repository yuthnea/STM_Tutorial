/*
 * sensors_mpu9250_bmp280.h
 *
 *  Created on: Aug 28, 2024
 *      Author: Admin
 */

#ifndef INC_SENSORS_MPU9250_BMP280_H_
#define INC_SENSORS_MPU9250_BMP280_H_

#include "sensors.h"

#define MPU9250_ADDR           0x68 << 1  // MPU9250 I2C address shifted for HAL library
#define AK8963_ADDR            0x0C << 1  // AK8963 Magnetometer I2C address
#define WHO_AM_I_REG           0x75
#define PWR_MGMT_1_REG         0x6B
#define SMPLRT_DIV_REG         0x19
#define CONFIG_REG             0x1A
#define GYRO_CONFIG_REG        0x1B
#define ACCEL_CONFIG_REG       0x1C
#define INT_PIN_CFG            0x37
#define I2C_MST_CTRL           0x24
#define I2C_SLV0_ADDR          0x25
#define I2C_SLV0_REG           0x26
#define I2C_SLV0_CTRL          0x27
#define I2C_SLV0_DO            0x63
#define EXT_SENS_DATA_00       0x49
#define AK8963_WHO_AM_I        0x00
#define AK8963_CNTL1           0x0A
#define AK8963_CNTL1_MODE      0x16       // 16-bit resolution, continuous measurement mode 2
#define AK8963_ASAX            0x10       // Sensitivity adjustment values
#define AK8963_ST1             0x02
#define AK8963_XOUT_L          0x03



void sensorsMpu9250Bmp280Init(void);
bool sensorsMpu9250Bmp280Test(void);
bool sensorsMpu9250Bmp280AreCalibrated(void);
bool sensorsMpu9250Bmp280ManufacturingTest(void);
void sensorsMpu9250Bmp280Acquire(sensorData_t *sensors);
void sensorsMpu9250Bmp280WaitDataReady(void);
bool sensorsMpu9250Bmp280ReadGyro(Axis3f *gyro);
bool sensorsMpu9250Bmp280ReadAcc(Axis3f *acc);
bool sensorsMpu9250Bmp280ReadMag(Axis3f *mag);
bool sensorsMpu9250Bmp280ReadBaro(baro_t *baro);
void sensorsMpu9250Bmp280SetAccMode(accModes accMode);

#endif /* INC_SENSORS_MPU9250_BMP280_H_ */
