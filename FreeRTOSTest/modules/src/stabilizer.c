/**
 *    ||          ____  _ __
 * +------+      / __ )(_) /_______________ _____  ___
 * | 0xBC |     / __  / / __/ ___/ ___/ __ `/_  / / _ \
 * +------+    / /_/ / / /_/ /__/ /  / /_/ / / /_/  __/
 *  ||  ||    /_____/_/\__/\___/_/   \__,_/ /___/\___/
 *
 * Crazyflie Firmware
 *
 * Copyright (C) 2011-2022 Bitcraze AB
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, in version 3.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 *
 */
#define DEBUG_MODULE "STAB"

#include <math.h>

#include "FreeRTOS.h"
#include "task.h"

#include "system.h"
#include "platform.h"

#include "stabilizer.h"

#include "sensors.h"


#include "estimator.h"
#include "quatcompress.h"


#include "static_mem.h"
#include "rateSupervisor.h"

static bool isInit;

static uint32_t inToOutLatency;

// State variables for the stabilizer
static setpoint_t setpoint;
static sensorData_t sensorData;
state_t state;
uint8_t skip =0;
//static control_t control;

//static motors_thrust_uncapped_t motorThrustUncapped;
//static motors_thrust_uncapped_t motorThrustBatCompUncapped;
//static motors_thrust_pwm_t motorPwm;

// For scratch storage - never logged or passed to other subsystems.
//static setpoint_t tempSetpoint;

static StateEstimatorType estimatorType;


static rateSupervisor_t rateSupervisorContext;
//static bool rateWarningDisplayed = false;

static struct {
  // position - mm
  int16_t x;
  int16_t y;
  int16_t z;
  // velocity - mm / sec
  int16_t vx;
  int16_t vy;
  int16_t vz;
  // acceleration - mm / sec^2
  int16_t ax;
  int16_t ay;
  int16_t az;
  // compressed quaternion, see quatcompress.h
  int32_t quat;
  // angular velocity - milliradians / sec
  int16_t rateRoll;
  int16_t ratePitch;
  int16_t rateYaw;
} stateCompressed;

static struct {
  // position - mm
  int16_t x;
  int16_t y;
  int16_t z;
  // velocity - mm / sec
  int16_t vx;
  int16_t vy;
  int16_t vz;
  // acceleration - mm / sec^2
  int16_t ax;
  int16_t ay;
  int16_t az;
} setpointCompressed;

STATIC_MEM_TASK_ALLOC(stabilizerTask, STABILIZER_TASK_STACKSIZE);

static void stabilizerTask(void* param);

static void calcSensorToOutputLatency(const sensorData_t *sensorData)
{
  uint64_t outTimestamp = usecTimestamp();
  inToOutLatency = outTimestamp - sensorData->interruptTimestamp;
}

static void compressState()
{
  stateCompressed.x = state.position.x * 1000.0f;
  stateCompressed.y = state.position.y * 1000.0f;
  stateCompressed.z = state.position.z * 1000.0f;

  stateCompressed.vx = state.velocity.x * 1000.0f;
  stateCompressed.vy = state.velocity.y * 1000.0f;
  stateCompressed.vz = state.velocity.z * 1000.0f;

  stateCompressed.ax = state.acc.x * 9.81f * 1000.0f;
  stateCompressed.ay = state.acc.y * 9.81f * 1000.0f;
  stateCompressed.az = (state.acc.z + 1) * 9.81f * 1000.0f;

  float const q[4] = {
    state.attitudeQuaternion.x,
    state.attitudeQuaternion.y,
    state.attitudeQuaternion.z,
    state.attitudeQuaternion.w};
  stateCompressed.quat = quatcompress(q);

  float const deg2millirad = ((float)M_PI * 1000.0f) / 180.0f;
  stateCompressed.rateRoll = sensorData.gyro.x * deg2millirad;
  stateCompressed.ratePitch = -sensorData.gyro.y * deg2millirad;
  stateCompressed.rateYaw = sensorData.gyro.z * deg2millirad;
}

