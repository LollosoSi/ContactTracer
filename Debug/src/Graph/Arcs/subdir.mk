################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Graph/Arcs/contact.cpp 

OBJS += \
./src/Graph/Arcs/contact.o 

CPP_DEPS += \
./src/Graph/Arcs/contact.d 


# Each subdirectory must supply rules for building sources it contributes
src/Graph/Arcs/%.o: ../src/Graph/Arcs/%.cpp src/Graph/Arcs/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


