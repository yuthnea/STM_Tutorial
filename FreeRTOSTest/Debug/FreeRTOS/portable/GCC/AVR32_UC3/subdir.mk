################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../FreeRTOS/portable/GCC/AVR32_UC3/port.c 

S_UPPER_SRCS += \
../FreeRTOS/portable/GCC/AVR32_UC3/exception.S 

OBJS += \
./FreeRTOS/portable/GCC/AVR32_UC3/exception.o \
./FreeRTOS/portable/GCC/AVR32_UC3/port.o 

S_UPPER_DEPS += \
./FreeRTOS/portable/GCC/AVR32_UC3/exception.d 

C_DEPS += \
./FreeRTOS/portable/GCC/AVR32_UC3/port.d 


# Each subdirectory must supply rules for building sources it contributes
FreeRTOS/portable/GCC/AVR32_UC3/%.o: ../FreeRTOS/portable/GCC/AVR32_UC3/%.S FreeRTOS/portable/GCC/AVR32_UC3/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m4 -g3 -DDEBUG -c -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"
FreeRTOS/portable/GCC/AVR32_UC3/%.o FreeRTOS/portable/GCC/AVR32_UC3/%.su FreeRTOS/portable/GCC/AVR32_UC3/%.cyclo: ../FreeRTOS/portable/GCC/AVR32_UC3/%.c FreeRTOS/portable/GCC/AVR32_UC3/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32F405xx -DSTM32 -DSTM32F4 -DSTM32F405RGTx -c -I"D:/STM32_Project/FreeRTOSTest/FreeRTOS/include" -I"D:/STM32_Project/FreeRTOSTest/FreeRTOS/portable/GCC/ARM_CM4F" -I../Inc -I"D:/STM32_Project/FreeRTOSTest/config" -I"D:/STM32_Project/FreeRTOSTest/DSP_DRIVERS/Include" -I"D:/STM32_Project/FreeRTOSTest/modules/inc/kalman_core" -I"D:/STM32_Project/FreeRTOSTest/modules/inc" -I"D:/STM32_Project/FreeRTOSTest/hal/inc" -I"D:/STM32_Project/FreeRTOSTest/utils/inc" -I"D:/STM32_Project/FreeRTOSTest/CMSIS/Include" -I"D:/STM32_Project/FreeRTOSTest/CMSIS/STM32F4xx/Include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-FreeRTOS-2f-portable-2f-GCC-2f-AVR32_UC3

clean-FreeRTOS-2f-portable-2f-GCC-2f-AVR32_UC3:
	-$(RM) ./FreeRTOS/portable/GCC/AVR32_UC3/exception.d ./FreeRTOS/portable/GCC/AVR32_UC3/exception.o ./FreeRTOS/portable/GCC/AVR32_UC3/port.cyclo ./FreeRTOS/portable/GCC/AVR32_UC3/port.d ./FreeRTOS/portable/GCC/AVR32_UC3/port.o ./FreeRTOS/portable/GCC/AVR32_UC3/port.su

.PHONY: clean-FreeRTOS-2f-portable-2f-GCC-2f-AVR32_UC3

