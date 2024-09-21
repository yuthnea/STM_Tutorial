################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../FreeRTOS/portable/GCC/RX200/port.c 

OBJS += \
./FreeRTOS/portable/GCC/RX200/port.o 

C_DEPS += \
./FreeRTOS/portable/GCC/RX200/port.d 


# Each subdirectory must supply rules for building sources it contributes
FreeRTOS/portable/GCC/RX200/%.o FreeRTOS/portable/GCC/RX200/%.su FreeRTOS/portable/GCC/RX200/%.cyclo: ../FreeRTOS/portable/GCC/RX200/%.c FreeRTOS/portable/GCC/RX200/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32F405xx -DSTM32 -DSTM32F4 -DSTM32F405RGTx -c -I"D:/STM32_Project/FreeRTOSTest/FreeRTOS/include" -I"D:/STM32_Project/FreeRTOSTest/FreeRTOS/portable/GCC/ARM_CM4F" -I../Inc -I"D:/STM32_Project/FreeRTOSTest/config" -I"D:/STM32_Project/FreeRTOSTest/DSP_DRIVERS/Include" -I"D:/STM32_Project/FreeRTOSTest/modules/inc/kalman_core" -I"D:/STM32_Project/FreeRTOSTest/modules/inc" -I"D:/STM32_Project/FreeRTOSTest/hal/inc" -I"D:/STM32_Project/FreeRTOSTest/utils/inc" -I"D:/STM32_Project/FreeRTOSTest/CMSIS/Include" -I"D:/STM32_Project/FreeRTOSTest/CMSIS/STM32F4xx/Include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-FreeRTOS-2f-portable-2f-GCC-2f-RX200

clean-FreeRTOS-2f-portable-2f-GCC-2f-RX200:
	-$(RM) ./FreeRTOS/portable/GCC/RX200/port.cyclo ./FreeRTOS/portable/GCC/RX200/port.d ./FreeRTOS/portable/GCC/RX200/port.o ./FreeRTOS/portable/GCC/RX200/port.su

.PHONY: clean-FreeRTOS-2f-portable-2f-GCC-2f-RX200

