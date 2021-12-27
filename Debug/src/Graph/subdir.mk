################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Graph/graph.cpp \
../src/Graph/node.cpp 

OBJS += \
./src/Graph/graph.o \
./src/Graph/node.o 

CPP_DEPS += \
./src/Graph/graph.d \
./src/Graph/node.d 


# Each subdirectory must supply rules for building sources it contributes
src/Graph/%.o: ../src/Graph/%.cpp src/Graph/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


