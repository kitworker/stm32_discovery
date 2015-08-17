################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lcd3310/lcd3310.c 

OBJS += \
./lcd3310/lcd3310.o 

C_DEPS += \
./lcd3310/lcd3310.d 


# Each subdirectory must supply rules for building sources it contributes
lcd3310/%.o: ../lcd3310/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC C Compiler'
	arm-none-eabi-gcc -DSTM32F10X_LD_VL -DUSE_STDPERIPH_DRIVER -I"D:\Discovery\Test_CopyWS160815\stm32_ld_vl\CMSIS" -I"D:\Discovery\Test_CopyWS160815\stm32_ld_vl\SPL\inc" -O0 -ffunction-sections -fdata-sections -Wall -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=cortex-m3 -mthumb -g3 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


