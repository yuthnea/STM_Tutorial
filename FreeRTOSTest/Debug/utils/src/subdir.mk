################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../utils/src/cfassert.c \
../utils/src/filter.c \
../utils/src/num.c \
../utils/src/pid.c \
../utils/src/rateSupervisor.c \
../utils/src/sleepus.c 

OBJS += \
./utils/src/cfassert.o \
./utils/src/filter.o \
./utils/src/num.o \
./utils/src/pid.o \
./utils/src/rateSupervisor.o \
./utils/src/sleepus.o 

C_DEPS += \
./utils/src/cfassert.d \
./utils/src/filter.d \
./utils/src/num.d \
./utils/src/pid.d \
./utils/src/rateSupervisor.d \
./utils/src/sleepus.d 


# Each subdirectory must supply rules for building sources it contributes
utils/src/%.o utils/src/%.su utils/src/%.cyclo: ../utils/src/%.c utils/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32F40_41xxx -DUSE_HAL_DRIVER -DARM_MATH_CM4 -DSTM32F405xx -c -I"D:/STM32_AIFRARM/STM_Tutorial/FreeRTOSTest/CMSIS/STM32F4xx/Include" -I"D:/STM32_AIFRARM/STM_Tutorial/FreeRTOSTest/deck/deck_spi/inc" -I"D:/STM32_AIFRARM/STM_Tutorial/FreeRTOSTest/deck/inc" -I"D:/STM32_AIFRARM/STM_Tutorial/FreeRTOSTest/vl53l1" -I"D:/STM32_AIFRARM/STM_Tutorial/FreeRTOSTest/vl53l1/core/inc" -I"D:/STM32_AIFRARM/STM_Tutorial/FreeRTOSTest/modules/inc/estimator" -I"D:/STM32_AIFRARM/STM_Tutorial/FreeRTOSTest/platform/inc" -I"D:/STM32_AIFRARM/STM_Tutorial/FreeRTOSTest/CMSIS/Include" -I"D:/STM32_AIFRARM/STM_Tutorial/FreeRTOSTest/CMSIS/stm32f4xx_hal_driver/Inc" -I"D:/STM32_AIFRARM/STM_Tutorial/FreeRTOSTest/CMSIS/stm32f4xx_hal_driver/Inc/Legacy" -I"D:/STM32_AIFRARM/STM_Tutorial/FreeRTOSTest/FreeRTOS/include" -I"D:/STM32_AIFRARM/STM_Tutorial/FreeRTOSTest/drivers/inc" -I"D:/STM32_AIFRARM/STM_Tutorial/FreeRTOSTest/FreeRTOS/portable/GCC/ARM_CM4F" -I../Inc -I"D:/STM32_AIFRARM/STM_Tutorial/FreeRTOSTest/config" -I"D:/STM32_AIFRARM/STM_Tutorial/FreeRTOSTest/DSP_DRIVERS/Include" -I"D:/STM32_AIFRARM/STM_Tutorial/FreeRTOSTest/modules/inc/kalman_core" -I"D:/STM32_AIFRARM/STM_Tutorial/FreeRTOSTest/modules/inc" -I"D:/STM32_AIFRARM/STM_Tutorial/FreeRTOSTest/hal/inc" -I"D:/STM32_AIFRARM/STM_Tutorial/FreeRTOSTest/utils/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-utils-2f-src

clean-utils-2f-src:
	-$(RM) ./utils/src/cfassert.cyclo ./utils/src/cfassert.d ./utils/src/cfassert.o ./utils/src/cfassert.su ./utils/src/filter.cyclo ./utils/src/filter.d ./utils/src/filter.o ./utils/src/filter.su ./utils/src/num.cyclo ./utils/src/num.d ./utils/src/num.o ./utils/src/num.su ./utils/src/pid.cyclo ./utils/src/pid.d ./utils/src/pid.o ./utils/src/pid.su ./utils/src/rateSupervisor.cyclo ./utils/src/rateSupervisor.d ./utils/src/rateSupervisor.o ./utils/src/rateSupervisor.su ./utils/src/sleepus.cyclo ./utils/src/sleepus.d ./utils/src/sleepus.o ./utils/src/sleepus.su

.PHONY: clean-utils-2f-src

