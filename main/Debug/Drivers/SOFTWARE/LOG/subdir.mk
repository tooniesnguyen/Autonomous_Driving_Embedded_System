################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/SOFTWARE/LOG/log.c 

OBJS += \
./Drivers/SOFTWARE/LOG/log.o 

C_DEPS += \
./Drivers/SOFTWARE/LOG/log.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/SOFTWARE/LOG/%.o Drivers/SOFTWARE/LOG/%.su: ../Drivers/SOFTWARE/LOG/%.c Drivers/SOFTWARE/LOG/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/HARDWARE -I../Drivers/SOFTWARE -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-SOFTWARE-2f-LOG

clean-Drivers-2f-SOFTWARE-2f-LOG:
	-$(RM) ./Drivers/SOFTWARE/LOG/log.d ./Drivers/SOFTWARE/LOG/log.o ./Drivers/SOFTWARE/LOG/log.su

.PHONY: clean-Drivers-2f-SOFTWARE-2f-LOG

