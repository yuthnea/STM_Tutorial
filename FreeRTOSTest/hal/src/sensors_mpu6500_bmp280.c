/*
 * sensors_mpu6500_bmp280.c
 *
 *  Created on: Sep 17, 2024
 *      Author: AI FARM
 */

#include <FreeRTOS.h>
#include <task.h>
#include <queue.h>
#include <semphr.h>

#include "sensors_mpu6500_bmp280.h"
#include "mpu6500.h"
#include "bmp280.h"

#include "stm32f4xx_hal.h"
#include "nvicconf.h"
#include "math.h"

#include "estimator.h"
#include "system.h"
#include "static_mem.h"
#include "usec_time.h"
#include "filter.h"
#include "i2c_drv.h"
#include "led.h"

#define MPU6500_G_PER_LSB_16     (float)((2 * 16) / 65536.0)
#define MPU6500_DEG_PER_LSB_2000 (float)((2 * 2000.0) / 65536.0)

#define MPU6500_ACCEL_FS_16         0x03
#define MPU6500_GYRO_FS_2000        0x03

#define SENSORS_GYRO_FS_CFG       MPU6500_GYRO_FS_2000
#define SENSORS_DEG_PER_LSB_CFG   MPU6500_DEG_PER_LSB_2000

#define SENSORS_ACCEL_FS_CFG      MPU6500_ACCEL_FS_16
#define SENSORS_G_PER_LSB_CFG     MPU6500_G_PER_LSB_16

#define SENSORS_VARIANCE_MAN_TEST_TIMEOUT M2T(2000) // Timeout in ms
#define SENSORS_MAN_TEST_LEVEL_MAX        5.0f      // Max degrees off

#define SENSORS_BIAS_SAMPLES       1000
#define SENSORS_ACC_SCALE_SAMPLES  200
#define SENSORS_GYRO_BIAS_CALCULATE_STDDEV

// Buffer length for MPU6500 slave reads
#define SENSORS_MPU6500_BUFF_LEN    14
#define SENSORS_MAG_BUFF_LEN        8
#define SENSORS_BARO_BUFF_S_P_LEN   4
#define SENSORS_BARO_BUFF_T_LEN     2
#define SENSORS_BARO_BUFF_LEN       (SENSORS_BARO_BUFF_S_P_LEN + SENSORS_BARO_BUFF_T_LEN)

#define GYRO_NBR_OF_AXES            3
#define GYRO_MIN_BIAS_TIMEOUT_MS    M2T(1*1000)
// Number of samples used in variance calculation. Changing this effects the threshold
#define SENSORS_NBR_OF_BIAS_SAMPLES     1024
// Variance threshold to take zero bias for gyro
#define GYRO_VARIANCE_BASE          50
#define GYRO_VARIANCE_THRESHOLD_X   (GYRO_VARIANCE_BASE)
#define GYRO_VARIANCE_THRESHOLD_Y   (GYRO_VARIANCE_BASE)
#define GYRO_VARIANCE_THRESHOLD_Z   (GYRO_VARIANCE_BASE)

uint8_t stand = 0;

typedef struct
{
  Axis3f     bias;
  Axis3f     variance;
  Axis3f     mean;
  bool       isBiasValueFound;
  bool       isBufferFilled;
  Axis3i16*  bufHead;
  Axis3i16   buffer[SENSORS_NBR_OF_BIAS_SAMPLES];
} BiasObj;


static xQueueHandle accelerometerDataQueue;
STATIC_MEM_QUEUE_ALLOC(accelerometerDataQueue, 1, sizeof(Axis3f));
static xQueueHandle gyroDataQueue;
STATIC_MEM_QUEUE_ALLOC(gyroDataQueue, 1, sizeof(Axis3f));
static xQueueHandle magnetometerDataQueue;
STATIC_MEM_QUEUE_ALLOC(magnetometerDataQueue, 1, sizeof(Axis3f));
static xQueueHandle barometerDataQueue;
STATIC_MEM_QUEUE_ALLOC(barometerDataQueue, 1, sizeof(baro_t));


