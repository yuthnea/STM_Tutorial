################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../modules/src/axis3fSubSampler.c \
../modules/src/kalman_supervisor.c \
../modules/src/range.c \
../modules/src/sensfusion6.c \
../modules/src/stabilizer.c \
../modules/src/static_mem.c \
../modules/src/system.c \
../modules/src/worker.c 

OBJS += \
./modules/src/axis3fSubSampler.o \
./modules/src/kalman_supervisor.o \
./modules/src/range.o \
./modules/src/sensfusion6.o \
./modules/src/stabilizer.o \
./modules/src/static_mem.o \
./modules/src/system.o \
./modules/src/worker.o 

C_DEPS += \
./modules/src/axis3fSubSampler.d \
./modules/src/kalman_supervisor.d \
./modules/src/range.d \
./modules/src/sensfusion6.d \
./modules/src/stabilizer.d \
./modules/src/static_mem.d \
./modules/src/system.d \
./modules/src/worker.d 


# Each subdirectory must supply rules for building sources it contributes
modules/src/%.o modules/src/%.su modules/src/%.cyclo: ../modules/src/%.c modules/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32F40_41xxx -DUSE_HAL_DRIVER -DARM_MATH_CM4 -DSTM32F405xx -c -I"D:/STM32_AIFRARM/STM_Tutorial/FreeRTOSTest/CMSIS/STM32F4xx/Include" -I"D:/STM32_AIFRARM/STM_Tutorial/FreeRTOSTest/deck/deck_spi/inc" -I"D:/STM32_AIFRARM/STM_Tutorial/FreeRTOSTest/deck/inc" -I"D:/STM32_AIFRARM/STM_Tutorial/FreeRTOSTest/vl53l1" -I"D:/STM32_AIFRARM/STM_Tutorial/FreeRTOSTest/vl53l1/core/inc" -I"D:/STM32_AIFRARM/STM_Tutorial/FreeRTOSTest/modules/inc/estimator" -I"D:/STM32_AIFRARM/STM_Tutorial/FreeRTOSTest/platform/inc" -I"D:/STM32_AIFRARM/STM_Tutorial/FreeRTOSTest/CMSIS/Include" -I"D:/STM32_AIFRARM/STM_Tutorial/FreeRTOSTest/CMSIS/stm32f4xx_hal_driver/Inc" -I"D:/STM32_AIFRARM/STM_Tutorial/FreeRTOSTest/CMSIS/stm32f4xx_hal_driver/Inc/Legacy" -I"D:/STM32_AIFRARM/STM_Tutorial/FreeRTOSTest/FreeRTOS/include" -I"D:/STM32_AIFRARM/STM_Tutorial/FreeRTOSTest/drivers/inc" -I"D:/STM32_AIFRARM/STM_Tutorial/FreeRTOSTest/FreeRTOS/portable/GCC/ARM_CM4F" -I../Inc -I"D:/STM32_AIFRARM/STM_Tutorial/FreeRTOSTest/config" -I"D:/STM32_AIFRARM/STM_Tutorial/FreeRTOSTest/DSP_DRIVERS/Include" -I"D:/STM32_AIFRARM/STM_Tutorial/FreeRTOSTest/modules/inc/kalman_core" -I"D:/STM32_AIFRARM/STM_Tutorial/FreeRTOSTest/modules/inc" -I"D:/STM32_AIFRARM/STM_Tutorial/FreeRTOSTest/hal/inc" -I"D:/STM32_AIFRARM/STM_Tutorial/FreeRTOSTest/utils/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-modules-2f-src

clean-modules-2f-src:
	-$(RM) ./modules/src/axis3fSubSampler.cyclo ./modules/src/axis3fSubSampler.d ./modules/src/axis3fSubSampler.o ./modules/src/axis3fSubSampler.su ./modules/src/kalman_supervisor.cyclo ./modules/src/kalman_supervisor.d ./modules/src/kalman_supervisor.o ./modules/src/kalman_supervisor.su ./modules/src/range.cyclo ./modules/src/range.d ./modules/src/range.o ./modules/src/range.su ./modules/src/sensfusion6.cyclo ./modules/src/sensfusion6.d ./modules/src/sensfusion6.o ./modules/src/sensfusion6.su ./modules/src/stabilizer.cyclo ./modules/src/stabilizer.d ./modules/src/stabilizer.o ./modules/src/stabilizer.su ./modules/src/static_mem.cyclo ./modules/src/static_mem.d ./modules/src/static_mem.o ./modules/src/static_mem.su ./modules/src/system.cyclo ./modules/src/system.d ./modules/src/system.o ./modules/src/system.su ./modules/src/worker.cyclo ./modules/src/worker.d ./modules/src/worker.o ./modules/src/worker.su

.PHONY: clean-modules-2f-src

