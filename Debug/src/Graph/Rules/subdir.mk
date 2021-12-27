################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Graph/Rules/rule.cpp 

OBJS += \
./src/Graph/Rules/rule.o 

CPP_DEPS += \
./src/Graph/Rules/rule.d 


# Each subdirectory must supply rules for building sources it contributes
src/Graph/Rules/%.o: ../src/Graph/Rules/%.cpp src/Graph/Rules/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


