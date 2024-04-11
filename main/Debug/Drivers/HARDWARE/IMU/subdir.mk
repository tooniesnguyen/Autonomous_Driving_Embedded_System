################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/HARDWARE/IMU/bno055.c 

OBJS += \
./Drivers/HARDWARE/IMU/bno055.o 

C_DEPS += \
./Drivers/HARDWARE/IMU/bno055.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/HARDWARE/IMU/%.o Drivers/HARDWARE/IMU/%.su: ../Drivers/HARDWARE/IMU/%.c Drivers/HARDWARE/IMU/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/HARDWARE -I../Drivers/SOFTWARE -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-HARDWARE-2f-IMU

clean-Drivers-2f-HARDWARE-2f-IMU:
	-$(RM) ./Drivers/HARDWARE/IMU/bno055.d ./Drivers/HARDWARE/IMU/bno055.o ./Drivers/HARDWARE/IMU/bno055.su

.PHONY: clean-Drivers-2f-HARDWARE-2f-IMU

