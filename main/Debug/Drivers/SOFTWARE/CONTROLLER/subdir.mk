################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/SOFTWARE/CONTROLLER/ute_ai.c 

OBJS += \
./Drivers/SOFTWARE/CONTROLLER/ute_ai.o 

C_DEPS += \
./Drivers/SOFTWARE/CONTROLLER/ute_ai.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/SOFTWARE/CONTROLLER/%.o Drivers/SOFTWARE/CONTROLLER/%.su: ../Drivers/SOFTWARE/CONTROLLER/%.c Drivers/SOFTWARE/CONTROLLER/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/HARDWARE -I../Drivers/SOFTWARE -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-SOFTWARE-2f-CONTROLLER

clean-Drivers-2f-SOFTWARE-2f-CONTROLLER:
	-$(RM) ./Drivers/SOFTWARE/CONTROLLER/ute_ai.d ./Drivers/SOFTWARE/CONTROLLER/ute_ai.o ./Drivers/SOFTWARE/CONTROLLER/ute_ai.su

.PHONY: clean-Drivers-2f-SOFTWARE-2f-CONTROLLER

