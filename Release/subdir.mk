################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
INO_SRCS += \
..\MEGAmaison.ino 

CPP_SRCS += \
..\.ino.cpp 

LINK_OBJ += \
.\.ino.cpp.o 

INO_DEPS += \
.\MEGAmaison.ino.d 

CPP_DEPS += \
.\.ino.cpp.d 


# Each subdirectory must supply rules for building sources it contributes
.ino.cpp.o: ../.ino.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"D:\00-Programme\Eclipse32\eclipse\arduinoPlugin\tools\arduino\avr-gcc\4.9.2-atmel3.5.3-arduino2/bin/avr-g++" -c -g -Os -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -flto -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10609 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR   -I"D:\00-Programme\Eclipse32\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.14\cores\arduino" -I"D:\00-Programme\Eclipse32\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.14\variants\mega" -I"D:\00-Programme\Eclipse32\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.14\libraries\Wire" -I"D:\00-Programme\Eclipse32\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.14\libraries\Wire\src" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<" -o "$@"  -Wall
	@echo 'Finished building: $<'
	@echo ' '

MEGAmaison.o: ../MEGAmaison.ino
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"D:\00-Programme\Eclipse32\eclipse\arduinoPlugin\tools\arduino\avr-gcc\4.9.2-atmel3.5.3-arduino2/bin/avr-g++" -c -g -Os -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -flto -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10609 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR   -I"D:\00-Programme\Eclipse32\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.14\cores\arduino" -I"D:\00-Programme\Eclipse32\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.14\variants\mega" -I"D:\00-Programme\Eclipse32\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.14\libraries\Wire" -I"D:\00-Programme\Eclipse32\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.14\libraries\Wire\src" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<" -o "$@"  -Wall
	@echo 'Finished building: $<'
	@echo ' '


