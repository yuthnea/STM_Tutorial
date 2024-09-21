/*
 * bmp280.c
 *
 *  Created on: Sep 2, 2024
 *      Author: Admin
 */

#include "bmp280.h"
#include "spi_drv.h"
#include "FreeRTOS.h"
#include "task.h"


static bool isInit;

static int16_t t2, t3, p2, p3, p4, p5, p6, p7, p8, p9;
static uint16_t t1, p1;
static int32_t t_fine;

static void bmp280_StartUp(){

	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, 0);
	vTaskDelay(5);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, 1);

}
static void bmp280_WriteReg(uint8_t reg, uint8_t val){

	uint8_t buf[2];
	buf[0] = reg;
	buf[0] &= ~(1<<7);
	buf[1] = val;

	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, 0);

	HAL_SPI_Transmit(&hspi2, buf, 2, 100);

	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, 1);
}
void bmp280_ReadReg(uint8_t reg, uint8_t *buffer, uint8_t len){
	uint8_t buf = reg | 0x80;

	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, 0);

	HAL_SPI_Transmit(&hspi2, &buf, 1, 100);
	HAL_SPI_Receive(&hspi2, buffer, len, 100);

	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, 1);

}
static void bmp280_ReadCalibrateValue(){

	uint8_t buf[24];
	bmp280_ReadReg(DIG_T1, buf, 24);

	t1 = buf[1] << 8 | buf[0];
	t2 = buf[3] << 8 | buf[2];
	t3 = buf[5] << 8 | buf[4];

	p1 = buf[7] << 8 | buf[6];
	p2 = buf[9] << 8 | buf[8];
	p3 = buf[11]<< 8 | buf[10];
	p4 = buf[13]<< 8 | buf[12];
	p5 = buf[15]<< 8 | buf[14];
	p6 = buf[17]<< 8 | buf[16];
	p7 = buf[19]<< 8 | buf[18];
	p8 = buf[21]<< 8 | buf[20];
	p9 = buf[23]<< 8 | buf[22];

}
static void bmp280GetTemperature(float* temperature)
{
	uint8_t temp_buf[3];
	int32_t temp_adc;
	int32_t var1, var2;

	bmp280_ReadReg(BMP280_TEMP_REG_DATA, temp_buf, 3);
	temp_adc = (temp_buf[0] << 16) | (temp_buf[1] << 8) | temp_buf[2];
	temp_adc >>= 4;

	var1  = ((((temp_adc>>3) - ((int32_t)t1 <<1))) * ((int32_t)t2)) >> 11;
	var2  = (((((temp_adc >> 4) - ((int32_t) t1)) * ((temp_adc >> 4) - ((int32_t) t1))) >> 12) * ((int32_t) t3)) >> 14;

	t_fine = (var1 + var2);

	*temperature = (((t_fine * 5) + 128 ) >> 8) /100.0f;
}
static void bmp280GetPressure(float *pressure)
{
	uint8_t pres_buf[3];
	int32_t pres_adc;
	int64_t var1, var2, p;
	float temp;

	bmp280GetTemperature(&temp);
	bmp280_ReadReg(BMP280_PRESSURE_REG_DAT, pres_buf, 3);

	pres_adc = (pres_buf[0] << 16) | (pres_buf[1] << 8) | pres_buf[2];
	pres_adc >>= 4;

	var1 = ((int64_t)t_fine) - 128000;
	var2 = var1 * var1 * (int64_t)p6;
	var2 = var2 + ((var1*(int64_t)p5)<<17);
	var2 = var2 + (((int64_t)p4)<<35);
	var1 = ((var1 * var1 * (int64_t)p3)>>8) + ((var1 * (int64_t)p2)<<12);
	var1 = (((((int64_t)1)<<47)+var1))*((int64_t)p1)>>33;

	if ( var1 == 0 ) return;

	p = 1048576 - pres_adc;
	p = (((p<<31) - var2)*3125) / var1;
	var1 = (((int64_t)p9) * (p>>13) * (p>>13)) >> 25;
	var2 = (((int64_t)p8) * p) >> 19;

	p = ((p + var1 + var2) >> 8) + (((int64_t)p7)<<4);
	*pressure = (float) p / 256.0f;

}
void bmp280Init()
{

	bmp280_StartUp();
	vTaskDelay(5);
	bmp280_ReadCalibrateValue();
	vTaskDelay(5);
	bmp280_WriteReg(BMP280_REG_CTRL, ( (TEMP_18BIT_RES<<5) | (PRES_18BIT_RES<<2) | BMP280_NORMAL_MODE));
	isInit = true;
}
bool bmp280SelfTest(void)
{

	return true;
}
bool bmp280EvaluateSelfTest(float min, float max, float value, char* string)
{

	return true;
}
bool bmp280TestConnection()
{
	uint8_t checkID;

	if (!isInit) return false;

	bmp280_StartUp();
	bmp280_ReadReg(BMP280_REG_ID, &checkID, 1);

	if ( checkID != 0x58 ) return false;

	return true;
}
void bmp280GetData(float* pressure, float* temperature, float* asl)
{
	bmp280GetTemperature(temperature);
	bmp280GetPressure(pressure);
	*asl = bmp280PressureToAltitude(pressure);

}

#include "math.h"
// Constants used to determine altitude from pressure
#define CONST_SEA_PRESSURE 102610.f //1026.1f //http://www.meteo.physik.uni-muenchen.de/dokuwiki/doku.php?id=wetter:stadt:messung
#define CONST_PF 0.1902630958f //(1/5.25588f) Pressure factor
#define CONST_PF2 44330.0f
#define FIX_TEMP 25         // Fixed Temperature. ASL is a function of pressure and temperature, but as the temperature changes so much (blow a little towards the flie and watch it drop 5 degrees) it corrupts the ASL estimates.
                            // TLDR: Adjusting for temp changes does more harm than good.

float bmp280PressureToAltitude(float* pressure)
{
    if (*pressure > 0)
    {
        //return (1.f - pow(*pressure / CONST_SEA_PRESSURE, CONST_PF)) * CONST_PF2;
        //return ((pow((1015.7 / *pressure), CONST_PF) - 1.0) * (25. + 273.15)) / 0.0065;
        return ((powf((1015.7f / *pressure), CONST_PF) - 1.0f) * (FIX_TEMP + 273.15f)) / 0.0065f;
    }
    else
    {
        return 0;
    }
}