static void compressSetpoint()
{
  setpointCompressed.x = setpoint.position.x * 1000.0f;
  setpointCompressed.y = setpoint.position.y * 1000.0f;
  setpointCompressed.z = setpoint.position.z * 1000.0f;

  setpointCompressed.vx = setpoint.velocity.x * 1000.0f;
  setpointCompressed.vy = setpoint.velocity.y * 1000.0f;
  setpointCompressed.vz = setpoint.velocity.z * 1000.0f;

  setpointCompressed.ax = setpoint.acceleration.x * 1000.0f;
  setpointCompressed.ay = setpoint.acceleration.y * 1000.0f;
  setpointCompressed.az = setpoint.acceleration.z * 1000.0f;
}

void stabilizerInit(StateEstimatorType estimator)
{
  if(isInit)
    return;
//  skip = 1;//JH

  sensorsInit();
//  skip = 1;// NJH

  stateEstimatorInit(estimator);

//  controllerInit(ControllerTypeAutoSelect);
//  powerDistributionInit();
//  motorsInit(platformConfigGetMotorMapping());
//  collisionAvoidanceInit();
  estimatorType = stateEstimatorGetType();
//  skip = 1;
//  controllerType = controllerGetType();

  STATIC_MEM_TASK_CREATE(stabilizerTask, stabilizerTask, STABILIZER_TASK_NAME, NULL, STABILIZER_TASK_PRI);

  isInit = true;
}

bool stabilizerTest(void)
{
  bool pass = true;

//  pass &= sensorsTest();
  pass &= stateEstimatorTest();
//  pass &= controllerTest();
//  pass &= powerDistributionTest();
//  pass &= motorsTest();
//  pass &= collisionAvoidanceTest();

  return pass;
}

//static void batteryCompensation(const motors_thrust_uncapped_t* motorThrustUncapped, motors_thrust_uncapped_t* motorThrustBatCompUncapped)
//{
//  float supplyVoltage = pmGetBatteryVoltage();
//
//  for (int motor = 0; motor < STABILIZER_NR_OF_MOTORS; motor++)
//  {
//    motorThrustBatCompUncapped->list[motor] = motorsCompensateBatteryVoltage(motor, motorThrustUncapped->list[motor], supplyVoltage);
//  }
//}

//static void setMotorRatios(const motors_thrust_pwm_t* motorPwm)
//{
//  motorsSetRatio(MOTOR_M1, motorPwm->motors.m1);
//  motorsSetRatio(MOTOR_M2, motorPwm->motors.m2);
//  motorsSetRatio(MOTOR_M3, motorPwm->motors.m3);
//  motorsSetRatio(MOTOR_M4, motorPwm->motors.m4);
//}

static void updateStateEstimatorAndControllerTypes() {
  if (stateEstimatorGetType() != estimatorType) {
    stateEstimatorSwitchTo(estimatorType);
    estimatorType = stateEstimatorGetType();
  }

//  if (controllerGetType() != controllerType) {
//    controllerInit(controllerType);
//    controllerType = controllerGetType();
//  }
}

//static void logCapWarning(const bool isCapped) {
//  #ifdef CONFIG_LOG_MOTOR_CAP_WARNING
//  static uint32_t nextReportTick = 0;
//
//  if (isCapped) {
//    uint32_t now = xTaskGetTickCount();
//    if (now > nextReportTick) {
//      DEBUG_PRINT("Warning: motor thrust saturated\n");
//      nextReportTick = now + M2T(3000);
//    }
//  }
//  #endif
//}

//static void controlMotors(const control_t* control) {
//  powerDistribution(control, &motorThrustUncapped);
//  batteryCompensation(&motorThrustUncapped, &motorThrustBatCompUncapped);
//  const bool isCapped = powerDistributionCap(&motorThrustBatCompUncapped, &motorPwm);
//  logCapWarning(isCapped);
//  setMotorRatios(&motorPwm);
//}

