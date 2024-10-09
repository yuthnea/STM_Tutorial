/*
 * QMC5883P.h
 *
 *  Created on: Aug 14, 2023
 *      Author: Admin
 */

#ifndef INC_QMC5883P_H_
#define INC_QMC5883P_H_

#include "stm32f4xx_hal.h"
//#include "i2c.h"
#include "math.h"


#define Q5883P_ADDR			0x2C<<1
#define Q5883P_ID_ADDR		0x00
#define Q5883P_DATA_REG		0x01
#define Q5883P_DATA_READY	0x09
#define Q5883P_CONTR_1		0x0A
#define Q5883P_CONTR_2		0x0B

#define ALPHA				0.002f

typedef struct{
	int16_t qmc_x;
	int16_t qmc_y;
	int16_t qmc_z;
	float compass;
	float heading;
}qmc_typedef;
uint8_t qmc5883p_init();
uint8_t qmc5883p_read(qmc_typedef *qmc);

#endif /* INC_QMC5883P_H_ */
