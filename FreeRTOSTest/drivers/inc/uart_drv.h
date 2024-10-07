/*
 * uart_drv.h
 *
 *  Created on: Sep 18, 2024
 *      Author: AI FARM
 */

#ifndef INC_UART_DRV_H_
#define INC_UART_DRV_H_
#include "main.h"
//#include "stdint.h"
//#include "stm32f4xx_hal_uart.h"
//#include "stm32f4xx_hal_usart.h"

extern UART_HandleTypeDef huart4;
extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;
extern UART_HandleTypeDef huart3;

extern DMA_HandleTypeDef hdma_usart1_rx;
extern DMA_HandleTypeDef hdma_usart2_rx;
extern DMA_HandleTypeDef hdma_usart3_rx;

void MX_UART4_Init(void);
void MX_USART1_UART_Init(void);
void MX_USART2_UART_Init(void);
void MX_USART3_UART_Init(void);

void uart_dma_init(void);


//void MX_DMA_Init(void);


#endif /* INC_UART_DRV_H_ */
