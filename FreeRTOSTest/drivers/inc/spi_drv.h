/*
 * spi_drv.h
 *
 *  Created on: Sep 2, 2024
 *      Author: Admin
 */

#ifndef INC_SPI_DRV_H_
#define INC_SPI_DRV_H_
#include "main.h"

extern SPI_HandleTypeDef hspi2;
extern SPI_HandleTypeDef hspi3;
extern DMA_HandleTypeDef hdma_spi3_rx;
extern DMA_HandleTypeDef hdma_spi3_tx;

extern SPI_HandleTypeDef hspi1;

void SPI2_Init(void);
void SPI3_Init(void);

void spi1_init(void);

#endif /* INC_SPI_DRV_H_ */
