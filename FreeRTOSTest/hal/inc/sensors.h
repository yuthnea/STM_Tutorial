/*
 * sensors.h
 *
 *  Created on: Aug 31, 2024
 *      Author: Admin
 */

#ifndef INC_SENSORS_H_
#define INC_SENSORS_H_

#include "stabilizer_types.h"

typedef enum { ACC_MODE_PROPTEST, ACC_MODE_FLIGHT } accModes;

void sensorsInit(void);
bool sensorsTest(void);
bool sensorsAreCalibrated(void);

/**
 * More extensive test of the sensors
 */
bool sensorsManufacturingTest(void);

// For legacy control
void sensorsAcquire(sensorData_t *sensors);

/**
 * This function should block and unlock at 1KhZ
 */
void sensorsWaitDataReady(void);

// Allows individual sensor measurement
bool sensorsReadGyro(Axis3f *gyro);
bool sensorsReadAcc(Axis3f *acc);
bool sensorsReadMag(Axis3f *mag);
bool sensorsReadBaro(baro_t *baro);

/**
 * Suspend or resume sensor data
 */
void sensorsSuspend();
void sensorsResume();

/**
 * Set acc mode, one of accModes enum
 */
void sensorsSetAccMode(accModes accMode);

#endif /* INC_SENSORS_H_ */
