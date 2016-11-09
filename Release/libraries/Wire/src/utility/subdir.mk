################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:\00-Programme\Eclipse32\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.14\libraries\Wire\src\utility\twi.c 

C_DEPS += \
.\libraries\Wire\src\utility\twi.c.d 

LINK_OBJ += \
.\libraries\Wire\src\utility\twi.c.o 


# Each subdirectory must supply rules for building sources it contributes
libraries\Wire\src\utility\twi.c.o: D:\00-Programme\Eclipse32\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.14\libraries\Wire\src\utility\twi.c
	@echo 'Building file: $<'
	@echo 'Starting C compile'
	"D:\00-Programme\Eclipse32\eclipse\arduinoPlugin\tools\arduino\avr-gcc\4.9.2-atmel3.5.3-arduino2/bin/avr-gcc" -c -g -Os -std=gnu11 -ffunction-sections -fdata-sections -MMD -flto -fno-fat-lto-objects -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10609 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR   -I"D:\00-Programme\Eclipse32\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.14\cores\arduino" -I"D:\00-Programme\Eclipse32\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.14\variants\mega" -I"D:\00-Programme\Eclipse32\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.14\libraries\Wire" -I"D:\00-Programme\Eclipse32\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.14\libraries\Wire\src" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 "$<" -o "$@"  -Wall
	@echo 'Finished building: $<'
	@echo ' '


