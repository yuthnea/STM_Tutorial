/*
 * i2cdev.h
 *
 *  Created on: Sep 6, 2024
 *      Author: Admin
 */

#ifndef INC_I2CDEV_H_
#define INC_I2CDEV_H_

#include <stdint.h>
#include <stdbool.h>
#include "i2c_drv.h"
#include "uart_drv.h"
#include "main.h"


bool i2cdevReadReg16(I2C_HandleTypeDef *dev, uint8_t devAddress, uint16_t memAddress,
               uint16_t len, uint8_t *data);
bool i2cdevWriteReg16(I2C_HandleTypeDef *dev, uint8_t devAddress, uint16_t memAddress,
                   uint16_t len, uint8_t *data);


#endif /* INC_I2CDEV_H_ */
