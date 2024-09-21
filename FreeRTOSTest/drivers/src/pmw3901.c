/*
 * pmw3901.c
 *
 *  Created on: Sep 6, 2024
 *      Author: Admin
 */

#include "FreeRTOS.h"
#include "task.h"

#include "main.h"
#include "pmw3901.h"
#include "system.h"
#include "sleepus.h"

#define HIGH	1
#define LOW		0
uint8_t isstate = 0;
//static bool flage; // wrong can't adjust value to static

static bool isInit = false;

static void digitalWrite(uint8_t value)
{
	if ( value == 0 ) HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, 0);
	else if ( value == 1 ) HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, 1);
}

static void registerWrite(uint8_t reg, uint8_t value)
{
	// Set MSB to 1 for write
	reg |= 0x80u;

	spiBeginTransaction();
	digitalWrite(LOW);

	sleepus(50);

	spiExchange(1, &reg, &reg);
	sleepus(50);
	spiExchange(1, &value, &value);

	sleepus(50);

	digitalWrite(HIGH);
	spiEndTransaction();
	sleepus(200);
}

static uint8_t registerRead(uint8_t reg)
{
	uint8_t data = 0;
	uint8_t dummy = 0;

	// Set MSB to 0 for read
	reg &= ~0x80u;

	spiBeginTransaction();
//	isstate = 1;//JH

	digitalWrite(LOW);
	sleepus(50);

	spiExchange(1, &reg, &reg);
//	isstate = 1; // NJH

	sleepus(500);
	spiExchange(1, &dummy, &data);

	sleepus(50);

	digitalWrite(HIGH);
	spiEndTransaction();
//	isstate = 1; //NJH
	sleepus(200);
//	isstate = 1; //NJH

	return data;
}

static void InitRegisters()
{
	registerWrite(0x7F, 0x00);
	registerWrite(0x61, 0xAD);
	registerWrite(0x7F, 0x03);
	registerWrite(0x40, 0x00);
	registerWrite(0x7F, 0x05);
	registerWrite(0x41, 0xB3);
	registerWrite(0x43, 0xF1);
	registerWrite(0x45, 0x14);
	registerWrite(0x5B, 0x32);
	registerWrite(0x5F, 0x34);
	registerWrite(0x7B, 0x08);
	registerWrite(0x7F, 0x06);
	registerWrite(0x44, 0x1B);
	registerWrite(0x40, 0xBF);
	registerWrite(0x4E, 0x3F);
	registerWrite(0x7F, 0x08);
	registerWrite(0x65, 0x20);
	registerWrite(0x6A, 0x18);
	registerWrite(0x7F, 0x09);
	registerWrite(0x4F, 0xAF);
	registerWrite(0x5F, 0x40);
	registerWrite(0x48, 0x80);
	registerWrite(0x49, 0x80);
	registerWrite(0x57, 0x77);
	registerWrite(0x60, 0x78);
	registerWrite(0x61, 0x78);
	registerWrite(0x62, 0x08);
	registerWrite(0x63, 0x50);
	registerWrite(0x7F, 0x0A);
	registerWrite(0x45, 0x60);
	registerWrite(0x7F, 0x00);
	registerWrite(0x4D, 0x11);
	registerWrite(0x55, 0x80);
	registerWrite(0x74, 0x1F);
	registerWrite(0x75, 0x1F);
	registerWrite(0x4A, 0x78);
	registerWrite(0x4B, 0x78);
	registerWrite(0x44, 0x08);
	registerWrite(0x45, 0x50);
	registerWrite(0x64, 0xFF);
	registerWrite(0x65, 0x1F);
	registerWrite(0x7F, 0x14);
	registerWrite(0x65, 0x67);
	registerWrite(0x66, 0x08);
	registerWrite(0x63, 0x70);
	registerWrite(0x7F, 0x15);
	registerWrite(0x48, 0x48);
	registerWrite(0x7F, 0x07);
	registerWrite(0x41, 0x0D);
	registerWrite(0x43, 0x14);
	registerWrite(0x4B, 0x0E);
	registerWrite(0x45, 0x0F);
	registerWrite(0x44, 0x42);
	registerWrite(0x4C, 0x80);
	registerWrite(0x7F, 0x10);
	registerWrite(0x5B, 0x02);
	registerWrite(0x7F, 0x07);
	registerWrite(0x40, 0x41);
	registerWrite(0x70, 0x00);

	vTaskDelay(M2T(10)); // delay 10ms

	registerWrite(0x32, 0x44);
	registerWrite(0x7F, 0x07);
	registerWrite(0x40, 0x40);
	registerWrite(0x7F, 0x06);
	registerWrite(0x62, 0xF0);
	registerWrite(0x63, 0x00);
	registerWrite(0x7F, 0x0D);
	registerWrite(0x48, 0xC0);
	registerWrite(0x6F, 0xD5);
	registerWrite(0x7F, 0x00);
	registerWrite(0x5B, 0xA0);
	registerWrite(0x4E, 0xA8);
	registerWrite(0x5A, 0x50);
	registerWrite(0x40, 0x80);

	registerWrite(0x7F, 0x00);
	registerWrite(0x5A, 0x10);
	registerWrite(0x54, 0x00);
}
bool pmw3901Init()
{
//	isstate = 1; //JH
  if (isInit) {
    return true;
  }

  digitalWrite(HIGH);

  spiBegin();
  vTaskDelay(M2T(40));

  digitalWrite(HIGH);
  vTaskDelay(M2T(2));
  digitalWrite(LOW);
  vTaskDelay(M2T(2));
  digitalWrite(HIGH);
  vTaskDelay(M2T(2));
//  isstate = 1; //JM

  uint8_t chipId    = registerRead(0x00);
  uint8_t invChipId = registerRead(0x5f);
//  isstate = 1; // NJH

  if (chipId == 0x49 && invChipId == 0xB6)
  {
    // Power on reset
    registerWrite(0x3a, 0x5a);
    vTaskDelay(M2T(5));

    // Reading the motion registers one time
    registerRead(0x02);
    registerRead(0x03);
    registerRead(0x04);
    registerRead(0x05);
    registerRead(0x06);
    vTaskDelay(M2T(1));

    InitRegisters();

    isInit = true;
  }

  return isInit;
}
void pmw3901ReadMotion(motionBurst_t * motion)
{
  uint8_t address = 0x16;

  spiBeginTransaction();
  digitalWrite(LOW);
  sleepus(50);
  spiExchange(1, &address, &address);
  sleepus(50);
  spiExchange(sizeof(motionBurst_t), (uint8_t*)motion, (uint8_t*)motion);
  sleepus(50);
  digitalWrite(HIGH);
  spiEndTransaction();
  sleepus(50);

  uint16_t realShutter = (motion->shutter >> 8) & 0x0FF;
  realShutter |= (motion->shutter & 0x0ff) << 8;
  motion->shutter = realShutter;
}
