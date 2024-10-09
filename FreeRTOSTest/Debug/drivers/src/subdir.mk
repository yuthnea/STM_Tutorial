################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../drivers/src/bmp280.c \
../drivers/src/dragonll_ibus.c \
../drivers/src/dragonll_imu6500.c \
../drivers/src/dshot.c \
../drivers/src/exti.c \
../drivers/src/gpio_drv.c \
../drivers/src/i2c_drv.c \
../drivers/src/i2cdev.c \
../drivers/src/led.c \
../drivers/src/mpu6500.c \
../drivers/src/mpu9250.c \
../drivers/src/ms5611.c \
../drivers/src/nvic.c \
../drivers/src/pmw3901.c \
../drivers/src/px4flow.c \
../drivers/src/qmc5883p.c \
../drivers/src/spi_drv.c \
../drivers/src/timer_drv.c \
../drivers/src/uart_drv.c \
../drivers/src/vl53l1x.c 

OBJS += \
./drivers/src/bmp280.o \
./drivers/src/dragonll_ibus.o \
./drivers/src/dragonll_imu6500.o \
./drivers/src/dshot.o \
./drivers/src/exti.o \
./drivers/src/gpio_drv.o \
./drivers/src/i2c_drv.o \
./drivers/src/i2cdev.o \
./drivers/src/led.o \
./drivers/src/mpu6500.o \
./drivers/src/mpu9250.o \
./drivers/src/ms5611.o \
./drivers/src/nvic.o \
./drivers/src/pmw3901.o \
./drivers/src/px4flow.o \
./drivers/src/qmc5883p.o \
./drivers/src/spi_drv.o \
./drivers/src/timer_drv.o \
./drivers/src/uart_drv.o \
./drivers/src/vl53l1x.o 

C_DEPS += \
./drivers/src/bmp280.d \
./drivers/src/dragonll_ibus.d \
./drivers/src/dragonll_imu6500.d \
./drivers/src/dshot.d \
./drivers/src/exti.d \
./drivers/src/gpio_drv.d \
./drivers/src/i2c_drv.d \
./drivers/src/i2cdev.d \
./drivers/src/led.d \
./drivers/src/mpu6500.d \
./drivers/src/mpu9250.d \
./drivers/src/ms5611.d \
./drivers/src/nvic.d \
./drivers/src/pmw3901.d \
./drivers/src/px4flow.d \
./drivers/src/qmc5883p.d \
./drivers/src/spi_drv.d \
./drivers/src/timer_drv.d \
./drivers/src/uart_drv.d \
./drivers/src/vl53l1x.d 


# Each subdirectory must supply rules for building sources it contributes
drivers/src/%.o drivers/src/%.su drivers/src/%.cyclo: ../drivers/src/%.c drivers/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32F40_41xxx -DUSE_HAL_DRIVER -DARM_MATH_CM4 -DSTM32F405xx -c -I"D:/STM32_AIFRARM/STM_Tutorial/FreeRTOSTest/CMSIS/STM32F4xx/Include" -I"D:/STM32_AIFRARM/STM_Tutorial/FreeRTOSTest/deck/deck_spi/inc" -I"D:/STM32_AIFRARM/STM_Tutorial/FreeRTOSTest/deck/inc" -I"D:/STM32_AIFRARM/STM_Tutorial/FreeRTOSTest/vl53l1" -I"D:/STM32_AIFRARM/STM_Tutorial/FreeRTOSTest/vl53l1/core/inc" -I"D:/STM32_AIFRARM/STM_Tutorial/FreeRTOSTest/modules/inc/estimator" -I"D:/STM32_AIFRARM/STM_Tutorial/FreeRTOSTest/platform/inc" -I"D:/STM32_AIFRARM/STM_Tutorial/FreeRTOSTest/CMSIS/Include" -I"D:/STM32_AIFRARM/STM_Tutorial/FreeRTOSTest/CMSIS/stm32f4xx_hal_driver/Inc" -I"D:/STM32_AIFRARM/STM_Tutorial/FreeRTOSTest/CMSIS/stm32f4xx_hal_driver/Inc/Legacy" -I"D:/STM32_AIFRARM/STM_Tutorial/FreeRTOSTest/FreeRTOS/include" -I"D:/STM32_AIFRARM/STM_Tutorial/FreeRTOSTest/drivers/inc" -I"D:/STM32_AIFRARM/STM_Tutorial/FreeRTOSTest/FreeRTOS/portable/GCC/ARM_CM4F" -I../Inc -I"D:/STM32_AIFRARM/STM_Tutorial/FreeRTOSTest/config" -I"D:/STM32_AIFRARM/STM_Tutorial/FreeRTOSTest/DSP_DRIVERS/Include" -I"D:/STM32_AIFRARM/STM_Tutorial/FreeRTOSTest/modules/inc/kalman_core" -I"D:/STM32_AIFRARM/STM_Tutorial/FreeRTOSTest/modules/inc" -I"D:/STM32_AIFRARM/STM_Tutorial/FreeRTOSTest/hal/inc" -I"D:/STM32_AIFRARM/STM_Tutorial/FreeRTOSTest/utils/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-drivers-2f-src

