/*
 * i2cdev.c
 *
 *  Created on: Sep 6, 2024
 *      Author: Admin
 */


#include "i2cdev.h"
#include "stdbool.h"


bool i2cdevReadReg16(I2C_HandleTypeDef *dev, uint8_t devAddress, uint16_t memAddress, uint16_t len, uint8_t *data)
{
	UNUSED(dev);
	HAL_StatusTypeDef status;
	status = HAL_I2C_Mem_Read(&hi2c2, devAddress<<1, memAddress, I2C_MEMADD_SIZE_16BIT, data, len, 100);

	if ( status == HAL_OK) return true;
	else return false;
}
bool i2cdevWriteReg16(I2C_HandleTypeDef *dev, uint8_t devAddress, uint16_t memAddress, uint16_t len, uint8_t *data)
{
	UNUSED(dev);
	HAL_StatusTypeDef status;
	status = HAL_I2C_Mem_Write(&hi2c2, devAddress<<1, memAddress, I2C_MEMADD_SIZE_16BIT, data, len, 100);

	if ( status == HAL_OK) return true;
	else return false;
}


