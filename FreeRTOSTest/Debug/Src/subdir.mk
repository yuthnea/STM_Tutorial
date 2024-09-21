################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/main.c \
../Src/syscalls.c \
../Src/sysmem.c 

OBJS += \
./Src/main.o \
./Src/syscalls.o \
./Src/sysmem.o 

C_DEPS += \
./Src/main.d \
./Src/syscalls.d \
./Src/sysmem.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o Src/%.su Src/%.cyclo: ../Src/%.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32F40_41xxx -DUSE_HAL_DRIVER -DARM_MATH_CM4 -DSTM32F405xx -c -I"D:/STM32_AIFRARM/FreeRTOSTest/FreeRTOSTest/CMSIS/STM32F4xx/Include" -I"D:/STM32_AIFRARM/FreeRTOSTest/FreeRTOSTest/deck/deck_spi/inc" -I"D:/STM32_AIFRARM/FreeRTOSTest/FreeRTOSTest/deck/inc" -I"D:/STM32_AIFRARM/FreeRTOSTest/FreeRTOSTest/vl53l1" -I"D:/STM32_AIFRARM/FreeRTOSTest/FreeRTOSTest/vl53l1/core/inc" -I"D:/STM32_AIFRARM/FreeRTOSTest/FreeRTOSTest/modules/inc/estimator" -I"D:/STM32_AIFRARM/FreeRTOSTest/FreeRTOSTest/platform/inc" -I"D:/STM32_AIFRARM/FreeRTOSTest/FreeRTOSTest/CMSIS/Include" -I"D:/STM32_AIFRARM/FreeRTOSTest/FreeRTOSTest/CMSIS/stm32f4xx_hal_driver/Inc" -I"D:/STM32_AIFRARM/FreeRTOSTest/FreeRTOSTest/CMSIS/stm32f4xx_hal_driver/Inc/Legacy" -I"D:/STM32_AIFRARM/FreeRTOSTest/FreeRTOSTest/FreeRTOS/include" -I"D:/STM32_AIFRARM/FreeRTOSTest/FreeRTOSTest/drivers/inc" -I"D:/STM32_AIFRARM/FreeRTOSTest/FreeRTOSTest/FreeRTOS/portable/GCC/ARM_CM4F" -I../Inc -I"D:/STM32_AIFRARM/FreeRTOSTest/FreeRTOSTest/config" -I"D:/STM32_AIFRARM/FreeRTOSTest/FreeRTOSTest/DSP_DRIVERS/Include" -I"D:/STM32_AIFRARM/FreeRTOSTest/FreeRTOSTest/modules/inc/kalman_core" -I"D:/STM32_AIFRARM/FreeRTOSTest/FreeRTOSTest/modules/inc" -I"D:/STM32_AIFRARM/FreeRTOSTest/FreeRTOSTest/hal/inc" -I"D:/STM32_AIFRARM/FreeRTOSTest/FreeRTOSTest/utils/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src

clean-Src:
	-$(RM) ./Src/main.cyclo ./Src/main.d ./Src/main.o ./Src/main.su ./Src/syscalls.cyclo ./Src/syscalls.d ./Src/syscalls.o ./Src/syscalls.su ./Src/sysmem.cyclo ./Src/sysmem.d ./Src/sysmem.o ./Src/sysmem.su

.PHONY: clean-Src

