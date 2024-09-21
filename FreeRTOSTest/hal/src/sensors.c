/*
 * sensors.c
 *
 *  Created on: Aug 31, 2024
 *      Author: Admin
 */

#include "sensors.h"
#include "platform.h"


#define xstr(s) str(s)
#define str(s) #s

//#define CONFIG_SENSORS_MPU9250_BMP280
#define CONFIG_SENSORS_MPU6500_BMP280

//#ifdef CONFIG_SENSORS_MPU9250_BMP280
//  #include "sensors_mpu9250_bmp280.h"
//#endif
#ifdef CONFIG_SENSORS_MPU6500_BMP280
  #include "sensors_mpu6500_bmp280.h"
#endif

uint8_t run = 0;


typedef struct {
  SensorImplementation_t implements;
  void (*init)(void);
  bool (*test)(void);
  bool (*areCalibrated)(void);
  bool (*manufacturingTest)(void);
  void (*acquire)(sensorData_t *sensors);
  void (*waitDataReady)(void);
  bool (*readGyro)(Axis3f *gyro);
  bool (*readAcc)(Axis3f *acc);
  bool (*readMag)(Axis3f *mag);
  bool (*readBaro)(baro_t *baro);
  void (*setAccMode)(accModes accMode);
  void (*dataAvailableCallback)(void);
} sensorsImplementation_t;

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-function"
static void nullFunction(void) {}
#pragma GCC diagnostic pop

static const sensorsImplementation_t sensorImplementations[SensorImplementation_COUNT] = {

//#ifdef CONFIG_SENSORS_MPU9250_BMP280
//  {
//    .implements = SensorImplementation_mpu9250_bmp280,
//    .init = sensorsMpu9250Bmp280Init,
//    .test = sensorsMpu9250Bmp280Test,
//    .areCalibrated = sensorsMpu9250Bmp280AreCalibrated,
//    .manufacturingTest = sensorsMpu9250Bmp280ManufacturingTest,
//    .acquire = sensorsMpu9250Bmp280Acquire,
//    .waitDataReady = sensorsMpu9250Bmp280WaitDataReady,
//    .readGyro = sensorsMpu9250Bmp280ReadGyro,
//    .readAcc = sensorsMpu9250Bmp280ReadAcc,
//    .readMag = sensorsMpu9250Bmp280ReadMag,
//    .readBaro = sensorsMpu9250Bmp280ReadBaro,
//    .setAccMode = sensorsMpu9250Bmp280SetAccMode,
//    .dataAvailableCallback = nullFunction,
//  },
//#endif

#ifdef CONFIG_SENSORS_MPU6500_BMP280
  {
    .implements = SensorImplementation_mpu6500_bmp280,
    .init = sensorsMpu6500Bmp280Init,
    .test = sensorsMpu6500Bmp280Test,
    .areCalibrated = sensorsMpu6500Bmp280AreCalibrated,
    .manufacturingTest = sensorsMpu6500Bmp280ManufacturingTest,
    .acquire = sensorsMpu6500Bmp280Acquire,
    .waitDataReady = sensorsMpu6500Bmp280WaitDataReady,
    .readGyro = sensorsMpu6500Bmp280ReadGyro,
    .readAcc = sensorsMpu6500Bmp280ReadAcc,
    .readMag = sensorsMpu6500Bmp280ReadMag,
    .readBaro = sensorsMpu6500Bmp280ReadBaro,
    .setAccMode = sensorsMpu6500Bmp280SetAccMode,
    .dataAvailableCallback = nullFunction,
  },
#endif

};

static const sensorsImplementation_t* activeImplementation;
static bool isInit = false;
static const sensorsImplementation_t* findImplementation(SensorImplementation_t implementation);

void sensorsInit(void) {
  if (isInit) {
    return;
  }

#ifndef SENSORS_FORCE
  SensorImplementation_t sensorImplementation = platformConfigGetSensorImplementation();
#else
  SensorImplementation_t sensorImplementation = SENSORS_FORCE;
  DEBUG_PRINT("Forcing sensors to " xstr(SENSORS_FORCE) "\n");
#endif
//run = 1;//JH

  activeImplementation = findImplementation(sensorImplementation);
//  run = 1;//JH

  activeImplementation->init();
//  run = 1; // NJH

  isInit = true;
}
bool sensorsTest(void) {
  return activeImplementation->test();
}

bool sensorsAreCalibrated(void) {
  return activeImplementation->areCalibrated();
}

bool sensorsManufacturingTest(void){
  return activeImplementation->manufacturingTest;
}

void sensorsAcquire(sensorData_t *sensors) {
  activeImplementation->acquire(sensors);
}

void sensorsWaitDataReady(void) {
  activeImplementation->waitDataReady();
}

bool sensorsReadGyro(Axis3f *gyro) {
  return activeImplementation->readGyro(gyro);
}

bool sensorsReadAcc(Axis3f *acc) {
  return activeImplementation->readAcc(acc);
}

bool sensorsReadMag(Axis3f *mag) {
  return activeImplementation->readMag(mag);
}

bool sensorsReadBaro(baro_t *baro) {
  return activeImplementation->readBaro(baro);
}

void sensorsSetAccMode(accModes accMode) {
  activeImplementation->setAccMode(accMode);
}

void __attribute__((used)) EXTI1_Callback(void) {
  activeImplementation->dataAvailableCallback();
}

static const sensorsImplementation_t* findImplementation(SensorImplementation_t implementation) {
  const sensorsImplementation_t* result = 0;

  for (int i = 0; i < SensorImplementation_COUNT; i++) {
    if (sensorImplementations[i].implements == implementation) {
      result = &sensorImplementations[i];
      break;
    }
  }

  return result;
}
