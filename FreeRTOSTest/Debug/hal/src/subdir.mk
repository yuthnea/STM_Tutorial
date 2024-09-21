################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../hal/src/flow.c \
../hal/src/led_test.c \
../hal/src/sensors.c \
../hal/src/sensors_flow_tof.c \
../hal/src/sensors_mpu6500_bmp280.c \
../hal/src/sensors_mpu9250_bmp280.c \
../hal/src/sensorsmpu6500_qmc5883.c \
../hal/src/tof.c \
../hal/src/usec_time.c 

OBJS += \
./hal/src/flow.o \
./hal/src/led_test.o \
./hal/src/sensors.o \
./hal/src/sensors_flow_tof.o \
./hal/src/sensors_mpu6500_bmp280.o \
./hal/src/sensors_mpu9250_bmp280.o \
./hal/src/sensorsmpu6500_qmc5883.o \
./hal/src/tof.o \
./hal/src/usec_time.o 

C_DEPS += \
./hal/src/flow.d \
./hal/src/led_test.d \
./hal/src/sensors.d \
./hal/src/sensors_flow_tof.d \
./hal/src/sensors_mpu6500_bmp280.d \
./hal/src/sensors_mpu9250_bmp280.d \
./hal/src/sensorsmpu6500_qmc5883.d \
./hal/src/tof.d \
./hal/src/usec_time.d 


# Each subdirectory must supply rules for building sources it contributes
hal/src/%.o hal/src/%.su hal/src/%.cyclo: ../hal/src/%.c hal/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32F40_41xxx -DUSE_HAL_DRIVER -DARM_MATH_CM4 -DSTM32F405xx -c -I"D:/STM32_AIFRARM/FreeRTOSTest/FreeRTOSTest/CMSIS/STM32F4xx/Include" -I"D:/STM32_AIFRARM/FreeRTOSTest/FreeRTOSTest/deck/deck_spi/inc" -I"D:/STM32_AIFRARM/FreeRTOSTest/FreeRTOSTest/deck/inc" -I"D:/STM32_AIFRARM/FreeRTOSTest/FreeRTOSTest/vl53l1" -I"D:/STM32_AIFRARM/FreeRTOSTest/FreeRTOSTest/vl53l1/core/inc" -I"D:/STM32_AIFRARM/FreeRTOSTest/FreeRTOSTest/modules/inc/estimator" -I"D:/STM32_AIFRARM/FreeRTOSTest/FreeRTOSTest/platform/inc" -I"D:/STM32_AIFRARM/FreeRTOSTest/FreeRTOSTest/CMSIS/Include" -I"D:/STM32_AIFRARM/FreeRTOSTest/FreeRTOSTest/CMSIS/stm32f4xx_hal_driver/Inc" -I"D:/STM32_AIFRARM/FreeRTOSTest/FreeRTOSTest/CMSIS/stm32f4xx_hal_driver/Inc/Legacy" -I"D:/STM32_AIFRARM/FreeRTOSTest/FreeRTOSTest/FreeRTOS/include" -I"D:/STM32_AIFRARM/FreeRTOSTest/FreeRTOSTest/drivers/inc" -I"D:/STM32_AIFRARM/FreeRTOSTest/FreeRTOSTest/FreeRTOS/portable/GCC/ARM_CM4F" -I../Inc -I"D:/STM32_AIFRARM/FreeRTOSTest/FreeRTOSTest/config" -I"D:/STM32_AIFRARM/FreeRTOSTest/FreeRTOSTest/DSP_DRIVERS/Include" -I"D:/STM32_AIFRARM/FreeRTOSTest/FreeRTOSTest/modules/inc/kalman_core" -I"D:/STM32_AIFRARM/FreeRTOSTest/FreeRTOSTest/modules/inc" -I"D:/STM32_AIFRARM/FreeRTOSTest/FreeRTOSTest/hal/inc" -I"D:/STM32_AIFRARM/FreeRTOSTest/FreeRTOSTest/utils/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-hal-2f-src

clean-hal-2f-src:
	-$(RM) ./hal/src/flow.cyclo ./hal/src/flow.d ./hal/src/flow.o ./hal/src/flow.su ./hal/src/led_test.cyclo ./hal/src/led_test.d ./hal/src/led_test.o ./hal/src/led_test.su ./hal/src/sensors.cyclo ./hal/src/sensors.d ./hal/src/sensors.o ./hal/src/sensors.su ./hal/src/sensors_flow_tof.cyclo ./hal/src/sensors_flow_tof.d ./hal/src/sensors_flow_tof.o ./hal/src/sensors_flow_tof.su ./hal/src/sensors_mpu6500_bmp280.cyclo ./hal/src/sensors_mpu6500_bmp280.d ./hal/src/sensors_mpu6500_bmp280.o ./hal/src/sensors_mpu6500_bmp280.su ./hal/src/sensors_mpu9250_bmp280.cyclo ./hal/src/sensors_mpu9250_bmp280.d ./hal/src/sensors_mpu9250_bmp280.o ./hal/src/sensors_mpu9250_bmp280.su ./hal/src/sensorsmpu6500_qmc5883.cyclo ./hal/src/sensorsmpu6500_qmc5883.d ./hal/src/sensorsmpu6500_qmc5883.o ./hal/src/sensorsmpu6500_qmc5883.su ./hal/src/tof.cyclo ./hal/src/tof.d ./hal/src/tof.o ./hal/src/tof.su ./hal/src/usec_time.cyclo ./hal/src/usec_time.d ./hal/src/usec_time.o ./hal/src/usec_time.su

.PHONY: clean-hal-2f-src

