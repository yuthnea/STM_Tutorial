################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../modules/src/estimator/estimator.c \
../modules/src/estimator/estimator_complementary.c \
../modules/src/estimator/estimator_kalman.c \
../modules/src/estimator/position_estimator_altitude.c 

OBJS += \
./modules/src/estimator/estimator.o \
./modules/src/estimator/estimator_complementary.o \
./modules/src/estimator/estimator_kalman.o \
./modules/src/estimator/position_estimator_altitude.o 

C_DEPS += \
./modules/src/estimator/estimator.d \
./modules/src/estimator/estimator_complementary.d \
./modules/src/estimator/estimator_kalman.d \
./modules/src/estimator/position_estimator_altitude.d 


# Each subdirectory must supply rules for building sources it contributes
modules/src/estimator/%.o modules/src/estimator/%.su modules/src/estimator/%.cyclo: ../modules/src/estimator/%.c modules/src/estimator/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32F40_41xxx -DUSE_HAL_DRIVER -DARM_MATH_CM4 -DSTM32F405xx -c -I"D:/STM32_AIFRARM/STM_Tutorial/FreeRTOSTest/CMSIS/STM32F4xx/Include" -I"D:/STM32_AIFRARM/STM_Tutorial/FreeRTOSTest/deck/deck_spi/inc" -I"D:/STM32_AIFRARM/STM_Tutorial/FreeRTOSTest/deck/inc" -I"D:/STM32_AIFRARM/STM_Tutorial/FreeRTOSTest/vl53l1" -I"D:/STM32_AIFRARM/STM_Tutorial/FreeRTOSTest/vl53l1/core/inc" -I"D:/STM32_AIFRARM/STM_Tutorial/FreeRTOSTest/modules/inc/estimator" -I"D:/STM32_AIFRARM/STM_Tutorial/FreeRTOSTest/platform/inc" -I"D:/STM32_AIFRARM/STM_Tutorial/FreeRTOSTest/CMSIS/Include" -I"D:/STM32_AIFRARM/STM_Tutorial/FreeRTOSTest/CMSIS/stm32f4xx_hal_driver/Inc" -I"D:/STM32_AIFRARM/STM_Tutorial/FreeRTOSTest/CMSIS/stm32f4xx_hal_driver/Inc/Legacy" -I"D:/STM32_AIFRARM/STM_Tutorial/FreeRTOSTest/FreeRTOS/include" -I"D:/STM32_AIFRARM/STM_Tutorial/FreeRTOSTest/drivers/inc" -I"D:/STM32_AIFRARM/STM_Tutorial/FreeRTOSTest/FreeRTOS/portable/GCC/ARM_CM4F" -I../Inc -I"D:/STM32_AIFRARM/STM_Tutorial/FreeRTOSTest/config" -I"D:/STM32_AIFRARM/STM_Tutorial/FreeRTOSTest/DSP_DRIVERS/Include" -I"D:/STM32_AIFRARM/STM_Tutorial/FreeRTOSTest/modules/inc/kalman_core" -I"D:/STM32_AIFRARM/STM_Tutorial/FreeRTOSTest/modules/inc" -I"D:/STM32_AIFRARM/STM_Tutorial/FreeRTOSTest/hal/inc" -I"D:/STM32_AIFRARM/STM_Tutorial/FreeRTOSTest/utils/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-modules-2f-src-2f-estimator

clean-modules-2f-src-2f-estimator:
	-$(RM) ./modules/src/estimator/estimator.cyclo ./modules/src/estimator/estimator.d ./modules/src/estimator/estimator.o ./modules/src/estimator/estimator.su ./modules/src/estimator/estimator_complementary.cyclo ./modules/src/estimator/estimator_complementary.d ./modules/src/estimator/estimator_complementary.o ./modules/src/estimator/estimator_complementary.su ./modules/src/estimator/estimator_kalman.cyclo ./modules/src/estimator/estimator_kalman.d ./modules/src/estimator/estimator_kalman.o ./modules/src/estimator/estimator_kalman.su ./modules/src/estimator/position_estimator_altitude.cyclo ./modules/src/estimator/position_estimator_altitude.d ./modules/src/estimator/position_estimator_altitude.o ./modules/src/estimator/position_estimator_altitude.su

.PHONY: clean-modules-2f-src-2f-estimator

