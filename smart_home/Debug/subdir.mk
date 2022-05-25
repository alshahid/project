################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../DIO_prog.c \
../adc.c \
../keypad.c \
../lcd.c \
../main.c \
../servo.c \
../timer0.c 

OBJS += \
./DIO_prog.o \
./adc.o \
./keypad.o \
./lcd.o \
./main.o \
./servo.o \
./timer0.o 

C_DEPS += \
./DIO_prog.d \
./adc.d \
./keypad.d \
./lcd.d \
./main.d \
./servo.d \
./timer0.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega16 -DF_CPU=1000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