static xSemaphoreHandle sensorsDataReady;
static StaticSemaphore_t sensorsDataReadyBuffer;
static xSemaphoreHandle dataReady;
static StaticSemaphore_t dataReadyBuffer;

static bool isInit = false;
static sensorData_t sensorData;
static volatile uint64_t imuIntTimestamp;


static Axis3i16 gyroRaw;
static Axis3i16 accelRaw;
NO_DMA_CCM_SAFE_ZERO_INIT static BiasObj gyroBiasRunning;
static Axis3f gyroBias;
static Axis3f accBias;

static bool    gyroBiasFound = false;
static float accScaleSum = 0;
static float accScale = 1;

// Low Pass filtering
#define GYRO_LPF_CUTOFF_FREQ  80
#define ACCEL_LPF_CUTOFF_FREQ 30
static lpf2pData accLpf[3];
static lpf2pData gyroLpf[3];
static void applyAxis3fLpf(lpf2pData *data, Axis3f* in);

static bool isBarometerPresent = false;
static bool isMagnetometerPresent = false;

static bool isMpu6500TestPassed = false;
//static bool isAK8963TestPassed = false;
//static bool isBMP280TestPassed = false;

// IMU alignment Euler angles
static float imuPhi = 0.0f;
static float imuTheta = 0.0f;
static float imuPsi = 0.0f;

static float R[3][3];
// Pre-calculated values for accelerometer alignment
//static float cosPitch = 1.0;
//static float sinPitch = 0.0;
//static float cosRoll = 1.0;
//static float sinRoll = 0.0;


static mpu6500_t imu;
static void processAccGyroMeasurements();
static void processBarometerMeasurements();


static bool processGyroBias(int16_t gx, int16_t gy, int16_t gz,  Axis3f *gyroBiasOut);

static bool processAccScale(int16_t ax, int16_t ay, int16_t az);
static void sensorsBiasObjInit(BiasObj* bias);
static void sensorsCalculateVarianceAndMean(BiasObj* bias, Axis3f* varOut, Axis3f* meanOut);
static void sensorsAddBiasValue(BiasObj* bias, int16_t x, int16_t y, int16_t z);
static bool sensorsFindBiasValue(BiasObj* bias);
static void sensorsAlignToAirframe(Axis3f* in, Axis3f* out);
//static void sensorsAccAlignToGravity(Axis3f* in, Axis3f* out);


static uint8_t mpuID;
static int sysCounter;
static int intCounter;
static bool check;
static uint8_t bmpID;

static float press;
static float asl;
static float gx,gy,gz;
static float ax,ay,az;


STATIC_MEM_TASK_ALLOC(sensorsTask, SENSORS_TASK_STACKSIZE);


bool sensorsMpu6500Bmp280ReadGyro(Axis3f *gyro)
{
	return (pdTRUE == xQueueReceive(gyroDataQueue, gyro, 0));
}
bool sensorsMpu6500Bmp280ReadAcc(Axis3f *acc)
{
	return (pdTRUE == xQueueReceive(accelerometerDataQueue, acc, 0));
}
bool sensorsMpu6500Bmp280ReadMag(Axis3f *mag)
{
	return (pdTRUE == xQueueReceive(magnetometerDataQueue, mag, 0));
}
bool sensorsMpu6500Bmp280ReadBaro(baro_t *baro)
{
	return (pdTRUE == xQueueReceive(barometerDataQueue, baro, 0));
}
void sensorsMpu6500Bmp280Acquire(sensorData_t *sensors)
{
	sensorsReadGyro(&sensors->gyro);
	sensorsReadAcc(&sensors->acc);
	sensorsReadMag(&sensors->mag);
	sensorsReadBaro(&sensors->baro);
	sensors->interruptTimestamp = sensorData.interruptTimestamp;
}
bool sensorsMpu6500Bmp280AreCalibrated(void)
{
	return gyroBiasFound;
}

