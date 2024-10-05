################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../CMSIS/stm32f4xx_hal_driver/Src/Legacy/stm32f4xx_hal_can.c \
../CMSIS/stm32f4xx_hal_driver/Src/Legacy/stm32f4xx_hal_eth.c 

OBJS += \
./CMSIS/stm32f4xx_hal_driver/Src/Legacy/stm32f4xx_hal_can.o \
./CMSIS/stm32f4xx_hal_driver/Src/Legacy/stm32f4xx_hal_eth.o 

C_DEPS += \
./CMSIS/stm32f4xx_hal_driver/Src/Legacy/stm32f4xx_hal_can.d \
./CMSIS/stm32f4xx_hal_driver/Src/Legacy/stm32f4xx_hal_eth.d 


# Each subdirectory must supply rules for building sources it contributes
CMSIS/stm32f4xx_hal_driver/Src/Legacy/%.o CMSIS/stm32f4xx_hal_driver/Src/Legacy/%.su CMSIS/stm32f4xx_hal_driver/Src/Legacy/%.cyclo: ../CMSIS/stm32f4xx_hal_driver/Src/Legacy/%.c CMSIS/stm32f4xx_hal_driver/Src/Legacy/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32F40_41xxx -DUSE_HAL_DRIVER -DARM_MATH_CM4 -DSTM32F405xx -c -I"D:/STM32_AIFRARM/STM_Tutorial/FreeRTOSTest/CMSIS/STM32F4xx/Include" -I"D:/STM32_AIFRARM/STM_Tutorial/FreeRTOSTest/deck/deck_spi/inc" -I"D:/STM32_AIFRARM/STM_Tutorial/FreeRTOSTest/deck/inc" -I"D:/STM32_AIFRARM/STM_Tutorial/FreeRTOSTest/vl53l1" -I"D:/STM32_AIFRARM/STM_Tutorial/FreeRTOSTest/vl53l1/core/inc" -I"D:/STM32_AIFRARM/STM_Tutorial/FreeRTOSTest/modules/inc/estimator" -I"D:/STM32_AIFRARM/STM_Tutorial/FreeRTOSTest/platform/inc" -I"D:/STM32_AIFRARM/STM_Tutorial/FreeRTOSTest/CMSIS/Include" -I"D:/STM32_AIFRARM/STM_Tutorial/FreeRTOSTest/CMSIS/stm32f4xx_hal_driver/Inc" -I"D:/STM32_AIFRARM/STM_Tutorial/FreeRTOSTest/CMSIS/stm32f4xx_hal_driver/Inc/Legacy" -I"D:/STM32_AIFRARM/STM_Tutorial/FreeRTOSTest/FreeRTOS/include" -I"D:/STM32_AIFRARM/STM_Tutorial/FreeRTOSTest/drivers/inc" -I"D:/STM32_AIFRARM/STM_Tutorial/FreeRTOSTest/FreeRTOS/portable/GCC/ARM_CM4F" -I../Inc -I"D:/STM32_AIFRARM/STM_Tutorial/FreeRTOSTest/config" -I"D:/STM32_AIFRARM/STM_Tutorial/FreeRTOSTest/DSP_DRIVERS/Include" -I"D:/STM32_AIFRARM/STM_Tutorial/FreeRTOSTest/modules/inc/kalman_core" -I"D:/STM32_AIFRARM/STM_Tutorial/FreeRTOSTest/modules/inc" -I"D:/STM32_AIFRARM/STM_Tutorial/FreeRTOSTest/hal/inc" -I"D:/STM32_AIFRARM/STM_Tutorial/FreeRTOSTest/utils/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-CMSIS-2f-stm32f4xx_hal_driver-2f-Src-2f-Legacy

clean-CMSIS-2f-stm32f4xx_hal_driver-2f-Src-2f-Legacy:
	-$(RM) ./CMSIS/stm32f4xx_hal_driver/Src/Legacy/stm32f4xx_hal_can.cyclo ./CMSIS/stm32f4xx_hal_driver/Src/Legacy/stm32f4xx_hal_can.d ./CMSIS/stm32f4xx_hal_driver/Src/Legacy/stm32f4xx_hal_can.o ./CMSIS/stm32f4xx_hal_driver/Src/Legacy/stm32f4xx_hal_can.su ./CMSIS/stm32f4xx_hal_driver/Src/Legacy/stm32f4xx_hal_eth.cyclo ./CMSIS/stm32f4xx_hal_driver/Src/Legacy/stm32f4xx_hal_eth.d ./CMSIS/stm32f4xx_hal_driver/Src/Legacy/stm32f4xx_hal_eth.o ./CMSIS/stm32f4xx_hal_driver/Src/Legacy/stm32f4xx_hal_eth.su

.PHONY: clean-CMSIS-2f-stm32f4xx_hal_driver-2f-Src-2f-Legacy

