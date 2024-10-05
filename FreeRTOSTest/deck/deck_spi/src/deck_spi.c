/*
 *    ||          ____  _ __
 * +------+      / __ )(_) /_______________ _____  ___
 * | 0xBC |     / __  / / __/ ___/ ___/ __ `/_  / / _ \
 * +------+    / /_/ / / /_/ /__/ /  / /_/ / / /_/  __/
 *  ||  ||    /_____/_/\__/\___/_/   \__,_/ /___/\___/
 *
 * Crazyflie control firmware
 *
 * Copyright (C) 2015 Bitcraze AB
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
 * deck_spi.c - Deck-API SPI communication implementation
 */
#include "main.h"
#include "deck_spi.h"
#include "config.h"

#include "FreeRTOS.h"
#include "semphr.h"

#include "cfassert.h"
#include "config.h"
#include "nvicconf.h"
#include "spi_drv.h"

uint32_t flate_t = 0;
extern DMA_HandleTypeDef hdma_spi3_rx;
extern DMA_HandleTypeDef hdma_spi3_tx;
extern SPI_HandleTypeDef hspi3;

#define DUMMY_BYTE         0xA5

static bool isInit = false;
HAL_StatusTypeDef status;

static SemaphoreHandle_t txComplete;
static SemaphoreHandle_t rxComplete;
static SemaphoreHandle_t spiMutex;

static void spiDMAInit();

void spiBegin(void)
{
	txComplete = xSemaphoreCreateBinary();
	rxComplete = xSemaphoreCreateBinary();
	spiMutex = xSemaphoreCreateMutex();

	SPI3_Init();
	spiDMAInit();

	isInit = true;
}
static void spiDMAInit()
{
	/* DMA controller clock enable */

/*
 * Do nothing
 *
 */

	__HAL_RCC_DMA1_CLK_ENABLE();

	/* DMA interrupt init */
	/* DMA1_Stream0_IRQn interrupt configuration */
//	HAL_NVIC_SetPriority(DMA1_Stream0_IRQn, 5, 0);
//	HAL_NVIC_EnableIRQ(DMA1_Stream0_IRQn);
	/* DMA1_Stream5_IRQn interrupt configuration */
//	HAL_NVIC_SetPriority(DMA1_Stream5_IRQn, 0, 0);
//	HAL_NVIC_EnableIRQ(DMA1_Stream5_IRQn);
}
bool spiTest(void)
{
  return isInit;
}

bool spiExchange(size_t length, const uint8_t * data_tx, uint8_t * data_rx)
{
  ASSERT_DMA_SAFE(data_tx);
  ASSERT_DMA_SAFE(data_rx);
//  flate_t = 1; //JH
  status = HAL_SPI_Transmit_DMA(&hspi3, data_tx, length);
  status = HAL_SPI_Receive_DMA(&hspi3, data_rx, length);
//  flate_t = 1;//JH
  bool result = (xSemaphoreTake(txComplete, portMAX_DELAY) == pdTRUE) && (xSemaphoreTake(rxComplete, portMAX_DELAY) == pdTRUE);
//  bool result = xSemaphoreTake(txComplete, portMAX_DELAY) == pdTRUE;

//  flate_t = 1;//NJH
  return result;
}

void spiBeginTransaction()
{
  xSemaphoreTake(spiMutex, portMAX_DELAY);
}

void spiEndTransaction()
{
  xSemaphoreGive(spiMutex);
}

//void __attribute__((used)) DMA1_Stream0_IRQHandler(void)
//{
//
//	portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;
//
//	HAL_DMA_IRQHandler(&hdma_spi3_rx);
//
//	xSemaphoreGiveFromISR(rxComplete, &xHigherPriorityTaskWoken);
////	  flate_t = 1;
//	if (xHigherPriorityTaskWoken) {
//		portYIELD();
//	}
//
//}

//void __attribute__((used)) DMA1_Stream5_IRQHandler(void)
//{
//
//	portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;
//
//	HAL_DMA_IRQHandler(&hdma_spi3_tx);
//
//	xSemaphoreGiveFromISR(txComplete, &xHigherPriorityTaskWoken);
////	  flate_t += 1; // JUMP TWO TIME
//	if (xHigherPriorityTaskWoken) {
//		portYIELD();
//	}
//
//
//}
void SPI3_IRQHandler(void)
{

  HAL_SPI_IRQHandler(&hspi3);

}
