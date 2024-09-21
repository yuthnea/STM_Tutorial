################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include vl53l1/core/src/subdir.mk
-include utils/src/subdir.mk
-include platform/src/subdir.mk
-include modules/src/kalman_core/subdir.mk
-include modules/src/estimator/subdir.mk
-include modules/src/controllers/subdir.mk
-include modules/src/subdir.mk
-include hal/src/subdir.mk
-include drivers/src/subdir.mk
-include deck/src/subdir.mk
-include deck/deck_spi/src/subdir.mk
-include Startup/subdir.mk
-include Src/subdir.mk
-include FreeRTOS/portable/MemMang/subdir.mk
-include FreeRTOS/portable/GCC/ARM_CM4F/subdir.mk
-include FreeRTOS/subdir.mk
-include CMSIS/stm32f4xx_hal_driver/Src/Legacy/subdir.mk
-include CMSIS/stm32f4xx_hal_driver/Src/subdir.mk
-include CMSIS/STM32F4xx/Source/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := FreeRTOSTest
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
FreeRTOSTest.elf \

MAP_FILES += \
FreeRTOSTest.map \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
FreeRTOSTest.list \


# All Target
all: main-build

# Main-build Target
main-build: FreeRTOSTest.elf secondary-outputs

# Tool invocations
FreeRTOSTest.elf FreeRTOSTest.map: $(OBJS) $(USER_OBJS) D:\STM32_AIFRARM\FreeRTOSTest\FreeRTOSTest\STM32F405RGTX_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -o "FreeRTOSTest.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m4 -T"D:\STM32_AIFRARM\FreeRTOSTest\FreeRTOSTest\STM32F405RGTX_FLASH.ld" --specs=nosys.specs -Wl,-Map="FreeRTOSTest.map" -Wl,--gc-sections -static -L"D:\STM32_AIFRARM\FreeRTOSTest\FreeRTOSTest\DSP_DRIVERS\Lib\GCC" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

FreeRTOSTest.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "FreeRTOSTest.list"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) FreeRTOSTest.elf FreeRTOSTest.list FreeRTOSTest.map default.size.stdout
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified

-include ../makefile.targets
