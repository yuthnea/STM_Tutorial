################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../FreeRTOS/portable/GCC/ARM7_LPC23xx/port.c \
../FreeRTOS/portable/GCC/ARM7_LPC23xx/portISR.c 

OBJS += \
./FreeRTOS/portable/GCC/ARM7_LPC23xx/port.o \
./FreeRTOS/portable/GCC/ARM7_LPC23xx/portISR.o 

C_DEPS += \
./FreeRTOS/portable/GCC/ARM7_LPC23xx/port.d \
./FreeRTOS/portable/GCC/ARM7_LPC23xx/portISR.d 


# Each subdirectory must supply rules for building sources it contributes
FreeRTOS/portable/GCC/ARM7_LPC23xx/%.o FreeRTOS/portable/GCC/ARM7_LPC23xx/%.su FreeRTOS/portable/GCC/ARM7_LPC23xx/%.cyclo: ../FreeRTOS/portable/GCC/ARM7_LPC23xx/%.c FreeRTOS/portable/GCC/ARM7_LPC23xx/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32F405xx -DSTM32 -DSTM32F4 -DSTM32F405RGTx -c -I"D:/STM32_Project/FreeRTOSTest/FreeRTOS/include" -I"D:/STM32_Project/FreeRTOSTest/FreeRTOS/portable/GCC/ARM_CM4F" -I../Inc -I"D:/STM32_Project/FreeRTOSTest/config" -I"D:/STM32_Project/FreeRTOSTest/DSP_DRIVERS/Include" -I"D:/STM32_Project/FreeRTOSTest/modules/inc/kalman_core" -I"D:/STM32_Project/FreeRTOSTest/modules/inc" -I"D:/STM32_Project/FreeRTOSTest/hal/inc" -I"D:/STM32_Project/FreeRTOSTest/utils/inc" -I"D:/STM32_Project/FreeRTOSTest/CMSIS/Include" -I"D:/STM32_Project/FreeRTOSTest/CMSIS/STM32F4xx/Include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-FreeRTOS-2f-portable-2f-GCC-2f-ARM7_LPC23xx

clean-FreeRTOS-2f-portable-2f-GCC-2f-ARM7_LPC23xx:
	-$(RM) ./FreeRTOS/portable/GCC/ARM7_LPC23xx/port.cyclo ./FreeRTOS/portable/GCC/ARM7_LPC23xx/port.d ./FreeRTOS/portable/GCC/ARM7_LPC23xx/port.o ./FreeRTOS/portable/GCC/ARM7_LPC23xx/port.su ./FreeRTOS/portable/GCC/ARM7_LPC23xx/portISR.cyclo ./FreeRTOS/portable/GCC/ARM7_LPC23xx/portISR.d ./FreeRTOS/portable/GCC/ARM7_LPC23xx/portISR.o ./FreeRTOS/portable/GCC/ARM7_LPC23xx/portISR.su

.PHONY: clean-FreeRTOS-2f-portable-2f-GCC-2f-ARM7_LPC23xx

