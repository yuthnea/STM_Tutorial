################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../vl53l1/core/src/vl53l1_api.c \
../vl53l1/core/src/vl53l1_api_calibration.c \
../vl53l1/core/src/vl53l1_api_core.c \
../vl53l1/core/src/vl53l1_api_debug.c \
../vl53l1/core/src/vl53l1_api_preset_modes.c \
../vl53l1/core/src/vl53l1_api_strings.c \
../vl53l1/core/src/vl53l1_core.c \
../vl53l1/core/src/vl53l1_core_support.c \
../vl53l1/core/src/vl53l1_error_strings.c \
../vl53l1/core/src/vl53l1_register_funcs.c \
../vl53l1/core/src/vl53l1_silicon_core.c \
../vl53l1/core/src/vl53l1_wait.c 

OBJS += \
./vl53l1/core/src/vl53l1_api.o \
./vl53l1/core/src/vl53l1_api_calibration.o \
./vl53l1/core/src/vl53l1_api_core.o \
./vl53l1/core/src/vl53l1_api_debug.o \
./vl53l1/core/src/vl53l1_api_preset_modes.o \
./vl53l1/core/src/vl53l1_api_strings.o \
./vl53l1/core/src/vl53l1_core.o \
./vl53l1/core/src/vl53l1_core_support.o \
./vl53l1/core/src/vl53l1_error_strings.o \
./vl53l1/core/src/vl53l1_register_funcs.o \
./vl53l1/core/src/vl53l1_silicon_core.o \
./vl53l1/core/src/vl53l1_wait.o 

C_DEPS += \
./vl53l1/core/src/vl53l1_api.d \
./vl53l1/core/src/vl53l1_api_calibration.d \
./vl53l1/core/src/vl53l1_api_core.d \
./vl53l1/core/src/vl53l1_api_debug.d \
./vl53l1/core/src/vl53l1_api_preset_modes.d \
./vl53l1/core/src/vl53l1_api_strings.d \
./vl53l1/core/src/vl53l1_core.d \
./vl53l1/core/src/vl53l1_core_support.d \
./vl53l1/core/src/vl53l1_error_strings.d \
./vl53l1/core/src/vl53l1_register_funcs.d \
./vl53l1/core/src/vl53l1_silicon_core.d \
./vl53l1/core/src/vl53l1_wait.d 


# Each subdirectory must supply rules for building sources it contributes
vl53l1/core/src/%.o vl53l1/core/src/%.su vl53l1/core/src/%.cyclo: ../vl53l1/core/src/%.c vl53l1/core/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32F40_41xxx -DUSE_HAL_DRIVER -DARM_MATH_CM4 -DSTM32F405xx -c -I"D:/STM32_AIFRARM/FreeRTOSTest/FreeRTOSTest/CMSIS/STM32F4xx/Include" -I"D:/STM32_AIFRARM/FreeRTOSTest/FreeRTOSTest/deck/deck_spi/inc" -I"D:/STM32_AIFRARM/FreeRTOSTest/FreeRTOSTest/deck/inc" -I"D:/STM32_AIFRARM/FreeRTOSTest/FreeRTOSTest/vl53l1" -I"D:/STM32_AIFRARM/FreeRTOSTest/FreeRTOSTest/vl53l1/core/inc" -I"D:/STM32_AIFRARM/FreeRTOSTest/FreeRTOSTest/modules/inc/estimator" -I"D:/STM32_AIFRARM/FreeRTOSTest/FreeRTOSTest/platform/inc" -I"D:/STM32_AIFRARM/FreeRTOSTest/FreeRTOSTest/CMSIS/Include" -I"D:/STM32_AIFRARM/FreeRTOSTest/FreeRTOSTest/CMSIS/stm32f4xx_hal_driver/Inc" -I"D:/STM32_AIFRARM/FreeRTOSTest/FreeRTOSTest/CMSIS/stm32f4xx_hal_driver/Inc/Legacy" -I"D:/STM32_AIFRARM/FreeRTOSTest/FreeRTOSTest/FreeRTOS/include" -I"D:/STM32_AIFRARM/FreeRTOSTest/FreeRTOSTest/drivers/inc" -I"D:/STM32_AIFRARM/FreeRTOSTest/FreeRTOSTest/FreeRTOS/portable/GCC/ARM_CM4F" -I../Inc -I"D:/STM32_AIFRARM/FreeRTOSTest/FreeRTOSTest/config" -I"D:/STM32_AIFRARM/FreeRTOSTest/FreeRTOSTest/DSP_DRIVERS/Include" -I"D:/STM32_AIFRARM/FreeRTOSTest/FreeRTOSTest/modules/inc/kalman_core" -I"D:/STM32_AIFRARM/FreeRTOSTest/FreeRTOSTest/modules/inc" -I"D:/STM32_AIFRARM/FreeRTOSTest/FreeRTOSTest/hal/inc" -I"D:/STM32_AIFRARM/FreeRTOSTest/FreeRTOSTest/utils/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-vl53l1-2f-core-2f-src