/* The stabilizer loop runs at 1kHz. It is the
 * responsibility of the different functions to run slower by skipping call
 * (ie. returning without modifying the output structure).
 */
static void stabilizerTask(void* param)
{
  stabilizerStep_t stabilizerStep;
  uint32_t lastWakeTime;
  vTaskSetApplicationTaskTag(0, (void*)TASK_STABILIZER_ID_NBR);

  //Wait for the system to be fully started to start stabilization loop
  systemWaitStart();

//  DEBUG_PRINT("Wait for sensor calibration...\n");

  // Wait for sensors to be calibrated
  lastWakeTime = xTaskGetTickCount();
  while(!sensorsAreCalibrated()) {
    vTaskDelayUntil(&lastWakeTime, F2T(RATE_MAIN_LOOP));
  }
  // Initialize stabilizerStep to something else than 0
  stabilizerStep = 1;


//  DEBUG_PRINT("Starting stabilizer loop\n");
  rateSupervisorInit(&rateSupervisorContext, xTaskGetTickCount(), M2T(1000), 997, 1003, 1);

  while(1) {
    // The sensor should unlock at 1kHz
    sensorsWaitDataReady();

    // update sensorData struct (for logging variables)
    sensorsAcquire(&sensorData);

//    if (healthShallWeRunTest()) {
//      healthRunTests(&sensorData);
//    }
//    else {
      updateStateEstimatorAndControllerTypes();

      stateEstimator(&state, stabilizerStep);

//      const bool areMotorsAllowedToRun = supervisorAreMotorsAllowedToRun();

      // Critical for safety, be careful if you modify this code!
//      crtpCommanderBlock(! areMotorsAllowedToRun);
//
//      if (crtpCommanderHighLevelGetSetpoint(&tempSetpoint, &state, stabilizerStep)) {
//        commanderSetSetpoint(&tempSetpoint, COMMANDER_PRIORITY_HIGHLEVEL);
//      }
//      commanderGetSetpoint(&setpoint, &state);

      // Critical for safety, be careful if you modify this code!
      // Let the supervisor update it's view of the current situation
//      supervisorUpdate(&sensorData, &setpoint, stabilizerStep);

      // Let the collision avoidance module modify the setpoint, if needed
//      collisionAvoidanceUpdateSetpoint(&setpoint, &sensorData, &state, stabilizerStep);

      // Critical for safety, be careful if you modify this code!
      // Let the supervisor modify the setpoint to handle exceptional conditions
//      supervisorOverrideSetpoint(&setpoint);
//
//      controller(&control, &setpoint, &sensorData, &state, stabilizerStep);

      // Critical for safety, be careful if you modify this code!
      // The supervisor will already set thrust to 0 in the setpoint if needed, but to be extra sure prevent motors from running.
//      if (areMotorsAllowedToRun) {
//        controlMotors(&control);
//      } else {
//        motorsStop();
//      }

      // Compute compressed log formats
      compressState();
      compressSetpoint();

#ifdef CONFIG_DECK_USD
      // Log data to uSD card if configured
      if (usddeckLoggingEnabled()
          && usddeckLoggingMode() == usddeckLoggingMode_SynchronousStabilizer
          && RATE_DO_EXECUTE(usddeckFrequency(), stabilizerStep)) {
        usddeckTriggerLogging();
      }
#endif
      calcSensorToOutputLatency(&sensorData);
      stabilizerStep++;

//      STATS_CNT_RATE_EVENT(&stabilizerRate);

//      if (!rateSupervisorValidate(&rateSupervisorContext, xTaskGetTickCount())) {
//        if (!rateWarningDisplayed) {
//          DEBUG_PRINT("WARNING: stabilizer loop rate is off (%lu)\n", rateSupervisorLatestCount(&rateSupervisorContext));
//          rateWarningDisplayed = true;
//        }
//      }
//    }
#ifdef CONFIG_MOTORS_ESC_PROTOCOL_DSHOT
    motorsBurstDshot();
#endif
  }
}


