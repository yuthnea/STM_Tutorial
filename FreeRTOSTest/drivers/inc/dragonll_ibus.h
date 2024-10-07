/*
 * dragonll_ibus.h
 *
 *  Created on: May 28, 2024
 *      Author: Yen Yuthnea
 */

#ifndef INC_DRAGONLL_IBUS_H_
#define INC_DRAGONLL_IBUS_H_

//#include "usart.h"
#include "stdbool.h"
#include "main.h"
#include "uart_drv.h"
//#include "stm32f4xx_it.h"

// user configuration
#define IBUS_UART				(&huart1)
#define IBUS_USER_CHANNELS		6


// define
#define IBUS_LENGTH			0X20
#define IBUS_COMMAND40		0X40
#define IBUS_MAX_CHANNELS	14

/*
 * Function Ibus
 */
void hal_ibus_init();
void hal_ibus_read(uint16_t* ibus_data);


/*
 * Helper Function Ibus
 */

bool ibus_is_valid();
bool ibus_checksum();
void ibus_update(uint16_t* ibus_data);
void ibus_soft_failsafe(uint16_t* ibus_data, uint8_t fail_safe_max);
void ibus_reset_failsafe();

#endif /* INC_DRAGONLL_IBUS_H_ */
