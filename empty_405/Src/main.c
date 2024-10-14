#include "main.h"

#include "Dshot.h"
#include "dragonll_ibus.h"
#include "dragonll_imu6500.h"
#include "QMC5883P.h"
#include "MadgwickAHRS.h"


typedef struct {
	float gyro_x;
	float gyro_y;
	float gyro_z;
	float acc_x;
	float acc_y;
	float acc_z;
} Scale_senor;

typedef struct{
	float roll;
	float pitch;
	float yaw;
}angle_;

MPU6500_IMU imu;
qmc_typedef qmc;
Scale_senor scale_;
angle_ angle__;


uint32_t cournter = 0;
uint16_t my_motors_values[4] = {0, 0, 0, 0};
uint16_t ibus_data[IBUS_USER_CHANNELS];

uint32_t time_ms = 0;



SPI_HandleTypeDef hspi1;

I2C_HandleTypeDef hi2c2;

TIM_HandleTypeDef htim4;
TIM_HandleTypeDef htim3;
TIM_HandleTypeDef htim14;
DMA_HandleTypeDef hdma_tim3_ch1_trig;
DMA_HandleTypeDef hdma_tim3_ch2;
DMA_HandleTypeDef hdma_tim3_ch3;
DMA_HandleTypeDef hdma_tim3_ch4_up;



UART_HandleTypeDef huart1;
DMA_HandleTypeDef hdma_usart1_rx;



void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void dma_init(void);
static void MX_TIM4_Init(void);
static void tim3_init(void);
static void tim14_init(void);
static void uart_init(void);
static void spi1_init(void);
static void i2c2_init(void);


int main(void) {
	HAL_Init();
	SystemClock_Config();
	MX_GPIO_Init();
	dma_init();
	MX_TIM4_Init();
	tim3_init();
	tim14_init();
	uart_init();
	spi1_init();
	i2c2_init();

	hal_dshot_init(DSHOT600);
	HAL_Delay(10);
	hal_ibus_init();
	HAL_Delay(10);
	if(MPU6500_Init(&imu) == 0){
		while(1);
	}
	HAL_Delay(100);
	qmc5883p_init();
	HAL_TIM_Base_Start(&htim14);
	HAL_TIM_Base_Start_IT(&htim4);

	/* Loop forever */
	for (;;) {
//		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, 1);
//		HAL_Delay(100);
//		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, 0);
//		HAL_Delay(100);

		MPU6500_ReadAcc(&imu);
		MPU6500_ReadGyr(&imu);
		qmc5883p_read(&qmc);
		/*
		 * Scale for IMU
		 */
		scale_.acc_x = imu.acc[0] * 0.00239501953125f;
		scale_.acc_y = imu.acc[1] * 0.00239501953125f;
		scale_.acc_z = imu.acc[2] * 0.00239501953125f;

		scale_.gyro_x = imu.gyr[0] * 0.00026632423f;
		scale_.gyro_y = imu.gyr[1] * 0.00026632423f;
		scale_.gyro_z = imu.gyr[2] * 0.00026632423f;

		MadgwickAHRSupdate(scale_.gyro_x, scale_.gyro_y, scale_.gyro_z,
				scale_.acc_x, scale_.acc_y, scale_.acc_y,
				qmc.qmc_x, qmc.qmc_y,qmc.qmc_z);
		angle__.roll = asin(2 * ((q0 * q2) - (q1 * q3)))* 57.29577951f;
		angle__.pitch = -atan2( 2 * ( (q0 * q1) + (q2 * q3)), 1 - (2 * ((q1 * q1) + (q2 * q2)))) * 57.29577951f; //degrees
		angle__.yaw = atan2(2 * ((q0 * q3) + (q1 * q2)), 1 - (2 * ((q2 * q2) + (q3 * q3)))) * 57.29577951f; //degrees
//		if (HAL_GetTick() - time_ms < 1000) time_ms = HAL_GetTick();
		while(__HAL_TIM_GET_COUNTER(&htim14) - time_ms < 250);
		time_ms = __HAL_TIM_GET_COUNTER(&htim14);
	}
}
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}
static void MX_TIM4_Init(void)
{

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  htim4.Instance = TIM4;
  htim4.Init.Prescaler = 83;
  htim4.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim4.Init.Period = 999;
  htim4.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim4.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim4) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim4, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim4, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }

}

