/*
 * bmp280.h
 *
 *  Created on: Sep 2, 2024
 *      Author: Admin
 */

#ifndef INC_BMP280_H_
#define INC_BMP280_H_

#include <stdbool.h>
#include "spi_drv.h"

#define BMP280_TEMP_REG_DATA		0xFA
#define BMP280_PRESSURE_REG_DAT 	0xF7

#define BMP280_REG_ID		0xD0
#define BMP280_REG_CONFIG	0xF5
#define BMP280_REG_CTRL		0xF4
#define BMP280_REG_STATUS	0xF3
#define BMP280_REG_RESET	0xE0


#define DIG_T1				0x88
#define DIG_T2				0x8A
#define DIG_T3				0x8C

#define DIG_P1				0x8E
#define DIG_P2				0x90
#define DIG_P3				0x92
#define DIG_P4				0x94
#define DIG_P5				0x96
#define DIG_P6				0x98
#define DIG_P7				0x9A
#define DIG_P8				0x9C
#define DIG_P9				0x9E

#define TEMP_16BIT_RES		1
#define TEMP_17BIT_RES		2
#define TEMP_18BIT_RES		3
#define TEMP_19BIT_RES		4
#define TEMP_20BIT_RES		5

#define PRES_16BIT_RES		1
#define PRES_17BIT_RES		2
#define PRES_18BIT_RES		3
#define PRES_19BIT_RES		4
#define PRES_20BIT_RES		5

#define BMP280_SLEEP_MODE	0
#define BMP280_FORCED_MODE	1
#define BMP280_NORMAL_MODE	3

void bmp280Init();
bool bmp280SelfTest(void);
bool bmp280EvaluateSelfTest(float min, float max, float value, char* string);
void bmp280_ReadReg(uint8_t reg, uint8_t *buffer, uint8_t len);
bool bmp280TestConnection();
void bmp280GetData(float* pressure, float* temperature, float* asl);
float bmp280PressureToAltitude(float* pressure);

#endif /* INC_BMP280_H_ */