clean-drivers-2f-src:
	-$(RM) ./drivers/src/bmp280.cyclo ./drivers/src/bmp280.d ./drivers/src/bmp280.o ./drivers/src/bmp280.su ./drivers/src/dragonll_ibus.cyclo ./drivers/src/dragonll_ibus.d ./drivers/src/dragonll_ibus.o ./drivers/src/dragonll_ibus.su ./drivers/src/dragonll_imu6500.cyclo ./drivers/src/dragonll_imu6500.d ./drivers/src/dragonll_imu6500.o ./drivers/src/dragonll_imu6500.su ./drivers/src/dshot.cyclo ./drivers/src/dshot.d ./drivers/src/dshot.o ./drivers/src/dshot.su ./drivers/src/exti.cyclo ./drivers/src/exti.d ./drivers/src/exti.o ./drivers/src/exti.su ./drivers/src/gpio_drv.cyclo ./drivers/src/gpio_drv.d ./drivers/src/gpio_drv.o ./drivers/src/gpio_drv.su ./drivers/src/i2c_drv.cyclo ./drivers/src/i2c_drv.d ./drivers/src/i2c_drv.o ./drivers/src/i2c_drv.su ./drivers/src/i2cdev.cyclo ./drivers/src/i2cdev.d ./drivers/src/i2cdev.o ./drivers/src/i2cdev.su ./drivers/src/led.cyclo ./drivers/src/led.d ./drivers/src/led.o ./drivers/src/led.su ./drivers/src/mpu6500.cyclo ./drivers/src/mpu6500.d ./drivers/src/mpu6500.o ./drivers/src/mpu6500.su ./drivers/src/mpu9250.cyclo ./drivers/src/mpu9250.d ./drivers/src/mpu9250.o ./drivers/src/mpu9250.su ./drivers/src/ms5611.cyclo ./drivers/src/ms5611.d ./drivers/src/ms5611.o ./drivers/src/ms5611.su ./drivers/src/nvic.cyclo ./drivers/src/nvic.d ./drivers/src/nvic.o ./drivers/src/nvic.su ./drivers/src/pmw3901.cyclo ./drivers/src/pmw3901.d ./drivers/src/pmw3901.o ./drivers/src/pmw3901.su ./drivers/src/px4flow.cyclo ./drivers/src/px4flow.d ./drivers/src/px4flow.o ./drivers/src/px4flow.su ./drivers/src/qmc5883p.cyclo ./drivers/src/qmc5883p.d ./drivers/src/qmc5883p.o ./drivers/src/qmc5883p.su ./drivers/src/spi_drv.cyclo ./drivers/src/spi_drv.d ./drivers/src/spi_drv.o ./drivers/src/spi_drv.su ./drivers/src/timer_drv.cyclo ./drivers/src/timer_drv.d ./drivers/src/timer_drv.o ./drivers/src/timer_drv.su ./drivers/src/uart_drv.cyclo ./drivers/src/uart_drv.d ./drivers/src/uart_drv.o ./drivers/src/uart_drv.su ./drivers/src/vl53l1x.cyclo ./drivers/src/vl53l1x.d ./drivers/src/vl53l1x.o ./drivers/src/vl53l1x.su

.PHONY: clean-drivers-2f-src