static void dma_init(void) {

	__HAL_RCC_DMA1_CLK_ENABLE();
	__HAL_RCC_DMA2_CLK_ENABLE();

	/* DMA interrupt init */
	/* DMA1_Stream2_IRQn interrupt configuration */
	HAL_NVIC_SetPriority(DMA1_Stream2_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(DMA1_Stream2_IRQn);
	/* DMA1_Stream4_IRQn interrupt configuration */
	HAL_NVIC_SetPriority(DMA1_Stream4_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(DMA1_Stream4_IRQn);
	/* DMA1_Stream5_IRQn interrupt configuration */
	HAL_NVIC_SetPriority(DMA1_Stream5_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(DMA1_Stream5_IRQn);
	/* DMA1_Stream7_IRQn interrupt configuration */
	HAL_NVIC_SetPriority(DMA1_Stream7_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(DMA1_Stream7_IRQn);
	/* DMA2_Stream2_IRQn interrupt configuration */
	HAL_NVIC_SetPriority(DMA2_Stream2_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(DMA2_Stream2_IRQn);

}

static void tim3_init(void) {
	TIM_MasterConfigTypeDef sMasterConfig = { 0 };
	TIM_OC_InitTypeDef sConfigOC = { 0 };

	htim3.Instance = TIM3;
	htim3.Init.Prescaler = 0;
	htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim3.Init.Period = 0;
	htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
	if (HAL_TIM_PWM_Init(&htim3) != HAL_OK) {
		Error_Handler();
	}
	sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig)
			!= HAL_OK) {
		Error_Handler();
	}
	sConfigOC.OCMode = TIM_OCMODE_PWM1;
	sConfigOC.Pulse = 0;
	sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
	sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
	if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_1)
			!= HAL_OK) {
		Error_Handler();
	}
	if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_2)
			!= HAL_OK) {
		Error_Handler();
	}
	if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_3)
			!= HAL_OK) {
		Error_Handler();
	}
	if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_4)
			!= HAL_OK) {
		Error_Handler();
	}
	HAL_TIM_MspPostInit(&htim3);
}

static void tim14_init(void){
	  htim14.Instance = TIM14;
	  htim14.Init.Prescaler = 84-1;
	  htim14.Init.CounterMode = TIM_COUNTERMODE_UP;
	  htim14.Init.Period = 65535-1;
	  htim14.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	  htim14.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
	  if (HAL_TIM_Base_Init(&htim14) != HAL_OK)
	  {
	    Error_Handler();
	  }
}

static void uart_init(void){
	  huart1.Instance = USART1;
	  huart1.Init.BaudRate = 115200;
	  huart1.Init.WordLength = UART_WORDLENGTH_8B;
	  huart1.Init.StopBits = UART_STOPBITS_1;
	  huart1.Init.Parity = UART_PARITY_NONE;
	  huart1.Init.Mode = UART_MODE_TX_RX;
	  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
	  if (HAL_UART_Init(&huart1) != HAL_OK)
	  {
	    Error_Handler();
	  }
}

static void spi1_init(void) {
	hspi1.Instance = SPI1;
	hspi1.Init.Mode = SPI_MODE_MASTER;
	hspi1.Init.Direction = SPI_DIRECTION_2LINES;
	hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
	hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
	hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
	hspi1.Init.NSS = SPI_NSS_SOFT;
	hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
	hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
	hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
	hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
	hspi1.Init.CRCPolynomial = 10;
	if (HAL_SPI_Init(&hspi1) != HAL_OK) {
		Error_Handler();
	}
}

static void i2c2_init(void){
	  hi2c2.Instance = I2C2;
	  hi2c2.Init.ClockSpeed = 400000;
	  hi2c2.Init.DutyCycle = I2C_DUTYCYCLE_2;
	  hi2c2.Init.OwnAddress1 = 0;
	  hi2c2.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
	  hi2c2.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
	  hi2c2.Init.OwnAddress2 = 0;
	  hi2c2.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
	  hi2c2.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
	  if (HAL_I2C_Init(&hi2c2) != HAL_OK)
	  {
	    Error_Handler();
	  }
}


static void MX_GPIO_Init(void)
{
	  GPIO_InitTypeDef GPIO_InitStruct = {0};
	  __HAL_RCC_GPIOC_CLK_ENABLE();
	  __HAL_RCC_GPIOH_CLK_ENABLE();
	  __HAL_RCC_GPIOA_CLK_ENABLE();

	  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);
	  HAL_GPIO_WritePin(GYRO_CS_GPIO_Port, GYRO_CS_Pin, GPIO_PIN_RESET);

	  /*Configure GPIO pin : PC13 */
	  GPIO_InitStruct.Pin = GPIO_PIN_13;
	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
	  /*Configure GPIO pin : GYRO_CS_Pin */
	  GPIO_InitStruct.Pin = GYRO_CS_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	  HAL_GPIO_Init(GYRO_CS_GPIO_Port, &GPIO_InitStruct);

	  /*Configure GPIO pin : GYRO_INT_Pin */
	  GPIO_InitStruct.Pin = GYRO_INT_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  HAL_GPIO_Init(GYRO_INT_GPIO_Port, &GPIO_InitStruct);
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
	if (htim->Instance == TIM4) {
		cournter +=1;
//		hal_dshot_write(my_motors_values);
		hal_ibus_read(ibus_data);
		ibus_soft_failsafe(ibus_data, 10);
	}
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
	if(huart == IBUS_UART){
		ibus_reset_failsafe();
	}
}

void Error_Handler(void)
{
  __disable_irq();
  while (1)
  {
  }

}

#ifdef  USE_FULL_ASSERT

void assert_failed(uint8_t *file, uint32_t line)
{

}
#endif
