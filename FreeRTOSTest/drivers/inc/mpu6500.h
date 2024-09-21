/*
 * mpu6500.h
 *
 *  Created on: Sep 13, 2024
 *      Author: AI FARM
 */

#ifndef INC_MPU6500_H_
#define INC_MPU6500_H_
#include "stdbool.h"

#define MPU6500_ADDRESS			0xD0
#define WHO_AM_I_REG			0x75

#define PWR_MGMT_1_REG         	0x6B
#define SMPLRT_DIV_REG         	0x19
#define CONFIG_REG             	0x1A
#define GYRO_CONFIG_REG        	0x1B
#define ACCEL_CONFIG_REG       	0x1C
#define ACCEL_CONFIG_2_REG      0x1D
#define INT_ENABLE_REG			0x38
#define INT_STATUS_REG			0x3A

#define ACCEL_XOUT_H_REG		0x3B
#define ACCEL_YOUT_H_REG		0x3D
#define ACCEL_ZOUT_H_REG		0x3F

#define GYRO_XOUT_H_REG			0x43
#define GYRO_YOUT_H_REG			0x45
#define GYRO_ZOUT_H_REG			0x47

#define MPU6500_RA_ST_X_GYRO        0x00
#define MPU6500_RA_ST_Y_GYRO        0x01
#define MPU6500_RA_ST_Z_GYRO        0x02
#define MPU6500_RA_ST_X_ACCEL       0x0D
#define MPU6500_RA_ST_Y_ACCEL       0x0E
#define MPU6500_RA_ST_Z_ACCEL       0x0F

// Test limits
#define MPU6500_ST_GYRO_LOW      (-14.0)  // %
#define MPU6500_ST_GYRO_HIGH     14.0  // %
#define MPU6500_ST_ACCEL_LOW     (-14.0)  // %
#define MPU6500_ST_ACCEL_HIGH    14.0  // %

#define MPU6500_ACCEL_DLPF_BW_460   0x00
#define MPU6500_ACCEL_DLPF_BW_218   0x01
#define MPU6500_ACCEL_DLPF_BW_99    0x02
#define MPU6500_ACCEL_DLPF_BW_44    0x03
#define MPU6500_ACCEL_DLPF_BW_21    0x04
#define MPU6500_ACCEL_DLPF_BW_10    0x05
#define MPU6500_ACCEL_DLPF_BW_5     0x06

#define MPU6500_DLPF_BW_250         0x00
#define MPU6500_DLPF_BW_184         0x01
#define MPU6500_DLPF_BW_92          0x02
#define MPU6500_DLPF_BW_41          0x03
#define MPU6500_DLPF_BW_20          0x04
#define MPU6500_DLPF_BW_10          0x05
#define MPU6500_DLPF_BW_5           0x06

//#define RAD2DEG 57.2957795131
//
//// Set Up MPU6500
//#define MPU6500_ADDRESS_AD0_LOW     0x68 // address pin low (GND), default for InvenSense evaluation board
//#define MPU6500_ADDRESS_AD0_HIGH	0x69 // address pin high (VCC)
//#define MPU6500_RA_INT_ENABLE       0x38
//// Write operation
//#define MPU6500_ADDR 				0xD0
//// Read operation
//#define MPU6500_ADDR_R				0xD1	​
//// Who am i
//#define MPU6500_RA_WHO_AM_I         0x75
//#define MPU6500_WHO_AM_I_ANS 		0x70
//#define CS_SELECT         			0
//#define CS_DESELECT       			1
//#define READWRITE         			0x80
//#define SPI_TIMOUT_MS     			1000
//// power
//#define MPU6500_RA_PWR_MGMT_1       0x6B
//#define MPU6500_RA_SMPLRT_DIV       0x19
//// accelerometer
//#define MPU6500_RA_ACCEL_CONFIG     0x1C
//#define MPU6500_RA_ACCEL_XOUT_H     0x3B
//
//#define MPU6500_RA_TEMP_OUT_H       0x41
//// Gyroscopic
//#define MPU6500_RA_GYRO_CONFIG      0x1B
//#define MPU6500_RA_GYRO_XOUT_H      0x43
//#define MPU6500_RA_USER_CTRL        0x6A
//
//#define ACCEL_CONFIG_2_REG			0x1D

typedef struct{
	uint8_t buf[14];
}mpu6500_t;
//
//// Full Scale range
//enum gyroscopeFullscaleRange{
//	gfsr_250DPS,
//	gfsr_500DPS,
//	gfsr_1000DPS,
//	gfsr_2000DPS
//};
//
//enum accelerometerFullscaleRange{
//	afsr_2G,
//	afsr_4G,
//	afsr_8G,
//	afsr_16G
//};
//
//typedef struct MPU6500{
//	struct RawData{
//		int16_t ax, ay, az, gx, gy, gz;
//	}rawData;
//	struct SensorData{
//		float aScaleFactor, gScaleFactor;
//		float ax, ay, az, gx, gy, gz;
//	}sensorData;
//	struct GryroCal{
//		float x, y, z;
//	}gyrocal;
//	struct Attitude {
//		float dt, tau;
//		float pitch, roll, yaw;
//	} attitude;
//	struct Settings{
//		uint8_t aFullScaleRange, gFullScaleRang;
//		GPIO_TypeDef *CS_Port;
//		uint8_t CS_Pin;
//	}settings;
//	double KamanAngleX;
//	double KamanAngleY;
//}MPU6500_SPI_t;


bool mpu6500TestConnection();
void mpu6500Init(void);
void mpu6500SetAccelDLPF(uint8_t range);
bool mpu6500SelfTest();
void mpu6500GetAccelGyroData(mpu6500_t *mpu6500TypeDef);
void mpu6500GetMotion6(int16_t* ax, int16_t* ay, int16_t* az, int16_t* gx, int16_t* gy, int16_t* gz);

// low level function
//void MPU_CS(MPU6500_SPI_t *pMPU6500, uint8_t stat);


#endif /* INC_MPU6500_H_ */
