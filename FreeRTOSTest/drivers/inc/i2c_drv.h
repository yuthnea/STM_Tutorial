/*
 * i2c_drv.h
 *
 *  Created on: Aug 29, 2024
 *      Author: Admin
 */

#ifndef INC_I2C_DRV_H_
#define INC_I2C_DRV_H_
#include "main.h"
#include "stdint.h"


extern I2C_HandleTypeDef hi2c1;
extern I2C_HandleTypeDef hi2c2;

void I2C1_Init(void);
void I2C2_Init(void);




#endif /* INC_I2C_DRV_H_ */
