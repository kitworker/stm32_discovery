################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := cs-rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include lcd3310/subdir.mk
-include SPL/src/subdir.mk
-include CMSIS/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
SECONDARY_FLASH += \
stm32_ld_vl.hex \

SECONDARY_LIST += \
stm32_ld_vl.lst \

SECONDARY_SIZE += \
stm32_ld_vl.siz \


# All Target
all: stm32_ld_vl.elf secondary-outputs

# Tool invocations
stm32_ld_vl.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: ARM Sourcery Windows GCC C Linker'
	arm-none-eabi-gcc -T"D:\Discovery\Test_CopyWS160815\stm32_ld_vl\CMSIS\stm32f100c4.ld" -nostartfiles -Xlinker --gc-sections -Wl,-Map,"stm32_ld_vl.map" -mcpu=cortex-m3 -mthumb -g3 -o "stm32_ld_vl.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

stm32_ld_vl.hex: stm32_ld_vl.elf
	@echo 'Invoking: ARM Sourcery Windows GNU Create Flash Image'
	arm-none-eabi-objcopy -O ihex "stm32_ld_vl.elf"  "stm32_ld_vl.hex"
	@echo 'Finished building: $@'
	@echo ' '

stm32_ld_vl.lst: stm32_ld_vl.elf
	@echo 'Invoking: ARM Sourcery Windows GNU Create Listing'
	arm-none-eabi-objdump -h -S "stm32_ld_vl.elf" > "stm32_ld_vl.lst"
	@echo 'Finished building: $@'
	@echo ' '

stm32_ld_vl.siz: stm32_ld_vl.elf
	@echo 'Invoking: ARM Sourcery Windows GNU Print Size'
	arm-none-eabi-size  --format=berkeley "stm32_ld_vl.elf"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(SECONDARY_SIZE)$(OBJS)$(C_DEPS)$(ASM_DEPS)$(SECONDARY_FLASH)$(EXECUTABLES)$(SECONDARY_LIST)$(S_UPPER_DEPS) stm32_ld_vl.elf
	-@echo ' '

secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_LIST) $(SECONDARY_SIZE)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