static void sensorsTask(void *param)
{
	measurement_t measurement;
	vTaskDelay(10);

	systemWaitStart();

	while (1) {


	    if (pdTRUE == xSemaphoreTake(sensorsDataReady, portMAX_DELAY))
	    {
	    	sensorData.interruptTimestamp = imuIntTimestamp;

	    	sysCounter++;
	    	mpu6500GetAccelGyroData(&imu);
	    	processAccGyroMeasurements();
	    	if (isBarometerPresent)
	    	{
	    		processBarometerMeasurements();

	    	}

	        measurement.type = MeasurementTypeAcceleration;
	        measurement.data.acceleration.acc = sensorData.acc;
	        ax = sensorData.acc.x;
	        ay = sensorData.acc.y;
	        az = sensorData.acc.z;
	        estimatorEnqueue(&measurement);
	        xQueueOverwrite(accelerometerDataQueue, &sensorData.acc);

	        measurement.type = MeasurementTypeGyroscope;
	        measurement.data.gyroscope.gyro = sensorData.gyro;
	        gx = sensorData.gyro.x;
	        gy = sensorData.gyro.y;
	        gz = sensorData.gyro.z;
	        estimatorEnqueue(&measurement);
	        xQueueOverwrite(gyroDataQueue, &sensorData.gyro);

			if (isBarometerPresent) {
				measurement.type = MeasurementTypeBarometer;
				measurement.data.barometer.baro = sensorData.baro;
				press = sensorData.baro.pressure;
				asl = sensorData.baro.asl;
				estimatorEnqueue(&measurement);
				xQueueOverwrite(barometerDataQueue, &sensorData.baro);
			}

	    	xSemaphoreGive(dataReady);
	    }
	}

}
void sensorsMpu6500Bmp280WaitDataReady(void)
{
	xSemaphoreTake(dataReady, portMAX_DELAY);
}
void processAccGyroMeasurements()
{
	Axis3f gyroScaledIMU;
	Axis3f accScaledIMU;
//	Axis3f accScaled;
	accelRaw.x = ((int16_t) imu.buf[0] << 8 | imu.buf[1]);
	accelRaw.y = ((int16_t) imu.buf[2] << 8 | imu.buf[3]);
	accelRaw.z = ((int16_t) imu.buf[4] << 8 | imu.buf[5]);
	gyroRaw.x = ((int16_t) imu.buf[8] << 8 | imu.buf[9]);
	gyroRaw.y = ((int16_t) imu.buf[10] << 8 | imu.buf[11]);
	gyroRaw.z = ((int16_t) imu.buf[12] << 8 | imu.buf[13]);

	gyroBiasFound = processGyroBias(gyroRaw.x, gyroRaw.y, gyroRaw.z, &gyroBias);

	if (gyroBiasFound) {
		processAccScale(accelRaw.x, accelRaw.y, accelRaw.z);
	}

	gyroScaledIMU.x = -(gyroRaw.x - gyroBias.x) * SENSORS_DEG_PER_LSB_CFG;
	gyroScaledIMU.y = (gyroRaw.y - gyroBias.y) * SENSORS_DEG_PER_LSB_CFG;
	gyroScaledIMU.z = (gyroRaw.z - gyroBias.z) * SENSORS_DEG_PER_LSB_CFG;
	sensorsAlignToAirframe(&gyroScaledIMU, &sensorData.gyro);
	applyAxis3fLpf((lpf2pData*) (&gyroLpf), &sensorData.gyro);

	accScaledIMU.x = -(accelRaw.x - accBias.x) * SENSORS_G_PER_LSB_CFG / accScale;
	accScaledIMU.y = (accelRaw.y - accBias.y) * SENSORS_G_PER_LSB_CFG / accScale;
	accScaledIMU.z = (accelRaw.z) * SENSORS_G_PER_LSB_CFG / accScale;
	sensorsAlignToAirframe(&accScaledIMU, &sensorData.acc);
//	sensorsAccAlignToGravity(&accScaled, &sensorData.acc);
	applyAxis3fLpf((lpf2pData*) (&accLpf), &sensorData.acc);


}
static void processBarometerMeasurements()
{
	float pressure, temperature,asl;
	bmp280GetData(&pressure, &temperature, &asl);

	sensorData.baro.pressure = pressure / 100.0f;
	sensorData.baro.temperature = temperature;
	sensorData.baro.asl = bmp280PressureToAltitude(&sensorData.baro.pressure);
}
static void sensorsDeviceInit(void)
{
	isMagnetometerPresent = false;
	isBarometerPresent = false;
	TickType_t xStartTime = 0;
	vTaskDelayUntil(&xStartTime, T2M(1000));
//	stand = 1;// JH

	if ( mpu6500TestConnection() == false ){
//		stand = 1;//NJH
		while(1);
	}
	vTaskDelay(100);
//	stand = 1;// NJH
	mpu6500Init();
//	stand = 1;// NJH

	vTaskDelay(100);
	for (uint8_t i = 0; i < 3; i++) {
		lpf2pInit(&gyroLpf[i], 1000, GYRO_LPF_CUTOFF_FREQ);
		lpf2pInit(&accLpf[i], 1000, ACCEL_LPF_CUTOFF_FREQ);
	}

	vTaskDelay(10);
	bmp280Init();
	if (bmp280TestConnection() == true){
		isBarometerPresent = true;
	}
	else{
		isBarometerPresent = false;
		while(1);
	}
	vTaskDelay(10);

}
static void sensorsTaskInit(void)
{
	accelerometerDataQueue = STATIC_MEM_QUEUE_CREATE(accelerometerDataQueue);
	gyroDataQueue = STATIC_MEM_QUEUE_CREATE(gyroDataQueue);
	magnetometerDataQueue = STATIC_MEM_QUEUE_CREATE(magnetometerDataQueue);
	barometerDataQueue = STATIC_MEM_QUEUE_CREATE(barometerDataQueue);

	STATIC_MEM_TASK_CREATE(sensorsTask, sensorsTask, SENSORS_TASK_NAME, NULL, SENSORS_TASK_PRI);

}

