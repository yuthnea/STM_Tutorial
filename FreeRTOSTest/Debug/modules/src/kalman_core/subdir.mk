################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../modules/src/kalman_core/kalman_core.c \
../modules/src/kalman_core/mm_absolute_height.c \
../modules/src/kalman_core/mm_distance.c \
../modules/src/kalman_core/mm_distance_robust.c \
../modules/src/kalman_core/mm_flow.c \
../modules/src/kalman_core/mm_pose.c \
../modules/src/kalman_core/mm_position.c \
../modules/src/kalman_core/mm_tof.c \
../modules/src/kalman_core/mm_yaw_error.c 

OBJS += \
./modules/src/kalman_core/kalman_core.o \
./modules/src/kalman_core/mm_absolute_height.o \
./modules/src/kalman_core/mm_distance.o \
./modules/src/kalman_core/mm_distance_robust.o \
./modules/src/kalman_core/mm_flow.o \
./modules/src/kalman_core/mm_pose.o \
./modules/src/kalman_core/mm_position.o \
./modules/src/kalman_core/mm_tof.o \
./modules/src/kalman_core/mm_yaw_error.o 

C_DEPS += \
./modules/src/kalman_core/kalman_core.d \
./modules/src/kalman_core/mm_absolute_height.d \
./modules/src/kalman_core/mm_distance.d \
./modules/src/kalman_core/mm_distance_robust.d \
./modules/src/kalman_core/mm_flow.d \
./modules/src/kalman_core/mm_pose.d \
./modules/src/kalman_core/mm_position.d \
./modules/src/kalman_core/mm_tof.d \
./modules/src/kalman_core/mm_yaw_error.d 


# Each subdirectory must supply rules for building sources it contributes
modules/src/kalman_core/%.o modules/src/kalman_core/%.su modules/src/kalman_core/%.cyclo: ../modules/src/kalman_core/%.c modules/src/kalman_core/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32F40_41xxx -DUSE_HAL_DRIVER -DARM_MATH_CM4 -DSTM32F405xx -c -I"D:/STM32_AIFRARM/STM_Tutorial/FreeRTOSTest/CMSIS/STM32F4xx/Include" -I"D:/STM32_AIFRARM/STM_Tutorial/FreeRTOSTest/deck/deck_spi/inc" -I"D:/STM32_AIFRARM/STM_Tutorial/FreeRTOSTest/deck/inc" -I"D:/STM32_AIFRARM/STM_Tutorial/FreeRTOSTest/vl53l1" -I"D:/STM32_AIFRARM/STM_Tutorial/FreeRTOSTest/vl53l1/core/inc" -I"D:/STM32_AIFRARM/STM_Tutorial/FreeRTOSTest/modules/inc/estimator" -I"D:/STM32_AIFRARM/STM_Tutorial/FreeRTOSTest/platform/inc" -I"D:/STM32_AIFRARM/STM_Tutorial/FreeRTOSTest/CMSIS/Include" -I"D:/STM32_AIFRARM/STM_Tutorial/FreeRTOSTest/CMSIS/stm32f4xx_hal_driver/Inc" -I"D:/STM32_AIFRARM/STM_Tutorial/FreeRTOSTest/CMSIS/stm32f4xx_hal_driver/Inc/Legacy" -I"D:/STM32_AIFRARM/STM_Tutorial/FreeRTOSTest/FreeRTOS/include" -I"D:/STM32_AIFRARM/STM_Tutorial/FreeRTOSTest/drivers/inc" -I"D:/STM32_AIFRARM/STM_Tutorial/FreeRTOSTest/FreeRTOS/portable/GCC/ARM_CM4F" -I../Inc -I"D:/STM32_AIFRARM/STM_Tutorial/FreeRTOSTest/config" -I"D:/STM32_AIFRARM/STM_Tutorial/FreeRTOSTest/DSP_DRIVERS/Include" -I"D:/STM32_AIFRARM/STM_Tutorial/FreeRTOSTest/modules/inc/kalman_core" -I"D:/STM32_AIFRARM/STM_Tutorial/FreeRTOSTest/modules/inc" -I"D:/STM32_AIFRARM/STM_Tutorial/FreeRTOSTest/hal/inc" -I"D:/STM32_AIFRARM/STM_Tutorial/FreeRTOSTest/utils/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-modules-2f-src-2f-kalman_core

clean-modules-2f-src-2f-kalman_core:
	-$(RM) ./modules/src/kalman_core/kalman_core.cyclo ./modules/src/kalman_core/kalman_core.d ./modules/src/kalman_core/kalman_core.o ./modules/src/kalman_core/kalman_core.su ./modules/src/kalman_core/mm_absolute_height.cyclo ./modules/src/kalman_core/mm_absolute_height.d ./modules/src/kalman_core/mm_absolute_height.o ./modules/src/kalman_core/mm_absolute_height.su ./modules/src/kalman_core/mm_distance.cyclo ./modules/src/kalman_core/mm_distance.d ./modules/src/kalman_core/mm_distance.o ./modules/src/kalman_core/mm_distance.su ./modules/src/kalman_core/mm_distance_robust.cyclo ./modules/src/kalman_core/mm_distance_robust.d ./modules/src/kalman_core/mm_distance_robust.o ./modules/src/kalman_core/mm_distance_robust.su ./modules/src/kalman_core/mm_flow.cyclo ./modules/src/kalman_core/mm_flow.d ./modules/src/kalman_core/mm_flow.o ./modules/src/kalman_core/mm_flow.su ./modules/src/kalman_core/mm_pose.cyclo ./modules/src/kalman_core/mm_pose.d ./modules/src/kalman_core/mm_pose.o ./modules/src/kalman_core/mm_pose.su ./modules/src/kalman_core/mm_position.cyclo ./modules/src/kalman_core/mm_position.d ./modules/src/kalman_core/mm_position.o ./modules/src/kalman_core/mm_position.su ./modules/src/kalman_core/mm_tof.cyclo ./modules/src/kalman_core/mm_tof.d ./modules/src/kalman_core/mm_tof.o ./modules/src/kalman_core/mm_tof.su ./modules/src/kalman_core/mm_yaw_error.cyclo ./modules/src/kalman_core/mm_yaw_error.d ./modules/src/kalman_core/mm_yaw_error.o ./modules/src/kalman_core/mm_yaw_error.su

.PHONY: clean-modules-2f-src-2f-kalman_core