clean-vl53l1-2f-core-2f-src:
	-$(RM) ./vl53l1/core/src/vl53l1_api.cyclo ./vl53l1/core/src/vl53l1_api.d ./vl53l1/core/src/vl53l1_api.o ./vl53l1/core/src/vl53l1_api.su ./vl53l1/core/src/vl53l1_api_calibration.cyclo ./vl53l1/core/src/vl53l1_api_calibration.d ./vl53l1/core/src/vl53l1_api_calibration.o ./vl53l1/core/src/vl53l1_api_calibration.su ./vl53l1/core/src/vl53l1_api_core.cyclo ./vl53l1/core/src/vl53l1_api_core.d ./vl53l1/core/src/vl53l1_api_core.o ./vl53l1/core/src/vl53l1_api_core.su ./vl53l1/core/src/vl53l1_api_debug.cyclo ./vl53l1/core/src/vl53l1_api_debug.d ./vl53l1/core/src/vl53l1_api_debug.o ./vl53l1/core/src/vl53l1_api_debug.su ./vl53l1/core/src/vl53l1_api_preset_modes.cyclo ./vl53l1/core/src/vl53l1_api_preset_modes.d ./vl53l1/core/src/vl53l1_api_preset_modes.o ./vl53l1/core/src/vl53l1_api_preset_modes.su ./vl53l1/core/src/vl53l1_api_strings.cyclo ./vl53l1/core/src/vl53l1_api_strings.d ./vl53l1/core/src/vl53l1_api_strings.o ./vl53l1/core/src/vl53l1_api_strings.su ./vl53l1/core/src/vl53l1_core.cyclo ./vl53l1/core/src/vl53l1_core.d ./vl53l1/core/src/vl53l1_core.o ./vl53l1/core/src/vl53l1_core.su ./vl53l1/core/src/vl53l1_core_support.cyclo ./vl53l1/core/src/vl53l1_core_support.d ./vl53l1/core/src/vl53l1_core_support.o ./vl53l1/core/src/vl53l1_core_support.su ./vl53l1/core/src/vl53l1_error_strings.cyclo ./vl53l1/core/src/vl53l1_error_strings.d ./vl53l1/core/src/vl53l1_error_strings.o ./vl53l1/core/src/vl53l1_error_strings.su ./vl53l1/core/src/vl53l1_register_funcs.cyclo ./vl53l1/core/src/vl53l1_register_funcs.d ./vl53l1/core/src/vl53l1_register_funcs.o ./vl53l1/core/src/vl53l1_register_funcs.su ./vl53l1/core/src/vl53l1_silicon_core.cyclo ./vl53l1/core/src/vl53l1_silicon_core.d ./vl53l1/core/src/vl53l1_silicon_core.o ./vl53l1/core/src/vl53l1_silicon_core.su ./vl53l1/core/src/vl53l1_wait.cyclo ./vl53l1/core/src/vl53l1_wait.d ./vl53l1/core/src/vl53l1_wait.o ./vl53l1/core/src/vl53l1_wait.su

.PHONY: clean-vl53l1-2f-core-2f-src