static void sensorsInterruptInit(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	__HAL_RCC_GPIOA_CLK_ENABLE();

	sensorsDataReady = xSemaphoreCreateBinaryStatic(&sensorsDataReadyBuffer);
	dataReady = xSemaphoreCreateBinaryStatic(&dataReadyBuffer);


	GPIO_InitStruct.Pin = GPIO_PIN_1;
	GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	/* EXTI interrupt init*/
	HAL_NVIC_SetPriority(EXTI1_IRQn, 7, 0);
	HAL_NVIC_EnableIRQ(EXTI1_IRQn);
}

void sensorsMpu6500Bmp280Init(void)
{
	if (isInit) {
		return;
	}
	sensorsBiasObjInit(&gyroBiasRunning);
//	stand = 1;//JH

	sensorsDeviceInit();
//	stand = 1;//NJH

	sensorsInterruptInit();
	sensorsTaskInit();

	isInit = true;
}
bool sensorsMpu6500Bmp280Test(void)
{
	  bool testStatus = true;

	  if (!isInit)
	  {
	    testStatus = false;
	  }

	  // Try for 3 seconds so the quad has stabilized enough to pass the test
	  for (int i = 0; i < 300; i++)
	  {
	    if(mpu6500SelfTest() == true)
	    {
	    	isMpu6500TestPassed = true;
	      break;
	    }
	    else
	    {
	      vTaskDelay(M2T(10));
	    }
	  }
	  testStatus &= isMpu6500TestPassed;

	#ifdef SENSORS_ENABLE_MAG_AK8963
	  testStatus &= isMagnetometerPresent;
	  if (testStatus)
	  {
	    isAK8963TestPassed = ak8963SelfTest();
	    testStatus = isAK8963TestPassed;
	  }
	#endif

	#ifdef SENSORS_ENABLE_PRESSURE_LPS25H
	  testStatus &= isBarometerPresent;
	  if (testStatus)
	  {
	    isLPS25HTestPassed = lps25hSelfTest();
	    testStatus = isLPS25HTestPassed;
	  }
	#endif

	  return true;
//	  return testStatus;
}

