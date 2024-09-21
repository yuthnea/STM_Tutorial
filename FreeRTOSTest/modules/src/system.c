/*
 * system.c
 *
 *  Created on: Aug 27, 2024
 *      Author: Admin
 */

#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

#include "config.h"

#include "system.h"
#include "platform.h"
#include "worker.h"
#include "static_mem.h"
#include "cfassert.h"

#include "stabilizer.h"
#include "estimator_kalman.h"

#include "flow.h"
#include "tof.h"
#include "zranger2.h"

#include "i2c_drv.h"
#include "spi_drv.h"
#include "timer_drv.h"
#include "uart_drv.h"


#include "led.h"
#include "flowdeck.h"

uint32_t counter = 0;
static uint8_t flage =0;
static bool isInit;


STATIC_MEM_TASK_ALLOC(systemTask, SYSTEM_TASK_STACKSIZE);

xSemaphoreHandle canStartMutex;
static StaticSemaphore_t canStartMutexBuffer;


static void systemTask(void *arg);


void systemLaunch(void)
{
  STATIC_MEM_TASK_CREATE(systemTask, systemTask, SYSTEM_TASK_NAME, NULL, SYSTEM_TASK_PRI);
}
void systemInit(void)
{

	if (isInit) return;

	canStartMutex = xSemaphoreCreateMutexStatic(&canStartMutexBuffer);
	xSemaphoreTake(canStartMutex, portMAX_DELAY);

	workerInit();

	isInit = true;
}
bool systemTest(void)
{
	bool pass=isInit;
	pass &= workerTest();

	return pass;
}
void systemTask(void *arg) {
	bool pass = true;
//	counter += 1; // JUMP HERE
	ledInit();
//	for (uint16_t i = 0; i < 3000; i++) {
//		if (i % 10 == 0){
//			HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
//		}
//		vTaskDelay(1);
//	}
	usecTimerInit();
	I2C1_Init();
	I2C2_Init();

	SPI2_Init();
	SPI3_Init();
	spi1_init();

//	MX_UART4_Init();
//	MX_USART1_UART_Init();
//	MX_USART2_UART_Init();
//	MX_USART3_UART_Init();

	systemInit();
//	counter +=1 ; // JUMP HERE

	StateEstimatorType estimator = StateEstimatorTypeAutoSelect;
	//Macro-Work when we defind its
#ifdef CONFIG_ESTIMATOR_KALMAN_ENABLE_TEST
//	counter = 1;
	estimatorKalmanTaskInit();
//	counter = 2;
	//JH
#endif
	zRanger2Init();
	//Test LED
	ledblink_test();

//	counter += 1; // JUMP HERE
//	flowdeck1Init();
//	counter +=1; // Not JUMP HERE
//	flowTofInit();
//	tofInit();

//	estimator = deckGetRequiredEstimator();
	stabilizerInit(estimator);
//	counter +=1 ;// NJH
	if (systemTest() == false) {
		pass = false;
	}

	if ( stabilizerTest() == false )
	{
		pass = false;
	}

#ifdef CONFIG_ESTIMATOR_KALMAN_ENABLE_TEST
//	counter = 3;
	//NJH
if (estimatorKalmanTaskTest() == false) {
//	counter = 1;
	//NJH
  pass = false;
}
#endif

	vTaskDelay(100);
	ledSet(1);
	if (pass) {
		systemStart();
	}
	vTaskDelay(100);
	workerLoop();
	while(1)
	{

		vTaskDelay(1000);
	}
}
void systemStart()
{
	xSemaphoreGive(canStartMutex);
}
void systemWaitStart(void)
{
//	flage = 2;
	while (!isInit) vTaskDelay(2);
//	flage = 2; // nan JUMP HERE
	xSemaphoreTake(canStartMutex, portMAX_DELAY);
	xSemaphoreGive(canStartMutex);
}


void vApplicationIdleHook(void) {

	static uint32_t tickOfLatestWatchdogReset = M2T(0);

	portTickType tickCount = xTaskGetTickCount();

	if (tickCount - tickOfLatestWatchdogReset > M2T(80)) {
		tickOfLatestWatchdogReset = tickCount;
//		watchdogReset();
	}

}



#if ( configCHECK_FOR_STACK_OVERFLOW > 0 )

    void vApplicationStackOverflowHook( TaskHandle_t xTask,
                                        char * pcTaskName )
    {
        /* Check pcTaskName for the name of the offending task,
         * or pxCurrentTCB if pcTaskName has itself been corrupted. */
        ( void ) xTask;
        ( void ) pcTaskName;
    }

#endif /* #if ( configCHECK_FOR_STACK_OVERFLOW > 0 ) */

void vApplicationMallocFailedHook( void ){
	while(1);
}
