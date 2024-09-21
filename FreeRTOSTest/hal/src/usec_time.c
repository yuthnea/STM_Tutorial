/**
 *    ||          ____  _ __                           
 * +------+      / __ )(_) /_______________ _____  ___ 
 * | 0xBC |     / __  / / __/ ___/ ___/ __ `/_  / / _ \
 * +------+    / /_/ / / /_/ /__/ /  / /_/ / / /_/  __/
 *  ||  ||    /_____/_/\__/\___/_/   \__,_/ /___/\___/
 *
 * Crazyflie control firmware
 *
 * Copyright (C) 2011-2023 Bitcraze AB
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
 *
 * usec_time.c - microsecond-resolution timer and timestamps.
 */

#include "stm32f4xx.h"
#include <stdbool.h>
#include "usec_time.h"
#include "cfassert.h"

static bool isInit = false;

static uint32_t usecTimerHighCount;

void usecTimerInit(void)
{
  if (isInit) {
    return;
  }

  usecTimerHighCount = 0;

  // 1. Enable the clock for TIM7
  RCC->APB1ENR |= RCC_APB1ENR_TIM7EN;

  // 2. Set the prescaler value
  // Assuming the APB1 clock is 42 MHz (84 MHz/2) and you want a 1 kHz timer clock (1 ms per tick)
  TIM7->PSC = 41;  // Prescaler = 42000 - 1

  // 3. Set the auto-reload value
  TIM7->ARR = 999;  // 1000 ticks -> 1 second (1 ms per tick)

  // 4. Enable the update interrupt (UIE)
  TIM7->DIER |= TIM_DIER_UIE;

  // 5. Enable the counter
  TIM7->CR1 |= TIM_CR1_CEN;
  NVIC_SetPriority(TIM7_IRQn, 3);
  // 6. Enable TIM7 interrupt in NVIC
  NVIC_EnableIRQ(TIM7_IRQn);
  isInit = true;
}

void usecTimerReset(void)
{
  IF_DEBUG_ASSERT(isInit);

  const uint32_t zero = 0;
  __atomic_store(&usecTimerHighCount, &zero, __ATOMIC_SEQ_CST);

  TIM7->CNT = 0;
}

uint64_t usecTimestamp(void)
{
  IF_DEBUG_ASSERT(isInit);

  uint32_t high0;
  __atomic_load(&usecTimerHighCount, &high0, __ATOMIC_SEQ_CST);
  uint32_t low = TIM7->CNT;
  uint32_t high;
  __atomic_load(&usecTimerHighCount, &high, __ATOMIC_SEQ_CST);

  // There was no increment in between
  if (high == high0)
  {
    return (((uint64_t)high) << 16) + low;
  }
  // There was an increment, but we don't expect another one soon
  return (((uint64_t)high) << 16) + TIM7->CNT;
}

void TIM7_IRQHandler(void)
{

    if (TIM7->SR & TIM_SR_UIF) {
        // Clear the update interrupt flag
        TIM7->SR &= ~TIM_SR_UIF;
    }

  __sync_fetch_and_add(&usecTimerHighCount, 1);
}