static bool processAccScale(int16_t ax, int16_t ay, int16_t az)
{
  static bool accBiasFound = false;
  static uint32_t accScaleSumCount = 0;
  static int64_t accSum[GYRO_NBR_OF_AXES] = {0};


  if (!accBiasFound)
  {
    accScaleSum += sqrtf(powf(ax * SENSORS_G_PER_LSB_CFG, 2) + powf(ay * SENSORS_G_PER_LSB_CFG, 2) + powf(az * SENSORS_G_PER_LSB_CFG, 2));
    accScaleSumCount++;
    accSum[0] += ax;
    accSum[1] += ay;
    accSum[2] += az;

    if (accScaleSumCount == SENSORS_ACC_SCALE_SAMPLES)
    {
      accScale = accScaleSum / SENSORS_ACC_SCALE_SAMPLES;
      accBias.x = (float) accSum[0] / SENSORS_ACC_SCALE_SAMPLES;
      accBias.y = (float) accSum[1] / SENSORS_ACC_SCALE_SAMPLES;
      accBias.z = (float) accSum[2] / SENSORS_ACC_SCALE_SAMPLES;
      accBiasFound = true;
    }
  }

  return accBiasFound;
}
static bool processGyroBias(int16_t gx, int16_t gy, int16_t gz,  Axis3f *gyroBiasOut)
{
	sensorsAddBiasValue(&gyroBiasRunning, gx, gy, gz);

	if (!gyroBiasRunning.isBiasValueFound)
	{
		sensorsFindBiasValue(&gyroBiasRunning);
	}

	gyroBiasOut->x = gyroBiasRunning.bias.x;
	gyroBiasOut->y = gyroBiasRunning.bias.y;
	gyroBiasOut->z = gyroBiasRunning.bias.z;

	return gyroBiasRunning.isBiasValueFound;
}
static void sensorsBiasObjInit(BiasObj* bias)
{
  bias->isBufferFilled = false;
  bias->bufHead = bias->buffer;
}

static void sensorsCalculateVarianceAndMean(BiasObj* bias, Axis3f* varOut, Axis3f* meanOut)
{
  uint32_t i;
  int64_t sum[GYRO_NBR_OF_AXES] = {0};
  int64_t sumSq[GYRO_NBR_OF_AXES] = {0};

  for (i = 0; i < SENSORS_NBR_OF_BIAS_SAMPLES; i++)
  {
		sum[0] += bias->buffer[i].x;
		sum[1] += bias->buffer[i].y;
		sum[2] += bias->buffer[i].z;
		sumSq[0] += bias->buffer[i].x * bias->buffer[i].x;
		sumSq[1] += bias->buffer[i].y * bias->buffer[i].y;
		sumSq[2] += bias->buffer[i].z * bias->buffer[i].z;

  }



  meanOut->x = (float) sum[0] / SENSORS_NBR_OF_BIAS_SAMPLES;
  meanOut->y = (float) sum[1] / SENSORS_NBR_OF_BIAS_SAMPLES;
  meanOut->z = (float) sum[2] / SENSORS_NBR_OF_BIAS_SAMPLES;

  varOut->x = sumSq[0] / SENSORS_NBR_OF_BIAS_SAMPLES - meanOut->x * meanOut->x;
  varOut->y = sumSq[1] / SENSORS_NBR_OF_BIAS_SAMPLES - meanOut->y * meanOut->y;
  varOut->z = sumSq[2] / SENSORS_NBR_OF_BIAS_SAMPLES - meanOut->z * meanOut->z;
}
static void __attribute__((used)) sensorsCalculateBiasMean(BiasObj* bias, Axis3i32* meanOut)
{
  uint32_t i;
  int32_t sum[GYRO_NBR_OF_AXES] = {0};

  for (i = 0; i < SENSORS_NBR_OF_BIAS_SAMPLES; i++)
  {
    sum[0] += bias->buffer[i].x;
    sum[1] += bias->buffer[i].y;
    sum[2] += bias->buffer[i].z;
  }

  meanOut->x = sum[0] / SENSORS_NBR_OF_BIAS_SAMPLES;
  meanOut->y = sum[1] / SENSORS_NBR_OF_BIAS_SAMPLES;
  meanOut->z = sum[2] / SENSORS_NBR_OF_BIAS_SAMPLES;
}
static void sensorsAddBiasValue(BiasObj* bias, int16_t x, int16_t y, int16_t z)
{
  bias->bufHead->x = x;
  bias->bufHead->y = y;
  bias->bufHead->z = z;
  bias->bufHead++;

  if (bias->bufHead >= &bias->buffer[SENSORS_NBR_OF_BIAS_SAMPLES])
  {
    bias->bufHead = bias->buffer;
    bias->isBufferFilled = true;
  }
}
static bool sensorsFindBiasValue(BiasObj* bias)
{
  static int32_t varianceSampleTime;
  bool foundBias = false;

  if (bias->isBufferFilled)
  {
    sensorsCalculateVarianceAndMean(bias, &bias->variance, &bias->mean);

    if (bias->variance.x < GYRO_VARIANCE_THRESHOLD_X &&
        bias->variance.y < GYRO_VARIANCE_THRESHOLD_Y &&
        bias->variance.z < GYRO_VARIANCE_THRESHOLD_Z &&
        (varianceSampleTime + GYRO_MIN_BIAS_TIMEOUT_MS < xTaskGetTickCount()))
    {
      varianceSampleTime = xTaskGetTickCount();
      bias->bias.x = bias->mean.x;
      bias->bias.y = bias->mean.y;
      bias->bias.z = bias->mean.z;
      foundBias = true;
      bias->isBiasValueFound = true;
    }
  }

  return foundBias;
}

bool sensorsMpu6500Bmp280ManufacturingTest(void)
{
	bool testStatus = false;
	Axis3i16 g;
	Axis3i16 a;
	Axis3f acc;  // Accelerometer axis data in mG
	float pitch, roll;
	uint32_t startTick = xTaskGetTickCount();

	testStatus = mpu6500SelfTest();
	if (testStatus)
	{
		sensorsBiasObjInit(&gyroBiasRunning);
		while (xTaskGetTickCount() - startTick < SENSORS_VARIANCE_MAN_TEST_TIMEOUT)
		{
			mpu6500GetMotion6(&a.y, &a.x, &a.z, &g.y, &g.x, &g.z);
			if (processGyroBias(g.x, g.y, g.z, &gyroBias))
			{
				gyroBiasFound = true;
				break;
			}
		}

		if (gyroBiasFound) {
			acc.x = -(a.x) * SENSORS_G_PER_LSB_CFG;
			acc.y = (a.y) * SENSORS_G_PER_LSB_CFG;
			acc.z = (a.z) * SENSORS_G_PER_LSB_CFG;

			// Calculate pitch and roll based on accelerometer. Board must be level
			pitch = tanf(-acc.x / (sqrtf(acc.y * acc.y + acc.z * acc.z)))
					* 180/(float) M_PI;
			roll = tanf(acc.y / acc.z) * 180 / (float) M_PI;

			if ((fabsf(roll) < SENSORS_MAN_TEST_LEVEL_MAX) && (fabsf(pitch) < SENSORS_MAN_TEST_LEVEL_MAX))
			{
				testStatus = true;
			}
			else
			{
				testStatus = false;
			}
		} else {

			testStatus = false;
		}
	}

	return testStatus;

}

static void __attribute__((used)) EXTI1_IRQHandler(void)
{

	portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;
	imuIntTimestamp = usecTimestamp();
    // Check if EXTI line 1 triggered the interrupt
    if (__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_1) != RESET)
    {
        // Clear the interrupt flag
        __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_1);
    	xSemaphoreGiveFromISR(sensorsDataReady, &xHigherPriorityTaskWoken);
    }

	intCounter++;
	if (xHigherPriorityTaskWoken) {
		portYIELD();
	}

}

static void sensorsAlignToAirframe(Axis3f* in, Axis3f* out)
{
  // IMU alignment
  static float sphi, cphi, stheta, ctheta, spsi, cpsi;

  sphi   = sinf(imuPhi * (float) M_PI / 180);
  cphi   = cosf(imuPhi * (float) M_PI / 180);
  stheta = sinf(imuTheta * (float) M_PI / 180);
  ctheta = cosf(imuTheta * (float) M_PI / 180);
  spsi   = sinf(imuPsi * (float) M_PI / 180);
  cpsi   = cosf(imuPsi * (float) M_PI / 180);

  // tait-bryan passive rotation in order: yaw, psi (1) -> pitch, theta (2) ->  roll, phi (3) [https://en.wikipedia.org/wiki/Euler_angles#cite_note-3]
  // mathematically R = R_x(phi)^T . R_y(theta)^T . R_z(psi)^T  [http://eecs.qmul.ac.uk/~gslabaugh/publications/euler.pdf]
  // transpose because it's a passive rotation not active [https://en.wikipedia.org/wiki/Active_and_passive_transformation]
  R[0][0] = ctheta * cpsi;
  R[0][1] = ctheta * spsi;
  R[0][2] = -stheta;
  R[1][0] = sphi * stheta * cpsi - cphi * spsi;
  R[1][1] = sphi * stheta * spsi + cphi * cpsi;
  R[1][2] = sphi * ctheta;
  R[2][0] = cphi * stheta * cpsi + sphi * spsi;
  R[2][1] = cphi * stheta * spsi - sphi * cpsi;
  R[2][2] = cphi * ctheta;

  out->x = in->x*R[0][0] + in->y*R[0][1] + in->z*R[0][2];
  out->y = in->x*R[1][0] + in->y*R[1][1] + in->z*R[1][2];
  out->z = in->x*R[2][0] + in->y*R[2][1] + in->z*R[2][2];
}
//static void sensorsAccAlignToGravity(Axis3f* in, Axis3f* out)
//{
//  Axis3f rx;
//  Axis3f ry;
//
//  // Rotate around x-axis
//  rx.x = in->x;
//  rx.y = in->y * cosRoll - in->z * sinRoll;
//  rx.z = in->y * sinRoll + in->z * cosRoll;
//
//  // Rotate around y-axis
//  ry.x = rx.x * cosPitch - rx.z * sinPitch;
//  ry.y = rx.y;
//  ry.z = -rx.x * sinPitch + rx.z * cosPitch;
//
//  out->x = ry.x;
//  out->y = ry.y;
//  out->z = ry.z;
//}
void sensorsMpu6500Bmp280SetAccMode(accModes accMode)
{
  switch (accMode)
  {
    case ACC_MODE_PROPTEST:
    	mpu6500SetAccelDLPF(MPU6500_ACCEL_DLPF_BW_460);
      for (uint8_t i = 0; i < 3; i++)
      {
        lpf2pInit(&accLpf[i],  1000, 500);
      }
      break;
    case ACC_MODE_FLIGHT:
    default:
    	mpu6500SetAccelDLPF(MPU6500_ACCEL_DLPF_BW_44);
      for (uint8_t i = 0; i < 3; i++)
      {
        lpf2pInit(&accLpf[i],  1000, ACCEL_LPF_CUTOFF_FREQ);
      }
      break;
  }
}
static void applyAxis3fLpf(lpf2pData *data, Axis3f* in)
{
  for (uint8_t i = 0; i < 3; i++) {
    in->axis[i] = lpf2pApply(&data[i], in->axis[i]);
  }
}

